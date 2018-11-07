/*  $Id: util.cpp,v 1.19 2016/07/10 06:36:22 sarrazip Exp $

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

#include "util.h"

#include "ClassDef.h"
#include "TranslationUnit.h"
#include "TreeSequence.h"
#include "FormalParameter.h"
#include "WordConstantExpr.h"
#include "BinaryOpExpr.h"
#include "UnaryOpExpr.h"
#include "DeclarationSpecifierList.h"

#include <string.h>

using namespace std;


const std::string inlineASMTag = "[inline asm]";


int16_t
getTypeSize(BasicType t)
{
    switch (t)
    {
        case BYTE_TYPE:
            return 1;
        case WORD_TYPE:
            return 2;
        case POINTER_TYPE:
            return 2;
        case ARRAY_TYPE:
            assert(!"cannot get size of ARRAY_TYPE");
            return 0;
        case CLASS_TYPE:
            assert(!"cannot get size of CLASS_TYPE");
            return 0;
        case VOID_TYPE:
        case SIZELESS_TYPE:
            return 0;
    }
    return 0;
}


string
getLoadInstruction(BasicType t)
{
    switch (t)
    {
        case WORD_TYPE:
        case POINTER_TYPE:
            return "LDD";
        case BYTE_TYPE:
            return "LDB";
        default:
            assert(false);
            return "";
    }
}


string
getAddInstruction(BasicType t)
{
    switch (t)
    {
        case WORD_TYPE:
        case POINTER_TYPE:
            return "ADDD";
        case BYTE_TYPE:
            return "ADDB";
        default:
            assert(false);
            return "";
    }
}


string
getSubInstruction(BasicType t)
{
    switch (t)
    {
        case WORD_TYPE:
        case POINTER_TYPE:
            return "SUBD";
        case BYTE_TYPE:
            return "SUBB";
        default:
            assert(false);
            return "";
    }
}


string
getAddOrSubInstruction(BasicType t, bool isAdd)
{
    return isAdd ? getAddInstruction(t) : getSubInstruction(t);
}


string
getStoreInstruction(BasicType t)
{
    switch (t)
    {
        case WORD_TYPE:
        case POINTER_TYPE:
            return "STD";
        case BYTE_TYPE:
            return "STB";
        default:
            assert(false);
            return "";
    }
}


string
wordToString(uint16_t w, bool hex)
{
    char t[512];
    const char *fmt;
    if (hex)
        if (w <= 0xFF)
            fmt = "$%02X";
        else
            fmt = "$%04X";
    else
        fmt = "%u";

    snprintf(t, sizeof(t), fmt, (unsigned) w);
    return t;
}


string
intToString(int16_t n, bool hex)
{
    return (n < 0 ? "-" : "") + wordToString(abs(n), hex);
}


string
int8ToString(int8_t n, bool hex)
{
    char t[16];
    const char *fmt = (hex) ? "$%02X" : "%d";
  
    snprintf(t, sizeof(t), fmt, n & 0xFF);
    return t;
}


void
stringToLower(string &s)
{
    for (size_t len = s.length(), i = 0; i < len; ++i)
        s[i] = tolower(s[i]);
}


bool
isPowerOf2(int16_t n)
{
    if (n == 0)
        return false;

    // Bring lowest set bit to position 0.
    while ((n & 1) == 0)
        n >>= 1;

    return n == 1;  // if only one set bit, original value was a power of 2
}


string
getSourceLineNo()
{
    extern int lineno;
    extern string sourceFilename;

    char s[1024];
    snprintf(s, sizeof(s), "%s:%d", sourceFilename.c_str(), lineno);
    return s;
}


void
diagnoseVa(const char *diagType, const string &explicitLineNo, const char *fmt, va_list ap)
{
    extern int numErrors, numWarnings;

    if (strcmp(diagType, "error") == 0)
        numErrors++;
    else
        numWarnings++;

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, ap);

    cout << explicitLineNo << ": " << diagType << ": " << buffer << "\n";
}


void
errormsg(const char *fmt, ...)
{
    extern int lineno;
    extern string sourceFilename;

    char s[1024];
    snprintf(s, sizeof(s), "%s:%d", sourceFilename.c_str(), lineno);

    va_list ap;
    va_start(ap, fmt);
    diagnoseVa("error", s, fmt, ap);
    va_end(ap);
}


void
errormsgEx(const string &explicitLineNo, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    diagnoseVa("error", explicitLineNo, fmt, ap);
    va_end(ap);
}


void
warnmsg(const char *fmt, ...)
{
    extern int lineno;
    extern string sourceFilename;

    char s[1024];
    snprintf(s, sizeof(s), "%s:%d", sourceFilename.c_str(), lineno);

    va_list ap;
    va_start(ap, fmt);
    diagnoseVa("warning", s, fmt, ap);
    va_end(ap);
}


void
yyerror(const char *msg)
{
    extern char *yytext;

    if (strcmp(msg, "parse error") == 0)
        msg = "syntax error";
    errormsg("%s: %s", msg, yytext);
}
