/*  $Id: ScopeCreator.cpp,v 1.9 2016/07/26 02:06:26 sarrazip Exp $

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

#include "ScopeCreator.h"

#include "TranslationUnit.h"
#include "CompoundStmt.h"
#include "ForStmt.h"
#include "WhileStmt.h"
#include "DeclarationSequence.h"
#include "VariableExpr.h"
#include "IdentifierExpr.h"
#include "FunctionCallExpr.h"

using namespace std;


ScopeCreator::ScopeCreator(TranslationUnit &tu, Scope *ancestorScope)
:   translationUnit(tu)
{
    translationUnit.pushScope(ancestorScope);
}


ScopeCreator::~ScopeCreator()
{
    translationUnit.popScope();
}


// If 't' is a statement that creates a scope, creates a Scope object, makes it
// the scope of 't', and pushes that scope onto that global scope stack.
//
// If 't' is a DeclarationSequence, calls declareVariable() on the current scope
// for each Declaration in the sequence.
//
// If 't' is an IdentifierExpr, calls processIdentifierExpr() on it.
//
// If 't' is a FunctionCallExpr and the function name is actually a variable name,
// tells the FunctionCallExpr about the Declaration of that variable.
//
bool
ScopeCreator::open(Tree *t)
{
    Scope *cs = translationUnit.getCurrentScope();
    assert(cs != NULL);

    // Compound statements create a scope.
    // So do the for() and while() statement bodies.
    //
    if (   dynamic_cast<CompoundStmt *>(t)
        || dynamic_cast<ForStmt *>(t)
        || dynamic_cast<WhileStmt *>(t))
    {
        Scope *s = new Scope(cs);
        assert(s->getParent() == cs);

        s->copyLineNo(*t);  // to help debugging

        // Note: 'cs' is now owner of 's', i.e., destroying 'cs' will call delete on 's'.

        t->setScope(s);
        t->pushScopeIfExists();
        return true;
    }

    DeclarationSequence *declSeq = dynamic_cast<DeclarationSequence *>(t);
    if (declSeq != NULL)
    {
        for (std::vector<Tree *>::iterator it = declSeq->begin(); it != declSeq->end(); ++it)
        {
            if (Declaration *decl = dynamic_cast<Declaration *>(*it))
            {
                /*cout << "ScopeCreator::open(" << t << "): Declaration: " << decl->getVariableId()
                        << " at line " << decl->getLineNo()
                        << ", cs=" << cs << "\n";*/
                if (!cs->declareVariable(decl))
                {
                    const Declaration *existingDecl = cs->getVariableDeclaration(decl->getVariableId(), false);
                    assert(existingDecl);
                    decl->errormsg("variable `%s' already declared in this scope at %s",
                                   decl->getVariableId().c_str(), existingDecl->getLineNo().c_str());
                }
            }
            else
                (*it)->errormsg("invalid declaration");
        }
        return true;
    }

    IdentifierExpr *ie = dynamic_cast<IdentifierExpr *>(t);
    if (ie)
    {
        processIdentifierExpr(*ie);
        return true;
    }

    FunctionCallExpr *fce = dynamic_cast<FunctionCallExpr *>(t);
    if (fce)
    {
        // Process a call through a pointer. Note that we can't call isCallThroughPointer()
        // on 'fce' yet because that method relies on FunctionCallExpr::funcPtrVarDecl,
        // which is the member we are going to initialize here.
        //
        string id = fce->getIdentifier();  // empty if call is not through identifier, e.g., (*pf)() or obj.member()
        Declaration *decl = cs->getVariableDeclaration(id, true);
        if (decl != NULL)
        {
            FunctionDef *fd = TranslationUnit::instance().getFunctionDef(id);
            if (fd != NULL)
            {
                fce->warnmsg("calling '%s', which is both a variable and a function name", id.c_str());
                return true;
            }
            else
            {
                const TypeDesc *declTD = decl->getTypeDesc();
                if (declTD->type != POINTER_TYPE || declTD->pointedTypeDesc->type != VOID_TYPE)
                {
                    fce->warnmsg("variable '%s' used as function pointer without being of type void *", id.c_str());
                }
            }
        }

        fce->setFunctionPointerVariableDeclaration(decl);
        return true;
    }

    return true;
}


bool
ScopeCreator::close(Tree *t)
{
    t->popScopeIfExists();
    return true;
}


// Determines if the identifier expression is a reference to a variable
// or to an enumerated type.
// Issues an error message if neither.
//
// In the case of a variable reference, sets the type of this object
// and of the created VariableExpr object.
// In the case of an enumerated name, the type is not set, because it is
// set by the ExpressionTypeSetter (look for the IdentifierExpr case).
// (This method is intended to be called during parsing, so it would be too
// soon to set the type of an enumerated name's initialization expression.)
//
// This should be the only place that creates a VariableExpr object.
//
void
ScopeCreator::processIdentifierExpr(IdentifierExpr &ie)
{
    string id = ie.getId();
    Scope *cs = translationUnit.getCurrentScope();
    assert(cs);
    Declaration *decl = cs->getVariableDeclaration(id, true);
    if (decl != NULL)
    {
        VariableExpr *ve = new VariableExpr(id);
        ve->setDeclaration(decl);

        assert(decl->getType() != VOID_TYPE);
        ve->setTypeDesc(decl->getTypeDesc());
        ie.setVariableExpr(ve);  // sets the type of *ie
        return;
    }

    const FunctionDef *fd = translationUnit.getFunctionDef(id);
    if (fd != NULL)
    {
        VariableExpr *ve = new VariableExpr(id);
        ve->markAsFuncAddrExpr();
        const TypeDesc *fpt  = translationUnit.getTypeManager().getFunctionPointerType();
        ve->setTypeDesc(fpt);
        ie.setTypeDesc(fpt);
        ie.setVariableExpr(ve);
        return;
    }

    if (TranslationUnit::getTypeManager().isEnumeratorName(id))  // if known enumerated name
        return;

    ie.errormsg("undeclared identifier `%s'", id.c_str());
}
