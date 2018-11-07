/*  $Id: WhileStmt.cpp,v 1.12 2016/05/06 03:42:56 sarrazip Exp $

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

#include "WhileStmt.h"

#include "TranslationUnit.h"
#include "BinaryOpExpr.h"

using namespace std;


WhileStmt::WhileStmt(Tree *cond, Tree *bodyStmt, bool isDoWhile)
  : Tree(),
    condition(cond),
    body(bodyStmt),
    isDo(isDoWhile)
{
}


/*virtual*/
WhileStmt::~WhileStmt()
{
    delete condition;
    delete body;
}


/*virtual*/
CodeStatus
WhileStmt::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    string stmtName = (isDo ? "do-while" : "while");

    bool alwaysFalse = condition->isExpressionAlwaysFalse();

    string bodyLabel = TranslationUnit::instance().generateLabel('L');
    string conditionLabel = TranslationUnit::instance().generateLabel('L');
    string endLabel = TranslationUnit::instance().generateLabel('L');

    // Remember that during the coming loop, a 'break' statement must jump to
    // endLabel and a 'continue' statement must jump to conditionLabel.
    //
    TranslationUnit::instance().pushBreakableLabels(endLabel, conditionLabel);

    // A while loop evaluates its condition first, then the body is emitted.
    // A do-while loop emits its body first, then evaluates its condition.
    //
    if (isDo || !alwaysFalse)
    {
        condition->writeLineNoComment(out, stmtName);

        if (!isDo)  // if while statement, evaluate condition first
        {
            out.emitLabel(conditionLabel, stmtName + " condition at " + condition->getLineNo());

            if (! condition->isExpressionAlwaysTrue())
            {
                // Passing 'false' for requiredCondition enables the use of an optimization when the condition
                // is an AND or an OR of relational operators. (bodyLabel is only used if that optimization applies.)
                if (!BinaryOpExpr::emitBoolJumps(out, condition, bodyLabel, endLabel))
                    return false;
            }
        }

        out.emitLabel(bodyLabel, stmtName + " body");
        if (!body->emitCode(out, false))
            return false;
    }

    if (!alwaysFalse)
    {
        // Emit the condition (for a do-while) or a branch back up to the condition (for a while).
        //
        if (isDo)
        {
            out.emitLabel(conditionLabel, stmtName + " condition at " + condition->getLineNo());

            if (! condition->isExpressionAlwaysTrue())
            {
                // Passing 'false' for requiredCondition enables the use of an optimization when the condition
                // is an AND or an OR of relational operators. (bodyLabel is only used if that optimization applies.)
                if (!BinaryOpExpr::emitBoolJumps(out, condition, bodyLabel, endLabel))
                    return false;
            }
            out.ins("LBRA", bodyLabel, "go to start of do-while body");  // if did not jump to endLabel, jump back to body
        }
        else
            out.ins("LBRA", conditionLabel, "go to while condition");
    }

    out.emitLabel(endLabel, "after end of " + stmtName + " starting at " + condition->getLineNo());

    TranslationUnit::instance().popBreakableLabels();
    return true;
}


bool
WhileStmt::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (!condition->iterate(f))
        return false;
    if (!body->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}
