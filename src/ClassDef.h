/*  $Id: ClassDef.h,v 1.6 2015/09/17 02:00:02 sarrazip Exp $

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

#ifndef _H_ClassDef
#define _H_ClassDef

#include "Tree.h"
#include "Declarator.h"

#include "util.h"

class FunctionDef;


class ClassDef : public Tree
{
public:

    class ClassMember : public Tree
    {
    public:
        // _di: Must come from new. Will be destroyed by this class's destructor.
        ClassMember(const TypeDesc *_tp, Declarator *_di);

        // Calls delete on Declarator given to constructor.
        ~ClassMember();

        std::string getName() const;

        int16_t getNumArrayElements() const;

        // Returns the size in bytes occupied by this member.
        int16_t getSizeInBytes() const;

        std::vector<uint16_t> getArrayDimensions() const;

        bool isArray() const;

        const Declarator &getDeclarator() const;

    private:
        Declarator *declarator;  // owned by this ClassMember

        // Forbidden:
        ClassMember(const ClassMember &);
        ClassMember &operator = (const ClassMember &);
    };

    ClassDef();

    virtual ~ClassDef();

    void setName(const std::string &_name);

    std::string getName() const;

    void setUnion(bool u);

    bool isUnion() const;

    // The ClassMember must have been allocated with 'new'.
    // It becomes owned by this ClassDef and will be destructed by ~ClassDef().
    //
    void addDataMember(ClassMember *m);

    // Returns the size in bytes occupied by an instance of this class.
    int16_t getSizeInBytes() const;

    size_t getNumDataMembers() const { return dataMembers.size(); }

    const ClassMember *getDataMember(size_t memberIndex) const
    {
        if (memberIndex >= dataMembers.size())
            return NULL;
        return dataMembers[memberIndex];
    }

    const ClassMember *getDataMember(const std::string &name) const;

    // Returns -1 if name not found.
    int16_t getDataMemberOffset(const std::string &name,
                                const ClassMember *&member) const;

    void clearMembers();

private:

    // Forbidden:
    ClassDef(const ClassDef &);
    ClassDef &operator = (const ClassDef &);

private:

    std::string name;
    std::vector<ClassMember *> dataMembers;  // owns the pointed objects
    bool Union;  // false means struct

};


#endif  /* _H_ClassDef */
