/*  $Id: WordConstantExpr.cpp,v 1.8 2016/05/06 03:42:56 sarrazip Exp $

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

#include "WordConstantExpr.h"

#include "TranslationUnit.h"

using namespace std;


WordConstantExpr::WordConstantExpr(double value, bool isWord, bool isSigned)
  : Tree(TranslationUnit::getTypeManager().getIntType(isWord ? WORD_TYPE : BYTE_TYPE, isSigned)),
    wordValue(value)
{
}


/*virtual*/
WordConstantExpr::~WordConstantExpr()
{
}


uint16_t
WordConstantExpr::getWordValue() const
{
    return uint16_t(wordValue);
}


/*virtual*/
void
WordConstantExpr::checkSemantics(Functor &)
{
    if (wordValue < -32768 || wordValue > 65535)
    {
        errormsg("invalid numerical constant %f (must be 16-bit integer)", wordValue);
    }
}


/*virtual*/
CodeStatus
WordConstantExpr::emitCode(ASMText &out, bool lValue) const
{
    if (lValue)
        return false;

    uint16_t uValue = getWordValue();
    if (uValue == 0)
    {
        out.ins("CLRA");
        out.ins("CLRB");
    }
    else
        out.ins("LDD", "#" + wordToString(uValue, true),
               "decimal " + (isSigned()
                               ? intToString(int16_t(uValue), false) + " signed"
                               : wordToString(uValue, false) + " unsigned"));
    return true;
}
