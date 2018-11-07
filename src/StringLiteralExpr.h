/*  $Id: StringLiteralExpr.h,v 1.10 2017/09/04 18:58:30 sarrazip Exp $

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

#ifndef _H_StringLiteralExpr
#define _H_StringLiteralExpr

#include "Tree.h"


class StringLiteralExpr : public Tree
{
public:

    StringLiteralExpr(const std::string &literal);

    virtual ~StringLiteralExpr();

    const std::string &getLiteral() const;  // before backslash interpretation
    const std::string &getValue() const;  // after backslash interpretation
    std::string getLabel() const;
    void setLabel(const std::string &newLabel);
    std::string getArg() const;
    std::string getEscapedVersion() const;

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    static std::string escape(const std::string &s);
    std::string decodeEscapedLiteral(bool &hexEscapeOutOfRange,
                                     bool &octalEscapeOutOfRange) const;
    size_t getDecodedLength() const;
    bool wasEmitted() const { return emitted; }
    static void emitStringLiteralDefinition(ASMText &out, const std::string &value);
    void emitStringLiteralDefinition(ASMText &out) const;

    virtual bool isLValue() const { return false; }

private:

    bool interpretStringLiteralPosition(size_t &i, char &out,
                                        bool &hexEscapeOutOfRange,
                                        bool &octalEscapeOutOfRange) const;

    std::string stringLiteral;  // contents of the literal (between the quotes, before backslash interpretation)
    std::string stringValue;  // contents of string (between the quotes, after backslash interpretation)
    std::string asmLabel;
    mutable bool emitted;  // true when at least one use of this literal has been recorded

};


#endif  /* _H_StringLiteralExpr */
