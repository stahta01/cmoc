/*  $Id: main.cpp,v 1.45 2016/06/18 04:16:17 sarrazip Exp $

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

#include "TranslationUnit.h"

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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


static const char *PROGRAM = "cmoc";

// Argument for the ORG directive.
// The default is 512 bytes past the default start of a Basic program
// on a Disk Basic CoCo ($2600).
//
static uint16_t codeAddress = 0x2800;
static uint16_t dataAddress = 0xFFFF;  // by default, data section follows code section
static bool codeAddressSetBySwitch = false;  // true if --org or --dos used

static uint16_t limitAddress = 0xFFFF;  // see --limit; 0xFFFF means not applicable
static bool limitAddressSetBySwitch = false;  // true if --limit used

static string pkgdatadir;


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
        "Copyright (C) 2003-2015 Pierre Sarrazin <http://sarrazip.com/>\n";
    cout <<
"This program is free software; you may redistribute it under the terms of\n"
"the GNU General Public License, either version 3 or later.\n"
"This program comes with absolutely no warranty.\n"
"\n";

    cout <<
        "--help|-h        Display this help page and exit.\n"
        "--version|-v     Display this program's version number and exit.\n"
        "--verbose|-V     Display more informationg about the compiling process.\n"
        "--preproc|-E     Copy preprocessor output to standard output,\n"
        "                 instead of compiling.\n"
        "--compile|-c     Compile only, do not assemble.\n"
        "--asm-cmd        Create a .cmd file with the assembly command.\n"
        "--org=X          Use X (in hex) as the first address at which to generate\n"
        "                 the code; default: "
                          << hex << codeAddress << dec << ".\n"
        "--limit=X        Fail if program_end exceeds address X (in hex)\n"
        "--coco           Compile a CoCo Disk Basic .bin file (default).\n"
        "--os9            Compile an OS-9 executable. (Requires lwasm.)\n"
        "--usim           Compile for the USIM 6809 simulator (executable is .hex file).\n"
        "--dos            Compile CoCo DECB Track 34 boot loader (implies --coco).\n"
        "--vectrex        Compile for the Vectrex video game console.\n"
        "--srec           Executable in Motorola SREC format (Disk Basic only).\n"
        "--a09=X          Use assembler specified by path X instead of installed a09.\n"
        "-Idir            Add directory <dir> to the compiler's include directories\n"
        "                 (also applies to assembler).\n"
        "-Dxxx=yyy        Equivalent to #define xxx yyy\n"
        "--check-null     Insert run-time checks for null pointers. See manual.\n"
        "--check-stack    Insert run-time checks for stack overflow. See manual.\n"
        "--emit-uncalled  Emit functions even if they are not called by C code.\n"
        "-O0|-O1|-O2      Optimization level (default is 2).\n"
        "--no-peephole    Deprecated: equivalent to -O0.\n"
        "-Werror          Treat warnings as errors.\n"
        "\n";

    cout << "System #include directory: " << pkgdatadir << "\n\n";

    cout << "For details, see the manual on the CMOC home page.\n\n";
}


static
void
substituteEnding(string &s, const char *target, const char *replacement)
{
    string::size_type posTarget = s.rfind(target);
    if (posTarget == s.length() - strlen(target))  // if found at end
        s.replace(posTarget, strlen(target), replacement);
    else
        s += replacement;
}


static string
getBasename(const string &filename)
{
    string::size_type lastSlash = filename.rfind('/');
    if (lastSlash == string::npos)  // if no slash
        return filename;
    return string(filename, lastSlash + 1, string::npos);
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


int
main(int argc, char *argv[])
{
    const char *e = getenv("PKGDATADIR");
    pkgdatadir = (e != NULL ? e : PKGDATADIR);


    /*  Default command-line option settings:
    */
    bool preprocOnly = false;
    bool compileOnly = false;
    bool asmCmd = false;  // write asm command in a .cmd file
    bool verbose = false;
    bool treatWarningsAsErrors = false;
    bool nullPointerCheckingEnabled = false;
    bool stackOverflowCheckingEnabled = false;
    TargetPlatform targetPlatform = COCO_BASIC;
    bool assumeTrack34 = false;  // true = CoCo DECB Track 34 (relevant only with COCO_BASIC)
    bool generateSREC = false;  // generate a Motorola SREC executable
    bool emitUncalledFunctions = false;
    bool wholeFunctionOptimization = false;
    size_t optimizationLevel = 2;
    string assemblerFilename = pkgdatadir + string("/") + "a09";

    list<string> includeDirList;
    bool searchDefaultIncludeDirs = true;

    list<string> defines;


    /*  Interpret the command-line options:
    */
    int optind;
    for (optind = 1; optind < argc; ++optind)
    {
        string curopt = argv[optind];

        if (curopt == "--version" || curopt == "-v")
        {
            displayVersionNo();
            return EXIT_SUCCESS;
        }
        if (curopt == "--help" || curopt == "-h")
        {
            displayHelp();
            return EXIT_SUCCESS;
        }
        if (curopt == "--preproc" || curopt == "-E")
        {
            preprocOnly = true;
            continue;
        }
        if (curopt == "--compile" || curopt == "-c")
        {
            compileOnly = true;
            continue;
        }
        if (curopt == "--asm-cmd")
        {
            asmCmd = true;
            continue;
        }
        if (curopt == "--verbose" || curopt == "-V")
        {
            verbose = true;
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
                return EXIT_FAILURE;
            }
            codeAddress = (uint16_t) n;
            codeAddressSetBySwitch = true;
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
                return EXIT_FAILURE;
            }
            limitAddress = (uint16_t) n;
            limitAddressSetBySwitch = true;
            continue;
        }
        if (curopt == "--coco-basic" || curopt == "--coco" || curopt == "--coco3")
        {
            targetPlatform = COCO_BASIC;
            continue;
        }
        if (curopt == "--usim")
        {
            targetPlatform = USIM;
            continue;
        }
        if (curopt == "--dos")
        {
            targetPlatform = COCO_BASIC;
            assumeTrack34 = true;
            codeAddress = 0x2600;
            codeAddressSetBySwitch = true;
            continue;
        }
        if (curopt == "--os9")
        {
            targetPlatform = OS9;
            continue;
        }
        if (curopt == "--vectrex")
        {
            codeAddress = 0x0000;
            targetPlatform = VECTREX;
            continue;
        }
        if (curopt == "--srec")
        {
            generateSREC = true;
            continue;
        }
        if (curopt.compare(0, 6, "--a09=") == 0)
        {
            if (curopt[6])
                assemblerFilename.assign(curopt, 6, string::npos);
            continue;
        }
        if (curopt == "--lwasm")
        {
            // Accepted for backward compatibility.
            continue;
        }
        if (curopt == "--frankasm")
        {
            cout << PACKAGE << ": --frankasm: obsolete option (must use lwasm).\n";
            displayHelp();
            return EXIT_FAILURE;
        }
        if (strncmp(curopt.c_str(), "-I", 2) == 0)
        {
            string dir(curopt, 2, string::npos);
            if (!dir.empty())
                includeDirList.push_back(dir);
            else if (optind + 1 < argc)  // if argument follows -I:
            {
                ++optind;
                includeDirList.push_back(argv[optind]);
            }
            else
            {
                cout << PACKAGE << ": Option -I not followed by directory.\n";
                return EXIT_FAILURE;
            }

            continue;
        }
        if (strncmp(curopt.c_str(), "-D", 2) == 0)
        {
            string arg(curopt, 2, string::npos);
            if (!arg.empty())
                defines.push_back(arg);
            else if (optind + 1 < argc)  // if argument follows -D:
            {
                ++optind;
                defines.push_back(argv[optind]);
            }
            else
            {
                cout << PACKAGE << ": Option -D not followed by macro definition.\n";
                return EXIT_FAILURE;
            }

            continue;
        }
        if (curopt == "-nostdinc")
        {
            searchDefaultIncludeDirs = false;
            continue;
        }
        if (curopt == "-Werror")
        {
            treatWarningsAsErrors = true;
            continue;
        }
        if (curopt == "--check-null")
        {
            nullPointerCheckingEnabled = true;
            continue;
        }
        if (curopt == "--check-stack")
        {
            stackOverflowCheckingEnabled = true;
            continue;
        }
        if (curopt == "--emit-uncalled")
        {
            emitUncalledFunctions = true;
            continue;
        }
        if (strncmp(curopt.c_str(), "-O", 2) == 0)
        {
            string level(curopt, 2, string::npos);
            if (level.length() != 1 || level[0] < '0' || level[0] > '2')
            {
                cout << PACKAGE << ": Invalid optimization option: " << curopt << "\n";
                displayHelp();
                return EXIT_FAILURE;
            }
            optimizationLevel = level[0] - '0';
            continue;
        }
        if (curopt == "--no-peephole")
        {
            optimizationLevel = 0;
            continue;
        }
        if (curopt == "--wfo")
        {
            wholeFunctionOptimization = true;
            continue;
        }

        if (curopt.empty() || curopt[0] == '-')
        {
            cout << PACKAGE << ": Invalid option: " << curopt << "\n";
            displayHelp();
            return EXIT_FAILURE;
        }

        break;  // end of options; optind now designated 1st non-option argument
    }


    // Forbid --org with --vectrex
    if (targetPlatform == VECTREX && codeAddressSetBySwitch)
    {
        cout << PACKAGE << ": --org is not permitted for Vectrex\n";
        return EXIT_FAILURE;
    }


    // Add default include dir at the end of any user-specified dirs.
    if (searchDefaultIncludeDirs)
        includeDirList.push_back(pkgdatadir);


    assert(optind <= argc);

    if (optind == argc)
    {
        cout << PACKAGE << ": no input files\n";
        return EXIT_FAILURE;
    }

    if (targetPlatform == OS9)
    {
        if (generateSREC)
        {
            cout << PACKAGE << ": generating an OS-9 executable in SREC format is not supported\n";
            return EXIT_FAILURE;
        }
    }


    /*  Check that the source file exists.
    */
    string cFilename = argv[optind];

    string programName = getBasename(cFilename);
    substituteEnding(programName, ".c", "");

    if (programName.find('\"') != string::npos || programName.find('\\') != string::npos)
    {
        // This check helps ensure valid OS-9 module name.
        cout << PACKAGE << ": illegal program file name: " << cFilename << endl;
        return EXIT_FAILURE;
    }

    struct stat statbuf;
    if (stat(cFilename.c_str(), &statbuf) != 0)
    {
        int e = errno;
        cout << PACKAGE << ": "
                << cFilename << ": " << strerror(e) << endl;
        return EXIT_FAILURE;
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        cout << PACKAGE << ": "
                << cFilename << ": " << strerror(EISDIR) << endl;
    }


    /*  Call the C preprocessor on the source file and prepare to read
        its output:
    */

    const char *targetPlatformName = NULL;
    const char *targetPreprocId = NULL;
    switch (targetPlatform)
    {
    case COCO_BASIC: targetPlatformName = "CoCo Disk Basic"; targetPreprocId = "_COCO_BASIC_"; break;
    case OS9:        targetPlatformName = "OS-9";            targetPreprocId = "OS9"; break;
    case USIM:       targetPlatformName = "usim";            targetPreprocId = "USIM"; break;
    case VECTREX:    targetPlatformName = "vectrex";         targetPreprocId = "VECTREX"; break;
    }

    if (verbose)
    {
        cout << "Target platform: " << targetPlatformName << endl;
        cout << "Preprocessing: " << cFilename << endl;
    }

    stringstream cppCommand;
    cppCommand << "cpp -xc++";  // -xc++ makes sure cpp accepts C++-style comments
    for (list<string>::const_iterator it = includeDirList.begin(); it != includeDirList.end(); ++it)
        cppCommand << " -I'" << *it << "'";
    cppCommand << " -D" << targetPreprocId << "=1";
    cppCommand << " -U__GNUC__ -nostdinc -undef ";
    cppCommand << cFilename;

    for (list<string>::const_iterator it = defines.begin(); it != defines.end(); ++it)
        cppCommand << " -D'" << *it << "'";

    if (verbose)
        cout << "Preprocessor command: " << cppCommand.str() << endl;

    yyin = popen(cppCommand.str().c_str(), "r");
    if (yyin == NULL)
    {
        int e = errno;
        cout << PACKAGE << ": could not start C preprocessor (through pipe):"
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
                cout << PACKAGE << ": "
                     << "failed to copy C preprocessor output to standard output:"
                     << " " << strerror(e) << endl;
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }


    /*  Create the compiler and tell it in which (in-memory) object theassembly code goes.
        Parse the source file and generate the assembly code if no errors were detected.
        Otherwise, stop.
    */
    TranslationUnit tu(targetPlatform);
    if (verbose)
        cout << "Compiling..." << endl;
    assert(yyin != NULL);
    yyparse();

    tu.processPragmas(codeAddress, codeAddressSetBySwitch,
                      limitAddress, limitAddressSetBySwitch, dataAddress);


    /*  On the Vectrex, the writable globals must be mapped at $C880
        while the code and readable globals are mapped at the start of memory.
    */
    if (targetPlatform == VECTREX)
        dataAddress = 0xC880;  // equivalent to #pragma data 0xC880


    tu.enableNullPointerChecking(nullPointerCheckingEnabled);

    tu.enableStackOverflowChecking(stackOverflowCheckingEnabled);

    if (verbose && targetPlatform != OS9)
    {
        cout << "Code address: $" << hex << codeAddress << dec << " (" << codeAddress << ")\n";
        cout << "Data address: ";
        if (dataAddress == 0xFFFF)
            cout << "after the code";
        else
            cout << "$" << hex << dataAddress << dec << " (" << dataAddress << ")";
        cout << "\n";
    }

    int pipeCmdStatus = preprocFileCloser.close();
    //cout << "pipeCmdStatus=" << pipeCmdStatus << endl;
    if (!WIFEXITED(pipeCmdStatus))
    {
        cout << PACKAGE << ": preprocessor terminated abnormally." << endl;
        return EXIT_FAILURE;
    }
    if (WEXITSTATUS(pipeCmdStatus) != 0)
    {
        cout << PACKAGE << ": preprocessor failed." << endl;
        return EXIT_FAILURE;
    }

    tu.checkSemantics();  // this is when Scope objects get created in FunctionDefs

    ASMText asmText;

    if (numErrors == 0)
    {
        tu.allocateLocalVariables();  // in all FunctionDef objects

        tu.emitAssembler(asmText, programName, compileOnly, codeAddress, dataAddress, assumeTrack34, emitUncalledFunctions);

        if (optimizationLevel > 0)
            asmText.peepholeOptimize(optimizationLevel == 2);
        if (wholeFunctionOptimization)
            asmText.optimizeWholeFunctions();
    }


    /*  Create a .asm file that will receive the assembly language code:
    */
    string asmFilename;
    if (numErrors == 0)
    {
        asmFilename = programName + ".asm";
        if (verbose)
        {
            cout << "Assembler: " << assemblerFilename << "\n";
            cout << "Assembly language filename: " << asmFilename << "\n";
            cout << flush;
        }
        ofstream asmFile(asmFilename.c_str(), ios::out);
        if (!asmFile)
        {
            int e = errno;
            cout << PACKAGE << ": failed to create assembler file:"
                            << " " << strerror(e) << endl;
            return EXIT_FAILURE;
        }
        if (!asmText.writeFile(asmFile))
        {
            cout << PACKAGE << ": failed to write output assembly file " << asmFilename << endl;
            return EXIT_FAILURE;
        }
        asmFile.close();
        if (!asmFile)
        {
            cout << PACKAGE << ": failed to close output assembly file " << asmFilename << endl;
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


    /*  Call the cross-assembler on the .asm file to produce .hex and
        CoCo .bin files:
    */
    stringstream ss;
    ss << assemblerFilename;
    for (list<string>::const_iterator it = includeDirList.begin(); it != includeDirList.end(); ++it)
        ss << " --includedir='" << *it << "'";
    if (targetPlatform != OS9)
        ss << " --entry=" << hex << codeAddress << dec;
    if (assumeTrack34)
        ss << " --entry=2602";
    if (limitAddress != 0xFFFF)
        ss << " --limit=" << hex << limitAddress << dec;
    ss << " --target=" << targetPreprocId;
    if (generateSREC)
        ss << " --srec";
    if (nullPointerCheckingEnabled)
        ss << " --check-null";
    if (stackOverflowCheckingEnabled)
        ss << " --check-stack";
    const set<string> &neededUtilitySubRoutines = TranslationUnit::instance().getNeededUtilitySubRoutines();
    for (set<string>::const_iterator it = neededUtilitySubRoutines.begin(); it != neededUtilitySubRoutines.end(); ++it)
        ss << " --need=" << *it;
    if (verbose)
        ss << " --verbose";
    ss << " " << asmFilename;
    string asmCommand = ss.str();

    if (asmCmd)
    {
        // Write asmCommand in a .cmd file. 
        const string asmCmdFilename = programName + ".cmd";
        if (verbose)
            cout << "Writing assembly command in " << asmCmdFilename << endl;
        ofstream asmCmdFile(asmCmdFilename.c_str(), ios::out);
        if (!asmCmdFile)
        {
            int e = errno;
            cout << PACKAGE << ": failed to create assembler command file: "
                            << strerror(e) << endl;
            return EXIT_FAILURE;
        }
        asmCmdFile << asmCommand << '\n';
        asmCmdFile.close();
        if (!asmCmdFile)
        {
            cout << PACKAGE << ": failed to close output assembly command file " << asmCmdFilename << endl;
            return EXIT_FAILURE;
        }
    }

    if (!compileOnly)  // assemble only if -c not passed
    {
        if (verbose)
            cout << "Assembling: " << asmCommand << endl;

        int status = system(asmCommand.c_str());
        if (status == -1)
        {
            int e = errno;
            cout << PACKAGE << ": could not start assembler script: " << strerror(e) << endl;
            return EXIT_FAILURE;
        }

        if (!WIFEXITED(status))
            return EXIT_FAILURE;
        return WEXITSTATUS(status);
    }
    return EXIT_SUCCESS;
}
