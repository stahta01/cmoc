/*  $Id: SwitchStmt.cpp,v 1.10 2016/06/18 18:14:20 sarrazip Exp $

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

#include "SwitchStmt.h"

#include "TranslationUnit.h"
#include "BinaryOpExpr.h"
#include "CompoundStmt.h"
#include "LabeledStmt.h"

using namespace std;


SwitchStmt::SwitchStmt(Tree *_expression, Tree *_statement)
  : Tree(),
    expression(_expression),
    statement(_statement),
    cases()
{
}


/*virtual*/
SwitchStmt::~SwitchStmt()
{
    delete expression;
    delete statement;
}


// Fills cases[].
//
/*virtual*/
void
SwitchStmt::checkSemantics(Functor & /*f*/)
{
    CompoundStmt *compoundStmt = dynamic_cast<CompoundStmt *>(statement);
    if (compoundStmt)
    {
        if (! compileLabeledStatements(*compoundStmt))
            return;  // error message already given
    }
    if (cases.size() == 0)
    {
        statement->errormsg("switch() statement has no `case' or `default' statement");
        return;
    }
}


// originalCaseValueLineNumber: Defined only if method returns true.
//
bool
SwitchStmt::isDuplicateCaseValue(uint16_t caseValue, string &originalCaseValueLineNumber) const
{
    originalCaseValueLineNumber = -1;

    for (SwitchCaseList::const_iterator it = cases.begin(); it != cases.end(); ++it)
        if (!it->isDefault && it->caseValue == caseValue)
        {
            originalCaseValueLineNumber = it->lineNo;
            return true;
        }
    return false;
}


// Fills cases[].
//
bool
SwitchStmt::compileLabeledStatements(TreeSequence &statements)
{
    bool success = true, defaultSeen = false;
    for (std::vector<Tree *>::iterator it = statements.begin(); it != statements.end(); ++it)
    {
        const Tree *tree = *it;
        if (tree == NULL)
            continue;

        const LabeledStmt *labeledStmt = dynamic_cast<const LabeledStmt *>(tree);
        if (labeledStmt && !labeledStmt->isId())
        {
            while (labeledStmt && !labeledStmt->isId())
            {
                uint16_t caseValue = 0;
                const Tree *caseExpr = labeledStmt->getExpression();
                if (labeledStmt->isCase())  // if 'case':
                {
                    assert(caseExpr);
                    if (!caseExpr->evaluateConstantExpr(caseValue))
                    {
                        labeledStmt->errormsg("case statement has a variable expression");
                        success = false;
                    }
                    else
                    {
                        string originalCaseValueLineNumber;

                        if (expression->getType() == BYTE_TYPE && ! expression->isSigned() && caseValue > 0xFF)
                            caseExpr->warnmsg("switch expression is unsigned char but case value is not in range 0..255");
                        else if (expression->getType() == BYTE_TYPE && expression->isSigned() && caseValue >= 0x80 && caseValue < 0xFF80)
                            caseExpr->warnmsg("switch expression is signed char but case value is not in range -128..127");
                        else if (isDuplicateCaseValue(caseValue, originalCaseValueLineNumber))
                            caseExpr->errormsg("duplicate case value (first used at %s)", originalCaseValueLineNumber.c_str());
                    }
                }
                else
                {
                    assert(labeledStmt->isDefault());
                    assert(!caseExpr);
                    if (defaultSeen)
                    {
                        labeledStmt->errormsg("more than one default statement in switch");
                        success = false;
                    }
                    else
                        defaultSeen = true;
                }

                // Add a case to the list.
                // The 'default' case will disregard caseValue.
                //
                string caseLineNo = caseExpr ? caseExpr->getLineNo() : labeledStmt->getLineNo();
                cases.push_back(SwitchCase(caseExpr == NULL, caseValue, caseLineNo));

                const Tree *subStmt = labeledStmt->getStatement();
                const LabeledStmt *subLabeledStmt = dynamic_cast<const LabeledStmt *>(subStmt);

                // Support case A: case B: foobar;
                // This is a LabeledStmt containing a LabeledStmt containing statement foobar.
                // Push the sub-statement in the list of statements for the current case
                // EXCEPT if the sub-statement is itself a labeled statement (case B: foobar;
                // in this example). In this case, we want case A to have no statements and
                // case B to have foobar as its first statement.
                //
                if (!subLabeledStmt || subLabeledStmt->isId())
                    cases.back().statements.push_back(subStmt);

                // If the sub-statement is a LabeledStmt, loop to process it.
                //
                labeledStmt = subLabeledStmt;
            }
        }
        else  // neither case nor default:
        {
            if (cases.size() == 0)
            {
                tree->errormsg("statement in switch precedes first `case' or `default' statement");
                success = false;
            }
            else
                cases.back().statements.push_back(tree);
        }
    }
    return success;
}


/*virtual*/
CodeStatus
SwitchStmt::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    expression->writeLineNoComment(out, "switch");

    TranslationUnit &tu = TranslationUnit::instance();

    string endSwitchLabel = tu.generateLabel('L');

    if (! expression->emitCode(out, lValue))
        return false;

    bool exprIsByte = (expression->getType() == BYTE_TYPE);
    const char *cmpInstr = (exprIsByte ? "CMPB" : "CMPD");

    vector<string> caseLabels;
    string defaultLabel;

    // Emit a series of comparisons and conditional branches:
    //      CMPr #caseValue1
    //      LBEQ label1
    //      etc.
    //
    for (SwitchCaseList::const_iterator it = cases.begin(); it != cases.end(); ++it)
    {
        const SwitchCase &c = *it;

        string caseLabel = TranslationUnit::instance().generateLabel('L');

        if (!c.isDefault)
        {
            if (exprIsByte && int16_t(c.caseValue) > 0xFF)
                ;  // no match possible: don't generate CMP+LBEQ
            else
            {
                uint16_t caseValue = c.caseValue;
                if (exprIsByte)
                    caseValue &= 0xFF;
                out.ins(cmpInstr, "#" + wordToString(caseValue, true), "case " + wordToString(caseValue, false));
                out.ins("LBEQ", caseLabel);
            }
        }

        caseLabels.push_back(caseLabel);
        if (c.isDefault)
            defaultLabel = caseLabel;
    }
    assert(caseLabels.size() == cases.size());

    if (defaultLabel.empty())  // if no default seen:
        defaultLabel = endSwitchLabel;

    out.ins("LBRA", defaultLabel, "switch default");

    pushScopeIfExists();
    tu.pushBreakableLabels(endSwitchLabel, "");  // continue statement is not supported in a switch

    // Emit the code for the switch() body.
    //
    for (SwitchCaseList::const_iterator it = cases.begin(); it != cases.end(); ++it)
    {
        const SwitchCase &c = *it;

        const string &caseLabel = caseLabels[it - cases.begin()];
        string comment;
        if (c.isDefault)
            comment = "default";
        else
            comment = "case " + wordToString(c.caseValue, false);

        out.emitLabel(caseLabel, comment);

        for (std::vector<const Tree *>::const_iterator jt = c.statements.begin(); jt != c.statements.end(); ++jt)
            if (! (*jt)->emitCode(out, lValue))
                return false;
    }

    tu.popBreakableLabels();
    popScopeIfExists();

    out.emitLabel(endSwitchLabel, "end of switch");
    return true;
}


bool
SwitchStmt::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (!expression->iterate(f))
        return false;
    if (!statement->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}
