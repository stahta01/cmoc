/*  $Id: TypeManager.cpp,v 1.17 2016/08/27 00:53:50 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2016 Pierre Sarrazin <http://sarrazip.com/>

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

#include "TypeManager.h"

#include "util.h"
#include "Declarator.h"
#include "WordConstantExpr.h"
#include "ExpressionTypeSetter.h"
#include "ClassDef.h"
#include "Scope.h"
#include "Declarator.h"

using namespace std;


TypeManager::TypeManager()
:   types(),
    typeDefs(),
    enumTypeNames(),
    enumerators()
{
}


void
TypeManager::createBasicTypes()
{
    // The order is significant. See the other methods.
    types.push_back(new TypeDesc(VOID_TYPE, NULL, string(), false, false));
    types.push_back(new TypeDesc(BYTE_TYPE, NULL, string(), false, false));
    types.push_back(new TypeDesc(BYTE_TYPE, NULL, string(), true, false));
    types.push_back(new TypeDesc(WORD_TYPE, NULL, string(), false, false));
    types.push_back(new TypeDesc(WORD_TYPE, NULL, string(), true, false));
    types.push_back(new TypeDesc(SIZELESS_TYPE, NULL, string(), false, false));
    types.push_back(new TypeDesc(SIZELESS_TYPE, NULL, string(), true, false));
}


void
TypeManager::createInternalStructs(Scope &globalScope)
{
    // Internal structs that represent 'float', 'double', 'long' and 'unsigned long', e.g.,
    // struct _Float { unsigned char bytes[N]; };
    // struct _Long { int hi; unsigned lo; };
    //
    // Order matters: these calls add elements to types[] and their indices are used in
    // getFloatType(), getLongType().
    //
    createStructWithPairOfWords(globalScope, "_Long",   true);
    createStructWithPairOfWords(globalScope, "_ULong", false);
    createStructWithArrayOfBytes(globalScope, "_Float",  5);  // TODO: make these sizes changeable with command-line param.
    createStructWithArrayOfBytes(globalScope, "_Double", 8);
}


void
TypeManager::createStructWithArrayOfBytes(Scope &globalScope, const char *structName, size_t numBytesInArray)
{
    types.push_back(new TypeDesc(CLASS_TYPE, NULL, structName, false, false));
    ClassDef *theStruct = new ClassDef();
    theStruct->setName(structName);  // use same name as TypeDesc
    const TypeDesc *memberTypeDesc = getIntType(BYTE_TYPE, false);
    Declarator *memberDeclarator = new Declarator("bytes", "<internal>", 0);  // no source filename and line no
    memberDeclarator->addArraySizeExpr(new WordConstantExpr(numBytesInArray, true, false));  // make the declarator an array
    assert(memberDeclarator->isArray());
    ClassDef::ClassMember *structMember = new ClassDef::ClassMember(memberTypeDesc, memberDeclarator);  // this appends 'unsigned char[]' to types[]
    theStruct->addDataMember(structMember);
    globalScope.declareClass(theStruct);
}


void
TypeManager::createStructWithPairOfWords(Scope &globalScope, const char *structName, bool isHighWordSigned)
{
    types.push_back(new TypeDesc(CLASS_TYPE, NULL, structName, false, false));
    ClassDef *theStruct = new ClassDef();
    theStruct->setName(structName);  // use same name as TypeDesc

    const TypeDesc *highWordTypeDesc = getIntType(WORD_TYPE, isHighWordSigned);
    const TypeDesc *lowWordTypeDesc  = getIntType(WORD_TYPE, false);

    Declarator *highMemberDeclarator = new Declarator("hi", "<internal>", 0);  // no source filename and line no
    Declarator *lowMemberDeclarator  = new Declarator("lo", "<internal>", 0);

    ClassDef::ClassMember *highStructMember = new ClassDef::ClassMember(highWordTypeDesc, highMemberDeclarator);
    ClassDef::ClassMember *lowStructMember  = new ClassDef::ClassMember(lowWordTypeDesc,  lowMemberDeclarator);

    // We compile for a big endian platform, so the high word is declared first.
    theStruct->addDataMember(highStructMember);
    theStruct->addDataMember(lowStructMember);

    globalScope.declareClass(theStruct);
}


TypeManager::~TypeManager()
{
    for (vector<TypeDesc *>::iterator it = types.begin(); it != types.end(); ++it)
        delete *it;

    // Destroy the Enumerator objects.
    for (EnumeratorMap::iterator it = enumerators.begin(); it != enumerators.end(); ++it)
        delete it->second;
}


const TypeDesc *
TypeManager::getVoidType() const
{
    return types[0];
}


const TypeDesc *
TypeManager::getIntType(BasicType byteOrWordType, bool isSigned) const
{
    if (byteOrWordType == BYTE_TYPE)
        return types[isSigned ? 2 : 1];
    if (byteOrWordType == WORD_TYPE)
        return types[isSigned ? 4 : 3];
    assert(false);
    return NULL;
}


const TypeDesc *
TypeManager::getIntType(const TypeDesc *baseTypeDesc, bool isSigned) const
{
    if (baseTypeDesc->type == BYTE_TYPE || baseTypeDesc->type == WORD_TYPE)
        return getIntType(baseTypeDesc->type, isSigned);
    return getLongType(isSigned);
}


const TypeDesc *
TypeManager::getLongType(bool isSigned) const
{
    return types[isSigned ? 7 : 8];
}


const TypeDesc *
TypeManager::getFloatType(bool isDoublePrecision) const
{
    return types[isDoublePrecision ? 11 : 9];
}


const TypeDesc *
TypeManager::getSizelessType(bool isSigned) const
{
    return types[isSigned ? 6 : 5];
}


const TypeDesc *
TypeManager::getPointerTo(const TypeDesc *pointedTypeDesc) const
{
    if (pointedTypeDesc == NULL)
        return NULL;

    for (vector<TypeDesc *>::const_iterator it = types.begin(); it != types.end(); ++it)
    {
        const TypeDesc *td = *it;
        assert(td && td->isValid());
        if (td->type == POINTER_TYPE && td->pointedTypeDesc == pointedTypeDesc)
            return td;
    }

    types.push_back(new TypeDesc(POINTER_TYPE, pointedTypeDesc, string(), false, false));
    return types.back();
}


// Example: getPointerTo([byte], 3) will return byte ***.
// Level zero means typeDesc itself.
//
const TypeDesc *
TypeManager::getPointerTo(const TypeDesc *typeDesc, size_t level) const
{
    for ( ; level > 0; --level)
        typeDesc = getPointerTo(typeDesc);
    return typeDesc;
}


const TypeDesc *
TypeManager::getPointerToIntegral(BasicType byteOrWordType, bool isSigned) const
{
    return getPointerTo(getIntType(byteOrWordType, isSigned));
}


const TypeDesc *
TypeManager::getPointerToVoid() const
{
    return getPointerTo(getVoidType());
}


// Can be called for a non-array, by passing zero for numArrayDimensions.
// Then this function just returns pointedTypeDesc.
//
const TypeDesc *
TypeManager::getArrayOf(const TypeDesc *pointedTypeDesc, size_t numArrayDimensions) const
{
    if (pointedTypeDesc == NULL)
        return NULL;

    if (numArrayDimensions == 0)
        return pointedTypeDesc;

    if (numArrayDimensions == 1)
    {
        for (vector<TypeDesc *>::const_iterator it = types.begin(); it != types.end(); ++it)
        {
            const TypeDesc *td = *it;
            assert(td && td->isValid());
            if (td->type == ARRAY_TYPE && td->pointedTypeDesc == pointedTypeDesc && td->numArrayElements == uint16_t(-1))
                return td;
        }

        types.push_back(new TypeDesc(ARRAY_TYPE, pointedTypeDesc, string(), false, false));
        return types.back();
    }

    return getArrayOf(getArrayOf(pointedTypeDesc, numArrayDimensions - 1), 1);
}


// getSizedArrayOf("int", {2, 3, 4}, 2) gives int[2][3][4].
// It recursively calls getSizedArrayOf("int", {2, 3, 4}, 1) to request int[2][3].
// This calls getSizedArrayOf("int", {2, 3, 4}, 0) to get int[2].
// Then int[2][3] is created and returned.
// Then int[2][3][4] is created and returned.
//
const TypeDesc *
TypeManager::getSizedArrayOf(const TypeDesc *pointedTypeDesc, const std::vector<uint16_t> &arrayDimensions, size_t dimIndex) const
{
    //cerr << "# TypeManager::getSizedArrayOf([" << pointedTypeDesc->toString() << "], {" << join(", ", arrayDimensions) << "}, " << dimIndex << ")\n";
    assert(dimIndex < arrayDimensions.size());

    if (pointedTypeDesc == NULL)
        return NULL;

    if (dimIndex == 0)
    {
        for (vector<TypeDesc *>::const_iterator it = types.begin(); it != types.end(); ++it)
        {
            const TypeDesc *td = *it;
            assert(td && td->isValid());
            if (td->type == ARRAY_TYPE && td->pointedTypeDesc == pointedTypeDesc && td->numArrayElements == arrayDimensions[dimIndex])
                return td;
        }

        types.push_back(new TypeDesc(ARRAY_TYPE, pointedTypeDesc, string(), false, false, arrayDimensions[dimIndex]));
        return types.back();
    }

    const TypeDesc *subTypeDesc = getSizedArrayOf(pointedTypeDesc, arrayDimensions, dimIndex - 1);
    return getSizedArrayOf(subTypeDesc, arrayDimensions, dimIndex);
}


const TypeDesc *
TypeManager::getClassType(const std::string &className, bool isUnion, bool createIfAbsent) const
{
    for (vector<TypeDesc *>::const_iterator it = types.begin(); it != types.end(); ++it)
    {
        const TypeDesc *td = *it;
        assert(td && td->isValid());
        if (td->type == CLASS_TYPE && td->isUnion == isUnion && td->className == className)
            return td;
    }

    if (createIfAbsent)
    {
        if (getClassType(className, !isUnion, false) != NULL)
            errormsg("referring to %s as a %s, but it is a %s",
                        className.c_str(), isUnion ? "union" : "struct", !isUnion ? "union" : "struct");

        types.push_back(new TypeDesc(CLASS_TYPE, NULL, className, false, isUnion));
        return types.back();
    }

    return NULL;
}


const TypeDesc *TypeManager::getFunctionPointerType() const
{
    return getPointerToVoid();
}


// Ends by calling delete on 'declarator'.
//
bool
TypeManager::addTypeDef(const TypeDesc *declSpecTypeDef, Declarator *declarator)
{
    assert(declSpecTypeDef);
    assert(declarator);

    bool success = false;

    string id = declarator->getId();
    TypeDefMap::iterator it = typeDefs.find(id);
    if (it != typeDefs.end())  // if type name already used:
        errormsg("cannot redefine typedef %s", id.c_str());
    else
    {
        // Example: With "typedef int **PP;", declSpecTypeDef represents "int"
        // and declarator represents (2, "PP"), where 2 is the pointer level.
        // The next call assigns "int **" to specificTypeDesc.
        //
        const TypeDesc *specificTypeDesc = declarator->processPointerLevel(declSpecTypeDef);
        assert(specificTypeDesc);
        //cerr << "#   After processPointerLevel: " << specificTypeDesc->toString() << endl;

        vector<uint16_t> arrayDimensions;
        if (declarator->computeArraySize(arrayDimensions))  // arrayDimensions will be empty if non-array
        {
            if (arrayDimensions.size() > 0)
            {
                specificTypeDesc = getSizedArrayOf(specificTypeDesc, arrayDimensions, arrayDimensions.size() - 1);
                //cerr << "#   After getSizedArrayOf    : " << specificTypeDesc->toString() << endl;
            }

            typeDefs[id] = specificTypeDesc;
            success = true;
        }
    }

    delete declarator;

    return success;
}


const TypeDesc *
TypeManager::getTypeDef(const char *id) const
{
    TypeDefMap::const_iterator it = typeDefs.find(id);
    if (it != typeDefs.end())
        return it->second;
    return NULL;
}


// If an Enumerator in enumerationList is a duplicate, it gets destroyed
// and removed from enumerationList.
// Otherwise, calls declareEnumerator() for each Enumerator.
// Also registers the enum type name with the list of its enumerated names.
//
// Does not keep a reference to enumerationList.
//
void
TypeManager::declareEnumerationList(const std::string &enumTypeName,
                                    std::vector<Enumerator *> &enumerationList)
{
    if (!enumTypeName.empty())
    {
        EnumTypeNameMap::const_iterator it = enumTypeNames.find(enumTypeName);
        if (it != enumTypeNames.end())
            errormsg("enum `%s' already defined at %s", enumTypeName.c_str(), it->second.sourceLineNo.c_str());
        else
        {
            // Register the named enum with the source line number where it is defined
            // and with the names of its members.
            //
            enumTypeNames[enumTypeName] = NamedEnum(getSourceLineNo());
            NamedEnum &namedEnum = enumTypeNames[enumTypeName];
            for (std::vector<Enumerator *>::const_iterator it = enumerationList.begin();
                                                          it != enumerationList.end(); ++it)
                namedEnum.members.push_back((*it)->name);
        }
    }

    const Enumerator *prevEnumerator = NULL;

    for (vector<Enumerator *>::iterator it = enumerationList.begin();
                                       it != enumerationList.end(); /* iterator moves in for() body */ )
    {
        Enumerator *enumerator = *it;
        if (!declareEnumerator(enumerator))
        {
            delete enumerator;
            it = enumerationList.erase(it);
            continue;
        }

        enumerator->setPreviousEnumerator(prevEnumerator);  // tie each enumerator to its predecessor(s)
        prevEnumerator = enumerator;
        ++it;
    }
}


// enumerator: Upon success, this pointer is stored in the 'enumerators' map.
// Returns true for success, false for failure (an error message is issued and
// 'enumerator' is not destroyed).
//
bool
TypeManager::declareEnumerator(Enumerator *enumerator)
{
    assert(enumerator);

    EnumeratorMap::const_iterator existingEnumerator = enumerators.find(enumerator->name);
    if (existingEnumerator != enumerators.end())
    {
        errormsg("enumerated name `%s' already defined at %s",
                 enumerator->name.c_str(), existingEnumerator->second->sourceLineNo.c_str());
        return false;
    }

    enumerators[enumerator->name] = enumerator;
    return true;
}

bool
TypeManager::isEnumeratorName(const string &id) const
{
    return enumerators.find(id) != enumerators.end();
}


const TypeDesc *
TypeManager::getEnumeratorTypeDesc(const std::string &id) const
{
    EnumeratorMap::const_iterator it = enumerators.find(id);
    if (it == enumerators.end())
        return NULL;  // not an enumerated name

    const Enumerator *enumerator = it->second;
    while (enumerator && enumerator->valueExpr == NULL)
        enumerator = enumerator->previousEnumerator;
    if (!enumerator)
        return getIntType(WORD_TYPE, true);  // signed int as default

    return enumerator->valueExpr->getTypeDesc();
}


bool
TypeManager::getEnumeratorValue(const std::string &id, uint16_t &value) const
{
    EnumeratorMap::const_iterator it = enumerators.find(id);
    if (it == enumerators.end())
        return false;  // not an enumerated name

    const Enumerator *enumerator = it->second;
    uint16_t increment = 0;
    while (enumerator && enumerator->valueExpr == NULL)
    {
        // Use value of preceding name, if any, plus one.
        enumerator = enumerator->previousEnumerator;
        ++increment;
    }

    if (!enumerator)  // if no initializer expression found before reaching start of enum{}
    {
        value = increment - 1;  // value depends on rank of 'id' in enum{}
        return true;
    }

    if (!enumerator->valueExpr->evaluateConstantExpr(value))
    {
        enumerator->valueExpr->errormsg("expression for enumerated name `%s' must be constant", id.c_str());
        value = 0;  // return zero as fallback value; no code should be emitted anyway
        return true;
    }

    value += increment;
    return true;
}


bool
TypeManager::isIdentiferMemberOfNamedEnum(const std::string &enumTypeName, const std::string &id) const
{
    EnumTypeNameMap::const_iterator it = enumTypeNames.find(enumTypeName);
    if (it == enumTypeNames.end())
        return false;  // unknown enum
    const NamedEnum &namedEnum = it->second;
    return find(namedEnum.members.begin(), namedEnum.members.end(), id) != namedEnum.members.end();
}


void
TypeManager::setEnumeratorTypes() const
{
    /*for (EnumTypeNameMap::const_iterator it = enumTypeNames.begin(); it != enumTypeNames.end(); ++it)
        cout << "# enum " << it->first << " defined at " << it->second.sourceLineNo << "\n";*/

    ExpressionTypeSetter ets;
    for (EnumeratorMap::const_iterator it = enumerators.begin(); it != enumerators.end(); ++it)
    {
        const Enumerator *enumerator = it->second;
        assert(enumerator);
        //cout << "# enumerator " << it->first << ": valueExpr=" << enumerator->valueExpr << "\n";
        if (enumerator->valueExpr)
        {
            //cout << "#     type: " << *enumerator->valueExpr->getTypeDesc() << "\n";
            enumerator->valueExpr->iterate(ets);
        }
    }
}


void
TypeManager::dumpTypes(std::ostream &out) const
{
    for (vector<TypeDesc *>::const_iterator it = types.begin(); it != types.end(); ++it)
        out << **it << "\n";
}


Enumerator::Enumerator(const char *_name, Tree *_valueExpr, const std::string &_sourceLineNo)
:   name(_name),
    valueExpr(_valueExpr),
    sourceLineNo(_sourceLineNo),
    previousEnumerator(NULL)
{
}


Enumerator::~Enumerator()
{
    delete valueExpr;
}
