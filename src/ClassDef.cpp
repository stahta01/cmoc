/*  $Id: ClassDef.cpp,v 1.6 2015/08/09 06:17:41 sarrazip Exp $

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

#include "ClassDef.h"

#include "FunctionDef.h"
#include "TranslationUnit.h"

using namespace std;


ClassDef::ClassDef()
  : Tree(),
    name(),
    dataMembers(),
    Union(false)
{
}


/*virtual*/
ClassDef::~ClassDef()
{
    clearMembers();
}


void
ClassDef::setName(const string &_name)
{
    name = _name;
}


string
ClassDef::getName() const
{
    return name;
}


void
ClassDef::setUnion(bool u)
{
    Union = u;
}


bool
ClassDef::isUnion() const
{
    return Union;
}


void
ClassDef::addDataMember(ClassMember *m)
{
    if (m != NULL)
        dataMembers.push_back(m);
}


int16_t
ClassDef::getSizeInBytes() const
{
    int16_t aggregateSize = 0;
    for (vector<ClassMember *>::const_iterator it = dataMembers.begin();
                                              it != dataMembers.end(); it++)
    {
        int16_t memberSize = (*it)->getSizeInBytes();
        if (Union)
            aggregateSize = max(aggregateSize, memberSize);
        else
            aggregateSize += memberSize;
    }
    return aggregateSize;
}


const ClassDef::ClassMember *
ClassDef::getDataMember(const string &name) const
{
    for (vector<ClassMember *>::const_iterator it = dataMembers.begin();
                                              it != dataMembers.end(); it++)
        if ((*it)->getName() == name)
            return *it;
    return NULL;
}


int16_t
ClassDef::getDataMemberOffset(const string &name,
                              const ClassMember *&member) const
{
    int16_t offset = 0;
    member = NULL;
    for (vector<ClassMember *>::const_iterator it = dataMembers.begin();
                                              it != dataMembers.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            member = *it;
            return Union ? 0 : offset;
        }
        offset += (*it)->getSizeInBytes();
    }
    return -1;
}


void
ClassDef::clearMembers()
{
    for (std::vector<ClassMember *>::iterator it = dataMembers.begin(); it != dataMembers.end(); ++it)
        delete *it;
    dataMembers.clear();
}


///////////////////////////////////////////////////////////////////////////////


ClassDef::ClassMember::ClassMember(const TypeDesc *_tp, Declarator *_di)
  : Tree(_tp), declarator(_di)
{
    assert(declarator != NULL);
    if (isArray())
    {
        // If this member is 'char a[4]' for example, then _tp is "char".
        // We adjust the member type to char array.
        //
        size_t numDims = 1;
        if (!_di->getNumDimensions(numDims))
            numDims = 1;  // failsafe
        setTypeDesc(TranslationUnit::getTypeManager().getArrayOf(getTypeDesc(), numDims));
    }
}


ClassDef::ClassMember::~ClassMember()
{
    assert(declarator != NULL);
    delete declarator;
}


std::string
ClassDef::ClassMember::getName() const
{
    assert(declarator != NULL);
    return declarator->getId();
}


// Returns 1 for a non-array class member.
//
int16_t
ClassDef::ClassMember::getNumArrayElements() const
{
    assert(declarator != NULL);

    uint16_t numElements = declarator->getArraySize();
    return int16_t(numElements > 0 ? numElements : 1);
}


int16_t
ClassDef::ClassMember::getSizeInBytes() const
{
    assert(declarator != NULL);

    const TypeDesc *td = getTypeDesc();
    while (td->type == ARRAY_TYPE)
    {
        td = td->pointedTypeDesc;
        assert(td);
    }

   return TranslationUnit::instance().getTypeSize(*td) * getNumArrayElements();
}


std::vector<uint16_t>
ClassDef::ClassMember::getArrayDimensions() const
{
    assert(declarator != NULL);

    vector<uint16_t> arrayDimensions;
    if (!declarator->computeArraySize(arrayDimensions))
        assert(false);
    return arrayDimensions;
}


bool
ClassDef::ClassMember::isArray() const
{
    assert(declarator != NULL);
    return declarator->getArraySize() > 0;
}


const Declarator &
ClassDef::ClassMember::getDeclarator() const
{
    return *declarator;
}
