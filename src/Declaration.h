/*  $Id: Declaration.h,v 1.12 2016/08/27 04:14:28 sarrazip Exp $

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

#ifndef _H_Declaration
#define _H_Declaration

#include "Tree.h"


class Declaration : public Tree
{
public:

    // numArrayElements: 0 means not an array; otherwise,
    // number of elements in array.
    //
    Declaration(const std::string &id,
                const TypeDesc *td,
                const std::vector<uint16_t> &numArrayElements,
                bool isStatic, bool isExtern);

    virtual ~Declaration();

    void setInitExpr(Tree *initExpr);

    std::string getVariableId() const;

    bool getVariableSizeInBytes(uint16_t &sizeInBytes, bool skipFirstDimensionIfArray = false) const;

    const std::vector<uint16_t> &getArrayDimensions() const;

    void setFrameDisplacement(int16_t disp);
    int16_t getFrameDisplacement(int16_t offset = 0) const;
    std::string getFrameDisplacementArg(int16_t offset = 0) const;
    Tree *getInitExpr();

    void setGlobal(bool g);
    bool isGlobal() const;
    bool isArray() const;
    void setReadOnly(bool ro);  // only used to place global variable in separate section
    bool isReadOnly() const;

    // Returns true only if this object declares an array that has
    // an initializer that only contains integer values, and no
    // string literals.
    //
    bool isArrayWithIntegerInitValues() const;

    // Sets the assembly language label to be used to represent
    // the starting address of this variable (useful only with global declarations).
    //
    void setLabel(const std::string &_label);

    std::string getLabel() const;

    // Emits FCB or FDB directives, but only if isArrayWithIntegerInitValues()
    // is true. Fails otherwise and writes nothing.
    // Returns true on success, false on failure.
    //
    bool emitStaticArrayInitializer(ASMText &out);

    virtual void checkSemantics(Functor &f);

    virtual CodeStatus emitCode(ASMText &out, bool lValue) const;

    virtual bool iterate(Functor &f);

    virtual void replaceChild(Tree *existingChild, Tree *newChild)
    {
        if (deleteAndAssign(initializationExpr, existingChild, newChild))
            return;
        assert(!"child not found");
    }

    bool emitStaticValues(ASMText &out, Tree *arrayElementInitializer, const TypeDesc *requiredTypeDesc);

public:

    std::string variableId;
    int16_t frameDisplacement;   // displacement from stack frame
    std::vector<uint16_t> arrayDimensions;   // empty means non-array; { a, b, c } meants T[a][b][c]
    Tree *initializationExpr;    // owns the pointed object
    std::string label;           // useful only with global declarations
    bool global;                 // true iff declaration is global
    bool readOnly;               // if true, can be put in ROM
    bool isStatic;               // if true, the 'static' keyword was used on this declaration
    bool isExtern;

private:
    // Forbidden:
    Declaration(const Declaration &);
    Declaration &operator = (const Declaration &);

private:

    void init(const std::string &id, uint16_t _numArrayElements = 0);
    static void checkInitExpr(Tree *initializationExpr, const TypeDesc *varTypeDesc, const std::string &variableId, const std::vector<uint16_t> &arrayDimensions, size_t dimIndex);
    static void checkArrayInitializer(Tree *initializationExpr, const TypeDesc *varTypeDesc, const std::string &variableId, const std::vector<uint16_t> &arrayDimensions, size_t dimIndex);
    static void checkClassInitializer(Tree *initializationExpr, const TypeDesc *varTypeDesc, const std::string &variableId);
    static bool isFloatOrLongInitWithNumber(const TypeDesc *varTypeDesc, const Tree &initializationExpr);
    bool isTreeSequenceWithOnlyIntegerValues(const TreeSequence *seq) const;
    bool emitInitCode(ASMText &out, const Tree *initializer, const TypeDesc *requiredTypeDesc, int16_t arraySizeInBytes, uint16_t& writingOffset) const;

};


#endif  /* _H_Declaration */
