/*  $Id: main.cpp,v 1.113 2018/09/08 20:37:31 sarrazip Exp $

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

#include "TranslationUnit.h"

#include "SwitchStmt.h"
#include "FunctionDef.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#if defined(__MINGW32__)
#define WIFEXITED(x)   ((unsigned) (x) < 259)
#define WEXITSTATUS(x) ((x) & 0xff)
#endif

using namespace std;


int yyparse(void);

extern FILE *yyin;
extern int numErrors;
extern int numWarnings;


#ifndef PROGRAM  // Allow the compilation to define the program name as a macro.
static const char *PROGRAM = "cmoc";
#endif


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

    uint16_t stackSpace;  // applies to --check-stack and sbrk()

    uint32_t functionStackSpace;  // uint32_t(-1) means not set by command-line argument

    string pkgdatadir;  // directory where CMOC support files (.h, etc.) get installed

    string getAssemblerFilename() const
    {
        if (assemblerFilename.empty())
            return pkgdatadir + "/a09";
        return assemblerFilename;
    }
    void setAssemblerFilename(const string &newFilename)
    {
        assemblerFilename = newFilename;
    }

    string lwasmPath;
    string lwlinkPath;

    bool intermediateFilesKept;

    bool generatePrerequisitesFile;      // --deps option
    bool generatePrerequisitesFileOnly;  // --deps-only option

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
    bool generateSREC;   // generate a Motorola SREC executable
    bool emitUncalledFunctions;
    bool callToUndefinedFunctionAllowed;
    bool warnSignCompare;
    bool warnPassingConstForFuncPtr;
    bool isConstIncorrectWarningEnabled;

    bool wholeFunctionOptimization;
    bool forceJumpMode;
    SwitchStmt::JumpMode forcedJumpMode;
    bool monolithMode;  // true means linker mode (lwasm, lwlink)
    size_t optimizationLevel;
    bool stackSpaceSpecifiedByCommandLine;
    uint16_t limitAddress;  // see --limit; 0xFFFF means not applicable
    bool limitAddressSetBySwitch;  // true if --limit used
    string outputFilename;
    vector<string> libDirs;  // list of directories to pass to lwlink via -L options
    bool useDefaultLibraries;
    bool relocatabilitySupported;

    list<string> includeDirList;
    bool searchDefaultIncludeDirs;

    list<string> defines;

private:
    string assemblerFilename;  // if empty, formed from pkgdatadir (useful monolith mode only)

    static uint32_t getVersionInteger();

public:
    Parameters()
    :   codeAddress(0x2800),  // DECB Basic program starts at 0x2601 by default
        dataAddress(0xFFFF),
        codeAddressSetBySwitch(false),
        dataAddressSetBySwitch(false),
        stackSpace(1024),
        functionStackSpace(uint32_t(-1)),
        pkgdatadir(),
        lwasmPath("lwasm"),
        lwlinkPath("lwlink"),
        intermediateFilesKept(false),
        generatePrerequisitesFile(false),
        generatePrerequisitesFileOnly(false),
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
        generateSREC(false),
        emitUncalledFunctions(false),
        callToUndefinedFunctionAllowed(false),
        warnSignCompare(false),
        warnPassingConstForFuncPtr(false),
        isConstIncorrectWarningEnabled(true),
        wholeFunctionOptimization(false),
        forceJumpMode(false),
        forcedJumpMode(SwitchStmt::IF_ELSE),
        monolithMode(false),
        optimizationLevel(2),
        stackSpaceSpecifiedByCommandLine(false),
        limitAddress(0xFFFF),
        limitAddressSetBySwitch(false),
        outputFilename(),
        libDirs(),
        useDefaultLibraries(true),
        relocatabilitySupported(true),
        includeDirList(),
        searchDefaultIncludeDirs(true),
        defines(),
        assemblerFilename()
    {
    }

    int compileCFile(const string &inputFilename,
                     const string &moduleName,
                     const string &asmFilename,
                     const string &outputFilename,
                     const char *targetPlatformName,
                     const char *targetPreprocId);

} params;


static const char *fatalErrorPrefix = ": fatal error: ";


static
void
displayVersionNo()
{
    cout << PROGRAM << " (" << PACKAGE << " " << VERSION << ")\n";
}


static
void
displayHelp()
{
    cout << "\n";

    displayVersionNo();

    cout << "\n"
        "Copyright (C) 2003-2017 Pierre Sarrazin <http://sarrazip.com/>\n";
    cout <<
"This program is free software; you may redistribute it under the terms of\n"
"the GNU General Public License, either version 3 or later.\n"
"This program comes with absolutely no warranty.\n"
"\n";

    cout <<
        "--help|-h           Display this help page and exit.\n"
        "--version|-v        Display this program's version number and exit.\n"
        "--verbose|-V        Display more informationg about the compiling process.\n"
        "--preproc|-E        Copy preprocessor output to standard output,\n"
        "                    instead of compiling.\n"
        "-S                  Stop after generating an assembly language file.\n"
        "--compile|-c        Stop after generating an object file.\n"
        "--deps              Create a .d file containing a makefile rule giving the\n"
        "                    dependencies of the compiled file.\n"
        "--deps-only         Same, but do nothing else and stop.\n"
        //"--asm-cmd           Create a .cmd file with the assembly command.\n"
        "--org=X             Use X (in hex) as the first address at which to generate\n"
        "                    the code; default: "
                             << hex << params.codeAddress << dec << ".\n"
        "--limit=X           Fail if program_end exceeds address X (in hex).\n"
        "--data=X            Use X (in hex) as the first address at which to generate the\n"
        "                    writable global variable space; by default that space follows\n"
        "                    the code.\n"
        "--coco              Compile a CoCo Disk Basic .bin file (default).\n"
        "--os9               Compile an OS-9 executable.\n"
        "--usim              Compile for USIM 6809 simulator (executable is .hex file).\n"
        "--dos               Compile CoCo DECB Track 34 boot loader (implies --coco).\n"
        "--vectrex           Compile for the Vectrex video game console.\n"
        "--srec              Executable in Motorola SREC format (Disk Basic only).\n"
        "--lwasm=X           Use X as the path to the LWTOOLS assembler.\n"
        "--lwlink=X          Use X as the path to the LWTOOLS linker.\n"
        //"--a09=X             Use assembler specified by path X instead of installed a09.\n"
        "-Idir               Add directory <dir> to the compiler's include directories\n"
        "                    (also applies to assembler).\n"
        "-Dxxx=yyy           Equivalent to #define xxx yyy\n"
        "-L dir              Add a directory to the library search path.\n"
        "-l name             Add a library to the linking phase. -lfoo expects `libfoo.a'.\n"
        "                    This option must be specified after the source/object files.\n"
        "-nodefaultlibs      Excludes CMOC-provided libraries from the linking phase.\n"
        "--no-relocate       Assume that the program will only be loaded at the addresses specified\n"
        "                    by --org and --data. Not compatible with OS-9. Default for Vectrex.\n"
        "--check-null        Insert run-time checks for null pointers. See the manual.\n"
        "--check-stack       Insert run-time checks for stack overflow. See the manual.\n"
        "                    Not usable under OS-9, where stack checking is automatic.\n"
        "--stack-space=N     Assume the stack may use as many as N bytes (in decimal).\n"
        "                    Affects --check-stack and sbrk().\n"
        "                    Not usable under OS-9, where stack checking is automatic.\n"
        "                    Ignored when targeting Vectrex.\n"
        "--function-stack=N  (OS-9 only.) Emit code at the start of each function to check that there\n"
        "                    is at least N bytes of free stack space in addition to local variables.\n"
        "                    0 means no stack checking. Default is 64.\n"
        //"--emit-uncalled     Emit functions even if they are not called by C code.\n"
        //"--allow-undef-func  Allow calls to undefined functions.\n"
        "-Wsign-compare      Warn when <, <=, >, >= used on operands of differing signedness.\n"
        "-Wno-const          Do not warn about const-incorrect code.\n"
        "--switch=MODE       Force all switch() statements to use MODE, where MODE is 'ifelse'\n"
        "                    for an if-else sequence or 'jump' for a jump table.\n"
        "-O0|-O1|-O2         Optimization level (default is 2). Compilation is faster with -O0.\n"
        //"--no-peephole       Deprecated: equivalent to -O0.\n"
        "-Werror             Treat warnings as errors.\n"
        "-o FILE             Place the output in FILE (default: change C file extension to .bin).\n"
        "--intermediate|-i   Keep intermediate compilation and linking files.\n"
        "--monolith          Compile one C file as a single unit, rather than use the linker mode.\n"
        "\n";

    cout << "Compiler data directory: " << params.pkgdatadir << "\n\n";

    cout << "For details, see the manual on the CMOC home page.\n\n";
}


class FileCloser
{
public:
    FileCloser(FILE *_file) : file(_file) {}
    ~FileCloser() { close(); }
    void close() { if (file != NULL) { fclose(file); file = NULL; } }

private:
    // Forbidden:
    FileCloser(const FileCloser &);
    FileCloser &operator = (const FileCloser &);

private:
    FILE *file;
};


class PipeCloser
{
public:
    PipeCloser(FILE *_file) : file(_file) {}
    ~PipeCloser() { close(); }
    int close()
    {
        if (file == NULL)
            return 0;  // success: nothing to do
        int status = pclose(file);
        file = NULL;
        return status;
    }
private:
    // Forbidden:
    PipeCloser(const PipeCloser &);
    PipeCloser &operator = (const PipeCloser &);

private:
    FILE *file;
};


// If the line has the form "Symbol: SYMBOLNAME (OBJECTFILENAME) = HEXADDR",
// then returns: SYMBOLNAME in *symbolName (if symbolName is not null),
//               OBJECTFILENAME in *objectFilename (if objectFilename is not null),
//               the value of HEXADDR in symbolValue,
//               and returns true.
// Returns false if the line does not have the expected form.
//
static bool
parseLinkerMapSymbolLine(const string &line,
                         string *symbolName,
                         string *objectFilename,
                         uint16_t &symbolValue)
{
    if (line.find("Symbol: ") != 0)
        return false;

    size_t posAfterSymbolName = line.find(" (");
    if (posAfterSymbolName == string::npos)
        return false;

    size_t posAfterFilename = line.find(") = ");
    if (posAfterFilename == string::npos)
        return false;

    string hexAddr = line.substr(posAfterFilename + 4, 4);
    char *endptr = NULL;
    unsigned long a = strtoul(hexAddr.c_str(), &endptr, 16);
    if (a > 0xFFFF)
        return false;

    if (symbolName != NULL)
        *symbolName = line.substr(8, posAfterSymbolName - 8);
    if (objectFilename != NULL)
        *objectFilename = line.substr(posAfterSymbolName + 2, posAfterFilename - (posAfterSymbolName + 2));
    symbolValue = uint16_t(a);
    return true;
}


static string
getDefaultOutputExtension(TargetPlatform p, bool generateSREC)
{
    switch (p)
    {
    case COCO_BASIC: return generateSREC ? ".srec" : ".bin";
    case USIM:       return ".srec";
    case VECTREX:    return ".bin";
    default:         return "";
    }
}


static int
invokeAssembler(const string &inputFilename,
                const string &moduleName,
                const string &outputFilename,
                const string &targetPreprocId,
                bool verbose)
{
    // Assemble the asm to a .o object file.

    string lwasmCmdLine = params.lwasmPath
                          + " -fobj --pragma=forwardrefmax"
                          + " -D" + targetPreprocId
                          + " --output='" + outputFilename + "'"
                          + (params.intermediateFilesKept ? " --list='" + moduleName + ".lst'" : "")
                          + " '" + inputFilename + "'";
    if (verbose)
        cout << "Assembler command: " << lwasmCmdLine << endl;

    int status = system(lwasmCmdLine.c_str());
    if (status == -1)
    {
        int e = errno;
        cout << PACKAGE << fatalErrorPrefix << "could not start assembler: "
                                            << strerror(e) << endl;
        return EXIT_FAILURE;
    }

    if (verbose)
        cout << "Exit code from assembler command: " << WEXITSTATUS(status) << "\n";

    if (!WIFEXITED(status))
        return EXIT_FAILURE;
    status = WEXITSTATUS(status);
    if (status != 0)
        return status;

    return EXIT_SUCCESS;
}


// Create a link script to tell lwlink in which order to write out the sections to the executable file.
// The first section is "start": it contains only the program_start routine.
// We want the start of the binary to be the entry point.
//
static bool
createLinkScript(const string &linkScriptFilename)
{
    ofstream linkScript(linkScriptFilename.c_str(), ios::trunc);
    if (!linkScript)
    {
        int e = errno;
        cout << PACKAGE << fatalErrorPrefix << "could not create link script " + linkScriptFilename + ": "
                                            << strerror(e) << endl;
        return false;
    }

    const char *initGLSections =
                  "section initgl_start\n"  // defines INITGL label
                  "section initgl\n"        // initialization code
                  "section initgl_end\n";   // RTS

    // Have the linker define a symbol for the ultimate base address and length of each section.
    // See the LWLINK manual (section 4.3).
    linkScript << "define basesympat s_%s\n"
                  "define lensympat l_%s\n";

    linkScript << "section start load " << hex << params.codeAddress << "\n"
                  "section code\n";  // main code section

    if (params.dataAddress != 0xFFFF || params.targetPlatform == OS9)  // if there is a separate data segment
        linkScript << initGLSections;  // put globals init code after main code

    // Put the read-only data next to the code.
    // Under OS-9, references to read-only data are made with ,PCR (see TranslationUnit's
    // getDataIndexRegister() and getLiteralIndexRegister()).
    // When targeting a CoCo cartridge, the read-only data goes in the ROM with the code.
    //
    linkScript << "section rodata\n";  // for OS-9, this must be last section of ,PCR segment

    // The writable data either follows, or it is positioned in a separate segment.
    // The latter is the case for OS-9 (where the writable data is in a segment designated by Y).
    // It is also the case if --data was passed.
    //
    linkScript << "section rwdata";

    if (params.targetPlatform == OS9)
        linkScript << " load 1";  // do not allocate data to offset 0, to distinguish (void *) 0 as invalid pointer
    else if (params.dataAddress != 0xFFFF)
        linkScript << " load " << params.dataAddress;

    linkScript << "\n";

    // Data area that does not receive initial values from the executable file.
    //
    linkScript << "section bss,bss\n";

    // If the data follows the code in the same segment, finish with initgl code.
    // This is useful under Disk Basic because the sbrk() pointer can optionally
    // be set at initgl_start if the program never needs to be run a second time,
    // it will never need to reinitialize its globals. This means more memory to
    // be dynamically allocated by sbrk().
    //
    if (params.dataAddress == 0xFFFF && params.targetPlatform != OS9)
        linkScript << initGLSections;

    linkScript << "entry program_start\n" << dec;

    linkScript.close();
    if (!linkScript)
    {
        int e = errno;
        cout << PACKAGE << fatalErrorPrefix << "could not close link script " + linkScriptFilename + ": "
                                            << strerror(e) << endl;
        return false;
    }

    return true;
}


// If a limit address must be enforced, looks for 'program_end' in the link map file.
// Checks for and reports multiply defined symbols.
//
static int
checkLinkingMap(uint16_t limitAddress,
                const string &mapFilename)
{
    ifstream mapFile(mapFilename.c_str());
    if (!mapFile)
    {
        cout << PACKAGE << fatalErrorPrefix << "failed to open linker map file " << mapFilename << endl;
        return EXIT_FAILURE;
    }

    typedef multimap<string, string> SymbolMap;  // key: symbol name; value(s): object filename
    typedef pair<string, string> Pair;

    SymbolMap symbolMap;
    bool programEndFound = false;
    int status = EXIT_SUCCESS;

    string line, symbolName, objectFilename;
    while (getline(mapFile, line))
    {
        // If the line defines a symbol, remember the name and its object filename,
        // in case multiple definitions are seen.
        // Also check for program_end vs. limitAddress.
        //
        uint16_t symbolValue = 0;
        if (parseLinkerMapSymbolLine(line, &symbolName, &objectFilename, symbolValue))
        {
            if (limitAddress != 0xFFFF && symbolName == "program_end")
            {
                programEndFound = true;
                if (symbolValue > limitAddress)
                {
                    cout << PACKAGE << fatalErrorPrefix << "code limit set at $" << hex << setw(4) << limitAddress
                                    << " but program_end exceeds it at $" << setw(4) << symbolValue << dec << endl;
                    status = EXIT_FAILURE;
                }
            }

            // We only care about underscore-led names because the map will mention any symbol
            // that appears in the linked modules, even if they were not exported from their module.
            if (symbolName[0] == '_')
                symbolMap.insert(make_pair(symbolName, objectFilename));
        }
    }

    if (limitAddress != 0xFFFF && !programEndFound)
    {
        cout << PACKAGE << fatalErrorPrefix << "failed to find value of program_end symbol in " << mapFilename << endl;
        status = EXIT_FAILURE;
    }

    // Check for multiple definitions.
    SymbolMap::const_iterator firstItSameName = symbolMap.end();
    vector<string> objectFilenames;
    for (SymbolMap::const_iterator it = symbolMap.begin(); it != symbolMap.end(); ++it)
    {
        const Pair &p = *it;
        if (firstItSameName != symbolMap.end() && firstItSameName->first == p.first)
        {
            objectFilenames.push_back(firstItSameName->second);
            objectFilenames.push_back(p.second);
        }
        else
        {
            if (firstItSameName != symbolMap.end() && objectFilenames.size() > 0)
            {
                const string &sym = firstItSameName->first;
                bool isError = (sym == "_main");  // we know main() is a function
                if (isError)
                    status = EXIT_FAILURE;
                cout << PACKAGE << ": " << (isError ? "error" : "warning")
                                << ": multiple definitions of symbol " << sym << " in modules ";
                for (vector<string>::const_iterator m = objectFilenames.begin(); m != objectFilenames.end(); ++m)
                {
                    if (m != objectFilenames.begin())
                        cout << ", ";
                    cout << *m;
                }
                cout << endl;
                objectFilenames.clear();
            }
            firstItSameName = it;
        }
    }

    return status;
}


static bool
removeFile(const string &path)
{
    // Belt and suspenders: refuse to remove a C file.
    if (endsWith(path, ".c") || endsWith(path, ".h"))
    {
        cout << PACKAGE << fatalErrorPrefix << "refusing to remove " << path << "\n";
        exit(1);
    }

    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
    {
        int e = errno;
        if (e == ENOENT)
            return true;  // file does not exist; nothing to do
        cout << PACKAGE << ": warning: failed to stat " << path << ": " << strerror(e) << "\n";
        return false;
    }

    if (unlink(path.c_str()) != 0)
    {
        int e = errno;
        cout << PACKAGE << ": warning: failed to remove " << path << ": " << strerror(e) << "\n";
        return false;
    }

    return true;
}


static void
removeIntermediateCompilationFiles(const vector<string> &intermediateCompilationFiles)
{
    if (params.intermediateFilesKept)
        return;

    for (vector<string>::const_iterator it = intermediateCompilationFiles.begin();
                                       it != intermediateCompilationFiles.end(); ++it)
        removeFile(*it);
}


static void
removeIntermediateLinkingFiles(const string &linkScriptFilename,
                               const string &mapFilename,
                               const vector<string> &intermediateObjectFiles)
{
    if (params.intermediateFilesKept)
        return;

    removeFile(linkScriptFilename);
    removeFile(mapFilename);

    for (vector<string>::const_iterator it = intermediateObjectFiles.begin();
                                       it != intermediateObjectFiles.end(); ++it)
        removeFile(*it);
}


static int
invokeLinker(const vector<string> &objectFilenames,
             const vector<string> &libraryFilenames,  // allowed to contain -l<name> elements
             bool useDefaultLibraries,
             const string &linkScriptFilename,
             const string &mapFilename,
             const string &outputFilename,
             TargetPlatform targetPlatform,
             const vector<string> &libDirs,
             uint16_t limitAddress,
             bool generateSREC,
             bool verbose)
{
    assert(!outputFilename.empty());

    if (!createLinkScript(linkScriptFilename))
        return EXIT_FAILURE;

    const char *targetKW = NULL, *lwlinkFormat = NULL;
    switch (targetPlatform)
    {
    case COCO_BASIC: targetKW = "ecb";  lwlinkFormat = generateSREC ? "srec" : "decb";  break;
    case OS9:        targetKW = "os9";  lwlinkFormat = "os9";  break;
    case USIM:       targetKW = "usim"; lwlinkFormat = "srec"; break;
    case VECTREX:    targetKW = "vec";  lwlinkFormat = "raw"; break;
    }

    string lwlinkCmdLine = params.lwlinkPath
                           + " --format=" + lwlinkFormat
                           + " --output='" + outputFilename
                           + "' --script='" + linkScriptFilename
                           + "' --map='" + mapFilename + "'";
    for (vector<string>::const_iterator it = libDirs.begin(); it != libDirs.end(); ++it)
        lwlinkCmdLine += " -L'" + *it + "'";

    lwlinkCmdLine += " -L" + params.pkgdatadir + "/lib";
    lwlinkCmdLine += " -lcmoc-crt-" + string(targetKW);
    if (useDefaultLibraries)
    {
        lwlinkCmdLine += " -lcmoc-std-" + string(targetKW);
        if (targetPlatform == COCO_BASIC)
            lwlinkCmdLine += " -lcmoc-float-" + string(targetKW);
    }

    for (vector<string>::const_iterator it = objectFilenames.begin();
                                       it != objectFilenames.end(); ++it)
        lwlinkCmdLine += " '" + *it + ".o'";

    for (vector<string>::const_iterator it = libraryFilenames.begin();
                                       it != libraryFilenames.end(); ++it)
        lwlinkCmdLine += " '" + *it + "'";

    if (verbose)
        cout << "Linker command: " << lwlinkCmdLine << endl;

    // Start the linker through a pipe and redirect the linker's stderr to that pipe.
    //
    FILE *lwlinkPipe = popen((lwlinkCmdLine + " 2>&1").c_str(), "r");
    if (!lwlinkPipe)
    {
        int e = errno;
        cout << PACKAGE << fatalErrorPrefix << "failed to start linker: " << strerror(e) << endl;
        return EXIT_FAILURE;
    }

    PipeCloser closer(lwlinkPipe);

    // Print every line from the linker. Tag non-warning messages as errors.
    // Filter out some unneeded warnings.
    //
    size_t numLinkerErrors = 0;
    char line[512];
    while (fgets(line, sizeof(line), lwlinkPipe))
    {
        if (strstr(line, "does not resolve any symbols") != NULL)
            continue;
        cout << "lwlink: ";
        if (strstr(line, "Warning:") == NULL)
        {
            cout << "error: ";
            ++numLinkerErrors;
        }
        cout << line;
    }

    int status = closer.close();

    if (verbose)
    {
        cout << "Exit code from linker command: " << WEXITSTATUS(status) << "\n";
        cout << "Number of error messages from linker: " << numLinkerErrors << "\n";
    }

    if (!WIFEXITED(status))
        return EXIT_FAILURE;
    status = WEXITSTATUS(status);
    if (status != 0)
        return status;
    if (numErrors > 0)
        return EXIT_FAILURE;

    return checkLinkingMap(limitAddress, mapFilename);
}


class TranslationUnitDestroyer
{
public:
    TranslationUnitDestroyer(bool _destroyTU) : destroyTU(_destroyTU) {}
    ~TranslationUnitDestroyer()
    {
        if (destroyTU)
            TranslationUnit::destroyInstance();
    }
private:
    bool destroyTU;
};


// If VERSION is x.y.z, then returns x * 100000 + y * 1000 + z.
// Assumes that y <= 99 and z <= 999.
//
uint32_t
Parameters::getVersionInteger()
{
    char *endptr = NULL;
    unsigned long major = strtoul(VERSION, &endptr, 10);
    unsigned long minor = strtoul(endptr + 1, &endptr, 10);
    unsigned long micro = strtoul(endptr + 1, &endptr, 10);
    return uint32_t(major * 100000UL + minor * 1000UL + micro);
}


// In monolith mode, finishes with generation of the assembly file.
// In linker mode, also invokes the assembler on that file.
//
// compilationOutputFilename: Only used if !monolithMode.
//
// Returns EXIT_SUCCESS or EXIT_FAILURE.
//
int
Parameters::compileCFile(const string &inputFilename,
                         const string &moduleName,
                         const string &asmFilename,
                         const string &compilationOutputFilename,
                         const char *targetPlatformName,
                         const char *targetPreprocId)
{
    assert(!compilationOutputFilename.empty() || monolithMode);

    if (verbose)
    {
        cout << "Target platform: " << targetPlatformName << endl;
        cout << "Preprocessing: " << inputFilename << endl;
    }

    // Call the C preprocessor on the source file and prepare to read its output:
    //
    stringstream cppCommand;
    cppCommand << "cpp -xc++ -U__cplusplus";  // -xc++ makes sure cpp accepts C++-style comments
    for (list<string>::const_iterator it = includeDirList.begin(); it != includeDirList.end(); ++it)
        cppCommand << " -I'" << *it << "'";
    cppCommand << " -D_CMOC_VERSION_=" << getVersionInteger();
    cppCommand << " -D" << targetPreprocId << "=1";
    if (monolithMode)
        cppCommand << " -DCMOC_MONOLITH";
    cppCommand << " -U__GNUC__ -nostdinc -undef";

    for (list<string>::const_iterator it = defines.begin(); it != defines.end(); ++it)
        cppCommand << " -D'" << *it << "'";

    cppCommand << " " << inputFilename;  // must be last argument, for portability

    if (verbose)
        cout << "Preprocessor command: " << cppCommand.str() << endl;

    yyin = popen(cppCommand.str().c_str(), "r");
    if (yyin == NULL)
    {
        int e = errno;
        cout << PACKAGE << fatalErrorPrefix << "could not start C preprocessor (through pipe):"
                                            << " " << strerror(e) << endl;
        return EXIT_FAILURE;
    }

    PipeCloser preprocFileCloser(yyin);


    if (preprocOnly)
    {
        enum { bufferSize = 8192 };
        string buffer(bufferSize, ' ');  // allocate buffer
        size_t numRead;
        while ((numRead = fread((void *) buffer.data(), 1, buffer.length(), yyin)) > 0)
        {
            if (fwrite(buffer.data(), 1, numRead, stdout) != numRead)
            {
                int e = errno;
                cout << PACKAGE << fatalErrorPrefix
                     << "failed to copy C preprocessor output to standard output:"
                     << " " << strerror(e) << endl;
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }


    // Create the translation unit object, if in linker mode.
    // In that mode, each .c file must be compiled as a separate unit.
    // In monolith mode, we use a single unit, which must have been created by the caller.
    //
    if (!monolithMode)
        TranslationUnit::createInstance(targetPlatform,
                                        callToUndefinedFunctionAllowed,
                                        warnSignCompare,
                                        warnPassingConstForFuncPtr,
                                        isConstIncorrectWarningEnabled,
                                        relocatabilitySupported);
    TranslationUnitDestroyer tud(!monolithMode);  // destroy TU at end of this function, when in linker mode
    TranslationUnit &tu = TranslationUnit::instance();

    if (verbose)
        cout << "Compiling..." << endl;
    assert(yyin != NULL);
    yyparse();  // invoke parser.yy


    uint16_t pragmaStackSpace = 0;

    tu.processPragmas(params.codeAddress, params.codeAddressSetBySwitch,
                      limitAddress, limitAddressSetBySwitch,
                      params.dataAddress, params.dataAddressSetBySwitch,
                      pragmaStackSpace, monolithMode, compileOnly);

    /*  Apply #pragma stack_space only if --stack-space not used.
    */
    if (pragmaStackSpace != 0 && !stackSpaceSpecifiedByCommandLine)
        params.stackSpace = pragmaStackSpace;

    /*  On the Vectrex, the writable globals must be mapped at $C880
        while the code and read-only globals are mapped at the start of memory.
    */
    if (targetPlatform == VECTREX)
        params.dataAddress = 0xC880;  // equivalent to --data=0xC880


    tu.enableNullPointerChecking(nullPointerCheckingEnabled);

    tu.enableStackOverflowChecking(stackOverflowCheckingEnabled);

    if (verbose && targetPlatform != OS9)
    {
        cout << "Code address: $" << hex << params.codeAddress << dec << " (" << params.codeAddress << ")\n";
        cout << "Data address: ";
        if (params.dataAddress == 0xFFFF)
            cout << "after the code";
        else
            cout << "$" << hex << params.dataAddress << dec << " (" << params.dataAddress << ")";
        cout << "\n";
    }

    int pipeCmdStatus = preprocFileCloser.close();
    //cout << "pipeCmdStatus=" << pipeCmdStatus << endl;
    if (!WIFEXITED(pipeCmdStatus))
    {
        cout << PACKAGE << fatalErrorPrefix << "preprocessor terminated abnormally." << endl;
        return EXIT_FAILURE;
    }
    if (WEXITSTATUS(pipeCmdStatus) != 0)
    {
        cout << PACKAGE << fatalErrorPrefix << "preprocessor failed." << endl;
        return EXIT_FAILURE;
    }

    if (numErrors == 0 && !params.generatePrerequisitesFileOnly)
    {
        tu.checkSemantics(params.monolithMode);  // this is when Scope objects get created in FunctionDefs

        tu.allocateLocalVariables();  // in all FunctionDef objects
    }

    if (targetPlatform == VECTREX)
    {
        // The Vectrex is limited in RAM space and shares the stack with freely available memory.
        // $C880 - $CBEA is user RAM (874 bytes)
        // $CBEA is Vec_Default_Stk Default top-of-stack
        //
        params.stackSpace = 256;
    }

    ASMText asmText;

    if (numErrors == 0 && !params.generatePrerequisitesFileOnly)
    {
        tu.emitAssembler(asmText, moduleName, compileOnly, params.codeAddress, params.dataAddress,
                         params.stackSpace, assumeTrack34, emitUncalledFunctions, monolithMode);

        if (optimizationLevel > 0)
            asmText.peepholeOptimize(optimizationLevel == 2);
        if (wholeFunctionOptimization)
            asmText.optimizeWholeFunctions();
    }


    /*  Now that yyparse() and emitAssembler() have been called, free the memory,
        to keep valgrind from reporting a leak.
    */
    extern string sourceFilename;
    sourceFilename.clear();


    /*  Create an asm file that will receive the assembly language code:
    */
    if (numErrors == 0 && !params.generatePrerequisitesFileOnly)
    {
        if (verbose)
        {
            if (monolithMode)
                cout << "Assembler: " << assemblerFilename << "\n";
            cout << "Assembly language filename: " << asmFilename << "\n";
            cout << flush;
        }
        ofstream asmFile(asmFilename.c_str(), ios::out);
        if (!asmFile)
        {
            int e = errno;
            cout << PACKAGE << fatalErrorPrefix << "failed to create assembler file:"
                            << " " << strerror(e) << endl;
            return EXIT_FAILURE;
        }
        if (!asmText.writeFile(asmFile, monolithMode))
        {
            cout << PACKAGE << fatalErrorPrefix << "failed to write output assembly file " << asmFilename << endl;
            return EXIT_FAILURE;
        }
        asmFile.close();
        if (!asmFile)
        {
            cout << PACKAGE << fatalErrorPrefix << "failed to close output assembly file " << asmFilename << endl;
            return EXIT_FAILURE;
        }
    }

    if (verbose)
        cout << numErrors << " error(s)"
                << ", " << numWarnings << " warning(s)." << endl;

    if (numErrors > 0)
        return EXIT_FAILURE;

    if (numWarnings > 0 && treatWarningsAsErrors)
        return EXIT_FAILURE;

    if (!monolithMode && params.generatePrerequisitesFile)
    {
        string dependenciesFilename = replaceExtension(compilationOutputFilename, ".d");
        ofstream dependenciesFile(dependenciesFilename.c_str(), ios::out);
        if (dependenciesFile.good())
            tu.writePrerequisites(dependenciesFile, dependenciesFilename, compilationOutputFilename, params.pkgdatadir);
        else
        {
            int e = errno;
            cout << PACKAGE << fatalErrorPrefix << "failed to create dependencies file "
                    << dependenciesFilename  << ": " << strerror(e) << endl;
        }
        if (params.generatePrerequisitesFileOnly)
            return EXIT_SUCCESS;
    }

    if (!monolithMode && !genAsmOnly)
    {
        int status = invokeAssembler(asmFilename, moduleName, compilationOutputFilename, targetPreprocId, verbose);
        if (compileOnly || status != EXIT_SUCCESS)
            return status;
    }

    return EXIT_SUCCESS;
}


// argi receives the index of the first non-option argument in argv[].
//
// Returns:
//   0 to ask the caller to quit with EXIT_SUCCESS;
//   1 to ask the caller to quit with EXIT_FAILURE;
//  -1 to ask the caller to continue.
//
static int
interpretCommandLineOptions(int argc, char *argv[], int &argi)
{
    for (argi = 1; argi < argc; ++argi)
    {
        string curopt = argv[argi];

        if (curopt == "--version" || curopt == "-v")
        {
            displayVersionNo();
            return 0;
        }
        if (curopt == "--help" || curopt == "-h")
        {
            displayHelp();
            return 0;
        }
        if (curopt == "--preproc" || curopt == "-E")
        {
            params.preprocOnly = true;
            continue;
        }
        if (curopt == "--compile" || curopt == "-c")
        {
            params.compileOnly = true;
            continue;
        }
        if (curopt == "-S")
        {
            params.genAsmOnly = true;
            continue;
        }
        if (curopt == "--deps")
        {
            params.generatePrerequisitesFile = true;
            continue;
        }
        if (curopt == "--deps-only")
        {
            params.generatePrerequisitesFile = true;
            params.generatePrerequisitesFileOnly = true;
            params.compileOnly = true;
            continue;
        }
        if (curopt == "--asm-cmd")
        {
            params.asmCmd = true;
            continue;
        }
        if (curopt == "--verbose" || curopt == "-V")
        {
            params.verbose = true;
            continue;
        }
        if (curopt.compare(0, 6, "--org=") == 0)
        {
            string address(curopt, 6, string::npos);
            unsigned long n = strtoul(address.c_str(), NULL, 16);
            if (n > 0xFFFF || errno == ERANGE)
            {
                cout << PACKAGE << ": Invalid code address: " << address << "\n";
                displayHelp();
                return 1;
            }
            params.codeAddress = (uint16_t) n;
            params.codeAddressSetBySwitch = true;
            continue;
        }
        if (curopt.compare(0, 8, "--limit=") == 0)
        {
            string address(curopt, 8, string::npos);
            unsigned long n = strtoul(address.c_str(), NULL, 16);
            if (n > 0xFFFF || errno == ERANGE)
            {
                cout << PACKAGE << ": Invalid limit address: " << address << "\n";
                displayHelp();
                return 1;
            }
            params.limitAddress = (uint16_t) n;
            params.limitAddressSetBySwitch = true;
            continue;
        }
        if (curopt.compare(0, 7, "--data=") == 0)
        {
            string address(curopt, 7, string::npos);
            unsigned long n = strtoul(address.c_str(), NULL, 16);
            if (n > 0xFFFF || errno == ERANGE)
            {
                cout << PACKAGE << ": Invalid data address: " << address << "\n";
                displayHelp();
                return 1;
            }
            params.dataAddress = (uint16_t) n;
            params.dataAddressSetBySwitch = true;
            continue;
        }
        if (curopt == "--coco-basic" || curopt == "--coco" || curopt == "--coco3")
        {
            params.targetPlatform = COCO_BASIC;
            continue;
        }
        if (curopt == "--usim")
        {
            params.targetPlatform = USIM;
            continue;
        }
        if (curopt == "--dos")
        {
            params.targetPlatform = COCO_BASIC;
            params.assumeTrack34 = true;
            params.codeAddress = 0x2600;
            params.codeAddressSetBySwitch = true;
            continue;
        }
        if (curopt == "--os9")
        {
            // As per LWTOOLS manual, subsection 4.4.1 ("OS9 Modules") of
            // section 4.4 ("Format Specific Linking Notes").
            params.codeAddress = 0x000D;

            params.targetPlatform = OS9;
            continue;
        }
        if (curopt == "--vectrex")
        {
            params.codeAddress = 0x0000;
            params.targetPlatform = VECTREX;
            continue;
        }
        if (curopt == "--srec")
        {
            params.generateSREC = true;
            continue;
        }
        if (curopt.compare(0, 6, "--a09=") == 0)
        {
            if (curopt.length() > 6)
                params.setAssemblerFilename(string(curopt, 6, string::npos));
            continue;
        }
        if (curopt.compare(0, 8, "--lwasm=") == 0)
        {
            params.lwasmPath.assign(curopt, 8, string::npos);
            continue;
        }
        if (curopt.compare(0, 9, "--lwlink=") == 0)
        {
            params.lwlinkPath.assign(curopt, 9, string::npos);
            continue;
        }
        if (curopt == "--frankasm")
        {
            cout << PACKAGE << ": --frankasm: obsolete option (must use lwasm).\n";
            displayHelp();
            return 1;
        }
        if (strncmp(curopt.c_str(), "-I", 2) == 0)
        {
            string dir(curopt, 2, string::npos);
            if (!dir.empty())
                params.includeDirList.push_back(dir);
            else if (argi + 1 < argc)  // if argument follows -I:
            {
                ++argi;
                params.includeDirList.push_back(argv[argi]);
            }
            else
            {
                cout << PACKAGE << ": Option -I not followed by directory.\n";
                return 1;
            }

            continue;
        }
        if (strncmp(curopt.c_str(), "-D", 2) == 0)
        {
            string arg(curopt, 2, string::npos);
            if (!arg.empty())
                params.defines.push_back(arg);
            else if (argi + 1 < argc)  // if argument follows -D:
            {
                ++argi;
                params.defines.push_back(argv[argi]);
            }
            else
            {
                cout << PACKAGE << ": Option -D not followed by macro definition.\n";
                return 1;
            }

            continue;
        }
        if (curopt == "-nostdinc")
        {
            params.searchDefaultIncludeDirs = false;
            continue;
        }
        if (startsWith(curopt, "-L"))
        {
            string arg(curopt, 2, string::npos);
            if (!arg.empty())
                params.libDirs.push_back(arg);
            else if (argi + 1 < argc)  // if argument follows -L:
            {
                ++argi;
                params.libDirs.push_back(argv[argi]);
            }
            else
            {
                cout << PACKAGE << ": Option -L not followed by directory.\n";
                return 1;
            }

            continue;
        }
        if (curopt == "-nodefaultlibs")
        {
            params.useDefaultLibraries = false;
            continue;
        }
        if (curopt == "--no-relocate")
        {
            params.relocatabilitySupported = false;
            continue;
        }
        if (curopt == "-Werror")
        {
            params.treatWarningsAsErrors = true;
            continue;
        }
        if (curopt == "--check-null")
        {
            params.nullPointerCheckingEnabled = true;
            continue;
        }
        if (curopt == "--check-stack")
        {
            params.stackOverflowCheckingEnabled = true;
            continue;
        }
        if (strncmp(curopt.c_str(), "--stack-space=", 14) == 0)
        {
            string arg(curopt, 14, string::npos);
            unsigned long n = strtoul(arg.c_str(), NULL, 10);
            if (n > 0xFFFF || errno == ERANGE)
            {
                cout << PACKAGE << ": Invalid argument for --stack-space: " << arg << "\n";
                displayHelp();
                return 1;
            }
            params.stackSpace = (uint16_t) n;
            params.stackSpaceSpecifiedByCommandLine = true;
            continue;
        }
        if (strncmp(curopt.c_str(), "--function-stack=", 17) == 0)
        {
            string arg(curopt, 17, string::npos);
            unsigned long n = strtoul(arg.c_str(), NULL, 10);
            if (n > 0xFFFF || errno == ERANGE)
            {
                cout << PACKAGE << ": Invalid argument for --function-stack: " << arg << "\n";
                displayHelp();
                return 1;
            }
            params.functionStackSpace = (uint16_t) n;
            continue;
        }
        if (curopt == "--emit-uncalled")
        {
            params.emitUncalledFunctions = true;
            continue;
        }
        if (curopt == "--allow-undef-func")
        {
            params.callToUndefinedFunctionAllowed = true;
            continue;
        }
        if (curopt == "-Wsign-compare")
        {
            params.warnSignCompare = true;
            continue;
        }
        if (curopt == "-Wno-const")
        {
            params.isConstIncorrectWarningEnabled = false;
            continue;
        }
        if (curopt == "-Wpass-const-for-func-pointer")  // not documented b/c may be annoying
        {
            params.warnPassingConstForFuncPtr = true;
            continue;
        }
        if (strncmp(curopt.c_str(), "-O", 2) == 0)
        {
            string level(curopt, 2, string::npos);
            if (level.length() != 1 || level[0] < '0' || level[0] > '2')
            {
                cout << PACKAGE << ": Invalid optimization option: " << curopt << "\n";
                displayHelp();
                return 1;
            }
            params.optimizationLevel = level[0] - '0';
            continue;
        }
        if (curopt == "--no-peephole")
        {
            params.optimizationLevel = 0;
            continue;
        }
        if (curopt == "--wfo")
        {
            params.wholeFunctionOptimization = true;
            continue;
        }
        if (curopt == "--intermediate" || curopt == "-i")
        {
            params.intermediateFilesKept = true;
            continue;
        }
        if (curopt == "--monolith")
        {
            params.monolithMode = true;
            continue;
        }
        if (strncmp(curopt.c_str(), "-o", 2) == 0)
        {
            string arg(curopt, 2, string::npos);
            if (!arg.empty())
                params.outputFilename = arg;
            else if (argi + 1 < argc)  // if argument follows -o:
            {
                ++argi;
                params.outputFilename = argv[argi];
            }
            else
            {
                cout << PACKAGE << ": Option -o not followed by filename.\n";
                return 1;
            }
            continue;
        }
        if (strncmp(curopt.c_str(), "--switch=", 9) == 0)
        {
            string arg(curopt, 9, string::npos);
            if (arg == "ifelse")
            {
                params.forceJumpMode = true;
                params.forcedJumpMode = SwitchStmt::IF_ELSE;
            }
            else if (arg == "jump")
            {
                params.forceJumpMode = true;
                params.forcedJumpMode = SwitchStmt::JUMP_TABLE;
            }
            else
            {
                cout << PACKAGE << ": Invalid argument for option --switch (must be ifelse or jump).\n";
                return 1;
            }
            continue;
        }

        if (curopt.empty() || curopt[0] == '-')
        {
            cout << PACKAGE << ": Invalid option: " << curopt << "\n";
            displayHelp();
            return 1;
        }

        break;  // end of options; argi now designates 1st non-option argument
    }

    return -1;
}


// Returns an exit status.
//
int
assembleInMonolithMode(const char *targetPreprocId,
                       const string &programName,
                       const string &asmFilename,
                       vector<string> &intermediateCompilationFiles)
{
    /*  Call the cross-assembler on the asm file to produce executable files:
    */
    stringstream ss;
    ss << params.getAssemblerFilename();
    for (list<string>::const_iterator it = params.includeDirList.begin(); it != params.includeDirList.end(); ++it)
        ss << " --includedir='" << *it << "'";
    if (params.targetPlatform != OS9)
        ss << " --entry=" << hex << params.codeAddress << dec;
    if (params.assumeTrack34)
        ss << " --entry=2602";
    if (params.limitAddress != 0xFFFF)
        ss << " --limit=" << hex << params.limitAddress << dec;
    ss << " --target=" << targetPreprocId;
    if (params.generateSREC)
        ss << " --srec";
    if (params.nullPointerCheckingEnabled)
        ss << " --check-null";
    if (params.stackOverflowCheckingEnabled)
        ss << " --check-stack";
    ss << " --stack-space=" << params.stackSpace;
    const set<string> &neededUtilitySubRoutines = TranslationUnit::instance().getNeededUtilitySubRoutines();
    for (set<string>::const_iterator it = neededUtilitySubRoutines.begin(); it != neededUtilitySubRoutines.end(); ++it)
        ss << " --need=" << *it;
    if (params.verbose)
        ss << " --verbose";
    if (!params.outputFilename.empty())
        ss << " --output='" << params.outputFilename << "'";
    ss << " " << asmFilename;
    string asmCommand = ss.str();

    int status = EXIT_SUCCESS;

    if (params.asmCmd)
    {
        // Write asmCommand in a .cmd file.
        const string asmCmdFilename = programName + ".cmd";
        if (params.verbose)
            cout << "Writing assembly command in " << asmCmdFilename << endl;
        ofstream asmCmdFile(asmCmdFilename.c_str(), ios::out);
        if (!asmCmdFile)
        {
            int e = errno;
            cout << PACKAGE << fatalErrorPrefix << "failed to create assembler command file: "
                            << strerror(e) << endl;
            status = EXIT_FAILURE;
        }
        else
        {
            asmCmdFile << asmCommand << '\n';
            asmCmdFile.close();
            if (!asmCmdFile)
            {
                cout << PACKAGE << fatalErrorPrefix << "failed to close output assembly command file "
                                                    << asmCmdFilename << endl;
                status = EXIT_FAILURE;
            }
        }
    }

    if (status == EXIT_SUCCESS && !params.compileOnly)  // assemble only if -c not passed
    {
        if (params.verbose)
            cout << "Assembling: " << asmCommand << endl;

        status = system(asmCommand.c_str());
        if (status == -1)
        {
            int e = errno;
            cout << PACKAGE << fatalErrorPrefix << "could not start assembler script: "
                                                << strerror(e) << endl;
            status = EXIT_FAILURE;
        }
        else
        {
            if (!WIFEXITED(status))
                status = EXIT_FAILURE;
            else
                status = WEXITSTATUS(status);
        }
    }

    removeIntermediateCompilationFiles(intermediateCompilationFiles);

    return status;
}


int
main(int argc, char *argv[])
{
    /*  Allow an environment variable to override the system #include directory.
    */
    const char *e = getenv("PKGDATADIR");
    params.pkgdatadir = (e != NULL ? e : PKGDATADIR);

    int argi = 1;
    int code = interpretCommandLineOptions(argc, argv, argi);
    if (code != -1)
        return code == 0 ? EXIT_SUCCESS : EXIT_FAILURE;

    const char *targetPlatformName = NULL;
    const char *targetPreprocId = NULL;
    switch (params.targetPlatform)
    {
    case COCO_BASIC: targetPlatformName = "CoCo Disk Basic"; targetPreprocId = "_COCO_BASIC_"; break;
    case OS9:        targetPlatformName = "OS-9";            targetPreprocId = "OS9"; break;
    case USIM:       targetPlatformName = "USim";            targetPreprocId = "USIM"; break;
    case VECTREX:    targetPlatformName = "Vectrex";         targetPreprocId = "VECTREX"; break;
    }


    if (params.monolithMode)
    {
        if (params.targetPlatform == OS9 || params.targetPlatform == VECTREX)
        {
            cout << PACKAGE << ": --monolith not supported when targeting " << targetPlatformName << endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        // In linker mode, allow defining a prototype and calling the function,
        // but letting another module or library define that function.
        params.callToUndefinedFunctionAllowed = true;

        // Do not try to link if dumping the preprocessor output or only generating asm.
        if (params.preprocOnly)
            params.compileOnly = true;
    }

    if (params.genAsmOnly)
        params.compileOnly = true;


    // Forbid --org with --vectrex
    if (params.targetPlatform == VECTREX && (params.codeAddressSetBySwitch || params.dataAddressSetBySwitch))
    {
        cout << PACKAGE << ": --org and --data are not permitted for Vectrex\n";
        return EXIT_FAILURE;
    }

    // Under Vectrex, relocatability is not possible anyway.
    if (params.targetPlatform == VECTREX)
        params.relocatabilitySupported = false;

    string executableFilename;
    if (!params.outputFilename.empty() && !params.compileOnly)
        executableFilename = params.outputFilename;


    // Add default include dir at the end of any user-specified dirs.
    if (params.searchDefaultIncludeDirs)
        params.includeDirList.push_back(params.pkgdatadir + (params.monolithMode ? "" : "/include"));


    assert(argi <= argc);

    if (argi == argc)
    {
        cout << PACKAGE << fatalErrorPrefix << "no input files\n";
        return EXIT_FAILURE;
    }

    if (params.targetPlatform == OS9)
    {
        if (params.generateSREC)
        {
            cout << PACKAGE << fatalErrorPrefix << "generating an OS-9 executable in SREC format is not supported\n";
            return EXIT_FAILURE;
        }
        if (params.stackOverflowCheckingEnabled)
        {
            cout << PACKAGE << fatalErrorPrefix << "--check-stack not usable with OS-9\n";
            return EXIT_FAILURE;
        }
        if (! params.relocatabilitySupported)
        {
            cout << PACKAGE << fatalErrorPrefix << "--no-relocate not compatible with OS-9\n";
            return EXIT_FAILURE;
        }
    }

    if (params.forceJumpMode)
        SwitchStmt::forceJumpMode(params.forcedJumpMode);

    {
        uint16_t fss = 0;  // by default, no stack checking upon function entry
        if (params.functionStackSpace != uint32_t(-1))  // if specified by --function-space
        {
            if (params.targetPlatform != OS9)
            {
                cout << PACKAGE << fatalErrorPrefix << "--function-stack only supported with OS-9\n";
                return EXIT_FAILURE;
            }
            fss = uint16_t(params.functionStackSpace);
        }
        else if (params.targetPlatform == OS9)
            fss = 64;
        FunctionDef::setFunctionStackSpace(fss);
    }

    vector<string> objectFilenames, libraryFilenames, intermediateCompilationFiles, intermediateObjectFiles;
    string programName;
    string asmFilename;

    if (params.monolithMode)
        TranslationUnit::createInstance(params.targetPlatform,
                                        params.callToUndefinedFunctionAllowed,
                                        params.warnSignCompare,
                                        params.warnPassingConstForFuncPtr,
                                        params.isConstIncorrectWarningEnabled,
                                        params.relocatabilitySupported);

    TranslationUnitDestroyer tud(params.monolithMode);

    int status = EXIT_SUCCESS;

    // Scan all non-option arguments.
    //
    for ( ; argi < argc; ++argi)
    {
        /*  Check that the source file exists.
        */
        const string inputFilename = argv[argi];

        if (inputFilename.empty())
        {
            cout << PACKAGE << fatalErrorPrefix << "empty filename" << endl;
            status = EXIT_FAILURE;
            break;
        }

        if (inputFilename[0] != '-')
        {
            struct stat statbuf;
            if (stat(inputFilename.c_str(), &statbuf) != 0)
            {
                int err = errno;
                cout << PACKAGE << fatalErrorPrefix << inputFilename << ": " << strerror(err) << endl;
                status = EXIT_FAILURE;
                break;
            }

            if (S_ISDIR(statbuf.st_mode))
            {
                cout << PACKAGE << fatalErrorPrefix << inputFilename << ": " << strerror(EISDIR) << endl;
                status = EXIT_FAILURE;
                break;
            }
        }


        // Extract the module name and input file extension.
        //
        string moduleName = getBasename(inputFilename);
        const string extension = removeExtension(moduleName);

        // In linker mode, the first module name is the program name.
        if (programName.empty())
            programName = moduleName;

        if (moduleName.find('\"') != string::npos || moduleName.find('\\') != string::npos)
        {
            // This check helps ensure valid OS-9 module name.
            cout << PACKAGE << fatalErrorPrefix << "illegal program file name: " << inputFilename << endl;
            status = EXIT_FAILURE;
            break;
        }


        // Determine this module's output filename (if compilation/assembly required).
        // Note that compilationOutputFilename not used by compileCFile() when in monolith mode.
        //
        string compilationOutputFilename;
        if (extension == ".c" || extension == ".s" || extension == ".asm")
        {
            if (params.compileOnly)
            {
                if (!params.outputFilename.empty())
                    compilationOutputFilename = params.outputFilename;
                else if (!params.monolithMode)
                    compilationOutputFilename = moduleName + ".o";
            }
            else
            {
                // In compile-and-link mode, outputFilename (if any) is the executable filename,
                // so it cannot be used for compilationOutputFilename.
                if (!params.monolithMode)
                    compilationOutputFilename = moduleName + ".o";
            }
        }


        // Process the input filename depending on its extension.
        // C files are compiled.
        // Object files are passed to the linker.
        //
        if (extension == ".c")
        {
            asmFilename = moduleName + (params.monolithMode ? ".asm" : ".s");

            int s = params.compileCFile(inputFilename,
                                        moduleName,
                                        asmFilename,
                                        compilationOutputFilename,
                                        targetPlatformName,
                                        targetPreprocId);

            objectFilenames.push_back(moduleName);
            if (!params.genAsmOnly && (!params.monolithMode || !params.compileOnly))  // keep .s/.asm in monolith with -c
                intermediateCompilationFiles.push_back(asmFilename);
            if (!params.intermediateFilesKept)
                intermediateCompilationFiles.push_back(moduleName + ".lst");
            if (params.monolithMode)
            {
                intermediateCompilationFiles.push_back(moduleName + ".i");
                if (params.targetPlatform != OS9)
                    intermediateCompilationFiles.push_back(moduleName + ".hex");
            }
            else if (!params.compileOnly)
                intermediateObjectFiles.push_back(compilationOutputFilename);

            if (s != EXIT_SUCCESS)
            {
                status = s;
                break;
            }
        }
        else if (extension == ".s" || extension == ".asm")
        {
            if (params.monolithMode)
            {
                cout << PACKAGE << fatalErrorPrefix << "assembler files (" << inputFilename
                                << ") are not supported in monolith mode" << endl;
            }
            else
            {
                int s = invokeAssembler(inputFilename, moduleName, compilationOutputFilename, targetPreprocId, params.verbose);

                if (s != EXIT_SUCCESS)
                {
                    status = s;
                    break;
                }

                objectFilenames.push_back(moduleName);
                if (!params.intermediateFilesKept)
                    intermediateCompilationFiles.push_back(moduleName + ".lst");
                if (!params.compileOnly)
                    intermediateObjectFiles.push_back(compilationOutputFilename);
            }
        }
        else if (extension == ".o")
        {
            objectFilenames.push_back(moduleName);
        }
        else if (extension == ".a")
        {
            libraryFilenames.push_back(inputFilename);
        }
        else if (startsWith(inputFilename, "-L"))
        {
            if (inputFilename.length() == 2)  // if -L alone
            {
                if (argi + 1 < argc)  // if next arg, use it as lib dir
                {
                    params.libDirs.push_back(argv[argi + 1]);
                    ++argi;
                }
                else
                {
                    cout << PACKAGE << fatalErrorPrefix << "-L not followed by library directory" << endl;
                    status = EXIT_FAILURE;
                    break;
                }
            }
            else  // -L followed by dir
                params.libDirs.push_back(inputFilename.substr(2));
        }
        else if (startsWith(inputFilename, "-l"))
        {
            libraryFilenames.push_back(inputFilename);
        }
        else
        {
            cout << PACKAGE << fatalErrorPrefix << "invalid input filename " << inputFilename << endl;
            status = EXIT_FAILURE;
            break;
        }

        if (params.monolithMode)
            break;  // only 1 module allowed in non-linker mode

        // If -o not used, then use 1st module name to form output filename.
        if (executableFilename.empty())
            executableFilename = moduleName + getDefaultOutputExtension(params.targetPlatform, params.generateSREC);

    }   // while

    if (!params.monolithMode)  // these intermediate files are still needed if in monolith mode
        removeIntermediateCompilationFiles(intermediateCompilationFiles);

    if (status != EXIT_SUCCESS)
        return status;

    if (!params.monolithMode && params.compileOnly)
        return EXIT_SUCCESS;


    // Link all modules together.
    //
    if (!params.monolithMode)
    {
        if (params.compileOnly)
            return EXIT_SUCCESS;
        string linkScriptFilename = replaceExtension(executableFilename, ".link");
        string mapFilename = replaceExtension(executableFilename, ".map");
        status = invokeLinker(objectFilenames, libraryFilenames, params.useDefaultLibraries,
                              linkScriptFilename, mapFilename,
                              executableFilename,
                              params.targetPlatform, params.libDirs,
                              params.limitAddress, params.generateSREC, params.verbose);
        removeIntermediateLinkingFiles(linkScriptFilename, mapFilename, intermediateObjectFiles);
        return status;
    }

    return assembleInMonolithMode(targetPreprocId, programName, asmFilename, intermediateCompilationFiles);
}
