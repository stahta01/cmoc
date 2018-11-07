/*  $Id: ExpressionTypeSetter.cpp,v 1.23 2016/07/26 01:55:11 sarrazip Exp $

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

#include "ExpressionTypeSetter.h"

#include "BinaryOpExpr.h"
#include "UnaryOpExpr.h"
#include "CastExpr.h"
#include "ClassDef.h"
#include "ConditionalExpr.h"
#include "ObjectMemberExpr.h"
#include "FunctionCallExpr.h"
#include "TranslationUnit.h"
#include "VariableExpr.h"
#include "IdentifierExpr.h"

using namespace std;


ExpressionTypeSetter::ExpressionTypeSetter()
{
}


ExpressionTypeSetter::~ExpressionTypeSetter()
{
}


// Calls setTypeDesc() on 't'.
//
// This method is called for each node of a syntax tree.
// It is called on a child node before being called on the parent node.
// For example, for "return 42", this method is called on the "42" node,
// then on the JumpStmt representing the "return".
//
// N.B.: A VariableExpr is not typed here. It is typed in ScopeCreator::processIdentifierExpr().
//
bool
ExpressionTypeSetter::close(Tree *t)
{
    BinaryOpExpr *bin = dynamic_cast<BinaryOpExpr *>(t);
    if (bin != NULL)
        return processBinOp(bin);

    UnaryOpExpr *un = dynamic_cast<UnaryOpExpr *>(t);
    if (un != NULL)
        return processUnaryOp(un);

    CastExpr *ce = dynamic_cast<CastExpr *>(t);
    if (ce != NULL)
    {
        if (ce->getType() == CLASS_TYPE)
            errormsg("cannot cast to class type");
        assert(ce->getType() != ARRAY_TYPE);  // no syntax for this
        return true;
    }

    FunctionCallExpr *fc = dynamic_cast<FunctionCallExpr *>(t);
    if (fc != NULL)
    {
        (void) fc->checkAndSetTypes();  // may report errors
        return true;
    }

    const TranslationUnit &tu = TranslationUnit::instance();

    ConditionalExpr *cond = dynamic_cast<ConditionalExpr *>(t);
    if (cond != NULL)
    {
        // Both expressions must be of the same type, but if one of them is an 8-bit constant,
        // take it as a byte expression. This allows "char b = (cond ? 42 : 43);" without
        // a useless warning about assigning a word to a byte.
        //
        const TypeDesc *trueTD  = cond->getTrueExpression()->getTypeDesc();
        const TypeDesc *falseTD = cond->getFalseExpression()->getTypeDesc();
        if (cond->getTrueExpression()->is8BitConstant() && cond->getFalseExpression()->is8BitConstant())
            cond->setTypeDesc(TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, trueTD->isSigned));
        else if (trueTD->type == BYTE_TYPE && cond->getFalseExpression()->is8BitConstant())
            cond->setTypeDesc(TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, trueTD->isSigned));
        else if (cond->getTrueExpression()->is8BitConstant() && falseTD->type == BYTE_TYPE)
            cond->setTypeDesc(TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, falseTD->isSigned));
        else if (trueTD->isPtrOrArray() != falseTD->isPtrOrArray())
            cond->errormsg("true and false expressions of conditional are of incompatible types (%s vs %s)",
                           trueTD->toString().c_str(), falseTD->toString().c_str());
        else
        {
            if (trueTD->isPtrOrArray())
                cond->setTypeDesc(trueTD);  // both types must be ptr/array
            else
            {
                // The type of the result is the larger of the two types.
                // If same size, true expression's type is used.
                if (tu.getTypeSize(*trueTD) >= tu.getTypeSize(*falseTD))
                    cond->setTypeDesc(trueTD);
                else
                    cond->setTypeDesc(falseTD);
            }

            if (*trueTD != *falseTD)
                cond->warnmsg("true and false expressions of conditional are not of the same type (%s vs %s); result is of type %s",
                                trueTD->toString().c_str(), falseTD->toString().c_str(),
                                cond->getTypeDesc()->toString().c_str());

        }
        return true;
    }

    ObjectMemberExpr *om = dynamic_cast<ObjectMemberExpr *>(t);
    if (om != NULL)
    {
        Tree *subExpr = om->getSubExpr();
        if (om->isDirect() && subExpr->getType() != CLASS_TYPE)
        {
            om->errormsg("left side of dot operator is not a struct");
            return true;
        }
        if (!om->isDirect() && (subExpr->getType() != POINTER_TYPE
            || subExpr->getTypeDesc()->getPointedType() != CLASS_TYPE))
        {
            om->errormsg("left side of arrow operator is not a pointer to a struct");
            return true;
        }

        const ClassDef *cl = tu.getClassDef(om->getClassName());
        if (cl == NULL)
        {
            om->errormsg("reference to member `%s' of undefined class `%s'",
                         om->getMemberName().c_str(), om->getClassName().c_str());
            assert(!om->getClassName().empty());
            return true;
        }
        const ClassDef::ClassMember *mi = cl->getDataMember(om->getMemberName());
        if (mi == NULL)
        {
            om->errormsg("struct %s has no member named %s",
                         cl->getName().c_str(), om->getMemberName().c_str());
            return true;
        }

        assert(mi->getTypeDesc()->type != VOID_TYPE);
        om->setTypeDesc(mi->getTypeDesc());
        return true;
    }

    const TypeManager &tm = TranslationUnit::getTypeManager();

    // Identifier that refers to an enumerated name.
    // If an IdentifierExpr refers to a variable or function address,
    // it gets typed in ScopeCreator::processIdentifierExpr().
    //
    if (const IdentifierExpr *ie = dynamic_cast<IdentifierExpr *>(t))
    {
        // If the identifier is an enumerated name, we get its TypeDesc and
        // set it as the type of this IdentifierExpr.
        //
        const TypeDesc *td = tm.getEnumeratorTypeDesc(ie->getId());
        if (td)
        {
            assert(td->type != VOID_TYPE);
            t->setTypeDesc(td);
        }
    }

    return true;
}


// Size is that of larger operand.
// Signed is that of left operand.
//
static void
setBinOpTypeDescForDiffSizedOperands(BinaryOpExpr *bin)
{
    const Tree *left = bin->getLeft();
    const Tree *right = bin->getRight();
    const TypeDesc *leftTD  = left->getTypeDesc();
    const TypeDesc *rightTD = right->getTypeDesc();

    assert(leftTD->type != rightTD->type);

    size_t leftSize  =  leftTD->type == BYTE_TYPE ||  left->is8BitConstant() ? 1 : 2;
    size_t rightSize = rightTD->type == BYTE_TYPE || right->is8BitConstant() ? 1 : 2;

    BasicType resultType = (std::max(leftSize, rightSize) == 1 ? BYTE_TYPE : WORD_TYPE);
    bin->setTypeDesc(TranslationUnit::getTypeManager().getIntType(resultType, !left->isUnsignedOrPositiveConst()));
}


// This function always return true so allow all parts of a tree to have
// its expression type set.
//
bool
ExpressionTypeSetter::processBinOp(BinaryOpExpr *bin)
{
    BinaryOpExpr::Op oper = bin->getOperator();
    string ot = BinaryOpExpr::getOperatorToken(oper);
    const Tree *left = bin->getLeft();
    const Tree *right = bin->getRight();
    const TypeDesc *leftTD = left->getTypeDesc();
    const TypeDesc *rightTD = right->getTypeDesc();

    if (oper != BinaryOpExpr::ASSIGNMENT && (leftTD->type == CLASS_TYPE || rightTD->type == CLASS_TYPE))
    {
        bin->errormsg("invalid use of an operator on a struct");
        return true;
    }

    switch (oper)
    {
        case BinaryOpExpr::ARRAY_REF:
            if (left->getType() != POINTER_TYPE
                && left->getType() != ARRAY_TYPE)
            {
                bin->errormsg("array reference on non array or pointer");
                return true;
            }

            bin->setTypeToPointedType(*left);
            return true;

        case BinaryOpExpr::SUB:
            if (leftTD->isPtrOrArray() && rightTD->isPtrOrArray())
            {
                if (*left->getFinalArrayElementType() != *right->getFinalArrayElementType())
                {
                    bin->errormsg("subtraction of incompatible pointers (%s vs %s)",
                                  leftTD->toString().c_str(),
                                  rightTD->toString().c_str());
                    return true;
                }
                bin->setTypeDesc(TranslationUnit::getTypeManager().getIntType(WORD_TYPE, false));
                return true;
            }
            if (leftTD->isPtrOrArray() && rightTD->isIntegral())
            {
                bin->setTypeDesc(leftTD);
                return true;
            }
            if (leftTD->isIntegral() && rightTD->isPtrOrArray())
            {
                bin->errormsg("subtraction of pointer or array from integral");
                bin->setTypeDesc(leftTD);
                return true;
            }
            if (   (leftTD->type == WORD_TYPE && rightTD->type == BYTE_TYPE)
                || (leftTD->type == BYTE_TYPE && rightTD->type == WORD_TYPE))
            {
                setBinOpTypeDescForDiffSizedOperands(bin);
                return true;
            }
            bin->setTypeDesc(leftTD);
            return true;

        case BinaryOpExpr::ADD:
        case BinaryOpExpr::BITWISE_OR:
        case BinaryOpExpr::BITWISE_XOR:
        case BinaryOpExpr::BITWISE_AND:
            if (leftTD->isPtrOrArray() && rightTD->isIntegral())
            {
                bin->setTypeDesc(leftTD);
                return true;
            }
            if (leftTD->isIntegral() && rightTD->isPtrOrArray())
            {
                bin->setTypeDesc(rightTD);
                return true;
            }

            /* FALLTHROUGH */

        case BinaryOpExpr::MUL:
        case BinaryOpExpr::DIV:
        case BinaryOpExpr::MOD:
            if (leftTD->isPtrOrArray() || rightTD->isPtrOrArray())
            {
                bin->errormsg("operator %s cannot be applied to two pointers", ot.c_str());
                return true;
            }
            if (   (leftTD->type == WORD_TYPE && rightTD->type == BYTE_TYPE)
                || (leftTD->type == BYTE_TYPE && rightTD->type == WORD_TYPE))
            {
                setBinOpTypeDescForDiffSizedOperands(bin);
                return true;
            }
            bin->setTypeDesc(leftTD);
            return true;

        case BinaryOpExpr::EQUALITY:
        case BinaryOpExpr::INEQUALITY:
        case BinaryOpExpr::INFERIOR:
        case BinaryOpExpr::INFERIOR_OR_EQUAL:
        case BinaryOpExpr::SUPERIOR:
        case BinaryOpExpr::SUPERIOR_OR_EQUAL:
        case BinaryOpExpr::LOGICAL_AND:
        case BinaryOpExpr::LOGICAL_OR:
            bin->setTypeDesc(TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, false));
            return true;

        case BinaryOpExpr::ASSIGNMENT:
            if (leftTD->type == POINTER_TYPE
                    && rightTD->type == POINTER_TYPE
                    && *leftTD->pointedTypeDesc != *rightTD->pointedTypeDesc)
            {
                stringstream ss;
                ss << "assignment to type '" << *leftTD
                   << "' from incompatible pointer type '" << *rightTD << "'";
                bin->warnmsg(ss.str().c_str());
            }
            else if (leftTD->type == POINTER_TYPE && (rightTD->type == WORD_TYPE || rightTD->type == BYTE_TYPE))  // taken from Declaration::checkInitExpr()
            {
                uint16_t value = 0;
                if (!right->evaluateConstantExpr(value))  // if not constant
                    right->warnmsg("assigning pointer with integer expression");
                else if (value >= 0x8000 && right->getTypeDesc()->isSigned)
                    right->warnmsg("assigning pointer with negative constant");
                // No return, to reach the call to setTypeDesc() below.
            }
            else if (leftTD->type == POINTER_TYPE && rightTD->type == ARRAY_TYPE)  // taken from Declaration::checkInitExpr()
            {
                const TypeDesc *declPointedTypeDesc = leftTD->getPointedTypeDesc();
                const TypeDesc *initPointedTypeDesc = rightTD->getPointedTypeDesc();

                if (*declPointedTypeDesc != *initPointedTypeDesc)
                    right->warnmsg("assigning pointer to %s with incompatible %s",
                            declPointedTypeDesc->toString().c_str(),
                            right->getTypeDesc()->toString().c_str());
                // No return, to reach the call to setTypeDesc() below.
            }
            else if ((leftTD->type == CLASS_TYPE) != (rightTD->type == CLASS_TYPE))  // if not struct on both sides
            {
                left->errormsg("cannot assign `%s' to `%s'", rightTD->toString().c_str(), leftTD->toString().c_str());
            }

            /* FALLTHROUGH */

        case BinaryOpExpr::INC_ASSIGN:
        case BinaryOpExpr::DEC_ASSIGN:
        case BinaryOpExpr::MUL_ASSIGN:
        case BinaryOpExpr::DIV_ASSIGN:
        case BinaryOpExpr::MOD_ASSIGN:
        case BinaryOpExpr::XOR_ASSIGN:
        case BinaryOpExpr::AND_ASSIGN:
        case BinaryOpExpr::OR_ASSIGN:
            if (leftTD->type == BYTE_TYPE && rightTD->type != BYTE_TYPE)
            {
                uint16_t rightValue = 0;
                if (!right->evaluateConstantExpr(rightValue))
                    bin->warnmsg("assigning to `%s' from larger type `%s'",
                                 leftTD->toString().c_str(), rightTD->toString().c_str());
                else if ((int16_t) rightValue < -128 || (int16_t) rightValue > 255)
                    bin->warnmsg("assigning to `%s' from larger constant of type `%s'",
                                 leftTD->toString().c_str(), rightTD->toString().c_str());
            }

            /* FALLTHROUGH */

        case BinaryOpExpr::LEFT_ASSIGN:
        case BinaryOpExpr::RIGHT_ASSIGN:
        case BinaryOpExpr::LEFT_SHIFT:
        case BinaryOpExpr::RIGHT_SHIFT:
            bin->setTypeDesc(leftTD);
            return true;

        default:
            assert(false);
    }
    return true;
}


bool
ExpressionTypeSetter::processUnaryOp(UnaryOpExpr *un)
{
    Tree *subExpr = un->getSubExpr();

    switch (un->getOperator())
    {
        case UnaryOpExpr::ADDRESS_OF:
        {
            if (subExpr->getType() == ARRAY_TYPE)
            {
                un->setTypeDesc(TranslationUnit::getTypeManager().getPointerTo(subExpr->getTypeDesc()->pointedTypeDesc));  // address of T[] is T *
                return true;
            }

            const IdentifierExpr *ie = dynamic_cast<const IdentifierExpr *>(subExpr);
            if (ie && ie->isFuncAddrExpr())
            {
                // Operator '&' used on a function name: gives the address of that function.
                //
                un->setTypeDesc(subExpr->getTypeDesc());
                return true;
            }

            // Note that taking the address of a pointer is supported.
            //
            un->setTypeDesc(TranslationUnit::getTypeManager().getPointerTo(subExpr->getTypeDesc()));
            return true;
        }

        case UnaryOpExpr::INDIRECTION:
            if (subExpr->getType() == VOID_TYPE)
            {
                un->errormsg("using void expression as pointer");
                return true;
            }
            if (subExpr->getType() != POINTER_TYPE
                && subExpr->getType() != ARRAY_TYPE)
            {
                un->setTypeDesc(TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, false));
                un->errormsg("indirection using %s as pointer (assuming pointer to byte)", subExpr->getTypeDesc()->toString().c_str());
                return true;
            }
            un->setTypeDesc(subExpr->getTypeDesc()->pointedTypeDesc);
            return true;

        case UnaryOpExpr::SIZE_OF:
            un->setTypeDesc(TranslationUnit::getTypeManager().getIntType(WORD_TYPE, false));
            un->setSizeofArgTypeDesc();
            un->checkForSizeOfUnknownStruct();
            return true;

        case UnaryOpExpr::BOOLEAN_NEG:
            un->setTypeDesc(TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, false));
            return true;

        case UnaryOpExpr::NEG:  // Negation always returns a signed type.
            if (subExpr->getType() == BYTE_TYPE || subExpr->getType() == WORD_TYPE)
                un->setTypeDesc(TranslationUnit::getTypeManager().getIntType(subExpr->getType(), true));
            else
                un->errormsg("cannot negate an expression of type %s", subExpr->getTypeDesc()->toString().c_str());
            return true;

        default:
            un->setTypeDesc(subExpr->getTypeDesc());
            return true;
    }
}
