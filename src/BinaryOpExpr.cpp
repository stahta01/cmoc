/*  $Id: BinaryOpExpr.cpp,v 1.64 2016/09/15 03:43:57 sarrazip Exp $

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

#include "BinaryOpExpr.h"

#include "TranslationUnit.h"
#include "VariableExpr.h"
#include "Declaration.h"
#include "WordConstantExpr.h"
#include "VariableExpr.h"
#include "IdentifierExpr.h"
#include "UnaryOpExpr.h"
#include "CastExpr.h"
#include "ClassDef.h"
#include "ObjectMemberExpr.h"
#include "FunctionCallExpr.h"

#include <assert.h>

using namespace std;


BinaryOpExpr::BinaryOpExpr(Op op, Tree *left, Tree *right)
  : Tree(),
    oper(op),
    subExpr0(left),
    subExpr1(right),
    numBytesPerElement(0)
{
}


/*virtual*/
BinaryOpExpr::~BinaryOpExpr()
{
    delete subExpr0;
    delete subExpr1;
}


/*virtual*/
void
BinaryOpExpr::checkSemantics(Functor &)
{
    switch (oper)
    {
    case ASSIGNMENT:
    case INC_ASSIGN:
    case DEC_ASSIGN:
    case MUL_ASSIGN:
    case DIV_ASSIGN:
    case MOD_ASSIGN:
    case XOR_ASSIGN:
    case AND_ASSIGN:
    case OR_ASSIGN:
    case LEFT_ASSIGN:
    case RIGHT_ASSIGN:
        if (subExpr0->getType() == ARRAY_TYPE)
            errormsg("cannot assign to array name");
        else if (!subExpr0->isLValue())
            errormsg("lvalue required as left operand of assignment");
        break;

    case ARRAY_REF:
        if (!subExpr0->isLValue() && subExpr0->getType() != POINTER_TYPE)
            errormsg("lvalue required as left operand of array reference");

        // Compute the number of bytes per array element, including the case
        // where subExpr0 is an array of arrays, or a pointer to an array.
        // The last case is useful in the case of a function parameter of array type,
        // as in "void f(int v[][3])". Here, 'v' is a pointer, not an array.
        //
        {
            const TypeDesc *sub0TD = subExpr0->getTypeDesc();
            if (sub0TD->type == ARRAY_TYPE)
                numBytesPerElement = getNumBytesPerMultiDimArrayElement(subExpr0);
            else if (sub0TD->type == POINTER_TYPE && sub0TD->pointedTypeDesc->type == ARRAY_TYPE)
                numBytesPerElement = getNumBytesPerMultiDimArrayElement(subExpr0);
            else if (sub0TD->pointedTypeDesc)
                numBytesPerElement = TranslationUnit::instance().getTypeSize(*sub0TD->pointedTypeDesc);
        }
        break;

    default:
        ;
    }

}


// Emits the code for both sub-expressions.
// One of them is left as a word on the stack.
// The other is left in D.
//
CodeStatus
BinaryOpExpr::emitSubExpressions(ASMText &out, bool reverseOrder) const
{
    Tree *first  = (reverseOrder ? subExpr1 : subExpr0);
    Tree *second = (reverseOrder ? subExpr0 : subExpr1);

    if (!first->emitCode(out, false))
        return false;
    if (first->getType() == BYTE_TYPE)
        out.ins(first->getConvToWordIns(), "", "promotion of binary operand");
    out.ins("PSHS", "B,A");
    if (!second->emitCode(out, false))
        return false;
    if (second->getType() == BYTE_TYPE)
        out.ins(second->getConvToWordIns(), "", "promotion of binary operand");
    return true;
}


/*virtual*/
CodeStatus
BinaryOpExpr::emitCode(ASMText &out, bool lValue) const
{
    assert(subExpr0 != NULL);
    assert(subExpr1 != NULL);

    // Check if tree is a constant expression. Emit a single instruction if it is.
    //
    uint16_t value = 0;
    if (evaluateConstantExpr(value))
    {
        if (getType() == BYTE_TYPE)
            value &= 0xFF;
        out.ins(getLoadInstruction(getType()), "#" + wordToString(value, true),
                        "constant expression: " + wordToString(value, false) + " decimal");
        return true;
    }

    bool signedBranch = subExpr0->isSigned() && subExpr1->isSigned();

    switch (oper)
    {
        case ADD:
            return emitAdd(out, lValue, false);

        case SUB:
            return emitAdd(out, lValue, true);

        case MUL:
        case DIV:
        case MOD:
            return emitMulDivMod(out, lValue);

        case EQUALITY:
            return emitComparison(out, true, "LBEQ");

        case INEQUALITY:
            return emitComparison(out, true, "LBNE");

        case INFERIOR:
            return emitComparison(out, true, (signedBranch ? "LBLT" : "LBLO"));

        case INFERIOR_OR_EQUAL:
            return emitComparison(out, true, (signedBranch ? "LBLE" : "LBLS"));

        case SUPERIOR:
            return emitComparison(out, true, (signedBranch ? "LBGT" : "LBHI"));

        case SUPERIOR_OR_EQUAL:
            return emitComparison(out, true, (signedBranch ? "LBGE" : "LBHS"));

        case LOGICAL_AND:
            return emitLogicalAnd(out, lValue);

        case LOGICAL_OR:
            return emitLogicalOr(out, lValue);

        case BITWISE_OR:
        case BITWISE_XOR:
        case BITWISE_AND:
            return emitBitwiseOperation(out, lValue, oper);

        case LEFT_SHIFT:
        case RIGHT_SHIFT:
            if (lValue)
                return false;  // should have been rejected before code emission
            return emitShift(out, oper == LEFT_SHIFT, false);

        case ASSIGNMENT:
        case INC_ASSIGN:
        case DEC_ASSIGN:
        case MUL_ASSIGN:
        case DIV_ASSIGN:
        case MOD_ASSIGN:
        case XOR_ASSIGN:
        case AND_ASSIGN:
        case OR_ASSIGN:
        case LEFT_ASSIGN:
        case RIGHT_ASSIGN:
            return emitAssignment(out, lValue, oper);

        case ARRAY_REF:
            if (!lValue && subExpr0->getTypeDesc()->isPtrOrArray() && subExpr0->getTypeDesc()->pointedTypeDesc->type == ARRAY_TYPE)
            {
                if (!emitArrayRef(out, true))  // cannot ask r-value here
                    return false;
                out.ins("TFR", "X,D", "array address as r-value");
                return true;
            }
            return emitArrayRef(out, lValue);

        default:
            assert(!"BinaryOpExpr::emitCode() called with unsupported operator");
    }
    return false;
}


CodeStatus
BinaryOpExpr::emitAddImmediateToVariable(ASMText &out,
                                        const VariableExpr *ve0,
                                        uint16_t imm) const
{
    if (ve0->getType() == BYTE_TYPE)
    {
        out.ins("LDB", ve0->getFrameDisplacementArg());
        out.ins(ve0->getConvToWordIns());
    }
    else if (ve0->getType() == ARRAY_TYPE)
    {
        out.ins("LEAX", ve0->getFrameDisplacementArg(),
                                "array " + ve0->getDeclaration()->getVariableId());
        out.ins("TFR", "X,D");
    }
    else
    {
        assert(ve0->getType() != CLASS_TYPE);
        out.ins("LDD", ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
    }

    if (imm != 0)
    {
        if (ve0->getTypeDesc()->isPtrOrArray())
        {
            switch (ve0->getTypeDesc()->pointedTypeDesc->type)
            {
            case VOID_TYPE:
            case BYTE_TYPE:
                break;
            case WORD_TYPE:
                imm *= 2;
                break;
            case CLASS_TYPE:
            {
                const ClassDef *cl = TranslationUnit::instance().getClassDef(ve0->getTypeDesc()->pointedTypeDesc->className);
                assert(cl != NULL);
                imm *= cl->getSizeInBytes();
                break;
            }
            case ARRAY_TYPE:
                imm *= ve0->getPointedTypeSize();
                break;
            default:
                assert(!"immediate added to pointer of unsupported type");
            };
        }

        out.ins("ADDD", "#" + wordToString(imm, true), wordToString(imm, false));
    }

    return true;
}


CodeStatus
BinaryOpExpr::emitBitwiseOperation(ASMText &out, bool lValue, Op op) const
{
    const char *aInstr = NULL, *bInstr = NULL;
    switch (op)
    {
    case BITWISE_OR : aInstr = "ORA" ; bInstr = "ORB" ; break;
    case BITWISE_XOR: aInstr = "EORA"; bInstr = "EORB"; break;
    case BITWISE_AND: aInstr = "ANDA"; bInstr = "ANDB"; break;
    default:
        assert(false);
        return false;
    }

    if (lValue)
        return false;

    // Optimization for VARIABLE & CONST value.
    //
    const VariableExpr *ve0 = subExpr0->asVariableExpr();
    uint16_t rightValue = 0;
    if (ve0 && subExpr1->evaluateConstantExpr(rightValue))
    {
        bool isByte = (ve0->getType() == BYTE_TYPE);
        out.ins(isByte ? "LDB" : "LDD", ve0->getFrameDisplacementArg(0), "variable " + ve0->getId());
        if (!isByte)
            out.ins(aInstr, "#" + wordToString(rightValue >> 8, true));
        out.ins(bInstr, "#" + wordToString(rightValue & 0xFF, true));
        return true;
    }

    // Optimization for (byte) VARIABLE & CONST value.
    //
    if (const CastExpr *castExpr0 = dynamic_cast<CastExpr *>(subExpr0))
    {
        const VariableExpr *castVar0 = castExpr0->getSubExpr()->asVariableExpr();
        if (castExpr0->getType() == BYTE_TYPE && castVar0 && subExpr1->evaluateConstantExpr(rightValue))
        {
            int16_t offset = (castVar0->getType() == BYTE_TYPE ? 0 : 1);  // if var is word, look at its LSB
            out.ins("LDB", castVar0->getFrameDisplacementArg(offset), "variable " + castVar0->getId() + ", cast to byte");
            out.ins(bInstr, "#" + wordToString(rightValue & 0xFF, true));
            return true;
        }
    }

    // General case.
    //
    if (!emitSubExpressions(out, true))
        return false;

    out.ins(aInstr, ",S+");
    out.ins(bInstr, ",S+");
    return true;
}


static uint16_t
add(uint16_t value0, uint16_t value1)
{
    return value0 + value1;
}


static uint16_t
subtract(uint16_t value0, uint16_t value1)
{
    return value0 - value1;
}


// subExpr0 must be the pointer to which an integer is added
// OR subExpr0 must be integral.
// The word on the stack must be the integer to be added to the pointer.
// This word will be pulled off the stack.
//
//static
void
BinaryOpExpr::emitAddIntegerToPointer(ASMText &out, const Tree *subExpr0, bool doSub)
{
    assert(subExpr0);
    const TypeDesc *td0 = subExpr0->getTypeDesc();
    assert(td0);
    assert(td0->isValid());
    assert(td0->isPtrOrArray() || td0->isIntegral());

    const char *instr = (doSub ? "SUBD" : "ADDD");

    if (td0->isIntegral())
    {
        out.ins(instr, ",S++");
        return;
    }

    assert(td0->isPtrOrArray());

    int16_t objectSize = subExpr0->getPointedTypeSize();

    if (objectSize == 1 || objectSize == 0)  // if pointer to byte or void
    {
        out.ins(instr, ",S++");
    }
    else if (objectSize == 2)  // if pointer to word, or to pointer
    {
        out.ins(instr, ",S");
        out.ins(instr, ",S++");
    }
    else
    {
        out.ins("LDX", ",S++", "retrieve right side of add");
        out.ins("PSHS", "B,A", "save left side (the pointer)");
        out.ins("LDD", "#" + wordToString(objectSize), "size of class instance");
        callUtility(out, "MUL16", "multiply right side by size of array element, result in D");
        if (doSub)
        {
            out.ins("TFR",  "D,X",  "right side in X");
            out.ins("PULS", "A,B",  "pointer in D");
            out.ins("PSHS", "X",    "right side on stack");
            out.ins("SUBD", ",S++", "subtract integer from pointer");
        }
        else
            out.ins("ADDD", ",S++", "add product to left side: addition is done");
    }
}


CodeStatus
BinaryOpExpr::emitAdd(ASMText &out, bool lValue, bool doSub) const
{
    if (lValue)
        return false;

    if (emitBinOpIfConstants(out, doSub ? subtract : add))  // if this emits code
        return true;  // done

    const VariableExpr *ve0 = subExpr0->asVariableExpr();
    uint16_t rightValue = 0;
    bool isRightConst = subExpr1->evaluateConstantExpr(rightValue);

    if (ve0 && !ve0->isFuncAddrExpr() && isRightConst)
        return emitAddImmediateToVariable(out, ve0, (doSub ? -1 : +1) * rightValue);

    if (!emitSubExpressions(out, true))
        return false;
    if (getType() == BYTE_TYPE)
    {
        out.ins("LEAS", "1,S");
        out.ins(doSub ? "SUBB" : "ADDB", ",S+");
    }
    else
    {
        if (!doSub
            && subExpr0->getTypeDesc()->isPtrOrArray()
            && subExpr0->getTypeDesc()->getPointedType() == WORD_TYPE
            && subExpr1->getTypeDesc()->isIntegral())
        {
            // <word *> + <integral type>:
            out.ins("ADDD", ",S");
            out.ins("ADDD", ",S++");
        }
        else if (!doSub
            && subExpr1->getTypeDesc()->isPtrOrArray()
            && subExpr1->getTypeDesc()->getPointedType() == WORD_TYPE
            && subExpr0->getTypeDesc()->isIntegral())
        {
            // <integral type> + <word *>:
            out.ins("LSLB");
            out.ins("ROLA");
            out.ins("ADDD", ",S++");
        }
        else if (!doSub)
        {
            if (subExpr1->getTypeDesc()->isPtrOrArray())
            {
                // Right side is pointer or array.
                // Swap with left side because following code expects
                // only pointer or array on left side.
                //
                emitAddIntegerToPointer(out, subExpr1, false);
            }
            else
                emitAddIntegerToPointer(out, subExpr0, false);
        }
        else
        {
            if (   subExpr0->getTypeDesc()->isPtrOrArray()
                && subExpr1->getTypeDesc()->isPtrOrArray())  // difference of pointers
            {
                out.ins("SUBD", ",S++");

                switch (subExpr0->getTypeDesc()->getPointedType())
                {
                case VOID_TYPE:
                case BYTE_TYPE:
                    break;
                case WORD_TYPE:
                    // subtracting two word pointers: result is number of words
                    out.ins("LSRA");
                    out.ins("RORB");
                    break;
                case CLASS_TYPE:
                {
                    // subtracting two object pointers; result is number of objects
                    const ClassDef *cl = TranslationUnit::instance().getClassDef(subExpr0->getTypeDesc()->pointedTypeDesc->className);
                    assert(cl != NULL);
                    out.ins("TFR", "D,X", "num bytes between addresses is dividend");
                    out.ins("LDD", "#" + wordToString(cl->getSizeInBytes()), "size of class instance is divisor");
                    callUtility(out, "DIV16", "divide num bytes by size of instance");
                    out.ins("TFR", "X,D", "leave quotient in D");
                    break;
                }
                default:
                    assert(false);
                }
            }
            else if (subExpr0->getTypeDesc()->isPtrOrArray())  // pointer minus integer
            {
                assert(subExpr1->getTypeDesc()->isIntegral());
                emitAddIntegerToPointer(out, subExpr0, true);
            }
            else if (subExpr1->getTypeDesc()->isPtrOrArray())  // integer minus pointer
            {
                assert(!"integer minus pointer: not supported");
            }
            else  // integer minus integer
            {
                assert(subExpr0->getTypeDesc()->isIntegral());
                assert(subExpr1->getTypeDesc()->isIntegral());
                out.ins("SUBD", ",S++");
            }
        }
    }
    return true;
}


// If subExpr0 and subExpr1 are both constant expressions,
// emits code that loads D (or B if the tree is of BYTE_TYPE) with
// the result of 'f' applied to the two constants, and returns true.
// Returns false if subExpr0 and subExpr1 are NOT both unsigned constant expressions
// (no code is emitted in this case).
// 'f' must be callable as f(uint16_t, uint16_t) and return a uint16_t.
// This call will receive the two constants in order.
//
template <typename BinaryFunctor>
bool
BinaryOpExpr::emitBinOpIfConstants(ASMText &out, BinaryFunctor &f) const
{
    if (subExpr0->isSigned() || subExpr1->isSigned())
        return false;

    uint16_t value0 = 0, value1 = 0;
    if (!subExpr0->evaluateConstantExpr(value0) || !subExpr1->evaluateConstantExpr(value1))
        return false;

    uint16_t result = f(value0, value1);
    const char *loadIns = "LDD";
    string extra;
    if (getType() == BYTE_TYPE)
    {
        result &= 0xFF;
        loadIns = "LDB";
        extra = ", byte type";
    }
    out.ins(loadIns, "#" + wordToString(result), "from " + wordToString(value0) + " and " + wordToString(value1) + extra);
    return true;
}


static uint16_t
multiply(uint16_t value0, uint16_t value1)
{
    return value0 * value1;
}


static uint16_t
divide(uint16_t value0, uint16_t value1)
{
    if (value1 == 0)
        return 0xFFFF;  // fallback
    return value0 / value1;
}


static uint16_t
modulo(uint16_t value0, uint16_t value1)
{
    if (value1 == 0)
        return 0xFFFF;  // fallback
    return value0 % value1;
}


CodeStatus
BinaryOpExpr::emitMulDivMod(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    uint16_t (*functor)(uint16_t, uint16_t) = NULL;
    const char *routine = NULL;
    switch (oper)
    {
    case MUL: functor = multiply; routine = "MUL16";                         break;
    case DIV: functor = divide;   routine = isSigned() ? "SDIV16" : "DIV16"; break;
    case MOD: functor = modulo;   routine = isSigned() ? "SDIV16" : "DIV16"; break;
    default:  assert(false); return false;
    }

    if (emitBinOpIfConstants(out, functor))  // if this emits code
        return true;  // done

    bool isByteResult = (getType() == BYTE_TYPE);

    uint16_t val0 = 0, val1 = 0;
    bool const0 = subExpr0->evaluateConstantExpr(val0);
    bool const1 = subExpr1->evaluateConstantExpr(val1);

    const VariableExpr *ve0 = subExpr0->asVariableExpr();
    const VariableExpr *ve1 = subExpr1->asVariableExpr();

    bool bothWordOperands = (subExpr0->getType() != BYTE_TYPE && subExpr1->getType() != BYTE_TYPE);
    bool bothVarOrConst = (ve0 || const0) && (ve1 || const1);

    if (oper == MUL)
    {
        // If result is byte and both operands are bytes, use MUL and avoid stack.
        // If mult. by a power of 2 <= 32, use LSLB, because MUL takes 11 cycles
        // while LSLB takes 2. Hence, 5 shifts are faster than MUL to mult. by 2**5.
        //
        if (isByteResult && bothVarOrConst)
        {
            val0 &= 0xFF;  // if constant is negative, avoid passing #$FFxx to LDA or LDB
            val1 &= 0xFF;
            string leftArg  = (const0 ? "#" + wordToString(val0, true) : ve0->getFrameDisplacementArg());
            string rightArg = (const1 ? "#" + wordToString(val1, true) : ve1->getFrameDisplacementArg());

            if (const0 && (val0 == 0 || (isPowerOf2(val0) && val0 <= 32)))  // if left side is zero or power of 2
            {
                std::swap(leftArg, rightArg);
                std::swap(const0, const1);
                std::swap(val0, val1);
            }

            if (const1)
            {
                if (val1 == 0)
                {
                    out.ins("CLRB", "", "multiplication by 0");
                    return true;
                }
                if (isPowerOf2(val1) && val1 <= 32)  // if right side is power of 2
                {
                    out.ins("LDB", leftArg, "to be multiplied by " + wordToString(val1));
                    for ( ; val1 > 1; val1 >>= 1)
                        out.ins("LSLB");
                    return true;
                }
            }

            out.ins("LDA", leftArg);
            out.ins("LDB", rightArg);
            out.ins("MUL", "", "result of type byte in B");
            return true;
        }
    }

    // Optimizations for an unsigned value divided by 10.
    if (oper == DIV && val1 == 10 && ! subExpr0->isSigned())
    {
        if (const0)
            out.ins("LDD", "#" + wordToString(val0, true), "dividend");
        else
        {
            // Evaluate dividend and obtain it in D.
            if (!subExpr0->emitCode(out, false))
                return false;
            if (subExpr0->getType() == BYTE_TYPE)
                out.ins(subExpr0->getConvToWordIns(), "", "promotion of binary operand");
        }
        callUtility(out, "DIV16BY10");
        return true;
    }

    // Optimizations for some cases of divison/modulo of 2 bytes or 2 words, unsigned.
    if (oper != MUL && (isByteResult || bothWordOperands) && (const1 || ve1) && subExpr0->isUnsignedOrPositiveConst() && subExpr1->isUnsignedOrPositiveConst())
    {
        bool leftIsVarOrConst = (const0 || ve0);
        string leftArg  = leftIsVarOrConst ? (const0 ? "#" + wordToString(val0, true) : ve0->getFrameDisplacementArg()) : "";
        string rightArg = (const1 ? "#" + wordToString(val1, true) : ve1->getFrameDisplacementArg());

        if (const1)  // if known divisor
        {
            if (val1 == 0)
            {
                out.ins(getLoadInstruction(getType()), "#-1", "division by zero");
                return true;
            }
            if (oper == DIV && isPowerOf2(val1))
            {
                if (isByteResult || val1 <= 256)  // limit word divisor to avoid too many shift instructions
                {
                    if (leftIsVarOrConst)
                        out.ins(getLoadInstruction(getType()), leftArg, "to be divided by " + wordToString(val1));
                    else if (!subExpr0->emitCode(out, false))  // get left side in B
                        return false;

                    // Shift B or D left.
                    if (isByteResult)
                    {
                        for ( ; val1 > 1; val1 >>= 1)
                            out.ins(isSigned() ? "ASRB" : "LSRB");
                    }
                    else if (val1 == 256)
                    {
                        out.ins("TFR", "A,B", "division of unsigned word by 256");
                        out.ins("CLRA");
                    }
                    else
                    {
                        for ( ; val1 > 1; val1 >>= 1)
                        {
                            out.ins(isSigned() ? "ASRA" : "LSRA");
                            out.ins("RORB");
                        }
                    }
                    return true;
                }
                // Continue...
            }
            if (oper == MOD && isPowerOf2(val1))
            {
                if (val1 == 1)
                {
                    if (!isByteResult)
                        out.ins("CLRA", "modulo 1");
                    out.ins("CLRB", "modulo 1");
                    return true;
                }
                if (leftIsVarOrConst)
                    out.ins(getLoadInstruction(getType()), leftArg, "to be moduloed by " + wordToString(val1));
                else if (!subExpr0->emitCode(out, false))  // get left side in B or D
                    return false;
                uint16_t imm = val1 - 1;
                if (!isByteResult)
                    out.ins("ANDA", "#" + wordToString(imm >> 8, true), "modulo " + wordToString(val1));
                out.ins("ANDB", "#" + wordToString(imm & 0xFF, true), "modulo " + wordToString(val1));
                return true;
            }
            if (val1 == 7 && isByteResult)
            {
                if (leftIsVarOrConst)
                    out.ins("LDA", leftArg, "dividend");
                else if (!subExpr0->emitCode(out, false))  // get left side in B
                    return false;
                else
                    out.ins("TFR", "B,A", "modulo dividend expected in A by DIV8BY7");

                callUtility(out, "DIV8BY7");
                if (oper == MOD)
                    out.ins("TFR", "A,B", "resulting modulo in B");
                return true;
            }
        }

        if (const0 && val0 == 0)
        {
            if (!isByteResult)
                out.ins("CLRA", "dividend is 0");
            out.ins("CLRB", "dividend is 0");
            return true;
        }

        if (isByteResult)
        {
            if (leftIsVarOrConst)
                out.ins("LDA", leftArg, "dividend");
            else if (!subExpr0->emitCode(out, false))  // get left side in B
                return false;
            else
                out.ins("TFR", "B,A", "dividend expected in A");

            out.ins("LDB", rightArg, "divisor");
            callUtility(out, isSigned() ? "SDIV8" : "DIV8");
            if (oper == MOD)
                out.ins("TFR", "A,B", "resulting modulo in B");
            return true;
        }
    }

    // If both operands are unsigned words, avoid stack.
    if (bothWordOperands && bothVarOrConst)
    {
        string leftArg  = (const0 ? "#" + wordToString(val0, true) : ve0->getFrameDisplacementArg());
        string rightArg = (const1 ? "#" + wordToString(val1, true) : ve1->getFrameDisplacementArg());
        out.ins("LDX", leftArg,  "left");
        out.ins("LDD", rightArg, "right");
        callUtility(out, routine);
        if (oper == DIV)
            out.ins("TFR", "X,D", "quotient");
        return true;
    }

    emitSubExpressions(out);

    // If multiplication and result is byte, use MUL.
    if (isByteResult)
    {
        out.ins("LDA", "1,S", "load LSB of left side of multiplication");
        out.ins("LEAS", "2,S", "pop left side");
        if (oper == MUL)
            out.ins("MUL", "", "only LSB used, left in B");
        else
        {
            // A = left side = dividend, B = divisor.
            callUtility(out, isSigned() ? "SDIV8" : "DIV8");
            if (oper == MOD)
                out.ins("TFR", "A,B", "resulting modulo in B");
        }
        return true;
    }

    // General case, done in 16 bits.
    out.ins("PULS", "X");  // LDX ,S++ would take one more cycle
    callUtility(out, routine);
    if (oper == DIV)
        out.ins("TFR", "X,D", "quotient");

    return true;
}


bool
BinaryOpExpr::emitComparisonIfNoFuncAddrExprInvolved(ASMText &out) const
{
    const VariableExpr *ve0 = subExpr0->asVariableExpr();
    const VariableExpr *ve1 = subExpr1->asVariableExpr();

    if (ve0 && ve0->isFuncAddrExpr())
        return false;
    if (ve1 && ve1->isFuncAddrExpr())
        return false;

    uint16_t rightValue = 0;
    bool isRightConst = subExpr1->evaluateConstantExpr(rightValue);

    if (ve0 != NULL && isRightConst)
    {
        uint16_t imm = rightValue;

        // If 'imm' is zero, TST must be not used in the 8 bit case because
        // it does not affect the carry flag, which is needed by branch
        // instructions like LBHI.
        // Similarly, LDD is not sufficient in the 16 bit case because it
        // does not affect the carry flag either.
        //
        if (ve0->getType() == BYTE_TYPE)
        {
            out.ins("LDB", ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
            if (imm < 256)
            {
                // We do not use TSTB if 'imm' is zero, because we need a comparison that affects C.
                //
                out.ins("CMPB", "#" + wordToString(imm, true));
            }
            else
            {
                out.ins(ve0->getConvToWordIns(), "", "comparing byte variable with 16-bit constant");
                out.emitCMPDImmediate(imm);
            }
        }
        else
        {
            out.ins("LDD", ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
            out.emitCMPDImmediate(imm);
        }
        return true;
    }
    if (ve0 && ve1 && ve0->getType() == WORD_TYPE && ve1->getType() == WORD_TYPE)  // comparing 2 word vars
    {
        out.ins("LDD",  ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
        out.ins("CMPD", ve1->getFrameDisplacementArg(), "variable " + ve1->getId());
        return true;
    }
    if (ve0 && ve1 && ve0->getType() == BYTE_TYPE && ve1->getType() == BYTE_TYPE)  // comparing 2 byte vars
    {
        out.ins("LDB",  ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
        out.ins("CMPB", ve1->getFrameDisplacementArg(), "variable " + ve1->getId());
        return true;
    }

    return false;  // nothing emitted
}


// condBranchInstr: Ignored if produceIntegerResult is false.
//
CodeStatus
BinaryOpExpr::emitComparison(ASMText &out,
                                bool produceIntegerResult,
                                const string &condBranchInstr) const
{
    if (! emitComparisonIfNoFuncAddrExprInvolved(out))  // try some specific cases
    {
        // General case.
        if (!emitSubExpressions(out, true))
            return false;
        if (subExpr0->fits8Bits() && subExpr1->fits8Bits()
            && subExpr0->isSigned() == subExpr1->isSigned())
        {
            // This optimization is only used if both operands have the same signednes.
            // It should not be used for this case:
            //   unsigned char *e; if (*e == (char) 0xFF) {...}
            // Here, we need to promote the operands to int to do the proper comparison,
            // i.e., *e gets zero-extended while the right side gets sign-extended to 0xFFFF.
            //
            out.ins("LEAS", "1,S", "disregard MSB");
            out.ins("CMPB", ",S+", "compare with LSB");
        }
        else
            out.ins("CMPD", ",S++");
    }

    if (produceIntegerResult)
    {
        string trueLabel  = TranslationUnit::genLabel('L');
        string falseLabel = TranslationUnit::genLabel('L');
        out.ins(condBranchInstr, trueLabel, "if true");
        out.ins("CLRB");
        out.ins("BRA", falseLabel, "false");
        out.emitLabel(trueLabel);
        out.ins("LDB", "#1");
        out.emitLabel(falseLabel);
    }

    return true;
}


CodeStatus
BinaryOpExpr::emitLogicalAnd(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    string endLabel = TranslationUnit::instance().generateLabel('L');
    if (!subExpr0->emitCode(out, false))
        return false;
    if (subExpr0->getType() == BYTE_TYPE)
        out.ins("TSTB", "", "&&");
    else
        out.emitCMPDImmediate(0, "&&");
    out.ins("LBEQ", endLabel, "&& at " + getLineNo() + " yields false, B == 0");

    if (!subExpr1->emitCode(out, false))
        return false;
    if (subExpr1->getType() == BYTE_TYPE)
        out.ins("TSTB", "", "&&");
    else
        out.emitCMPDImmediate(0, "&&");
    out.ins("LBEQ", endLabel, "&& at " + getLineNo() + " yields false, B == 0");

    out.ins("LDB", "#1", "&& yields true");

    assert(getType() == BYTE_TYPE);

    out.emitLabel(endLabel);
    return true;
}


CodeStatus
BinaryOpExpr::emitLogicalOr(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    string trueLabel = TranslationUnit::instance().generateLabel('L');
    string endLabel  = TranslationUnit::instance().generateLabel('L');
    if (!subExpr0->emitCode(out, false))
        return false;
    if (subExpr0->getType() == BYTE_TYPE)
        out.ins("TSTB", "", "||");
    else
        out.ins("CMPD", "#0", "||");
    out.ins("LBNE", trueLabel, "|| yields true");

    if (!subExpr1->emitCode(out, false))
        return false;
    if (subExpr1->getType() == BYTE_TYPE)
        out.ins("TSTB", "", "||");
    else
        out.ins("CMPD", "#0", "||");
    out.ins("LBEQ", endLabel);

    if (subExpr0->getType() == BYTE_TYPE && subExpr1->getType() == BYTE_TYPE)
    {
        // If trueLabel is reached and the two subexpressions are bytes,
        // then the last TSTB instruction must have seen B != 0.
        //
        out.emitLabel(trueLabel, "|| at " + getLineNo() + " yields true, B != 0");
    }
    else
    {
        out.emitLabel(trueLabel);
        out.ins("LDB", "#1", "|| at " + getLineNo() + " yields true");
    }

    assert(getType() == BYTE_TYPE);

    out.emitLabel(endLabel);
    return true;
}


// changeLeftSide: If true, the left side gets the result of the shift AND
//                 the address of the left side is left in X.
//                 If false, only an r-value is computed (and left in D or B).
//
CodeStatus
BinaryOpExpr::emitShift(ASMText &out, bool isLeftShift, bool changeLeftSide) const
{
    bool isLeftByte = (getType() == BYTE_TYPE);

    uint16_t numBits = 0;
    bool constShift = subExpr1->evaluateConstantExpr(numBits);

    if (constShift && numBits <= 7)  // if number of bits to shift by is a constant and small
    {
        // If changeLeftSide true, get address of left side in X.
        // Otherwise, get value of left side in D or B.
        if (!subExpr0->emitCode(out, changeLeftSide))
            return false;

        if (isLeftByte)
        {
            if (changeLeftSide)
                out.ins("LDB", ",X", "get byte to be shifted");

            if (!isLeftShift && subExpr0->isSigned() && numBits == 7)
            {
                // Left side is in B. Result of right shift is $FF if B < 0, zero otherwise.
                out.ins("SEX");
                out.ins("TFR", "A,B");
                out.ins("CLRA");
            }
            else
            {
                const char *op = (isLeftShift ? "LSLB" : (subExpr0->isSigned() ? "ASRB" : "LSRB"));
                for ( ; numBits--; )
                    out.ins(op);
            }

            if (changeLeftSide)
            {
                out.ins("STB", ",X", "store shifted byte");
                // Leave address of left side in X.
            }
        }
        else
        {
            if (changeLeftSide)
                out.ins("LDD", ",X", "get word to be shifted");

            const char *op1 = (isLeftShift ? "LSLB" : (subExpr0->isSigned() ? "ASRA" : "LSRA"));
            const char *op2 = (isLeftShift ? "ROLA" : "RORB");
            for ( ; numBits--; )
            {
                out.ins(op1);
                out.ins(op2);
            }

            if (changeLeftSide)
            {
                out.ins("STD", ",X", "store shifted word");
                // Leave address of left side in X.
            }
        }
    }
    else if (constShift && numBits >= 8)  // if shift by 8, use TFR
    {
        if (isLeftByte)
        {
            if (!isLeftShift && subExpr0->isSigned())
            {
                if (!subExpr0->emitCode(out, changeLeftSide))
                    return false;

                if (changeLeftSide)
                    out.ins("LDB", ",X", "get byte to be shifted");

                // Left side is in B. Result of right shift is $FF if B < 0, zero otherwise.
                out.ins("SEX");
                out.ins("TFR", "A,B");
                out.ins("CLRA");
            }
            else
            {
                // Note: No call to subExpr0->emitCode() needed.
                out.ins("CLRB", "", "shift B 8 or more bits " + string(isLeftShift ? "left" : "right"));
            }

            if (changeLeftSide)
            {
                out.ins("STB", ",X", "store shifted byte");
                // Leave address of left side in X.
            }
        }
        else  // left is word:
        {
            if (!subExpr0->emitCode(out, changeLeftSide))
                return false;

            if (changeLeftSide)
                out.ins("LDD", ",X", "get word to be shifted");

            if (isLeftShift)
            {
                out.ins("TFR", "B,A", "shift D 8 bits left");
                out.ins("CLRB");
            }
            else
            {
                out.ins("TFR", "A,B", "shift D 8 bits right");
                if (subExpr0->isSigned())
                    out.ins("SEX", "", "signed");
                else
                    out.ins("CLRA", "", "unsigned");
            }

            numBits -= 8;
            if (numBits > 0)
            {
                if (isLeftShift)
                {
                    if (numBits >= 8)
                        out.ins("CLRA");
                    else
                        for ( ; numBits--; )
                            out.ins("LSLA");
                }
                else
                {
                     if (numBits >= 7 && subExpr0->isSigned())
                         out.ins("TFR", "A,B");
                     else if (numBits >= 8 && !subExpr0->isSigned())
                         out.ins("CLRB");
                     else
                         for ( ; numBits--; )
                            out.ins(subExpr0->isSigned() ? "ASRB" : "LSRB");
                }
            }

            if (changeLeftSide)
            {
                out.ins("STD", ",X", "store shifted word");
                // Leave address of left side in X.
            }
        }
    }
    else  // general case:
    {
        if (!subExpr0->emitCode(out, changeLeftSide))
            return false;

        if (changeLeftSide)
        {
            out.ins(subExpr0->getLoadIns(), ",X", "get value to be shifted");
            out.ins("PSHS", "X", "preserve address of left side");
        }

        const char *utilityName = NULL;  // name of stdlib.inc subroutine
        if (isLeftShift)
            utilityName = (isLeftByte ? "shiftByteLeft" : "shiftLeft");
        else if (subExpr0->isSigned())
            utilityName = (isLeftByte ? "shiftByteRightSigned" : "shiftRightSigned");
        else
            utilityName = (isLeftByte ? "shiftByteRightUnsigned" : "shiftRightUnsigned");

        out.ins("PSHS", isLeftByte ? "B" : "B,A", "left side of shift: used and popped by " + string(utilityName));

        if (!subExpr1->emitCode(out, false))
            return false;
        if (subExpr1->getType() == BYTE_TYPE)
            out.ins("CLRA");

        callUtility(out, utilityName);

        if (changeLeftSide)
        {
            out.ins("PULS", "X", "restore address of left side of shift");
            out.ins(subExpr0->getStoreIns(), ",X", "store shifted value");
            // Leave address of left side in X.
        }
    }

    return true;
}


/*static*/
string
BinaryOpExpr::getOperatorToken(Op oper)
{
    switch (oper)
    {
        case ADD: return "+";
        case SUB: return "-";
        case MUL: return "*";
        case DIV: return "/";
        case MOD: return "%";
        case EQUALITY: return "==";
        case INEQUALITY: return "!=";
        case INFERIOR: return "<";
        case INFERIOR_OR_EQUAL: return "<=";
        case SUPERIOR: return ">";
        case SUPERIOR_OR_EQUAL: return ">=";
        case LEFT_SHIFT: return "<<";
        case RIGHT_SHIFT: return ">>";
        case LOGICAL_AND: return "&&";
        case LOGICAL_OR: return "||";
        case BITWISE_OR: return "|";
        case BITWISE_XOR: return "^";
        case BITWISE_AND: return "&";
        case ASSIGNMENT: return "=";
        case INC_ASSIGN: return "+=";
        case DEC_ASSIGN: return "-=";
        case MUL_ASSIGN: return "*=";
        case DIV_ASSIGN: return "/=";
        case MOD_ASSIGN: return "%=";
        case XOR_ASSIGN: return "^=";
        case AND_ASSIGN: return "&=";
        case OR_ASSIGN:  return "|=";
        case ARRAY_REF: return "[]";
        case LEFT_ASSIGN:  return "<<=";
        case RIGHT_ASSIGN: return ">>=";
        default:
            assert(!"BinaryOpExpr::getOperatorToken() called with unsupported operator");
            return "<ERROR>";
    }
}


// If true is returned, the assignment is completely emitted.
// If false is returned, no instructions have been emitted,
// but assignedValueArg may have received a (non empty) value.
//
bool
BinaryOpExpr::emitAssignmentIfNoFuncAddrExprInvolved(ASMText &out,
                                                     bool lValue,
                                                     string &assignedValueArg) const
{
    const VariableExpr *ve0 = subExpr0->asVariableExpr();
    const VariableExpr *ve1 = subExpr1->asVariableExpr();

    if (ve0 && ve0->isFuncAddrExpr())
        return false;
    if (ve1 && ve1->isFuncAddrExpr())
        return false;

    uint16_t val = 0;
    bool isRightHandConst = subExpr1->evaluateConstantExpr(val);

    if (oper == ASSIGNMENT && isRightHandConst)  // assign from a constant
    {
        if (getType() == BYTE_TYPE || subExpr1->getType() == BYTE_TYPE)
            val &= 0xFF;
        assignedValueArg = "#" + wordToString(val, true);
        return optimizeConstantAddressCase(out, assignedValueArg);
    }
    if (oper == ASSIGNMENT && ve1 != NULL)  // assign from variable
    {
        /*  If loading a single byte from a word, remember that the 6809
            is a big endian processor:
        */
        assignedValueArg = ve1->getFrameDisplacementArg(getType() == BYTE_TYPE && ve1->getType() == WORD_TYPE);
        return optimizeConstantAddressCase(out, assignedValueArg);
    }
    if (!lValue && (oper == INC_ASSIGN || oper == DEC_ASSIGN) && ve0 && isRightHandConst)  // += or -= on variable with constant right-hand
    {
        if (getType() == BYTE_TYPE || subExpr1->getType() == BYTE_TYPE)
            val &= 0xFF;
        const TypeDesc *pointedTD = ve0->getTypeDesc()->getPointedTypeDesc();
        if (pointedTD)  // if applying += or -= on pointer/array, right side must be multiplied by array element type
            val *= TranslationUnit::instance().getTypeSize(*pointedTD);
        out.ins(getLoadInstruction(getType()), ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
        if (val != 0)  // if nothing to inc/dec, we still need to load the variable in B or D, as per convention: needed for i = (j += 0);
        {
            string instr = (oper == INC_ASSIGN ? getAddInstruction(getType()) : getSubInstruction(getType()));
            out.ins(instr,  "#" + wordToString(val, true), getOperatorToken(oper) + " operator at " + getLineNo());
            out.ins(getStoreInstruction(getType()), ve0->getFrameDisplacementArg());
        }
        return true;
    }
    if (!lValue && (oper == INC_ASSIGN || oper == DEC_ASSIGN) && ve0 && ve1
                && (   (ve0->getType() == BYTE_TYPE && ve1->getType() == BYTE_TYPE)
                    || (ve0->getType() == WORD_TYPE && ve1->getType() == WORD_TYPE)
                   )
            )  // var += var, or var -= var, bytes on both sides
    {
        assert(getType() == ve0->getType());
        out.ins(getLoadInstruction(getType()), ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
        out.ins(getAddOrSubInstruction(getType(), oper == INC_ASSIGN), ve1->getFrameDisplacementArg(), "variable " + ve1->getId());
        out.ins(getStoreInstruction(getType()), ve0->getFrameDisplacementArg(), "variable " + ve0->getId());
        return true;
    }

    return false;  // nothing emitted
}


// Applies to ASSIGNMENT, INC_ASSIGN, etc.
//
CodeStatus
BinaryOpExpr::emitAssignment(ASMText &out, bool lValue, Op oper) const
{
    writeLineNoComment(out, "assignment: " + getOperatorToken(oper));

    #if 0
    cerr << "Assigning to " << subExpr0->getTypeDesc()
            << " from " << subExpr1->getTypeDesc() << "\n";
    #endif

    // Treat struct assignment specially.
    //
    if (oper == ASSIGNMENT && getType() == CLASS_TYPE)
    {
        if (!subExpr1->emitCode(out, true))  // get address of right-side struct in X
            return false;

        int16_t structSizeInBytes = TranslationUnit::instance().getTypeSize(*getTypeDesc());
        out.ins("LDD", "#" + wordToString(structSizeInBytes), "size of struct " + getTypeDesc()->className);
        out.ins("PSHS", "B,A", "push size to _memcpy");
        out.ins("PSHS", "X", "source struct");

        if (!subExpr0->emitCode(out, true))  // get address of left-side struct in X
            return false;

        out.ins("PSHS", "X");
        out.ins("LBSR", "_memcpy", "copy struct (preserves X)");
        TranslationUnit::instance().registerNeededUtility("memcpy");  // define _CMOC_NEED_memcpy_ re: stdlib.inc
        out.ins("LEAS", "6,S");

        // CAUTION: We do not check lValue, so it can be false, which we should reject
        //          in theory, because r-value structs are not supported (they cannot
        //          be stored in register D).
        //          This means that we will return garbage in D when lValue is false.
        //          However, there is no legal context in the language where this bad D
        //          can be used. For instance, one cannot pass a struct by value, so
        //          the compiler never gets here because no code gets emitted.

        return true;
    }

    // Process /= and %=.
    //
    if (oper == DIV_ASSIGN || oper == MOD_ASSIGN)
    {
        // Emit the dividend as an l-value, which puts its address in X.
        if (!subExpr0->emitCode(out, true))
            return false;
        out.ins("PSHS", "X", "preserve address of left side of assignment");

        // Emit the divisor as an r-value, which puts the divisor in D or B.
        // This may trash X, hence the previous PSHS X.
        if (!subExpr1->emitCode(out, false))
            return false;

        // Promote the divisor to a word (in D).
        if (subExpr1->getType() == BYTE_TYPE)
            out.ins(subExpr1->getConvToWordIns());

        // Get the value of the dividend in X, without touching D, which
        // contains the divisor.
        if (getType() == BYTE_TYPE)
        {
            out.ins("PSHS", "B", "preserve divisor");
            out.ins("LDB", "[1,S]", "get value of left side of assignment");
            out.ins(subExpr0->getConvToWordIns(), "promote dividend to word in D");
            out.ins("TFR", "D,X", "dividend to X");
            out.ins("PULS", "B", "restore divisor");
        }
        else
            out.ins("LDX", "[,S]", "get value of left side of assignment");

        // Divide X by D: quotient will be in X, remainder in D.
        callUtility(out, subExpr0->isSigned() && subExpr1->isSigned() ? "SDIV16" : "DIV16");

        // Store the result.
        if (oper == DIV_ASSIGN)
        {
            out.ins("TFR", "X,D", "quotient to D");  // necessary in case lValue is false: r-value must be left in D
            if (getType() == BYTE_TYPE)
                out.ins("STB", "[,S]", "store LSB of quotient at address of left side of assignment");
            else
                out.ins("STD", "[,S]", "store quotient at address of left side of assignment");
        }
        else  // MOD_ASSIGN: remainder in D
        {
            if (getType() == BYTE_TYPE)
                out.ins("STB", "[,S]", "store LSB of remainder at address of left side of assignment");
            else
                out.ins("STD", "[,S]", "store quotient at address of left side of assignment");
        }
        if (lValue)
            out.ins("PULS", "X", "assignment requested as l-value, so X => address of left side");
        else
            out.ins("LEAS", "2,S", "dispose of address of left side of assignment");
        return true;
    }

    // Process <<= and >>=.
    if (oper == LEFT_ASSIGN || oper == RIGHT_ASSIGN)
    {
        return emitShift(out, oper == LEFT_ASSIGN, true);
    }

    /*  Prepare the assigned value argument, i.e., immediate, pushed,
        indexed, etc:
    */
    string assignedValueArg;
    if (emitAssignmentIfNoFuncAddrExprInvolved(out, lValue, assignedValueArg))
        return true;

    const VariableExpr *ve0 = subExpr0->asVariableExpr();

    // Emit code for the right side, except for <<= and >>=.
    //
    if (oper != LEFT_ASSIGN && oper != RIGHT_ASSIGN)
    {
        if (!subExpr1->emitCode(out, false))
            return false;

        if (oper == ASSIGNMENT && ve0 != NULL)
        {
            // No need to save D because no code will be needed to obtain
            // the address of the left side, which is a variable (ve0).
            if (getType() != BYTE_TYPE && subExpr1->getType() == BYTE_TYPE)  // if assigning byte to word
                out.ins(subExpr1->getConvToWordIns());
        }
        else
        {
            if (getType() == BYTE_TYPE)
            {
                out.ins("PSHS", "B");
                assignedValueArg = ",S+";
            }
            else
            {
                // Left side is word so force right side to be word.
                if (subExpr1->getType() == BYTE_TYPE)
                    out.ins(subExpr1->getConvToWordIns());

                out.ins("PSHS", "B,A");
                assignedValueArg = ",S++";
            }
        }
    }


    /*  Generate code to get the address of the left-hand side,
        unless none is needed, as in the case of a simple variable.
    */
    string destAddr;
    if (ve0 != NULL)
    {
        destAddr = ve0->getFrameDisplacementArg();
    }
    else
    {
        if (!subExpr0->emitCode(out, true))
        {
            assert(!"assignment to r-value");
            return false;
        }
        destAddr = ",X";
    }


    if (oper == ASSIGNMENT)
    {
        assert(getType() != VOID_TYPE);
        if (getType() == BYTE_TYPE)
        {
            // The assigned value must be loaded in B at the end of the assignment operation
            // because the assignment could be part of a larger expression, i.e., n = (k = t);
            // Even if 't' is a constant 0, a 'CLR destAddr' instruction, although faster,
            // would not comply with the condition.
            //
            if (assignedValueArg == "#$00")
                out.ins("CLRB");
            else if (!assignedValueArg.empty())
                out.ins("LDB", assignedValueArg);
            out.ins("STB", destAddr);
        }
        else
        {
            if (!assignedValueArg.empty())
            {
                // If right side is byte, but has been pushed in stack as word, don't use LDB.
                //
                if (subExpr1->getType() == BYTE_TYPE && assignedValueArg != ",S++")
                {
                    out.ins("LDB", assignedValueArg);
                    out.ins(subExpr1->getConvToWordIns());
                }
                else
                {
                    const VariableExpr *ve1 = subExpr1->asVariableExpr();
                    if (ve1 != NULL && ve1->getType() == ARRAY_TYPE)
                    {
                        bool preserveX = (destAddr == ",X");
                        if (preserveX)
                            out.ins("TFR", "X,D", "preserve X using D, because X already points to destination");
                        out.ins("LEAX", assignedValueArg);
                        if (preserveX)
                            out.ins("EXG", "X,D", "right-hand side in D; X restored");
                        else
                            out.ins("TFR", "X,D", "right-hand side in D");
                    }
                    else  // otherwise: just load value in D; no need to use X
                    {
                        out.ins("LDD", assignedValueArg);
                    }
                }
            }

            out.ins("STD", destAddr);
        }
    }
    else if (oper == INC_ASSIGN || oper == DEC_ASSIGN)
    {
        assert(getType() != VOID_TYPE);
        if (getType() == BYTE_TYPE)
        {
            out.ins("LDB", destAddr);
            out.ins(oper == INC_ASSIGN ? "ADDB" : "SUBB", assignedValueArg);
            out.ins("STB", destAddr);
            out.ins("CLRA");
        }
        else if (getType() == POINTER_TYPE && getTypeDesc()->getPointedType() == WORD_TYPE)
        {
            // word *ptr = ...; ptr += argument;
            // Load the argument and double it.
            //
            out.ins("LDD", assignedValueArg);
            out.ins("LSLB", "", "inc/dec on word pointer");
            out.ins("ROLA");

            if (oper == INC_ASSIGN)
                out.ins("ADDD", destAddr);
            else
            {
                out.ins("PSHS", "B,A", "preserve right side of -=");
                out.ins("LDD", destAddr, "value from which to subtract");
                out.ins("SUBD", ",S++", "-=");
            }
            out.ins("STD", destAddr);
        }
        else
        {
            assert(getType() != BYTE_TYPE);  // left side is word
            out.ins("LDD", destAddr);
            assert(assignedValueArg != ",S+");
            out.ins(oper == INC_ASSIGN ? "ADDD" : "SUBD", assignedValueArg);
            out.ins("STD", destAddr);
        }
    }
    else if (oper == MUL_ASSIGN)
    {
        assert(getType() != VOID_TYPE);
        assert(getType() == subExpr0->getType());
        if (getType() == BYTE_TYPE)  // if left side is byte
        {
            out.ins("LDB", assignedValueArg);
            out.ins("LDA", destAddr);
            out.ins("MUL");
            out.ins("STB", destAddr);
            out.ins("CLRA");
        }
        else  // left side is word: assignedValueArg assumed to be word too
        {
            out.ins("LDD", assignedValueArg);

            if (destAddr == ",X")
                out.ins("PSHS", "X");
            out.ins("LDX", destAddr);
            callUtility(out, "MUL16");
            if (destAddr == ",X")
                out.ins("PULS", "X");
            out.ins("STD", destAddr);
        }
    }
    else if (oper == XOR_ASSIGN || oper == AND_ASSIGN || oper == OR_ASSIGN)
    {
        assert(getType() != VOID_TYPE);
        string op;
        switch (oper)
        {
        case XOR_ASSIGN: op = "EOR"; break;
        case AND_ASSIGN: op = "AND"; break;
        case OR_ASSIGN:  op = "OR";  break;
        default: op = "_ERROR_";
        }

        if (getType() == BYTE_TYPE)
        {
            out.ins("LDB", destAddr);
            out.ins(op + "B", assignedValueArg);
            out.ins("STB", destAddr);
        }
        else
        {
            // Point to destination with X.
            if (destAddr != ",X")
                out.ins("LEAX", destAddr);

            out.ins("LDD", assignedValueArg);
            out.ins(op + "A", ",X");
            out.ins(op + "B", "1,X");
            out.ins("STD", ",X");
        }
    }

    // If a left-value address was requested, and the destination address
    // is not already in X, then load X with that destination address.
    //
    if (lValue && destAddr != ",X")
        out.ins("LEAX", destAddr);

    return true;
}


// Check for statement of this form: * (byte|word *) 0xXXXX = ...;
// Emits a load and a store instruction (without using X) and returns true.
// Returns false if this optimization is not applicable.
//
bool
BinaryOpExpr::optimizeConstantAddressCase(ASMText &out, const string &assignedValueArg) const
{
    UnaryOpExpr *uo0 = dynamic_cast<UnaryOpExpr *>(subExpr0);

    if (uo0 != NULL && uo0->getOperator() == UnaryOpExpr::INDIRECTION)
    {
        CastExpr *ce = dynamic_cast<CastExpr *>(uo0->getSubExpr());
        if (ce != NULL && ce->getType() == POINTER_TYPE)
        {
            uint16_t constValue = 0;
            if (ce->getSubExpr()->evaluateConstantExpr(constValue))
            {
                const char *load  = (ce->getTypeDesc()->getPointedType() == BYTE_TYPE ? "LDB" : "LDD");
                const char *store = (ce->getTypeDesc()->getPointedType() == BYTE_TYPE ? "STB" : "STD");

                out.ins(load, assignedValueArg);
                out.ins(store, wordToString(constValue, true));

                return true;  // optimization done
            }
        }
    }

    return false;  // no optimization done
}


// Returns true if 'tree' is of type array OR if it is a variable of type pointer.
//
bool
BinaryOpExpr::isArrayOrPointerVariable(const Tree *tree)
{
    assert(tree);

    if (tree->getType() == ARRAY_TYPE)
        return true;

    if (tree->getType() != POINTER_TYPE)
        return false;
    return tree->asVariableExpr() != NULL;
}


int16_t
BinaryOpExpr::getNumBytesPerMultiDimArrayElement(const Tree *tree)
{
    assert(tree);

    // We might have multiple indexes, as in v[i][j][k].
    // Look for the variable by traversing left subtrees, because the VariableExpr
    // points to the declaration, which gives the array dimensions.
    // Take care of the case where (for example) v[i][j] is a pointer instead of an array.
    //
    size_t dimIndex = 1;  // to be incremented with each [] applied to an array
    for (;;)
    {
        if (const VariableExpr *ve = tree->asVariableExpr())  // found the variable?
        {
            // Get the array dimensions.
            // Multiply the dimensions from the one designated by dimIndex to the last one.
            // Example: int v[4][3][5]. 've' designates 'v', and v[i] has 15 elements (3 * 5),
            // which means 30 bytes, because int is 2 bytes.
            //
            const vector<uint16_t> &dims = ve->getDeclaration()->getArrayDimensions();
            assert(dims.size() >= 1);
            assert(dimIndex <= dims.size());
            uint16_t rowSize = product(dims.begin() + dimIndex, dims.end());
            assert(rowSize <= 0x7FFF);
            uint16_t rowSizeInBytes = rowSize * ve->getFinalArrayElementTypeSize();
            assert(rowSizeInBytes <= 0x7FFF);
            return int16_t(rowSizeInBytes);
        }

        if (const ObjectMemberExpr *ome = dynamic_cast<const ObjectMemberExpr *>(tree))
        {
            // Similar to VariableExpr case.
            //
            const Tree *classExpr = ome->getSubExpr();
            string className;
            if (ome->isDirect())
                className = classExpr->getClassName();
            else  // expression is a pointer to a class object:
                className = classExpr->getTypeDesc()->pointedTypeDesc->className;
            const ClassDef *cl = TranslationUnit::instance().getClassDef(className);
            assert(cl);
            const ClassDef::ClassMember *member = cl->getDataMember(ome->getMemberName());
            std::vector<uint16_t> dims = member->getArrayDimensions();
            assert(dims.size() >= 1);
            assert(dimIndex <= dims.size());
            uint16_t rowSize = product(dims.begin() + dimIndex, dims.end());
            assert(rowSize <= 0x7FFF);
            uint16_t rowSizeInBytes = rowSize * ome->getFinalArrayElementTypeSize();
            assert(rowSizeInBytes <= 0x7FFF);
            return int16_t(rowSizeInBytes);
        }

        const BinaryOpExpr *bin = dynamic_cast<const BinaryOpExpr *>(tree);
        if (bin && bin->getOperator() == ARRAY_REF && isArrayOrPointerVariable(bin->subExpr0))
        {
            tree = bin->subExpr0;
            ++dimIndex;
            continue;
        }

        // Not a binary op, or not a [] op, or the left side is a pointer.
        return TranslationUnit::instance().getTypeSize(*tree->getTypeDesc()->pointedTypeDesc);
    }
}


CodeStatus
BinaryOpExpr::emitArrayRef(ASMText &out, bool lValue) const
{
    assert(numBytesPerElement > 0);

    bool checkNullPtr = TranslationUnit::instance().isNullPointerCheckingEnabled();

    // Optimization: left side is array variable and right side is a numerical constant.
    //
    const VariableExpr *ve0 = subExpr0->asVariableExpr();
    uint16_t rightValue = 0;
    bool isRightConst = subExpr1->evaluateConstantExpr(rightValue);
    if (ve0 != NULL && isRightConst)
    {
        // Multiply the array index with the size in bytes of an array element.
        // Example: word v[5] --> v[3] --> 3 * sizeof(word) -> 6.
        //
        uint16_t index = rightValue;
        uint16_t imm = index * numBytesPerElement;

        if (ve0->getType() == POINTER_TYPE)  // this must come first, to handle case of array formal parameter, which is a pointer
        {
            out.ins("LDX", ve0->getFrameDisplacementArg(), "get pointer value");

            if (checkNullPtr)
                out.ins("LBSR", "check_null_ptr_x");

            if (imm != 0)
                out.ins("LEAX", wordToString(imm) + ",X", "add index (" + wordToString(index)
                                + ") multiplied by pointed object size (" + wordToString(numBytesPerElement) + ")");
            if (!lValue)
                out.ins(getLoadInstruction(getType()), ",X");
            return true;
        }

        if (ve0->getType() == ARRAY_TYPE)
        {
            string comment = "index " + wordToString(index) + " in array " + ve0->getId() + "[]";
            if (checkNullPtr)
            {
                out.ins("LEAX", ve0->getFrameDisplacementArg(0), comment);

                out.ins("LBSR", "check_null_ptr_x");

                if (lValue)
                    out.ins("LEAX", wordToString(imm) + ",X", "l-value");
                else
                    out.ins(getLoadInstruction(getType()), wordToString(imm) + ",X", "r-value");
            }
            else
            {
                string instr = (lValue ? "LEAX" : getLoadInstruction(getType()));
                out.ins(instr, ve0->getFrameDisplacementArg(imm), comment);
            }
            return true;
        }

        assert(!"array reference on non-pointer type");
        return false;
    }

    // Get the address of the array in X.
    // If the array is a variable name, avoid asking for an r-value,
    // which does not exist for an array (see VariableExpr::emitCode()).
    //
    bool leftIsArray = (subExpr0->getType() == ARRAY_TYPE);
    if (ve0 && leftIsArray)
        out.ins("LEAX", ve0->getFrameDisplacementArg(), "address of array " + ve0->getId());
    else if (ve0 && !leftIsArray)  // pointer
        out.ins("LDX", ve0->getFrameDisplacementArg(), "pointer " + ve0->getId());
    else
    {
        bool wantLeftSideLValue = (subExpr0->getType() == ARRAY_TYPE);
        if (!subExpr0->emitCode(out, wantLeftSideLValue))
            return false;
        if (!wantLeftSideLValue)  // if left side is pointer, we loaded its value in D
            out.ins("TFR", "D,X");
    }

    if (checkNullPtr)
        out.ins("LBSR", "check_null_ptr_x");

    // Optimization: right side is a numerical constant.
    //
    if (isRightConst)
    {
        uint16_t index = rightValue;
        if (index != 0)
        {
            uint16_t imm = index * numBytesPerElement;
            out.ins("LEAX", wordToString(imm) + ",X",
                           "index " + wordToString(index) + " in array of "
                           + wordToString(numBytesPerElement) + "-byte elements");
        }
    }
    else
    {
        const VariableExpr *ve1 = subExpr1->asVariableExpr();

        // If right side is variable, no need to preserve X during evaluation of index,
        // because we can load right side directly into D or B.
        //
        bool preserveX = !ve1;
        if (preserveX)
            out.ins("PSHS", "X", "preserve array address, then eval array index");

        if (ve1)  // if index is var, load it directly into D or B: this does not affect X
            out.ins(getLoadInstruction(ve1->getType()), ve1->getFrameDisplacementArg(), "variable " + ve1->getId());
        else if (!subExpr1->emitCode(out, false))  // evaluate index into D or B
            return false;
        if (subExpr1->getType() == BYTE_TYPE)
            out.ins(subExpr1->getConvToWordIns(), "", "index expression is of byte type");

        // Multiply the array index (in D) with the size in bytes of an array element.
        // For some sizes, try to get by with shifts.
        //
        switch (numBytesPerElement)
        {
        case 0:
            assert(false);
            break;
        case 1:
            break;
        case 16:
            out.ins("LSLB");
            out.ins("ROLA");
            /* FALLTHROUGH */
        case 8:
            out.ins("LSLB");
            out.ins("ROLA");
            /* FALLTHROUGH */
        case 4:
            out.ins("LSLB");
            out.ins("ROLA");
            /* FALLTHROUGH */
        case 2:
            out.ins("LSLB");
            out.ins("ROLA");
            break;
        default:
            if (!preserveX)  // if X was not preserved earlier, we must preserve it here
                out.ins("PSHS", "X");
            out.ins("LDX", "#" + wordToString(numBytesPerElement), "size of array element");
            callUtility(out, "MUL16", "get offset in bytes in D");
            if (!preserveX)
                out.ins("PULS", "X");
        }

        if (preserveX)  // if X was preserved
            out.ins("PULS", "X", "retrieve array address");
        out.ins("LEAX", "D,X", "add byte offset");
    }

    // Result address in now in X.
    //
    if (!lValue)
        out.ins(getLoadInstruction(getType()), ",X", "get r-value");
    return true;
}


CodeStatus
BinaryOpExpr::emitBoolJumps(ASMText &out,
                            Tree *condition,
                            const std::string &successLabel,
                            const std::string &failureLabel)
{
    assert(condition);

    // If the condition is the boolean negation of something,
    // then evaluate that thing directly and reverse the target labels.
    //
    UnaryOpExpr *ue = dynamic_cast<UnaryOpExpr *>(condition);
    if (ue && ue->getOperator() == UnaryOpExpr::BOOLEAN_NEG)
        return emitBoolJumps(out, ue->getSubExpr(), failureLabel, successLabel);

    // Check for ||, && or relational operators.
    //
    const BinaryOpExpr *be = dynamic_cast<const BinaryOpExpr *>(condition);
    if (be)
    {
        BinaryOpExpr::Op binop = be->getOperator();

        if (binop == BinaryOpExpr::LOGICAL_OR)
        {
            string orFailureLabel = TranslationUnit::instance().generateLabel('L');
            if (!emitBoolJumps(out, be->subExpr0, successLabel, orFailureLabel))
                return false;
            out.emitLabel(orFailureLabel);
            return emitBoolJumps(out, be->subExpr1, successLabel, failureLabel);
        }
        else if (binop == BinaryOpExpr::LOGICAL_AND)
        {
            string andSuccessLabel = TranslationUnit::instance().generateLabel('L');
            if (!emitBoolJumps(out, be->subExpr0, andSuccessLabel, failureLabel))
                return false;
            out.emitLabel(andSuccessLabel);
            return emitBoolJumps(out, be->subExpr1, successLabel, failureLabel);
        }
        else if (be->isRelationalOperator())
        {
            if ((be->getOperator() == EQUALITY || be->getOperator() == INEQUALITY) && be->subExpr1->isExpressionAlwaysFalse())
            {
                // We have "if ({something} == 0)" or "if ({something} != 0)".
                // Simplify to "if (!{something})" or "if ({something})" respectively.
                //
                be->subExpr0->emitCode(out, false);  // {something}
                if (be->subExpr0->getType() == BYTE_TYPE)
                    out.ins("CMPB", "#0");    // TSTB does not affect C, which is needed for LBHI, etc.
                else
                    out.emitCMPDImmediate(0);
            }
            else
                if (!be->emitComparison(out, false, ""))
                    return false;

            bool signedBranch = be->subExpr0->isSigned() && be->subExpr1->isSigned();

            string opcode;
            switch (binop)
            {
                case BinaryOpExpr::EQUALITY:          opcode = "LBEQ"; break;
                case BinaryOpExpr::INEQUALITY:        opcode = "LBNE"; break;
                case BinaryOpExpr::INFERIOR:          opcode = (signedBranch ? "LBLT" : "LBLO"); break;
                case BinaryOpExpr::INFERIOR_OR_EQUAL: opcode = (signedBranch ? "LBLE" : "LBLS"); break;
                case BinaryOpExpr::SUPERIOR:          opcode = (signedBranch ? "LBGT" : "LBHI"); break;
                case BinaryOpExpr::SUPERIOR_OR_EQUAL: opcode = (signedBranch ? "LBGE" : "LBHS"); break;
                default: assert(false);
            }
            out.ins(opcode, successLabel);
            out.ins("LBRA", failureLabel);
            return true;
        }
    }


    // Not ||, && or relational operator, so compare expression with zero:

    if (!condition->emitCode(out, false))
        return false;
    if (condition->getType() == BYTE_TYPE)
        out.ins("TSTB");
    else
        out.emitCMPDImmediate(0);
    out.ins("LBNE", successLabel);
    out.ins("LBRA", failureLabel);
    return true;
}


bool
BinaryOpExpr::isRelationalOperator() const
{
    return oper == EQUALITY || oper == INEQUALITY
        || oper == INFERIOR || oper == INFERIOR_OR_EQUAL
        || oper == SUPERIOR || oper == SUPERIOR_OR_EQUAL;
}


BinaryOpExpr::Op
BinaryOpExpr::getOperator() const
{
    return oper;
}


Tree *BinaryOpExpr::getLeft() const
{
    return subExpr0;
}


Tree *BinaryOpExpr::getRight() const
{
    return subExpr1;
}


bool
BinaryOpExpr::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (!subExpr0->iterate(f))
        return false;
    if (!subExpr1->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}


void
BinaryOpExpr::replaceChild(Tree *existingChild, Tree *newChild)
{
    if (deleteAndAssign(subExpr0, existingChild, newChild))
        return;
    if (deleteAndAssign(subExpr1, existingChild, newChild))
        return;
    assert(!"child not found");
}

