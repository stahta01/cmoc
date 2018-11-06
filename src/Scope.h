/*  $Id: Scope.h,v 1.5 2016/09/18 06:10:52 sarrazip Exp $

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

#ifndef _H_Scope
#define _H_Scope

#include "Tree.h"

class TreeSequence;
class Declaration;
class ClassDef;


class Scope
{
public:

    // Calls addSubScope(this) on _parent if _parent is not null.
    // _parent thus becomes owner of this Scope.
    //
    Scope(Scope *_parent);

    // Calls delete on each sub-scope of this scope.
    //
    virtual ~Scope();

    // This Scope becomes owner of 'ss', which must not be null.
    // ~Scope() will delete it.
    //
    void addSubScope(Scope *ss);

    const Scope *getParent() const;

    Scope *getParent();

    // Allocate a frame displacement to each Declaration in this scope's
    // declaration table, except those that represent a global array with
    // an initializer.
    // The Declaration objects are allocated in the reverse order in which
    // they were added by declareVariable().
    // The declaractions in the sub-scopes are only processed if
    // 'processSubScopes' is true.
    //
    int16_t allocateLocalVariables(int16_t displacement, bool processSubScopes);

    // Keeps a copy of the Declaration address.
    // This Scope object does NOT own the Declaration objects.
    // Returns false if a declaration of the same ID is already present
    // in this Scope.
    // Returns true otherwise ('d' has been added to this Scope's
    // declaration table).
    //
    bool declareVariable(Declaration *d);

    // Returns the Declaration object belonging to this Scope
    // whose ID is the given one.
    // Only consults the ancestors of this Scope if 'lookInAncestors' is true.
    //
    Declaration *getVariableDeclaration(const std::string &id,
                                        bool lookInAncestors) const;

    // Returns the identifiers of all declarations in this scope.
    //
    void getDeclarationIds(std::vector<std::string> &dest) const;

    // Calls operator delete on each Declaration object passed to
    // this Scope through calls to declareVariable().
    // This Scope's declaration table becomes empty.
    //
    void destroyDeclarations();

    void declareClass(ClassDef *cl);

    const ClassDef *getClassDef(const std::string &className) const;

    /** @param  f               functor that accepts a reference to a
                                ClassDef object
    */
    template <class F>
    void forEachClassDef(F &f);

    virtual bool isLValue() const { return false; }

private:

    Scope *parent;  // NULL if global scope; 'parent' not owned by this Scope
    std::vector<Scope *> subScopes;  // OWNS the pointed objects
    std::vector< std::pair<std::string, Declaration *> > declTable;
                                // does not own the pointed objects
                                // no two entries may have same string value
    std::map<std::string, ClassDef *> classTable;
                                // owns the pointed objects

    // Forbidden operations:
    Scope(const Scope &x);
    Scope &operator = (const Scope &x);

};


template <class F>
void
Scope::forEachClassDef(F &f)
{
    for (std::map<std::string, ClassDef *>::iterator it = classTable.begin();
                                                it != classTable.end(); it++)
        f(*it->second);
}


#endif  /* _H_Scope */
