/*  $Id: TreeSequence.cpp,v 1.8 2016/05/06 03:42:56 sarrazip Exp $

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

#include "TreeSequence.h"

#include "TranslationUnit.h"
#include "CastExpr.h"

using namespace std;


TreeSequence::TreeSequence(Tree *tree /*= NULL*/)
:   Tree(),
    sequence()
{
    if (tree != NULL)
        addTree(tree);
}


/*virtual*/
TreeSequence::~TreeSequence()
{
    for (std::vector<Tree *>::iterator it = sequence.begin(); it != sequence.end(); ++it)
        delete *it;
}


void
TreeSequence::addTree(Tree *tree)
{
    assert(tree != NULL);
    sequence.push_back(tree);
}


size_t
TreeSequence::size() const
{
    return sequence.size();
}


vector<Tree *>::const_iterator
TreeSequence::begin() const
{
    return sequence.begin();
}


vector<Tree *>::iterator
TreeSequence::begin()
{
    return sequence.begin();
}


vector<Tree *>::const_iterator
TreeSequence::end() const
{
    return sequence.end();
}


vector<Tree *>::iterator
TreeSequence::end()
{
    return sequence.end();
}


vector<Tree *>::const_reverse_iterator
TreeSequence::rbegin() const
{
    return sequence.rbegin();
}


vector<Tree *>::reverse_iterator
TreeSequence::rbegin()
{
    return sequence.rbegin();
}


vector<Tree *>::const_reverse_iterator
TreeSequence::rend() const
{
    return sequence.rend();
}


vector<Tree *>::reverse_iterator
TreeSequence::rend()
{
    return sequence.rend();
}


/*virtual*/
CodeStatus
TreeSequence::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    pushScopeIfExists();

    bool success = true;
    for (vector<Tree *>::const_iterator it = sequence.begin(); it != sequence.end(); it++)
    {
        const Tree *tree = *it;

        // Do not emit anything if 'tree' is (void) 0 (or other constant expression).
        if (const CastExpr *castExpr = dynamic_cast<const CastExpr *>(tree))
        {
            uint16_t result = 0;
            if (castExpr->getSubExpr()->evaluateConstantExpr(result))
                continue;
        }

        if (!tree->emitCode(out, false))
        {
            success = false;
            break;  // go pop the scope before returning
        }
    }

    popScopeIfExists();

    return success;
}


bool
TreeSequence::iterate(Functor &f)
{
    if (!f.open(this))
        return false;

    for (vector<Tree *>::iterator it = sequence.begin();
                                    it != sequence.end();
                                    it++)
        if (!(*it)->iterate(f))
            return false;

    if (!f.close(this))
        return false;
    return true;
}


void
TreeSequence::replaceChild(Tree *existingChild, Tree *newChild)
{
    for (vector<Tree *>::iterator it = sequence.begin(); it != sequence.end(); it++)
        if (deleteAndAssign(*it, existingChild, newChild))
            return;
    assert(!"child not found");
}
