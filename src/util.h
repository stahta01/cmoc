/*  $Id: util.h,v 1.19 2016/07/10 06:36:23 sarrazip Exp $

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

#ifndef _H_util
#define _H_util

#include "TypeManager.h"

#include <typeinfo>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <memory>

class Tree;
class FormalParamList;
class TreeSequence;


// Supported platforms for the resulting executable.
//
enum TargetPlatform
{
    COCO_BASIC,     // Extended Color Basic on the Color Computer
    OS9,            // OS-9 or NitrOS-9
    USIM,           // USim 6809 simulator
    VECTREX,        // Vectrex video game console
};


// Representation used by ASMText::InsEffects.
//
enum
{
    PC = 0x80, U = 0x40, Y = 0x20, X  = 0x10,
    DP = 0x08, B = 0x04, A = 0x02, CC = 0x01
};


typedef std::vector<std::string> StringVector;


// Graph that maps a string to a list of strings.
//
typedef std::map<std::string, StringVector> StringGraph;


// Appends 'x' to 'v' only if 'x' is not already present.
// Takes linear time.
//
template <typename T>
inline void
pushBackUnique(std::vector<T> &v, const T &x)
{
    if (find(v.begin(), v.end(), x) == v.end())
        v.push_back(x);
}


template <typename T>
inline void
appendVector(std::vector<T>& dest, const std::vector<T>& src)
{
    std::copy(src.begin(), src.end(), std::inserter(dest, dest.end()));
}


// Tag used in comments for asm(INS, ARG) statements.
// Also used by ASMText.
//
extern const std::string inlineASMTag;


std::string getLoadInstruction(BasicType t);

std::string getAddInstruction(BasicType t);

std::string getSubInstruction(BasicType t);

std::string getAddOrSubInstruction(BasicType t, bool isAdd);

std::string getStoreInstruction(BasicType t);

// Inserts 'element' in 'v' in sorted order. Takes logarithmic time.
//
template <typename T>
bool addUnique(std::vector<T> &v, const T &element)
{
    typename std::vector<T>::iterator it = std::lower_bound(v.begin(), v.end(), element);
    if (it != v.end() && *it == element)
        return false;  // already present
    v.insert(it, element);
    return true;
}

// Determines if 'element' is in *sorted* vector 'v'. Takes logarithmic time.
//
template <typename T>
bool isPresent(std::vector<T> &v, const T &element)
{
    typename std::vector<T>::iterator it = std::lower_bound(v.begin(), v.end(), element);
    return it != v.end() && *it == element;
}


struct FilenameAndLineNo
{
    std::string filename;
    int lineno;

    FilenameAndLineNo(const std::string &fn, int ln)
      : filename(fn), lineno(ln) {}
};


struct BreakableLabels
{
    std::string breakLabel;
    std::string continueLabel;

    BreakableLabels()
      : breakLabel(), continueLabel() {}
};


// In hex, returned string starts with dollar sign.
//
std::string wordToString(uint16_t w, bool hex = false);


// In hex, returned string starts with dollar sign.
//
std::string intToString(int16_t n, bool hex = false);
std::string int8ToString(int8_t n, bool hex = false);


void stringToLower(std::string &s);

bool isPowerOf2(int16_t n);


template <typename ForwardIterator>
inline uint16_t
product(ForwardIterator begin, ForwardIterator end)
{
    uint16_t result = 1;
    for ( ; begin != end; ++begin)
        result *= *begin;
    return result;
}


// Like Perl's join() function.
// Type T must be usable in an ostream.
//
template <typename T>
inline std::string
join(const std::string &delimiter, const std::vector<T> &vec)
{
    std::stringstream ss;
    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin())
            ss << delimiter;
        ss << *it;
    }
    return ss.str();
}


// Prints a vector's elements, separated by ", ".
//
template <typename T>
inline std::ostream &
operator << (std::ostream &out, const std::vector<T> &vec)
{
    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin())
            out << ", ";
        out << *it;
    }
    return out;
}


// Returns a string of the form "foo.cpp:42".
//
std::string getSourceLineNo();

void errormsg(const char *fmt, ...);
void errormsgEx(const std::string &explicitLineNo, const char *fmt, ...);

// diagType: "error" or "warning".
void diagnoseVa(const char *diagType, const std::string &explicitLineNo, const char *fmt, va_list ap);

void warnmsg(const char *fmt, ...);


#endif  /* _H_util */
