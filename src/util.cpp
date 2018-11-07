/*  $Id: util.cpp,v 1.33 2018/05/23 03:34:13 sarrazip Exp $

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
#include <iomanip>

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
        case FUNCTION_TYPE:
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


static struct { const char *name; Register reg; } registerNames[] =
{
    { "A",  A },
    { "B",  B },
    { "D",  D },
    { "X",  X },
    { "U",  U },
    { "S",  S },
    { "Y",  Y },
    { "PC", PC },
    { "DP", DP },
};


Register
getRegisterFromName(const char *name)
{
    for (size_t i = 0; i < sizeof(registerNames) / sizeof(registerNames[0]); ++i)
    {
        const char *n = registerNames[i].name;
        if (n[0] == name[0])  // if 1st char matches
            if (!n[1] || n[1] == name[1])  // if name to match is single char, or 2nd char matches
                return registerNames[i].reg;
    }
    return NO_REGISTER;
}


static void
dwordToCharBuffer(char *buffer, size_t bufferSize, uint32_t dw, bool hex)
{
    const char *fmt;
    if (hex)
        if (dw <= 0xFFFF)
            fmt = "$%04lX";
        else
            fmt = "$%08lX";
    else
        fmt = "%lu";

    snprintf(buffer, bufferSize, fmt, (unsigned long) dw);
}


string
dwordToString(uint32_t dw, bool hex)
{
    char t[32];
    dwordToCharBuffer(t, sizeof(t), dw, hex);
    return t;
}


static void
wordToCharBuffer(char *buffer, size_t bufferSize, uint16_t w, bool hex)
{
    const char *fmt;
    if (hex)
        if (w <= 0xFF)
            fmt = "$%02X";
        else
            fmt = "$%04X";
    else
        fmt = "%u";

    snprintf(buffer, bufferSize, fmt, unsigned(w));
}


string
wordToString(uint16_t w, bool hex)
{
    char t[32];
    wordToCharBuffer(t, sizeof(t), w, hex);
    return t;
}


string
intToString(int16_t n, bool hex)
{
    if (n >= 0)
        return wordToString(uint16_t(n), hex);
    if (n == -32768)
        return wordToString(0x8000, hex);
    char t[32];
    t[0] = '-';
    wordToCharBuffer(t + 1, sizeof(t) - 1, uint16_t(-n), hex);
    return t;
}


string
int8ToString(int8_t n, bool hex)
{
    char t[16];
    const char *fmt = (hex) ? "$%02X" : "%d";
  
    snprintf(t, sizeof(t), fmt, n);
    return t;
}


string
doubleToString(double d)
{
    char t[64];
    snprintf(t, sizeof(t), "%.9g", d);
    return t;
}


void
stringToLower(string &s)
{
    for (size_t len = s.length(), i = 0; i < len; ++i)
        s[i] = (char) tolower(s[i]);
}


bool
isRegisterName(const std::string &s)
{
    std::string lc = s;
    stringToLower(lc);
    return (lc.length() == 1 && strchr("uyxbad", lc[0])) || lc == "pc" || lc == "cc" || lc == "dp";
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


bool
startsWith(const string &s, const char *prefix)
{
    return s.compare(0, strlen(prefix), prefix) == 0;
}


bool
endsWith(const string &s, const char *suffix)
{
    size_t suffixLen = strlen(suffix);
    if (s.length() < suffixLen)
        return false;  // s too short
    return s.compare(s.length() - suffixLen, suffixLen, suffix) == 0;
}


string
removeExtension(string &s)
{
    string::size_type posExt = s.rfind('.');
    if (posExt == string::npos)
        return string();
    string ext(s, posExt);
    s.erase(posExt);
    return ext;
}


string
replaceExtension(const string &s, const char *newExt)
{
    string result = s;
    (void) removeExtension(result);
    return result + newExt;
}


string
getBasename(const string &filename)
{
    string::size_type lastSlash = filename.rfind('/');
    if (lastSlash == string::npos)  // if no slash
        return filename;
    return string(filename, lastSlash + 1, string::npos);
}


ConstCorrectnessCode
isPointerInitConstCorrect(const TypeDesc *declPointedTypeDesc, const TypeDesc *initPointedTypeDesc)
{
    for (;;)
    {
        assert(declPointedTypeDesc && initPointedTypeDesc);

        if (! declPointedTypeDesc->isConstant()
            && initPointedTypeDesc->isConstant()
            && TypeDesc::sameTypesModuloConst(*declPointedTypeDesc, *initPointedTypeDesc))
        {
            return CONST_INCORRECT;  // e.g., int * = const int *
        }
        if (declPointedTypeDesc->type == POINTER_TYPE && initPointedTypeDesc->type == POINTER_TYPE)
        {
            declPointedTypeDesc = declPointedTypeDesc->pointedTypeDesc;
            initPointedTypeDesc = initPointedTypeDesc->pointedTypeDesc;
            continue;  // e.g., go check next pointer level
        }
        if (declPointedTypeDesc->type != initPointedTypeDesc->type)
            return INCOMPAT_TYPES;
        return CONST_CORRECT;
    }
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
errormsgEx(const std::string &sourceFilename, int lineno, const char *fmt, ...)
{
    char s[1024];
    snprintf(s, sizeof(s), "%s:%d", sourceFilename.c_str(), lineno);

    va_list ap;
    va_start(ap, fmt);
    diagnoseVa("error", s, fmt, ap);
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

    // Escape any non-printable characters in yytext[].
    stringstream escapedText;
    escapedText << hex;
    for (size_t i = 0; yytext[i]; ++i)
        if (isprint(yytext[i]))
            escapedText << yytext[i];
        else
            escapedText << "\\x" << setw(2) << (unsigned) (unsigned char) yytext[i];

    errormsg("%s: %s", msg, escapedText.str().c_str());
}

