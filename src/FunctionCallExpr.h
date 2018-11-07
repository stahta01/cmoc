/*  $Id: FunctionCallExpr.h,v 1.7 2016/07/26 01:55:12 sarrazip Exp $

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

#ifndef _H_FunctionCallExpr
#define _H_FunctionCallExpr

#include "Tree.h"

class TreeSequence;
class Declaration;


class FunctionCallExpr : public Tree
{
public:

    FunctionCallExpr(Tree *func, TreeSequence *args);

    virtual ~FunctionCallExpr();

    /** Checks that this function call is valid and sets the return TypeDesc.
        If errors are detected, they are reported.
        @returns                        true if the call is valid,
                                        false if errors were detected
    */
    bool checkAndSetTypes();

    /** Determines if this call is made as in pf(), (*pf)() or obj.member(),
        or if it is a standard, direct function call.
    */
    bool isCallThroughPointer() const;

    /** If this expression consists solely of an identifier, return it.
        Otherwise, returns an empty string.
        An identifier is used for standard calls and for pointer-to-function calls
        of the form pf().
    */
    std::string getIdentifier() const;

    /** Call this with a non-null Declaration pointer when the function call
        uses a function pointer variable, or with NULL when the call is
        directly to a global function name.
    */
    void setFunctionPointerVariableDeclaration(Declaration *_funcPtrVarDecl);

    bool hasFunctionPointerVariableDeclaration() const { return funcPtrVarDecl != NULL; }

    virtual void checkSemantics(Functor &f);

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

private:

    void checkPrintfArguments(const TreeSequence &arguments) const;
    void checkForStructsPassedByValue();

    // Forbidden:
    FunctionCallExpr(const FunctionCallExpr &);
    FunctionCallExpr &operator = (const FunctionCallExpr &);

private:

    Tree *function;  // IdentifierExpr for f() and for ptrToF(); UnaryOpExpr or ObjectMemberExpr (typically) for (*expr)(); owns the pointed object
    Declaration *funcPtrVarDecl;  // non null when calling through function pointer variable
    TreeSequence *arguments;  // owns the pointed object

};


#endif  /* _H_FunctionCallExpr */
