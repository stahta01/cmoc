/*  $Id: ExpressionTypeSetter.h,v 1.2 2015/05/31 23:43:24 sarrazip Exp $

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

#ifndef _H_ExpressionTypeSetter
#define _H_ExpressionTypeSetter

#include "Tree.h"

class BinaryOpExpr;
class UnaryOpExpr;


class ExpressionTypeSetter : public Tree::Functor
{
public:
    ExpressionTypeSetter();
    virtual ~ExpressionTypeSetter();

    virtual bool close(Tree *t);

private:
    bool processBinOp(BinaryOpExpr *bin);
    bool processUnaryOp(UnaryOpExpr *un);
};


#endif  /* _H_ExpressionTypeSetter */
