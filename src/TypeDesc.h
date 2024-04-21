/*  $Id: TypeDesc.h,v 1.44 2024/02/12 02:48:32 sarrazip Exp $

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

#include <string.h>
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
    FUNCTION_TYPE,
    SIZELESS_TYPE,  // for 'signed' and 'unsigned'
};


const char *getBasicTypeName(BasicType bt);


std::ostream &operator << (std::ostream &out, BasicType bt);


// Instances must be allocated only by TypeManager.
//
class TypeDesc
{
public:
    BasicType type;
    const TypeDesc *pointedTypeDesc;  // must come from TypeManager or be null;
                                      // relevant when type == POINTER_TYPE or type == ARRAY_TYPE
private:
    // Revelant only when type == FUNCTION_TYPE:
    const TypeDesc *returnTypeDesc;
    std::vector<const TypeDesc *> formalParamTypeDescList;  // may be empty
    bool isISR;  // function type uses the 'interrupt' keyword
    bool ellipsis;  // variadic function, i.e., arguments end with '...'
    bool receivesFirstParamInReg; // function that expects its first argument in a register, instead of on stack
    bool isConst;

public:
    std::string className;      // non empty if type == CLASS_TYPE
    uint16_t numArrayElements;  // relevant when type == ARRAY_TYPE; uint16_t(-1) means undetermined number of elements
    bool isSigned;
    bool isUnion;               // false means struct (only applies when type == CLASS_TYPE)


    bool isValid() const;

    std::string toString() const;

    bool isArray() const;

    bool isPtrOrArray() const;

    bool isPtrToArray() const;

    // The signedness of the char type is ignored.
    //
    bool isArrayOfChar() const;
    bool isPtrToChar() const;
    bool isPtrOrArrayOfChar() const;

    bool isPtrToFunction() const;

    // Returns 1 if this type is a pointer to a function, e.g., void (*)(void).
    // Returns 2 if this type is a pointer to a pointer to a function, e.g., void (**)(void).
    // Returns N+1 if this type is a pointer to an N-th level pointer to a function.
    // Returns 0 if this type is a pointer to something other than a function.
    // Returns 0 if this type is not a pointer.
    // Returns 0 if this type is an array.
    //
    size_t getFunctionPointerLevel() const;

    bool isUnsignedByte() const { return !isSigned && type == BYTE_TYPE; }

    bool isUnsignedShort() const { return !isSigned && type == WORD_TYPE; }

    bool isByteOrWord() const;

    bool isByteOrWordOrPointer() const;

    bool isIntegral() const;

    bool isNumerical() const;

    bool isLong() const;

    bool isReal() const;

    bool isSingle() const;

    bool isDouble() const;

    bool isRealOrLong() const;

    // Also returns true for a union.
    //
    bool isStruct() const;

    bool isInterruptServiceRoutine() const;

    bool isFunctionReceivingFirstParamInReg() const;

    bool isTypeWithCallingConventionFlags() const;

    bool isTypeWithoutCallingConventionFlags() const;

    // Returns true if this type has the const keyword at the first level (e.g., const int)
    // or if it is an array of elements whose type isConstant() (e.g., const int a[]).
    // Note that this method returns false for 'const int *', because the pointer is writable,
    // i.e., the const keyword is not at the first level.
    // This function's name is misleading. See also isConstAtFirstLevel() and isPointerToOrArrayOfConst().
    //
    bool isConstant() const;

    // Returns true if this type has the const keyword, regardless of whether
    // the pointed-to type is const, in the case of a pointer type.
    // This means that true is returned for 'int * const p', but not for 'const int *p'.
    //
    bool isConstAtFirstLevel() const;

    // Returns true of this type is a pointer to, or an array of, a type that is const
    // at its first level.
    // This means that true is returned for 'const int *p', but not for 'int * const p'.
    //
    bool isPointerToOrArrayOfConst() const;

    // Determines if a variable of this type is suitable for the rodata section, for ROM.
    // This is different from isConstant(), which checks for "C constness".
    //
    bool canGoInReadOnlySection(bool isRelocatabilitySupported) const;

    // Returns a TypeDesc that represents the pointed type.
    // Returns NULL if this type is not a pointer or array.
    //
    const TypeDesc *getPointedTypeDesc() const;

    BasicType getPointedType() const;

    size_t getPointerLevel() const;

    // Returns NULL if this type is not a FUNCTION_TYPE.
    //
    const TypeDesc *getReturnTypeDesc() const;

    const std::vector<const TypeDesc *> &getFormalParamTypeDescList() const;

    bool endsWithEllipsis() const;

    void appendDimensions(std::vector<uint16_t> &arrayDimensions) const;

    // Returns true if this type is an array whose size is an empty bracket (e.g., int a[]).
    //
    bool isArrayOfUndeterminedSize() const;

    // Returns a number of elements (across all the dimensions), not a number of bytes.
    //
    size_t getTotalNumArrayElements() const;

    // If pointer, then get the final pointer type (e.g., the "int" in "int ***").
    // If not pointer, returns 'this'.
    //
    const TypeDesc *getFinalPointerType() const;

    // If array, then get the final array type (e.g., the "int" in "int[2][3]").
    // If not array, returns 'this'.
    //
    const TypeDesc *getFinalArrayType() const;

    // Returns true iff this type and 'td' are both pointers or arrays
    // and the pointed type is the same.
    //
    bool pointsToSameType(const TypeDesc &td) const;

    const char *getConvToWordIns() const { return isSigned ? "SEX" : "CLRA"; }

    // Returns 0 if a and b are exactly the same type.
    // Returns -1 if they differ.
    // Returns a negate bit field if they differ only by the isISR or receivesFirstParamInReg fields.
    // In the bit field:
    //   2 means differs by isISR;
    //   4 means differs by receivesFirstParamInReg.
    //
    static int compare(const TypeDesc &a, const TypeDesc &b);

    static bool sameTypesModuloConst(const TypeDesc &a, const TypeDesc &b);

    static bool samePointerOrArrayTypesModuloSignedness(const TypeDesc &a, const TypeDesc &b);

    static bool sameTypesModuloConstAtPtrLevel(const TypeDesc &a, const TypeDesc &b);

    static bool sameFunctionTypesModuloKAndREmptyParamLilst(const TypeDesc &a, const TypeDesc &b);

private:

    TypeDesc(const TypeDesc &);

    friend std::ostream &operator << (std::ostream &out, const TypeDesc &td);
    friend bool operator == (const TypeDesc &a, const TypeDesc &b);

    static void printFunctionSignature(std::ostream &out, const TypeDesc &funcTD,
                                       bool pointer, bool isPointerConst, bool arrayOfPointers,
                                       size_t numAsterisks);

    friend class TypeManager;  // the only class that can create TypeDesc instances

    TypeDesc(BasicType _basicType,
             const TypeDesc *_pointedTypeDesc,
             const std::string &_className,
             bool _isSigned,
             bool _isUnion,
             uint16_t _numArrayElements = uint16_t(-1));

    TypeDesc(const TypeDesc *_returnTypeDesc, bool _isISR, bool _endsWithEllipsis, bool _receivesFirstParamInReg);

    void addFormalParamTypeDesc(const TypeDesc *_formalParamTypeDesc);

    bool canMemberGoInReadOnlySection(const TypeDesc *memberTypeDesc, bool isRelocatabilitySupported) const;

    // Forbidden:
    TypeDesc &operator = (const TypeDesc &);

};


class Enumerator;


class TypeSpecifier
{
public:
    const TypeDesc *typeDesc;
    std::string enumTypeName;  // empty for anonymous enum, and for non-enum type
    std::vector<Enumerator *> *enumeratorList;  // null unless enum type

    TypeSpecifier(const TypeDesc *_typeDesc, const std::string &_enumTypeName, std::vector<Enumerator *> *_enumeratorList)
    :   typeDesc(_typeDesc), enumTypeName(_enumTypeName), enumeratorList(_enumeratorList) {}

private:
    TypeSpecifier(const TypeSpecifier &);
    TypeSpecifier &operator = (const TypeSpecifier &);
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
