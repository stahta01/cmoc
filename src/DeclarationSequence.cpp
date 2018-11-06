/*  $Id: DeclarationSequence.cpp,v 1.9 2016/08/27 00:53:50 sarrazip Exp $

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

#include "DeclarationSequence.h"
#include "TranslationUnit.h"
#include "SemanticsChecker.h"

using namespace std;


DeclarationSequence::DeclarationSequence(const TypeDesc *_typeDesc, std::vector<Enumerator *> *_enumeratorList)
:   TreeSequence(),
    enumeratorList(_enumeratorList)
{
    assert(_typeDesc);
    assert(_typeDesc->isValid());
    setTypeDesc(_typeDesc);
}


DeclarationSequence::~DeclarationSequence()
{
    delete enumeratorList;

    // We do not delete the Enumerators and the Trees b/c they are owned
    // by the TypeManager (see TypeManager::declareEnumerationList()).
}


void DeclarationSequence::processDeclarator(Declarator *declarator, const DeclarationSpecifierList &dsl)
{
    if (declarator == NULL)
        return;
    const TypeDesc *specificTypeDesc = getTypeDesc();

    // Apply asterisks specified in the Declarator, unless the declarator
    // declares a function pointer.
    // For example: if the declaration is of type char **, then getTypeDesc()
    // returned type "char", and declarator->pointerLevel == 2.
    // After the call to processPointerLevel(), specificTypeDesc will be "char **".
    //
    if (! declarator->isFunctionPointer())
        specificTypeDesc = declarator->processPointerLevel(specificTypeDesc);

    //cout << "# DeclarationSequence::processDeclarator: specificTypeDesc='" << *specificTypeDesc
    //     << "', " << declarator->getId() << "\n";

    if (declarator->getFormalParamList() != NULL)  // if function prototype
    {
        FunctionDef *fd = new FunctionDef(dsl, *declarator);
        fd->setLineNo(declarator->getSourceFilename(), declarator->getLineNo());
        // Body of 'fd' is left null.
        addTree(fd);
    }
    else
    {
        if (! dsl.isModifierLegalOnVariable())
            errormsg("illegal modifier used on declaration of variable `%s'", declarator->getId().c_str());

        const TypeDesc *typeDesc = (declarator->isFunctionPointer()
                                    ? TranslationUnit::getTypeManager().getFunctionPointerType()
                                    : specificTypeDesc);

        Declaration *decl = declarator->declareVariable(typeDesc, dsl.isStaticDeclaration(), dsl.isExternDeclaration());

        if (decl)
            addTree(decl);
    }
    delete declarator;
}


void
DeclarationSequence::checkSemantics(Functor &f)
{
    if (!enumeratorList)
        return;

    const SemanticsChecker &sc = dynamic_cast<SemanticsChecker &>(f);
    if (sc.getCurrentFunctionDef() != NULL)
        errormsg("non-global enum not supported");
}
