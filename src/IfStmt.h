/*  $Id: IfStmt.h,v 1.6 2016/05/06 03:42:55 sarrazip Exp $

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

#ifndef _H_IfStmt
#define _H_IfStmt

#include "Tree.h"


class IfStmt : public Tree
{
public:

    IfStmt(Tree *cond, Tree *conseq, Tree *alt = NULL);

    virtual ~IfStmt();

    const Tree *getCondition() const { return condition; }

    const Tree *getConsequence() const { return consequence; }

    const Tree *getAlternative() const { return alternative; }

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

    virtual void replaceChild(Tree *existingChild, Tree *newChild)
    {
        if (deleteAndAssign(condition, existingChild, newChild))
            return;
        if (deleteAndAssign(consequence, existingChild, newChild))
            return;
        if (deleteAndAssign(alternative, existingChild, newChild))
            return;
        assert(!"child not found");
    }

private:

    // Forbidden:
    IfStmt(const IfStmt &);
    IfStmt &operator = (const IfStmt &);

public:

    Tree *condition;  // owns the pointed object
    Tree *consequence;  // owns the pointed object
    Tree *alternative;  // owns the pointed object (may be NULL)

};


#endif  /* _H_IfStmt */
