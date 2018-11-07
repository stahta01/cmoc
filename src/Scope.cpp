/*  $Id: Scope.cpp,v 1.4 2016/03/25 02:00:09 sarrazip Exp $

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

#include "Scope.h"

#include "TreeSequence.h"
#include "Declaration.h"
#include "TranslationUnit.h"
#include "ClassDef.h"

#include <assert.h>
#include <algorithm>

using namespace std;


Scope::Scope(Scope *_parent)
  : Tree(),
    parent(_parent),
    subScopes(),
    declTable(),
    classTable()
{
    if (parent != NULL)
        parent->addSubScope(this);
}


Scope::~Scope()
{
    for (vector<Scope *>::iterator its = subScopes.begin();
                                        its != subScopes.end();
                                        its++)
    {
        Scope *child = *its;
        assert(child != NULL);
        assert(child->getParent() == this);
        delete child;
    }

    for (std::map<std::string, ClassDef *>::iterator it = classTable.begin();
                                                    it != classTable.end(); ++it)
        delete it->second;
}



void
Scope::addSubScope(Scope *ss)
{
    assert(ss != NULL);

    // 'ss' must not already be in subScopes.
    assert(find(subScopes.begin(), subScopes.end(), ss) == subScopes.end());

    subScopes.push_back(ss);
}


const Scope *
Scope::getParent() const
{
    return parent;  // allowed to be null
}


Scope *
Scope::getParent()
{
    return parent;  // allowed to be null
}


int16_t
Scope::allocateLocalVariables(int16_t displacement, bool processSubScopes)
{
    /*cerr << "Scope(" << this << ")::allocateLocalVariables("
        << displacement << ", " << processSubScopes << "): " << subScopes.size() << " subscopes\n";*/
    for (vector< pair<string, Declaration *> >::reverse_iterator itd = declTable.rbegin();
                                                                itd != declTable.rend(); itd++)
    {
        Declaration *decl = itd->second;
        assert(decl != NULL);

        if (decl->isGlobal())
        {
            assert(!"global declaration in a Scope on which allocateLocalVariables() is called");
            continue;
        }

        uint16_t size = 0;
        if (!decl->getVariableSizeInBytes(size))
        {
            errormsg("invalid dimensions for array %s", decl->getVariableId().c_str());
            continue;
        }
        if (size > 32767)
        {
            errormsg("local variable %s exceeds maximum of 32767 bytes", decl->getVariableId().c_str());
            continue;
        }

        displacement -= int16_t(size);
        /*cerr << "  " << decl->getVariableId() << " is "
                << decl->getVariableSize()
                << " byte(s), which puts displacement at "
                << displacement << "\n";*/
        decl->setFrameDisplacement(displacement);
    }

    int16_t minDisplacement = displacement;

    if (processSubScopes)
        for (vector<Scope *>::iterator its = subScopes.begin();
                                      its != subScopes.end(); its++)
        {
            int16_t d = (*its)->allocateLocalVariables(displacement, true);
            minDisplacement = min(minDisplacement, d);
        }

    /*std::cerr << "Scope(" << this << ")::allocateLocalVariables: "
                << "returning minDisplacement of " << minDisplacement << "\n";*/
    return minDisplacement;
}


bool
Scope::declareVariable(Declaration *d)
{
    assert(d != NULL);
    const string &id = d->getVariableId();
    const Declaration *found = getVariableDeclaration(id, false);
    if (found != NULL)  // if already declared in this scope
        return false;
    declTable.push_back(make_pair(id, d));
    return true;
}


Declaration *
Scope::getVariableDeclaration(const string &id, bool lookInAncestors) const
{
    for (vector< pair<string, Declaration *> >::const_iterator it = declTable.begin();
                                                              it != declTable.end(); ++it)
        if (it->first == id)
        {
            Declaration *decl = it->second;
            return decl;
        }

    if (lookInAncestors && parent != NULL)
        return parent->getVariableDeclaration(id, lookInAncestors);

    return NULL;
}


void
Scope::destroyDeclarations()
{
    for (vector< pair<string, Declaration *> >::iterator it = declTable.begin();
                                                        it != declTable.end(); ++it)
        delete it->second;

    declTable.clear();
}


void
Scope::declareClass(ClassDef *cl)
{
    if (cl == NULL)
        return;
    const string &className = cl->getName();
    assert(!className.empty());

    if (classTable.find(className) != classTable.end())
    {
        cl->errormsg("struct %s already declared", className.c_str());
        return;
    }

    classTable[className] = cl;
}


const ClassDef *
Scope::getClassDef(const std::string &className) const
{
    map<string, ClassDef *>::const_iterator it = classTable.find(className);
    //cerr << "Scope[" << this << "]: getClassDef('" << className << "'): "
    //      << (it != classTable.end()) << "\n";
    return (it != classTable.end() ? it->second : (ClassDef *) 0);
}


void
Scope::getDeclarationIds(std::vector<std::string> &dest) const
{
    for (vector< pair<string, Declaration *> >::const_iterator it = declTable.begin();
                                                              it != declTable.end(); it++)
        dest.push_back(it->first);
}
