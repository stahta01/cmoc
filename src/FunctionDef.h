/*  $Id: FunctionDef.h,v 1.14 2016/10/05 03:17:31 sarrazip Exp $

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

#ifndef _H_FunctionDef
#define _H_FunctionDef

#include "FormalParamList.h"

class DeclarationSpecifierList;
class Declaration;
class Scope;


// The return type of a function is the type of the Tree base object,
// i.e., it is obtained by calling getTypeDesc() on the FunctionDef.
//
class FunctionDef : public Tree
{
public:

    FunctionDef(const DeclarationSpecifierList &dsl,
                const Declarator &declarator);

    // Does NOT destroy the Scope objects used by this function.
    //
    virtual ~FunctionDef();
    
    // If this FunctionDef already has a body, this method calls delete on 'body'
    // and issues a compiler error.
    // Otherwise, this FunctionDef becomes owner of the TreeSequence object,
    // and the FunctionDef destructor will call delete on it.
    // Does nothing if 'body' is null.
    //
    void setBody(TreeSequence *body);

    const TreeSequence *getBody() const;
    TreeSequence *getBody();

    const Scope *getScope() const;
    Scope *getScope();
    std::string getId() const;
    std::string getLabel() const;
    std::string getEndLabel() const;

    bool hasSameReturnType(const FunctionDef &fd) const;
    bool hasSameFormalParams(const FunctionDef &fd) const;
    size_t getNumFormalParams() const;

    // Mark this function as called, for the purposes of not emitting code
    // for functions that are defined but not called.
    //
    void setCalled();

    // Indicates if this function is considered to be called at least once,
    // possibly through a function pointer.
    //
    bool isCalled() const;

    virtual void checkSemantics(Functor &f);

    // Must be called before calling emitCode().
    // Must only be called once.
    //
    void allocateLocalVariables();

    // declareFormalParams() and allocateLocalVariables() must have been called.
    //
    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

    const FormalParamList *getFormalParamList() const;

    bool isInterruptServiceRoutine() const;

    bool isAssemblyOnly() const;

    // Returns true if numArguments is exactly the number of formal parameters,
    // in the case of a non-variadic function, or if numArguments is at least
    // the number of named formal parameters, in the case of a variadic function
    // (one whose format parameter list ends with an ellipsis).
    //
    bool isAcceptableNumberOfArguments(size_t numArguments) const;

    // Returns an empty string if not found.
    //
    std::string findAssemblyLabelFromIDLabeledStatement(const std::string &id) const;

    virtual bool isLValue() const { return false; }

private:
    // Forbidden:
    FunctionDef(const FunctionDef &);
    FunctionDef &operator = (const FunctionDef &);

private:

    void declareFormalParams();

private:

    std::string functionId;
    FormalParamList *formalParamList;
    std::string functionLabel;
    std::string endLabel;
    Scope *scope;  // Scope NOT owned by this object
    int16_t minDisplacement;  // set by allocateLocalVariables()
    TreeSequence *bodyStmts;  // owns the pointed object
    std::vector<Declaration *> formalParamDeclarations;  // owns the pointed objects
    bool isISR;
    bool asmOnly;
    bool called;  // true means at least one call or address-of seen on this function

};


#endif  /* _H_FunctionDef */
