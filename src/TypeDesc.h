/*  $Id: TypeDesc.h,v 1.8 2016/10/08 18:15:06 sarrazip Exp $

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

#ifndef _H_TypeDesc
#define _H_TypeDesc

#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>


enum BasicType
{
    VOID_TYPE,
    BYTE_TYPE,
    WORD_TYPE,
    POINTER_TYPE,
    ARRAY_TYPE,
    CLASS_TYPE,
    SIZELESS_TYPE,  // for 'signed' and 'unsigned'
};


inline
const char *
getBasicTypeName(BasicType bt)
{
    switch (bt)
    {
        case VOID_TYPE: return "void";
        case BYTE_TYPE: return "char";
        case WORD_TYPE: return "int";
        case POINTER_TYPE: return "pointer";
        case ARRAY_TYPE: return "array";
        case CLASS_TYPE: return "class";
        case SIZELESS_TYPE: return "sizeless";
    }
    return "???";
}


inline
std::ostream &
operator << (std::ostream &out, BasicType bt)
{
    return out << getBasicTypeName(bt);
}


// Instances must be allocated only by TypeManager.
//
class TypeDesc
{
public:
    BasicType type;
    const TypeDesc *pointedTypeDesc;  // must come from TypeManager or be null;
                                      // relevant when type == POINTER_TYPE or type == ARRAY_TYPE
    std::string className;      // non empty if type == CLASS_TYPE
    uint16_t numArrayElements;  // relevant when type == ARRAY_TYPE; uint16_t(-1) means undermined number of elements
    bool isSigned;
    bool isUnion;               // false means struct (only applies when type == CLASS_TYPE)


    bool isValid() const;

    std::string toString() const;

    bool isArray() const;

    bool isPtrOrArray() const;

    bool isIntegral() const;

    bool isNumerical() const;

    bool isLong() const;

    bool isFloat() const;

    bool isSingle() const;

    bool isDouble() const;

    const TypeDesc *getPointedTypeDesc() const;

    BasicType getPointedType() const;

    size_t getPointerLevel() const;

    void appendDimensions(std::vector<uint16_t> &arrayDimensions) const;

    // Returns a number of elements, not a number of bytes.
    //
    size_t getNumArrayElements() const;

private:

    friend class TypeManager;  // the only class that can create TypeDesc instances

    TypeDesc(BasicType _basicType,
             const TypeDesc *_pointedTypeDesc,
             const std::string &_className,
             bool _isSigned,
             bool _isUnion,
             uint16_t _numArrayElements = uint16_t(-1));

    // Forbidden:
    TypeDesc(const TypeDesc &);
    TypeDesc &operator = (const TypeDesc &);

};


std::ostream &operator << (std::ostream &out, const TypeDesc &td);


bool operator == (const TypeDesc &a, const TypeDesc &b);


inline bool
operator != (const TypeDesc &a, const TypeDesc &b)
{
    return !(a == b);
}


std::ostream &
operator << (std::ostream &out, const TypeDesc &td);


int16_t getTypeSize(BasicType t);


#endif  /* _H_TypeDesc */
