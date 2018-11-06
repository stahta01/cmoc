/*  $Id: StringLiteralExpr.h,v 1.7 2016/08/23 01:34:58 sarrazip Exp $

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

    std::string getLiteral() const;
    std::string getLabel() const;
    void setLabel(const std::string &newLabel);
    std::string getArg() const;
    std::string getEscapedVersion() const;

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    static std::string escape(const std::string &s);
    std::string decodeEscapedLiteral(bool &hexEscapeOutOfRange,
                                     bool &octalEscapeOutOfRange) const;
    size_t getDecodedLength() const;
    static void emitStringLiteralDefinition(ASMText &out, const std::string &value);

private:

    bool interpretStringLiteralPosition(size_t &i, char &out,
                                        bool &hexEscapeOutOfRange,
                                        bool &octalEscapeOutOfRange) const;

    std::string stringLiteral;  // contents of the literal (between the quotes, before backslash interpretation)
    std::string stringLabel;

};


#endif  /* _H_StringLiteralExpr */
