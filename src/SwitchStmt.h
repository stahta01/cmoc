/*  $Id: SwitchStmt.h,v 1.7 2016/06/18 17:15:35 sarrazip Exp $

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

#ifndef _H_SwitchStmt
#define _H_SwitchStmt

#include "Tree.h"
#include "TreeSequence.h"


class SwitchStmt : public Tree
{
public:

    struct SwitchCase
    {
        bool isDefault;  // false means 'case'
        uint16_t caseValue;
        std::string lineNo;  // source filename and line number where 'case' or 'default' keyword appears
        std::vector<const Tree *> statements;

        SwitchCase(bool _isDefault, uint16_t _caseValue, const std::string _lineNo)
            : isDefault(_isDefault), caseValue(_caseValue), lineNo(_lineNo), statements() {}
    };

    typedef std::vector<SwitchCase> SwitchCaseList;

    SwitchStmt(Tree *_expression, Tree *_statement);

    virtual ~SwitchStmt();

    const SwitchCaseList &getCases() const { return cases; }

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

    virtual void checkSemantics(Functor &f);

    virtual void replaceChild(Tree *existingChild, Tree *newChild)
    {
        if (deleteAndAssign(expression, existingChild, newChild))
            return;
        if (deleteAndAssign(statement, existingChild, newChild))
            return;
        assert(!"child not found");
    }

private:

    bool isDuplicateCaseValue(uint16_t caseValue, std::string &originalCaseValueLineNumber) const;
    bool compileLabeledStatements(TreeSequence &statements);

    // Forbidden:
    SwitchStmt(const SwitchStmt &);
    SwitchStmt &operator = (const SwitchStmt &);

public:

    Tree *expression;  // owns the pointed object
    Tree *statement;   // owns the pointed object
    SwitchCaseList cases;

};


#endif  /* _H_SwitchStmt */
