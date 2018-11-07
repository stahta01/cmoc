/*  $Id: ASMText.cpp,v 1.56 2016/07/24 23:03:05 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2003-2015 Pierre Sarrazin <http://sarrazip.com/>
    Copyright (C) 2016 Jamie Cho <https://github.com/jamieleecho>

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

#include "ASMText.h"

#include "Pseudo6809.h"
#include "TranslationUnit.h"
#include "FunctionDef.h"

#include <algorithm>
#include <iomanip>
#include <utility>
#include <stack>
#include <climits>
#include <iostream>
#include <strings.h>  /* for strcasecmp(), as per POSIX.1 */

using namespace std;


static int mystoi(const string &s, char **ptr, int base) {
  return strtol(s.c_str(), ptr, base);
}


static string my_to_string(int val, bool hex=false) {
  stringstream strstream;
  if (hex)
    strstream << std::hex << val;
  else
    strstream << val;
  return strstream.str();
}


ASMText::ASMText()
:   elements(),
    labelTable(),
    basicBlocks()
{
    elements.reserve(16384);  // as of 2015-07-27, Color Verbiste 0.1.3 takes about 7800 elements
}


void
ASMText::addElement(Type type, const string &field0, const string &field1, const string &field2)
{
    elements.push_back(Element());
    Element &e = elements.back();
    e.type = type;
    e.fields[0] = field0;
    e.fields[1] = field1;
    e.fields[2] = field2;
}


void
ASMText::ins(const string &instr, const string &arg, const string &comment)
{
    assert(! (instr == "LDA" && arg.empty()));
    addElement(INSTR, instr, arg, comment);
}


// Emits a CMPD #xxxx, or an equivalent instruction.
//
void
ASMText::emitCMPDImmediate(uint16_t immediateValue, const string &comment)
{
    if (immediateValue == 0)
        ins("ADDD", "#0", comment);  // 1 fewer byte, 1 fewer cycle than CMPD
    else
        ins("CMPD", "#" + wordToString(immediateValue, true), comment);
}


void
ASMText::writeIns(ostream &out, const Element &e)
{
    string instr = e.fields[0], arg = e.fields[1], comment = e.fields[2];

    assert(!instr.empty());
    assert(!(instr == "LDB" && arg == ",S++"));
    assert(!(instr == "LDA" && arg == ",S++"));
    assert(!(instr == "LDD" && arg == ",S+"));

    out << "\t" << instr;
    if (!arg.empty() || !comment.empty())
        out << "\t" << arg << (arg.length() < 8 ? "\t" : "");
    if (!comment.empty())
        out << "\t" << comment;
    out << "\n";
}


void
ASMText::emitFunctionStart(const string &functionId, const string &lineNo)
{
    addElement(FUNCTION_START, functionId, lineNo);
}


void
ASMText::emitFunctionEnd()
{
    addElement(FUNCTION_END);
}


void
ASMText::emitInlineAssembly(const string &text)
{
    addElement(INLINE_ASM, text);
}


void
ASMText::writeInlineAssembly(ostream &out, const Element &e)
{
    out << "* Inline assembly:\n\n";
    out << e.fields[0] << "\n";
    out << "\n* End of inline assembly.\n";
}


void
ASMText::emitLabel(const string &label, const string &comment)
{
    addElement(LABEL, label, comment);
}


void
ASMText::writeLabel(ostream &out, const Element &e)
{
    const string &label = e.fields[0], &comment = e.fields[1];

    // Always EQU *, in case a comment follows, so the 1st word of the comment
    // is not taken for an opcode.
    //
    out << label << "\tEQU\t*";
    if (!comment.empty())
        out << "\t\t" << comment;
    out << "\n";
}


void
ASMText::emitComment(const string &text)
{
    addElement(COMMENT, text);
}


void
ASMText::writeComment(ostream &out, const Element &e)
{
    out << "* " << e.fields[0] << "\n";
}


void
ASMText::emitSeparatorComment()
{
    addElement(SEPARATOR);
}


void
ASMText::writeSeparatorComment(ostream &out, const Element &)
{
    out << "\n";
    out << "\n";
    out << "*******************************************************************************\n";
    out << "\n";
}


void
ASMText::emitInclude(const string &filename)
{
    addElement(INCLUDE, filename);
}


void
ASMText::writeInclude(ostream &out, const Element &e)
{
    out << "#include \"" << e.fields[0] << "\"\n";
}


// Creates basic blocks from elements[] and calls processBasicBlocks() at
// the end of each function.
//
void
ASMText::optimizeWholeFunctions()
{
    string curFuncId;  // empty means not currently in a function, as per FUNCTION_START/FUNCTION_END
    size_t blockStartIndex = size_t(-1);  // not inside a block initially

    basicBlocks.reserve(1024);

    for (size_t i = 0; i < elements.size(); ++i)
    {
        const Element &e = elements[i];
        cout << "### " << setw(5) << i << ". ";
        writeElement(cout, e);
        switch (e.type)
        {
        case FUNCTION_START:
            curFuncId = e.fields[0];  // remember function's id
            assert(!curFuncId.empty());
            labelTable.clear();
            basicBlocks.clear();
            break;
        case COMMENT:
            break;  // ignore comments
        case INSTR:
        case INLINE_ASM:
            if (!curFuncId.empty())  // if inside a function
            {
                if (blockStartIndex == size_t(-1))
                    blockStartIndex = i;  // start block if no block already started

                if (e.type == INSTR && isBasicBlockEndingInstruction(e))  // does the element at i end the current block?
                {
                    createBasicBlock(blockStartIndex, i + 1);  // include current element in block
                    blockStartIndex = size_t(-1);  // no inside a block anymore
                }
            }
            break;
        case LABEL:
            labelTable[e.fields[0]] = i;  // remember elements[] index where label is
            // NO BREAK.
        default:
            if (blockStartIndex != size_t(-1))  // if inside function
            {
                createBasicBlock(blockStartIndex, i);  // exclude the label from the block
                blockStartIndex = size_t(-1);  // no inside a block anymore
            }
            break;
        case FUNCTION_END:
            processBasicBlocks(curFuncId);
            blockStartIndex = size_t(-1);  // not inside a block anymore
            curFuncId.clear();  // remember that not inside function anymore
            break;
        }
    }
}


// Must be in alphabetical order.
//
static const char *basicBlockEndingInstructions[] =
{
    "BCC", "BCS", "BEQ", "BGE", "BGT", "BHI", "BHS", "BLE", "BLO", "BLS",
    "BLT", "BMI", "BNE", "BPL", "BRA", "BVC", "BVS", "JMP", "LBCC",
    "LBCS", "LBEQ", "LBGE", "LBGT", "LBHI", "LBHS", "LBLE", "LBLO", "LBLS",
    "LBLT", "LBMI", "LBNE", "LBPL", "LBRA", "LBVC", "LBVS", "RTI", "RTS",
};


inline bool firstStringComesBeforeSecond(const char *a, const char *b)
{
    return strcmp(a, b) < 0;
}


// Determines if the given instruction marks the end of the basic block
// it is part of. Typically, 'e' must be a branch or a return.
//
bool
ASMText::isBasicBlockEndingInstruction(const Element &e) const
{
    assert(e.type == INSTR);
    if (binary_search(basicBlockEndingInstructions,
                         basicBlockEndingInstructions + sizeof(basicBlockEndingInstructions) / sizeof(basicBlockEndingInstructions[0]),
                         e.fields[0].c_str(),
                         firstStringComesBeforeSecond))
        return true;
    return e.fields[0] == "PULS" && e.fields[1] == "U,PC";
}


// Creates a basic block containing the instructions from startIndex
// (inclusively) to endIndex (exclusively).
// Does not create a block if these indices designate an empty interval,
// of if nothing but comments appear in the interval,
// or if startIndex is invalid.
//
void
ASMText::createBasicBlock(size_t startIndex, size_t endIndex)
{
    cout << "# createBasicBlock(" << startIndex << ", " << endIndex << ")\n";

    if (startIndex >= elements.size())
        return;  // ignore: we are not inside a function
    assert(endIndex >= 1 && endIndex <= elements.size());

    // Decrement endIndex as long as the last block element is a comment.
    while (elements[endIndex - 1].type == COMMENT)
        --endIndex;

    if (startIndex >= endIndex)
        return;  // ignore: empty interval

    basicBlocks.push_back(BasicBlock(startIndex, endIndex));
    BasicBlock &newBlock = basicBlocks.back();

    const Element &lastElem = elements[endIndex - 1];
    if (lastElem.type == INSTR)
    {
        const string &lastIns = lastElem.fields[0];
        const string &lastArg = lastElem.fields[1];

        if (lastIns == "RTS" || lastIns == "RTI" || (lastIns == "PULS" && lastArg == "U,PC"))
        {
            cout << "#   no successor block\n";
        }
        else if (lastIns == "BRA" || lastIns == "LBRA" || lastIns == "JMP")
        {
            cout << "#   single successor at label '" << lastArg << "'\n";
            assert(!lastArg.empty());
            newBlock.firstSuccessorLabel = lastArg;
        }
        else if ((lastIns[0] == 'B' && lastIns != "BSR")
                 || (lastIns[0] == 'L' && lastIns[1] == 'B' && lastIns != "LBSR"))  // short or long branch
        {
            cout << "#   2 successors: next block and block at label '" << lastArg << "'\n";
            assert(!lastArg.empty());
            newBlock.firstSuccessorLabel = lastArg;
            newBlock.secondSuccessorIndex = endIndex;
        }
        else
        {
            cout << "#   fall through at index " << endIndex << "\n";
            newBlock.firstSuccessorIndex = endIndex;  // firstSuccessorLabel left empty, b/c firstSuccessorIndex already set
        }
        cout << "# BasicBlock at " << basicBlocks.size() - 1
                << ": newBlock.firstSuccessorLabel='" << newBlock.firstSuccessorLabel << "'"
                << ", newBlock.firstSuccessorIndex=" << newBlock.firstSuccessorIndex
                << endl;
    }
    else if (lastElem.type == INLINE_ASM)
    {
        cout << "#   inline asm falls through at index " << endIndex << "\n";
        newBlock.firstSuccessorIndex = endIndex;  // firstSuccessorLabel left empty, b/c firstSuccessorIndex already set
    }
    else
        assert(!"failed to determine successors: last element is not instruction");
}


void
ASMText::processBasicBlocks(const string & /*functionId*/)
{
}


size_t
ASMText::findBlockIndex(size_t elementIndex) const
{
    for (vector<BasicBlock>::const_iterator it = basicBlocks.begin(); it != basicBlocks.end(); ++it)
        if (it->startIndex >= elementIndex)
            return it - basicBlocks.begin();
    return size_t(-1);
}


// "Stage 2" optimizations are the ones implemented by Jamie Cho
// in early 2016.
//
void
ASMText::peepholeOptimize(bool useStage2Optims)
{
    for (;;)
    {
        removeUselessLabels();

        bool modified = false;
        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (branchToNextLocation(i))
                modified = true;
            else if (instrFollowingUncondBranch(i))
                modified = true;
            else if (lddToLDB(i))
                modified = true;
            else if (pushLoadDiscardAdd(i))
            {
                replaceWithInstr(i, "ADDB", "#" + wordToString(extractImmedArg(i + 1) & 0xFF, true), "optim: pushLoadDiscardAdd");
                commentOut(i + 1);
                commentOut(i + 2);
                commentOut(i + 3);
                i += 3;
                modified = true;
            }
            else if (pushBLoadAdd(i))
            {
                replaceWithInstr(i, "ADDB", elements[i + 1].fields[1], "optim: pushBLoadAdd");
                commentOut(i + 1);
                commentOut(i + 2);
                i += 2;
                modified = true;
            }
            else if (pushDLoadAdd(i))
            {
                replaceWithInstr(i, "ADDD", elements[i + 1].fields[1], "optim: pushDLoadAdd");
                commentOut(i + 1);
                commentOut(i + 2);
                i += 2;
                modified = true;
            }
            else if (pushLoadDLoadX(i))
            {
                replaceWithInstr(i, "TFR", "D,X", "optim: pushLoadDLoadX");
                commentOut(i + 2);
                modified = true;
            }
            else if (isInstr(i, "LDD", "#$00"))
            {
                insertInstr(i, "CLRB");
                ++i;  // point to the LDD element, which the insertion has moved forward
                replaceWithInstr(i, "CLRA");
                modified = true;
            }
            else if (pushDLoadXLoadD(i))
            {
                commentOut(i, "optim: pushDLoadXLoadD");
                commentOut(i + 2);
                i += 2;
                modified = true;
            }
            else if (stripConsecutiveLoadsToSameReg(i))  // advances 'i' if optimization applies
                modified = true;
            else if (storeLoad(i))  // advances 'i' if optimization applies
                modified = true;
            else if (condBranchOverUncondBranch(i))
                modified = true;
            else if (shortenBranch(i))
                modified = true;
            else if (loadCmpZeroBeqOrBne(i))
                modified = true;
            else if (pushWordForByteComparison(i))
                modified = true;
            else if (useStage2Optims)
            {
                if (fasterPointerIndexing(i))
                    modified = true;
                else if (fasterPointerPushing(i))
                    modified = true;
                else if (stripExtraClrA_B(i))
                    modified = true;
                else if (stripExtraPulsX(i))
                    modified = true;
                else if (stripExtraPushPullB(i))
                    modified = true;
                else if (andA_B0(i))
                    modified = true;
                else if (transformPshsDPshsD(i))
                    modified = true;
                else if (changeLoadDToLoadB(i))
                    modified = true;
                else if (changeAddDToAddB(i))
                    modified = true;
                else if (stripPushLeas1(i))
                    modified = true;
                else if (orAndA_B(i))
                    modified = true;
                else if (loadDToClrALoadB(i))
                    modified = true;
                else if (optimizeStackOperations1(i))
                    modified = true;
                else if (optimizeStackOperations2(i))
                    modified = true;
                else if (optimizeStackOperations3(i))
                    modified = true;
                else if (removeClr(i))
                    modified = true;
                //else if (removeAndOrMulAddSub(i))  // unit tests do not pass with this, as of 2016-07-24
                    //modified = true;
                else if (isInstr(i, "CMPB", "#$00") ||
                         isInstr(i, "CMPA", "#$00") ||
                         isInstr(i, "CMPB", "#0") ||
                         isInstr(i, "CMPA", "#0"))
                {
                    if ((elements[i + 1].fields[0].find("BEQ") != string::npos) ||
                        (elements[i + 1].fields[0].find("BNE") != string::npos))
                    {
                        const string tstInstr = string("TST") + elements[i].fields[0].substr(3);
                        replaceWithInstr(i, tstInstr.c_str());
                        modified = true;
                    }
                }
                else if (optimizeLoadDX(i))
                    modified = true;
                else if (optimizeTfrPush(i))
                    modified = true;
                else if (optimizeTfrOp(i))
                    modified = true;
                else if (removePushB(i))
                    modified = true;
                else if (optimizeLdbTfrClrb(i))
                    modified = true;
                else if (remove16BitStackOperation(i))
                    modified = true;
                else if (optimizePostIncrement(i))
                    modified = true;
                else if (removeUselessOps(i))
                    modified = true;
                else if (optimize16BitStackOps1(i))
                    modified = true;
                else if (optimize16BitStackOps2(i))
                    modified = true;
                else if (optimize8BitStackOps(i))
                    modified = true;
                else if (removeTfrDX(i))
                    modified = true;
                else if (removeUselessLeax(i))
                    modified = true;
                else if (removeUselessLdx(i))
                    modified = true;
                else if (removeUnusedLoad(i))
                    modified = true;
                else if (optimizeAndbTstb(i))
                    modified = true;
                else if (optimizeIndexedX(i))
                    modified = true;
                else if (optimizeIndexedX2(i))
                    modified = true;
                //else if (removeUselessLdb(i))  // unit tests do not pass with this, as of 2016-07-24
                    //modified = true;
                else if (removeUselessLdd(i))
                    modified = true;
                else if (transformPshsXPshsX(i))
                    modified = true;
                else if (optimizePshsOps(i))
                    modified = true;
                else if (optimize16BitCompares(i))
                    modified = true;
            }
        }

        if (!modified)
            break;
    }
}


inline bool
isGeneratedLabel(const string &label)
{
    return label.length() == 6 && label[0] == 'L' && isdigit(label[1]);
}


void
ASMText::removeUselessLabels()
{
    // Fill 'usedLabels' with every generated label that is used in the argument
    // of an instruction, then comment out generated labels that do not appear in this list.
    //
    vector<string> usedLabels;  // must remain sorted
    usedLabels.reserve(2048);

    for (size_t i = 0; i < elements.size(); ++i)
    {
        const Element &e = elements[i];
        if (e.type == INSTR && isGeneratedLabel(e.fields[1]))
            addUnique(usedLabels, e.fields[1]);
    }
    for (size_t i = 0; i < elements.size(); ++i)
    {
        Element &e = elements[i];
        if (e.type != LABEL)
            continue;
        string &label = e.fields[0];
        if (!isGeneratedLabel(label))
            continue;
        if (isPresent(usedLabels, label))
            continue;
        e.type = COMMENT;
        label = "Useless label removed";
    }
}


bool
ASMText::branchToNextLocation(size_t index)
{
    if (index + 1 >= elements.size())  // pattern has 2 instructions
        return false;
    if (!isInstrAnyArg(index, "LBRA") && !isInstrAnyArg(index, "BRA"))  // require uncond. branch
        return false;
    if (!isLabel(index + 1, elements[index].fields[1]))  // require next element to be a label equal to branch argument
        return false;
    commentOut(index, "optim: branchToNextLocation");
    return true;
}


bool
ASMText::instrFollowingUncondBranch(size_t index)
{
    if (index + 1 >= elements.size())  // pattern has 2 instructions
        return false;
    if (!isInstrAnyArg(index, "LBRA") && !isInstrAnyArg(index, "BRA"))  // require uncond. branch
        return false;
    size_t nextInstrIndex = findNextInstrBeforeLabel(index + 1);  // find next instr. unless label/non-instr. is seen first
    if (nextInstrIndex == size_t(-1))
        return false;
    commentOut(nextInstrIndex, "optim: instrFollowingUncondBranch");
    return true;
}


bool
ASMText::lddToLDB(size_t index)
{
    if (!isInstrAnyArg(index, "LDD"))
        return false;
    Element &load = elements[index];
    if (load.fields[1].find("#$") != 0)  // if LDD is not immediate and in hex
        return false;
    size_t nextInstrIndex = findNextInstr(index + 1);  // find next instr., even over a label
    if (nextInstrIndex == size_t(-1))
        return false;
    if (!isInstr(nextInstrIndex, "SEX", "") && !isInstr(nextInstrIndex, "CLRA", ""))
        return false;

    // Register A is dead, so only load B.
    load.fields[0] = "LDB";

    // Make sure immediate value is 8 bits.
    char *end;
    unsigned long n = strtoul(load.fields[1].c_str() + 2, &end, 16);
    load.fields[1] = "#" + wordToString(uint16_t(n) & 0xFF, true);
    load.fields[2] = "optim: lddToLDB";
    return true;
}


// Determine if we have this pattern starting at elements[index]:
//    PSHS    B,A
//    LDD     #$__
//    LEAS    1,S
//    ADDB    ,S+
// This can be replaced with ADDB #$__.
//
bool
ASMText::pushLoadDiscardAdd(size_t index) const
{
    if (index + 3 >= elements.size())  // pattern has 4 instructions
        return false;
    return    isInstr(index, "PSHS", "B,A")
           && isInstrWithImmedArg(index + 1, "LDD")
           && isInstr(index + 2, "LEAS", "1,S")
           && isInstr(index + 3, "ADDB", ",S+");
}


// Check for this pattern:
//    PSHS    B
//    LDB     immediate/,U/,PCR
//    ADDB    ,S+
//
bool
ASMText::pushBLoadAdd(size_t index) const
{
    if (index + 2 >= elements.size())  // pattern has 3 instructions
        return false;
    return     isInstr(index, "PSHS", "B")
            && isInstrWithVarArg(index + 1, "LDB")
            && isInstr(index + 2, "ADDB", ",S+");
}


// Check for this pattern:
//    PSHS    B,A
//    LDD     ____
//    ADDD    ,S++
//
bool
ASMText::pushDLoadAdd(size_t index) const
{
    if (index + 2 >= elements.size())  // pattern has 3 instructions
        return false;
    return     isInstr(index, "PSHS", "B,A")
            && isInstrAnyArg(index + 1, "LDD")
            && isInstr(index + 2, "ADDD", ",S++");
}


// Check for this pattern:
//    PSHS    B,A
//    LDD     immediate/,U/,PCR
//    LDX     ,S++
//
bool
ASMText::pushLoadDLoadX(size_t index) const
{
    if (index + 2 >= elements.size())  // pattern has 3 instructions
        return false;
    return     isInstr(index, "PSHS", "B,A")
            && (isInstrWithVarArg(index + 1, "LDD") || isInstrWithImmedArg(index + 1, "LDD"))
            && isInstr(index + 2, "LDX", ",S++");
}


// Check for this pattern:
//    PSHS    B,A
//    LDX     immediate/,U/,PCR
//    LDD     ,S++
//
bool
ASMText::pushDLoadXLoadD(size_t index) const
{
    if (index + 2 >= elements.size())  // pattern has 3 instructions
        return false;
    return     isInstr(index, "PSHS", "B,A")
            && (isInstrWithVarArg(index + 1, "LDX") || isInstrWithImmedArg(index + 1, "LDX"))
            && isInstr(index + 2, "LDD", ",S++");
}


// Optimize two consecutive LDr instructions, where r is A, B or D,
// with no label in between. Remove the 1st load.
// r must not be X, U or S, because we could have LDX ____; LDX ,X, where
// the 1st load is used by the 2nd.
//
bool
ASMText::stripConsecutiveLoadsToSameReg(size_t &index)
{
    if (index + 1 >= elements.size())  // pattern uses 2 or 3 elements
        return false;
    Element &e = elements[index];
    if (! (e.type == INSTR && e.fields[0].find("LD") == 0 && strchr("ABD", e.fields[0][2])))  // require LD{A,B,D} instruction
        return false;

    // Check if next element is a comment or instruction.
    size_t nextInstrIndex = findNextInstrBeforeLabel(index + 1);  // skips comments, not labels
    if (nextInstrIndex == size_t(-1))
        return false;
    Element &nextInstr = elements[nextInstrIndex];

    // Require same instruction.
    if (! (nextInstr.type == INSTR && nextInstr.fields[0] == e.fields[0]))
        return false;

    // Case that can pop up
    if ((nextInstr.fields[0][2] == 'B') &&
        (nextInstr.fields[1] == "D,X" || nextInstr.fields[1] == "B,X" ||
         nextInstr.fields[1] == "[D,X]" || nextInstr.fields[1] == "[B,X]"))
      return false;

    // Optimize.
    commentOut(index, "optim: stripConsecutiveLoadsToSameReg");

    // Advance the caller's index.
    index = nextInstrIndex;

    // Indicate that the optimization was applied.
    return true;
}


// Check for this pattern:
//    STB -1,U        variable danger
//    LDB -1,U        variable danger, declared at support/color8.c:1546
// Removes the load.
// Accept comments between the two instructions.
//
bool
ASMText::storeLoad(size_t &index)
{
    const Element &e = elements[index];
    if (! (e.type == INSTR && e.fields[0].find("ST") == 0 && strchr("ABD", e.fields[0][2]) != NULL))  // require ST{A,B,D}
        return false;
    size_t nextInstrIndex = findNextInstrBeforeLabel(index + 1);  // skips comments, not labels
    if (nextInstrIndex == size_t(-1))
        return false;
    Element &nextInstr = elements[nextInstrIndex];
    if (! (nextInstr.fields[0].find("LD") == 0 && nextInstr.fields[0][2] == e.fields[0][2]))  // require LD of same register
        return false;
    if (nextInstr.fields[1] != e.fields[1])  // if not same argument
        return false;
    commentOut(nextInstrIndex, "optim: storeLoad");
    index = nextInstrIndex;
    return true;
}


// Check for this pattern:
//      LBxx foo
//      LBRA bar
// foo:
// Replace LBxx with 'LB!xx bar' and remove LBRA.
//
bool
ASMText::condBranchOverUncondBranch(size_t &index)
{
    // Require label after 2 instructions.
    if (index + 2 >= elements.size())
        return false;
    const Element &labelElement = elements[index + 2];
    if (labelElement.type != LABEL)
        return false;

    if (!isInstrAnyArg(index + 1, "LBRA") && !isInstrAnyArg(index + 1, "BRA"))  // require uncond. branch before label
        return false;

    string inverseBranchInstr;
    if (! isConditionalBranch(index, inverseBranchInstr))  // require cond. branch as 1st instr.
        return false;

    Element &condBranch = elements[index];
    if (condBranch.fields[1] != labelElement.fields[0])  // require that cond. branch jump to label
        return false;

    Element &uncondBranch = elements[index + 1];
    condBranch.fields[0] = inverseBranchInstr;
    condBranch.fields[1] = uncondBranch.fields[1];
    commentOut(index + 1, "optim: condBranchOverUncondBranch");
    return true;
}


// If 'index' is a long branch, try to convert it to a short branch.
// This is done when the target label is no farther than 28 instructions
// from the branch. Assuming at most 4 bytes per instruction, this means
// at most a 112-byte offset, which is well below the limit of 127.
// No shortening is done if inline assembly appears between the branch
// and its destination. (This optimization does not try to measure
// the machine language produced by the inline assembly.)
//
bool
ASMText::shortenBranch(size_t index)
{
    Element &e = elements[index];
    if (! (e.type == INSTR && e.fields[0].find("LB") == 0))  // require long branch
        return false;

    size_t targetLabelIndex = findLabelIndex(e.fields[1]);
    if (targetLabelIndex == size_t(-1))
        return false;  // unexpected

    size_t begin = (index <= targetLabelIndex ? index : targetLabelIndex);
    size_t end   = (index >  targetLabelIndex ? index : targetLabelIndex);
    size_t numInstr = 0;
    for (size_t i = begin; i <= end; ++i)
    {
        const Element &t = elements[i];
        if (t.type == INLINE_ASM || t.type == INCLUDE || t.type == SEPARATOR)
            return false;  // do not optimize if these are in range
        if (t.type == INSTR)
            ++numInstr;
    }
    if (numInstr > 28)
        return false;  // to far: short branch may not be able to reach

    e.fields[0].erase(0, 1);  // remove 'L'
    return true;
}


// Optimize indexing into fixed pointers. Optimize the following sequence:
//  LDD XXXX
//  TFR D,X
//  LDD YYYY
//  LEAX D,X
//
// To
//  LDX #$XXXX
//  LDD YYYY
//  LEAX D,X
//
bool
ASMText::fasterPointerIndexing(size_t index)
{
    if (index + 3 >= elements.size())  // pattern uses 4 elements
        return false;

    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "LDD"))   // require LDD
        return false;

    Element &e2 = elements[index + 1];
    if (! (e2.type == INSTR && e2.fields[0] == "TFR" &&  // require TFR D,X
           e2.fields[1] == "D,X"))
        return false;

    Element &e3 = elements[index + 2];
    if (! (e3.type == INSTR && e3.fields[0] == "LDD"))   // require LDD
        return false;

    Element &e4 = elements[index + 3];
    if (! (e4.type == INSTR && e4.fields[0] == "LEAX" && // require LEAX D,X
           e4.fields[1] == "D,X"))
        return false;

    replaceWithInstr(index, "LDX", e1.fields[1], "optim: fasterPointerIndexing");
    commentOut(index + 1);

    return true;
}


// Optimize pushing pointers onto the stack. Optimize the following sequence:
//  LEAX XXXX,U
//  TFR X,D
//  ADDD #YYYY
//  PSHS B,A
//
// To
//  LEAX #XXXX+YYYY,U
//  PSHS X
//
// Note that this assumes that the #YYYY values in the D register is not
// used later on. Testing so far has confirmed that this is a safe assumption.
bool
ASMText::fasterPointerPushing(size_t index)
{
    if (index + 3 >= elements.size())  // pattern uses 43 elements
        return false;

    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "LEAX" && // require LEAX XXXX,U
           e1.fields[1].find(",U") != string::npos))
        return false;

    Element &e2 = elements[index + 1];
    if (! (e2.type == INSTR && e2.fields[0] == "TFR" &&  // require TFR D,X
           e2.fields[1] == "X,D"))
        return false;

    Element &e3 = elements[index + 2];
    if (! (e3.type == INSTR && e3.fields[0] == "ADDD" && // require ADDD #YYYY
           e3.fields[1].find("#") == 0))
        return false;

    Element &e4 = elements[index + 3];
    if (! (e4.type == INSTR && e4.fields[0] == "PSHS" && // require PSHS B,A
           e4.fields[1] == "B,A"))
        return false;

    // Add the offset from the LEAX to the addened in the ADDD
    const string strOffset = e1.fields[1].substr(0, e1.fields[1].find(",U"));
    int offset = 0;
    if (strOffset.length() > 0) {
      if (strOffset[0] == '$') {
        offset = mystoi(strOffset.substr(1), NULL, 16);
      } else {
        offset = mystoi(strOffset, NULL, 10);
      }
    }
    if (e3.fields[1][1] == '$')
      offset += mystoi(e3.fields[1].substr(2), NULL, 16);
    else
      offset += mystoi(e3.fields[1].substr(1), NULL, 10);

    replaceWithInstr(index, "LEAX", my_to_string(offset) + ",U", "optim: fasterPointerPushing");
    replaceWithInstr(index + 1, "PSHS", "X", "optim: fasterPointerPushing");
    commentOut(index + 2, "optim: fasterPointerPushing");
    commentOut(index + 3, "optim: fasterPointerPushing");

    return true;
}


// Remove all CLR[A/B] after a CLR[A/B] but before other instructions
// that might change those registers.
//
bool
ASMText::stripExtraClrA_B(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && (e1.fields[0] == "CLRA" || e1.fields[0] == "CLRB"))) // require CLR[A/B]
        return false;

    const string &ins = e1.fields[0];
    const uint8_t mask = (ins == "CLRA") ? A : B;
    const string andInstr = (ins == "CLRA") ? "ANDA" : "ANDB";

    bool madeChanges = false;
    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if ((e.type != INSTR) && (e.type != COMMENT)) {
        break;
      } else if (e.type == INSTR && e.fields[0] == ins) {
        commentOut(index, "optim: stripExtraClrA_B");
        madeChanges = true;
      } else if (e.type == INSTR) {
        // Replace AND_ ,S+ with LEAS 1,S. Not any fater, buy opens up more optimizations
        if ((e.fields[0] == andInstr) && (e.fields[1] == ",S+")) {
          replaceWithInstr(index, "LEAS", "1,S", "optim: stripExtraClrA_B");
          madeChanges = true;
        } else {
          const InsEffects insEffects(e);
          if (isBasicBlockEndingInstruction(e) || (insEffects.written & mask))
            break;
        }
      }
    }

    return madeChanges;
}


// Remove PSHS/PULS X when the PSHS is either a PSHS B,A or PSHS X
// and there are no instructions in between that can change X.
//
bool
ASMText::stripExtraPulsX(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR &&
           (e1.fields[0] == "PSHS" &&
            (e1.fields[1] == "B,A" ||
             e1.fields[1] == "X"))))
        return false;

    // Find matching PULS X
    const size_t startIndex = index;
    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if ((e.type != INSTR) && (e.type != COMMENT)) {
        return false;
      } else if (e.type == INSTR && e.fields[0] == "PULS" && e.fields[1] == "X") {
        break;
      } else if (e.type == INSTR) {
        const InsEffects insEffects(e);
        if (isBasicBlockEndingInstruction(e) || (insEffects.written & X) ||
            e.fields[0] == "PSHS" || e.fields[0] == "PULS" || e.fields[0] == "LEAS" ||
            e.fields[1].find(",S") != string::npos) {
          return false;
        }
      }
    }
    const size_t endIndex = index;

    // Remove the PSHS
    if (e1.fields[1] == "B,A")
      replaceWithInstr(startIndex, "TFR", "D,X", "optim: stripExtraPulsX");
    else
      commentOut(startIndex, "optim: stripExtraPulsX");

    // Remove the PULS
    commentOut(endIndex, "optim: stripExtraPulsX");

    return true;
}


// Remove PSHS B/LDB ,S+ when there are no instructions in between
// that can modify the B.
//
bool
ASMText::stripExtraPushPullB(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR &&
           e1.fields[0] == "PSHS" && e1.fields[1] == "B"))
        return false;

    // Find matching LDB ,S+
    const size_t startIndex = index;
    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if ((e.type != INSTR) && (e.type != COMMENT)) {
        return false;
      } else if (e.type == INSTR && e.fields[0] == "LDB" && e.fields[1] == ",S+") {
        commentOut(index, "optim: stripExtraPushPullB");
        break;
      } else if (e.type == INSTR) {
        const InsEffects insEffects(e);
        if (isBasicBlockEndingInstruction(e) || (insEffects.written & B) ||
            e.fields[0] == "PSHS" || e.fields[0] == "PULS" || e.fields[0] == "LEAS" ||
            e.fields[1].find(",S") != string::npos) {
          return false;
        }
      }
    }
    const size_t endIndex = index;

    // Remove the PSHS and LDB
    commentOut(startIndex, "optim: stripExtraPushPullB");
    commentOut(endIndex, "optim: stripExtraPushPullB");

    return true;
}


// Changes ANDA/B #$00 to CLRA/B
//
bool
ASMText::andA_B0(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR &&
           (e1.fields[0] == "ANDA" || e1.fields[0] == "ANDB") &&
          (e1.fields[1] == "#$00")))
        return false;

    const string instr = string("CLR") + e1.fields[0].substr(3);
    replaceWithInstr(index, instr.c_str(), "", "optim: andA_B0");
    return true;
}


// Change LDD instruction after a CLRA that load only 8 bit literals
// to LDB.
//
bool
ASMText::changeLoadDToLoadB(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "CLRA")) // require CLRA
        return false;

    bool madeChanges = false;
    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if ((e.type != INSTR) && (e.type != COMMENT)) {
        break;
      } else if (e.type == INSTR && e.fields[0] == "LDD" &&
                 e.fields[1].substr(0, 2) == "#$" &&
                 e.fields[1].length() <= 4) {
        replaceWithInstr(index, "LDB", e.fields[1], "optim: changeLoadDToLoadB");
        madeChanges = true;
      } else if (e.type == INSTR) {
        const InsEffects insEffects(e);
        if (isBasicBlockEndingInstruction(e) || (insEffects.written & A)) {
          break;
        }
      }
    }

    return madeChanges;
}


// Change ADDD instruction before a CLRA to an ADDB
//
bool
ASMText::changeAddDToAddB(size_t index)
{
    if (index + 1 >= elements.size())  // pattern has 2 instructions
        return false;

    // Note that this excludes LDD #0 which is used for branching
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "ADDD" &&
           e1.fields[1].length() > 2 &&
           e1.fields[1].substr(0, 2) == "#$"))
        return false;

    // Next instruction must be CLRA
    Element &e2 = elements[index + 1];
    if (! (e2.type == INSTR && e2.fields[0] == "CLRA"))
        return false;

    const string operand = string("#$") + e1.fields[1].substr(e1.fields[1].length() - 2, 2);
    replaceWithInstr(index, "ADDB", operand.c_str(), "optim: changeAddDToAddB");

    return true;
}


// Remove PUSH A,B/LEAS 1,S when possible
//
bool
ASMText::stripPushLeas1(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "PSHS" && e1.fields[1] == "B,A"))
        return false;
    const size_t startIndex = index;

    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if ((e.type != INSTR) && (e.type != COMMENT)) {
        return false;
      } else if (e.type == INSTR &&
                 e.fields[0] == "LEAS" &&
                 e.fields[1] == "1,S") {
        replaceWithInstr(startIndex, "PSHS", "B", "optim: stripPushLeas");
        commentOut(index, "optim: stripPushLeas1");
        return true;
      } else if (e.type == INSTR) {
        const InsEffects insEffects(e);
        if (isBasicBlockEndingInstruction(e) || 
            e.fields[0] == "LBSR" || e.fields[0] == "PSHS" ||
            e.fields[0] == "PULS" || e.fields[0] == "LEAS" ||
            e.fields[1].find(",S") != string::npos) {
          return false;
        }
      }
    }

    return false;
}


// When there is a CLR[A/B] followed by a PSHS B,A and a corresponding
// OR[A/B] ,S+ or AND[A/B], S+ and no instruction that modifies [A/B],
// and no other instructions that manipulates the stack, then it is
// possible to reduce or remove the PSHS and eliminate the OR[A/B] or
// AND[A/B]
//
bool
ASMText::orAndA_B(size_t index)
{
    // Whether or not A/B are known to be zero
    bool aKnown = false, bKnown = false;

    // Start with a CLRA or CLRB
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && (e1.fields[0] == "CLRA" || e1.fields[0] == "CLRB")))
        return false;
    aKnown = (e1.fields[0] == "CLRA") ? true : false;
    bKnown = !aKnown;
    stack<pair<bool, size_t> > stack;

    for(index++; index<elements.size(); index++ && (aKnown || bKnown)) {
      Element &e = elements[index];
      if ((e.type != INSTR) && (e.type != COMMENT)) {
        return false;
      } else if (e.type == INSTR) {
        // Deal with popping off a value
        if (e.fields[0] == "LEAS" && e.fields[1] == "1,S") {
          if (stack.size() == 0)
            return false;
          stack.pop();
        }

        // Deal with [AND/OR]A ,S+
        else if ((e.fields[0] == "ANDA" || e.fields[0] == "ORA") && (e.fields[1] == ",S+") &&
            aKnown && (stack.size() > 0) && stack.top().first) {
          Element pshsElement = elements[stack.top().second];
          if (pshsElement.fields[1] == "B,A") {
            pshsElement.fields[1] = "B";
            replaceWithInstr(index, "LEAS", "1,S", "optim: orAndA_B");
            return false;
          } else {
            commentOut(stack.top().second, "optim: orAndA_B");
            commentOut(index, "optim: orAndA_B");
          }
          return true;
        // Deal with [AND/OR]A ,S+
        } else if ((e.fields[0] == "ANDB" || e.fields[0] == "ORB") && (e.fields[1] == ",S+") &&
            bKnown && (stack.size() > 0) && stack.top().first) {
          Element pshsElement = elements[stack.top().second];
          if (pshsElement.fields[1] == "B,A") {
            pshsElement.fields[1] = "B";
            replaceWithInstr(index, "LEAS", "1,S", "optim: orAndA_B");
            return false;
          } else {
            commentOut(stack.top().second, "optim: orAndA_B");
            commentOut(index, "optim: orAndA_B");
          }
          return true;
        }

        // If it is a push instruction, push current known state of A,B
        else if (e.fields[0] == "PSHS")  {
          if (e.fields[1] == "B,A") {
            stack.push(pair<bool, size_t>(bKnown, index));
            stack.push(pair<bool, size_t>(aKnown, index));
          } else if (e.fields[1] == "B") {
            stack.push(pair<bool, size_t>(bKnown, index));
          } else if (e.fields[1] == "A") {
            stack.push(pair<bool, size_t>(aKnown, index));
          } else {
            // Don't deal with other registers
            return false;
          }
        } else {
          const InsEffects insEffects(e);
          if (isBasicBlockEndingInstruction(e) || 
              e.fields[0] == "PULS" || e.fields[0] == "LEAS" ||
              e.fields[1].find(",S") != string::npos) {
            return false;
          }

          // Update the current state of A and B
          else {
            if (insEffects.written & A)
              aKnown = false;
            if (insEffects.written & B)
              bKnown = false;
            if (e.fields[0] == "CLRA")
              aKnown = true;
            if (e.fields[0] == "CLRB")
              bKnown = true;
          }
        }
      }
    }

    return false;
}


// Transforms an 8-bit LDD to CLRA followed by LDB. In some cases this makes
// it possible to optimize out the CLRA.
//
bool
ASMText::loadDToClrALoadB(size_t index)
{
    Element &e1 = elements[index];
    if (e1.type == INSTR && e1.fields[0] == "LDD" &&
        e1.fields[1].size() > 2 &&
        e1.fields[1].substr(0, 2) == "#$" &&
        e1.fields[1].find("-") == string::npos &&
        e1.fields[1].size() == 4) {
      elements[index].fields[0] = "LDB";
      Element clrA;
      clrA.type = INSTR;
      clrA.fields[0] = "CLRA";
      clrA.liveRegs = 0;
      elements.insert(elements.begin() + index, clrA);
      return true;
    }

    return false;
}


// Sometimes a constant is pushed on the stack via the A or B registers.
// Via the stack, this constant is then ADDed, ORed, ANDed or SUBed.
// When this occurs, the stack operation can be optimized away and
// the constant can be applied to the appropriate register.
//
// This optimization starts by looking for an instruction with a known
// value. If it is destroyed before being placed on a stack, then the
// optimization exits without changes. Otherwise, this optimization
// will continue to run until the end of a basic block is hit or there
// are no known constants on the stack. This optimization will keep
// track of the known constant on the stack until the point it gets
// consumed. When it is consumed, the push will be removed and the
// OP[A/B] ,S+ will be replaced with OP[A/B] #CONSTANT.
bool
ASMText::optimizeStackOperations1(size_t index)
{
    const size_t startIndex = index;
    Pseudo6809 simulator;
    bool firstInstr = true;
    bool canGoOn = true;

    do {
      const Element &e = elements[index];
      if (firstInstr && (e.type != INSTR || isBasicBlockEndingInstruction(e)))
        return false;
      firstInstr = false;

      // Only process non basic block ending instructions
      if (e.type == LABEL)
        break;
      if (e.type != INSTR)
        continue;
      if (isBasicBlockEndingInstruction(e))
        break;

      // Output the instruction
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() &&
            (simulator.pushedConstant || (simulator.regs.knownRegisters() != 0)));

    // Simulator hit an error
    if (!canGoOn) {
      return false;
    }

    // Go through each line
    for(size_t ii=startIndex; ii<index; ii++) {
      // We can only deal with lines with at least 2 references
      const size_t numRefs = simulator.indexToReferences[ii].size();
      if (numRefs < 2) continue;

      // We can only deal with lines that produce 1 constant
      const vector<PossiblyKnownVal<int> > &constantVals = simulator.indexToConstantVals[ii];
      if (constantVals.size() != 1) continue;

      // Get the index of the pshs instruction
      const vector<int> &refs = simulator.indexToReferences[ii];
      int foundPushIndex = -1;
      size_t numPushes = 0;
      for(size_t pushIndex=0; pushIndex<numRefs; pushIndex++) {
        if (elements[refs[pushIndex]].fields[0] == "PSHS") {
          numPushes++;
          foundPushIndex = refs[pushIndex];
        }
      }
      if (numPushes != 1) continue;
      Element &e1 = elements[foundPushIndex];

      // Must be 1 or 2 byte push
      const int numBytesPushed = simulator.numBytesPushedOrPulled(e1.fields[1]);
      if ((numBytesPushed < 1) || (numBytesPushed > 2))
        continue;

      // Get all the ,S+/,S++ elements
      vector<int> stackRefs;
      int numStackBytesRef = 0;
      int lowestRef = INT_MAX;
      for(size_t jj=0; jj<numRefs; jj++) {
        Element &e0 = elements[refs[jj]];
        if (e0.fields[1] == ",S") {
          return false;
        }
        if (e0.fields[1] == ",S+") {
          numStackBytesRef++;
          stackRefs.push_back(refs[jj]);
          if (refs[jj] < lowestRef)
            lowestRef = jj;
        }
        if (e0.fields[1] == ",S++") {
          numStackBytesRef += 2;
          stackRefs.push_back(refs[jj]);
          if (refs[jj] < lowestRef)
            lowestRef = jj;
        }
      }

      // The stack references must be the last items referenced
      if (numRefs - stackRefs.size() != (size_t)lowestRef)
        continue;

      // Must have 1 or 2 refs
      if ((stackRefs.size() == 0) || (stackRefs.size() > 2))
        continue;

      // The number of bytes refed must be <= number of bytes pushed
      if (numStackBytesRef > numBytesPushed)
        continue;

      // If the stack push is not B,A, then the number of bytes
      // pushed have to equal the number of bytes refed
      if ((e1.fields[1] != "B,A") && (numBytesPushed != numStackBytesRef))
        continue;

      // If the stack push is B,A and the number of bytes pushed
      // > the number of bytes refed then we have to transform
      // B,A to either B or A
      bool transformPushBAToA = false;
      bool transformPushBAToB = false;
      if ((e1.fields[1] == "B,A") && (numBytesPushed != numStackBytesRef)) {
        // If the instruction previous to lowestRef is a ,S+, we keep A.
        // If the instruction after lowestRef is a ,S+, we keep B
        const Element &eBefore = elements[refs[lowestRef]-1];
        const Element &eAfter= elements[refs[lowestRef]+1];
        transformPushBAToA = eBefore.fields[1] == ",S+";
        transformPushBAToB = eAfter.fields[1] == ",S+";
 
        // Not sure what todo when they both are stack ops or neither
        if (transformPushBAToA && transformPushBAToB) continue;
        if (!transformPushBAToA && !transformPushBAToB) continue;
      }

      // Make sure the bytes we pushed are the bytes we pull
      stack<PossiblyKnownVal<uint8_t> > pushStackState = simulator.indexToState[foundPushIndex+1].second;
      const stack<PossiblyKnownVal<uint8_t> > &pullStackState0 = simulator.indexToState[stackRefs[0]].second;
      if (pushStackState.empty() || pullStackState0.empty() ||
          pushStackState.top() != pullStackState0.top() || !pushStackState.top().known)
        continue;

      // There was a single 16-bit reference. Make sure both values
      // were constants
      if ((numStackBytesRef == 2) && (stackRefs.size() == 1)) {
        if ((pushStackState.size() < 2) ||
            (pullStackState0.size() < 2))
          continue;
        stack<PossiblyKnownVal<uint8_t> > pushStackStateCopy
          = pushStackState;
        stack<PossiblyKnownVal<uint8_t> > pullStackState0Copy 
          = pullStackState0;
        pushStackStateCopy.pop();
        pullStackState0Copy.pop();
        if (pushStackStateCopy.top() != pullStackState0Copy.top() ||
            !pushStackStateCopy.top().known)
          continue;
      }

      if (stackRefs.size() > 1) {
        const stack<PossiblyKnownVal<uint8_t> > &pullStackState1 =
          simulator.indexToState[stackRefs[1]].second;
        pushStackState.pop();
        if (pushStackState.empty() || pullStackState1.empty() ||
            pushStackState.top() != pullStackState1.top() ||
            !pushStackState.top().known)
          continue;
      }

      // We can comment out the instr at index when the number of references
      // = 1 + numStackRefs. Note that if two instructions were used to
      // generate a 16-bit value (clra; ldb), then the second instruction
      // will perform a useless load. We'll clean this up later.
      if (numRefs == (1 + stackRefs.size())) {
        Element &loadElement = elements[ii];
        const std::string targetReg =
          loadElement.fields[0].substr(loadElement.fields[0].size()-1);
        if (targetReg == "D" || numStackBytesRef != 2)
          commentOut(ii,
                     loadElement.fields[0] + " " + loadElement.fields[1] +
                       " optim: optimizeStackOperations1");
      }

      // We can either remove or transform the push
      if (transformPushBAToA) {
        e1.fields[1] = "A";
        e1.fields[2] = "optim: optimizeStackOperations1";
      } else if (transformPushBAToB) {
        e1.fields[1] = "B";
        e1.fields[2] = "optim: optimizeStackOperations1";
      } else {
        commentOut(foundPushIndex, e1.fields[0] + " " + e1.fields[1] + " optim: optimizeStackOperations1");
      }

      // Remove the stack references
      pushStackState = simulator.indexToState[foundPushIndex+1].second;
      int stackVal = pushStackState.top().val;
      if ((numStackBytesRef == 2) && (stackRefs.size() == 1)) {
        pushStackState.pop();
        stackVal = (stackVal << 8) | pushStackState.top().val;
      }
      elements[stackRefs[0]].fields[1] = string("#") + my_to_string(stackVal);
      elements[stackRefs[0]].fields[2] = "optim: optimizeStackOperations1";
      if (stackRefs.size() > 1) {
        pushStackState.pop();
        elements[stackRefs[1]].fields[1] = string("#") + my_to_string(pushStackState.top().val);
        elements[stackRefs[1]].fields[2] = "optim: optimizeStackOperations1";
      }

      return true;
    }

    return false;
}


// Sometimes an unknown value is pushed on the stack from B register followed
// by loading a constant in the B register which is subsequently ADDed, ORed or
// ANDed with the value on the stack.  When this occurs, the stack push
// operation can be optimized away and the operation can be applied directly to
// the constant.
//
// This optimization starts by looking for a PSHS B instructioni followed by a
// LOAD constant followed by an ADDB, ANDB or ORB with the stack value.
  bool
ASMText::optimizeStackOperations2(size_t index)
{
    if (index + 3 >= elements.size()) {
      return false;
    }

    // First instruction must be a PSHS
    const size_t startIndex = index;
    const Element &pshs = elements[index++];
    if (!(pshs.type == INSTR && pshs.fields[0] == "PSHS" && pshs.fields[1] == "B")) {
      return false;
    }

    // Second instruction must be a LDB #
    const Element &ldb = elements[index++];
    if (!(ldb.type == INSTR && ldb.fields[0] == "LDB" && ldb.fields[1][0] == '#')) {
      return false;
    }

    // Ignore comments, look for ADDB/ORB/ANDB ,S+
    for(Element e = elements[index]; index < elements.size(); e = elements[++index]) {
      if (e.type == COMMENT) {
        continue;
      }
      if (e.type != INSTR) {
        return false;
      }
      if ((e.fields[0] == "ADDB" || e.fields[0] == "ORB" || e.fields[0] == "ANDB") &&
          (e.fields[1] == ",S+")) {
        break;
      }
      return false;
    }

    // Make sure we did not hit the end
    if (index >= elements.size()) {
      return false;
    }

    // We can remove the PSHS, the LD and transform the last op
    Element &lastOp = elements[index];
    lastOp.fields[1] = ldb.fields[1];
    lastOp.fields[2] = "optim: optimizeStackOperations2";
    commentOut(startIndex, "optim: optimizeStackOperations2");
    commentOut(startIndex + 1, "optim: optimizeStackOperations2");

    return true;
}


// Sometimes an unknown value is pushed on the stack from D register followed
// by loading a constant in the D register which is subsequently ADDed
// with the value on the stack.  When this occurs, the stack push
// operation can be optimized away and the operation can be applied directly to
// the constant.
//
// This optimization starts by looking for a PSHS B,A instructioni followed by a
// LOAD constant followed by an ADDD.
//
// Note that this is symmteric to optimizeStackOperations2, but 16-bit. However
// it may be that this 16-bit version does not occur in practice.
  bool
ASMText::optimizeStackOperations3(size_t index)
{
    if (index + 3 >= elements.size()) {
      return false;
    }

    // First instruction must be a PSHS
    const size_t startIndex = index;
    const Element &pshs = elements[index++];
    if (!(pshs.type == INSTR && pshs.fields[0] == "PSHS" && pshs.fields[1] == "B,A")) {
      return false;
    }

    // Second instruction must be a LDD #
    const Element &ldd = elements[index++];
    if (!(ldd.type == INSTR && ldd.fields[0] == "LDD" && ldd.fields[1][0] == '#')) {
      return false;
    }

    // Ignore comments, look for ADDD ,S+
    for(Element e = elements[index]; index < elements.size(); e = elements[++index]) {
      if (e.type == COMMENT) {
        continue;
      }
      if (e.type != INSTR) {
        return false;
      }
      if (e.fields[0] == "ADDD" && e.fields[1] == ",S++") {
        break;
      }
      return false;
    }

    // Make sure we did not hit the end
    if (index >= elements.size()) {
      return false;
    }

    // We can remove the PSHS, the LD and transform the last op
    Element &lastOp = elements[index];
    lastOp.fields[1] = ldd.fields[1];
    lastOp.fields[2] = "optim: optimizeStackOperations3";
    commentOut(startIndex, "optim: optimizeStackOperations3");
    commentOut(startIndex + 1, "optim: optimizeStackOperations3");

    return true;
}


// Remove CLR[A/B] operations if A or B are already known to be zero.
bool
ASMText::removeClr(size_t index)
{
    Pseudo6809 simulator;
    bool madeChanges = false, canGoOn = false, firstInstr = true;

    do {
      const Element &e = elements[index];
      if (firstInstr && (e.type != INSTR || isBasicBlockEndingInstruction(e)))
        return false;
      firstInstr = false;

      // Only process non basic block ending instructions
      if (e.type == COMMENT)
        continue;
      if (e.type != INSTR)
        break;
      if (e.type == INSTR && isBasicBlockEndingInstruction(e))
        break;

      const string &instr = e.fields[0];
      if (instr == "CLRA" || instr == "CLRB") {
        if ((instr[3] == 'A' && simulator.regs.accum.a.known && simulator.regs.accum.a.val == 0) || 
            (instr[3] == 'B' && simulator.regs.accum.b.known && simulator.regs.accum.b.val == 0)) {
          commentOut(index, "optim: removeClr");
          madeChanges = true;
        }
      }

      // Simulate
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);

    } while(canGoOn && ++index<elements.size() && (simulator.regs.knownRegisters() != 0));

    return madeChanges;
}


// Remove AND, OR, MUL or ADD operations if we can show that 
// they will not change performance of the program.
bool
ASMText::removeAndOrMulAddSub(size_t index)
{
    Pseudo6809 simulator;
    bool madeChanges = false, canGoOn = false, firstInstr = true;

    do {
      Element &e = elements[index];
      if (firstInstr && (e.type != INSTR || isBasicBlockEndingInstruction(e)))
        return false;
      firstInstr = false;

      // Only process non basic block ending instructions
      if (e.type == COMMENT)
        continue;
      if (e.type != INSTR)
        break;
      if (e.type == INSTR && isBasicBlockEndingInstruction(e))
        break;

      // Get the preconditions
      const string &instr = e.fields[0];
      const string &oper = e.fields[1];
      const bool changesIndex = isInstrWithPreDecrOrPostIncr(index);

      int val = 0;
      if (instr == "ANDA" || instr == "ANDB") {
        if (!changesIndex &&
            ((instr[3] == 'A' && simulator.regs.accum.a.known && simulator.regs.accum.a.val == 0) || 
             (instr[3] == 'B' && simulator.regs.accum.b.known && simulator.regs.accum.b.val == 0))) {
          if (!isInstrWithPreDecrOrPostIncr(index)) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
          }
        } else if (extractConstantLiteral(e.fields[1], val)) {
          if (val == 0) {
            const string newInstr = string("CLR") + instr.substr(3);
            replaceWithInstr(index, newInstr.c_str(), "", "optim: removeAndOrMulAddSub");
            madeChanges = true;
          } else if (val == 0xff) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
          }
        }
      } else if (instr == "ORA" || instr == ("ORB")) {
        if (!changesIndex &&
            ((instr[2] == 'A' && simulator.regs.accum.a.known && simulator.regs.accum.a.val == 0xff) || 
             (instr[2] == 'B' && simulator.regs.accum.b.known && simulator.regs.accum.b.val == 0xff))) {
          if (!isInstrWithPreDecrOrPostIncr(index)) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
          }
        } else if (extractConstantLiteral(e.fields[1], val)) {
          if (val == 0xff) {
            const string newInstr = string("LD") + instr.substr(2);
            replaceWithInstr(index, newInstr.c_str(), "#$ff", "optim: removeAndOrMulAddSub");
            madeChanges = true;
          } else if (val == 0) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
          }
        }
      } else if (instr == "MUL") {
        if ((simulator.regs.accum.a.known && simulator.regs.accum.a.val == 0) || 
            (simulator.regs.accum.b.known && simulator.regs.accum.b.val == 0)) {
          commentOut(index, "optim: removeAndOrMulAddSub");
          madeChanges = true;
        }
      } else if ((instr == "ADDA") || (instr == "ADDB") || (instr == "ADDD")) {
        if (!changesIndex &&
            ((instr[3] == 'A' && simulator.regs.accum.a.known && simulator.regs.accum.a.val == 0) || 
             (instr[3] == 'B' && simulator.regs.accum.b.known && simulator.regs.accum.b.val == 0) ||
             (instr[3] == 'D' && simulator.regs.accum.dknown() && simulator.regs.accum.dval() == 0))) {
          const Element &e1 = elements[index + 1];
          if (e1.type != INSTR || !isBasicBlockEndingInstruction(e1)) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
          }
        } else if (extractConstantLiteral(e.fields[1], val)) {
          const Element &e1 = elements[index + 1];
          if (val == 0 && (e1.type != INSTR || !isBasicBlockEndingInstruction(e1))) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
          } else if (val == 0 && e1.type == INSTR && isBasicBlockEndingInstruction(e1) &&
                     simulator.regs.accum.a.known && simulator.regs.accum.a.val == 0) {
            replaceWithInstr(index, "TSTB", "", "optim: removeAndOrMulAddSub");
            madeChanges = true;
          } else if (val == 0 && e1.type == INSTR && isBasicBlockEndingInstruction(e1) &&
                     simulator.regs.accum.b.known && simulator.regs.accum.b.val == 0) {
            replaceWithInstr(index, "TSTA", "", "optim: removeAndOrMulAddSub");
            madeChanges = true;
          } 
        }
      } else if ((instr == "LEAX") && (oper == "D,X")) {
        if (simulator.regs.accum.dknown() && simulator.regs.accum.dval() == 0) {
            commentOut(index, "optim: removeAndOrMulAddSub");
            madeChanges = true;
        } else if (simulator.regs.accum.a.known && (simulator.regs.accum.a.val == 0)) {
          e.fields[0] = "ABX";
          e.fields[1] = "";
          e.fields[2] = "optim: removeAndOrMulAddSub";
          madeChanges = true;
        }
      } else if ((instr == "LEAX") && endsWith(oper, ",X") && simulator.regs.x.known)  {
          const string offsetStr = oper.substr(0, oper.size() - 2);
          if (!(offsetStr == "A" || offsetStr == "B" || offsetStr == "D")) {
            e.fields[0] = "LDX";
            e.fields[1] = "#$" + my_to_string(mystoi(offsetStr, NULL, 10) + simulator.regs.x.val, 16);
            e.fields[2] = "optim: removeAndOrMulAddSub";
            madeChanges = true;
          }
      } else if ((instr == "LDD") && extractConstantLiteral(e.fields[1], val)) {
          if ((val < 256) && simulator.regs.accum.a.known && (simulator.regs.accum.a.val == 0)) {
            e.fields[0] = "LDB";
            e.fields[2] = "optim: removeAndOrMulAddSub";
            madeChanges = true;
          }
      } else if (instr == "SEX" && simulator.regs.accum.b.known && simulator.regs.accum.b.val < 0x80) {
          commentOut(index, "optim: removeAndOrMulAddSub");
          madeChanges = true;
      } else if ((instr == "STB" || instr == "STD") && oper == ",X" && simulator.regs.x.known) {
          e.fields[1] = string("$") + my_to_string(simulator.regs.x.val, true);
          e.fields[2] = "optim: removeAndOrMulAddSub";
          madeChanges = true;
      } else if ((instr == "LDB" || instr == "LDD") && oper == ",X" && simulator.regs.x.known) {
          // Found a weird mess bug toggling HW registers, so avoid that
          if (simulator.regs.x.val < 0xff00) {
            e.fields[1] = string("$") + my_to_string(simulator.regs.x.val, true);
            e.fields[2] = "optim: removeAndOrMulAddSub";
            madeChanges = true;
          }
      }

      // Simulate
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() && (simulator.regs.knownRegisters() != 0));

    return madeChanges;
  }


bool
ASMText::optimizeLoadDX(size_t index) {
    if (index + 1 >= elements.size())  // pattern has at least 2 instructions
        return false;

    if (!isInstr(index, "LEAX", "D,X"))
        return false;
    if (!isInstr(index + 1, "LDA", ",X") && !isInstr(index + 1, "LDB", ",X") &&
        !isInstr(index + 1, "LDD", ",X"))
        return false;

    // Make sure there are no references to ,X
    for(size_t ii=index+2; ii<elements.size(); ii++) {
        const Element &e = elements[ii];
        if (e.type == COMMENT) continue;
        if (e.type != INSTR || isBasicBlockEndingInstruction(e))
            break;
        InsEffects effects(e);
        if (effects.read & X) return false;
        if (effects.written & X) break;
    }

    commentOut(index, "optimizeLoadDX");
    elements[index + 1].fields[1] = "D,X";

    return true;
}


// Pattern: LDreg; CMPreg #0; BEQ or BNE.
// Remove CMP because LD sets Z.
//
bool
ASMText::loadCmpZeroBeqOrBne(size_t index)
{
    if (index + 2 >= elements.size())  // pattern has 3 instructions
        return false;

    string ins0 = getInstr(index);
    if (ins0 != "LDB" && ins0 != "LDD")
        return false;

    string ins1 = getInstr(index + 1);
    if (ins1 != "CMPB" && ins1 != "CMPD" && ins1 != "ADDD" && ins1 != "TSTB")
        return false;
    if (ins0[ins0.length() - 1] != ins1[ins1.length() - 1])  // if not same register
        return false;
    string arg1 = getInstrArg(index + 1);
    if (ins1 != "TSTB" && arg1 != "#0")
        return false;

    string ins2 = getInstr(index + 2);
    if (ins2 != "LBEQ" && ins2 != "BEQ" && ins2 != "LBNE" && ins2 != "BNE")
        return false;

    commentOut(index + 1, "optim: loadCmpZeroBeqOrBne");
    return true;
}


// Optimize this pattern:
//    PSHS B,A; LDB ...; CLRA; LEAS 1,S; CMPB ,S+
// No need to push and discard the MSB.
//
bool
ASMText::pushWordForByteComparison(size_t index)
{
    if (index + 4 >= elements.size())  // pattern has 5 instructions
        return false;

    if (!isInstr(index, "PSHS", "B,A"))
        return false;
    if (!isInstrAnyArg(index + 1, "LDB"))
        return false;
    if (!isInstr(index + 2, "CLRA", ""))
        return false;
    if (!isInstr(index + 3, "LEAS", "1,S"))
        return false;
    if (!isInstr(index + 4, "CMPB", ",S+"))
        return false;

    replaceWithInstr(index, "PSHS", "B", "optim: pushWordForByteComparison");  // don't push useless MSB
    commentOut(index + 2, "optim: pushWordForByteComparison");  // remove CLRA
    commentOut(index + 3, "optim: pushWordForByteComparison");  // no need to pop useless byte anymore

    return true;
}


// Change TFR X,D PSHS B,A to PSHS X
//
bool
ASMText::optimizeTfrPush(size_t index)
{
    if (index + 1 >= elements.size())  // pattern has 2 instructions
        return false;
    if (! (isInstr(index, "TFR", "X,D") && isInstr(index + 1, "PSHS", "B,A")))
        return false;

    // Make sure there are no references to D
    for(size_t ii=index+3; ii<elements.size(); ii++) {
        const Element &e = elements[ii];
        if (e.type == COMMENT) continue;
        if (e.type != INSTR || isBasicBlockEndingInstruction(e))
            break;
        InsEffects effects(e);
        if (effects.read & (A | B)) return false;
        if ((effects.written & (A | B)) == (A | B)) break;
    }

    replaceWithInstr(index, "PSHS", "X", "optim: optimizeTfrPush");
    commentOut(index + 1, "optim: optimizeTfrPush");
   
    return true;
}


// Change TFR X,D OPD to OPX
//
bool
ASMText::optimizeTfrOp(size_t index)
{
    if (index + 2 >= elements.size())  // pattern has 2 instructions
        return false;
    if (! (isInstr(index, "TFR", "X,D")))
        return false;

    InsEffects effects(elements[index + 1]);
    if (!(effects.read & (A | B)))
      return false;

    const string &instr = elements[index + 1].fields[0];
    if (! (instr == "CMPD" || instr == "STD"))
      return false;

    commentOut(index, "optim: optimizeTfrOp");
    elements[index + 1].fields[0] = (instr == "CMPD") ? "CMPX" : "STX";
    elements[index + 1].fields[2] = "optim: optimizeTfrOp";

    return true;
}


// Remove Push B ... OPB ,S+ when possible
//
bool
ASMText::removePushB(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "PSHS" && e1.fields[1] == "B"))
        return false;
    const size_t startIndex = index;

    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if (e.type == COMMENT && e.type == LABEL)
        continue;
      if (e.type != INSTR || isBasicBlockEndingInstruction(e))
        return false;

      const InsEffects insEffects(e);
      if (insEffects.written & B) {
        if (e.fields[1] != ",S+") return false;
        commentOut(startIndex, "optim: removePushB");
        commentOut(index, "optim: removePushB");
        return true;
      }

      if (e.fields[0] == "PSHS" || e.fields[1].find(",S") != string::npos)
        return false; 
    }

    return false;
}


// Remove Push B ... OPB ,S+ when possible
//
bool
ASMText::optimizeLdbTfrClrb(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "LDB"))
        return false;

    vector<size_t> instrs;
    for(index++; index<elements.size() && instrs.size()<2; index++) {
      Element &e = elements[index];
      if (e.type == COMMENT || e.type == LABEL)
        continue;
      if (e.type != INSTR || isBasicBlockEndingInstruction(e))
        return false;
      instrs.push_back(index);
    }
    if (! (isInstr(instrs[0], "TFR", "B,A") &&
           isInstr(instrs[1], "CLRB", "")) )
      return false;
    
    e1.fields[0] = "LDA";
    e1.fields[2] = "optim: optimizeLdbTfrClrb";
    commentOut(instrs[0], "optim: optimizeLdbTfrClrb");

    return false;
}


// Change LDD ??? .... PSHS B,A .... LDD ,S++
// to LDD ???  .... OP ???,U
//
bool
ASMText::remove16BitStackOperation(size_t index)
{
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "LDD"))
        return false;

    // Step through the next ops until we find an op that
    // modifies D or does a PSHS B,A
    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if (e.type == COMMENT || e.type == LABEL)
        continue;
      if (e.type != INSTR || isBasicBlockEndingInstruction(e))
        return false;

      const InsEffects insEffects(e);
      if (insEffects.written & (A | B))
        return false;
      if (isInstr(index, "PSHS", "B,A"))
        break;
    }
    if (index >= elements.size())
      return false;
    const size_t pushIndex = index;

    // Step through the next ops until we find an op that
    // modifies D or does a LDD ,S++
    for(index++; index<elements.size(); index++) {
      Element &e = elements[index];
      if (e.type == COMMENT || e.type == LABEL)
        continue;
      if (e.type != INSTR || isBasicBlockEndingInstruction(e))
        return false;

      if (isInstr(index, "LDD", ",S++"))
        break;

      const InsEffects insEffects(e);
      if (insEffects.written & (A | B))
        return false;
    }
    if (index >= elements.size())
      return false;
    const size_t popIndex = index;

    // We can remove the PSHS and LDD
    commentOut(pushIndex, "optim: remove16BitStackOperation");
    commentOut(popIndex, "optim: remove16BitStackOperation");

    return false;
}


// Try to optimize post increment operations
//
bool
ASMText::optimizePostIncrement(size_t index)
{
    if (index + 5 >= elements.size())
      return false;

    // first instr must reference a stack variable
    Element &e1 = elements[index];
    if (! (e1.type == INSTR && e1.fields[0] == "LDX" &&
           endsWith(e1.fields[1], ",U")) )
        return false;

    // next instr must increment X
    Element &e2 = elements[index + 1];
    if (! ((e2.type == INSTR && e2.fields[0] == "LEAX") &&
           (e2.fields[1] == "1,X" || e2.fields[1] == "2,X")) )
        return false;

    // next instr must save X
    Element &e3 = elements[index + 2];
    if (! ((e3.type == INSTR && e3.fields[0] == "STX") &&
           (e3.fields[1] == e1.fields[1])) )
        return false;

    // next instr must decrement X by the same amount
    Element &e4 = elements[index + 3];
    if (! ((e4.type == INSTR && e4.fields[0] == "LEAX") &&
           (e4.fields[1] == (string("-") + e2.fields[1]))) )
        return false;

    // Look for instructions until we find a ,X
    const size_t startIndex = index;
    for(index += 4; index<elements.size(); index++) {
      Element &e = elements[index];
      if (e.type == COMMENT || e.type == LABEL)
        continue;
      if (e.type != INSTR || isBasicBlockEndingInstruction(e))
        return false;

      // This is the reference we are looking for
      if (e.fields[1] == ",X")
        break;

      // Watch for aliases
      if ((startsWith(e.fields[0], "LD") && !startsWith(e.fields[1], "#")) ||
          (startsWith(e.fields[0], "ST")))
        return false;

      // Make sure X does not get trashed
      const InsEffects insEffects(e);
      if (insEffects.written & X)
        return false;
    }
    if (index >= elements.size())
      return false;
    Element &e5 = elements[index];

    // The indexed instruction will reference another register. We must find
    // any instruction that modifies this register between startIndex and
    // index
    const InsEffects indexInstrEffects(e5);
    uint8_t readRegs = indexInstrEffects.read & ~X;
    vector<size_t> loadIndices;
    for(size_t ii=startIndex + 4; ii<index; ii++) {
      const Element &ee = elements[ii];
      const InsEffects eeEffects(ee);
      if ((eeEffects.written & readRegs) != 0) {
        loadIndices.push_back(ii);
      }
    }

    // Don't try to deal with situations with more than one load.
    if (loadIndices.size() > 1)
      return false;

    // Replace decrement with OP, X++ instr
    e4.fields[0] = e5.fields[0];
    e4.fields[1] = string(",X") + ((e2.fields[1] == "1,X") ? "+" : "++");
    e4.fields[2] = "optimiz: optimizePostIncrement";

    // Replace old OP, X instr with STX
    e5.fields[0] = "STX";
    e5.fields[1] = e1.fields[1];
    e5.fields[2] = "optimiz: optimizePostIncrement";

    // Either comment out or put the load instr at e2
    if (loadIndices.size() == 0)
      commentOut(startIndex + 1, "optimiz: optimizePostIncrement");
    else {
      const Element &ee = elements[loadIndices[0]];
      e2.fields[0] = ee.fields[0];
      e2.fields[1] = ee.fields[1];
      e2.fields[2] = "optimiz: optimizePostIncrement";
      commentOut(loadIndices[0], "optimiz: optimizePostIncrement");
    }

    // Comment out e3
    commentOut(startIndex + 2, "optimiz: optimizePostIncrement");

    return false;
}


// Remove operations that generate a value that does not get
// used
//
bool
ASMText::removeUselessOps(size_t index) {
    Pseudo6809 simulator;
    const size_t startIndex = index;
    size_t numInstrs = 0;
    bool firstInstr = true, canGoOn = true;
    do {
      const Element &e = elements[index];
      if (firstInstr && (e.type != INSTR || isBasicBlockEndingInstruction(e)))
        return false;
      if (firstInstr &&
          (e.fields[1].find("+") != string::npos ||
           !((e.fields[0] == "ADDD") ||
             (e.fields[0] == "ADDA") ||
             (e.fields[0] == "ADDB") ||
             (e.fields[0] == "SUBD") ||
             (e.fields[0] == "SUBA") ||
             (e.fields[0] == "SUBB") ||
             (e.fields[0] == "LDA") ||
             (e.fields[0] == "LDB") ||
             (e.fields[0] == "LDD"))))
        return false;
      firstInstr = false;

      // Don't optimize an instruction away if we reach the end of a function
      if ((e.fields[1].find("PC") != string::npos) ||
          (e.fields[0].find("LEAS") == 0)) {
        return false;
      }

      // Only process non basic block ending instructions
      if (e.type == LABEL || e.type == COMMENT)
        continue;
      if (e.type == INSTR && isBasicBlockEndingInstruction(e))
        break;
      if (e.type != INSTR)
        break;

      // Run the instruction
      numInstrs++;
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() &&
        (simulator.indexToReferences[startIndex].size() < 1));

    // There can be no instructions referencing this instruction
    if (!canGoOn || simulator.indexToReferences[startIndex].size() > 0) {
      return false;
    }

    // If index == startIndex + 1, chances are the change was just before the
    // end of a block, so it is probably needed
    if (numInstrs <= 2) {
      return false;
    }

    commentOut(startIndex, "optim: removeUselessOps");
    return true;
}


// Optimize 16-bit stack operations of the form:
//   LD[X/D] ?,U
//     ...
//   PSHS [X/B,A]
//     ...
//   OP ,S++
//
bool
ASMText::optimize16BitStackOps1(size_t index) {
    Pseudo6809 simulator;
    const size_t startIndex = index;
    size_t numInstrs = 0;
    bool firstInstr = true, canGoOn = true;
    do {
      const Element &e = elements[index];

      // First instruction has to be "LD? *,U""
      if (firstInstr && (e.type != INSTR || isBasicBlockEndingInstruction(e)))
        return false;
      if (firstInstr &&
          (e.fields[0].find("LD") != 0 || e.fields[1].find(",U") == string::npos
           || e.fields[1].find("[") == 0))
        return false;
      firstInstr = false;

      // Only process non basic block ending instructions
      if (e.type == LABEL)
        return false;
      if (e.type == COMMENT)
        continue;
      if (e.type != INSTR)
        break;
      if (isBasicBlockEndingInstruction(e))
        break;

      // Don't try to optimize when there are stores between references
      if (e.fields[0].find("ST") == 0 &&
          simulator.indexToReferences[startIndex].size() < 2) {
        return false;
      }

      // Don't try to optimize when there are bsrs
      if (e.fields[0].find("BSR") <= 2) {
        return false;
      }

      // Run the instruction
      numInstrs++;
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() &&
            (simulator.indexToReferences[startIndex].size() < 3));

    // Simulator hit a problem
    if (!canGoOn) {
      return false;
    }

    // We can only handle two references
    if (simulator.indexToReferences[startIndex].size() != 2) {
      return false;
    }

    // The first reference must be a PSHS [X|B,A]
    const string &targetReg = elements[startIndex].fields[0].substr(2);
    Element &pshs = elements[simulator.indexToReferences[startIndex][0]];
    if (pshs.fields[0] != "PSHS" ||
        !((pshs.fields[1] == "X" && targetReg == "X") ||
          (pshs.fields[1] == "B,A" && targetReg == "D"))) {
      return false;
    }

    // The second reference must be OP ,S++
    Element &op = elements[simulator.indexToReferences[startIndex][1]];
    if (op.fields[1] != ",S++") {
      return false;
    }

    // Make sure that no instructions between startIndex and PSHS write
    // A or B
    if (targetReg == "D") {
      for (int ii = startIndex + 1;
           ii<simulator.indexToReferences[startIndex][0];
           ii++) {
        InsEffects effects(elements[ii]);
        if (effects.written & (A | B))
          return false;
      }
    }

    // OP can directly refernce the LD value
    op.fields[1] = elements[startIndex].fields[1];
    op.fields[2] = "optim: optimize16BitStackOps1";

    // We can comment out the load value and pshs
    commentOut(startIndex, "optim: optimize16BitStackOps1");
    commentOut(simulator.indexToReferences[startIndex][0],
              "optim: optimize16BitStackOps1");

    return true;
}


// Optimize 16-bit stack operations of the form:
//   LDD ?
//   PSHS B,A
//   LDD ??
//   [ADDD/SUBD/CMPD] ,S++
//
//   to
//   LDD ??
//   [ADDD/SUBD/CMPD] ,S++
//
bool
ASMText::optimize16BitStackOps2(size_t index) {
    if (index + 4 >= elements.size()) {
      return false;
    }

    Element &ldd1 = elements[index];
    if (ldd1.type != INSTR || ldd1.fields[0] != "LDD" ||
        ldd1.fields[1].find(",S") != string::npos ||
        ldd1.fields[1].find(",PC") != string::npos ||
        ldd1.fields[1].find(",X") != string::npos) {
      return false;
    }

    Element &pshs = elements[index + 1];
    if (pshs.type != INSTR || pshs.fields[0] != "PSHS" ||
        pshs.fields[1] != "B,A") {
      return false;
    }

    size_t ii = index + 2;
    for(; ii<elements.size(); ii++) {
        Element &e = elements[ii];
        if (e.type == COMMENT || e.type == LABEL) {
          continue;
        }
        if (e.type != INSTR) {
          return false;
        }

        if (e.fields[0] == "LDD") {
          break;
        }

        // Pretty much anything that does not read or write 
        // D or S or does a store is OK 
        InsEffects effects(e);
        if (((effects.written & (A | B)) != 0) ||
            ((effects.read & (A | B)) != 0) ||
            startsWith(e.fields[0], "ST") ||
            e.fields[1].find(",S") != string::npos) {
          return false;
        }
    }

    Element &ldd2 = elements[ii];
    if (ldd2.type != INSTR || ldd2.fields[0] != "LDD" ||
        ldd2.fields[1].find("D,") != string::npos ||
        ldd2.fields[1].find(",S") != string::npos) {
      return false;
    }

    Element &op = elements[ii + 1];
    if ((op.type != INSTR || op.fields[1] != ",S++") ||
        !(op.fields[0] == "ADDD" || op.fields[0] == "SUBD" ||
          op.fields[0] == "CMPD")) {
      return false;
    }

    op.fields[1] = ldd1.fields[1];
    op.fields[2] = "optim: optimize16BitStackOps2";
    commentOut(index, "optim: optimize16BitStackOps2");
    commentOut(index + 1, "optim: optimize16BitStackOps2");

    return true;
}


// Optimize 8-bit stack operations of the form:
//   LD[A/B] ?,U
//     ...
//   PSHS [A/B]
//     ...
//   OP ,S+
//
bool
ASMText::optimize8BitStackOps(size_t index) {
    Pseudo6809 simulator;
    const size_t startIndex = index;
    size_t numInstrs = 0;
    bool firstInstr = true, canGoOn = true;
    do {
      const Element &e = elements[index];

      // First instruction has to be "LD? *,U""
      if (firstInstr && (e.type != INSTR || isBasicBlockEndingInstruction(e)))
        return false;
      if (firstInstr &&
          (e.fields[0].find("LD") != 0 || e.fields[1].find(",U") == string::npos
           || e.fields[1].find("[") == 0))
        return false;
      firstInstr = false;

      // Only process non basic block ending instructions
      if (e.type == LABEL)
        return false;
      if (e.type == COMMENT)
        continue;
      if (e.type == INSTR && isBasicBlockEndingInstruction(e))
        break;
      if (e.type != INSTR)
        break;

      // Don't try to optimize when there are stores between references
      if (e.fields[0].find("ST") == 0 &&
          simulator.indexToReferences[startIndex].size() < 2) {
        return false;
      }

      // Don't try to optimize when there are bsrs
      if (e.fields[0].find("BSR") <= 2) {
        return false;
      }

      // Run the instruction
      numInstrs++;
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() &&
            (simulator.indexToReferences[startIndex].size() < 3));

    // Simulator hit a problem
    if (!canGoOn) {
      return false;
    }

    // We can only handle two references
    if (simulator.indexToReferences[startIndex].size() != 2) {
      return false;
    }

    // The first reference must be a PSHS [A/B]
    Element &pshs = elements[simulator.indexToReferences[startIndex][0]];
    if (pshs.fields[0] != "PSHS" ||
        !(pshs.fields[1] == "A" || pshs.fields[1] == "B" || pshs.fields[1] == "B,A")) {
      return false;
    }

    // The second reference must be OP ,S+
    Element &op = elements[simulator.indexToReferences[startIndex][1]];
    if (op.fields[1] != ",S+") {
      return false;
    }

    // OP can directly reference the LD value. The tricky thing is that if
    // the original load is the D register but the PSHS is on the B register
    // we have to bump the index by one.
    const string &targetReg = elements[startIndex].fields[0].substr(2);
    if (targetReg == "D" && pshs.fields[1] == "B") {
      size_t commaIndex = elements[startIndex].fields[1].find(",");
      if (commaIndex == string::npos) {
        return false;
      }
      int offset = mystoi(elements[startIndex].fields[1].substr(0, commaIndex),
                          NULL, 10);
      if (offset >= 0) {
        return false;
      }
      offset++;
      op.fields[1] = my_to_string(offset, false)
                   + elements[startIndex].fields[1].substr(commaIndex);
    } else {
    op.fields[1] = elements[startIndex].fields[1];
    }
    op.fields[2] = "optim: optimize8BitStackOps";

    // We can comment out the load value and possibly the pshs
    commentOut(startIndex, "optim: optimize8BitStackOps");
    if (pshs.fields[1] == "B,A") {
      pshs.fields[1] = (targetReg == "A") ? "B" : "A";
      pshs.fields[2] = "optim: optimize8BitStackOps";
    } else {
      commentOut(simulator.indexToReferences[startIndex][0],
                 "optim: optimize8BitStackOps");
    }

    return true;
}


//  When possible, replace
//   LDD ?
//   TFR D,X
//
//  With
//   LDX ?
//
bool
ASMText::removeTfrDX(size_t index) {
    if (index + 2 >= elements.size())
      return false;

    Pseudo6809 simulator;
    const size_t startIndex = index;

    Element &e1 = elements[index];
    if (e1.type != INSTR || e1.fields[0] != "LDD")
      return false;
    Element &e2 = elements[index + 1];
    if (e2.type != INSTR || e2.fields[0] != "TFR" || e2.fields[1] != "D,X")
      return false;

    size_t numInstrs = 0;
    bool canGoOn = true;
    do {
      const Element &e = elements[index];

      // Only process non basic block ending instructions
      if (e.type == LABEL || e.type == COMMENT)
        continue;
      if (e.type == INSTR && isBasicBlockEndingInstruction(e))
        break;
      if (e.type != INSTR)
        break;

      // Don't try to optimize when there are bsrs
      if (e.fields[0].find("BSR") <= 2) {
        return false;
      }

      // Run the instruction
      numInstrs++;
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() &&
            (simulator.indexToReferences[startIndex].size() < 2));

    // Simulator hit a problem
    if (!canGoOn) {
      return false;
    }

    // We can only handle one reference to D
    if (simulator.indexToReferences[startIndex].size() != 1) {
      return false;
    }

    // Transform the LDD to LDX and remove TFR
    e1.fields[0] = "LDX";
    e1.fields[2] = "optim: removeTfrDX";
    commentOut(startIndex + 1, "optim: removeTfrDX");

    return true;
}


//  When possible, remove repeated
//   LEAX ?,U
//
bool
ASMText::removeUselessLeax(size_t index) {
    Element &e = elements[index];
    if (!(e.fields[0] == "LEAX" && e.fields[1].find(",U") != string::npos))
      return false;

    size_t numChanges = 0;
    for(index++; index<elements.size(); index++) {
        Element &e1 = elements[index];
        if (e1.type == COMMENT)
            continue;
        if (e1.type != INSTR || isBasicBlockEndingInstruction(e1))
            break;

        InsEffects effects(e1);
        if (e1.fields[0] == e.fields[0] && e1.fields[1] == e.fields[1]) {
            commentOut(index, "optim: removeUselessLeax");
            numChanges++;
            continue;
        }

        if (effects.written & X)
            break;
    }

    return numChanges > 0;
}


//  When possible, remove repeated
//   LDX ?,U
//
bool
ASMText::removeUselessLdx(size_t index) {
    Element &e = elements[index];
    if (!((e.fields[0] == "LDX" || e.fields[0] == "STX") &&
          e.fields[1].find(",U") != string::npos))
      return false;

    size_t numChanges = 0;
    for(index++; index<elements.size(); index++) {
        Element &e1 = elements[index];
        if (e1.type == COMMENT)
            continue;
        if (e1.type != INSTR || isBasicBlockEndingInstruction(e1))
            break;

        // The value could change as a result of the STORE
        if (e1.fields[0].find("ST") == 0)
          break;

        InsEffects effects(e1);
        if (e1.fields[0] == "LDX" && e1.fields[1] == e.fields[1]) {
            commentOut(index, "optim: removeUselessLdx");
            numChanges++;
            continue;
        }

        if (effects.written & X)
            break;
    }

    return numChanges > 0;
}


//  When possible, remove unused LEAX
//
bool
ASMText::removeUnusedLoad(size_t index) {
    if (index + 2 >= elements.size())
      return false;

    Pseudo6809 simulator;
    const size_t startIndex = index;

    Element &e1 = elements[index];
    if (!(e1.type == INSTR &&
         ((e1.fields[0] == "LEAX") ||
          (e1.fields[0].find("LD") == 0 &&
           e1.fields[1].find("#") == 0))))
      return false;

    bool canGoOn = true;
    size_t numInstrs = 0;
    do {
      const Element &e = elements[index];

      // Only process non basic block ending instructions
      if (e.type == LABEL || e.type == COMMENT)
        continue;

      if (e.type == INSTR && isBasicBlockEndingInstruction(e)) {
        // Loads followed almost immediately by a branch are loading a value
        // that is likely required by the subsequent block. Disable the
        // optimization for this case
        if (index <= startIndex + 2)
          return false;
        break;
      }

      if (e.type != INSTR)
        break;

      // Don't try to optimize when there are bsrs
      if (e.fields[0].find("BSR") <= 2) {
        return false;
      }

      // Run the instruction
      numInstrs++;
      canGoOn &= simulator.process(e.fields[0], e.fields[1], (int)index, true);
    } while(++index<elements.size() &&
            (simulator.indexToReferences[startIndex].size() < 1));

    // Simulator hit a problem
    if (!canGoOn) {
      return false;
    }

    // Do not allow any references to the load
    if (simulator.indexToReferences[startIndex].size() > 0) {
      return false;
    }

    // If the instruction is a LOAD and there have been only 2
    // INSTRs, don't try this.
    if (e1.fields[0].find("LD") == 0 && numInstrs <= 2) {
      // Give a little extra leeway for LDX
      if (!(e1.fields[0] == "LDX" && numInstrs >= 2))
        return false;
    }

    // Transform the LDD to LDX and remove TFR
    commentOut(startIndex, "optim: removeUnusedLoad");
    return true;
}


// Remove TSTB in the following scenario
//  ANDB ???
//  TSTB
//
bool
ASMText::optimizeAndbTstb(size_t index) {
    const Element &e1 = elements[index];
    if (e1.fields[0] != "ANDB")
      return false;
    const Element &e2 = elements[index + 1];
    if (e2.fields[0] != "TSTB")
      return false;
    commentOut(index + 1, "optim: optimizeAndbTstb");
    return true;
}


// Optimize the following when possible:
//  LDX ?,U
//  LD? ,X
// To
//  LD? [?,U]
// When there are no other references to X
bool
ASMText::optimizeIndexedX(size_t index) {
    if (index + 2 >= elements.size())
      return false;

    Pseudo6809 simulator;
    const size_t startIndex = index;

    // index must point to LDX ?,U, but not LDX [?,U].
    Element &e1 = elements[index];
    if (!(e1.type == INSTR && e1.fields[0] == "LDX" &&
         e1.fields[1].find(",U") != string::npos &&
         e1.fields[1].find("[") == string::npos))
      return false;

    // index + 1 must point to LD? ,X.
    Element &e2 = elements[index + 1];
    if (!(e2.type == INSTR && e2.fields[0].find("LD") == 0 &&
         e2.fields[1] == ",X"))
      return false;

    size_t numInstrs = 0;
    bool canGoOn = true;
    do {
      const Element &e = elements[index];

      // Only process non basic block ending instructions
      if (e.type == LABEL || e.type == COMMENT)
        continue;
      if (e.type != INSTR)
        break;

      // Don't try to optimize when there are bsrs
      if (e.fields[0].find("BSR") <= 2) {
        return false;
      }

      if (isBasicBlockEndingInstruction(e))
        break;

      if (index >= startIndex + 2) {
        InsEffects effects(e);
        if (effects.written & X) {
          break;
        }
        if (effects.read & X) {
          return false;
        }
      }

      // Run the instruction
      numInstrs++;
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);
    } while(canGoOn && ++index<elements.size() &&
            (simulator.indexToReferences[startIndex].size() < 2));

    // We can only handle one reference to X
    if (!canGoOn || simulator.indexToReferences[startIndex].size() != 1) {
      return false;
    }

    e2.fields[1] = string("[") + e1.fields[1] + string("]");
    e2.fields[2] = "optim: optimizeIndexedX";
    commentOut(startIndex, "optim: optimizeIndexedX");

    return true;
}


// Optimize the following when possible:
//  LEAX ?,U
//  LD? ,X
// To
//  LD? ?,U
// When there are no other references to X
bool
ASMText::optimizeIndexedX2(size_t index) {
    if (index + 2 >= elements.size())
      return false;

    Pseudo6809 simulator;
    const size_t startIndex = index;

    Element &e1 = elements[index];
    if (!(e1.type == INSTR && e1.fields[0] == "LEAX" &&
         e1.fields[1].find(",U") != string::npos))
      return false;
    Element &e2 = elements[index + 1];
    if (!(e2.type == INSTR && e2.fields[0].find("LD") == 0 &&
         e2.fields[1] == ",X"))
      return false;

    size_t numInstrs = 0;
    bool canGoOn = true;
    do {
      const Element &e = elements[index];

      // Only process non basic block ending instructions
      if (e.type == LABEL || e.type == COMMENT)
        continue;
      if (e.type == INSTR && isBasicBlockEndingInstruction(e))
        break;
      if (e.type != INSTR)
        return false;

      if (index >= startIndex + 2) {
        InsEffects effects(e);
        if (effects.written & X) {
          break;
        }
        if (effects.read & X) {
          return false;
        }
      }

      // Don't try to optimize when there are bsrs
      if (e.fields[0].find("BSR") <= 2) {
        return false;
      }

      // Run the instruction
      numInstrs++;
      canGoOn = simulator.process(e.fields[0], e.fields[1], (int)index);

    } while(canGoOn && ++index<elements.size() &&
            (simulator.indexToReferences[startIndex].size() < 2));

    // We can only handle one reference to X
    if (!canGoOn || simulator.indexToReferences[startIndex].size() != 1) {
      return false;
    }

    e2.fields[1] = e1.fields[1];
    e2.fields[2] = "optim: optimizeIndexedX2";
    commentOut(startIndex, "optim: optimizeIndexedX2");

    return true;
}


//  When possible, remove repeated
//   LDB ?,U
//
bool
ASMText::removeUselessLdb(size_t index) {
    Element &e = elements[index];
    if (!((e.fields[0] == "LDB" || e.fields[0] == "STB") &&
          e.fields[1].find(",U") != string::npos))
      return false;

    size_t numChanges = 0;
    for(index++; index<elements.size(); index++) {
        Element &e1 = elements[index];
        if (e1.type == COMMENT)
            continue;
        if (e1.type != INSTR || isBasicBlockEndingInstruction(e1))
            break;

        // The value could change as a result of the STORE
        if (e1.fields[0].find("ST") == 0)
          break;

        // If e1 loads same thing as e:
        InsEffects effects(e1);
        if (e1.fields[0] == "LDB" && e1.fields[1] == e.fields[1]) {
            string inverse;
            if (!isConditionalBranch(index + 1, inverse)) {
              commentOut(index, "optim: removeUselessLdb");
              numChanges++;
              continue;
            }
        }

        if (effects.written & B)
            break;
    }

    return numChanges > 0;
}


//  When possible, remove repeated
//   LDD ?,U
//
bool
ASMText::removeUselessLdd(size_t index) {
    Element &e = elements[index];
    if (!((e.fields[0] == "LDD" || e.fields[0] == "STD") &&
          e.fields[1].find(",U") != string::npos))
      return false;

    size_t numChanges = 0;
    for(index++; index<elements.size(); index++) {
        Element &e1 = elements[index];
        if (e1.type == COMMENT)
            continue;
        if (e1.type != INSTR || isBasicBlockEndingInstruction(e1))
            break;

        // The value could change as a result of the STORE
        if (e1.fields[0].find("ST") == 0)
          break;

        // If e1 loads same thing as e:
        InsEffects effects(e1);
        if (e1.fields[0] == "LDD" && e1.fields[1] == e.fields[1]) {
            string inverse;
            if (!isConditionalBranch(index + 1, inverse)) {
              commentOut(index, "optim: removeUselessLdd");
              numChanges++;
              continue;
            }
        }

        if (effects.written & (A | B))
            break;
    }

    return numChanges > 0;
}


//  Transform 
//   LDD
//   PSHS B,A
//   LDD
//   PSHS B,A
//
//   to
//
//   LDX
//   PSHS X
//   LDD
//   PSHS B,A
//
bool
ASMText::transformPshsDPshsD(size_t index) {
    // Needs 4 elements
    if (index + 4 >= elements.size()) {
      return false;
    }

    // Make sure the first 4 instructions fit the pattern
    Element &e1 = elements[index];
    Element &e2 = elements[index + 1];
    const Element &e3 = elements[index + 2];
    const Element &e4 = elements[index + 3];
    if (e1.type != INSTR || e1.fields[0] != "LDD") {
      return false;
    }
    if (e2.type != INSTR || e2.fields[0] != "PSHS" || e2.fields[1] != "B,A") {
      return false;
    }
    if (e3.type != INSTR || e3.fields[0] != "LDD" ||
        e3.fields[1].find("D,") != string::npos ||
        e3.fields[1].find("B,") != string::npos) {
      return false;
    }
    if (e4.type != INSTR || e4.fields[0] != "PSHS" || e4.fields[1] != "B,A") {
      return false;
    }

    // Make sure no subsequent instructions read X before we hit
    // the end of the basic block or X is written
    for(index = index + 4; index < elements.size(); index++) {
      Element &e = elements[index];
      if (e.type == COMMENT) {
        continue;
      }
      if (e.type != INSTR) {
        return false;
      }
      InsEffects effects(e);
      if (effects.written & X) {
        break;
      }
      if (effects.read & X) {
        return false;
      }
    }

    // Transform the first instruction to use X. This will will help us to
    // remove a PSHS later on
    e1.fields[0][e1.fields[0].size() - 1] = 'X';
    e1.fields[2] = "optim: transformPshsDPshsD";
    e2.fields[1] = 'X';
    e2.fields[2] = "optim: transformPshsDPshsD";

    return true;
}


//  Transform 
//   LDX/LEAX
//   PSHS X
//   LDX/LEAX
//   PSHS X
//   (where the 2nd load does not itself read from X)
//
//   to
//
//   LDX/LEAY
//   PSHS Y
//   LD/LEAX
//   PSHS X
//
bool
ASMText::transformPshsXPshsX(size_t index) {
    // Does not work with OS-9 because the Y register points to the global data.
    if (TranslationUnit::instance().getTargetPlatform() == OS9) {
      return false;
    }

    // Needs 4 elements
    if (index + 4 >= elements.size()) {
      return false;
    }

    // Make sure the first 4 instructions fit the pattern
    Element &e1 = elements[index];
    Element &e2 = elements[index + 1];
    const Element &e3 = elements[index + 2];
    const Element &e4 = elements[index + 3];
    if (e1.type != INSTR || !(e1.fields[0] == "LDX" || e1.fields[0] == "LEAX")) {
      return false;
    }
    if (e2.type != INSTR || e2.fields[0] != "PSHS" || e2.fields[1] != "X") {
      return false;
    }
    if (e3.type != INSTR || !(e3.fields[0] == "LDX" || e3.fields[0] == "LEAX")
        || e3.fields[1].find(",X") != string::npos) {
      return false;
    }
    if (e4.type != INSTR || e4.fields[0] != "PSHS" || e4.fields[1] != "X") {
      return false;
    }

    // Transform the first instruction to use Y. These take more space usually
    // but will allow us to remove a PSHS later on
    e1.fields[0][e1.fields[0].size() - 1] = 'Y';
    e1.fields[2] = "optim: transformPshsXPshsX";
    e2.fields[1][e2.fields[1].size() - 1] = 'Y';
    e2.fields[2] = "optim: transformPshsXPshsX";

    return true;
}


//  Optimize
//   LDY/LEAY
//   PSHS Y
//   LDX/LEAX
//   PSHS X
//   LDD
//   PSHS B,A
//
//   to
//
//   LDY/LEAY
//   LDX/LEAX
//   LDD
//   PSHS Y,X,B,A
//
bool
ASMText::optimizePshsOps(size_t index) {
    vector<int> pshsIndices;

    // First element has to be an instruction
    Element e = elements[index++];
    if (e.type != INSTR)
      return false;

    // Look for LDY/LEAY followed by PSHS Y
    bool pshsY = false;
    if (e.fields[0] == "LDY" || e.fields[0] == "LEAY") {
      e = elements[index++];

      if (e.type == INSTR && e.fields[0] == "PSHS" && e.fields[1] == "Y") {
        pshsIndices.push_back(index - 1);
        pshsY = true;
        e = elements[index++];
      }
    }

    // Look for LDX/LEAX followed by PSHS X
    bool pshsX = false;
    if (e.type == INSTR && (e.fields[0] == "LDX" || e.fields[0] == "LEAX") &&
        e.fields[1].find(",S") == string::npos) {
      e = elements[index++];

      if (e.type == INSTR && e.fields[0] == "PSHS" && e.fields[1] == "X") {
        pshsIndices.push_back(index - 1);
        pshsX = true;
        e = elements[index++];
      }
    }

    // Should not happen   
    if (pshsY && !pshsX) {
      return false;
    }

    // Look for CLRA/CLRB/LDA/LDB/LDD followed by PSHS B,A 
    bool pshsD = false;
    if (e.type == INSTR &&
        (e.fields[0] == "CLRA" || e.fields[0] == "CLRB" ||
         e.fields[0] == "LDA" || e.fields[0] == "LDB" || e.fields[0] == "LDD") &&
        e.fields[1].find(",S") == string::npos) {
      e = elements[index++];

      // Next instruction may be another CLRA/CLRB/LDA/LDB/LDDD
      if (e.type == INSTR && e.fields[0] != "PSHS") {
        if ((e.fields[0] == "CLRA" || e.fields[0] == "CLRB" ||
             e.fields[0] == "LDA" || e.fields[0] == "LDB" || e.fields[0] == "LDD") &&
            e.fields[1].find(",S") == string::npos) {
          e = elements[index++];
        } else {
          return false;
        }
      }

      if (e.type == INSTR && e.fields[0] == "PSHS" && e.fields[1] == "B,A") {
        pshsIndices.push_back(index - 1);
        pshsD = true;
        e = elements[index++];
      }
    }

    // Only worth doing if there are at least 2 Pushes
    if (pshsIndices.size() < 2) {
      return false;
    }

    // Generate the new PSHS instruction
    string regsToPush = (pshsY) ? ",Y" : "";
    regsToPush += (pshsX) ? ",X" : "";
    regsToPush += (pshsD) ? ",B,A" : "";
    regsToPush = regsToPush.substr(1);
    Element &pshs = elements[pshsIndices[pshsIndices.size() - 1]];
    pshs.fields[1] = regsToPush;
    pshs.fields[2] = "optim: optimizePshsOps";

    // Comment out the old pshs instructions
    for(size_t ii = 0; ii < (pshsIndices.size() - 1); ii++) {
      commentOut(pshsIndices[ii], "optim: optimizePshsOps");
    }

    return true;
}


//  Optimize
//   PSHS B,A
//   LDD ?,U
//   CMPD ,S++
//   [L]B?? ?
//
//  To
//   LDD ?,U
//   CMPD ?,U
//   inverse([L]B??) ?
//
bool
ASMText::optimize16BitCompares(size_t index) {
    if (index + 4 >= elements.size()) {
      return false;
    }

    Element &pshs = elements[index];
    if (pshs.type != INSTR || pshs.fields[0] != "PSHS" ||
        pshs.fields[1] != "B,A") {
      return false;
    }

    Element &ldd = elements[index + 1];
    if (ldd.type != INSTR || ldd.fields[0] != "LDD" ||
        !endsWith(ldd.fields[1], ",U")) {
      return false;
    }

    Element &cmpd = elements[index + 2];
    if (cmpd.type != INSTR || cmpd.fields[0] != "CMPD" ||
        cmpd.fields[1] != ",S++") {
      return false;
    }

    string invertedOperandsBranchInstr;
    if (!isRelativeSizeConditionalBranch(index + 3, invertedOperandsBranchInstr)) {
      return false;
    }
    Element &branch = elements[index + 3];

    commentOut(index, "optim: optimize16BitCompares");
    cmpd.fields[1] = ldd.fields[1];
    cmpd.fields[2] = "optim: optimize16BitCompares";
    commentOut(index + 1, "optim: optimize16BitCompares");
    branch.fields[0] = invertedOperandsBranchInstr;
    branch.fields[2] = "optim: optimize16BitCompares";

    return true;
}


bool
ASMText::isInstr(size_t index, const char *ins, const char *arg) const
{
    const Element &e = elements[index];
    return e.type == INSTR && e.fields[0] == ins && e.fields[1] == arg;
}


bool
ASMText::isInstrAnyArg(size_t index, const char *ins) const
{
    const Element &e = elements[index];
    return e.type == INSTR && e.fields[0] == ins;
}


bool
ASMText::isInstrWithImmedArg(size_t index, const char *ins) const
{
    const Element &e = elements[index];
    return e.type == INSTR && e.fields[0] == ins && e.fields[1][0] == '#';
}


bool
ASMText::isInstrWithVarArg(size_t index, const char *ins) const
{
    const Element &e = elements[index];
    return e.type == INSTR
        && e.fields[0] == ins
        && (endsWith(e.fields[1], ",U") || endsWith(e.fields[1], ",PCR"));
}


string
ASMText::getInstr(size_t index) const
{
    const Element &e = elements[index];
    if (e.type != INSTR)
        return string();
    return e.fields[0];
}


string
ASMText::getInstrArg(size_t index) const
{
    const Element &e = elements[index];
    if (e.type != INSTR)
        return string();
    return e.fields[1];
}


const static struct
{
    const char *branchInstr;
    const char *inverseInstr;
} branchInstrTable[] =
{
    { "BCC", "BCS" },
    { "BEQ", "BNE" },
    { "BGE", "BLT" },
    { "BGT", "BLE" },
    { "BHI", "BLS" },
    { "BHS", "BLO" },
    { "BMI", "BPL" },
    { "BVC", "BVS" },
};


const static struct
{
    const char *branchInstr;
    const char *invertedOperandsInstr;
} relativeSizeBranchInstrTable[] =
{
    { "BEQ", "BEQ" },
    { "BNE", "BNE" },

    { "BGE", "BLE" },
    { "BGT", "BLT" },

    { "BHI", "BLO" },
    { "BHS", "BLS" },
};


// Determines if elements[index] is a conditional branch (short or long).
// If it is, true is returned and 'inverseBranchInstr' receives the branch
// instruction that uses the opposite condition (e.g., BEQ becomes BNE).
// Uses branchInstrTable.
//
bool
ASMText::isConditionalBranch(size_t index, string &inverseBranchInstr) const
{
    const Element &e = elements[index];
    if (e.type != INSTR)
        return false;
    const char *ins = e.fields[0].c_str();
    inverseBranchInstr.clear();
    if (ins[0] == 'L')
    {
        inverseBranchInstr = "L";
        ++ins;
    }
    if (ins[0] != 'B')
        return false;

    size_t n = sizeof(branchInstrTable) / sizeof(branchInstrTable[0]);
    for (size_t i = 0; i < n; ++i)
    {
        if (!strcmp(ins, branchInstrTable[i].branchInstr))
        {
            inverseBranchInstr += branchInstrTable[i].inverseInstr;
            return true;
        }
        if (!strcmp(ins, branchInstrTable[i].inverseInstr))
        {
            inverseBranchInstr += branchInstrTable[i].branchInstr;
            return true;
        }
    }

    return false;
}


bool
ASMText::isConditionalBranch(const char *ins)
{
    if (!ins)
        return false;

    if (toupper(ins[0]) == 'L')
        ++ins;
    if (toupper(ins[0]) != 'B')
        return false;

    size_t n = sizeof(branchInstrTable) / sizeof(branchInstrTable[0]);
    for (size_t i = 0; i < n; ++i)
    {
        if (!strcasecmp(ins, branchInstrTable[i].branchInstr))
            return true;
        if (!strcasecmp(ins, branchInstrTable[i].inverseInstr))
            return true;
    }

    return false;
}


// Checks if elements[index] appears in relativeSizeBranchInstrTable.
// If it does, true is returned and 'invertedOperandsBranchInstr' returns
// the branch instruction that is equivalent when the comparison operands
// are reversed.
// For example, if k <= n is to be replaced with n >= k, then
// { LDD k; CMPD n; BLS z } must be replaced with { LDD n; CMPD k; BHS z }.
//
bool
ASMText::isRelativeSizeConditionalBranch(size_t index, string &invertedOperandsBranchInstr) const
{
    const Element &e = elements[index];
    if (e.type != INSTR)
        return false;
    const char *ins = e.fields[0].c_str();
    invertedOperandsBranchInstr.clear();
    if (ins[0] == 'L')
    {
        invertedOperandsBranchInstr = "L";
        ++ins;
    }
    if (ins[0] != 'B')
        return false;

    size_t n = sizeof(relativeSizeBranchInstrTable) / sizeof(relativeSizeBranchInstrTable[0]);
    for (size_t i = 0; i < n; ++i)
    {
        if (!strcmp(ins, relativeSizeBranchInstrTable[i].branchInstr))
        {
            invertedOperandsBranchInstr += relativeSizeBranchInstrTable[i].invertedOperandsInstr;
            return true;
        }
        if (!strcmp(ins, relativeSizeBranchInstrTable[i].invertedOperandsInstr))
        {
            invertedOperandsBranchInstr += relativeSizeBranchInstrTable[i].branchInstr;
            return true;
        }
    }

    return false;
}


uint16_t
ASMText::extractImmedArg(size_t index) const
{
    const Element &e = elements[index];
    const char *arg = e.fields[1].c_str();
    unsigned long n;
    char *endptr;
    if (arg[1] == '$')
        n = strtoul(arg + 2, &endptr, 16);
    else
        n = strtoul(arg + 1, &endptr, 10);
    return uint16_t(n) & 0xFFFF;
}


void
ASMText::replaceWithInstr(size_t index, const char *ins, const string &arg, const string &comment)
{
    Element &e = elements[index];
    e.type = INSTR;
    e.fields[0] = ins;
    e.fields[1] = arg;
    e.fields[2] = comment;
}


// Inserts the given instruction at position 'index' in elements[]
// and pushes all elements at and after that index one position forward.
//
void
ASMText::insertInstr(size_t index, const char *ins, const string &arg, const string &comment)
{
    elements.insert(elements.begin() + index, Element());
    replaceWithInstr(index, ins, arg, comment);
}


void
ASMText::commentOut(size_t index, const string &comment)
{
    Element &e = elements[index];
    e.type = COMMENT;
    e.fields[0] = comment;
}


// Returns size_t(-1) if no instruction found before a non-instruction is found.
// Tolerates comments.
//
size_t
ASMText::findNextInstrBeforeLabel(size_t index) const
{
    for ( ; index < elements.size(); ++index)
    {
        const Element &e = elements[index];
        if (e.type == INSTR)
            return index;
        if (e.type != COMMENT)
            return size_t(-1);  // failure because found LABEL, etc. before INSTR
    }
    return size_t(-1);  // reached end of elements
}


// Returns size_t(-1) if no instruction found before an inline assembly element
// or an #include element.
// Tolerates comments.
//
size_t
ASMText::findNextInstr(size_t index) const
{
    for ( ; index < elements.size(); ++index)
    {
        const Element &e = elements[index];
        if (e.type == INSTR)
            return index;
        if (e.type == INLINE_ASM || e.type == INCLUDE || e.type == SEPARATOR)
            return size_t(-1);
    }
    return size_t(-1);  // reached end of elements
}


// Searches elements[] for a LABEL element with the given 'label'.
// Returns the index in elements[] if found, or size_t(-1) if not.
//
size_t
ASMText::findLabelIndex(const string &label) const
{
    for (vector<Element>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        if (it->type == LABEL && it->fields[0] == label)
            return size_t(it - elements.begin());
    return size_t(-1);
}


bool
ASMText::isLabel(size_t index, const string &label) const
{
    const Element &e = elements[index];
    return e.type == LABEL && e.fields[0] == label;
}


bool
ASMText::startsWith(const string &s, const char *prefix)
{
    return s.compare(0, strlen(prefix), prefix) == 0;
}


bool
ASMText::endsWith(const string &s, const char *suffix)
{
    size_t suffixLen = strlen(suffix);
    if (s.length() < suffixLen)
        return false;  // s too short
    return s.compare(s.length() - suffixLen, suffixLen, suffix) == 0;
}
    

bool
ASMText::extractConstantLiteral(const string &s, int &val) {
  if (s.find("#") != 0) return false;
  const bool isHex = s.find("$") == 1;
  val = mystoi(s.substr(isHex ? 2 : 1), NULL, isHex ? 16 : 10);
  return true;
}


bool
ASMText::isInstrWithPreDecrOrPostIncr(size_t index) const {
  const Element &e = elements[index];
  const string &op = e.fields[1];
  return (startsWith(op, ",-") || startsWith(op, "[,-") ||
          endsWith(op, "+") || endsWith(op, "+]"));
}


void
ASMText::writeElement(ostream &out, const Element &e)
{
    switch (e.type)
    {
    case INSTR:         writeIns(out, e);                 break;
    case INLINE_ASM:    writeInlineAssembly(out, e);      break;
    case LABEL:         writeLabel(out, e);               break;
    case COMMENT:       writeComment(out, e);             break;
    case SEPARATOR:     writeSeparatorComment(out, e);    break;
    case INCLUDE:       writeInclude(out, e);             break;
    case FUNCTION_START:
        out << "* FUNCTION " << e.fields[0] << "(): defined at " << e.fields[1] << "\n";
        break;
    case FUNCTION_END  :
        out << "* END FUNCTION\n";
        break;
    default: assert(!"unsupported element");
    }
}


bool
ASMText::writeFile(ostream &out)
{
    for (vector<Element>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        writeElement(out, *it);

    return out.good();
}


// Returns a comma-separated list of the registers whose bit is set
// in the given bit field, based on the private enum.
//
string
ASMText::listRegisters(uint8_t registers)
{
    stringstream ss;
    static const char *names[] =
    {
        "PC", "U", "Y", "X", "DP", "B", "A", "CC"  // bit 7 to bit 0
    };
    for (size_t i = 0; i < 8; ++i, registers <<= 1)
        if (registers & 0x80)
        {
            if (ss.tellp() > 0)
                ss << ",";
            ss << names[i];
        }
    return ss.str();
}


// Fills members 'read' and 'written' with bits representing the registers
// that are read or written by the instruction in 'e'.
// Those members remain zero if 'e' is not an instruction.
//
ASMText::InsEffects::InsEffects(const Element &e)
:   read(0), written(0)
{
    if (e.type != INSTR)
        return;

    const string &ins = e.fields[0];
    const string &arg = e.fields[1];

    bool isInlineASMIns = (e.fields[2].find(inlineASMTag) != string::npos);

    // Analyze opcode.
    //
    if (isInlineASMIns)
        read |= A | B | X | Y | U, written |= A | B | X | Y | U;  // be pessimistic
    else if (ins == "BITA" || ins == "TSTA")
        read |= A;
    else if (ins == "BITB" || ins == "TSTB")
        read |= B;
    else if (ins == "BSR" || ins == "LBSR" || ins == "JSR")
        read |= U, written = A | B | X | Y | U;
    else if (ins[0] == 'B')  // all other B instructions are conditional branches
        ;
    else if (ins == "LDD")
        written |= A | B;
    else if (ins == "LDA" || ins == "CLRA")
        written |= A;
    else if (ins == "LDB" || ins == "CLRB")
        written |= B;
    else if (ins == "LDX" || ins == "LEAX")
        written |= X;
    else if (ins == "LDY" || ins == "LEAY")
        written |= Y;
    else if (ins == "LDU" || ins == "LEAU")
        written |= U;
    else if (ins == "STD")
        read |= A | B;
    else if (ins == "STA")
        read |= A;
    else if (ins == "STB")
        read |= B;
    else if (ins == "STX")
        read |= X;
    else if (ins == "STY")
        read |= Y;
    else if (ins == "STU")
        read |= U;
    else if (ins == "SEX")
        read |= B, written |= A;
    else if (ins == "CMPD")
        read |= A | B;
    else if (ins == "CMPA")
        read |= A;
    else if (ins == "CMPB")
        read |= B;
    else if (ins == "CMPX")
        read |= X;
    else if (ins == "MUL")
        read |= A | B, written = A | B;
    else if (ins == "ADDD" || ins == "SUBD")
        read |= A | B, written |= A | B;
    else if (ins == "ADDA" || ins == "SUBA" || ins == "INCA"
            || ins == "COMA" || ins == "NEGA"
            || ins == "LSLA" || ins == "LSRA" || ins == "ASRA"
            || ins == "ROLA" || ins == "RORA"
            || ins == "ANDA" || ins == "ORA" || ins == "EORA")
        read |= A, written |= A;
    else if (ins == "ADDB" || ins == "SUBB" || ins == "INCB"
            || ins == "COMB" || ins == "NEGB"
            || ins == "LSLB" || ins == "LSRB" || ins == "ASRB"
            || ins == "ROLB" || ins == "RORB"
            || ins == "ANDB" || ins == "ORB" || ins == "EORB")
        read |= B, written |= B;
    else if (startsWith(ins, "LB"))  // long branches
        ;
    else if (ins == "PSHS")
        read |= parsePushPullArg(arg);
    else if (ins == "PULS")
        written |= parsePushPullArg(arg);
    else if (ins == "LEAS" || ins == "INC" || ins == "DEC" || ins == "CLR")
        ;
    else if (ins == "RTS" || ins == "RTI")
        ;
    else if (ins == "TFR")
        ;  // processed below
    else if (ins == "ABX")
        read = B | X, written = X;
    else
        cout << "# failed to determine registers affected by opcode of " << ins << " " << arg << endl;

    // Analyze argument.
    //
    if (isInlineASMIns)
        ;
    else if (ins == "TFR")
    {
        size_t commaPos = arg.find(',');
        assert(commaPos > 0 && commaPos < string::npos);
        read    |= parseRegName(string(arg, 0, commaPos));
        written |= parseRegName(string(arg, commaPos + 1));
    }
    else if (endsWith(arg, ",X"))
        read |= X;
    else if (endsWith(arg, ",U") || endsWith(arg, ",U]"))
        read |= U;
    else if (arg == ",X+" || arg == ",X++")
        read |= X;
    else if (arg == ",Y+" || arg == ",Y++")
        read |= Y;
    else if (arg == ",U+" || arg == ",U++")
        read |= U;
    else if (endsWith(arg, ",S") || arg == ",S+" || arg == ",S++")
        ;  // do not care about S
    else if (arg.empty() || arg[0] == '#' || arg[0] == '_' || isalpha(arg[0])
            || onlyDecimalDigits(arg)
            || (arg[0] == '$' || onlyHexDigits(arg, 1)))
        ;
    else
        cout << "# failed to determine registers affected by argument of " << ins << " " << arg << endl;
}


string
ASMText::InsEffects::toString() const
{
    stringstream ss;
    //ss << wordToString(read, true) << ", " << wordToString(written, true);
    ss << "(" << listRegisters(read) << "), (" << listRegisters(written) << ")";
    return ss.str();
}


uint8_t
ASMText::parseRegName(const string &name)
{
    switch (name.empty() ? 0 : name[0])
    {
        case 'P': return PC;
        case 'U': return U;
        case 'Y': return Y;
        case 'X': return X;
        case 'B': return B;
        case 'A': return A;
        case 'C': return CC;
        case 'D': return name.length() == 1 ? (A | B) : DP;
        default:  assert(!"unrecognized register name"); return 0;
    }
}


// Returns a bit field representation of the comma-separated list
// of register names in 'arg'.
//
uint8_t
ASMText::InsEffects::parsePushPullArg(const string &arg)
{
    uint8_t regs = 0;
    for (size_t len = arg.length(), i = 0; i < len; ++i)
    {
        switch (toupper(arg[i]))
        {
        case ',': break;
        case 'P': ++i; break;  // don't care about PC
        case 'U': regs |= U; break;
        case 'Y': regs |= Y; break;
        case 'X': regs |= X; break;
        case 'B': regs |= B; break;
        case 'A': regs |= A; break;
        case 'C': ++i; break;  // don't care about CC
        case 'D':
            if (i + 1 < len && toupper(arg[i + 1]) == 'P')
                ;  // don't care about DP
            else
                regs |= A | B;
            break;
        }
    }
    return regs;
}


bool
ASMText::InsEffects::onlyDecimalDigits(const string &s)
{
    for (size_t len = s.length(), i = 0; i < len; ++i)
        if (!isdigit(s[i]))
            return false;
    return true;
}


// Starts checking 's' of the given character offset.
// Ignores preceding characters.
//
bool
ASMText::InsEffects::onlyHexDigits(const string &s, size_t offset)
{
    for (size_t len = s.length(), i = offset; i < len; ++i)
        if (!isxdigit(s[i]))
            return false;
    return true;
}


bool
Pseudo6809::process(const string &instr, const string &operand, int index, bool ignoreStackErrors)
{
  // Excluding limited stack tracking, this does not simulate memory operations.
  // It simply assumes that all memory values are unknown
  
  // Record the current state
  indexToState[index] = make_pair(regs, stack);

  // Determine whether operand is a constant literal
  const bool operandIsConstant = operand.find("#") == 0;
  uint16_t val16 = 0;
  if (operandIsConstant) {
    const bool isHex = operand.find("$") == 1;
    val16 = (uint16_t)mystoi(operand.substr(isHex ? 2 : 1), NULL, isHex ? 16 : 10);
  }

  // Determine whether instr is a comma op that is not an indexed op
  const bool isStackOp = instr == "PSHS" || instr == "PULS" ||
                         instr == "PSHU" || instr == "PULU";
  const bool isOddCommaOp = isStackOp ||
                            instr == "TFR" || instr == "EXG";

  // Determine whether operand is indexed
  const size_t commaIndex = operand.find(",");
  const bool isIndexed = !isOddCommaOp && commaIndex != string::npos;
  const string indexReg = isIndexed ? operand.substr(commaIndex+1, 1) : "";

  // Determine whether operand is indirect
  const bool isIndirect = operand.find("[") != string::npos;

  // Determine whether operand is post increment
  const bool postIncrement1 = isIndexed && operand.find("+") != string::npos;
  const bool postIncrement2 = isIndexed && operand.find("++") != string::npos;

  // Determine whether operand is pre decrement
  const bool preDecrement1 = isIndexed && operand.find("-") != string::npos;
  const bool preDecrement2 = isIndexed && operand.find("--") != string::npos;

  // Determine whether there is an offset
  const bool hasOffset = isIndexed && ((commaIndex > 1) || (commaIndex > 0 && !isIndirect));
  const string offsetStr = operand.substr(0, commaIndex);
  const bool isConstantOffset = hasOffset && !(offsetStr == "D" || offsetStr == "A" || offsetStr == "B");
  const int offsetVal 
    = isConstantOffset ? (offsetStr[0] == '$' ? mystoi(offsetStr.substr(1), NULL, 16) 
                                              : (offsetStr[0] == '-' || isdigit(offsetStr[0])) ? mystoi(offsetStr, NULL, 10) 
                                                                                               : 0)
                       : 0;

  // Run basic stack ops
  if (isStackOp) {
    const string stackReg = instr.substr(3);
    if (instr.find("PSH") == 0)
      processPush(stackReg, operand, index);
    else
      return processPull(stackReg, operand, index);
    return true;
  }

  // Tests A or B for zero
  if (instr == "TSTA" || instr == "TSTB") {
    getVal(instr.substr(3), index);
    return true;
  }

  // This instruction adds B to X
  if (instr == "ABX") {
    getVal("B", index);
    getVal("X", index);
    addVal("X", "B", index);
    return true;
  }

  // These instructions have no dependencies or side effects
  if (instr == "CWAI" || instr == "SYNC" || 
      instr == "NOP" || instr.find("BRN") != string::npos) {
    return true;
  }

  // Thie instruction converts A into a decimal equivalent
  if (instr == "DAA") {
    PossiblyKnownVal<int> val = getVal("A", index);
    if (val.known && val.val <= 100)
      loadVal("A", PossiblyKnownVal<int>(((val.val / 10)<<4) + (val.val % 10), true, index), index);
    else
      loadVal("A", PossiblyKnownVal<int>(0, false, index), index);
    return true;
  }

  // Transfer and exchange registgers
  if (instr == "TFR" || instr == "EXG") {
    const string reg1 = operand.substr(0, commaIndex);
    const string reg2 = operand.substr(commaIndex + 1);
    getVal(reg1, index);
    if (instr == "TFR") {
      tfr(reg1, reg2, index);
    } else {
      getVal(reg2, index);
      exg(reg1, reg2, index);
    }
    return true;
  }

  // This instruction multiples AxB and puts the result in D
  if (instr == "MUL") {
    getVal("D", index);
    if ((regs.accum.a.val == 0 && regs.accum.a.known) ||
        (regs.accum.b.val == 0 && regs.accum.b.known))
      loadVal("D", PossiblyKnownVal<uint16_t>(0, true, index), index);
    else
      loadVal("D", PossiblyKnownVal<uint16_t>(regs.accum.a.val * regs.accum.b.val,
                                              regs.accum.dknown(), index), index);
    return true;
  }

  // If B >= 0x80, make A 0xFF, otherwise make it 0x00
  if (instr == "SEX") {
    PossiblyKnownVal<int> val = getVal("B", index);
    if (val.known)
      loadVal("A", PossiblyKnownVal<int>(val.val > 128 ? 0xff : 0, true, index), index);
    else
      loadVal("A", PossiblyKnownVal<int>(0, false, index), index);
  }

  // Don't bother with stack ops for now
  if (instr == "JSR" || instr == "JMP" ||
      instr.find("BRA") != string::npos ||
      instr.find("BCC") != string::npos ||
      instr.find("BCS") != string::npos ||
      instr.find("BEQ") != string::npos ||
      instr.find("BGE") != string::npos ||
      instr.find("BGT") != string::npos ||
      instr.find("BHI") != string::npos ||
      instr.find("BHS") != string::npos ||
      instr.find("BLE") != string::npos ||
      instr.find("BLO") != string::npos ||
      instr.find("BLS") != string::npos ||
      instr.find("BLT") != string::npos ||
      instr.find("BLE") != string::npos ||
      instr.find("BMI") != string::npos ||
      instr.find("BNE") != string::npos ||
      instr.find("BPL") != string::npos ||
      instr.find("BSR") != string::npos ||
      instr.find("BVC") != string::npos ||
      instr.find("BVS") != string::npos ||
      instr.find("SWI") != string::npos ||
      instr == "RTS" || instr == "RTI")
      return false;

  // Try to deal with the remaining instructions as generically as possible
  // First try to figure out the target register. If blank then this is
  // a memory op.
  string targetRegister;
  if (instr.find("OR") == 0 || instr.find("LD") == 0 || instr.find("ST") == 0)
    targetRegister = instr.substr(2);
  else
    targetRegister = instr.substr(3);

  // All instructions except LEA and LD reference targetRegister
  PossiblyKnownVal<int> lhs;
  if (! (instr.find("LD") == 0 || instr.find("LEA"))) {
    lhs = getVal(targetRegister, index);
  }

  // The RHS may be constant (immediate), indexed (possibly constant),
  // indirect indexed, direct, extended or indirect extended.
  // Make sure we ascertain the RHS as well as possible
  PossiblyKnownVal<int> rhs;
  if (operandIsConstant) {
    rhs = PossiblyKnownVal<int>(val16, true, index);
  } else if (isIndexed) {
    // Get the register value of the RHS and prep the value that the
    // rhs will point to
    rhs = getVal(indexReg, index);
    PossiblyKnownVal<int> indexVal = PossiblyKnownVal<int>(0, false, index);

    // Deal with pre decrement
    if (preDecrement1) {
      rhs = rhs - 1;
      if (indexReg == "S")
        return false;
      if (preDecrement2) {
        rhs = rhs - 1;
      }
      loadVal(indexReg, rhs, index);
    }

    // Deal with post increment
    if (!preDecrement1 && !isConstantOffset) {
      if (postIncrement1)
        rhs = rhs + 1;
      if (postIncrement2) 
        rhs = rhs + 1;
      if (postIncrement1) {
        loadVal(indexReg, rhs, index);
      } else {
        getVal(indexReg, index);
      }

      if (indexReg == "S") {
        if (stack.size() < ((postIncrement2) ? 2 : 1)) {
          if (!ignoreStackErrors)
            return false;
        }
        else if (postIncrement2)
          indexVal = pull16(index);
        else if (postIncrement1)
          indexVal = pull8(index);
        else {
          if (stack.size() < (regIs16Bit(targetRegister) ? 2 : 1)) {
            if (!ignoreStackErrors)
              return false;
          }
          indexVal = regIs16Bit(targetRegister) ? peek16(index) : peek8(index);
        }
      } else if (instr.find("LEA") != 0) {
        rhs = PossiblyKnownVal<int>(0, false, index);
      }
    }

    // Deal with constant offsets
    if (isConstantOffset)
      rhs = rhs + offsetVal;
    else if (hasOffset)
      rhs = rhs + getVal(offsetStr, index);

    // Instructions that are not LEA, load from memory
    if (instr.find("LEA") != 0)
      rhs = indexVal;

    // Indirect instructions load from memory
    rhs.known = rhs.known && !isIndirect;
  } else { // direct, extended, possibly being indirect
    rhs = PossiblyKnownVal<int>(0, false, index);
  }

  // Short cut - if there is no register than make the lhs = rhs.
  // This makes implementing instruction support easier.
  if (targetRegister == "") {
    lhs = rhs;
  }

  // ADD with carry. We don't track CC, so don't bother
  if (instr.find("ADC") == 0) {
    loadVal(targetRegister, PossiblyKnownVal<int>(0, false, index), index);
    return true;
  }

  // Performs an add
  if (instr.find("ADD") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs + rhs, index);
    return true;
  }

  // ANDs register
  if (instr.find("AND") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs & rhs, index);
    return true;
  }

  // Shifts bits left, don't bother with CC bits for now
  if (instr.find("ASL") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs.asl(), index);
    return true;
  }

  // Shifts bits right, don't bother with CC bits for now
  if (instr.find("ASR") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs.asr(), index);
    return true;
  }

  // Clears the registers or memory
  if (instr.find("CLR") == 0) {
    loadVal(targetRegister, PossiblyKnownVal<int>(0, true, index), index);
    return true;
  }

  // Compares registers or memory.
  if (instr.find("CMP") == 0) {
    getVal(targetRegister, index);
    return true;
  }

  // Complements memory or register
  if (instr.find("COM") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, ~lhs, index);
    return true;
  }

  // Decrements memory or register
  if (instr.find("DEC") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs - 1, index);
    return true;
  }

  // Exclusive OR a register
  if (instr.find("EOR") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs ^ rhs, index);
    return true;
  }

  // Increments memory or register
  if (instr.find("INC") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs + 1, index);
    return true;
  }

  // Perform a load
  if (instr.find("LD") == 0) {
    if (operandIsConstant)
      loadVal(targetRegister, rhs, index);
    else
      loadVal(targetRegister, PossiblyKnownVal<int>(0, false, index), index);
    return true;
  }

  // Shifts bits left, don't bother with CC bits for now
  if (instr.find("LSL") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs.lsl(), index);
    return true;
  }

  // Shifts bits right, don't bother with CC bits for now
  if (instr.find("LSR") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs.lsr(), index);
    return true;
  }

  // Perform an LEA
  if (instr.find("LEA") == 0) {
    // Deal with the S register specially
    if (targetRegister == "S") {
      // Avoid voodoo magic
      if (indexReg != "S")
        return false;

      // Try to deal with constant offsets here
      if (offsetVal < 0) {
        for(int ii=0; ii<-offsetVal; ii++)
          push8(PossiblyKnownVal<int>(0, false, index));
      } else {
        for(int ii=0; ii<offsetVal; ii++) {
          if (stack.empty())
            return false;
          stack.pop();
        }
      }
    } else {
      loadVal(targetRegister, rhs, index);
    }
    return true;
  }

  // Negates the given value
  if (instr.find("NEG") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, -lhs, index);
    return true;
  }

  // ORs register
  if (instr.find("OR") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs | rhs, index);
    return true;
  }

  // Can't do much here without CC bits
  if (instr.find("ROR") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, PossiblyKnownVal<int>(0, false,index), index);
    return true;
  }

  // Can't do much here without CC bits
  if (instr.find("ROL") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, PossiblyKnownVal<int>(0, false,index), index);
    return true;
  }

  // Can't do much here without CC bits
  if (instr.find("SBC") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, PossiblyKnownVal<int>(0, false,index), index);
    return true;
  }

  // The main thing here is that we referenced the registers
  if (instr.find("ST") == 0) {
    getVal(targetRegister, index);
    return true;
  }

  // Performs an sub
  if (instr.find("SUB") == 0) {
    getVal(targetRegister, index);
    loadVal(targetRegister, lhs - rhs, index);
    return true;
  }

  // Compares registers or memory. Don't bother for now
  if (instr.find("TST") == 0) {
    getVal(targetRegister, index);
    return true;
  }

  // Some unknown weirdness
  return false;
}


void
Pseudo6809::processPush(const string &stackReg, const string &operand, int index) 
{
  const bool isS = stackReg == "S";
  if (operand.find("PC") != string::npos) {
    if (isS) push16(getVal("PC", index));
    addVal(stackReg, -2, index);
  }
  if (operand.find("U") != string::npos) {
    if (isS) push16(getVal("U", index));
    addVal(stackReg, -2, index);
  }
  if (operand.find("S") != string::npos) {
    if (isS) push16(getVal("S", index));
    addVal(stackReg, -2, index);
  }
  if (operand.find("Y") != string::npos) {
    if (isS) push16(getVal("Y", index));
    addVal(stackReg, -2, index);
  }
  if (operand.find("X") != string::npos) {
    if (isS) push16(getVal("X", index));
    addVal(stackReg, -2, index);
  }
  if (operand.find("DP") != string::npos) {
    if (isS) push8(getVal("DP", index));
    addVal(stackReg, -1, index);
  }
  if (operand.find("B") != string::npos) {
    if (isS)  {
      push8(getVal("B", index));
    }
    addVal(stackReg, -1, index);
  }
  if (operand.find("A") != string::npos) {
    if (isS) {
      push8(getVal("A", index));
    }
    addVal(stackReg, -1, index);
  }
  if (operand.find("CC") != string::npos) {
    if (isS) push8(getVal("CC", index));
    addVal(stackReg, -1, index);
  }
}

bool
Pseudo6809::processPull(const string &stackReg, const string &operand, int index)
{
  const bool isS = stackReg == "S";

  if (operand.find("CC") != string::npos) {
    if (stack.empty()) return false;
    regs.setVal("CC", isS ? pull8(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 1, index);
  }
  if (operand.find("A") != string::npos) {
    if (stack.empty()) return false;
    regs.setVal("A", isS ? pull8(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 1, index);
  }
  if (operand.find("B") != string::npos) {
    if (stack.empty()) return false;
    regs.setVal("B", isS ? pull8(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 1, index);
  }
  if (operand.find("DP") != string::npos) {
    if (stack.empty()) return false;
    regs.setVal("DP", isS ? pull8(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 1, index);
  }
  if (operand.find("X") != string::npos) {
    if (stack.size() < 2) return false;
    regs.setVal("X", isS ? pull16(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 2, index);
  }
  if (operand.find("S") != string::npos) {
    if (stack.size() < 2) return false;
    regs.setVal("S", isS ? pull16(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 2, index);
  }
  if (operand.find("Y") != string::npos) {
    if (stack.size() < 2) return false;
    regs.setVal("Y", isS ? pull16(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 2, index);
  }
  if (operand.find("U") != string::npos) {
    if (stack.size() < 2) return false;
    regs.setVal("U", isS ? pull16(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 2, index);
  }
  if (operand.find("PC") != string::npos) {
    if (stack.size() < 2) return false;
    regs.setVal("PC", isS ? pull16(index) : PossiblyKnownVal<int>(0, false));
    addVal(stackReg, 2, index);
  }

  return true;
}


int
Pseudo6809::numBytesPushedOrPulled(const string &operand) {
  int sum = 0;
  if (operand.find("CC") != string::npos) sum++;
  if (operand.find("A") != string::npos) sum++;
  if (operand.find("B") != string::npos) sum++;
  if (operand.find("DP") != string::npos) sum++;
  if (operand.find("X") != string::npos) sum += 2;
  if (operand.find("S") != string::npos) sum += 2;
  if (operand.find("Y") != string::npos) sum += 2;
  if (operand.find("U") != string::npos) sum += 2;
  if (operand.find("PC") != string::npos) sum += 2;
  return sum;
}
