/*  $Id: TreeSequence.h,v 1.7 2016/09/15 03:34:57 sarrazip Exp $

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

#ifndef _H_TreeSequence
#define _H_TreeSequence

#include "Tree.h"


class TreeSequence : public Tree
{
public:

    // If 'tree' is not null, adds it to this sequence.
    //
    TreeSequence(Tree *tree = NULL);

    virtual ~TreeSequence();

    void addTree(Tree *tree);

    size_t size() const;
    std::vector<Tree *>::const_iterator begin() const;
    std::vector<Tree *>::iterator begin();
    std::vector<Tree *>::const_iterator end() const;
    std::vector<Tree *>::iterator end();
    std::vector<Tree *>::const_reverse_iterator rbegin() const;
    std::vector<Tree *>::reverse_iterator rbegin();
    std::vector<Tree *>::const_reverse_iterator rend() const;
    std::vector<Tree *>::reverse_iterator rend();

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

    virtual void replaceChild(Tree *existingChild, Tree *newChild);

    virtual bool isLValue() const { return false; }

private:
    std::vector<Tree *> sequence;  // owns the Tree objects
};


#endif  /* _H_TreeSequence */
