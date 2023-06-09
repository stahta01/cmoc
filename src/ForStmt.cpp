/*  $Id: ForStmt.cpp,v 1.13 2023/03/04 01:56:25 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2023 Pierre Sarrazin <http://sarrazip.com/>

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

#include "ForStmt.h"

#include "TranslationUnit.h"
#include "TreeSequence.h"
#include "UnaryOpExpr.h"
#include "BinaryOpExpr.h"

using namespace std;


ForStmt::ForStmt(Tree *initExprList, Tree *cond,
                Tree *incrExprList, Tree *bodyStmt)
  : Tree(),
    initializations(initExprList),
    condition(cond),
    increments(incrExprList),
    body(bodyStmt)
{
}


/*virtual*/
ForStmt::~ForStmt()
{
    delete body;
    delete increments;
    delete condition;
    delete initializations;
}


// Example: unsigned max = 256; for (unsigned char i = 0; i < max; ++i) {...}
// Variable i can never reach 256, so the loop will be infinite, which is probably not intended.
//
void
ForStmt::warnIfForConditionComparesDifferentSizes() const
{
    auto &tu = TranslationUnit::instance();
    if (!tu.warnIfForConditionComparesDifferentSizes())
        return;

    if (!condition)
        return;
    auto binExpr = dynamic_cast<BinaryOpExpr *>(condition);
    if (!binExpr || !binExpr->isRelationalOperator())
        return;
    
    // Get the sizes of the two sides of the comparison.
    //
    auto leftTS  = binExpr->getLeft()->getTypeDesc();
    auto rightTS = binExpr->getRight()->getTypeDesc();
    int16_t leftSize  = tu.getTypeSize(*leftTS);
    int16_t rightSize = tu.getTypeSize(*rightTS);
    if (leftSize == rightSize)
        return;

    // Tolerate for (byte i = 0; i < 42; ++i) because 42 fits in a byte.
    //
    const Tree *largerTypeTree = NULL;
    int16_t smallerSize = 0;
    if (leftSize < rightSize)
    {
        smallerSize = leftSize;
        largerTypeTree = binExpr->getRight();
    }
    else
    {
        smallerSize = rightSize;
        largerTypeTree = binExpr->getLeft();
    }
    if (smallerSize == 1 && largerTypeTree->fits8Bits())
        return;

    condition->warnmsg("for loop condition compares expressions of different sizes (`%s' vs `%s')",
                            leftTS->toString().c_str(),
                            rightTS->toString().c_str());
}


/*virtual*/
void
ForStmt::checkSemantics(Functor &)
{
    if (condition && condition->getType() == CLASS_TYPE && !condition->isRealOrLong())
        condition->errormsg("invalid use of %s as condition of for statement",
                            condition->getTypeDesc()->isUnion ? "union" : "struct");

    warnIfForConditionComparesDifferentSizes();
}


/*virtual*/
CodeStatus
ForStmt::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    //cerr << "pushing ForStmt scope:\n";
    pushScopeIfExists();
    TranslationUnit &tu = TranslationUnit::instance();

    string bodyLabel = TranslationUnit::instance().generateLabel('L');
    string conditionLabel = TranslationUnit::instance().generateLabel('L');
    string incrementLabel = TranslationUnit::instance().generateLabel('L');
    string endLabel = TranslationUnit::instance().generateLabel('L');

    tu.pushBreakableLabels(endLabel, incrementLabel);

    CodeStatus cs = emitInScope(out, bodyLabel, conditionLabel, incrementLabel, endLabel);

    tu.popBreakableLabels();
    //cerr << "popping ForStmt scope:\n";
    popScopeIfExists();
    return cs;
}


// The code to evaluate condition is emitted after the loop body, instead of before,
// to save one branch instruction per iteration.
//
CodeStatus
ForStmt::emitInScope(ASMText &out,
                     const string &bodyLabel, const string &conditionLabel,
                     const string &incrementLabel, const string &endLabel) const
{
    if (initializations != NULL)
    {
        initializations->writeLineNoComment(out, "for init");
        if (!initializations->emitCode(out, false))
            return false;
    }
    
    if (condition != NULL)
        out.ins("LBRA", conditionLabel, "jump to for condition");
    out.emitLabel(bodyLabel);
    if (body != NULL)
    {
        body->writeLineNoComment(out, "for body");
        if (!body->emitCode(out, false))
            return false;
    }


    out.emitLabel(incrementLabel);
    if (increments != NULL)
    {
        increments->writeLineNoComment(out, "for increment(s)");

        UnaryOpExpr *ue = NULL;
        TreeSequence *ts = dynamic_cast<TreeSequence *>(increments);
        if (ts != NULL && ts->size() == 1)
            ue = dynamic_cast<UnaryOpExpr *>(*ts->begin());

        if (ue != NULL)
        {
            if (!ue->emitSimplerIfIncrement(out))
                return false;
        }
        else
        {
            if (!increments->emitCode(out, false))
                return false;
        }
    }


    if (condition != NULL)
    {
        out.emitLabel(conditionLabel);
        condition->writeLineNoComment(out, "for condition");

        if (!BinaryOpExpr::emitBoolJumps(out, condition, bodyLabel, endLabel))
            return false;
    }
    else
        out.ins("LBRA", bodyLabel);


    out.emitLabel(endLabel, "end for");
    return true;
}


const Tree *
ForStmt::getBody() const
{
    return body;
}


const Tree *
ForStmt::getInitializations() const
{
    return initializations;
}


bool
ForStmt::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (initializations != NULL && !initializations->iterate(f))
        return false;
    if (condition != NULL && !condition->iterate(f))
        return false;
    if (increments != NULL && !increments->iterate(f))
        return false;
    if (body != NULL && !body->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}
