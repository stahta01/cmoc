/*  $Id: Declarator.h,v 1.11 2016/10/08 18:15:06 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2016 Pierre Sarrazin <http://sarrazip.com/>

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

#ifndef _H_Declarator
#define _H_Declarator

#include <string>

#include "util.h"

class Tree;
class Declaration;
class FormalParameter;
class DeclarationSpecifierList;


class Declarator
{
public:

    enum Type { SINGLETON, ARRAY, FUNCPTR };

    // _id: Allow to be empyt, but only to call createFormalParameter().
    //
    Declarator(const std::string &_id,
               const std::string &_srcFilename, int _lineno);

    ~Declarator();

    void setInitExpr(Tree *_initExpr);

    void addArraySizeExpr(Tree *_arraySizeExpr);

    void setFormalParamList(FormalParamList *_formalParamList);

    FormalParamList *getFormalParamList() const;

    Declaration *declareVariable(const TypeDesc *varType, bool isStatic, bool isExtern);

    const std::string &getId() const;

    bool isFunctionPointer() const { return type == FUNCPTR; }

    bool isArray() const { return type == ARRAY; }  // may be multi-dimensional

    bool getNumDimensions(size_t &numDimensions) const;

    // Returns the number of elements, not the number of bytes.
    uint16_t getNumArrayElements() const;

    void incPointerLevel() { ++pointerLevel; }

    size_t getPointerLevel() const { return pointerLevel; }

    void setAsFunctionPointer() { type = FUNCPTR; }

    const TypeDesc *processPointerLevel(const TypeDesc *td) const;

    FormalParameter *createFormalParameter(DeclarationSpecifierList &dsl) const;

    const std::string &getSourceFilename() const { return srcFilename; }

    int getLineNo() const { return lineno; }

    bool computeArrayDimensions(std::vector<uint16_t> &arrayDimensions,
                          bool allowUnknownFirstDimension = false) const;

    std::string toString() const;

private:
    // Forbidden:
    Declarator(const Declarator &);
    Declarator &operator = (const Declarator &);

private:
    std::string id;
    std::string srcFilename;
    int lineno;
    Tree *initExpr;
    std::vector<Tree *> arraySizeExprList;  // only useful if isArray is true; may still be null in that case (size then given by initExpr)
    FormalParamList *formalParamList;
    Type type;
    size_t pointerLevel;  // the declarator was qualified with this many leading asterisks (e.g., byte, byte *p, byte **p, etc.)
};


#endif  /* _H_Declarator */
