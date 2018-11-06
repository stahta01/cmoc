/*  $Id: TranslationUnit.h,v 1.28 2016/10/19 03:33:39 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2015 Pierre Sarrazin <http://sarrazip.com/>

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

#ifndef _H_TranslationUnit
#define _H_TranslationUnit

#include "util.h"
#include "Scope.h"

class Tree;
class TreeSequence;
class Declaration;
class FunctionDef;
class ClassDef;
class DeclarationSequence;
class DeclarationSpecifierList;
class Declarator;


class TranslationUnit
{
public:

    static TranslationUnit &instance();

    static TypeManager &getTypeManager() { return instance().typeManager; }

    TranslationUnit(TargetPlatform targetPlatform,
                    bool _callToUndefinedFunctionAllowed,
                    bool _warnSignCompare);

    // Resets the instance pointer. Do not call instance() after this.
    ~TranslationUnit();

    // defList: Must come from 'new' (or be null). Ownership transfered to TranslationUnit.
    void setDefinitionList(TreeSequence *defList);
    
    // Stores 'fd' in a table (indexed by function identifiers) used by getFunctionDef().
    void addFunctionDef(FunctionDef *fd);

    // Removes 'fd' from the table used by getFunctionDef().
    void removeFunctionDef(FunctionDef *fd);

    // See also addFunctionDef() and removeFunctionDef().
    FunctionDef *getFunctionDef(const std::string &functionId);
    std::string getFunctionLabel(const std::string &functionId);

    const FunctionDef *getFunctionDefFromScope(const Scope &functionScope) const;

    // Emits an error message if the function is not valid.
    // Calls addFunctionDef() otherwise.
    void registerFunction(FunctionDef *fd);

    // Remembers that the named caller calls the named callee.
    // See detectCalledFunctions().
    void registerFunctionCall(const std::string &callerId, const std::string &calleeId);

    void checkSemantics();

    void setTargetPlatform(TargetPlatform platform);

    TargetPlatform getTargetPlatform() const;

    void allocateLocalVariables();

    // allocateLocalVariables() must have been called.
    void emitAssembler(ASMText &out, const std::string &programName, bool compileOnly,
                       uint16_t codeAddress, uint16_t dataAddress,
                       bool emitBootLoaderMarker, bool emitUncalledFunctions);

    void pushScope(Scope *scope);
    Scope *getCurrentScope();
    void popScope();

    Scope &getGlobalScope();

    void pushBreakableLabels(const std::string &brkLabel,
                                        const std::string &contLabel);
    const BreakableLabels *getCurrentBreakableLabels();
    void popBreakableLabels();

    void setCurrentFunctionEndLabel(const std::string &label);
    std::string getCurrentFunctionEndLabel();

    static std::string genLabel(char letter);
    std::string generateLabel(char letter);

    // Returns the assembly label now associated with the contents of sle's literal string.
    //
    std::string registerStringLiteral(const class StringLiteralExpr &sle);

    std::string getEscapedStringLiteral(const std::string &stringLabel);

    int16_t getTypeSize(const TypeDesc &typeDesc) const;

    const ClassDef *getClassDef(const std::string &className) const;

    // See Tree::callUtility().
    void registerNeededUtility(const std::string &utilitySubRoutine);

    const std::set<std::string> &getNeededUtilitySubRoutines() const;

    void warnNotRelocatable(Tree *responsible, const char *reason);

    void processPragmas(uint16_t &codeAddress, bool codeAddressSetBySwitch,
                        uint16_t &codeLimitAddress, bool codeLimitAddressSetBySwitch,
                        uint16_t &dataAddress);

    /** Determines if accesses to pointers will include a run-time null pointer check.
    */
    void enableNullPointerChecking(bool enable);

    /** Indicates if accesses to pointers must include a run-time null pointer check.
    */
    bool isNullPointerCheckingEnabled() const;

    /** Determines if stack overflows are checked for at the beginning of a function.
    */
    void enableStackOverflowChecking(bool enable);

    /** Indicates if stack overflows are checked for at the beginning of a function.
    */
    bool isStackOverflowCheckingEnabled() const;

    // If the function body of 'functionId' is provided by stdlib.inc, register the name as
    // a needed utility sub-routine, and also register any other needed routine.
    //
    void checkForNeededUtility(const std::string &functionId);

    // Determines if the definition of the named function is provided by stdlib.inc or not.
    //
    bool isStandardFunction(const std::string &functionId) const;

    DeclarationSequence *createDeclarationSequence(DeclarationSpecifierList *dsl,
                                                   std::vector<Declarator *> *declarators);

    static void checkForEllipsisWithoutNamedArgument(const FormalParamList *formalParamList);

    bool isCallToUndefinedFunctionAllowed() const;

    bool isWarningOnSignCompareEnabled() const;

private:

    void detectCalledFunctions();
    bool emitWritableGlobals(ASMText &out) const;
    bool emitGlobalVariables(ASMText &out, bool readOnlySection, bool withStaticInitializer) const;
    void checkConstDataDeclarationInitializer(const Declaration &decl) const;

    struct StandardFunctionDeclaration
    {
        enum { MAXREQS = 1 };

        const char *name;  // C name of the function (e.g., "sprintf")
        const char *required[MAXREQS];  // C names of the functions needed by 'name'() (e.g., "printf", when name is "sprintf")
    };

    static const StandardFunctionDeclaration stdLibTable[];

private:

    static TranslationUnit *theInstance;

    TypeManager typeManager;
    Scope *globalScope;  // Scope tree must be destroyed after the TreeSequences in definitionList
    TreeSequence *definitionList;  // owns the object, which must have been allocated with 'new'
    std::map<std::string, FunctionDef *> functionDefs;  // does not own the pointed objects
    StringGraph callGraph;  // maps a function to the functions it calls
    std::vector<Declaration *> globalVariables;  // in order of declaration; does not own the pointed objects
    std::vector<Scope *> scopeStack;  // does not own the pointed objects
    std::vector<BreakableLabels> breakableStack;
    std::string functionEndLabel;  // assembly label of the function currently being emitted
    size_t labelGeneratorIndex;
    std::map<std::string, std::string> stringLiteralLabelToValue;
                        // key = string label, value = string value
    std::map<std::string, std::string> stringLiteralValueToLabel;
                        // key = string value, value = string label
    std::map<std::string, std::string> builtInFunctionDescs;
    size_t numNonRelocatableExpressions;
    bool isProgramExecutableOnlyOnce;
    bool nullPointerCheckingEnabled;
    bool stackOverflowCheckingEnabled;
    bool callToUndefinedFunctionAllowed;
    bool warnSignCompare;  // warn if <, <=, >, >= used on operands of differing signedness
    std::set<std::string> neededUtilitySubRoutines;
    TargetPlatform targetPlatform;

    // Vectrex fields:
    std::string vxTitle;    
    std::string vxMusic;
    int8_t vxTitleSizeWidth;
    int8_t vxTitleSizeHeight;
    int8_t vxTitlePosX;
    int8_t vxTitlePosY;
    std::string vxCopyright;

    // Forbidden operations:
    TranslationUnit(const TranslationUnit &);
    TranslationUnit & operator = (const TranslationUnit &);
};



#endif  /* _H_TranslationUnit */
