/*  $Id: Declarator.cpp,v 1.19 2016/10/11 01:34:50 sarrazip Exp $

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

#include "Declarator.h"

#include "Declaration.h"
#include "TreeSequence.h"
#include "StringLiteralExpr.h"
#include "ExpressionTypeSetter.h"
#include "TranslationUnit.h"
#include "FormalParameter.h"
#include "FormalParamList.h"
#include "DeclarationSpecifierList.h"

using namespace std;


Declarator::Declarator(const std::string &_id,
                       const std::string &_srcFilename, int _lineno)
  : id(_id),
    srcFilename(_srcFilename),
    lineno(_lineno),
    initExpr(NULL),
    arraySizeExprList(),
    formalParamList(NULL),
    type(SINGLETON),
    pointerLevel(0)
{
}


Declarator::~Declarator()
{
    delete initExpr;

    for (vector<Tree *>::iterator it = arraySizeExprList.begin(); it != arraySizeExprList.end(); ++it)
        delete *it;
}


void
Declarator::setInitExpr(Tree *_initExpr)
{
    assert(!initExpr);
    initExpr = _initExpr;
}


// Adds a dimension to this declarator.
// (Can be called more than once.)
// _arraySizeExpr may be null: it means no size specified, as in v[].
// However, only the first dimension can be null, as in v[][5][7].
// Sets 'type' to ARRAY, even if _arraySizeExpr is null.
//
// NOTE: The Tree becomes owned by this object. It will be destroyed by ~Declarator().
//
void
Declarator::addArraySizeExpr(Tree *_arraySizeExpr)
{
    assert(!formalParamList);
    arraySizeExprList.push_back(_arraySizeExpr);
    assert(type == SINGLETON || type == ARRAY);
    type = ARRAY;
}


FormalParamList *
Declarator::getFormalParamList() const
{
    return formalParamList;
}


void
Declarator::setFormalParamList(FormalParamList *_formalParamList)
{
    assert(type == SINGLETON);
    assert(!formalParamList);
    formalParamList = _formalParamList;
}


// Returns a Declaration object allocated by 'new'.
// This Declarator does not own the Declaration object:
// the destruction is the responsibility of the caller.
//
// The ownership of initExpr is transferred to this Declaration object.
// This Declarator object loses its initialization expression.
//
// Upon error, sends an error message and returns NULL.
//
Declaration *
Declarator::declareVariable(const TypeDesc *varType, bool isStatic, bool isExtern)
{
    assert(!formalParamList);

    if (id.empty())
        return NULL;

    vector<uint16_t> arrayDimensions;

    // arrayDimensions will contain dimensions from varType as well as from this declarator.
    // Example: typedef char A[10]; A v[5];
    // varType is A, which is char[10], and this declarator contains dimension 5.
    // We start arrayDimensions with the 5, because the type of v is as if v had been
    // declared as char v[5][10].

    if (!computeArrayDimensions(arrayDimensions))
        return NULL;

    size_t numDimsDueToDeclarator = arrayDimensions.size();

    if (varType->type == ARRAY_TYPE)
    {
        // varType may contain dimensions, if the variable is being declared using
        // a typedef of an array, e.g.,
        //   typedef A a[2][3];
        //   A someVar;
        // Then varType->appendDimensions() will put 2 and 3 in arrayDimensions.
        // In the case of
        //   A someArray[4][5];
        // then the 4 and 5 are stored in this Declarator, and it is the call to computeArraySize()
        // that will have inserted 4 and 5 in arrayDimensions.
        //
        varType->appendDimensions(arrayDimensions);
    }

    // Here, arrayDimensions is empty if non-array.

    //cerr << "# Declarator::declareVariable: arrayDimensions={" << join(", ", arrayDimensions) << "}\n";

    const TypeDesc *td = TranslationUnit::getTypeManager().getArrayOf(varType, numDimsDueToDeclarator);

    //cerr << "# Declarator::declareVariable: td='" << td->toString() << "'\n";

    Declaration *decl = new Declaration(id, td, arrayDimensions, isStatic, isExtern);

    decl->setInitExpr(initExpr);  // ownership of initExpr transferred to decl
    initExpr = NULL;

    decl->setLineNo(srcFilename, lineno);
    return decl;
}


bool
Declarator::getNumDimensions(size_t &numDimensions) const
{
    numDimensions = 0;

    vector<uint16_t> arrayDimensions;
    if (!computeArrayDimensions(arrayDimensions))
        return false;

    numDimensions = arrayDimensions.size();
    return true;
}


// Upon success, returns the size of each dimension of the array.
// Does not return any dimension for a non-array declaration.
//
// Displays an error message upon failure.
//
// arrayDimensions: NOT cleared before elements are added, if any.
// allowUnknownFirstDimension: if true, this unknown 1st dimension is assumed to be 1.
//
bool
Declarator::computeArrayDimensions(vector<uint16_t> &arrayDimensions,
                                   bool allowUnknownFirstDimension) const
{
    assert(!formalParamList);

    if (type != ARRAY)
        return true;  // success

    if (arraySizeExprList.size() == 0)
    {
        errormsg("array %s: no dimensions", id.c_str());
        return false;
    }

    // Check that only the first dimension is unspecified, if any.
    //
    for (vector<Tree *>::const_iterator it = arraySizeExprList.begin(); it != arraySizeExprList.end(); ++it)
        if (*it == NULL && it != arraySizeExprList.begin())
        {
            errormsg("array %s: dimension other than first one is unspecified", id.c_str());
            return false;
        }

    if (arraySizeExprList.front() == NULL)  // if no size in [] for 1st dimension, use # of elements in init list
    {
        if (initExpr != NULL)
        {
            size_t len = 0;
            if (const TreeSequence *ts = dynamic_cast<const TreeSequence *>(initExpr))
                len = ts->size();
            else if (const StringLiteralExpr *sle = dynamic_cast<const StringLiteralExpr *>(initExpr))
                len = sle->getLiteral().length() + 1;  // include terminaing '\0'
            else
            {
                errormsg("unexpected type of array initializer");
                return false;
            }
            if (len > 0xFFFF)
            {
                errormsg("array initializer too long");
                return false;
            }
            arrayDimensions.push_back(uint16_t(len));
        }
        else if (!allowUnknownFirstDimension)
        {
            errormsg("array %s: no size of first dimension, no initialization expression", id.c_str());  // should have been detected by parser.yy
            return false;
        }
    }

    for (vector<Tree *>::const_iterator it = arraySizeExprList.begin(); it != arraySizeExprList.end(); ++it)
    {
        Tree *arraySizeExpr = *it;
        if (arraySizeExpr == NULL)
        {
            if (initExpr == NULL)
                arrayDimensions.push_back(1);
            continue;
        }

        try
        {
            // Set the expression type for evaluateConstantExpr().
            //
            ExpressionTypeSetter ets;
            arraySizeExpr->iterate(ets);

            if (arraySizeExpr->getTypeDesc()->isPtrOrArray())
            {
                errormsg("pointer or array expression used for size of array '%s'", id.c_str());
                return false;
            }
            uint16_t value;
            if (!arraySizeExpr->evaluateConstantExpr(value))
            {
                size_t dim = it - arraySizeExprList.begin() + 1;
                errormsg("invalid size expression for dimension %u array '%s'", dim, id.c_str());
                return false;
            }
            arrayDimensions.push_back(value);
        }
        catch (...)
        {
            errormsg("unexpected exception caught in Declarator::computeArraySize() for '%s'", id.c_str());
            return false;
        }
    }

    return true;
}


const string &
Declarator::getId() const
{
    return id;
}


uint16_t
Declarator::getNumArrayElements() const
{
    assert(!formalParamList);

    vector<uint16_t> arrayDimensions;
    if (!computeArrayDimensions(arrayDimensions))  // arrayDimensions will be empty if non-array
        return 0;
    if (arrayDimensions.size() == 0)
        return 0;

    uint16_t product = 1;
    for (vector<uint16_t>::const_iterator it = arrayDimensions.begin(); it != arrayDimensions.end(); ++it)
        product *= *it;
    return product;
}


// Applies the pointer level to 'td' and returns the resulting type.
//
const TypeDesc *
Declarator::processPointerLevel(const TypeDesc *td) const
{
    assert(td);
    TypeManager &tm = TranslationUnit::getTypeManager();
    for (size_t i = 0; i < pointerLevel; ++i)
        td = tm.getPointerTo(td);
    assert(td);
    return td;
}


// Returns an object allocated with 'new'.
//
FormalParameter *
Declarator::createFormalParameter(DeclarationSpecifierList &dsl) const
{
    if (dsl.hasEnumeratorList())
    {
        errormsg("enum with enumerated names is not supported in a function's formal parameter");
        delete dsl.detachEnumeratorList();  // won't be needed
    }

    const TypeDesc *td = dsl.getTypeDesc();

    if (! isFunctionPointer())
        td = processPointerLevel(td);

    assert(initExpr == NULL);  // no initialization expression for formal parameter
    vector<uint16_t> arrayDimensions;  // empty means not an array
    if (isArray())
    {
        TypeManager &tm = TranslationUnit::getTypeManager();
        if (!computeArrayDimensions(arrayDimensions, true))  // arrayDimensions will be empty if non-array
            return NULL;
        if (arrayDimensions.size() > 1)
            td = tm.getArrayOf(td, arrayDimensions.size() - 1);
        td = tm.getPointerTo(td);
    }
    else if (isFunctionPointer())
    {
        td = TranslationUnit::getTypeManager().getFunctionPointerType();
    }
    return new FormalParameter(td, id, arrayDimensions, dsl.getEnumTypeName());
}


string
Declarator::toString() const
{
    stringstream ss;
    ss << "Declarator(id '" << id << "' at " << srcFilename << ":" << lineno;
    if (initExpr)
       ss << ", with init expr";
    if (type == ARRAY)
        ss << ", array with " << arraySizeExprList.size() << " size expression(s)";
    else if (type == FUNCPTR)
        ss << ", function pointer";
    ss << ", pointer level " << pointerLevel;
    if (formalParamList)
        ss << ", with formal param list";
    ss << ")";
    return ss.str();
}
