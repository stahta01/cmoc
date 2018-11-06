/*  $Id: Declaration.cpp,v 1.38 2016/10/05 02:28:23 sarrazip Exp $

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

#include "Declaration.h"

#include "TranslationUnit.h"
#include "WordConstantExpr.h"
#include "StringLiteralExpr.h"
#include "ClassDef.h"
#include "TreeSequence.h"
#include "ExpressionTypeSetter.h"
#include "VariableExpr.h"
#include "ScopeCreator.h"
#include "SemanticsChecker.h"

#include <assert.h>

using namespace std;

Declaration::Declaration(const string &id, const TypeDesc *td,
                         const vector<uint16_t> &_arrayDimensions,
                         bool isStatic, bool isExtern)
:   Tree(td),
    variableId(id),
    frameDisplacement(0),
    arrayDimensions(_arrayDimensions),
    initializationExpr(NULL),
    label(),
    global(false),
    readOnly(false),
    isStatic(isStatic),
    isExtern(isExtern)
{
}


/*virtual*/
Declaration::~Declaration()
{
    delete initializationExpr;
}


void
Declaration::setInitExpr(Tree *initExpr)
{
    initializationExpr = initExpr;
}


string
Declaration::getVariableId() const
{
    return variableId;
}


// skipFirstDimensionIfArray: If this declaration is an array, do not include the first dimension
//                            in the product of all dimensions. This is useful when the caller
//                            wants the size of the type pointed to.
//
bool
Declaration::getVariableSizeInBytes(uint16_t &sizeInBytes, bool skipFirstDimensionIfArray) const
{
    sizeInBytes = 0;

    if (getType() == ARRAY_TYPE)
    {
        if (arrayDimensions.size() == 0)
            return false;
        uint16_t totalNumElements = 1;
        for (vector<uint16_t>::const_iterator it = arrayDimensions.begin();
                                             it != arrayDimensions.end(); ++it)
        {
            if (skipFirstDimensionIfArray)
            {
                skipFirstDimensionIfArray = false;
                continue;
            }
            uint16_t dim = *it;
            if (dim == 0)
                return false;
            totalNumElements *= dim;
        }

        sizeInBytes = uint16_t(getFinalArrayElementTypeSize()) * totalNumElements;
    }
    else
        sizeInBytes = getTypeSize();

    return sizeInBytes <= 32767;
}


const std::vector<uint16_t> &
Declaration::getArrayDimensions() const
{
    return arrayDimensions;
}


void
Declaration::setFrameDisplacement(int16_t disp)
{
    if (disp >= 0 && disp < 4)  // Caution: This 4 implicitly assumed 16-bit return address and 16-bit saved frame pointer.
        errormsgEx(getLineNo(), "invalid frame displacement %d for variable %s", disp, variableId.c_str());

    frameDisplacement = disp;
}


int16_t
Declaration::getFrameDisplacement(int16_t offset) const
{
    return frameDisplacement + offset;
}


string
Declaration::getFrameDisplacementArg(int16_t offset) const
{
    if (global)
    {
        // "label,Y" under OS-9 (Y is initialized after program_start;
        // see TranslationUnit::emitAssembler()).
        // "label,PCR" under other platforms.
        //
        assert(!label.empty());
        const char *reg = (TranslationUnit::instance().getTargetPlatform() == OS9 ? "Y" : "PCR");
        return label + "+" + wordToString(offset) + "," + reg;
    }

    if (frameDisplacement == 0)
        errormsgEx(getLineNo(), "unallocated variable: %s", variableId.c_str());

    return intToString(getFrameDisplacement(offset)) + ",U";
}


Tree *
Declaration::getInitExpr()
{
    return initializationExpr;
}


void
Declaration::setGlobal(bool g)
{
    global = g;
}


bool
Declaration::isGlobal() const
{
    return global;
}


bool
Declaration::isArray() const
{
    return arrayDimensions.size() > 0;
}


void
Declaration::setReadOnly(bool ro)
{
    readOnly = ro;
}


bool
Declaration::isReadOnly() const
{
    return readOnly;
}


// Also returns true if the initializer is a string literal.
//
bool
Declaration::isArrayWithIntegerInitValues() const
{
    if (!isArray() || initializationExpr == NULL)
        return false;

    if (dynamic_cast<const StringLiteralExpr *>(initializationExpr))
        return true;  // passes for an array of byte integers

    const TreeSequence *seq = dynamic_cast<TreeSequence *>(initializationExpr);
    if (seq == NULL)
        return false;  // not supposed to happen

    return isTreeSequenceWithOnlyIntegerValues(seq);
}


// Recursive check.
//
bool
Declaration::isTreeSequenceWithOnlyIntegerValues(const TreeSequence *seq) const
{
    for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it)
    {
        const Tree *tree = *it;

        if (const TreeSequence *subSeq = dynamic_cast<const TreeSequence *>(tree))
        {
            if (!isTreeSequenceWithOnlyIntegerValues(subSeq))
                return false;
            continue;
        }

        uint16_t value;
        if (!tree->evaluateConstantExpr(value))
            return false;
    }

    return true;
}


void
Declaration::setLabel(const string &_label)
{
    assert(_label.length() > 0);
    label = _label;
}


string
Declaration::getLabel() const
{
    return label;
}


// Also supports string literal initializer.
//
bool
Declaration::emitStaticArrayInitializer(ASMText &out)
{
    assert(getType() == ARRAY_TYPE);

    if (const StringLiteralExpr *sle = dynamic_cast<StringLiteralExpr *>(initializationExpr))
    {
        out.emitLabel(label, getVariableId() + ": " + getTypeDesc()->toString());
        StringLiteralExpr::emitStringLiteralDefinition(out, sle->getLiteral());
        return true;
    }

    const TreeSequence *seq = dynamic_cast<TreeSequence *>(initializationExpr);
    if (seq == NULL)
        return false;

    if (label.empty())
        return false;

    out.emitLabel(label, getVariableId() + ": " + getTypeDesc()->toString());

    for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it)
        if (!emitStaticValues(out, *it, getTypeDesc()->getPointedTypeDesc()))  // pass the array element type
            return false;

    return true;
}


// Emits FCB and FDB directives.
// The initializer value will be in the representation specified by 'requiredTypeDesc'.
//
bool
Declaration::emitStaticValues(ASMText &out, Tree *arrayElementInitializer, const TypeDesc *requiredTypeDesc)
{
    // Try to evaluate arrayElementInitializer as a constant expression.
    //
    uint16_t initValue = 0;
    if (arrayElementInitializer->evaluateConstantExpr(initValue))
    {
        if (arrayElementInitializer->getTypeDesc()->isIntegral()
            && requiredTypeDesc->type != BYTE_TYPE && requiredTypeDesc->type != WORD_TYPE && requiredTypeDesc->type != POINTER_TYPE)
        {
            errormsg("integer value cannot be used to initialize field of type %s", requiredTypeDesc->toString().c_str());
            return false;
        }

        const char *directive = (requiredTypeDesc->type == BYTE_TYPE ? "FCB" : "FDB");

        // Warn if trying to fit a >8 bit value in a byte field.
        //
        if (requiredTypeDesc->type == BYTE_TYPE)
        {
            if (! requiredTypeDesc->isSigned && initValue > 0xFF)
            {
                warnmsg("value %u (0x%x) does not fit in an unsigned character (value will be truncated)", initValue, initValue);
                initValue &= 0xFF;
            }
            else if (requiredTypeDesc->isSigned && (int16_t(initValue) < -128 || int16_t(initValue) > 127))
            {
                warnmsg("value %u (0x%x) does not fit in a signed character (value will be truncated)", initValue, initValue);
                initValue &= 0xFF;
            }
        }

        out.ins(directive, wordToString(initValue, true), "decimal " + wordToString(initValue));
        return true;
    }

    if (StringLiteralExpr *sle = dynamic_cast<StringLiteralExpr *>(arrayElementInitializer))
    {
        if (requiredTypeDesc->type != POINTER_TYPE || requiredTypeDesc->pointedTypeDesc->type != BYTE_TYPE)
            errormsg("string literal must only be used to initialize byte pointer field");

        TranslationUnit::instance().warnNotRelocatable(sle, "using string literal in array initializer");
        out.ins("FDB", sle->getLabel(), sle->getEscapedVersion());
        return true;
    }

    if (TreeSequence *seq = dynamic_cast<TreeSequence *>(arrayElementInitializer))
    {
        // 'seq' must contain one element for each member of the struct or array to initialize.
        //
        if (requiredTypeDesc->type == CLASS_TYPE)
        {
            const ClassDef *cl = TranslationUnit::instance().getClassDef(requiredTypeDesc->className);
            assert(cl);
            if (cl->getNumDataMembers() != seq->size())
            {
                errormsg("wrong number of initializers for struct %s", cl->getClassName().c_str());
                return false;
            }

            size_t memberIndex = 0;
            for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it, ++memberIndex)
            {
                const ClassDef::ClassMember *member = cl->getDataMember(memberIndex);
                assert(member);

                stringstream comment;
                comment << "Element " << size_t(it - seq->begin()) << " of compound initializer: member '"
                        << member->getName() << "' of type " << member->getTypeDesc()->toString();
                out.emitComment(comment.str());
                if (!emitStaticValues(out, *it, member->getTypeDesc()))
                    return false;
            }
            return true;
        }
        if (requiredTypeDesc->type == ARRAY_TYPE)
        {
            const TypeDesc *arrayElemTypeDesc = requiredTypeDesc->getPointedTypeDesc();
            for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it)
            {
                stringstream comment;
                comment << "Element " << size_t(it - seq->begin()) << " of array";
                out.emitComment(comment.str());
                if (!emitStaticValues(out, *it, arrayElemTypeDesc))
                    return false;
            }
            return true;
        }

        errormsg("compound initializer must only be used to initialize a struct");
        return false;
    }

    errormsg("invalid element in initializer for array '%s'", getVariableId().c_str());
    return false;
}


// Register X must point to the current point in the struct or array where to write.
// The initializer value will be in the representation specified by 'requiredTypeDesc'.
//
// numArrayElements: Only used if 'requiredTypeDesc' is of ARRAY_TYPE.
// writingOffset: In/out counter that gets advanced by the number of data bytes
//                affected by the emitted code.
//
bool
Declaration::emitInitCode(ASMText &out, const Tree *initializer, const TypeDesc *requiredTypeDesc, int16_t numArrayElements, uint16_t& writingOffset) const
{
    assert(requiredTypeDesc->isValid());

    if (const TreeSequence *seq = dynamic_cast<const TreeSequence *>(initializer))
    {
        // 'seq' must contain one element for each member of the struct to initialize.
        //
        if (requiredTypeDesc->type == CLASS_TYPE)
        {
            const ClassDef *cl = TranslationUnit::instance().getClassDef(requiredTypeDesc->className);
            assert(cl);
            if (cl->getNumDataMembers() != seq->size())
            {
                errormsg("wrong number of initializers for struct %s", requiredTypeDesc->className.c_str());
                return false;
            }

            size_t memberIndex = 0;
            for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it, ++memberIndex)
            {
                const ClassDef::ClassMember *member = cl->getDataMember(memberIndex);
                assert(member);

                stringstream comment;
                comment << "Element " << size_t(it - seq->begin()) << " of compound initializer: member '"
                        << member->getName() << "' of type " << member->getTypeDesc()->toString();
                out.emitComment(comment.str());
                if (!emitInitCode(out, *it, member->getTypeDesc(), member->getNumArrayElements(), writingOffset))
                    return false;
            }
            return true;
        }
        if (requiredTypeDesc->type == ARRAY_TYPE)
        {
            const TypeDesc *arrayElemTypeDesc = requiredTypeDesc->getPointedTypeDesc();
            for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it)
            {
                stringstream comment;
                comment << "Element " << size_t(it - seq->begin()) << " of array";
                out.emitComment(comment.str());

                if (!emitInitCode(out, *it, arrayElemTypeDesc, 0, writingOffset))
                    return false;
            }
            return true;
        }

        errormsg("compound initializer must only be used to initialize a struct or array");
        return false;
    }

    // Emit single r-value.
    //
    if (const StringLiteralExpr *sle = dynamic_cast<const StringLiteralExpr *>(initializer))
    {
        assert(requiredTypeDesc->type != BYTE_TYPE);

        // If the string literal is used to initalize a byte array, call strncpy().
        // Otherwise, copy the pointer.
        //
        if (requiredTypeDesc->type == ARRAY_TYPE)
        {
            uint16_t elementSizeInBytes = TranslationUnit::instance().getTypeSize(*requiredTypeDesc->pointedTypeDesc);
            assert(elementSizeInBytes > 0);
            uint16_t arraySizeInBytes = numArrayElements * elementSizeInBytes;

            if (requiredTypeDesc->pointedTypeDesc->type != BYTE_TYPE)
            {
                errormsg("initialize non-byte array with string literal");
                return false;
            }

            out.ins("LDD", "#" + wordToString(arraySizeInBytes), "array has " + wordToString(numArrayElements)
                                                                    + " element(s) of " + wordToString(elementSizeInBytes)
                                                                    + " byte(s) each");
            out.ins("PSHS", "B,A", "size argument of strncpy()");
            out.ins("LEAX", sle->getArg(), sle->getEscapedVersion());
            out.ins("PSHS", "X", "source argument of strncpy()");
            out.ins("LEAX", getFrameDisplacementArg(writingOffset), "array to initialize");
            out.ins("PSHS", "X", "destination argument of strncpy()");
            callUtility(out, "strncpy", "copy without overflowing array");
            out.ins("LEAS", "6,S");

            writingOffset += arraySizeInBytes;
        }
        else
        {
            out.ins("LEAX", sle->getArg(), sle->getEscapedVersion());
            out.ins("STX", getFrameDisplacementArg(writingOffset), "offset in variable " + getVariableId());
            writingOffset += 2;
        }
    }
    else
    {
        string storeIns = (requiredTypeDesc->type == BYTE_TYPE ? "STB" : "STD");
        const VariableExpr *ve = initializer->asVariableExpr();
        if (ve != NULL && initializer->getType() == ARRAY_TYPE)
        {
            out.ins("LEAX", ve->getFrameDisplacementArg(), "address of array " + ve->getId());
            storeIns = "STX";
        }
        else if (!initializer->emitCode(out, false))
            return false;

        if (initializer->getType() == BYTE_TYPE && requiredTypeDesc->type != BYTE_TYPE)
            out.ins("CLRA", "", "initializer of type byte, but field is 16 bits");

        out.ins(storeIns, getFrameDisplacementArg(writingOffset), "offset in variable " + getVariableId());
        writingOffset += (requiredTypeDesc->type == BYTE_TYPE ? 1 : 2);
    }

    return true;
}


/*virtual*/
void
Declaration::checkSemantics(Functor &f)
{
    // If this declaration is global, use a ScopeCreator to register it in the
    // global space and to set the declaration of each variable expression in
    // any initialization expression.
    // If this declaration is local, nothing is done here because the ScopeCreator
    // is created and used by FunctionDef::checkSemantics(), which will end up here.
    //
    if (global)
    {
        TranslationUnit &translationUnit = TranslationUnit::instance();
        ScopeCreator sc(translationUnit, &translationUnit.getGlobalScope());
        iterate(sc);

        // Also set the expression type in the initializer. For local declarations,
        // this is done when the semantics checker is called on the function definition.
        //
        if (initializationExpr != NULL)
        {
            ExpressionTypeSetter ets;
            initializationExpr->iterate(ets);
        }
    }
    else if (isStatic)
    {
        SemanticsChecker &checker = dynamic_cast<SemanticsChecker &>(f);
        const FunctionDef *parentFunctionDef = checker.getCurrentFunctionDef();
        if (parentFunctionDef)  // if declaration is local to a function
            errormsg("local static variables are not supported");
    }

    if (initializationExpr != NULL)
    {
        checkInitExpr(initializationExpr, getTypeDesc(), variableId, arrayDimensions, 0);
    }
}


void
Declaration::checkInitExpr(Tree *initializationExpr, const TypeDesc *varTypeDesc, const string &variableId, const vector<uint16_t> &arrayDimensions, size_t dimIndex)
{
    //cerr << "# Declaration::checkInitExpr(_, '" << varTypeDesc->toString() << "', " << variableId << ", {" << join(", ", arrayDimensions) << "}, " << dimIndex << ")\n";
    assert(initializationExpr);
    assert(varTypeDesc);
    assert(!variableId.empty());

    BasicType varType = varTypeDesc->type;

    BasicType initExprType = initializationExpr->getType();

    uint16_t value = 0;
    bool initExprIsConst = initializationExpr->evaluateConstantExpr(value);

    if (varType == WORD_TYPE && initExprType == BYTE_TYPE)
        ;
    else if (varType == BYTE_TYPE && initExprType == BYTE_TYPE)
        ;  // do not care about signedness
    else if (varType == WORD_TYPE && initExprType == WORD_TYPE)
        ; // do not care about signedness
    else if (varType == POINTER_TYPE && (initExprType == WORD_TYPE || initExprType == BYTE_TYPE))
    {
        if (! initExprIsConst)  // if not constant
            initializationExpr->warnmsg("initializing pointer '%s' from integer expression", variableId.c_str());
        else if (value >= 0x8000 && initializationExpr->getTypeDesc()->isSigned)
            initializationExpr->warnmsg("initializing pointer '%s' from negative constant", variableId.c_str());
    }
    else if (varType == POINTER_TYPE && initExprType == ARRAY_TYPE)
    {
        const TypeDesc *declPointedTypeDesc = varTypeDesc->getPointedTypeDesc();
        const TypeDesc *initPointedTypeDesc = initializationExpr->getTypeDesc()->getPointedTypeDesc();

        if (*declPointedTypeDesc != *initPointedTypeDesc)
            initializationExpr->warnmsg("initializing pointer to %s '%s' from incompatible %s",
                    declPointedTypeDesc->toString().c_str(),
                    variableId.c_str(),
                    initializationExpr->getTypeDesc()->toString().c_str());
    }
    else if (varType == ARRAY_TYPE)
        checkArrayInitializer(initializationExpr, varTypeDesc, variableId, arrayDimensions, dimIndex);
    else if (varType == BYTE_TYPE && initExprType == WORD_TYPE)
    {
        if (!initializationExpr->is8BitConstant())
            initializationExpr->errormsg("initializing byte variable with word value");
    }
    else if (varType == CLASS_TYPE)
        checkClassInitializer(initializationExpr, varTypeDesc, variableId);
    else if (*varTypeDesc != *initializationExpr->getTypeDesc())
    {
        string varTypeName = varTypeDesc->toString();
        string initExprTypeName = initializationExpr->getTypeDesc()->toString();
        initializationExpr->errormsg("initializing %s with expression of type %s",
                                     varTypeName.c_str(),
                                     initExprTypeName.c_str());
    }
}

// This Declaration must be of ARRAY_TYPE.
// initializationExpr must be of type TreeSequence *.
// Checks the number of elements in that sequence. Issues a warning or error
// if it is not equal to the size of the array.
// Checks that the type of each element of initializationExpr is compatible
// with the array element type.
//
void
Declaration::checkArrayInitializer(Tree *initializationExpr, const TypeDesc *varTypeDesc, const string &variableId, const vector<uint16_t> &arrayDimensions, size_t dimIndex)
{
    assert(initializationExpr != NULL);
    assert(varTypeDesc);
    assert(varTypeDesc->type == ARRAY_TYPE);
    assert(!variableId.empty());

    TreeSequence *seq = dynamic_cast<TreeSequence *>(initializationExpr);
    if (seq != NULL)
    {
        // Check that initializationExpr is not too long. Warn if too short.
        //
        assert(dimIndex < arrayDimensions.size());
        uint16_t numArrayElements = arrayDimensions[dimIndex];
        if (seq->size() > size_t(numArrayElements))
        {
            initializationExpr->errormsg("too many elements (%u) in initializer for array of %hu element(s)",
                                        seq->size(), numArrayElements);
            return;
        }
        if (seq->size() < size_t(numArrayElements))
        {
            initializationExpr->warnmsg("only %u element(s) in initializer for array of %hu element(s)",
                                        seq->size(), numArrayElements);
        }

        for (vector<Tree *>::const_iterator it = seq->begin(); it != seq->end(); ++it)
            checkInitExpr(*it, varTypeDesc->pointedTypeDesc, variableId, arrayDimensions, dimIndex + 1);
    }
    else  // initializer is not a sequence:
    {
        // Require that the variable to initialize be a byte array and that the initializer be one too.
        //
        if (varTypeDesc->getPointedType() != BYTE_TYPE
            || ! initializationExpr->getTypeDesc()->isPtrOrArray()
            || initializationExpr->getTypeDesc()->getPointedType() != BYTE_TYPE)
        {
            initializationExpr->errormsg("initializer for array `%s' is invalid", variableId.c_str());
        }
    }
}

// This Declaration must be of CLASS_TYPE.
// initializationExpr must be of type TreeSequence *.
// Checks that the number of values in the sequence is equal to the number
// of members in the class.
//
void
Declaration::checkClassInitializer(Tree *initializationExpr, const TypeDesc *varTypeDesc, const string &variableId)
{
    assert(initializationExpr != NULL);
    assert(varTypeDesc);
    assert(varTypeDesc->type == CLASS_TYPE);
    assert(!variableId.empty());

    const string &className = varTypeDesc->className;

    TreeSequence *seq = dynamic_cast<TreeSequence *>(initializationExpr);
    if (seq == NULL && initializationExpr->getTypeDesc() != varTypeDesc
                    && ! isFloatOrLongInitWithNumber(varTypeDesc, *initializationExpr))
    {
        initializationExpr->errormsg("initializer for struct %s is of type `%s': must be list, or struct of same type",
                                     className.c_str(), initializationExpr->getTypeDesc()->toString().c_str());
        return;
    }

    if (seq)
    {
        const ClassDef *cl = TranslationUnit::instance().getClassDef(className);
        assert(cl);

        if (seq->size() != cl->getNumDataMembers())
        {
            seq->errormsg("initializing struct %s, which has %u member(s), with initializer containing %u value(s)",
                          className.c_str(), cl->getNumDataMembers(), seq->size());
            return;
        }


        size_t memberIndex = 0;
        for (std::vector<Tree *>::const_iterator initExprIt = seq->begin(); initExprIt != seq->end(); ++initExprIt, ++memberIndex)
        {
            const ClassDef::ClassMember *member = cl->getDataMember(memberIndex);
            checkInitExpr(*initExprIt, member->getTypeDesc(), variableId, member->getArrayDimensions(), 0);
        }
    }
}


bool
Declaration::isFloatOrLongInitWithNumber(const TypeDesc *varTypeDesc, const Tree &initializationExpr)
{
    return (varTypeDesc->isLong() || varTypeDesc->isFloat())
           && initializationExpr.getTypeDesc()->isNumerical();
}


/*virtual*/
CodeStatus
Declaration::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    if (initializationExpr != NULL)
    {
        writeLineNoComment(out, "init of variable " + variableId);

        const TypeDesc *declTD = getTypeDesc();
        const WordConstantExpr *wce = dynamic_cast<const WordConstantExpr *>(initializationExpr);
        const StringLiteralExpr *sle = dynamic_cast<const StringLiteralExpr *>(initializationExpr);

        if (wce != NULL && wce->getWordValue() == 0 && getType() == BYTE_TYPE)
            out.ins("CLR", getFrameDisplacementArg(), "variable " + variableId);
        else if (const TreeSequence *seq = dynamic_cast<const TreeSequence *>(initializationExpr))
        {
            uint16_t writingOffset = 0;
            uint16_t numArrayElements = (arrayDimensions.size() > 0 ? arrayDimensions.front() : 1);
            if (!emitInitCode(out, seq, declTD, numArrayElements, writingOffset))
                return false;
        }
        else if (getType() == ARRAY_TYPE && sle)  // if char[] init by string literal
        {
            // Emit a call to memcpy() that reads from the string literal
            // and writes to the array address.
            //
            out.ins("LDD", "#" + wordToString(sle->getLiteral().length() + 1), "length of string literal + terminating NUL");
            out.ins("PSHS", "B,A", "push length to _memcpy");
            out.ins("LEAX", sle->getArg(), sle->getEscapedVersion());
            out.ins("PSHS", "X", "source array");
            out.ins("LEAX", getFrameDisplacementArg(), "byte array " + variableId);
            out.ins("PSHS", "X", "destination array");
            out.ins("LBSR", "_memcpy", "initialize array");
            TranslationUnit::instance().registerNeededUtility("memcpy");  // define _CMOC_NEED_memcpy_ re: stdlib.inc
            out.ins("LEAS", "6,S");
            return true;
        }
        else if (initializationExpr->getType() == CLASS_TYPE)  // if struct initialized from other struct
        {
            assert(declTD == initializationExpr->getTypeDesc());

            if (!initializationExpr->emitCode(out, true))  // get address of other struct in X
                return false;

            int16_t structSizeInBytes = TranslationUnit::instance().getTypeSize(*declTD);
            out.ins("LDD", "#" + wordToString(structSizeInBytes), "size of struct " + declTD->className);
            out.ins("PSHS", "B,A", "push size to _memcpy");
            out.ins("PSHS", "X", "source struct");
            out.ins("LEAX", getFrameDisplacementArg(), "destination struct: " + variableId);
            out.ins("PSHS", "X");
            out.ins("LBSR", "_memcpy", "initialize struct");
            TranslationUnit::instance().registerNeededUtility("memcpy");  // define _CMOC_NEED_memcpy_ re: stdlib.inc
            out.ins("LEAS", "6,S");
        }
        else
        {
            uint16_t val = 0;
            if (initializationExpr->evaluateConstantExpr(val))
            {
                if (getType() == BYTE_TYPE)
                {
                    val &= 0xFF;
                    if (val == 0)
                        out.ins("CLRB");
                    else
                        out.ins("LDB", "#" + wordToString(val, true), wordToString(val, false));
                }
                else if (val == 0)
                {
                    out.ins("CLRA");
                    out.ins("CLRB");
                }
                else
                {
                    out.ins("LDD", "#" + wordToString(val, true), wordToString(val, false));
                }
            }
            else
            {
                if (!initializationExpr->emitCode(out, false))
                    return false;

                // If initializing word from byte expression, make sure MSB is 0.
                if (getType() != BYTE_TYPE && initializationExpr->getType() == BYTE_TYPE)
                    out.ins("CLRA");
            }

            if (declTD->isFloat())
            {
                out.ins("LEAX", getFrameDisplacementArg(), "address of variable " + variableId);
                const char *utility = NULL;
                if (     declTD->isSingle() && ! initializationExpr->isSigned())
                    utility = "initSingleFromUWord";
                else if (declTD->isSingle() &&   initializationExpr->isSigned())
                    utility = "initSingleFromSWord";
                else if (declTD->isDouble() && ! initializationExpr->isSigned())
                    utility = "initDoubleFromUWord";
                else if (declTD->isDouble() &&   initializationExpr->isSigned())
                    utility = "initDoubleFromSWord";
                callUtility(out, utility);
            }
            else
            {
                string store = getStoreInstruction(getType());
                if (store.empty())
                {
                    assert(!"unknown type");
                    return false;
                }

                out.ins(store, getFrameDisplacementArg(), "variable " + variableId);
            }
        }
    }
    return true;
}


bool
Declaration::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (initializationExpr != NULL && !initializationExpr->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}
