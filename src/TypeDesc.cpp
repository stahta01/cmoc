/*  $Id: TypeDesc.cpp,v 1.38 2018/09/16 03:34:40 sarrazip Exp $

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
  : type(_basicType), pointedTypeDesc(_pointedTypeDesc),
    returnTypeDesc(NULL), formalParamTypeDescList(), isISR(false), ellipsis(false), isConst(false),
    className(_className), numArrayElements(_numArrayElements), isSigned(_isSigned), isUnion(_isUnion)
{
    assert(!pointedTypeDesc || pointedTypeDesc->isValid());
    assert(isValid());
}


// Forms a FUNCTION_TYPE.
// _returnTypeDesc: Must not be null.
//
TypeDesc::TypeDesc(const TypeDesc *_returnTypeDesc, bool _isISR, bool _endsWithEllipsis)
  : type(FUNCTION_TYPE), pointedTypeDesc(NULL),
    returnTypeDesc(_returnTypeDesc), formalParamTypeDescList(), isISR(_isISR), ellipsis(_endsWithEllipsis), isConst(false),
    className(), numArrayElements(0), isSigned(false), isUnion(false)
{
    assert(returnTypeDesc && returnTypeDesc->isValid());
}


TypeDesc::TypeDesc(const TypeDesc &td)
  : type(td.type), pointedTypeDesc(td.pointedTypeDesc),
    returnTypeDesc(td.returnTypeDesc), formalParamTypeDescList(td.formalParamTypeDescList),
    isISR(td.isISR), ellipsis(td.ellipsis), isConst(td.isConst),
    className(td.className), numArrayElements(td.numArrayElements), isSigned(td.isSigned), isUnion(td.isUnion)
{
}


void
TypeDesc::addFormalParamTypeDesc(const TypeDesc *_formalParamTypeDesc)
{
    assert(_formalParamTypeDesc);
    formalParamTypeDescList.push_back(_formalParamTypeDesc);
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
        return pointedTypeDesc == NULL && !className.empty();
    case POINTER_TYPE:
    case ARRAY_TYPE:
        return pointedTypeDesc != NULL && pointedTypeDesc->isValid() && className.empty() && !isSigned;
    case FUNCTION_TYPE:
        if (returnTypeDesc == NULL || !returnTypeDesc->isValid())
            return false;
		for (vector<const TypeDesc *>::const_iterator it = formalParamTypeDescList.begin();
		                                             it != formalParamTypeDescList.end(); ++it)
		    if (*it == NULL || ! (*it)->isValid())
		        return false;
        return true;
    }
    return false;
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
TypeDesc::isPtrToFunction() const
{
    assert(isValid());
    return type == POINTER_TYPE && pointedTypeDesc->type == FUNCTION_TYPE;
}


bool
TypeDesc::isByteOrWord() const
{
    return type == BYTE_TYPE || type == WORD_TYPE;
}


bool
TypeDesc::isIntegral() const
{
    return isByteOrWord() || isLong();
}


bool
TypeDesc::isLong() const
{
    return type == CLASS_TYPE && (className == "_ULong" || className == "_Long");
}


bool
TypeDesc::isReal() const
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
TypeDesc::isRealOrLong() const
{
    return isReal() || isLong();
}


bool
TypeDesc::isNumerical() const
{
    return isIntegral() || isReal();
}


bool
TypeDesc::isStruct() const
{
    return type == CLASS_TYPE && !isNumerical();
}


bool
TypeDesc::isInterruptServiceRoutine() const
{
    return isISR;
}


bool
TypeDesc::isConstant() const
{
    if (isConst)
        return true;
    if (type != ARRAY_TYPE)
        return false;
    return pointedTypeDesc->isConstant();
}


bool
TypeDesc::canGoInReadOnlySection(bool isRelocatabilitySupported) const
{
    if (isConst)
        return true;
    if (type != ARRAY_TYPE)
        return false;
    if (pointedTypeDesc->type == POINTER_TYPE && ! pointedTypeDesc->isConst)  // array of modifiable pointers
        return false;
    if (pointedTypeDesc->type == POINTER_TYPE && isRelocatabilitySupported)  // array of ptrs: array[i] could be array name, so need run-time init
        return false;
    return pointedTypeDesc->canGoInReadOnlySection(isRelocatabilitySupported);
}


const TypeDesc *
TypeDesc::getPointedTypeDesc() const
{
    if (type == POINTER_TYPE || type == ARRAY_TYPE)
        return pointedTypeDesc;
    return NULL;
}


const TypeDesc *
TypeDesc::getReturnTypeDesc() const
{
    assert(isValid());
    return returnTypeDesc;
}


const vector<const TypeDesc *> &
TypeDesc::getFormalParamTypeDescList() const
{
    return formalParamTypeDescList;
}


bool
TypeDesc::endsWithEllipsis() const
{
    return ellipsis;
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
TypeDesc::pointsToSameType(const TypeDesc &td) const
{
    const TypeDesc *thisPT = getPointedTypeDesc();
    if (!thisPT)
        return false;
    const TypeDesc *otherPT = td.getPointedTypeDesc();
    return otherPT && *thisPT == *otherPT;
}


int
TypeDesc::compare(const TypeDesc &a, const TypeDesc &b)
{
    assert(a.isValid());
    assert(b.isValid());
    if (a.type != b.type)
        return -1;
    const int isrComparison = (a.isISR == b.isISR ? 0 : -2);
    switch (a.type)
    {
    case BYTE_TYPE:
    case WORD_TYPE:
        return (a.isSigned == b.isSigned && a.isConst == b.isConst) ? 0 : -1;
    case CLASS_TYPE:
        return (a.className == b.className && a.isConst == b.isConst) ? 0 : -1;
    case POINTER_TYPE:
    case ARRAY_TYPE:
        if (a.isConst != b.isConst)
            return -1;
        return compare(*a.pointedTypeDesc, *b.pointedTypeDesc);
    case VOID_TYPE:
        if (a.isConst != b.isConst)
            return -1;
        return isrComparison;
    case FUNCTION_TYPE:
        if (a.isConst != b.isConst)
            return -1;
        if (a.ellipsis != b.ellipsis)
            return -1;
        if (int code = compare(*a.returnTypeDesc, *b.returnTypeDesc))
            return code;
        if (a.formalParamTypeDescList.size() != b.formalParamTypeDescList.size())
            return -1;
        for (vector<const TypeDesc *>::const_iterator itA = a.formalParamTypeDescList.begin(),
                                                      itB = b.formalParamTypeDescList.begin();
                                               itA != a.formalParamTypeDescList.end(); ++itA, ++itB)
            if (int code = compare(**itA, **itB))
                return code;
        return isrComparison;
    case SIZELESS_TYPE:
        if (a.isConst != b.isConst)
            return -1;
        return isrComparison;
    }
    return -1;
}


bool
operator == (const TypeDesc &a, const TypeDesc &b)
{
    return TypeDesc::compare(a, b) == 0;
}


bool
TypeDesc::sameTypesModuloConst(const TypeDesc &a, const TypeDesc &b)
{
    TypeDesc tmp(a);
    tmp.isConst = b.isConst;
    return tmp == b;
}


void
TypeDesc::printFunctionSignature(std::ostream &out, const TypeDesc &funcTD,
                                 bool pointer, bool isPointerConst, bool arrayOfPointers)
{
    assert(funcTD.type == FUNCTION_TYPE);
    if (funcTD.isISR)
        out << "interrupt ";
    out << *funcTD.returnTypeDesc;
    if (funcTD.returnTypeDesc->type != POINTER_TYPE)
        out << " ";
    out << "(";
    if (pointer)
    {
        out << "*";
        if (isPointerConst)
            out << " const";
        if (isPointerConst && arrayOfPointers)
            out << " ";
        if (arrayOfPointers)
            out << "[]";  // dimensions would go here
    }
    out << ")(";
    for (vector<const TypeDesc *>::const_iterator it = funcTD.formalParamTypeDescList.begin(); it != funcTD.formalParamTypeDescList.end(); ++it)
    {
        if (it != funcTD.formalParamTypeDescList.begin())
            out << ", ";
        out << **it;
    }
    if (funcTD.ellipsis)
        out << ", ...";
    out << ")";
}


std::ostream &
operator << (std::ostream &out, const TypeDesc &td)
{
    assert(td.isValid());

    switch (td.type)
    {
    case POINTER_TYPE:
        if (td.pointedTypeDesc->type == FUNCTION_TYPE)
        {
            TypeDesc::printFunctionSignature(out, *td.pointedTypeDesc, true, td.isConst, false);
            break;
        }
        out << *td.pointedTypeDesc;
        if (td.pointedTypeDesc->type != POINTER_TYPE)
            out << " ";
        out << "*";
        if (td.isConst)
            out << " const";
        break;
    case ARRAY_TYPE:
    {
        if (td.pointedTypeDesc->type == POINTER_TYPE && td.pointedTypeDesc->pointedTypeDesc->type == FUNCTION_TYPE)
        {
            TypeDesc::printFunctionSignature(out, *td.pointedTypeDesc->pointedTypeDesc, true, td.pointedTypeDesc->isConst, true);
            break;
        }
        string numElem = (td.numArrayElements == uint16_t(-1) ? "" : wordToString(td.numArrayElements, false));
        out << *td.pointedTypeDesc << "[" << numElem << "]";
        break;
    }
    case CLASS_TYPE:
        if (td.isConst)
            out << "const ";
        if (td.isSingle())
            out << "float";
        else if (td.isDouble())
            out << "double";
        else if (td.isLong())
        {
            if (!td.isSigned)
                out << "unsigned ";
            out << "long";
        }
        else
            out << (td.isUnion ? "union" : "struct") << " " << td.className;
        break;
    case FUNCTION_TYPE:
        TypeDesc::printFunctionSignature(out, td, false, false, false);
        break;
    default:
        if (td.isISR)
            out << "interrupt ";
        if (td.isConst)
            out << "const ";
        if (!td.isSigned && td.isIntegral())
            out << "unsigned ";
        out << td.type;
    }

    return out;
}


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
        case FUNCTION_TYPE: return "function";
        case SIZELESS_TYPE: return "sizeless";
    }
    return "???";
}


std::ostream &
operator << (std::ostream &out, BasicType bt)
{
    return out << getBasicTypeName(bt);
}
