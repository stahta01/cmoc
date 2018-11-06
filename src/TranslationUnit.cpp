/*  $Id: TranslationUnit.cpp,v 1.58 2016/09/11 20:23:13 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2016 Pierre Sarrazin <http://sarrazip.com/>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TranslationUnit.h"

#include "TreeSequence.h"
#include "DeclarationSequence.h"
#include "FunctionDef.h"
#include "SemanticsChecker.h"
#include "FunctionCallExpr.h"
#include "Scope.h"
#include "StringLiteralExpr.h"
#include "ClassDef.h"
#include "Pragma.h"

#include <assert.h>
#include <errno.h>
#include <fstream>

using namespace std;


/*static*/ TranslationUnit *TranslationUnit::theInstance = NULL;


/*static*/
TranslationUnit &
TranslationUnit::instance()
{
    assert(theInstance);
    return *theInstance;
}


TranslationUnit::TranslationUnit(TargetPlatform _targetPlatform)
  : typeManager(),
    globalScope(NULL),
    definitionList(NULL),
    functionDefs(),
    callGraph(),
    globalVariables(),
    scopeStack(),
    breakableStack(),
    functionEndLabel(),
    labelGeneratorIndex(0),
    stringLiteralLabelToValue(),
    stringLiteralValueToLabel(),
    builtInFunctionDescs(),
    numNonRelocatableExpressions(0),
    isProgramExecutableOnlyOnce(false),
    nullPointerCheckingEnabled(false),
    stackOverflowCheckingEnabled(false),
    neededUtilitySubRoutines(),
    targetPlatform(_targetPlatform),
    vxTitle("CMOC"),
    vxMusic("vx_music_1"),
    vxTitleSizeWidth(80),
    vxTitleSizeHeight(-8),
    vxTitlePosX(-0x56),
    vxTitlePosY(0x20),
    vxCopyright("2015")
{
    theInstance = this;  // instance() needed by Scope constructor
    typeManager.createBasicTypes();
    globalScope = new Scope(NULL);  // requires 'void', i.e., must come after createBasicTypes()
    typeManager.createInternalStructs(*globalScope);  // global scope must be created; receives internal structs

    //typeManager.dumpTypes(cout); // dumps all predefined types in C notation
}


void
TranslationUnit::setDefinitionList(TreeSequence *defList)
{
    delete definitionList;
    definitionList = defList;
}


void
TranslationUnit::addFunctionDef(FunctionDef *fd)
{
    if (fd == NULL)
        return;
    functionDefs[fd->getId()] = fd;
}


void
TranslationUnit::removeFunctionDef(FunctionDef *fd)
{
    if (fd == NULL)
        return;
    functionDefs.erase(fd->getId());
}


void
TranslationUnit::registerFunction(FunctionDef *fd)
{
    if (fd == NULL)
        return;

    FunctionDef *preexisting = getFunctionDef(fd->getId());
    if (preexisting != NULL)
    {
        bool sameRetType = preexisting->hasSameReturnType(*fd);
        bool sameParams  = preexisting->hasSameFormalParams(*fd);
        if (!sameRetType || !sameParams)
        {
            const char *msg = NULL, *be = "are";
            if (!sameRetType && !sameParams)
                msg = "return type and formal parameters";
            else if (!sameRetType)
                msg = "return type", be = "is";
            else if (!sameParams)
                msg = "formal parameters";

            fd->errormsg("%s for %s() %s different from previously declared at %s",
                         msg, fd->getId().c_str(), be, preexisting->getLineNo().c_str());
        }
        if (fd->getId() == "main")
            fd->errormsg("main() cannot be declared or defined more than once");
        if (preexisting->getBody() != NULL && fd->getBody() != NULL)
            fd->errormsg("%s() already has a body at %s",
                         fd->getId().c_str(), preexisting->getLineNo().c_str());
        if (preexisting->getBody() == NULL && fd->getBody() != NULL)
        {
            removeFunctionDef(preexisting);
            addFunctionDef(fd);
        }
        return;
    }

    if (fd->getId() == "main")
    {
        const TypeDesc *returnType = fd->getTypeDesc();
        assert(returnType->isValid());
        if (returnType->type != WORD_TYPE || !returnType->isSigned)
            fd->errormsg("return type of main() must be int");
        if (fd->getNumFormalParams() != 0)
            fd->errormsg("main() cannot have parameters");
    }

    addFunctionDef(fd);
}


void
TranslationUnit::registerFunctionCall(const string &callerId, const string &calleeId)
{
    pushBackUnique(callGraph[callerId], calleeId);
}


// Checks function prototypes, definitions and calls.
//
class FunctionChecker : public Tree::Functor
{
public:
    FunctionChecker()
    :   declaredFunctions(), undefinedFunctions(), definedFunctions(), calledFunctions()
    {
    }
    virtual bool open(Tree *t)
    {
        if (FunctionDef *fd = dynamic_cast<FunctionDef *>(t))
        {
            processFunctionDef(fd);
        }
        else if (FunctionCallExpr *fc = dynamic_cast<FunctionCallExpr *>(t))
        {
            if (!fc->isCallThroughPointer())
            {
                string funcId = fc->getIdentifier();
                calledFunctions.insert(funcId);
                if (declaredFunctions.find(funcId) == declaredFunctions.end())  // if unknown ID
                    fc->errormsg("calling undeclared function %s()", funcId.c_str());
            }
        }
        return true;
    }
    virtual bool close(Tree * /*t*/)
    {
        return true;
    }
    void reportErrors() const
    {
        for (map<string, const FunctionDef *>::const_iterator it = undefinedFunctions.begin();
                                                             it != undefinedFunctions.end(); ++it)
        {
            const string& funcId = it->first;

            // If the undefined function is not provided by the compiler,
            // and it is called by the program, then report it as undefined.
            //
            if (! TranslationUnit::instance().isStandardFunction(funcId)
                    && calledFunctions.find(funcId) != calledFunctions.end())
            {
                it->second->errormsg("function %s() declared and called but not defined", funcId.c_str());
            }
        }
    }
private:
    void processFunctionDef(FunctionDef *fd)
    {
        string funcId = fd->getId();
        declaredFunctions.insert(funcId);

        if (fd->getBody() == NULL)  // if prototype:
        {
            if (definedFunctions.find(funcId) == definedFunctions.end())  // if body not seen:
                undefinedFunctions[funcId] = fd;  // remember that this function is declared and might lack a definition
        }
        else  // if body:
        {
            definedFunctions.insert(funcId);  // remember that this function is defined
            map<string, const FunctionDef *>::iterator it = undefinedFunctions.find(funcId);
            if (it != undefinedFunctions.end())  // if prototype seen:
                undefinedFunctions.erase(it);  // not undefined anymore
        }
    }

    set<string> declaredFunctions;
    map<string, const FunctionDef *> undefinedFunctions;
    set<string> definedFunctions;
    set<string> calledFunctions;
};


void
TranslationUnit::checkSemantics()
{
    if (!definitionList)
        return;

    vector<const Declaration *> constDataDeclarationsToCheck;
    constDataDeclarationsToCheck.reserve(32);

    /*  Declare all functions and global variables before
        interpreting any code.

        Global variables are stored in globalVariables in the order in which
        they are declared. This is necessary to emit correct initializers.
        Example: word a = 42; word b = a;
    */
    bool inConstDataSection = false;  // true when inside a '#pragma const_start' section
    assert(scopeStack.size() == 0);  // ensure current scope is global one
    for (vector<Tree *>::iterator it = definitionList->begin();
                                 it != definitionList->end(); it++)
    {
        FunctionDef *fd = dynamic_cast<FunctionDef *>(*it);
        if (fd != NULL)
        {
            #if 0
            cerr << "Registering function " << fd->getId() << " at "
                    << fd << " which has "
                    << (fd->getBody() ? "a" : "no") << " body\n";
            #endif
            registerFunction(fd);
            continue;
        }

        DeclarationSequence *declSeq = dynamic_cast<DeclarationSequence *>(*it);
        if (declSeq != NULL)
        {
            for (std::vector<Tree *>::iterator it = declSeq->begin(); it != declSeq->end(); ++it)
            {
                if (Declaration *decl = dynamic_cast<Declaration *>(*it))
                {
                    //cerr << "# Declaring global variable " << decl->getVariableId() << " at line " << decl->getLineNo() << "\n";
                    bool hasExtern = false;

                    if (!decl->isExtern)
                        globalVariables.push_back(decl);

                    if (!globalScope->declareVariable(decl))
                    {
                        const Declaration *existingDecl = globalScope->getVariableDeclaration(decl->getVariableId(), false);
                        assert(existingDecl);
                        if (!existingDecl->isExtern)
                            decl->errormsg("global variable `%s' already declared at global scope at %s",
                                       decl->getVariableId().c_str(), existingDecl->getLineNo().c_str());

                        hasExtern = true;
                    }

                    decl->setGlobal(true);
                    decl->setReadOnly(inConstDataSection);

                    if (inConstDataSection)
                        constDataDeclarationsToCheck.push_back(decl);  // do check after ExpressionTypeSetter

                    // Set the assembly label on this global variable.
                    uint16_t size = 0;
                    if (!decl->getVariableSizeInBytes(size))
                        decl->errormsg("invalid dimensions for array %s", decl->getVariableId().c_str());
                    else
                    {
                        if (decl->isExtern || hasExtern)
                            decl->setLabel("_" + decl->getVariableId());
                        else
                            decl->setLabel(generateLabel('G'));
                    }
                }
                else if (FunctionDef *fd = dynamic_cast<FunctionDef *>(*it))
                {
                    assert(fd->getBody() == NULL);  // only prototype expected here, not function definition
                    registerFunction(fd);
                }
                else
                    assert(false);
            }
            continue;
        }

        ClassDef *cd = dynamic_cast<ClassDef *>(*it);
        if (cd != NULL)
        {
            //cerr << "Declaring class '" << cd->getName() << "'\n";
            globalScope->declareClass(cd);
            continue;
        }

        if (Pragma *pragma = dynamic_cast<Pragma *>(*it))
        {
            bool isStart = false;
            if (pragma->isConstData(isStart))  // if #pragma const_start
            {
                inConstDataSection = isStart;  // "start" or "end" argument starts or ends section
            }
            continue;
        }
    }


    class StringLiteralRegistererererer : public Tree::Functor
    {
    public:
        virtual bool open(Tree *t)
        {
            StringLiteralExpr *sle = dynamic_cast<StringLiteralExpr *>(t);
            if (sle != NULL)
                sle->setLabel(TranslationUnit::instance().registerStringLiteral(*sle));
            return true;
        }
        virtual bool close(Tree * /*t*/)
        {
            return true;
        }
    };

    StringLiteralRegistererererer r;
    definitionList->iterate(r);


    // Set the TypeDesc of all enumerated names.
    //
    getTypeManager().setEnumeratorTypes();


    // Among other things, the ExpressionTypeSetter is run over the function bodies
    // during the following step.
    //
    SemanticsChecker sc;
    definitionList->iterate(sc);


    // Check the initializers of declarations found in const_data sections.
    // This step assumes that the ExpressionTypeSetter has been run.
    //
    for (vector<const Declaration *>::const_iterator it = constDataDeclarationsToCheck.begin();
                                                    it != constDataDeclarationsToCheck.end(); ++it)
        checkConstDataDeclarationInitializer(**it);


    // The following step assumes that the ExpressionTypeSetter has been run
    // over the function bodies, so that function calls that use a function pointer
    // can be differentiated from standard calls.
    //
    FunctionChecker ufc;
    definitionList->iterate(ufc);
    ufc.reportErrors();
}


// This method assumes that the ExpressionTypeSetter has been run.
// This ensures that an initializer like -1, which is represented as a UnaryOpExpr,
// is typed as WORD_TYPE, for example.
//
void
TranslationUnit::checkConstDataDeclarationInitializer(const Declaration &decl) const
{
    uint16_t result = 0;
    if (decl.initializationExpr == NULL)
    {
        decl.errormsg("global variable '%s' declared in const_data section but has no initializer",
                        decl.getVariableId().c_str());
    }
    else if (! decl.initializationExpr->evaluateConstantExpr(result) && ! decl.isArrayWithIntegerInitValues())
    {
        decl.errormsg("global variable '%s' declared in const_data section but has a run-time initializer",
                        decl.getVariableId().c_str());
    }
}


void
TranslationUnit::setTargetPlatform(TargetPlatform platform)
{
    targetPlatform = platform;
}


TargetPlatform
TranslationUnit::getTargetPlatform() const
{
    return targetPlatform;
}


// Calls setCalled() on each function called from the entry point.
//
void TranslationUnit::detectCalledFunctions()
{
    // Accumulate a list of functions called directly or indirectly from the entry point,
    // i.e., the internal code that calls main().
    //
    StringVector calledFunctionIds;
    calledFunctionIds.push_back("main");  // main() is always called

    size_t index = 0, initSize = 0;
    do
    {
        // Process each function in calledFunctionIds[] starting at 'index',
        // up to the current size of calledFunctionIds.
        //
        initSize = calledFunctionIds.size();

        for ( ; index < initSize; ++index)  // for each caller to process
        {
            const string &callerId = calledFunctionIds[index];

            // Get the list of functions called by 'callerId'.
            //
            StringGraph::const_iterator it = callGraph.find(callerId);
            if (it == callGraph.end())
                continue;  // not expected

            // For each function called by 'callerId', add that function to
            // 'calledFunctionIds'. Note that 'size' marks the end of the
            // functions that were in this list before the for() loop.
            // Any new name added by pushBackUnique() will be beyond 'size'.
            //
            const StringVector &callees = it->second;
            for (StringVector::const_iterator jt = callees.begin(); jt != callees.end(); ++jt)
            {
                const string &calleeId = *jt;
                pushBackUnique(calledFunctionIds, calleeId);
            }
        }

        // If the preceding for() loop added new names to 'calledFunctionIds',
        // then we have new callers to process, so we do another iteration.
        // Note that 'index' is now 'initSize', which means the next iteration
        // will only process the newly added names.
        assert(index == initSize);

    } while (calledFunctionIds.size() > initSize);

    // 'calledFunctionIds' is now the total list of functions called from the entry point.
    // Mark each of them as called. Assembly code will be emitted for those functions.
    //
    for (StringVector::const_iterator jt = calledFunctionIds.begin(); jt != calledFunctionIds.end(); ++jt)
    {
        FunctionDef *fd = getFunctionDef(*jt);
        if (fd)
            fd->setCalled();
    }
}


void
TranslationUnit::allocateLocalVariables()
{
    for (map<string, FunctionDef *>::iterator  kt = functionDefs.begin(); kt != functionDefs.end(); kt++)
        kt->second->allocateLocalVariables();
}


// setTargetPlatform() must have been called before calling this method.
// Stops short if an error is detected.
// emitUncalledFunctions: Emits a function even if it is never called by C code.
//
void
TranslationUnit::emitAssembler(ASMText &out, const string &programName, bool compileOnly,
                               uint16_t codeAddress, uint16_t dataAddress,
                               bool emitBootLoaderMarker, bool emitUncalledFunctions)
{
    detectCalledFunctions();

    out.emitComment("6809 assembly program generated by " + string(PACKAGE) + " " + string(VERSION));

    if (targetPlatform == OS9)
    {
        out.emitSeparatorComment();
        out.emitComment("OS-9 DATA SECTION");
        out.ins("ORG", "0");

        // Generate the global variables.
        //
        out.emitSeparatorComment();
        out.emitComment("READ-ONLY GLOBAL VARIABLES");
        if (!emitGlobalVariables(out, true, true))
            return;
        emitWritableGlobals(out);


        out.emitLabel("stack");
        out.ins("RMB", "stack_space");  // stack_space is defined in stdlib.inc
        out.emitLabel("datsiz");
        out.emitSeparatorComment();
        out.emitComment("OS-9 MODULE");
        out.ins("mod", "length,name,$11,$81,program_start,datsiz");
        out.emitLabel("name");
        out.ins("fcs", "\"" + programName + "\"");
    }
    else if (targetPlatform == VECTREX)
    {
        out.emitComment("VECTREX");
        out.ins("ORG", "0");
        out.ins("fcc", "'g GCE " + vxCopyright + "'");
        out.ins("fcb", "$80");
        out.ins("fdb", vxMusic);
        out.ins("fcb", int8ToString(vxTitleSizeHeight, true));
        out.ins("fcb", int8ToString(vxTitleSizeWidth, true));
        out.ins("fcb", int8ToString(vxTitlePosY, true));
        out.ins("fcb", int8ToString(vxTitlePosX, true));
        out.ins("fcc", "'" + vxTitle + "'");
        out.ins("fcb", "$80");
        out.ins("fcb", "0");
    }
    else
        out.ins("ORG", wordToString(codeAddress, true), "Code section");

    out.emitLabel("program_start");

    if (emitBootLoaderMarker)
        out.ins("FCC", "\"OS\"", "marker for CoCo DECB DOS command");

    if (targetPlatform == OS9)
    {
        // OS-9 launches a process by passing it the start and end addresses of
        // its data segment in U and Y respectively. We transfer U (the start)
        // to Y because CMOC uses U to point to the stack frame. Every reference
        // to a global variable under OS-9 and CMOC thus has the form FOO,Y.
        // Variable FOO must have been declared with an RMB directive in a section
        // that starts with ORG 0. This way, FOO represents an offset from the
        // start of the data segment of the current process.
        // This convention is used by Declaration::getFrameDisplacementArg().
        //
        // CAUTION: All of the emitted code must be careful to preserve Y.
        //
        out.ins("LEAY", ",U", "point Y to start of static data of OS-9 process");
    }


    // Find the function named 'main':

    FunctionDef *mainFunctionDef = NULL;
    if (!compileOnly)
    {
        map<string, FunctionDef *>::iterator kt = functionDefs.find("main");
        if (kt == functionDefs.end())
        {
            errormsg("main() undefined");
            return;
        }
        mainFunctionDef = kt->second;
    }


    // Start the program by initializing the global variables, then
    // jumping to the main() function's label.

    if (targetPlatform == VECTREX)
    {
        out.ins("LBSR", "INILIB", "initialize standard library and global variables");
        if (mainFunctionDef != NULL)
        {
            out.ins("LBSR", mainFunctionDef->getLabel(), "call main()");
        }
        // Vectrex just loops on exit.
        out.ins("LBSR", "_exit", "use LBSR to respect calling convention");
    }
    else
    {
        out.ins("LBSR", "INILIB", "initialize standard library and global variables");
        if (mainFunctionDef != NULL)
        {
            out.ins("LBSR", mainFunctionDef->getLabel(), "call main()");
        }
        else
        {
            out.ins("CLRA", "", "no main() to call: use 0 as exit status");
            out.ins("CLRB");
        }
        out.ins("PSHS", "B,A", "send main() return value to exit()");
        out.ins("LBSR", "_exit", "use LBSR to respect calling convention");
    }

    // Generate code for each function that is called at least once
    // or has its address taken at least once (see calls to FunctionDef::setCalled()):

    out.emitLabel("functions_start");  // labels to allow measuring user code size
    map<string, FunctionDef *>::iterator kt;
    set<string> emittedFunctions;
    for (kt = functionDefs.begin(); kt != functionDefs.end(); kt++)
    {
        FunctionDef *fd = kt->second;
        if (emitUncalledFunctions || fd->isCalled())
        {
            fd->emitCode(out, false);
            emittedFunctions.insert(fd->getId());  // remember that this func has been emitted
        }
    }
    // Second pass in case some inline assembly has referred to a C function.
    for (kt = functionDefs.begin(); kt != functionDefs.end(); kt++)
    {
        FunctionDef *fd = kt->second;
        if (fd->isCalled() && emittedFunctions.find(fd->getId()) == emittedFunctions.end())
        {
            fd->emitCode(out, false);
            emittedFunctions.insert(fd->getId());  // remember that this func has been emitted
        }
    }

    out.emitLabel("functions_end");

    // Generate the string literals:

    out.emitLabel("string_literals_start");
    if (stringLiteralLabelToValue.size() > 0)
    {
        out.emitSeparatorComment();
        out.emitComment("STRING LITERALS");
        for (map<string, string>::const_iterator it = stringLiteralLabelToValue.begin();
                                                it != stringLiteralLabelToValue.end(); it++)
        {
            out.emitLabel(it->first);
            StringLiteralExpr::emitStringLiteralDefinition(out, it->second);
        }
    }
    out.emitLabel("string_literals_end");

    // Generate the read-only global variables.
    //
    if (targetPlatform != OS9)
    {
        out.emitSeparatorComment();
        out.emitComment("READ-ONLY GLOBAL VARIABLES");

        if (!emitGlobalVariables(out, true, true))
            return;

        // If no data section, then emit the globals after the code.
        // In this case, nothing other than INITGL should come after
        // the 'program_end' label, because sbrk() uses the memory
        // that starts at that label.
        //
        if (dataAddress == 0xFFFF)
        {
            emitWritableGlobals(out);
        }
    }

    // Include standard library functions.
    // Must contain only code, no data.

    out.emitSeparatorComment();
    out.emitInclude("stdlib.inc");

    // Initial program break, for use by sbrk().
    // INITGL is placed at the break, because after it has been executed,
    // its memory can be made available to sbrk() if #pragma exec_once was given.
    //
    if (isProgramExecutableOnlyOnce)
    {
        out.emitSeparatorComment();
        out.emitLabel("program_end");
    }

    {
        // Generate code for global variables that are not initialized statically.
        //
        out.emitSeparatorComment();
        out.emitComment("Initialize global variables.");
        out.emitLabel("INITGL");
        assert(scopeStack.size() == 0);  // ensure current scope is global one
        for (vector<Declaration *>::iterator jt = globalVariables.begin();
                                            jt != globalVariables.end(); jt++)
        {
            Declaration *decl = *jt;
            assert(decl);
            if (! decl->isArrayWithIntegerInitValues())
                decl->emitCode(out, false);
        }
        out.ins("RTS", "", "end of global variable initialization");
    }

    if (! isProgramExecutableOnlyOnce)
    {
        out.emitSeparatorComment();
        out.emitLabel("program_end");
    }


    if (targetPlatform != OS9)
    {
        // Start of data section, if separate from code.
        //
        out.emitSeparatorComment();
        out.emitComment("WRITABLE DATA SECTION");
        if (dataAddress != 0xFFFF)
        {
            out.ins("ORG", wordToString(dataAddress, true));
            emitWritableGlobals(out);
        }
    }

    out.emitSeparatorComment();

    if (targetPlatform == OS9)
    {
        out.emitComment("OS-9");
        out.ins("emod");
        out.emitLabel("length");
    }
    else
        out.ins("END");
}


bool
TranslationUnit::emitWritableGlobals(ASMText &out) const
{
    out.emitLabel("writable_globals_start");

    // Emit FCB or FDB directives for arrays with initializers.
    //
    out.emitSeparatorComment();
    out.emitComment("WRITABLE GLOBAL VARIABLES");

    out.emitComment("Globals with static initializers");
    if (!emitGlobalVariables(out, false, true))
        return false;

    out.emitComment("Uninitialized globals");
    if (!emitGlobalVariables(out, false, false))
        return false;

    out.emitSeparatorComment();
    out.emitInclude("stdlib-data.inc");

    out.emitLabel("writable_globals_end");
    return true;
}


// readOnlySection: Selects which globals get emitted: true means the read-only globals,
//                  false means the writable globals.
// withStaticInitializer: If true, selects only globals that have a static initializer,
//                        i.e., are initialized with FCB/FDB directives.
//                        If false, selects RMB-defined globals.
//
bool
TranslationUnit::emitGlobalVariables(ASMText &out, bool readOnlySection, bool withStaticInitializer) const
{
    bool success = true;

    for (vector<Declaration *>::const_iterator jt = globalVariables.begin();
                                              jt != globalVariables.end(); jt++)
    {
        Declaration *decl = *jt;
        assert(decl);
        uint16_t size = 0;
        if (!decl->getVariableSizeInBytes(size))
        {
            success = false;
            continue;
        }

        if (decl->isReadOnly() != readOnlySection)
            continue;

        if (decl->isArrayWithIntegerInitValues())
        {
            if (withStaticInitializer)  // if selecting FCB/FDB globals
                decl->emitStaticArrayInitializer(out);
        }
        else if (readOnlySection)
        {
            uint16_t value = 0;
            if (decl->initializationExpr == NULL || ! decl->initializationExpr->evaluateConstantExpr(value))
                decl->errormsg("cannot emit assembler directive for global '%s': it does not have a constant initializer",
                                decl->getVariableId().c_str());
            else if (withStaticInitializer)
            {
                out.emitLabel(decl->getLabel(), decl->getVariableId() + ": " + decl->getTypeDesc()->toString());
                decl->emitStaticValues(out, decl->initializationExpr, decl->getTypeDesc());
            }
        }
        else if (!withStaticInitializer)  // if selecting RMB globals
        {
            // We do not emit an FCB or FDB because these globals are initialized
            // at run-time by INITGL, so that they are re-initialized every time
            // the program is run.
            // This re-initialization does not happen for constant integer arrays,
            // for space saving purposes.
            //
            out.emitLabel(decl->getLabel());
            out.ins("RMB", wordToString(size), decl->getVariableId());
        }
    }

    return success;
}


TranslationUnit::~TranslationUnit()
{
    assert(scopeStack.size() == 0);

    // Scope tree must be destroyed after the TreeSequences in definitionList.
    delete definitionList;
    delete globalScope;

    theInstance = NULL;
}


void
TranslationUnit::pushScope(Scope *scope)
{
    assert(scope != NULL);
    scopeStack.push_back(scope);
}


Scope *
TranslationUnit::getCurrentScope()
{
    return (scopeStack.size() > 0 ? scopeStack.back() : NULL);
}


void
TranslationUnit::popScope()
{
    assert(scopeStack.size() > 0);
    //cerr << "popScope: " << scopeStack.back() << "\n";
    scopeStack.pop_back();
}


Scope &
TranslationUnit::getGlobalScope()
{
    return *globalScope;
}


void
TranslationUnit::pushBreakableLabels(const string &brkLabel,
                                        const string &contLabel)
{
    breakableStack.push_back(BreakableLabels());
    breakableStack.back().breakLabel = brkLabel;
    breakableStack.back().continueLabel = contLabel;
}


const BreakableLabels *
TranslationUnit::getCurrentBreakableLabels()
{
    if (breakableStack.size() > 0)
        return &breakableStack.back();
    return NULL;
}


void
TranslationUnit::popBreakableLabels()
{
    assert(breakableStack.size() > 0);
    breakableStack.pop_back();
}


void
TranslationUnit::setCurrentFunctionEndLabel(const string &label)
{
    functionEndLabel = label;
}


string
TranslationUnit::getCurrentFunctionEndLabel()
{
    return functionEndLabel;
}


/*static*/
string
TranslationUnit::genLabel(char letter)
{
    return instance().generateLabel(letter);
}


string
TranslationUnit::generateLabel(char letter)
{
    char label[7];
    snprintf(label, sizeof(label), "%c%05u",
                        letter, (unsigned) ++labelGeneratorIndex);
    return label;
}


FunctionDef *
TranslationUnit::getFunctionDef(const string &functionId)
{
    map<string, FunctionDef *>::iterator it = functionDefs.find(functionId);
    return (it == functionDefs.end() ? (FunctionDef *) 0 : it->second);
}


string
TranslationUnit::getFunctionLabel(const string &functionId)
{
    FunctionDef *fd = getFunctionDef(functionId);
    return (fd != NULL ? fd->getLabel() : "");
}


const FunctionDef *
TranslationUnit::getFunctionDefFromScope(const Scope &functionScope) const
{
    for (map<string, FunctionDef *>::const_iterator it = functionDefs.begin();
                                                   it != functionDefs.end(); ++it)
    {
        const FunctionDef *fd = it->second;
        if (fd && fd->getScope() == &functionScope)
            return fd;
    }
    return NULL;
}

string
TranslationUnit::registerStringLiteral(const StringLiteralExpr &sle)
{
    bool hexEscapeOutOfRange = false, octalEscapeOutOfRange = false;

    string stringValue = sle.decodeEscapedLiteral(hexEscapeOutOfRange, octalEscapeOutOfRange);

    if (hexEscapeOutOfRange)
        sle.warnmsg("hex escape sequence out of range");
    if (octalEscapeOutOfRange)
        sle.warnmsg("octal escape sequence out of range");

    map<string, string>::iterator it = stringLiteralValueToLabel.find(stringValue);
    if (it != stringLiteralValueToLabel.end())
        return it->second;

    string stringLabel = generateLabel('S');
    stringLiteralLabelToValue[stringLabel] = stringValue;
    stringLiteralValueToLabel[stringValue] = stringLabel;
    return stringLabel;
}


string
TranslationUnit::getEscapedStringLiteral(const string &stringLabel)
{
    assert(!stringLabel.empty());
    map<string, string>::iterator it = stringLiteralLabelToValue.find(stringLabel);
    if (it != stringLiteralLabelToValue.end())
        return StringLiteralExpr::escape(it->second);
    assert(!"unknown string literal label");
    return "";
}


// In bytes.
//
int16_t
TranslationUnit::getTypeSize(const TypeDesc &typeDesc) const
{
    assert(typeDesc.isValid());

    if (typeDesc.type == CLASS_TYPE)
    {
        const ClassDef *cl = getClassDef(typeDesc.className);
        assert(cl != NULL);
        return cl->getSizeInBytes();
    }

    return ::getTypeSize(typeDesc.type);
}


const ClassDef *
TranslationUnit::getClassDef(const std::string &className) const
{
    if (className.empty())
    {
        assert(!"empty class name passed to TranslationUnit::getClassDef()");
        return NULL;
    }
    for (vector<Scope *>::const_reverse_iterator it = scopeStack.rbegin();
                                                it != scopeStack.rend();
                                                it++)
    {
        const ClassDef *cl = (*it)->getClassDef(className);
        if (cl != NULL)
            return cl;
    }
    return globalScope->getClassDef(className);

}


void
TranslationUnit::registerNeededUtility(const std::string &utilitySubRoutine)
{
    neededUtilitySubRoutines.insert(utilitySubRoutine);
}


const set<string> &
TranslationUnit::getNeededUtilitySubRoutines() const
{
    return neededUtilitySubRoutines;
}


// Warns that the program will not be relocatable because of the expression
// or statement designated by 'responsible', for the given 'reason'.
// Does not issue the warning if it has already been given a certain number of times.
//
void
TranslationUnit::warnNotRelocatable(Tree *responsible, const char *reason)
{
    ++numNonRelocatableExpressions;
    if (numNonRelocatableExpressions < 5 && responsible && reason)
        responsible->warnmsg("program will not be relocatable (%s)", reason);
}


// Processes #pragma directives that need to be processed right after parsing.
//
// Changes 'codeAddress' iff a '#pragma org' directive is seen.
// codeAddressSetBySwitch: Indicates if the code address was set by a command-line argument.
//
// Changes 'codeLimitAddress' iff a '#pragma limit' directive is seen.
// codeLimitAddressSetBySwitch: Indicates if the code limit address was set by a command-line argument.
//
// Changes 'dataAddress' iff a '#pragma data' directive is seen.
//
void
TranslationUnit::processPragmas(uint16_t &codeAddress, bool codeAddressSetBySwitch,
                                uint16_t &codeLimitAddress, bool codeLimitAddressSetBySwitch,
                                uint16_t &dataAddress)
{
    if (! definitionList)
        return;
    for (vector<Tree *>::iterator it = definitionList->begin();
                                 it != definitionList->end(); ++it)
        if (Pragma *pragma = dynamic_cast<Pragma *>(*it))
        {
            bool isStart = false;
            if (pragma->isCodeOrg(codeAddress))  // if #pragma org ADDRESS
            {
                if (targetPlatform == VECTREX)
                    pragma->errormsg("#pragma org is not permitted for Vectrex");
                else if (codeAddressSetBySwitch)
                    pragma->warnmsg("#pragma org and --org (or --dos) both used");
            }
            else if (pragma->isCodeLimit(codeLimitAddress))  // if #pragma limit ADDRESS
            {
                if (codeLimitAddressSetBySwitch)
                    pragma->warnmsg("#pragma limit and --limit both used");
            }
            else if (pragma->isDataOrg(dataAddress))  // if #pragma data ADDRESS
            {
                if (targetPlatform == VECTREX)
                    pragma->errormsg("#pragma data is not permitted for Vectrex");
            }
            else if (pragma->isConstData(isStart))
            {
            }
            else if (pragma->isExecOnce())
            {
                isProgramExecutableOnlyOnce = true;  // see emitAssembler()
            }
            else if (pragma->isVxTitle(vxTitle))
            {
            }
            else if (pragma->isVxMusic(vxMusic))
            {
            }
            else if (pragma->isVxTitleSize(vxTitleSizeHeight, vxTitleSizeWidth))
            {
            }
            else if (pragma->isVxTitlePos(vxTitlePosY, vxTitlePosX))
            {
            }
            else if (pragma->isVxCopyright(vxCopyright))
            {
            }
            else
                pragma->errormsg("invalid pragma directive: %s", pragma->getDirective().c_str());
        }
}


void
TranslationUnit::enableNullPointerChecking(bool enable)
{
    nullPointerCheckingEnabled = enable;
}


bool
TranslationUnit::isNullPointerCheckingEnabled() const
{
    return nullPointerCheckingEnabled;
}


void
TranslationUnit::enableStackOverflowChecking(bool enable)
{
    stackOverflowCheckingEnabled = enable;
}


bool
TranslationUnit::isStackOverflowCheckingEnabled() const
{
    return stackOverflowCheckingEnabled;
}


const TranslationUnit::StandardFunctionDeclaration TranslationUnit::stdLibTable[] =
{
    { "exit",       { NULL } },
    { "printf",     { NULL } },
    { "sprintf",    { "printf" } },  // in stdlib.inc, _sprintf requires _printf
    { "putchar",    { NULL } },
    { "putstr",     { NULL } },
    { "srand",      { NULL } },
    { "rand",       { NULL } },
    { "atoui",      { NULL } },
    { "atoi",       { NULL } },
    { "mulww",      { NULL } },
    { "mulwb",      { NULL } },
    { "zerodw",     { NULL } },
    { "adddww",     { NULL } },
    { "div328",     { NULL } },
    { "readword",   { NULL } },
    { "readline",   { NULL } },
    { "delay",      { NULL } },
    { "strcmp",     { NULL } },
    { "strlen",     { NULL } },
    { "memset",     { NULL } },
    { "memcpy",     { NULL } },
    { "memcmp",     { NULL } },
    { "strcpy",     { NULL } },
    { "strncpy",    { NULL } },
    { "strcat",     { NULL } },
    { "strchr",     { NULL } },
    { "strlwr",     { NULL } },
    { "strupr",     { NULL } },
    { "toupper",    { NULL } },
    { "tolower",    { NULL } },
    { "dwtoa",      { NULL } },
    { "sbrk",       { NULL } },
    { "sbrkmax",    { NULL } },
    { "set_null_ptr_handler", { NULL } },
    { "set_stack_overflow_handler", { NULL } },
    { "setConsoleOutHook", { NULL } },
};


void
TranslationUnit::checkForNeededUtility(const string &functionId)
{
    for (size_t f = 0; f < sizeof(stdLibTable) / sizeof(stdLibTable[0]); ++f)
    {
        if (functionId == stdLibTable[f].name)
        {
            registerNeededUtility(functionId);  // use the definition from stdlib.inc
            for (int r = 0; r < TranslationUnit::StandardFunctionDeclaration::MAXREQS; ++r)
                if (stdLibTable[f].required[r])  // if functionId requires another sub-routine
                    registerNeededUtility(stdLibTable[f].required[r]);  // register the sub-routine too
                else
                    break;  // break at 1st NULL
            break;
        }
    }
}


bool
TranslationUnit::isStandardFunction(const std::string &functionId) const
{
    for (size_t f = 0; f < sizeof(stdLibTable) / sizeof(stdLibTable[0]); ++f)
        if (functionId == stdLibTable[f].name)
            return true;
    return false;
}


// Destroys the DeclarationSpecifierList, the vector of Declarators
// and the Declarators.
// May return null in the case of a typedef.
//
DeclarationSequence *
TranslationUnit::createDeclarationSequence(DeclarationSpecifierList *dsl,
                                           std::vector<Declarator *> *declarators)
{
    DeclarationSequence *ds = NULL;

    const TypeDesc *td = dsl->getTypeDesc();
    assert(td->type != SIZELESS_TYPE);
    TypeManager &tm = TranslationUnit::getTypeManager();

    if (!declarators)
    {
        std::vector<Enumerator *> *enumeratorList = dsl->detachEnumeratorList();  // null if not an enum
        if (td->type != CLASS_TYPE && ! enumeratorList)
        {
            errormsg("declaration specifies a type but no variable name");
        }

        // We have taken the enumeratorList out of the DeclarationSpecifierList
        // to give it to the created DeclarationSequence, whose checkSemantics()
        // method is responsible for checking that this enum is global.
        // (Enums local to a function are not supported.)
        //
        ds = new DeclarationSequence(td, enumeratorList);
    }
    else if (dsl->isTypeDefinition())
    {
        if (! dsl->isModifierLegalOnVariable())
            errormsg("illegal modifier used on typedef");
        if (! declarators || declarators->size() == 0)
            errormsg("typedef defines no names");
        else
            for (std::vector<Declarator *>::iterator it = declarators->begin(); it != declarators->end(); ++it)
                (void) tm.addTypeDef(td, *it);  // destroys the Declarator object
        ds = NULL;
    }
    else if (dsl->isExternDeclaration())
    {
        // Ignore the declarators in a 'extern' declaration because
        // separate compilation is not supported.
        if (! declarators || declarators->size() == 0)
            errormsg("extern declaration defines no names");
        else
            for (std::vector<Declarator *>::iterator it = declarators->begin(); it != declarators->end(); ++it)
                delete *it;
        ds = NULL;
    }
    else
    {
        bool isEnumType = dsl->hasEnumeratorList();
        ds = new DeclarationSequence(td, dsl->detachEnumeratorList());  // don't detach enumerator list from dsl yet

        bool undefClass = (td->type == CLASS_TYPE
                           && TranslationUnit::instance().getClassDef(td->className) == NULL);

        assert(declarators->size() > 0);
        for (std::vector<Declarator *>::iterator it = declarators->begin(); it != declarators->end(); ++it)
        {
            Declarator *d = *it;
            if (undefClass && d->getPointerLevel() == 0)
            {
                errormsg("declaring `%s' of undefined type struct `%s'",
                         d->getId().c_str(), td->className.c_str());
            }
            else if (d->getFormalParamList() != NULL && isEnumType)
            {
                errormsg("enum with enumerated names is not supported in a function prototype's return type");
            }

            ds->processDeclarator(d, *dsl);  // destroys the Declarator object; may need to check dsl's enumerator list
        }
    }

    delete declarators;
    delete dsl->detachEnumeratorList();  // delete enumerator list if not used
    delete dsl;

    return ds;
}


void
TranslationUnit::checkForEllipsisWithoutNamedArgument(const FormalParamList *formalParamList)
{
    if (formalParamList && formalParamList->endsWithEllipsis() && formalParamList->size() == 0)
        errormsg("named argument is required before `...'");  // as in GCC
}
