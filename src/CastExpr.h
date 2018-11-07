/*  $Id: CastExpr.h,v 1.5 2016/05/06 03:42:54 sarrazip Exp $

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

#ifndef _H_CastExpr
#define _H_CastExpr

#include "Tree.h"


class CastExpr : public Tree
{
public:

    CastExpr(const TypeDesc *td, Tree *e);

    virtual ~CastExpr();

    const Tree *getSubExpr() const;

    Tree *getSubExpr();

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

    virtual void replaceChild(Tree *existingChild, Tree *newChild)
    {
        if (deleteAndAssign(subExpr, existingChild, newChild))
            return;
        assert(!"child not found");
    }

private:

    // Forbidden:
    CastExpr(const CastExpr &);
    CastExpr &operator = (const CastExpr &);

private:

    Tree *subExpr;  // owns the Tree object

};


#endif  /* _H_CastExpr */
