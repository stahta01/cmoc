/*  $Id: TypeDesc.cpp,v 1.11 2016/10/11 01:23:50 sarrazip Exp $

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

#include "TypeDesc.h"

#include "util.h"

using namespace std;


TypeDesc::TypeDesc(BasicType _basicType,
                   const TypeDesc *_pointedTypeDesc,
                   const string &_className,
                   bool _isSigned,
                   bool _isUnion,
                   uint16_t _numArrayElements)
  : type(_basicType), pointedTypeDesc(_pointedTypeDesc), className(_className),
    numArrayElements(_numArrayElements), isSigned(_isSigned), isUnion(_isUnion)
{
    assert(!pointedTypeDesc || pointedTypeDesc->isValid());
    assert(isValid());
}


bool
TypeDesc::isValid() const
{
    if (isUnion && type != CLASS_TYPE)
        return false;
    switch (type)
    {
    case VOID_TYPE:
    case BYTE_TYPE:
    case WORD_TYPE:
    case SIZELESS_TYPE:
        return pointedTypeDesc == NULL && className.empty();
    case CLASS_TYPE:
        return pointedTypeDesc == NULL && !className.empty() && !isSigned;
    case POINTER_TYPE:
    case ARRAY_TYPE:
        return pointedTypeDesc != NULL && pointedTypeDesc->isValid() && className.empty() && !isSigned;
    default:
        return false;
    }
}


string
TypeDesc::toString() const
{
    stringstream ss;
    ss << *this;
    return ss.str();
}


bool
TypeDesc::isArray() const
{
    return type == ARRAY_TYPE;
}


bool
TypeDesc::isPtrOrArray() const
{
    return type == POINTER_TYPE || type == ARRAY_TYPE;
}


bool
TypeDesc::isIntegral() const
{
    return type == BYTE_TYPE || type == WORD_TYPE || isLong();
}


bool
TypeDesc::isLong() const
{
    return type == CLASS_TYPE && (className == "_ULong" || className == "_Long");
}


bool
TypeDesc::isFloat() const
{
    return type == CLASS_TYPE && (className == "_Float" || className == "_Double");
}


bool
TypeDesc::isSingle() const
{
    return type == CLASS_TYPE && className == "_Float";
}


bool
TypeDesc::isDouble() const
{
    return type == CLASS_TYPE && className == "_Double";
}


bool
TypeDesc::isNumerical() const
{
    return isIntegral() || isFloat();
}


// Returns a new TypeDesc that represents the pointed type.
// Returns NULL if this type is not a pointer or array.
//
const TypeDesc *
TypeDesc::getPointedTypeDesc() const
{
    if (type == POINTER_TYPE || type == ARRAY_TYPE)
        return pointedTypeDesc;
    return NULL;
}


BasicType
TypeDesc::getPointedType() const
{
    assert(isValid());
    if (!isPtrOrArray())
        return VOID_TYPE;
    return pointedTypeDesc->type;
}


// Returns the number of indirections needed to obtain a non-pointer type.
// Example: "int **" gives 2, "int" gives 0.
//
size_t
TypeDesc::getPointerLevel() const
{
    size_t level = 0;
    const TypeDesc *td = this;
    assert(td->isValid());
    while (td->type == POINTER_TYPE)
    {
        ++level;
        td = td->pointedTypeDesc;
        assert(td && td->isValid());
    }
    return level;
}


void
TypeDesc::appendDimensions(vector<uint16_t> &arrayDimensions) const
{
    const TypeDesc *td = this;
    while (td->type == ARRAY_TYPE)
    {
        if (td->numArrayElements != uint16_t(-1))
            arrayDimensions.push_back(td->numArrayElements);
        td = td->pointedTypeDesc;
        assert(td);
    }
}


// This type may contain an array size, e.g., typedef int Array[5].
// It also may not contain any type: in a "char b[5]" declaration,
// the 5 is part of a Declarator, not part of the TypeDesc, which
// only represents "char".
// The type may also represent both cases: an "Array v[3]" declaration
// will yield a TypeDesc that is "array of array of char", where
// - the first "array" has numArrayElements == uint16_t(-1) because that
//   size must be provided by a Declarator (which will contain 3);
// - the second "array" has numArrayElements == 5 as per the typedef.
//
size_t
TypeDesc::getNumArrayElements() const
{
    size_t numElements = 1;
    const TypeDesc *td = this;
    while (td->type == ARRAY_TYPE)
    {
        if (td->numArrayElements != uint16_t(-1))
            numElements *= td->numArrayElements;
        td = td->pointedTypeDesc;
        assert(td);
    }
    return numElements;
}


bool
operator == (const TypeDesc &a, const TypeDesc &b)
{
    assert(a.isValid());
    assert(b.isValid());
    if (a.type != b.type)
        return false;
    switch (a.type)
    {
    case BYTE_TYPE:
    case WORD_TYPE:
        return a.isSigned == b.isSigned;
    case CLASS_TYPE:
        return a.className == b.className;
    case POINTER_TYPE:
    case ARRAY_TYPE:
        return *a.pointedTypeDesc == *b.pointedTypeDesc;
    case VOID_TYPE:
        return true;
    default:
        return false;
    }
}


std::ostream &
operator << (std::ostream &out, const TypeDesc &td)
{
    assert(td.isValid());

    switch (td.type)
    {
    case POINTER_TYPE:
        out << *td.pointedTypeDesc;
        if (td.pointedTypeDesc->type != POINTER_TYPE)
            out << " ";
        out << "*";
        break;
    case ARRAY_TYPE:
    {
        string numElem = (td.numArrayElements == uint16_t(-1) ? "" : wordToString(td.numArrayElements, false));
        out << *td.pointedTypeDesc << "[" << numElem << "]";
        break;
    }
    case CLASS_TYPE:
        out << (td.isUnion ? "union" : "struct") << " " << td.className;
        break;
    default:
        if (!td.isSigned && td.isIntegral())
            out << "unsigned ";
        out << td.type;
    }

    return out;
}
