/*  $Id: DeclarationSpecifierList.cpp,v 1.10 2016/08/27 00:53:50 sarrazip Exp $

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

#include "DeclarationSpecifierList.h"

#include "TranslationUnit.h"

using namespace std;


DeclarationSpecifierList::DeclarationSpecifierList()
  : typeDesc(NULL),
    isTypeDef(false),
    isISR(false),
    asmOnly(false),
    isExtern(false),
    isStatic(false),
    enumTypeName(),
    enumeratorList(NULL)
{
}

DeclarationSpecifierList::~DeclarationSpecifierList()
{
    // detachEnumeratorList() must have been called.
    if (enumeratorList)
    {
        warnmsg("suspicious use of enum");
        delete enumeratorList;
    }
}


// Does not keep a reference to 'tsToAdd', but keeps a pointer to 'tsToAdd.typeDesc'.
//
void
DeclarationSpecifierList::add(const TypeSpecifier &tsToAdd)
{
    if (!typeDesc)
    {
        typeDesc = tsToAdd.typeDesc;
        enumTypeName = tsToAdd.enumTypeName;
        assert(!enumeratorList);
        enumeratorList = tsToAdd.enumeratorList;

        if (enumeratorList)
            TranslationUnit::getTypeManager().declareEnumerationList(tsToAdd.enumTypeName, *enumeratorList);

        return;
    }

    if (tsToAdd.typeDesc->type == SIZELESS_TYPE)  // if type in 'tsToAdd' is just 'signed' or 'unsigned', without a size
    {
        // Apply the signedness of that keyword to 'typeDesc', if the latter is an integral type.
        if (!typeDesc->isIntegral())
        {
            errormsg("signed and unsigned modifiers can only be applied to integral type");
            return;
        }
        if (enumeratorList)
        {
            errormsg("signed and unsigned modifiers cannot be applied to an enum");
            return;
        }
        typeDesc = TranslationUnit::getTypeManager().getIntType(typeDesc, tsToAdd.typeDesc->isSigned);
        return;
    }

    if (typeDesc != tsToAdd.typeDesc)
        errormsg("combining type specifiers is not supported");
}


void
DeclarationSpecifierList::add(Specifier specifier)
{
    switch (specifier)
    {
    case TYPEDEF_SPEC:
        isTypeDef = true;
        break;
    case INTERRUPT_SPEC:
        isISR = true;
        break;
    case ASSEMBLY_ONLY_SPEC:
        asmOnly = true;
        break;
    case EXTERN_SPEC:
        isExtern = true;
        break;
    case STATIC_SPEC:
        isStatic = true;
        break;
    default:
        assert(!"specifier not handled");
    }
}


const TypeDesc *
DeclarationSpecifierList::getTypeDesc() const
{
    TypeManager &tm = TranslationUnit::getTypeManager();

    if (!typeDesc)  // if no type_specifier given
        return tm.getIntType(WORD_TYPE, true);  // sword is default type (as int in C)

    if (typeDesc->type == SIZELESS_TYPE)  // if type described only with 'signed' or 'unsigned', it is a word
        return tm.getIntType(WORD_TYPE, typeDesc->isSigned);

    return typeDesc;
}


bool
DeclarationSpecifierList::isInterruptServiceFunction() const
{
    return isISR;
}


bool
DeclarationSpecifierList::isAssemblyOnly() const
{
    return asmOnly;
}


bool
DeclarationSpecifierList::isTypeDefinition() const
{
    return isTypeDef;
}


bool
DeclarationSpecifierList::isExternDeclaration() const
{
    return isExtern;
}


bool
DeclarationSpecifierList::isStaticDeclaration() const
{
    return isStatic;
}


const string &
DeclarationSpecifierList::getEnumTypeName() const
{
    return enumTypeName;
}


bool
DeclarationSpecifierList::hasEnumeratorList() const
{
    return enumeratorList != NULL;
}


vector<Enumerator *> *
DeclarationSpecifierList::detachEnumeratorList()
{
    vector<Enumerator *> *ret = enumeratorList;
    enumeratorList = NULL;
    return ret;
}


bool
DeclarationSpecifierList::isModifierLegalOnVariable() const
{
    return !isISR && !asmOnly;
}
