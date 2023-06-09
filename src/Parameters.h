/*  $Id: Parameters.h,v 1.3 2023/04/10 04:48:48 sarrazip Exp $

    CMOC - A C-like cross-compiler
    Copyright (C) 2023 Pierre Sarrazin <http://sarrazip.com/>

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

#ifndef _H_Parameters
#define _H_Parameters

#include "SwitchStmt.h"


class Parameters
{
public:

    // Argument for the ORG directive.
    // The default is 512 bytes past the default start of a Basic program
    // on a Disk Basic CoCo ($2600).
    //
    uint16_t codeAddress;
    uint16_t dataAddress;  // by default, data section follows code section
    bool codeAddressSetBySwitch;  // true if --org or --dos used
    bool dataAddressSetBySwitch;  // true if --data used

    uint16_t stackSpace;  // applies to --check-stack and sbrk(); not for OS-9
    uint16_t extraStackSpace;  // OS-9 only

    uint32_t functionStackSpace;  // uint32_t(-1) means not set by command-line argument

    std::string pkgdatadir;  // directory where CMOC support files (header files, etc.) are installed
    std::string cmocfloatlibdir;  // directory where CMOC floating-point library files and object files are installed

    std::string lwasmPath;
    std::string lwlinkPath;

    bool intermediateFilesKept;
    std::string intermediateDir;  // files where intermediate files (e.g., .lst, .i) are created;
                             // if empty, use user-specified directory

    bool generatePrerequisitesFile;      // --deps option
    bool generatePrerequisitesFileOnly;  // --deps-only option
    std::string prerequisiteFilename;  // if not empty, used instead of forming .d from .o

    bool preprocOnly;
    bool genAsmOnly;
    bool compileOnly;
    bool asmCmd;  // write asm command in a .cmd file
    bool verbose;
    bool treatWarningsAsErrors;
    bool nullPointerCheckingEnabled;
    bool stackOverflowCheckingEnabled;
    TargetPlatform targetPlatform;
    bool assumeTrack34;  // true = CoCo DECB Track 34 (relevant only with COCO_BASIC)
    std::string forcedLWLinkFormat;  // if not empty, passed to --format option of lwlink
    bool callToUndefinedFunctionAllowed;
    bool warnSignCompare;
    bool warnPassingConstForFuncPtr;
    bool isConstIncorrectWarningEnabled;
    bool isBinaryOpGivingByteWarningEnabled;
    bool isLocalVariableHidingAnotherWarningEnabled;
    bool isNonLiteralPrintfFormatWarningEnabled;
    bool isUncalledStaticFunctionWarningEnabled;
    bool isMissingFieldInitializersWarningEnabled;
    bool inlineAsmArrayIndexesWarningEnabled;
    bool forConditionComparesDifferentSizesWarningEnabled;

    bool wholeFunctionOptimization;
    bool forceJumpMode;
    SwitchStmt::JumpMode forcedJumpMode;
    size_t optimizationLevel;
    bool omitFramePointer;
    bool stackSpaceSpecifiedByCommandLine;
    uint16_t limitAddress;  // see --limit; 0xFFFF means not applicable
    bool limitAddressSetBySwitch;  // true if --limit used
    std::string outputFilename;
    std::vector<std::string> libDirs;  // list of directories to pass to lwlink via -L options
    bool useDefaultLibraries;  // if false, only libcmoc-crt-*.a is used
    bool useNativeFloatLibrary;
    bool relocatabilitySupported;

    std::list<std::string> includeDirList;
    bool searchDefaultIncludeDirs;

    std::list<std::string> defines;

    static uint32_t getVersionInteger();

public:
    Parameters()
    :   codeAddress(0x2800),  // DECB Basic program starts at 0x2601 by default
        dataAddress(0xFFFF),
        codeAddressSetBySwitch(false),
        dataAddressSetBySwitch(false),
        stackSpace(1024),
        extraStackSpace(0),
        functionStackSpace(uint32_t(-1)),
        pkgdatadir(),
        cmocfloatlibdir(),
        lwasmPath("lwasm"),
        lwlinkPath("lwlink"),
        intermediateFilesKept(false),
        intermediateDir(),
        generatePrerequisitesFile(false),
        generatePrerequisitesFileOnly(false),
        prerequisiteFilename(),
        preprocOnly(false),
        genAsmOnly(false),
        compileOnly(false),
        asmCmd(false),  // write asm command in a .cmd file
        verbose(false),
        treatWarningsAsErrors(false),
        nullPointerCheckingEnabled(false),
        stackOverflowCheckingEnabled(false),
        targetPlatform(COCO_BASIC),
        assumeTrack34(false),
        forcedLWLinkFormat(),
        callToUndefinedFunctionAllowed(false),
        warnSignCompare(false),
        warnPassingConstForFuncPtr(false),
        isConstIncorrectWarningEnabled(true),
        isBinaryOpGivingByteWarningEnabled(false),
        isLocalVariableHidingAnotherWarningEnabled(false),
        isNonLiteralPrintfFormatWarningEnabled(true),
        isUncalledStaticFunctionWarningEnabled(true),
        isMissingFieldInitializersWarningEnabled(true),
        inlineAsmArrayIndexesWarningEnabled(true),
        forConditionComparesDifferentSizesWarningEnabled(false),
        wholeFunctionOptimization(false),
        forceJumpMode(false),
        forcedJumpMode(SwitchStmt::IF_ELSE),
        optimizationLevel(2),
        omitFramePointer(false),
        stackSpaceSpecifiedByCommandLine(false),
        limitAddress(0xFFFF),
        limitAddressSetBySwitch(false),
        outputFilename(),
        libDirs(),
        useDefaultLibraries(true),
        useNativeFloatLibrary(false),
        relocatabilitySupported(true),
        includeDirList(),
        searchDefaultIncludeDirs(true),
        defines()
    {
    }

    // May change some parameters of this object.
    //
    int compileCFile(const std::string &inputFilename,
                     const std::string &moduleName,
                     const std::string &asmFilename,
                     const std::string &outputFilename,
                     const char *targetPlatformName,
                     const char *targetPreprocId);

    int invokeAssembler(const std::string &inputFilename,
                        const std::string &objectFilename,
                        const std::string &lstFilename,
                        const std::string &targetPreprocId) const;

    // Returns 's' if no intermediate directory has been specified or
    // if 's' already contains a directory specification.
    // Otherwise, returns the basename of 's' preceded by the specified intermediate directory.
    //
    std::string useIntDir(const std::string &s) const;

    // Prints to cout.
    // Returns 1.
    //
    int declareInvalidOption(const std::string &opt) const;

    // Prints to cout.
    //
    void displayVersionNo() const;

    // Prints to cout.
    //
    void displayHelp() const;

};


#endif  /* _H_Parameters */
