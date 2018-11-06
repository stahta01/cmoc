/*  $Id: FunctionCallExpr.cpp,v 1.38 2016/10/15 04:10:19 sarrazip Exp $

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

#include "FunctionCallExpr.h"

#include "TranslationUnit.h"
#include "TreeSequence.h"
#include "IdentifierExpr.h"
#include "WordConstantExpr.h"
#include "VariableExpr.h"
#include "StringLiteralExpr.h"
#include "FunctionDef.h"
#include "SemanticsChecker.h"
#include "Declaration.h"
#include "ObjectMemberExpr.h"
#include "FormalParameter.h"
#include "UnaryOpExpr.h"


using namespace std;


FunctionCallExpr::FunctionCallExpr(Tree *func, TreeSequence *args)
  : Tree(),
    function(func),
    funcPtrVarDecl(NULL),
    arguments(args)
{
    assert(function != NULL);
    assert(arguments != NULL);
}


/*virtual*/
FunctionCallExpr::~FunctionCallExpr()
{
    delete function;
    delete arguments;
}


string
FunctionCallExpr::getIdentifier() const
{
    const IdentifierExpr *ie = dynamic_cast<const IdentifierExpr *>(function);
    return ie ? ie->getId() : string();
}


bool
FunctionCallExpr::isCallThroughPointer() const
{
    const IdentifierExpr *ie = dynamic_cast<const IdentifierExpr *>(function);
    return !ie || funcPtrVarDecl;
}


void 
FunctionCallExpr::setFunctionPointerVariableDeclaration(Declaration *_funcPtrVarDecl)
{
    funcPtrVarDecl = _funcPtrVarDecl;
}


void
FunctionCallExpr::checkForStructsPassedByValue()
{
    assert(!isCallThroughPointer());
    int argIndex = 1;
    for (std::vector<Tree *>::const_iterator a = arguments->begin(); a != arguments->end(); ++a, ++argIndex)
        if ((*a)->getType() == CLASS_TYPE)
            errormsg("argument %d of call to function %s() is of type %s (cannot pass struct by value)",
                    argIndex, getIdentifier().c_str(), (*a)->getTypeDesc()->toString().c_str());
}


static bool
ptrParamAcceptsPtrArg(const TypeDesc &paramTD, const TypeDesc &argTD)
{
    assert(paramTD.isPtrOrArray());
    assert(argTD.isPtrOrArray());

    if (*paramTD.getPointedTypeDesc() == *argTD.getPointedTypeDesc())
        return true;

    // Void pointer param accepts pointer to any type.
    // Non-void pointer param requires exact match.
    //
    return paramTD.getPointedTypeDesc()->type == VOID_TYPE;
}


// Called by the ExpressionTypeSetter.
//
bool
FunctionCallExpr::checkAndSetTypes()
{
    if (isCallThroughPointer())
    {
        // Assume that the pointed function returns int.
        // emitCode() will declare an error if the expression is not valid.
        //
        setTypeDesc(TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true));
        return true;
    }


    {
        assert(arguments != NULL);

        string fid = getIdentifier();
        const FunctionDef *fd = TranslationUnit::instance().getFunctionDef(fid);
        if (!fd)
            return true;  // undeclared function: let FunctionChecker handle this

        if (fd->isInterruptServiceRoutine())
        {
            errormsg("calling function %s() is forbidden because it is an interrupt service routine",
                     fid.c_str());
            return true;
        }

        if (!fd->isAcceptableNumberOfArguments(arguments->size()))
            errormsg("call to %s() passes %u argument(s) but function expects %s%u",
                     fid.c_str(), arguments->size(),
                     fd->getFormalParamList()->endsWithEllipsis() ? "at least " : "",
                     fd->getFormalParamList()->size());
        else
        {
            checkForStructsPassedByValue();

            // Check the type of each argument against the corresponding formal parameter.
            // Arguments that are passed through the ellipsis of a variadic function are not checked.
            //
            const FormalParamList *formalParams = fd->getFormalParamList();
            assert(formalParams != NULL);
            //cout << "args: " << arguments->size() << ", params: " << formalParams->size() << endl;
            size_t numParamsToCheck = formalParams->size();
            std::vector<Tree *>::const_iterator a, f;
            for (a = arguments->begin(), f = formalParams->begin(); numParamsToCheck > 0; --numParamsToCheck, ++a, ++f)
            {
                const Tree *argTree = *a;
                const Tree *paramTree = *f;

                assert(argTree && paramTree);

                const FormalParameter *fp = dynamic_cast<const FormalParameter *>(paramTree);
                unsigned fpIndex = unsigned(f - formalParams->begin()) + 1;

                if (paramTree->getType() == BYTE_TYPE && argTree->getType() != BYTE_TYPE && !argTree->is8BitConstant())
                {
                    argTree->errormsg("passing 16-bit argument as byte parameter %u ('%s') of function %s()",
                             fpIndex,
                             fp->getId().c_str(),
                             fd->getId().c_str());
                    continue;
                }

                if (paramTree->getTypeDesc()->isPtrOrArray())  // if parameter is pointer/array
                {
                    if (argTree->getTypeDesc()->isPtrOrArray())  // if argument also pointer/array
                    {
                        if (! ptrParamAcceptsPtrArg(*paramTree->getTypeDesc(), *argTree->getTypeDesc()))
                        {
                            argTree->errormsg("pointer type mismatch: passing %s as parameter %u of function %s(), which is a %s",
                                     argTree->getTypeDesc()->toString().c_str(),
                                     fpIndex, fd->getId().c_str(),
                                     paramTree->getTypeDesc()->toString().c_str());
                            continue;
                        }
                    }
                    else  // argument is not pointer/array: warn on integer arg, except if non-negative constant
                    {
                        uint16_t result = 0;
                        if (! argTree->evaluateConstantExpr(result))
                        {
                            // Warn unless arg is struct/union because checkForStructsPassedByValue() already gave error.
                            if (argTree->getTypeDesc()->type != CLASS_TYPE)
                                argTree->warnmsg("passing non-pointer/array (%s) as parameter %u of function %s(), which is %s",
                                                 argTree->getTypeDesc()->toString().c_str(),
                                                 fpIndex, fd->getId().c_str(), paramTree->getTypeDesc()->toString().c_str());
                        }
                        else if (result >= 0x8000 && argTree->getTypeDesc()->isSigned)
                            argTree->warnmsg("passing negative constant as parameter %u of function %s(), which is %s",
                                     fpIndex, fd->getId().c_str(), paramTree->getTypeDesc()->toString().c_str());
                        continue;
                    }
                }

                // If parameter is named enum, check that argument is member of it.
                const string &enumTypeName = fp->getEnumTypeName();
                if (!enumTypeName.empty())
                {
                    const IdentifierExpr *ie = dynamic_cast<const IdentifierExpr *>(argTree);
                    if (!ie)
                        argTree->errormsg("parameter %u of function %s() must be a member of enum %s",
                                          fpIndex, fd->getId().c_str(), enumTypeName.c_str());
                    else
                    {
                        // Get the enumerator list of the named enum.
                        string id = ie->getId();
                        if (! TranslationUnit::getTypeManager().isIdentiferMemberOfNamedEnum(enumTypeName, id))
                            argTree->errormsg("`%s' used as parameter %u of function %s() but is not a member of enum %s",
                                              id.c_str(), fpIndex, fd->getId().c_str(), enumTypeName.c_str());
                    }
                }
            }
        }

        if (fid == "printf")
            checkPrintfArguments(*arguments);

        setTypeDesc(fd->getTypeDesc());
        return true;
    }

    assert(function != NULL);

    UnaryOpExpr *unary = dynamic_cast<UnaryOpExpr *>(function);
    if (unary && unary->getOperator() == UnaryOpExpr::INDIRECTION)
    {
        // We have a call of the form (*pf)(...).
        // Regardless of the type of 'pf', we assume the return value to be of type 'word'.
        //
        setTypeDesc(TranslationUnit::getTypeManager().getIntType(WORD_TYPE, false));
    }
    else
        setTypeDesc(function->getTypeDesc());

    return true;
}


// Check that each printf() argument is compatible with the corresponding % placeholder.
// For example, passing -1 for %u results in a warning.
//
void
FunctionCallExpr::checkPrintfArguments(const TreeSequence &arguments) const
{
    std::vector<Tree *>::const_iterator a = arguments.begin();

    if (a == arguments.end())  // no arguments: already reported
        return;

    const StringLiteralExpr *formatArg = dynamic_cast<StringLiteralExpr *>(*a);
    if (!formatArg)
        return;  // cannot check format if not a string literal

    ++a;  // advance to first post-format argument

    const string formatStr = formatArg->getLiteral();
    size_t formatLen = formatStr.length();
    for (size_t i = 0; i < formatLen; ++i)
        if (formatStr[i] == '%')
        {
            ++i;
            if (i < formatLen && formatStr[i] == '%')
                continue;

            // Look for end of placeholder.
            while (i < formatLen && !isalpha(formatStr[i]))
                ++i;

            if (i == formatLen)
            {
                formatArg->warnmsg("no letter follows last %% in printf() format string");
                break;
            }

            if (a == arguments.end())
            {
                formatArg->warnmsg("not enough arguments to printf() to match its format string");
                break;
            }

            ++a;  // point to next argument
        }

    if (a != arguments.end())
        formatArg->warnmsg("too many arguments for printf() format string");
}


// Register this function call for the purposes of determining which functions
// are never called and do not need to have assembly code emitted for them.
// When there is no calling function (as in a global variable's initialization
// expression), we do as if main() were the caller. This is not actually the
// case, because the caller is the INITGL routine, but it is close enough for
// the purposes of TranslationUnit::detectCalledFunctions().
//
/*virtual*/
void
FunctionCallExpr::checkSemantics(Functor &f)
{
    if (isCallThroughPointer())
    {
        UnaryOpExpr *u = dynamic_cast<UnaryOpExpr *>(function);
        if (u)
            u->allowDereferencingVoid();
        return;
    }
    SemanticsChecker &sem = dynamic_cast<SemanticsChecker &>(f);
    const FunctionDef *caller = sem.getCurrentFunctionDef();
    string callerId;
    if (caller == NULL)
        callerId = "main";
    else
        callerId = caller->getId();
    TranslationUnit::instance().registerFunctionCall(callerId, getIdentifier());
}


/*virtual*/
CodeStatus
FunctionCallExpr::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    assert(function != NULL);
    
    IdentifierExpr *ie = dynamic_cast<IdentifierExpr *>(function);

    // If standard call (i.e., not made through pointer), then get name of callee.
    //
    string functionId = (isCallThroughPointer() ? "" : ie->getId());

    /*cout << "- FunctionCallExpr::emitCode: ie=" << ie << ", functionId=" << functionId
            << ", funcPtrVarDecl=" << funcPtrVarDecl << endl;*/

    writeLineNoComment(out, "function call"
                            + (functionId.empty() ? " through pointer" : ": " + functionId + "()"));

    TranslationUnit &tu = TranslationUnit::instance();

    /*  Special cases: functions that are defined in stdlib.inc.
    */
    if (!functionId.empty())  // if standard call (i.e., not made through pointer)
    {
        const FunctionDef *fd = tu.getFunctionDef(functionId);
        if (fd == NULL || fd->getBody() == NULL)  // if not declared or does not have a body
        {
            // If the function body is provided by stdlib.inc, register the name as
            // a needed utility sub-routine.
            //
            tu.checkForNeededUtility(functionId);
        }
    }


    /*  Push the arguments in reverse order on the stack.
        Promote byte expressions to word.
    */

    size_t index = arguments->size();
    for (vector<Tree *>::reverse_iterator it = arguments->rbegin();
                                         it != arguments->rend(); it++, index--)
    {
        const Tree *expr = *it;
        string comment = "argument " + wordToString(uint16_t(index))
                         + (functionId.empty() ? "" : " of " + functionId + "()");
        const VariableExpr *ve = expr->asVariableExpr();
        const UnaryOpExpr *unary = dynamic_cast<const UnaryOpExpr *>(expr);

        if (const StringLiteralExpr *sle = dynamic_cast<const StringLiteralExpr *>(expr))
        {
            out.ins("LEAX", sle->getArg(), sle->getEscapedVersion());
            out.ins("PSHS", "X", comment);
        }
        else if (ve && ve->getType() == ARRAY_TYPE)  // if argument is an array
        {
            out.ins("LEAX", ve->getFrameDisplacementArg(), "address of array " + ve->getId());
            out.ins("PSHS", "X", comment);
        }
        else if (unary && unary->getOperator() == UnaryOpExpr::ADDRESS_OF)
        {
            if (!unary->getSubExpr()->emitCode(out, true))  // emit r-value, to get address in X and avoid TFR X,D
                return false;
            out.ins("PSHS", "X", comment);
        }
        else
        {
            if (!expr->emitCode(out, false))
                return false;
            if (expr->getType() == BYTE_TYPE)
                out.ins(expr->getTypeDesc()->isSigned ? "SEX" : "CLRA", "", "promoting byte argument to word");
            out.ins("PSHS", "B,A", comment);
        }
    }

    // Call the function.  If the function to call is designated simply
    // by an identifier, and that identifier is not a variable,
    // then find the corresponding assembly label, and call it directly.
    // Otherwise, compute the address of the function to call and
    // call it indirectly.

    if (ie != NULL && funcPtrVarDecl == NULL)  // if standard call
    {
        assert(!functionId.empty());

        string functionLabel = TranslationUnit::instance().getFunctionLabel(functionId);
        if (functionLabel.empty())
            return false;  // error expected to have been reported by FunctionChecker
        out.ins("LBSR", functionLabel);
    }
    else if (ie != NULL && funcPtrVarDecl != NULL)  // if called address is in a variable, e.g., pf()
    {
        assert(functionId.empty());

        // Prepare a temporary VariableExpr with the function pointer variable declaration,
        // and have it emit code that loads that function pointer in D.
        //
        VariableExpr ve(ie->getId());
        ve.setTypeDesc(TranslationUnit::getTypeManager().getIntType(WORD_TYPE, false));
        ve.setDeclaration(funcPtrVarDecl);
        if (!ve.emitCode(out, false))
            return false;
        out.ins("TFR", "D,X");
        out.ins("JSR", ",X");
    }
    else  // called address is (*pf)() or object.member().
    {
        assert(functionId.empty());

        string jsrArg = ",X";
        UnaryOpExpr *unary = dynamic_cast<UnaryOpExpr *>(function);
        if (unary && unary->getOperator() == UnaryOpExpr::INDIRECTION)  // if (*pf)()
        {
            const VariableExpr *ve = unary->getSubExpr()->asVariableExpr();
            if (ve)
                jsrArg = "[" + ve->getFrameDisplacementArg(0) + "]";
            else if (!function->emitCode(out, true))  // get function address in X
                return false;
        }
        else  // object.member()
        {
            if (!function->emitCode(out, false))
                return false;
            out.ins("TFR", "D,X");
        }
        out.ins("JSR", jsrArg);
    }

    // Pop the arguments off the stack:

    if (arguments->size() > 0)
        out.ins("LEAS", wordToString(uint16_t(arguments->size()) * 2) + ",S");

    return true;
}


bool
FunctionCallExpr::iterate(Functor &f)
{
    if (!f.open(this))
        return false;
    if (!function->iterate(f))
        return false;
    if (!arguments->iterate(f))
        return false;
    if (!f.close(this))
        return false;
    return true;
}
