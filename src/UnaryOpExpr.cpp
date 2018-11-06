/*  $Id: UnaryOpExpr.cpp,v 1.26 2016/10/15 04:10:19 sarrazip Exp $

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

#include "UnaryOpExpr.h"

#include "TranslationUnit.h"
#include "VariableExpr.h"
#include "WordConstantExpr.h"
#include "VariableExpr.h"
#include "ObjectMemberExpr.h"
#include "BinaryOpExpr.h"
#include "IdentifierExpr.h"
#include "CastExpr.h"
#include "Declaration.h"
#include "StringLiteralExpr.h"

#include <assert.h>

using namespace std;


const char *
UnaryOpExpr::getOperatorName(Op op)
{
    switch (op)
    {
    case IDENTITY: return "identity";
    case NEG: return "arithmetic negation";
    case POSTINC: return "post-increment";
    case POSTDEC: return "post-decrement";
    case PREINC: return "pre-increment";
    case PREDEC: return "pre-decrement";
    case ADDRESS_OF: return "address-of";
    case INDIRECTION: return "indirection";
    case BOOLEAN_NEG: return "boolean negation";
    case BITWISE_NOT: return "bitwise not";
    case SIZE_OF: return "sizeof";
    default: return "<UNKNOWN UNARY OPERATOR>";
    }
}

UnaryOpExpr::UnaryOpExpr(Op op, Tree *e)
  : Tree(),
    oper(op),
    dereferencingVoidAllowed(false),
    subExpr(e),
    sizeofArgTypeDesc(NULL)  // will be determined by checkSemantics()
{
    assert(subExpr != NULL);
}


UnaryOpExpr::UnaryOpExpr(const TypeDesc *_typeDesc)
  : Tree(),
    oper(SIZE_OF),
    dereferencingVoidAllowed(false),
    subExpr(NULL),
    sizeofArgTypeDesc(_typeDesc)
{
}


/*virtual*/
UnaryOpExpr::~UnaryOpExpr()
{
    delete subExpr;
}


UnaryOpExpr::Op UnaryOpExpr::getOperator() const
{
    return oper;
}


const Tree *
UnaryOpExpr::getSubExpr() const
{
    return subExpr;
}


Tree *
UnaryOpExpr::getSubExpr()
{
    return subExpr;
}


void
UnaryOpExpr::checkSemantics(Functor & /*f*/)
{
    bool requireLValueSubExpr = false;

    switch (oper)
    {
        case ADDRESS_OF:
            assert(subExpr != NULL);
            requireLValueSubExpr = true;
            break;

        case INDIRECTION:
            assert(subExpr != NULL);
            if (subExpr->getType() == POINTER_TYPE || subExpr->getType() == ARRAY_TYPE)
            {
                if (subExpr->getTypeDesc()->pointedTypeDesc->type == VOID_TYPE && !dereferencingVoidAllowed)
                    errormsg("indirection of a pointer to void");
            }
            else if (subExpr->getType() == BYTE_TYPE || subExpr->getType() == WORD_TYPE)
                ;  // already warned about this in ExpressionTypeSetter::processUnaryOp
            else
                errormsg("indirection of a non-pointer");
            break;

        case SIZE_OF:
            if (!sizeofArgTypeDesc)  // should have been set by ctor, or by ExpressionTypeSetter calling setSizeofArgTypeDesc()
                errormsg("sizeof argument is invalid");
            else if (sizeofArgTypeDesc->type == VOID_TYPE)
                errormsg("cannot take sizeof(void)");
            break;

        case PREINC:
        case PREDEC:
        case POSTINC:
        case POSTDEC:
            requireLValueSubExpr = true;
            if (subExpr->getType() == ARRAY_TYPE)
                errormsg("cannot %screment array name", (oper == PREINC || oper == POSTINC ? "in" : "de"));
            break;

        case NEG:
            if (subExpr->getType() == ARRAY_TYPE)
                errormsg("cannot use minus operator on array name");
            break;

        case BITWISE_NOT:
            if (subExpr->getType() == ARRAY_TYPE)
                errormsg("cannot do bitwise negation on array name");
            break;

        default:
            ;
    }

    if (requireLValueSubExpr && !subExpr->isLValue())
    {
        errormsg("lvalue required as operand of %s", getOperatorName(oper));
    }
}


// Determines if 'tree', which must be the argument of an indirection operator,
// is of the form var++, where 'var' is a pointer to a byte or word.
// Returns the VariableExpr if true, NULL otherwise.
//
const VariableExpr *
UnaryOpExpr::isPostIncOfPtrToSmallType(const Tree &tree)
{
    const UnaryOpExpr *unary = dynamic_cast<const UnaryOpExpr *>(&tree);
    if (!unary)
        return NULL;
    if (unary->getOperator() != POSTINC)
        return NULL;
    const VariableExpr *ve = unary->getSubExpr()->asVariableExpr();
    if (!ve)
        return NULL;
    if (ve->getType() != POINTER_TYPE)
        return NULL;
    const TypeDesc *pointedTD = ve->getTypeDesc()->getPointedTypeDesc();
    int16_t sizeInBytes = TranslationUnit::instance().getTypeSize(*pointedTD);
    return sizeInBytes <= 2 ? ve : NULL;
}


static const BinaryOpExpr *
isArrayRef(const Tree *expr)
{
    const BinaryOpExpr *bin = dynamic_cast<const BinaryOpExpr *>(expr);
    if (bin == NULL)
        return NULL;
    if (bin->getOperator() == BinaryOpExpr::ARRAY_REF)
        return bin;
    return NULL;
}


void
UnaryOpExpr::setSizeofArgTypeDesc()
{
    assert(oper == SIZE_OF);

    if (subExpr != NULL && sizeofArgTypeDesc == NULL)  // if sizeof unary_expr instead of sizeof(type)
    {
        sizeofArgTypeDesc = subExpr->getTypeDesc();
        assert(sizeofArgTypeDesc != NULL);

        // At this point, if the argument is invalid (e.g., an unknown variable name),
        // then sizeofArgTypeDesc->type is VOID_TYPE. We assume that an error message
        // has already been issued about the invalid argument.

        if (sizeofArgTypeDesc->type == ARRAY_TYPE
                && (! subExpr->asVariableExpr()
                   && ! dynamic_cast<ObjectMemberExpr *>(subExpr)
                   && ! dynamic_cast<StringLiteralExpr *>(subExpr)
                   && ! isArrayRef(subExpr)))
            errormsg("taking size of array expression that is not an array name nor a struct member");
    }

    assert(sizeofArgTypeDesc != NULL);
}


void
UnaryOpExpr::checkForSizeOfUnknownStruct()
{
    if (oper != SIZE_OF || subExpr != NULL)
        return;

    assert(sizeofArgTypeDesc);  // should have been set by setSizeofArgTypeDesc()

    if (sizeofArgTypeDesc->type != CLASS_TYPE)
        return;
    if (TranslationUnit::instance().getClassDef(sizeofArgTypeDesc->className) != NULL)
        return;

    errormsg("cannot take sizeof unknown struct or union '%s'", sizeofArgTypeDesc->className.c_str());
}


bool
UnaryOpExpr::getSizeOfValue(uint16_t &size) const
{
    size = 0;  // ensure defined value
    assert(sizeofArgTypeDesc != NULL);  // should have been set by a ctor or by checkSemantics()

    if (subExpr == NULL || (sizeofArgTypeDesc && sizeofArgTypeDesc->type != ARRAY_TYPE))
    {
        if (sizeofArgTypeDesc->type == CLASS_TYPE && TranslationUnit::instance().getClassDef(sizeofArgTypeDesc->className) == NULL)
            return false;  // error msg already emitted by checkForSizeOfUnknownStruct()

        size = TranslationUnit::instance().getTypeSize(*sizeofArgTypeDesc);
        return true;
    }

    if (const VariableExpr *ve = subExpr->asVariableExpr())
    {
        if (!ve->getDeclaration()->getVariableSizeInBytes(size))
        {
            errormsg("invalid dimensions for array %s", ve->getId().c_str());
            return false;
        }
        return true;
    }

    if (const ObjectMemberExpr *obj = dynamic_cast<const ObjectMemberExpr *>(subExpr))
    {
        const ClassDef *cl = obj->getClass();
        if (cl == NULL)
        {
            errormsg("taking size of undefined class %s", obj->getClassName().c_str());
            return false;
        }
        const ClassDef::ClassMember *member = cl->getDataMember(obj->getMemberName());
        if (member == NULL)
        {
            errormsg("taking size of undefined member %s oF %s", obj->getMemberName().c_str(), obj->getClassName().c_str());
            return false;
        }
        size = member->getSizeInBytes();
        return true;
    }

    if (const BinaryOpExpr *bin = isArrayRef(subExpr))
    {
        // We have sizeof(a[0]) or sizeof(a[0][0]), etc.
        // (The actual indices do not matter.)
        // Count the number of [] in a[0][0]...[0] until we get to 'a'.
        //
        size_t numDimsInSizeof = 0;
        const VariableExpr *ve = NULL;
        const ObjectMemberExpr *ome = NULL;
        const Tree *left = NULL;
        do
        {
            ++numDimsInSizeof;
            left = bin->getLeft();
            assert(left != NULL);
            ve = left->asVariableExpr();
            ome = dynamic_cast<const ObjectMemberExpr *>(left);
            if (ve != NULL || ome != NULL)
                break;
        } while ((bin = isArrayRef(left)) != NULL);

        if (ve != NULL)  // if reached a variable
        {
            // Get the dimensions of the array.
            // Example: if the array is int [5][3][4], we want { 5, 3, 4 }.
            //
            const Declaration *decl = ve->getDeclaration();
            assert(decl != NULL);
            const std::vector<uint16_t> &arrayDims = decl->getArrayDimensions();
            if (numDimsInSizeof > arrayDims.size())
            {
                errormsg("sizeof() argument uses more indices (%u) than the array accepts (%u)",
                        unsigned(numDimsInSizeof), unsigned(arrayDims.size()));
                return false;
            }

            // The number of array elements to be counted by sizeof() is the product
            // of the array dimensions except those reprensented by the indices used
            // in the sizeof() argument.
            // Example: If 'a' is a 4-dimension array, then for sizeof(a[0]) we compute
            // the product of the *last* 3 dimensions.
            // If the number of indices is equal to the number of array dimensions,
            // we take the size of the final array element.
            //
            size = ve->getFinalArrayElementTypeSize();  // initialize product with size in bytes of final array element
            for (size_t index = numDimsInSizeof; index < arrayDims.size(); ++index)
            {
                uint16_t dim = arrayDims[index]; //*it;
                if (size > 0xFFFF / dim)  // test if size * dim is too large, without overflowing in the test itself
                {
                    errormsg("sizeof() value not representable in 16 bits");
                    return false;
                }
                size *= dim;
            }
            return true;
        }

        if (ome != NULL)  // if reached a struct member access
        {
            const ClassDef::ClassMember *member = ome->getClassMember();
            if (!member)
                return true;  // error message issued

            vector<uint16_t> dims = member->getArrayDimensions();

            vector<uint16_t> dimsDueToType;
            ome->getTypeDesc()->appendDimensions(dimsDueToType);

            size = ome->getFinalArrayElementTypeSize();

            size_t index = 0;
            for ( ; index < dimsDueToType.size(); ++index)
                size *= dimsDueToType[index];

            for (index = numDimsInSizeof; index < dims.size(); ++index)
            {
                uint16_t dim = dims[index];
                if (size > 0xFFFF / dim)  // test if size * dim is too large, without overflowing in the test itself
                {
                    errormsg("sizeof() value not representable in 16 bits");
                    return false;
                }
                size *= dim;
            }
            return true;
        }
    }

    // sizeof("literal") is the size between the quotes, plus 1 for the terminating '\0'.
    if (const StringLiteralExpr *sle = dynamic_cast<const StringLiteralExpr *>(subExpr))
    {
        size_t decodedLength = sle->getDecodedLength();
        if (decodedLength + 1 > 0xFFFF)
        {
            errormsg("string literal used in sizeof() is too large (%u bytes)", decodedLength + 1);
            return false;
        }
        size = uint16_t(decodedLength) + 1;
        return true;
    }

    errormsg("unexpected type %s as argument of sizeof()", subExpr->getTypeDesc()->toString().c_str());
    return false;
}


/*virtual*/
CodeStatus
UnaryOpExpr::emitCode(ASMText &out, bool lValue) const
{
    // Check if tree is a constant expression. Emit a single instruction if it is.
    //
    uint16_t value;
    if (evaluateConstantExpr(value))
    {
        if (getType() == BYTE_TYPE)
            value &= 0xFF;
        out.ins(getLoadInstruction(getType()), "#" + wordToString(value, true),
                        "constant expression: " + wordToString(value, false) + " decimal");
        return true;
    }

    switch (oper)
    {
        case IDENTITY:
            if (lValue)
                return false;
            if (!subExpr->emitCode(out, false))
                return false;
            break;

        case NEG:
            if (lValue)
                return false;
            if (!subExpr->emitCode(out, false))
                return false;
            if (getType() == BYTE_TYPE)
                out.ins("NEGB");
            else
            {
                out.ins("COMA");
                out.ins("COMB");
                out.ins("ADDD", "#1");
            }
            break;

        case BITWISE_NOT:
            if (lValue)
                return false;
            if (!subExpr->emitCode(out, false))
                return false;
            if (getType() != BYTE_TYPE)
                out.ins("COMA");
            out.ins("COMB");
            break;

        case POSTINC:
        case PREINC:
        case POSTDEC:
        case PREDEC:
        {
            if (!subExpr->emitCode(out, true))
                return false;

            bool isInc = (oper == POSTINC || oper == PREINC);
            bool isPre = (oper == PREINC || oper == PREDEC);
            if (getType() == BYTE_TYPE)
            {
                string instr = (isInc ? "INC" : "DEC");
                if (isPre)
                    out.ins(instr, ",X");
                out.ins("LDB", ",X");
                if (!isPre)
                    out.ins(instr, ",X");
            }
            else
            {
                out.ins("LDD", ",X");
                uint16_t size = (subExpr->getType() == POINTER_TYPE ? subExpr->getPointedTypeSize() : 1);
                assert(size != 0);
                string imm = "#" + wordToString(size);
                out.ins(isInc ? "ADDD" : "SUBD", imm);
                out.ins("STD", ",X");
                if (!isPre)
                    out.ins(isInc ? "SUBD" : "ADDD", imm, "post increment yields initial value");
            }
            break;
        }

        case ADDRESS_OF:
        {
            if (lValue)
                return false;  // should have been rejected before code emission

            // Special case #1: if subExpr is an array, we cannot ask for its l-value,
            // because it has none (i.e., cannot do this: word a[5]; a = 0;).
            // So in such a case, we ask subExpr->emitCode() to put the array address in D,
            // so no TFR X,D is needed.
            // Special case #2: if subExpr takes the address of a function, this '&' operator
            // has nothing to do.
            //
            bool subIsLValue = (subExpr->getType() != ARRAY_TYPE);
            if (!subExpr->emitCode(out, subIsLValue))
            {
                assert(false);
                return false;
            }
            if (subIsLValue)
                out.ins("TFR", "X,D", "address-of operator");
            break;
        }

        case INDIRECTION:
            {
                // Indirection of struct pointer as r-value not supported.
                if (!lValue && subExpr->getType() == POINTER_TYPE && subExpr->getTypeDesc()->getPointedTypeDesc()->type == CLASS_TYPE)
                {
                    errormsg("indirection of struct as an r-value not supported: use '->' operator instead");
                    return true;  // continuing is harmless and allows compiler to report further errors if any
                }

                WordConstantExpr *wce = dynamic_cast<WordConstantExpr *>(subExpr);
                CastExpr *castExpr = dynamic_cast<CastExpr *>(subExpr);
                WordConstantExpr *castWCE = (castExpr != NULL
                                    ? dynamic_cast<WordConstantExpr *>(castExpr->getSubExpr())
                                    : NULL);
                const VariableExpr *ve = NULL;
                bool checkNullPtr = TranslationUnit::instance().isNullPointerCheckingEnabled();

                if (wce != NULL || castWCE != NULL)  // if address is a constant
                {
                    uint16_t wc = (wce != NULL ? wce->getWordValue() : castWCE->getWordValue());

                    // Load directly from memory, without using X.
                    if (lValue)
                        out.ins("LDX", "#" + wordToString(wc, true), "decimal " + wordToString(wc));
                    else
                        out.ins(getLoadInstruction(getType()), wordToString(wc, true), "decimal " + wordToString(wc));
                }
                else if ((ve = isPostIncOfPtrToSmallType(*subExpr)) != NULL)
                {
                    out.ins("LDX", ve->getFrameDisplacementArg(), "get pointer " + ve->getId());

                    if (checkNullPtr)
                        out.ins("LBSR", "check_null_ptr_x");

                    if (!lValue)
                    {
                        out.ins(getLoadInstruction(getType()), string(",X+") + (getType() == BYTE_TYPE ? "" : "+"), "indirection with post-increment");
                        out.ins("STX", ve->getFrameDisplacementArg(), "store incremented pointer " + ve->getId());
                    }
                    else
                    {
                        string leaxArg = string(getType() == BYTE_TYPE ? "1" : "2") + ",X";
                        out.ins("LEAX", leaxArg, "++");
                        out.ins("STX", ve->getFrameDisplacementArg(), "store incremented pointer " + ve->getId());
                        out.ins("LEAX", "-" + leaxArg, "post-increment yields original pointer");
                    }
                }
                else
                {
                    const VariableExpr *ve = subExpr->asVariableExpr();
                    if (ve != NULL)
                    {
                        string comment = "indirection of variable " + ve->getId();
                        if (subExpr->getType() == ARRAY_TYPE)
                            out.ins("LEAX", ve->getFrameDisplacementArg(), comment);
                        else
                            out.ins("LDX", ve->getFrameDisplacementArg(), comment);
                    }
                    else
                    {
                        if (!subExpr->emitCode(out, false))
                            return false;
                        if (subExpr->getType() == BYTE_TYPE)
                            out.ins("CLRA", "", "pointer is actually byte; need to cast");
                        out.ins("TFR", "D,X");
                    }

                    if (checkNullPtr)
                        out.ins("LBSR", "check_null_ptr_x");

                    if (!lValue)
                        out.ins(getLoadInstruction(getType()), ",X", "indirection");
                }
            }
            break;

        case BOOLEAN_NEG:
            assert(getType() == BYTE_TYPE);
            if (lValue)
                return false;
            if (!subExpr->emitCode(out, false))
                return false;
            if (subExpr->getType() == BYTE_TYPE)
                out.ins("TSTB", "", "boolean negation: get Z flag");
            else
                out.emitCMPDImmediate(0, "boolean negation: get Z flag");
            out.ins("TFR", "CC,B");
            out.ins("ANDB", "#4", "Z flag is result of boolean negation");
            break;

        case SIZE_OF:
        {
            if (lValue)
                return false;

            uint16_t size = 0;
            if (!getSizeOfValue(size))
                return false;
            out.ins("LDD", "#" + wordToString(size), "sizeof");
            break;
        }

        default:
            assert(!"invalid operator");
            return false;
    }
    return true;
}


// Useful to ForStmt.
//
CodeStatus
UnaryOpExpr::emitSimplerIfIncrement(ASMText &out)
{
    if (oper != POSTINC && oper != POSTDEC && oper != PREINC && oper != PREDEC)
        return emitCode(out, false);

    assert(subExpr != NULL);
    const VariableExpr *ve = subExpr->asVariableExpr();
    if (ve == NULL)
        return emitCode(out, false);

    switch (getType())
    {
    case BYTE_TYPE:
    {
        string instr = (oper == POSTINC || oper == PREINC ? "INC" : "DEC");
        out.ins(instr, ve->getFrameDisplacementArg());
        return true;
    }
    case WORD_TYPE:
    case POINTER_TYPE:
    {
        out.ins("LDD", ve->getFrameDisplacementArg());
        string instr = (oper == POSTINC || oper == PREINC ? "ADDD" : "SUBD");
        uint16_t inc = (getType() == POINTER_TYPE ? getPointedTypeSize() : 1);
        out.ins(instr, "#" + wordToString(inc));
        out.ins("STD", ve->getFrameDisplacementArg());
        return true;
    }
    default:
        return emitCode(out, false);
    }
}


bool
UnaryOpExpr::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (subExpr != NULL && !subExpr->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}


void
UnaryOpExpr::replaceChild(Tree *existingChild, Tree *newChild)
{
    if (deleteAndAssign(subExpr, existingChild, newChild))
        return;
    assert(!"child not found");
}
