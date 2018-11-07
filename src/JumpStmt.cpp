/*  $Id: JumpStmt.cpp,v 1.11 2016/06/30 18:40:05 sarrazip Exp $

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

#include "JumpStmt.h"

#include "TranslationUnit.h"
#include "FunctionDef.h"
#include "SemanticsChecker.h"
#include "WordConstantExpr.h"

#include <assert.h>

using namespace std;


JumpStmt::JumpStmt(JumpType jt, Tree *arg)
  : Tree(),
    jumpType(jt),
    argument(arg),
    targetLabelID(),
    currentFunctionDef(NULL)  // to be filled by checkSemantics()
{
}


JumpStmt::JumpStmt(const char *_targetLabelID)
  : Tree(),
    jumpType(GO_TO),
    argument(NULL),
    targetLabelID(_targetLabelID),
    currentFunctionDef(NULL)  // to be filled by checkSemantics()
{
}


/*virtual*/
JumpStmt::~JumpStmt()
{
    delete argument;
}


JumpStmt::JumpType
JumpStmt::getJumpType() const
{
    return jumpType;
}


const Tree *
JumpStmt::getArgument() const
{
    return argument;
}


void
JumpStmt::checkSemantics(Functor &f)
{
    SemanticsChecker *sem = dynamic_cast<SemanticsChecker *>(&f);
    if (sem == NULL)
        return;

    currentFunctionDef = sem->getCurrentFunctionDef();
    if (currentFunctionDef == NULL)
    {
        errormsg("jump statement must be inside a function definition");
        return;
    }

    if (jumpType == RET)
    {
        const BasicType funcRetType = currentFunctionDef->getType();
        if (argument != NULL)
        {
            uint16_t value = 0;
            const BasicType argType = argument->getType();

            if (funcRetType == WORD_TYPE && argType == BYTE_TYPE)
                ;  // returning a byte from a word function: fine, regardless of signedness
            else if (funcRetType == BYTE_TYPE && argType == WORD_TYPE && argument->is8BitConstant())
                ;  // returning a word constant that fits in a byte: fine
            else if (funcRetType == WORD_TYPE &&argType == WORD_TYPE)
                ;  // returning a word from a word function: fine, regardless of signedness
            else if (funcRetType == BYTE_TYPE &&argType == BYTE_TYPE)
                ;  // returning a byte from a byte function: fine, regardless of signedness
            else if (funcRetType == POINTER_TYPE && (argType == BYTE_TYPE || argType == WORD_TYPE)
                    && argument->evaluateConstantExpr(value) && value == 0)
                ;  // returning zero from a pointer function: fine
            else if (funcRetType == POINTER_TYPE
                    && argType == ARRAY_TYPE
                    && *currentFunctionDef->getTypeDesc()->pointedTypeDesc == *argument->getTypeDesc()->pointedTypeDesc)
                ;  // returning T[] from function that must return T *: fine
            else if (currentFunctionDef->getTypeDesc() != argument->getTypeDesc())
                errormsg("returning expression of type %s, which differs from function's return type (%s)",
                            argument->getTypeDesc()->toString().c_str(),
                            currentFunctionDef->getTypeDesc()->toString().c_str());
        }
        else if (funcRetType != VOID_TYPE)
            errormsg("return without argument in a non-void function");
    }

    if (jumpType == GO_TO)
    {
        if (currentFunctionDef->findAssemblyLabelFromIDLabeledStatement(targetLabelID).empty())
            errormsg("goto targets label `%s' which is unknown to function %s()",
                     targetLabelID.c_str(), currentFunctionDef->getId().c_str());
    }
}


/*virtual*/
CodeStatus
JumpStmt::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    switch (jumpType)
    {
        case BRK:
        case CONT:
            {
                const char *t = (jumpType == BRK ? "break" : "continue");
                const BreakableLabels *b = TranslationUnit::instance().getCurrentBreakableLabels();
                if (b == NULL)
                {
                    errormsg("%s outside of a %sable statement", t, t);
                    return false;
                }
                if (jumpType == CONT && b->continueLabel.empty())
                    errormsg("continue statement is not supported in a switch");
                else
                    out.ins("LBRA", (jumpType == BRK ? b->breakLabel : b->continueLabel), t);
            }
            return true;
        
        case RET:
            {
                if (argument != NULL)  // if value to be returned
                {
                    writeLineNoComment(out, "return with value");

                    if (!argument->emitCode(out, false))  // value in D
                        return false;

                    if (currentFunctionDef->getType() != BYTE_TYPE
                               && argument->getType() == BYTE_TYPE)
                        out.ins("CLRA");
                }
                string label =
                    TranslationUnit::instance().getCurrentFunctionEndLabel();
                if (label.empty())
                    assert(!"return outside of a function body");
                out.ins("LBRA", label, "return (" + getLineNo() + ")");
            }
            return true;

        case GO_TO:
            {
                string asmLabel = currentFunctionDef->findAssemblyLabelFromIDLabeledStatement(targetLabelID);
                assert(!asmLabel.empty());
                writeLineNoComment(out, "goto " + targetLabelID);
                out.ins("LBRA", asmLabel);
            }
            return true;

        default:
            assert(!"unsupported jump statement");
            return false;
    }
}


bool
JumpStmt::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (argument != NULL && !argument->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}
