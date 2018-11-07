/*  $Id: IdentifierExpr.h,v 1.5 2016/07/24 23:03:06 sarrazip Exp $

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

#ifndef _H_IdentifierExpr
#define _H_IdentifierExpr

#include "Tree.h"

class VariableExpr;


class IdentifierExpr : public Tree
{
public:

    IdentifierExpr(const char *id);

    // Calls delete on a VariableExpr given to this object via
    // setVariableExpr(), if any.
    //
    virtual ~IdentifierExpr();

    std::string getId() const;

    // ve: Must come from operator new. If not null:
    //     - sets the type of this IdentifierExpr to that of 've';
    //     - this IdentifierExpr becomes owner of 've' and the destructor will
    //       delete the VariableExpr.
    // If this object already had a VariableExpr, the existing one gets destroyed.
    //
    void setVariableExpr(VariableExpr *ve);

    // May be null.
    //
    const VariableExpr *getVariableExpr() const;

    bool isFuncAddrExpr() const;

    virtual bool iterate(Functor &f);

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

private:

    // Forbidden:
    IdentifierExpr(const IdentifierExpr &);
    IdentifierExpr &operator = (const IdentifierExpr &);

private:

    std::string identifier;
    VariableExpr *variableExpr;  // may be null; owned by this IdentifierExpr

};


#endif  /* _H_IdentifierExpr */
