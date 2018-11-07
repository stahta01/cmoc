/*  $Id: FunctionDef.cpp,v 1.54 2018/03/12 03:32:21 sarrazip Exp $

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

#include "FunctionDef.h"

#include "Scope.h"
#include "DeclarationSequence.h"
#include "CompoundStmt.h"
#include "TranslationUnit.h"
#include "StringLiteralExpr.h"
#include "FormalParameter.h"
#include "ForStmt.h"
#include "WhileStmt.h"
#include "VariableExpr.h"
#include "BinaryOpExpr.h"
#include "UnaryOpExpr.h"
#include "CastExpr.h"
#include "FunctionCallExpr.h"
#include "ObjectMemberExpr.h"
#include "ClassDef.h"
#include "ConditionalExpr.h"
#include "JumpStmt.h"
#include "ExpressionTypeSetter.h"
#include "ScopeCreator.h"
#include "AssemblerStmt.h"
#include "SemanticsChecker.h"
#include "LabeledStmt.h"

#include <assert.h>

using namespace std;


uint16_t FunctionDef::functionStackSpace = 0;


class Tracer : public Tree::Functor
{
public:
    Tracer() : trace(cerr), ind() {}
    virtual ~Tracer() {}
    virtual bool open(Tree *t)
    {
        assert(t != NULL);
        t->pushScopeIfExists();
        Scope *cs = TranslationUnit::instance().getCurrentScope();
        trace << ind << "open(" << t
                << ") [current scope is now " << cs << "]\n";
        ind += "  ";
        Scope *scope = t->getScope();
        trace << ind << "scope=" << scope << "\n";
        if (scope != NULL)
        {
            vector<string> v;
            scope->getDeclarationIds(v);
            trace << ind << "scope at " << scope << " w/ decls: {";
            for (vector<string>::const_iterator it = v.begin();
                                                it != v.end(); it++)
                trace << " " << *it;
            trace << " }\n";
        }
        Declaration *decl = dynamic_cast<Declaration *>(t);
        if (decl != NULL)
            trace << ind << "declaration: " << decl->getVariableId() << ": " << decl->getLineNo() << "\n";
        const VariableExpr *ve = t->asVariableExpr();
        if (ve != NULL)
            trace << ind << "variable expr: " << ve->getId() << ": " << ve->getLineNo() << "\n";
        TreeSequence *ts = dynamic_cast<TreeSequence *>(t);
        if (ts != NULL)
            trace << ind << "tree sequence with " << ts->size() << " statement(s)\n";
        FunctionCallExpr *fce = dynamic_cast<FunctionCallExpr *>(t);
        if (fce != NULL)
            trace << ind << "function call: " << fce->isCallThroughPointer() << ", " << fce->getIdentifier() << "()\n";
        return true;
    }
    virtual bool close(Tree *t)
    {
        t->popScopeIfExists();
        ind.erase(ind.length() - 2, 2);
        Scope *cs = TranslationUnit::instance().getCurrentScope();
        trace << ind << "close(" << t << ") [current scope is now "
                << cs << "]\n";
        return true;
    }

    ostream &trace;
    string ind;
};


///////////////////////////////////////////////////////////////////////////////


// Counts the number of return statements in the body of a function.
//
class ReturnStmtChecker : public Tree::Functor
{
public:
    ReturnStmtChecker() : numReturnStmts(0) {}
    virtual ~ReturnStmtChecker() {}
    virtual bool close(Tree *t)
    {
        JumpStmt *jump = dynamic_cast<JumpStmt *>(t);
        if (jump && jump->getJumpType() == JumpStmt::RET)
            ++numReturnStmts;
        return true;
    }

    size_t numReturnStmts;
};


///////////////////////////////////////////////////////////////////////////////


// Checks that no ID of a labeled-statement is used more than once
// in the same function body.
//
class IDLabeledStatementChecker : public Tree::Functor
{
public:
    IDLabeledStatementChecker() : seenIDs() {}

    // Processing done in open() instead of close() so that the statements are seen in text order.
    virtual bool open(Tree *t)
    {
        if (const LabeledStmt *ls = dynamic_cast<LabeledStmt *>(t))
        {
            if (!ls->isId())
                return true;
            string id = ls->getId();
            map<string, string>::const_iterator it = seenIDs.find(id);
            if (it != seenIDs.end())
            {
                ls->errormsg("label `%s' already defined at %s", id.c_str(), it->second.c_str());
                return true;
            }
            seenIDs[id] = ls->getLineNo();
        }
        return true;
    }
private:
    map<string, string> seenIDs;  // key: ID; value: line number where ID first seen
};


///////////////////////////////////////////////////////////////////////////////


// dsl: Specifies the return type of this function.
//
FunctionDef::FunctionDef(const DeclarationSpecifierList &dsl,
                         Declarator &declarator)
  : Tree(),
    functionId(declarator.getId()),
    formalParamList(declarator.detachFormalParamList()),
    functionLabel("_" + functionId),
    endLabel(TranslationUnit::instance().generateLabel('L')),
    bodyStmts(NULL),
    formalParamDeclarations(),
    numLocalVariablesAllocated(0),
    minDisplacement(9999),  // positive value means allocateLocalVariables() not called yet
    isISR(dsl.isInterruptServiceFunction()),
    isStatic(dsl.isStaticDeclaration()),
    asmOnly(dsl.isAssemblyOnly()),
    noReturnInstruction(dsl.hasNoReturnInstruction()),
    called(false)
{
    const TypeDesc *returnTD = declarator.processPointerLevel(dsl.getTypeDesc());
    if (! returnTD->isPtrToFunction() && returnTD->isInterruptServiceRoutine())
        returnTD = TranslationUnit::instance().getTypeManager().getNonInterruptType(returnTD);
    setTypeDesc(returnTD);

    /*cout << "# FunctionDef::FunctionDef: " << declarator.getId() << "(): returns {"
         << getTypeDesc()->toString() << "}, formalParamList=(" << formalParamList->toString() << ")\n";*/
    assert(getTypeDesc()->isPtrToFunction() || ! getTypeDesc()->isInterruptServiceRoutine());
}


template <typename T>
inline void deletePtr(T *ptr)
{
    delete ptr;
}


/*virtual*/
FunctionDef::~FunctionDef()
{
    delete formalParamList;

    for_each(formalParamDeclarations.begin(), formalParamDeclarations.end(), deletePtr<Declaration>);

    delete bodyStmts;
}


// Generates Declaration objects for each formal parameter.
// Stores them in this function's Scope object.
// Sets the declarations' frame displacement.
// Issues error messages if needed (e.g., two parameters with the same name).
// Must be called before setBody().
//
void
FunctionDef::declareFormalParams()
{
    if (formalParamList == NULL)
        return;  // error message already reported by TranslationUnit::registerFunction()

    assert(getScope() != NULL);

    int16_t paramFrameDisplacement = Declaration::FIRST_FUNC_PARAM_FRAME_DISPLACEMENT;

    // If return type is struct/union, receive address of return value
    // as hidden parameter.
    //
    if (getType() == CLASS_TYPE)
        paramFrameDisplacement += 2;

    for (vector<Tree *>::const_iterator it = formalParamList->begin();
                                       it != formalParamList->end(); it++)
    {
        const FormalParameter *fp = dynamic_cast<FormalParameter *>(*it);
        assert(fp != NULL);
        uint16_t argIndex = uint16_t(it - formalParamList->begin()) + 1;

        string fpId = fp->getId();
        if (fpId.empty())
            fpId = "$" + wordToString(argIndex);  // to avoid clash between two unnamed parameters

        //cout << "# FunctionDef::declareFormalParams: new Declaration('" << fpId << "', {" << fp->getTypeDesc()->toString() << "}, " << fp->getArrayDimensions() << ")\n";

        Declaration *decl = new Declaration(fpId, fp->getTypeDesc(), fp->getArrayDimensions(), false, false);
        decl->copyLineNo(*fp);
        if (!getScope()->declareVariable(decl))  // 'scope' keeps copy of 'decl' pointer but does not take ownership
            errormsg("function %s() has more than one formal parameter named '%s'",
                                                functionId.c_str(), fpId.c_str());

        // Keep a copy of 'decl' so that ~FunctionDef() destroys them.
        formalParamDeclarations.push_back(decl);

        if (TranslationUnit::instance().getTypeSize(*fp->getTypeDesc()) == 1)  // if byte or 1-byte struct/union
            paramFrameDisplacement++;
        decl->setFrameDisplacement(paramFrameDisplacement);

        // If struct, check that it is defined.
        if (fp->getType() == CLASS_TYPE && TranslationUnit::instance().getClassDef(fp->getTypeDesc()->className) == NULL)
        {
            errormsg("argument %u of %s() receives undefined `%s' by value",
                     argIndex, functionId.c_str(), fp->getTypeDesc()->toString().c_str());
            continue;
        }

        uint16_t size = 0;
        if (!decl->getVariableSizeInBytes(size))
            assert(false);
        else
            paramFrameDisplacement += int16_t(size);
    }

    // Require at least one named argument before an ellipsis, as does GCC.
    //
    if (formalParamList->endsWithEllipsis() && formalParamList->size() == 0)
        errormsg("%s %s() uses `...' but has no named argument before it",
                 bodyStmts ? "function" : "prototype",
                 functionId.c_str());
}


// declareFormalParams() must have been called.
//
void
FunctionDef::setBody(TreeSequence *body)
{
    if (body != NULL)
    {
        if (bodyStmts != NULL)
        {
            body->errormsg("%s() already has a body at %s", functionId.c_str(), bodyStmts->getLineNo().c_str());
            delete body;
        }
        else
            bodyStmts = body;
    }
}

    
const TreeSequence *
FunctionDef::getBody() const
{
    return bodyStmts;
}


TreeSequence *
FunctionDef::getBody()
{
    return bodyStmts;
}


string
FunctionDef::getId() const
{
    return functionId;
}


string
FunctionDef::getLabel() const
{
    return functionLabel;
}


string
FunctionDef::getEndLabel() const
{
    return endLabel;
}


bool
FunctionDef::hasSameReturnType(const FunctionDef &fd) const
{
    return getTypeDesc() == fd.getTypeDesc();
}


bool
FunctionDef::hasSameFormalParams(const FunctionDef &fd) const
{
    const FormalParamList *otherFormalParams = fd.formalParamList;
    if (otherFormalParams == NULL)
        return formalParamList == NULL;
    if (formalParamList == NULL)
        return false;

    if (otherFormalParams->size() != formalParamList->size())
        return false;

    if (otherFormalParams->endsWithEllipsis() != formalParamList->endsWithEllipsis())
        return false;

    vector<Tree *>::const_iterator it = formalParamList->begin();
    vector<Tree *>::const_iterator itOther = otherFormalParams->begin();
    for ( ; it != formalParamList->end(); it++, itOther++)
    {
        FormalParameter *fp = dynamic_cast<FormalParameter *>(*it);
        if (fp == NULL)
        {
            assert(false);
            return false;
        }

        FormalParameter *otherFp = dynamic_cast<FormalParameter *>(*itOther);
        if (otherFp == NULL)
        {
            assert(false);
            return false;
        }

        if (*fp->getTypeDesc() != *otherFp->getTypeDesc())
            return false;
    }

    return true;
}


size_t
FunctionDef::getNumFormalParams() const
{
    return formalParamList ? formalParamList->size() : 0;
}


void
FunctionDef::setCalled()
{
    called = true;
}


bool
FunctionDef::isCalled() const
{
    return called;
}


/*virtual*/
void
FunctionDef::checkSemantics(Functor &f)
{
    SemanticsChecker &sem = dynamic_cast<SemanticsChecker &>(f);
    if (bodyStmts)
        sem.setCurrentFunctionDef(this);

    /*  Create a scope for the function.
        Make it a child of the global scope.
        This means the global Scope object owns 'scope'.
        When the global Scope will be destroyed, delete will be called on 'scope'.
    */
    assert(getScope() == NULL);
    setScope(new Scope(&TranslationUnit::instance().getGlobalScope()));
    //cerr << "FunctionDef's top scope at " << scope << "\n";
    assert(getScope()->getParent() == &TranslationUnit::instance().getGlobalScope());

    /*  An interrupt service routine is not allowed to receive parameters,
        because it is only called by the system, which does not provide
        any parameters.
    */
    if (isISR && getNumFormalParams() > 0)
        errormsg("interrupt service routine %s() has parameters", functionId.c_str());

    /*  main() not allowed to be static.
    */
    if (getId() == "main" && hasInternalLinkage())
        errormsg("main() must not be static");

    /*  Declare the function's formal parameters in 'scope'.
    */
    declareFormalParams();

    if (bodyStmts)
    {
        /*  Create a Scope for each compound statement anywhere in the function's body.
            The function's main braces do not get their own scope. They are part of
            the function's scope.
        */
        {
            ScopeCreator sc(TranslationUnit::instance(), getScope());
            bodyStmts->iterate(sc);
        }  // destroy ScopeCreator here so that it pops all scopes it pushed onto the TranslationUnit's stack

        static const bool debug = (getenv("DEBUG") != 0);
        if (debug)
        {
            Tracer tracer;
            bodyStmts->iterate(tracer);
        }

        if (asmOnly)
        {
            for (vector<Tree *>::const_iterator it = bodyStmts->begin(); it != bodyStmts->end(); ++it)
            {
                if (AssemblerStmt *asmStmt = dynamic_cast<AssemblerStmt *>(*it))
                    asmStmt->setAssemblyOnly(getScope());
                else
                {
                    (*it)->errormsg("body of function %s() contains statement(s) other than inline assembly",
                                    functionId.c_str());
                    return;
                }
            }
            return;
        }
        if (noReturnInstruction && !asmOnly)
            errormsg("`__norts__' must be used with `asm' when defining an asm-only function");

        ExpressionTypeSetter ets;
        bodyStmts->iterate(ets);

        // Check if a non-void returning function contains at least one return statement.
        // (This does not prove that all code paths have a return statement however.)
        //
        if (getType() != VOID_TYPE)
        {
            ReturnStmtChecker rsc;
            bodyStmts->iterate(rsc);
            if (rsc.numReturnStmts == 0)
                errormsg("function '%s' is not void but does not have any return statement", functionId.c_str());
        }

        // Check ID-labeled statements.
        {
            IDLabeledStatementChecker checker;
            bodyStmts->iterate(checker);
        }
    }
}


void
FunctionDef::allocateLocalVariables()
{
    assert(minDisplacement > 0);  // must be first call
    assert(getScope() != NULL);
    assert(getScope()->getParent() != NULL);  // function's scope is not the global one

    if (bodyStmts == NULL)
        return;  // no body: nothing to do

    assert(bodyStmts->getScope() == NULL);  // function's top-level braced scope is 'scope'

    numLocalVariablesAllocated = 0;
    minDisplacement = getScope()->allocateLocalVariables(0, true, numLocalVariablesAllocated);

    assert(minDisplacement <= 0);
}


/*virtual*/
CodeStatus
FunctionDef::emitCode(ASMText &out, bool lValue) const
{
    assert(getScope() != NULL);
    assert(getScope()->getParent() != NULL);  // function's scope is not the global one

    if (bodyStmts == NULL)
        return true;

    if (lValue)
        return false;

    assert(minDisplacement <= 0);  // allocateLocalVariables() must have been called

    // Generate code that sets up the function's stack frame:
    
    out.emitSeparatorComment();
    out.emitFunctionStart(functionId, getLineNo());
    out.emitLabel(functionLabel);

    // A stack frame is only needed if the function:
    // - receives parameters or declares local variables or returns a struct (including a real number);
    // and:
    // - is not an asm-only function (the point of which is to forego the stack frame).
    //
    // (We use numLocalVariablesAllocated to determine if this functoin has
    // local variables, instead of minDisplacement < 0, because minDisplacement
    // can be 0 if all locals are empty structs.)
    //
    bool needStackFrame = !asmOnly && (getNumFormalParams() > 0 || numLocalVariablesAllocated > 0 || getType() == CLASS_TYPE);

    if (needStackFrame)
        out.ins("PSHS", "U");

    // Function-entry stack check, if enabled. This is the point where it is done under OS-9.
    if (!asmOnly && getFunctionStackSpace() > 0)
    {
        out.ins("LDD", "#-" + wordToString(getFunctionStackSpace() - minDisplacement));
        callUtility(out, "_stkcheck");
    }

    if (needStackFrame)
    {
        out.ins("LEAU", ",S");  // takes 4 cycles and 2 bytes; TFR U,S takes 6 cycles
        if (minDisplacement < 0)
            out.ins("LEAS", intToString(minDisplacement) + ",S");
    }

    if (TranslationUnit::instance().isStackOverflowCheckingEnabled())
    {
        callUtility(out, "check_stack_overflow");
    }

    // Generate code for the body:

    TranslationUnit::instance().setCurrentFunctionEndLabel(endLabel);
    TranslationUnit::instance().pushScope(const_cast<Scope *>(getScope()));  // const_cast should be removed...
    bool success = bodyStmts->emitCode(out, false);
    out.emitLabel(endLabel, "end of " + functionId + "()");

    // The scope must be popped whether or not this function succeeds.
    TranslationUnit::instance().popScope();

    TranslationUnit::instance().setCurrentFunctionEndLabel("");

    if (needStackFrame)
    {
        assert(!asmOnly);
        out.ins("LEAS", ",U");  // takes 4 cycles and 2 bytes; TFR U,S takes 6 cycles
        if (isISR)
        {
            out.ins("PULS", "U");
            out.ins("RTI");
        }
        else
            out.ins("PULS", "U,PC");
    }
    else
    {
        if (!noReturnInstruction)
            out.ins(isISR ? "RTI" : "RTS");
    }

    out.emitFunctionEnd();

    return success;
}


bool
FunctionDef::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (bodyStmts != NULL && !bodyStmts->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}


const FormalParamList *
FunctionDef::getFormalParamList() const
{
    return formalParamList;
}


bool
FunctionDef::isAcceptableNumberOfArguments(size_t numArguments) const
{
    if (formalParamList == NULL)
        return numArguments == 0;

    return formalParamList->isAcceptableNumberOfArguments(numArguments);
}


class IDLabeledStatementFinder : public Tree::Functor
{
public:
    IDLabeledStatementFinder(const string &_targetID) : foundAsmLabel(), targetID(_targetID) {}
    virtual bool close(Tree *t)
    {
        if (const LabeledStmt *ls = dynamic_cast<LabeledStmt *>(t))
        {
            string asmLabel = ls->getAssemblyLabelIfIDEqual(targetID);
            if (!asmLabel.empty())
            {
                foundAsmLabel = asmLabel;
                return false;  // stop iteration
            }
        }
        return true;
    }

    string foundAsmLabel;
private:
    string targetID;
};


string
FunctionDef::findAssemblyLabelFromIDLabeledStatement(const std::string &id) const
{
    if (!bodyStmts)
        return string();

    IDLabeledStatementFinder finder(id);
    bodyStmts->iterate(finder);
    return finder.foundAsmLabel;
}


bool
FunctionDef::isInterruptServiceRoutine() const
{
    return isISR;
}


bool
FunctionDef::isAssemblyOnly() const
{
    return asmOnly;
}


bool
FunctionDef::hasInternalLinkage() const
{
    return isStatic;
}


uint16_t
FunctionDef::getFunctionStackSpace()
{
    return functionStackSpace;
}


void
FunctionDef::setFunctionStackSpace(uint16_t numBytes)
{
    functionStackSpace = numBytes;
}
