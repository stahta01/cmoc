/*  AncestorFunctor.h

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2022 Pierre Sarrazin <http://sarrazip.com/>

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

#ifndef _H_AncestorFunctor
#define _H_AncestorFunctor

#include "FunctionDef.h"


class AncestorFunctor : public Tree::Functor
{
public:

    AncestorFunctor();

    ~AncestorFunctor();

    virtual bool open(Tree *t);

    virtual bool close(Tree *t);

private:

    static bool doesParentNeedValueOfChild(const Tree *parent, const Tree *child);

    // Forbidden:
    AncestorFunctor(const AncestorFunctor &);
    AncestorFunctor &operator = (const AncestorFunctor &);

private:

    std::vector<Tree *> ancestors;

};


#endif  /* _H_AncestorFunctor */
