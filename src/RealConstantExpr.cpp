/*  $Id: RealConstantExpr.cpp,v 1.20 2022/08/19 01:23:06 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2018 Pierre Sarrazin <http://sarrazip.com/>

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

#include "RealConstantExpr.h"

#include "TranslationUnit.h"

#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;


#if 0  /* Would be used if double were supported. */
static bool
hasFloatSuffix(const char *floatNumber)
{
    if (!floatNumber)
        return false;
    size_t len = strlen(floatNumber);
    return len > 0 && tolower(floatNumber[len - 1]) == 'f';
}
#endif


RealConstantExpr::RealConstantExpr(double value, const char * /*tokenText*/)
  : Tree(TranslationUnit::getTypeManager().getRealType(false)),  // false would be !hasFloatSuffix(tokenText) if double were supported
    realValue(value),
    asmLabel()
{
    TranslationUnit::instance().warnIfFloatUnsupported();
}


/*virtual*/
RealConstantExpr::~RealConstantExpr()
{
}


void
RealConstantExpr::setLabel(const string &newLabel)
{
    assert(newLabel.length() > 0);
    asmLabel = newLabel;
}


bool
RealConstantExpr::isDoublePrecision() const
{
    return getTypeDesc() == TranslationUnit::getTypeManager().getRealType(true);
}


// Extract the bits from the floating-point representation of the machine
// running this compiler.
// Source: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
//
static void
getDoublePrecisionBits(double value, bool &isNegative, int16_t &exponent, uint64_t &mantissa)
{
    const uint8_t *bytes = (uint8_t *) &value;
    isNegative = (bytes[7] & 0x80) != 0;

    uint16_t tmp = (uint16_t(bytes[7] & 0x7F) << 8) | bytes[6];
    tmp >>= 4;
    exponent = int16_t(tmp) - 0x3FF;

    mantissa = uint64_t(bytes[6] & 0x0F) << 48;
    for (int i = 6; i--; )  // 5..0
        mantissa |= uint64_t(bytes[i]) << (i * 8);
}


void
RealConstantExpr::emitRealConstantDefinition(ASMText &out, const std::vector<uint8_t> &representation)
{
    size_t len = representation.size();
    assert(len > 0);
    stringstream arg;
    for (size_t i = 0; i < len; ++i)
    {
        if (i > 0)
            arg << ',';
        arg << wordToString(representation[i], true);
    }
    string argstr = arg.str();
    assert(!argstr.empty());
    out.ins("FCB", argstr);
}


bool
RealConstantExpr::emitRealConstantDefinition(ASMText &out) const
{
    vector<uint8_t> rep = getRepresentation();
    if (rep.size() == 0)
    {
        errormsg("floating-point value %g cannot be represented on the targeted platform", realValue);
        return false;
    }
    emitRealConstantDefinition(out, rep);
    return true;
}


vector<uint8_t>
RealConstantExpr::getRepresentation() const
{
    if (isDoublePrecision())
        return vector<uint8_t>();

    if (!TranslationUnit::instance().isFloatingPointSupported())
        return vector<uint8_t>();

    // Extract info from IEEE 754 of 'realValue'.
    // CAUTION: This assumes a little endian platform.

    TargetPlatform targetPlatform = TranslationUnit::instance().getTargetPlatform();
    vector<uint8_t> rep;

    size_t numBytes = TranslationUnit::instance().getTypeManager().getFloatingPointFormatSize(targetPlatform, false);

    if (realValue == 0.0)
    {
        fill_n(back_inserter(rep), numBytes, 0);
    }
    else
    {
        bool isNegative;
        int16_t exponent;
        uint64_t mantissa;
        getDoublePrecisionBits(realValue, isNegative, exponent, mantissa);

        //cout << "# RealConstantExpr::getRepresentation: " << realValue
        //        << " -> " << (isNegative ? "-" : "+") << ", " << exponent << ", $" << hex << mantissa << dec << endl;

        // Color Basic format: "Color Basic Unravelled II".
        // OS-9 format: "Microware C Compiler User's Guide - The C Compiler system (C-Compiler-Ch1.PDF), page 1-5.

        if (exponent < -128 || exponent > 126)
            return vector<uint8_t>();  // cannot represent on target platform

        uint8_t expByte = uint8_t(exponent + 1) + 0x80;

        assert(expByte != 0);

        bool is40BitFormat = (numBytes == 5);  // if false, then OS-9 C format
        if (is40BitFormat)
            rep.push_back(expByte);
        int numMantissaBytes = (is40BitFormat ? 4 : 3);
        for (int i = 0; i < numMantissaBytes; ++i)
            rep.push_back(uint8_t(mantissa >> (52 - 7 - i * 8)));
        if (isNegative)
            rep[is40BitFormat ? 1 : 0] |= 0x80;
        if (!is40BitFormat)
            rep.push_back(expByte);

        /*cout << "#   Result: " << hex
                 << setw(2) << (unsigned) rep[0] << " "
                 << setw(2) << (unsigned) rep[1] << " "
                 << setw(2) << (unsigned) rep[2] << " "
                 << setw(2) << (unsigned) rep[3] << " "
                 << setw(2) << (unsigned) rep[4] << dec << endl;*/
    }
    return rep;
}


uint32_t
RealConstantExpr::getDWordValue() const
{
    if (realValue >= 4294967296.0)
        return 0x7FFFFFFF;
    if (realValue <= -2147483649.0)
        return 0x80000000;
    if (realValue >= 0.0)
        return uint32_t(realValue);
    // Convert double to non-negative value, so that conversion to uint32_t is portable.
    // Then do a 2's complement to obtain a 32-bit unsigned representation of the actual negative value.
    return ~ uint32_t(- realValue) + uint32_t(1);
}


/*virtual*/
void
RealConstantExpr::checkSemantics(Functor &)
{
}


/*virtual*/
CodeStatus
RealConstantExpr::emitCode(ASMText &out, bool lValue) const
{
    if (!lValue)
    {
        errormsg("cannot emit a real number as an r-value");  // doesn't fit in D
        return false;
    }
    if (asmLabel.empty())
    {
        // Somewhat ugly hack to register this constant now that we know that it is used.
        // This will cause the constant and its label to be emitted in the rodata section.
        string label = TranslationUnit::instance().registerRealConstant(*this);
        if (label.empty())
        {
            errormsg("floating-point value %g cannot be represented on the targeted platform", realValue);
            return false;
        }
        const_cast<RealConstantExpr *>(this)->setLabel(label);
    }

    out.ins("LEAX", asmLabel + TranslationUnit::instance().getLiteralIndexRegister(true),
                    "real constant: " + doubleToString(realValue) + " (" + getTypeDesc()->toString() + ")");
    return true;
}
