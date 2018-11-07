/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.yy" /* yacc.c:339  */

/*  $Id: parser.yy,v 1.78 2018/05/23 03:34:13 sarrazip Exp $

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

#include "DeclarationSequence.h"
#include "WordConstantExpr.h"
#include "RealConstantExpr.h"
#include "DWordConstantExpr.h"
#include "IdentifierExpr.h"
#include "VariableExpr.h"
#include "FunctionCallExpr.h"
#include "StringLiteralExpr.h"
#include "BinaryOpExpr.h"
#include "UnaryOpExpr.h"
#include "CastExpr.h"
#include "CompoundStmt.h"
#include "IfStmt.h"
#include "SwitchStmt.h"
#include "LabeledStmt.h"
#include "WhileStmt.h"
#include "ForStmt.h"
#include "JumpStmt.h"
#include "Scope.h"
#include "FunctionDef.h"
#include "FormalParameter.h"
#include "FormalParamList.h"
#include "AssemblerStmt.h"
#include "TranslationUnit.h"
#include "ObjectMemberExpr.h"
#include "ClassDef.h"
#include "ConditionalExpr.h"
#include "DeclarationSpecifierList.h"
#include "Pragma.h"
#include "CommaExpr.h"

#include <string.h>
#include <time.h>

using namespace std;

int yyparse(void);
int yylex(void);
void yyerror(const char *msg);
extern char *yytext;

extern string sourceFilename;  // defined in lexer.ll
extern int lineno;  // defined in lexer.ll
int numErrors = 0;  // error counter for yyerror()
int numWarnings = 0;
static bool doubleTypeWarningIssued = false;

void _PARSERTRACE(int parserLineNo, const char *fmt, ...);
#define PARSERTRACE(...) _PARSERTRACE(__LINE__, __VA_ARGS__)


#line 138 "parser.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    STRLIT = 259,
    PRAGMA = 260,
    CHARLIT = 261,
    REAL = 262,
    TYPE_NAME = 263,
    INT = 264,
    CHAR = 265,
    SHORT = 266,
    LONG = 267,
    FLOAT = 268,
    DOUBLE = 269,
    SIGNED = 270,
    UNSIGNED = 271,
    VOID = 272,
    PLUS_PLUS = 273,
    MINUS_MINUS = 274,
    IF = 275,
    ELSE = 276,
    WHILE = 277,
    DO = 278,
    FOR = 279,
    EQUALS_EQUALS = 280,
    BANG_EQUALS = 281,
    LOWER_EQUALS = 282,
    GREATER_EQUALS = 283,
    AMP_AMP = 284,
    PIPE_PIPE = 285,
    LT_LT = 286,
    GT_GT = 287,
    BREAK = 288,
    CONTINUE = 289,
    RETURN = 290,
    ASM = 291,
    NORTS = 292,
    VERBATIM_ASM = 293,
    STRUCT = 294,
    UNION = 295,
    THIS = 296,
    PLUS_EQUALS = 297,
    MINUS_EQUALS = 298,
    ASTERISK_EQUALS = 299,
    SLASH_EQUALS = 300,
    PERCENT_EQUALS = 301,
    LT_LT_EQUALS = 302,
    GT_GT_EQUALS = 303,
    CARET_EQUALS = 304,
    AMP_EQUALS = 305,
    PIPE_EQUALS = 306,
    RIGHT_ARROW = 307,
    INTERRUPT = 308,
    SIZEOF = 309,
    ELLIPSIS = 310,
    TYPEDEF = 311,
    ENUM = 312,
    SWITCH = 313,
    CASE = 314,
    DEFAULT = 315,
    REGISTER = 316,
    GOTO = 317,
    EXTERN = 318,
    STATIC = 319,
    CONST = 320,
    VOLATILE = 321,
    AUTO = 322
  };
#endif
/* Tokens.  */
#define ID 258
#define STRLIT 259
#define PRAGMA 260
#define CHARLIT 261
#define REAL 262
#define TYPE_NAME 263
#define INT 264
#define CHAR 265
#define SHORT 266
#define LONG 267
#define FLOAT 268
#define DOUBLE 269
#define SIGNED 270
#define UNSIGNED 271
#define VOID 272
#define PLUS_PLUS 273
#define MINUS_MINUS 274
#define IF 275
#define ELSE 276
#define WHILE 277
#define DO 278
#define FOR 279
#define EQUALS_EQUALS 280
#define BANG_EQUALS 281
#define LOWER_EQUALS 282
#define GREATER_EQUALS 283
#define AMP_AMP 284
#define PIPE_PIPE 285
#define LT_LT 286
#define GT_GT 287
#define BREAK 288
#define CONTINUE 289
#define RETURN 290
#define ASM 291
#define NORTS 292
#define VERBATIM_ASM 293
#define STRUCT 294
#define UNION 295
#define THIS 296
#define PLUS_EQUALS 297
#define MINUS_EQUALS 298
#define ASTERISK_EQUALS 299
#define SLASH_EQUALS 300
#define PERCENT_EQUALS 301
#define LT_LT_EQUALS 302
#define GT_GT_EQUALS 303
#define CARET_EQUALS 304
#define AMP_EQUALS 305
#define PIPE_EQUALS 306
#define RIGHT_ARROW 307
#define INTERRUPT 308
#define SIZEOF 309
#define ELLIPSIS 310
#define TYPEDEF 311
#define ENUM 312
#define SWITCH 313
#define CASE 314
#define DEFAULT 315
#define REGISTER 316
#define GOTO 317
#define EXTERN 318
#define STATIC 319
#define CONST 320
#define VOLATILE 321
#define AUTO 322

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 75 "parser.yy" /* yacc.c:355  */

    char *str;
    signed char character;
    double real;
    int integer;
    BasicType basicType;
    const TypeDesc *typeDesc;
    TypeSpecifier *typeSpecifier;
    DeclarationSpecifierList *declarationSpecifierList;
    Tree *tree;
    CompoundStmt *compoundStmt;
    TreeSequence *treeSequence;
    FormalParamList *formalParamList;
    FormalParameter *formalParameter;
    DeclarationSequence *declarationSequence;
    Declarator *declarator;
    std::vector<Declarator *> *declaratorVector;
    BinaryOpExpr::Op binop;
    UnaryOpExpr::Op unop;
    Scope *scope;
    FunctionDef *functionDef;
    std::vector<std::string> *strList;
    ClassDef *classDef;
    ClassDef::ClassMember *classMember;
    FilenameAndLineNo *filenameAndLineNo;
    std::vector<ClassDef::ClassMember *> *classMemberList;
    Enumerator *enumerator;
    std::vector<Enumerator *> *enumeratorList;
    TypeQualifierBitFieldVector *typeQualifierBitFieldVector;

#line 343 "parser.cc" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 358 "parser.cc" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1045

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  245
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  398

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     2,     2,     2,    88,    82,     2,
      70,    72,    71,    85,    69,    86,    91,    87,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    68,
      83,    75,    84,    79,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    81,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,    80,    74,    90,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   148,   148,   149,   153,   159,   168,   169,   170,   171,
     175,   204,   205,   206,   212,   213,   218,   228,   239,   255,
     259,   260,   264,   265,   269,   270,   271,   272,   276,   277,
     278,   279,   283,   288,   289,   295,   299,   308,   310,   312,
     314,   316,   318,   323,   324,   325,   326,   327,   328,   329,
     330,   334,   335,   336,   339,   340,   341,   345,   346,   350,
     351,   355,   367,   383,   384,   388,   394,   399,   408,   409,
     413,   414,   418,   419,   423,   424,   425,   426,   427,   428,
     429,   433,   445,   446,   450,   454,   458,   459,   465,   466,
     470,   474,   478,   484,   487,   493,   498,   503,   508,   515,
     521,   532,   533,   537,   541,   542,   546,   547,   548,   549,
     550,   554,   555,   559,   560,   564,   574,   587,   591,   592,
     597,   598,   599,   608,   609,   613,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   629,
     632,   635,   639,   645,   646,   650,   654,   655,   659,   660,
     664,   665,   679,   680,   684,   685,   690,   691,   692,   693,
     694,   695,   696,   697,   698,   699,   700,   704,   705,   710,
     711,   716,   717,   722,   723,   727,   728,   732,   733,   737,
     738,   743,   744,   748,   749,   753,   754,   756,   761,   762,
     763,   764,   768,   769,   773,   774,   778,   779,   783,   784,
     785,   789,   790,   810,   811,   812,   813,   817,   818,   819,
     820,   821,   822,   826,   827,   831,   832,   835,   838,   840,
     842,   844,   846,   851,   852,   853,   871,   872,   873,   877,
     878,   887,   888,   892,   893,   897,   898,   902,   906,   907,
     911,   915,   919,   923,   924,   928
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRLIT", "PRAGMA", "CHARLIT",
  "REAL", "TYPE_NAME", "INT", "CHAR", "SHORT", "LONG", "FLOAT", "DOUBLE",
  "SIGNED", "UNSIGNED", "VOID", "PLUS_PLUS", "MINUS_MINUS", "IF", "ELSE",
  "WHILE", "DO", "FOR", "EQUALS_EQUALS", "BANG_EQUALS", "LOWER_EQUALS",
  "GREATER_EQUALS", "AMP_AMP", "PIPE_PIPE", "LT_LT", "GT_GT", "BREAK",
  "CONTINUE", "RETURN", "ASM", "NORTS", "VERBATIM_ASM", "STRUCT", "UNION",
  "THIS", "PLUS_EQUALS", "MINUS_EQUALS", "ASTERISK_EQUALS", "SLASH_EQUALS",
  "PERCENT_EQUALS", "LT_LT_EQUALS", "GT_GT_EQUALS", "CARET_EQUALS",
  "AMP_EQUALS", "PIPE_EQUALS", "RIGHT_ARROW", "INTERRUPT", "SIZEOF",
  "ELLIPSIS", "TYPEDEF", "ENUM", "SWITCH", "CASE", "DEFAULT", "REGISTER",
  "GOTO", "EXTERN", "STATIC", "CONST", "VOLATILE", "AUTO", "';'", "','",
  "'('", "'*'", "')'", "'{'", "'}'", "'='", "'['", "']'", "':'", "'?'",
  "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'/'", "'%'", "'!'",
  "'~'", "'.'", "$accept", "goal", "translation_unit",
  "external_declaration", "function_definition", "parameter_type_list",
  "parameter_list", "parameter_declaration", "type_name",
  "abstract_declarator", "function_pointer_cast_opt",
  "function_pointer_cast", "pointer", "specifier_qualifier_list",
  "compound_stmt", "stmt_list_opt", "declaration",
  "declaration_specifiers", "storage_class_specifier", "type_specifier",
  "type_qualifier", "type_qualifier_list", "struct_or_union_specifier",
  "struct_or_union", "enum_specifier", "enumerator_list", "enumerator",
  "comma_opt", "non_void_basic_type", "basic_type", "save_src_fn",
  "save_line_no", "init_declarator_list", "init_declarator", "declarator",
  "direct_declarator", "subscript_list", "subscript",
  "parameter_type_list_opt", "initializer", "initializer_list",
  "struct_declaration_list_opt", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "stmt_list", "stmt", "labeled_stmt", "constant_expr", "expr_stmt",
  "expr_opt", "expr", "arg_expr_list", "assignment_expr", "assignment_op",
  "conditional_expr", "logical_or_expr", "logical_and_expr",
  "inclusive_or_expr", "exclusive_or_expr", "and_expr", "equality_expr",
  "equality_op", "rel_expr", "shift_expr", "rel_op", "add_expr", "add_op",
  "mul_expr", "mul_op", "unary_expr", "unary_op", "cast_expr",
  "postfix_expr", "primary_expr", "strlit_seq", "expr_list_opt",
  "expr_list", "selection_stmt", "if_cond", "else_part_opt", "while_stmt",
  "while_cond", "do_while_stmt", "for_init", "for_stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,    59,    44,
      40,    42,    41,   123,   125,    61,    91,    93,    58,    63,
     124,    94,    38,    60,    62,    43,    45,    47,    37,    33,
     126,    46
};
# endif

#define YYPACT_NINF -202

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-202)))

#define YYTABLE_NINF -85

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     879,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,    12,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,    55,   879,  -202,  -202,
    -202,    74,   978,   978,   978,  -202,    13,  -202,  -202,  -202,
     -23,    62,  -202,  -202,  -202,  -202,     5,   -12,    64,    31,
    -202,    58,    -6,  -202,  -202,  -202,    38,  -202,   423,    62,
      15,    70,  -202,     9,  -202,  -202,   -12,  -202,  -202,    64,
    -202,   568,  -202,   780,   102,   423,    17,   423,   423,    53,
     423,  -202,    70,   102,    62,    88,   -25,   107,  -202,  -202,
    -202,    94,  -202,  -202,  -202,  -202,  -202,   683,   683,  -202,
     716,   499,  -202,   224,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,    -7,   150,   121,   116,   127,   135,    14,   122,
      80,   -27,   324,   102,  -202,   128,  -202,   199,   138,  -202,
    -202,   139,   144,  -202,    64,   137,   147,  -202,   146,   102,
     143,    99,  -202,  -202,  -202,  -202,  -202,   148,  -202,  -202,
    -202,  -202,  -202,   153,   102,    -1,  -202,   912,   323,   102,
    -202,  -202,   499,  -202,   157,   112,    35,   151,  -202,  -202,
     -45,   102,   102,   102,   102,   102,   102,  -202,  -202,   102,
    -202,  -202,  -202,  -202,   102,   102,   102,  -202,  -202,   102,
    -202,  -202,  -202,   102,  -202,  -202,  -202,  -202,   229,   102,
     230,  -202,  -202,  -202,  -202,   945,  -202,  -202,   102,  -202,
    -202,   102,  -202,    17,  -202,   912,   158,   164,  -202,  -202,
     165,   161,   170,   171,   323,   174,   177,   179,   614,   180,
    -202,   181,   102,   176,   246,  -202,  -202,   178,  -202,    74,
     323,  -202,  -202,  -202,   117,  -202,  -202,  -202,  -202,   184,
     102,   186,   188,  -202,  -202,  -202,  -202,  -202,   525,  -202,
     150,   -29,   121,   116,   127,   135,    14,   122,    80,    80,
     -27,  -202,   732,  -202,   -52,  -202,   189,  -202,  -202,  -202,
    -202,  -202,   190,  -202,   912,  -202,  -202,   102,   102,   238,
    -202,  -202,  -202,  -202,   125,   257,   102,   185,   323,   198,
    -202,  -202,  -202,  -202,  -202,   192,  -202,  -202,  -202,   102,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,   102,  -202,   656,  -202,   195,   191,   147,   200,   147,
     201,   205,  -202,  -202,    50,    79,   323,  -202,  -202,   206,
    -202,  -202,  -202,    83,  -202,  -202,   323,   323,   323,   102,
     411,   196,   203,   323,  -202,   814,   102,  -202,  -202,   247,
    -202,   209,  -202,   147,   214,   208,  -202,   211,   213,  -202,
    -202,  -202,   215,  -202,   323,  -202,   218,  -202,   102,  -202,
     222,   223,  -202,  -202,  -202,   147,   102,  -202,  -202,   228,
    -202,  -202,   102,   220,  -202,  -202,   323,  -202
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     8,    56,    74,    75,    76,    79,    80,    81,    77,
      78,    83,    45,    46,    63,    64,    43,    44,     0,    47,
      50,    49,    57,    58,    48,     9,     0,     2,     4,     6,
       7,    93,    37,    39,    41,    52,     0,    55,    82,    51,
      67,     0,     1,     5,    92,    35,     0,    24,    93,     0,
      86,    88,    91,    38,    40,    42,    53,    54,   113,     0,
      70,    73,    68,     0,    26,    59,    25,    90,    36,    93,
      84,     0,    10,     0,   148,   113,    93,    29,    31,     0,
     114,   115,    73,     0,    72,     0,     0,     0,    27,    60,
      87,    88,    85,   223,   229,   226,   225,     0,     0,   224,
       0,     0,   210,     0,   209,   207,   208,   211,   212,    89,
     106,   154,   167,   169,   171,   173,   175,   177,   179,   183,
     185,   192,   213,     0,   196,   201,   215,   227,    83,    13,
      96,     0,    11,    14,    93,     0,   149,   150,     0,     0,
     120,     0,   118,    28,    30,    62,   116,     0,    71,   145,
     213,    69,    66,     0,   148,     0,   101,   104,    33,     0,
     203,   204,     0,   206,     0,    20,     0,     0,   109,   111,
       0,     0,     0,     0,     0,     0,     0,   181,   182,     0,
     189,   191,   188,   190,     0,     0,     0,   194,   195,     0,
     198,   199,   200,     0,    85,   202,   219,   220,     0,     0,
       0,    85,   230,    97,    95,     0,    16,    94,     0,    61,
     121,     0,   117,    93,    65,   104,     0,     0,   102,   105,
       0,   223,     0,     0,     0,     0,     0,     0,     0,    45,
     141,     0,     0,     0,     0,   146,   127,     0,   126,    93,
      34,   123,   129,   125,     0,   128,   130,   131,   132,     0,
       0,     0,    20,    17,    21,    19,   228,   110,     0,   107,
     170,     0,   172,   174,   176,   178,   180,   184,   186,   187,
     193,   197,     0,   222,     0,   221,     0,    12,    15,   151,
     122,   119,     0,   103,   104,    99,    85,     0,     0,     0,
      84,   134,   135,   136,     0,     0,     0,     0,     0,     0,
      32,   124,   147,   205,   214,     0,    18,   108,   112,     0,
     157,   158,   159,   160,   161,   165,   166,   162,   163,   164,
     156,     0,   218,     0,    98,     0,     0,   237,     0,   241,
       0,     0,    85,   137,     0,     0,     0,   144,   133,     0,
     168,   155,   216,     0,   152,   100,     0,     0,     0,     0,
     231,     0,     0,     0,   143,     0,     0,   217,   142,   238,
     240,     0,   244,   233,     0,   232,    84,     0,     0,   140,
     236,    23,     0,   153,     0,   235,     0,   243,     0,    85,
       0,     0,    22,   239,   242,   234,   148,   138,   139,     0,
      84,    85,   231,     0,    84,    85,     0,   245
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,  -202,   272,  -202,   -66,  -202,    95,   140,  -202,
      49,  -202,   -28,   -21,   252,  -202,     1,     0,  -202,   -32,
      16,  -202,  -202,  -202,  -202,   245,   221,   225,  -202,  -202,
    -120,  -183,  -202,   242,   -18,  -202,  -202,   160,  -201,   -95,
    -202,   237,  -202,   239,  -202,   104,  -202,  -172,  -202,    86,
    -202,  -148,   -70,  -202,   -68,  -202,   -73,  -202,   149,   152,
     154,   169,   145,  -202,   173,   166,  -202,    21,  -202,   134,
    -202,   -61,  -202,  -114,  -202,  -202,  -202,   -44,  -202,  -202,
    -202,  -202,  -202,     4,  -202,  -202,  -202
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    29,   219,   132,   133,   164,   252,
     253,   254,    48,    76,   236,   237,   238,   239,    32,    33,
      34,    66,    35,    36,    37,    61,    62,    85,    38,    39,
      92,   158,    49,    50,    91,    52,   155,   156,   220,   109,
     170,    79,    80,    81,   141,   142,   240,   241,   242,   148,
     243,   135,   244,   343,   137,   321,   111,   112,   113,   114,
     115,   116,   117,   179,   118,   119,   184,   120,   189,   121,
     193,   122,   123,   124,   125,   126,   127,   364,   365,   245,
     328,   375,   246,   330,   247,   366,   248
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,    30,   194,   110,   136,   201,   216,   131,   169,   195,
     149,   272,    86,    51,   282,    40,    56,   208,   276,    64,
      44,    57,   150,   171,   258,   322,    77,    31,    30,   259,
      67,   166,    53,    54,    55,   110,   160,   161,    88,   163,
     208,   180,   181,    77,   190,    77,    77,   153,    77,   309,
      59,   154,   289,    22,    23,    42,   143,   144,   140,    47,
     191,   192,   150,    65,    73,    60,   210,    44,   301,    77,
      74,   217,   172,   134,    78,   154,    63,    44,   150,   271,
     165,    87,    89,   325,   136,    41,    58,    46,    47,   166,
      83,    78,   166,    78,    78,   139,    78,   182,   183,    68,
      69,   286,   261,   326,   208,    93,    94,   256,    95,    96,
     150,    75,   150,   150,   150,   150,   206,    78,   150,   351,
      97,    98,   352,   150,   150,   150,   337,   145,   150,   274,
      77,    70,   150,    71,    46,    47,   304,   255,   280,    84,
     279,   165,    45,    99,    46,    47,   196,   197,   208,   350,
     150,   353,   356,   185,   186,   357,   100,   134,   294,   149,
     177,   178,   152,   308,   354,   187,   188,   212,   213,    71,
     332,   150,   101,   102,   358,   359,   360,   157,    78,   173,
     198,   370,   251,    47,   104,   302,   208,   105,   106,   150,
     110,   107,   108,   333,   208,   140,   386,   175,   -84,   367,
     368,   174,   383,   202,   199,   134,   268,   269,   392,   176,
     203,   204,   396,   205,   207,   134,   208,   327,   329,   200,
     209,   211,   214,   215,   397,   257,   335,    93,    94,   250,
      95,    96,   273,   275,   284,   283,   340,   285,   389,   -84,
     287,   288,    97,    98,   290,   291,   379,   292,   150,   299,
     295,   296,   300,   341,   298,   344,   303,   305,   251,   323,
     331,   334,   324,   336,   339,    99,   338,   345,   374,   346,
     391,   369,   347,   348,   395,   349,   355,   378,   100,   329,
     363,   376,   377,   380,   134,   381,   384,   382,   373,   372,
     387,   388,   394,   167,   101,   102,   390,   103,   168,    43,
     278,   306,   249,    72,    82,   151,   104,   147,   385,   105,
     106,    90,   138,   107,   108,   218,   136,   281,   297,   146,
     260,   265,   363,   270,     0,   262,   221,    94,   263,    95,
      96,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    97,    98,   222,   264,   223,   224,   225,   393,     0,
     267,   362,   266,   361,     0,   134,   226,   227,   228,   229,
      13,   230,    14,    15,    99,     0,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,    16,   100,     0,    17,
      18,   231,   232,   233,    19,   234,    20,    21,    22,    23,
      24,   235,     0,   101,   102,     0,    70,     0,     0,   -84,
       0,     0,     0,     0,     0,   104,     0,     0,   105,   106,
       0,     0,   107,   108,    93,    94,     0,    95,    96,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    97,
      98,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,     0,    12,    13,     0,
      14,    15,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    15,    16,   100,     0,    17,    18,     0,
       0,     0,    19,     0,    20,    21,    22,    23,    24,     0,
      18,   101,   102,     0,     0,     0,     0,     0,    22,    23,
       0,     0,     0,   104,     0,     0,   105,   106,     0,     0,
     107,   108,    93,    94,     0,    95,    96,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    97,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    94,
       0,    95,    96,     0,     0,     0,     0,     0,    14,    15,
      99,     0,     0,    97,    98,     0,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,    22,    23,    99,     0,     0,   101,
     102,    93,    94,     0,    95,    96,     0,     0,     0,   100,
       0,   104,     0,     0,   105,   106,    97,    98,   107,   108,
       0,     0,     0,     0,     0,   101,   102,     0,   103,   307,
       0,     0,     0,     0,     0,     0,     0,   104,     0,    99,
     105,   106,     0,     0,   107,   108,     0,    93,    94,     0,
      95,    96,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    98,     0,     0,     0,     0,   101,   102,
       0,   103,     0,     0,     0,     0,     0,     0,     0,     0,
     104,     0,     0,   105,   106,    99,     0,   107,   108,    93,
      94,     0,    95,    96,     0,     0,     0,     0,   100,     0,
       0,     0,     0,     0,    97,    98,     0,     0,     0,     0,
       0,     0,   293,     0,   101,   102,    93,    94,     0,    95,
      96,     0,     0,     0,     0,     0,   104,    99,     0,   105,
     106,    97,    98,   107,   108,     0,     0,     0,     0,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,    93,
      94,     0,    95,    96,    99,     0,   101,   102,   342,     0,
       0,     0,     0,     0,    97,    98,     0,   100,   104,     0,
       0,   105,   106,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,   159,   102,     0,     0,    99,     0,     0,
       0,     0,     0,     0,     0,   104,     0,     0,   105,   106,
     100,     0,   107,   108,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,     0,     0,   162,   102,     2,     3,
       4,     5,     6,     7,     8,     9,    10,   128,   104,     0,
       0,   105,   106,     0,     0,   107,   108,   320,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,     0,    14,
      15,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,    16,     0,   129,    17,    18,     0,     0,
       0,    19,     0,    20,    21,    22,    23,    24,     0,     0,
      12,    13,   130,    14,    15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,     0,   129,
      17,    18,     0,     0,     0,    19,     0,    20,    21,    22,
      23,    24,     0,     0,     1,     0,   371,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,     0,    14,    15,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,    16,     0,     0,    17,    18,     0,     0,     0,
      19,     0,    20,    21,    22,    23,    24,    25,    12,    13,
       0,    14,    15,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,    16,     0,   129,    17,    18,
       0,     0,     0,    19,     0,    20,    21,    22,    23,    24,
       0,    12,    13,     0,    14,    15,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,    16,     0,
     277,    17,    18,     0,     0,     0,    19,     0,    20,    21,
      22,    23,    24,     0,    12,    13,     0,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     0,     0,    17,    18,     0,     0,     0,    19,
       0,    20,    21,    22,    23,    24
};

static const yytype_int16 yycheck[] =
{
       0,     0,   122,    71,    74,   125,   154,    73,   103,   123,
      83,   194,     3,    31,   215,     3,     3,    69,   201,    47,
       3,     8,    83,    30,    69,    77,    58,    27,    27,    74,
      48,   101,    32,    33,    34,   103,    97,    98,    66,   100,
      69,    27,    28,    75,    71,    77,    78,    72,    80,    78,
      73,    76,   224,    65,    66,     0,    77,    78,    76,    71,
      87,    88,   123,    47,    70,     3,   139,     3,   240,   101,
      76,    72,    79,    73,    58,    76,    71,     3,   139,   193,
     101,    72,    66,   284,   154,    73,    73,    70,    71,   159,
      75,    75,   162,    77,    78,    78,    80,    83,    84,    68,
      69,   221,   172,   286,    69,     3,     4,    72,     6,     7,
     171,    73,   173,   174,   175,   176,   134,   101,   179,    69,
      18,    19,    72,   184,   185,   186,   298,    74,   189,   199,
     162,    73,   193,    75,    70,    71,   250,   165,   211,    69,
     208,   162,    68,    41,    70,    71,    18,    19,    69,   332,
     211,    72,    69,    31,    32,    72,    54,   157,   228,   232,
      25,    26,    74,   258,   336,    85,    86,    68,    69,    75,
     290,   232,    70,    71,   346,   347,   348,    70,   162,    29,
      52,   353,    70,    71,    82,    68,    69,    85,    86,   250,
     258,    89,    90,    68,    69,   213,   379,    81,    70,     3,
       4,    80,   374,     4,    76,   205,   185,   186,   391,    82,
      72,    72,   395,    69,    77,   215,    69,   287,   288,    91,
      74,    78,    74,    70,   396,    74,   296,     3,     4,    72,
       6,     7,     3,     3,    70,    77,   309,    72,   386,    78,
      70,    70,    18,    19,    70,    68,   366,    68,   309,     3,
      70,    70,    74,   321,    78,   323,    72,    71,    70,    70,
      22,     4,    72,    78,    72,    41,    68,    72,    21,    78,
     390,    68,    72,    72,   394,    70,    70,    69,    54,   349,
     350,    72,    68,    72,   284,    72,    68,    72,   356,   355,
      68,    68,    72,    69,    70,    71,    68,    73,    74,    27,
     205,   252,   162,    51,    59,    84,    82,    82,   378,    85,
      86,    69,    75,    89,    90,   155,   386,   213,   232,    80,
     171,   176,   392,   189,    -1,   173,     3,     4,   174,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,   175,    22,    23,    24,   392,    -1,
     184,   350,   179,   349,    -1,   355,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    53,    54,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    70,    71,    -1,    73,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    -1,    89,    90,     3,     4,    -1,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    53,    54,    -1,    56,    57,    -1,
      -1,    -1,    61,    -1,    63,    64,    65,    66,    67,    -1,
      57,    70,    71,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    -1,
      89,    90,     3,     4,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,     6,     7,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    41,    -1,    -1,    70,
      71,     3,     4,    -1,     6,     7,    -1,    -1,    -1,    54,
      -1,    82,    -1,    -1,    85,    86,    18,    19,    89,    90,
      -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    41,
      85,    86,    -1,    -1,    89,    90,    -1,     3,     4,    -1,
       6,     7,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    70,    71,
      -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    41,    -1,    89,    90,     3,
       4,    -1,     6,     7,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    71,     3,     4,    -1,     6,
       7,    -1,    -1,    -1,    -1,    -1,    82,    41,    -1,    85,
      86,    18,    19,    89,    90,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,     6,     7,    41,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    18,    19,    -1,    54,    82,    -1,
      -1,    85,    86,    -1,    -1,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      54,    -1,    89,    90,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    70,    71,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    82,    -1,
      -1,    85,    86,    -1,    -1,    89,    90,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    39,
      40,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    53,    -1,    55,    56,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    65,    66,    67,    -1,    -1,
      36,    37,    72,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    55,
      56,    57,    -1,    -1,    -1,    61,    -1,    63,    64,    65,
      66,    67,    -1,    -1,     5,    -1,    72,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    39,    40,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    53,    -1,    -1,    56,    57,    -1,    -1,    -1,
      61,    -1,    63,    64,    65,    66,    67,    68,    36,    37,
      -1,    39,    40,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    53,    -1,    55,    56,    57,
      -1,    -1,    -1,    61,    -1,    63,    64,    65,    66,    67,
      -1,    36,    37,    -1,    39,    40,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    53,    -1,
      55,    56,    57,    -1,    -1,    -1,    61,    -1,    63,    64,
      65,    66,    67,    -1,    36,    37,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    56,    57,    -1,    -1,    -1,    61,
      -1,    63,    64,    65,    66,    67
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    36,    37,    39,    40,    53,    56,    57,    61,
      63,    64,    65,    66,    67,    68,    93,    94,    95,    96,
     108,   109,   110,   111,   112,   114,   115,   116,   120,   121,
       3,    73,     0,    95,     3,    68,    70,    71,   104,   124,
     125,   126,   127,   109,   109,   109,     3,     8,    73,    73,
       3,   117,   118,    71,   104,   112,   113,   126,    68,    69,
      73,    75,   106,    70,    76,    73,   105,   111,   112,   133,
     134,   135,   117,    75,    69,   119,     3,    72,   104,   112,
     125,   126,   122,     3,     4,     6,     7,    18,    19,    41,
      54,    70,    71,    73,    82,    85,    86,    89,    90,   131,
     146,   148,   149,   150,   151,   152,   153,   154,   156,   157,
     159,   161,   163,   164,   165,   166,   167,   168,    17,    55,
      72,    97,    98,    99,   109,   143,   144,   146,   133,    78,
     126,   136,   137,   105,   105,    74,   135,   119,   141,   148,
     163,   118,    74,    72,    76,   128,   129,    70,   123,    70,
     163,   163,    70,   163,   100,   105,   144,    69,    74,   131,
     132,    30,    79,    29,    80,    81,    82,    25,    26,   155,
      27,    28,    83,    84,   158,    31,    32,    85,    86,   160,
      71,    87,    88,   162,   122,   165,    18,    19,    52,    76,
      91,   122,     4,    72,    72,    69,   126,    77,    69,    74,
     148,    78,    68,    69,    74,    70,   143,    72,   129,    97,
     130,     3,    20,    22,    23,    24,    33,    34,    35,    36,
      38,    58,    59,    60,    62,    68,   106,   107,   108,   109,
     138,   139,   140,   142,   144,   171,   174,   176,   178,   100,
      72,    70,   101,   102,   103,   104,    72,    74,    69,    74,
     150,   144,   151,   152,   153,   154,   156,   157,   159,   159,
     161,   165,   123,     3,   144,     3,   123,    55,    99,   146,
     148,   137,   130,    77,    70,    72,   122,    70,    70,   139,
      70,    68,    68,    68,   144,    70,    70,   141,    78,     3,
      74,   139,    68,    72,   165,    71,   102,    74,   131,    78,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      75,   147,    77,    70,    72,   130,   123,   144,   172,   144,
     175,    22,   122,    68,     4,   144,    78,   139,    68,    72,
     148,   146,    72,   145,   146,    72,    78,    72,    72,    70,
     123,    69,    72,    72,   139,    70,    69,    72,   139,   139,
     139,   175,   108,   144,   169,   170,   177,     3,     4,    68,
     139,    72,    97,   146,    21,   173,    72,    68,    69,   122,
      72,    72,    72,   139,    68,   144,   123,    68,    68,   143,
      68,   122,   123,   169,    72,   122,   123,   139
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    94,    94,    95,    95,    95,    95,
      96,    97,    97,    97,    98,    98,    99,   100,   100,   101,
     102,   102,   103,   103,   104,   104,   104,   104,   105,   105,
     105,   105,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   111,   111,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   121,   122,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   129,   130,   130,   131,   131,   131,   131,
     131,   132,   132,   133,   133,   134,   134,   135,   136,   136,
     137,   137,   137,   138,   138,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   140,   140,   140,   141,   142,   142,   143,   143,
     144,   144,   145,   145,   146,   146,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   148,   148,   149,
     149,   150,   150,   151,   151,   152,   152,   153,   153,   154,
     154,   155,   155,   156,   156,   157,   157,   157,   158,   158,
     158,   158,   159,   159,   160,   160,   161,   161,   162,   162,
     162,   163,   163,   163,   163,   163,   163,   164,   164,   164,
     164,   164,   164,   165,   165,   166,   166,   166,   166,   166,
     166,   166,   166,   167,   167,   167,   167,   167,   167,   168,
     168,   169,   169,   170,   170,   171,   171,   172,   173,   173,
     174,   175,   176,   177,   177,   178
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     3,     2,     2,     3,     1,
       0,     1,     6,     5,     1,     2,     2,     3,     2,     1,
       2,     1,     5,     0,     1,     2,     3,     1,     2,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       2,     5,     4,     1,     1,     6,     5,     2,     1,     3,
       1,     3,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     0,     1,     3,     1,     3,
       2,     1,     1,     0,     4,     4,     3,     4,     7,     6,
       8,     1,     2,     3,     0,     1,     1,     3,     4,     2,
       3,     1,     3,     0,     1,     1,     2,     3,     1,     3,
       1,     2,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     2,     3,     7,     7,
       5,     1,     5,     4,     3,     1,     1,     2,     0,     1,
       1,     3,     1,     3,     1,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     2,     2,     2,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     5,     6,     4,     2,
       2,     3,     3,     1,     1,     1,     1,     1,     3,     1,
       2,     0,     1,     1,     3,     6,     5,     1,     0,     2,
       5,     1,     7,     2,     1,    16
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 148 "parser.yy" /* yacc.c:1646  */
    { TranslationUnit::instance().setDefinitionList((yyvsp[0].treeSequence)); }
#line 1887 "parser.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 149 "parser.yy" /* yacc.c:1646  */
    { TranslationUnit::instance().setDefinitionList(NULL); }
#line 1893 "parser.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 154 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.treeSequence) = new TreeSequence();
                if ((yyvsp[0].tree))
                    (yyval.treeSequence)->addTree((yyvsp[0].tree)); 
            }
#line 1903 "parser.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 160 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.treeSequence) = (yyvsp[-1].treeSequence);
                if ((yyvsp[0].tree))
                    (yyval.treeSequence)->addTree((yyvsp[0].tree));
            }
#line 1913 "parser.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 168 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].functionDef); }
#line 1919 "parser.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 169 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].declarationSequence); }
#line 1925 "parser.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 170 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new Pragma((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1931 "parser.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 171 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1937 "parser.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 176 "parser.yy" /* yacc.c:1646  */
    {
                DeclarationSpecifierList *dsl = (yyvsp[-2].declarationSpecifierList);
                Declarator *di = (yyvsp[-1].declarator);

                if (dsl->hasEnumeratorList())
                {
                    errormsg("enum with enumerated names is not supported in a function's return type");
                    dsl->detachEnumeratorList();
                }
                if (dsl->isStaticDeclaration() && dsl->isExternDeclaration())
                {
                    errormsg("function definition must not be both static and extern");
                }

                // Example: In byte **f() {}, dsl represents "byte" and
                // di represents **f. Hence, di contains a pointer level of 2,
                // which is applied to the TypeDesc found in dsl, i.e., "byte".
                // di also contains the name of the function, "f".
                //
                (yyval.functionDef) = new FunctionDef(*dsl, *di);
                (yyval.functionDef)->setLineNo(di->getSourceFilename(), di->getLineNo());
                (yyval.functionDef)->setBody((yyvsp[0].compoundStmt));
                delete di;
                delete dsl;
            }
#line 1967 "parser.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 204 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 1973 "parser.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 205 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = (yyvsp[-2].formalParamList); (yyval.formalParamList)->endWithEllipsis(); }
#line 1979 "parser.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 206 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = new FormalParamList(); (yyval.formalParamList)->endWithEllipsis(); }
#line 1985 "parser.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 212 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = new FormalParamList(); if ((yyvsp[0].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[0].formalParameter)); }
#line 1991 "parser.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 214 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = (yyvsp[-2].formalParamList); if ((yyvsp[0].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[0].formalParameter)); }
#line 1997 "parser.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 219 "parser.yy" /* yacc.c:1646  */
    {
                    DeclarationSpecifierList *dsl = (yyvsp[-1].declarationSpecifierList);
                    (yyval.formalParameter) = (yyvsp[0].declarator)->createFormalParameter(*dsl);
                    delete dsl;
                    delete (yyvsp[0].declarator);
                }
#line 2008 "parser.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 229 "parser.yy" /* yacc.c:1646  */
    {
                    if ((yyvsp[0].formalParamList))
                    {
                        (yyval.typeDesc) = TranslationUnit::getTypeManager().getFunctionPointerType((yyvsp[-1].declarationSpecifierList)->getTypeDesc(), *(yyvsp[0].formalParamList), (yyvsp[-1].declarationSpecifierList)->isInterruptServiceFunction());
                        delete (yyvsp[0].formalParamList);
                    }
                    else
                        (yyval.typeDesc) = (yyvsp[-1].declarationSpecifierList)->getTypeDesc();
                    delete (yyvsp[-1].declarationSpecifierList);
                }
#line 2023 "parser.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 240 "parser.yy" /* yacc.c:1646  */
    {
                    const TypeDesc *td = TranslationUnit::getTypeManager().getPointerTo((yyvsp[-2].declarationSpecifierList)->getTypeDesc(), *(yyvsp[-1].typeQualifierBitFieldVector));
                    if ((yyvsp[0].formalParamList))
                    {
                        (yyval.typeDesc) = TranslationUnit::getTypeManager().getFunctionPointerType(td, *(yyvsp[0].formalParamList), (yyvsp[-2].declarationSpecifierList)->isInterruptServiceFunction());
                        delete (yyvsp[0].formalParamList);
                    }
                    else
                        (yyval.typeDesc) = td;
                    delete (yyvsp[-1].typeQualifierBitFieldVector);  /* originally created by 'pointer' rule */
                    delete (yyvsp[-2].declarationSpecifierList);
                }
#line 2040 "parser.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 255 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); }
#line 2046 "parser.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 259 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = NULL; }
#line 2052 "parser.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 260 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2058 "parser.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 264 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = (yyvsp[-1].formalParamList); }
#line 2064 "parser.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 265 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = new FormalParamList(); }
#line 2070 "parser.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 269 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeQualifierBitFieldVector) = new TypeQualifierBitFieldVector(); (yyval.typeQualifierBitFieldVector)->push_back(0); }
#line 2076 "parser.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 270 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeQualifierBitFieldVector) = new TypeQualifierBitFieldVector(); (yyval.typeQualifierBitFieldVector)->push_back(TypeQualifierBitField((yyvsp[0].integer))); }
#line 2082 "parser.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 271 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); (yyval.typeQualifierBitFieldVector)->push_back(0); }
#line 2088 "parser.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 272 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); (yyval.typeQualifierBitFieldVector)->push_back((yyvsp[-1].integer)); }
#line 2094 "parser.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 276 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[-1].typeSpecifier)); delete (yyvsp[-1].typeSpecifier); }
#line 2100 "parser.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 277 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[0].typeSpecifier)); delete (yyvsp[0].typeSpecifier); }
#line 2106 "parser.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 278 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2112 "parser.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 279 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2118 "parser.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 284 "parser.yy" /* yacc.c:1646  */
    { (yyval.compoundStmt) = (yyvsp[-1].compoundStmt); (yyval.compoundStmt)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer)); free((yyvsp[-3].str)); }
#line 2124 "parser.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 288 "parser.yy" /* yacc.c:1646  */
    { (yyval.compoundStmt) = new CompoundStmt(); }
#line 2130 "parser.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 289 "parser.yy" /* yacc.c:1646  */
    { (yyval.compoundStmt) = (yyvsp[0].compoundStmt); }
#line 2136 "parser.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 296 "parser.yy" /* yacc.c:1646  */
    {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[-1].declarationSpecifierList), NULL);  // deletes $1
                        }
#line 2144 "parser.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 300 "parser.yy" /* yacc.c:1646  */
    {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[-2].declarationSpecifierList), (yyvsp[-1].declaratorVector));  // deletes $1 and $2
                        }
#line 2152 "parser.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 309 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2158 "parser.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 311 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2164 "parser.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 313 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[0].typeSpecifier)); delete (yyvsp[0].typeSpecifier); }
#line 2170 "parser.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 315 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[-1].typeSpecifier)); delete (yyvsp[-1].typeSpecifier); }
#line 2176 "parser.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 317 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2182 "parser.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 319 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2188 "parser.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 323 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::INTERRUPT_SPEC; }
#line 2194 "parser.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 324 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::TYPEDEF_SPEC; }
#line 2200 "parser.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 325 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::ASSEMBLY_ONLY_SPEC; }
#line 2206 "parser.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 326 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::NO_RETURN_INSTRUCTION; }
#line 2212 "parser.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 327 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = -1; /* not supported, ignored */ }
#line 2218 "parser.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 328 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = -1; /* not supported, ignored */ }
#line 2224 "parser.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 329 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::STATIC_SPEC; }
#line 2230 "parser.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 330 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::EXTERN_SPEC; }
#line 2236 "parser.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 334 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2242 "parser.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 335 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2248 "parser.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 336 "parser.yy" /* yacc.c:1646  */
    { const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[0].str), (yyvsp[-1].integer) == UNION, true);
                                      (yyval.typeSpecifier) = new TypeSpecifier(td, "", NULL);
                                      free((yyvsp[0].str)); }
#line 2256 "parser.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 339 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2262 "parser.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 340 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeSpecifier) = (yyvsp[0].typeSpecifier); }
#line 2268 "parser.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 341 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2274 "parser.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 345 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::CONST_QUALIFIER; }
#line 2280 "parser.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 346 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = DeclarationSpecifierList::VOLATILE_QUALIFIER; TranslationUnit::instance().warnAboutVolatile(); }
#line 2286 "parser.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 350 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = ((yyvsp[0].integer) == DeclarationSpecifierList::CONST_QUALIFIER ? CONST_BIT : VOLATILE_BIT); }
#line 2292 "parser.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 351 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-1].integer) | ((yyvsp[0].integer) == DeclarationSpecifierList::CONST_QUALIFIER ? CONST_BIT : VOLATILE_BIT); }
#line 2298 "parser.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 356 "parser.yy" /* yacc.c:1646  */
    {
                        ClassDef *classDef = (yyvsp[-1].classDef);
                        assert(classDef);
                        classDef->setName((yyvsp[-3].str));
                        classDef->setUnion((yyvsp[-4].integer) == UNION);
                        TranslationUnit::instance().getGlobalScope().declareClass(classDef);
                        const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[-3].str), (yyvsp[-4].integer) == UNION, true);
                        assert(td);
                        (yyval.typeDesc) = td;
                        free((yyvsp[-3].str));
                    }
#line 2314 "parser.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 368 "parser.yy" /* yacc.c:1646  */
    {
                        string anonStructName = "AnonStruct_" + (yyvsp[-1].classDef)->getLineNo();
                        ClassDef *classDef = (yyvsp[-1].classDef);
                        assert(classDef);
                        classDef->setName(anonStructName);
                        classDef->setUnion((yyvsp[-3].integer) == UNION);
                        TranslationUnit::instance().getGlobalScope().declareClass(classDef);
                        const TypeDesc *td = TranslationUnit::getTypeManager().getClassType(anonStructName, (yyvsp[-3].integer) == UNION, true);
                        assert(td);
                        (yyval.typeDesc) = td;
                    }
#line 2330 "parser.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 383 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = STRUCT; }
#line 2336 "parser.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 384 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = UNION;  }
#line 2342 "parser.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 389 "parser.yy" /* yacc.c:1646  */
    {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[-4].str), (yyvsp[-2].enumeratorList));
                            free((yyvsp[-4].str));
                        }
#line 2352 "parser.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 395 "parser.yy" /* yacc.c:1646  */
    {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, "", (yyvsp[-2].enumeratorList));
                        }
#line 2361 "parser.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 400 "parser.yy" /* yacc.c:1646  */
    {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[0].str), NULL);
                            free((yyvsp[0].str));
                        }
#line 2371 "parser.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 408 "parser.yy" /* yacc.c:1646  */
    { (yyval.enumeratorList) = new vector<Enumerator *>(); (yyval.enumeratorList)->push_back((yyvsp[0].enumerator)); }
#line 2377 "parser.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 409 "parser.yy" /* yacc.c:1646  */
    { (yyval.enumeratorList) = (yyvsp[-2].enumeratorList); (yyval.enumeratorList)->push_back((yyvsp[0].enumerator)); }
#line 2383 "parser.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 413 "parser.yy" /* yacc.c:1646  */
    { (yyval.enumerator) = new Enumerator((yyvsp[0].str), NULL, getSourceLineNo()); free((yyvsp[0].str)); }
#line 2389 "parser.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 414 "parser.yy" /* yacc.c:1646  */
    { (yyval.enumerator) = new Enumerator((yyvsp[-2].str), (yyvsp[0].tree),   getSourceLineNo()); free((yyvsp[-2].str)); }
#line 2395 "parser.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 423 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
#line 2401 "parser.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 424 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, true); }
#line 2407 "parser.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 425 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
#line 2413 "parser.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 426 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(true);  }
#line 2419 "parser.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 427 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(false); }
#line 2425 "parser.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 428 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getLongType(true); }
#line 2431 "parser.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 429 "parser.yy" /* yacc.c:1646  */
    {
                    TranslationUnit::instance().warnIfFloatUnsupported();
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getRealType(false);
                }
#line 2440 "parser.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 433 "parser.yy" /* yacc.c:1646  */
    {
                    TranslationUnit::instance().warnIfFloatUnsupported();
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getRealType(false);
                    if (!doubleTypeWarningIssued)
                    {
                        warnmsg("`double' is an alias for `float' for this compiler");
                        doubleTypeWarningIssued = true;
                    }
                }
#line 2454 "parser.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 445 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = (yyvsp[0].typeDesc); }
#line 2460 "parser.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 446 "parser.yy" /* yacc.c:1646  */
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getVoidType(); }
#line 2466 "parser.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 450 "parser.yy" /* yacc.c:1646  */
    { (yyval.str) = strdup(sourceFilename.c_str()); }
#line 2472 "parser.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 454 "parser.yy" /* yacc.c:1646  */
    { (yyval.integer) = lineno; }
#line 2478 "parser.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 458 "parser.yy" /* yacc.c:1646  */
    { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2484 "parser.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 459 "parser.yy" /* yacc.c:1646  */
    { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2490 "parser.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 465 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2496 "parser.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 466 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[-2].declarator); (yyval.declarator)->setInitExpr((yyvsp[0].tree)); }
#line 2502 "parser.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 470 "parser.yy" /* yacc.c:1646  */
    {
                                            (yyval.declarator) = (yyvsp[0].declarator);
                                            (yyval.declarator)->setPointerLevel((yyvsp[-1].typeQualifierBitFieldVector));  // ownership of $1 transfered to the Declarator
                                        }
#line 2511 "parser.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 474 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2517 "parser.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 479 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = new Declarator((yyvsp[0].str), sourceFilename, lineno);
                free((yyvsp[0].str));
            }
#line 2526 "parser.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 484 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = new Declarator(string(), sourceFilename, lineno);
            }
#line 2534 "parser.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 488 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->checkForFunctionReturningArray();
                (yyval.declarator)->addArraySizeExpr((yyvsp[-1].tree));
            }
#line 2544 "parser.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 494 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->setFormalParamList((yyvsp[-1].formalParamList));
            }
#line 2553 "parser.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 499 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = (yyvsp[-2].declarator);
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
#line 2562 "parser.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 504 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
#line 2571 "parser.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 509 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = new Declarator((yyvsp[-4].str), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                free((yyvsp[-4].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2582 "parser.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 516 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = new Declarator(string(), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2592 "parser.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 522 "parser.yy" /* yacc.c:1646  */
    {
                (yyval.declarator) = new Declarator((yyvsp[-5].str), sourceFilename, lineno);
                (yyval.declarator)->setAsArrayOfFunctionPointers((yyvsp[-1].formalParamList), (yyvsp[-4].treeSequence));  // takes ownership of FormalParamList ($7), deletes $4
                free((yyvsp[-5].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2603 "parser.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 532 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2609 "parser.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 533 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = (yyvsp[-1].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2615 "parser.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 537 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 2621 "parser.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 541 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = new FormalParamList(); }
#line 2627 "parser.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 542 "parser.yy" /* yacc.c:1646  */
    { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2633 "parser.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 546 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2639 "parser.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 547 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].treeSequence); }
#line 2645 "parser.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 548 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-2].treeSequence); }
#line 2651 "parser.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 549 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new TreeSequence(); }
#line 2657 "parser.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 550 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new TreeSequence(); }
#line 2663 "parser.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 554 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2669 "parser.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 555 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = (yyvsp[-2].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2675 "parser.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 559 "parser.yy" /* yacc.c:1646  */
    { (yyval.classDef) = new ClassDef(); }
#line 2681 "parser.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 560 "parser.yy" /* yacc.c:1646  */
    { (yyval.classDef) = (yyvsp[0].classDef); }
#line 2687 "parser.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 565 "parser.yy" /* yacc.c:1646  */
    {
                    (yyval.classDef) = new ClassDef();
                    if ((yyvsp[0].classMemberList))
                        for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[0].classMemberList)->begin(); it != (yyvsp[0].classMemberList)->end(); ++it)
                            (yyval.classDef)->addDataMember(*it);
                    else
                        assert(0);
                    delete (yyvsp[0].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
#line 2701 "parser.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 575 "parser.yy" /* yacc.c:1646  */
    {
                    (yyval.classDef) = (yyvsp[-1].classDef);
                    if ((yyvsp[0].classMemberList))
                        for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[0].classMemberList)->begin(); it != (yyvsp[0].classMemberList)->end(); ++it)
                            (yyval.classDef)->addDataMember(*it);
                    else
                        assert(0);
                    delete (yyvsp[0].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
#line 2715 "parser.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 587 "parser.yy" /* yacc.c:1646  */
    { (yyval.classMemberList) = ClassDef::createClassMembers((yyvsp[-2].declarationSpecifierList), (yyvsp[-1].declaratorVector)); }
#line 2721 "parser.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 591 "parser.yy" /* yacc.c:1646  */
    { (yyval.declaratorVector) = new std::vector<Declarator *>(); if ((yyvsp[0].declarator)) (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2727 "parser.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 592 "parser.yy" /* yacc.c:1646  */
    { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); if ((yyvsp[0].declarator)) (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2733 "parser.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 597 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2739 "parser.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 598 "parser.yy" /* yacc.c:1646  */
    { (yyval.declarator) = NULL; }
#line 2745 "parser.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 600 "parser.yy" /* yacc.c:1646  */
    {
                    (yyval.declarator) = (yyvsp[-2].declarator);
                    (yyval.declarator)->setBitFieldWidth(*(yyvsp[0].tree));  // emits error if $3 is not constant expression
                    delete (yyvsp[0].tree);
                }
#line 2755 "parser.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 608 "parser.yy" /* yacc.c:1646  */
    { (yyval.compoundStmt) = new CompoundStmt(); if ((yyvsp[0].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[0].tree)); }
#line 2761 "parser.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 609 "parser.yy" /* yacc.c:1646  */
    { (yyval.compoundStmt) = (yyvsp[-1].compoundStmt); if ((yyvsp[0].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[0].tree)); }
#line 2767 "parser.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 613 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2773 "parser.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 614 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = ((yyvsp[0].declarationSequence) ? (yyvsp[0].declarationSequence) : new TreeSequence()); }
#line 2779 "parser.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 615 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].compoundStmt); }
#line 2785 "parser.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 616 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2791 "parser.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 617 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2797 "parser.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 618 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2803 "parser.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 619 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2809 "parser.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 620 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2815 "parser.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 621 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new JumpStmt((yyvsp[-1].str)); free((yyvsp[-1].str)); }
#line 2821 "parser.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 622 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new JumpStmt(JumpStmt::BRK, NULL); }
#line 2827 "parser.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 623 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new JumpStmt(JumpStmt::CONT, NULL); }
#line 2833 "parser.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 624 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new JumpStmt(JumpStmt::RET, NULL); }
#line 2839 "parser.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 625 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new JumpStmt(JumpStmt::RET, (yyvsp[-1].tree)); }
#line 2845 "parser.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 627 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new AssemblerStmt((yyvsp[-4].str), (yyvsp[-2].str), true);
                          free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 2852 "parser.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 630 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new AssemblerStmt((yyvsp[-4].str), (yyvsp[-2].str), false);
                          free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 2859 "parser.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 633 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new AssemblerStmt((yyvsp[-2].str), "", false);
                          free((yyvsp[-2].str)); }
#line 2866 "parser.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 635 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new AssemblerStmt(yytext); }
#line 2872 "parser.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 640 "parser.yy" /* yacc.c:1646  */
    {
                                      (yyval.tree) = new LabeledStmt((yyvsp[-4].str), TranslationUnit::instance().generateLabel('L'), (yyvsp[0].tree));
                                      (yyval.tree)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer));
                                      free((yyvsp[-4].str)); free((yyvsp[-3].str));
                                    }
#line 2882 "parser.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 645 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new LabeledStmt((yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 2888 "parser.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 646 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new LabeledStmt((yyvsp[0].tree)); }
#line 2894 "parser.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 650 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2900 "parser.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 654 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new TreeSequence(); }
#line 2906 "parser.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 655 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 2912 "parser.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 659 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2918 "parser.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 660 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2924 "parser.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 664 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2930 "parser.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 665 "parser.yy" /* yacc.c:1646  */
    {
                                    Tree *left = (yyvsp[-2].tree);
                                    Tree *right = (yyvsp[0].tree);
                                    if (CommaExpr *ts = dynamic_cast<CommaExpr *>(left))
                                    {
                                        ts->addTree(right);
                                        (yyval.tree) = ts;
                                    }
                                    else
                                        (yyval.tree) = new CommaExpr(left, right);
                                }
#line 2946 "parser.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 679 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2952 "parser.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 680 "parser.yy" /* yacc.c:1646  */
    { (yyvsp[-2].treeSequence)->addTree((yyvsp[0].tree)); (yyval.treeSequence) = (yyvsp[-2].treeSequence); }
#line 2958 "parser.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 684 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2964 "parser.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 686 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-4].tree), (yyvsp[0].tree)); free((yyvsp[-3].str)); }
#line 2970 "parser.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 690 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::ASSIGNMENT; }
#line 2976 "parser.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 691 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::INC_ASSIGN; }
#line 2982 "parser.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 692 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::DEC_ASSIGN; }
#line 2988 "parser.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 693 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::MUL_ASSIGN; }
#line 2994 "parser.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 694 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::DIV_ASSIGN; }
#line 3000 "parser.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 695 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::MOD_ASSIGN; }
#line 3006 "parser.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 696 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::XOR_ASSIGN; }
#line 3012 "parser.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 697 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::AND_ASSIGN; }
#line 3018 "parser.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 698 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::OR_ASSIGN; }
#line 3024 "parser.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 699 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::LEFT_ASSIGN; }
#line 3030 "parser.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 700 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::RIGHT_ASSIGN; }
#line 3036 "parser.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 704 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3042 "parser.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 706 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new ConditionalExpr((yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3048 "parser.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 710 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3054 "parser.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 712 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3060 "parser.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 716 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3066 "parser.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 718 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3072 "parser.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 722 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3078 "parser.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 724 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3084 "parser.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 727 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3090 "parser.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 729 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_XOR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3096 "parser.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 732 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3102 "parser.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 734 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3108 "parser.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 737 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3114 "parser.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 739 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3120 "parser.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 743 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::EQUALITY; }
#line 3126 "parser.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 744 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::INEQUALITY; }
#line 3132 "parser.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 748 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3138 "parser.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 749 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3144 "parser.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 753 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3150 "parser.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 754 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::LEFT_SHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3157 "parser.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 756 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::RIGHT_SHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3164 "parser.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 761 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::INFERIOR; }
#line 3170 "parser.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 762 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::INFERIOR_OR_EQUAL; }
#line 3176 "parser.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 763 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::SUPERIOR; }
#line 3182 "parser.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 764 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::SUPERIOR_OR_EQUAL; }
#line 3188 "parser.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 768 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3194 "parser.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 769 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3200 "parser.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 773 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::ADD; }
#line 3206 "parser.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 774 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::SUB; }
#line 3212 "parser.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 778 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3218 "parser.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 779 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3224 "parser.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 783 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::MUL; }
#line 3230 "parser.cc" /* yacc.c:1646  */
    break;

  case 199:
#line 784 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::DIV; }
#line 3236 "parser.cc" /* yacc.c:1646  */
    break;

  case 200:
#line 785 "parser.yy" /* yacc.c:1646  */
    { (yyval.binop) = BinaryOpExpr::MOD; }
#line 3242 "parser.cc" /* yacc.c:1646  */
    break;

  case 201:
#line 789 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3248 "parser.cc" /* yacc.c:1646  */
    break;

  case 202:
#line 790 "parser.yy" /* yacc.c:1646  */
    {
                                    RealConstantExpr *rce;
                                    DWordConstantExpr *dwce;
                                    if ((yyvsp[-1].unop) == UnaryOpExpr::NEG && (rce = dynamic_cast<RealConstantExpr *>((yyvsp[0].tree))) != NULL)
                                    {
                                        // We have the negation of a real constant.
                                        // Simplify by negating the value in the RealConstantExpr and getting rid of the negation operator.
                                        rce->negateValue();
                                        (yyval.tree) = rce;
                                    }
                                    else if ((yyvsp[-1].unop) == UnaryOpExpr::NEG && (dwce = dynamic_cast<DWordConstantExpr *>((yyvsp[0].tree))) != NULL)
                                    {
                                        dwce->negateValue();
                                        (yyval.tree) = dwce;
                                    }
                                    else
                                    {
                                        (yyval.tree) = new UnaryOpExpr((yyvsp[-1].unop), (yyvsp[0].tree));
                                    }
                                }
#line 3273 "parser.cc" /* yacc.c:1646  */
    break;

  case 203:
#line 810 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREINC, (yyvsp[0].tree)); }
#line 3279 "parser.cc" /* yacc.c:1646  */
    break;

  case 204:
#line 811 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREDEC, (yyvsp[0].tree)); }
#line 3285 "parser.cc" /* yacc.c:1646  */
    break;

  case 205:
#line 812 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new UnaryOpExpr((yyvsp[-1].typeDesc)); }
#line 3291 "parser.cc" /* yacc.c:1646  */
    break;

  case 206:
#line 813 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::SIZE_OF, (yyvsp[0].tree)); }
#line 3297 "parser.cc" /* yacc.c:1646  */
    break;

  case 207:
#line 817 "parser.yy" /* yacc.c:1646  */
    { (yyval.unop) = UnaryOpExpr::IDENTITY; }
#line 3303 "parser.cc" /* yacc.c:1646  */
    break;

  case 208:
#line 818 "parser.yy" /* yacc.c:1646  */
    { (yyval.unop) = UnaryOpExpr::NEG; }
#line 3309 "parser.cc" /* yacc.c:1646  */
    break;

  case 209:
#line 819 "parser.yy" /* yacc.c:1646  */
    { (yyval.unop) = UnaryOpExpr::ADDRESS_OF; }
#line 3315 "parser.cc" /* yacc.c:1646  */
    break;

  case 210:
#line 820 "parser.yy" /* yacc.c:1646  */
    { (yyval.unop) = UnaryOpExpr::INDIRECTION; }
#line 3321 "parser.cc" /* yacc.c:1646  */
    break;

  case 211:
#line 821 "parser.yy" /* yacc.c:1646  */
    { (yyval.unop) = UnaryOpExpr::BOOLEAN_NEG; }
#line 3327 "parser.cc" /* yacc.c:1646  */
    break;

  case 212:
#line 822 "parser.yy" /* yacc.c:1646  */
    { (yyval.unop) = UnaryOpExpr::BITWISE_NOT; }
#line 3333 "parser.cc" /* yacc.c:1646  */
    break;

  case 213:
#line 826 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3339 "parser.cc" /* yacc.c:1646  */
    break;

  case 214:
#line 827 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new CastExpr((yyvsp[-2].typeDesc), (yyvsp[0].tree)); }
#line 3345 "parser.cc" /* yacc.c:1646  */
    break;

  case 215:
#line 831 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3351 "parser.cc" /* yacc.c:1646  */
    break;

  case 216:
#line 833 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new FunctionCallExpr((yyvsp[-4].tree), new TreeSequence());
                          free((yyvsp[-3].str)); }
#line 3358 "parser.cc" /* yacc.c:1646  */
    break;

  case 217:
#line 836 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new FunctionCallExpr((yyvsp[-5].tree), (yyvsp[-1].treeSequence));
                          free((yyvsp[-4].str)); }
#line 3365 "parser.cc" /* yacc.c:1646  */
    break;

  case 218:
#line 839 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::ARRAY_REF, (yyvsp[-3].tree), (yyvsp[-1].tree)); }
#line 3371 "parser.cc" /* yacc.c:1646  */
    break;

  case 219:
#line 841 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTINC, (yyvsp[-1].tree)); }
#line 3377 "parser.cc" /* yacc.c:1646  */
    break;

  case 220:
#line 843 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTDEC, (yyvsp[-1].tree)); }
#line 3383 "parser.cc" /* yacc.c:1646  */
    break;

  case 221:
#line 845 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new ObjectMemberExpr((yyvsp[-2].tree), (yyvsp[0].str), true); free((yyvsp[0].str)); }
#line 3389 "parser.cc" /* yacc.c:1646  */
    break;

  case 222:
#line 847 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new ObjectMemberExpr((yyvsp[-2].tree), (yyvsp[0].str), false); free((yyvsp[0].str)); }
#line 3395 "parser.cc" /* yacc.c:1646  */
    break;

  case 223:
#line 851 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new IdentifierExpr((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 3401 "parser.cc" /* yacc.c:1646  */
    break;

  case 224:
#line 852 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new IdentifierExpr("this"); }
#line 3407 "parser.cc" /* yacc.c:1646  */
    break;

  case 225:
#line 853 "parser.yy" /* yacc.c:1646  */
    {
                            bool isHexOrBin = (yytext[0] == '0' && (tolower(yytext[1]) == 'x' || tolower(yytext[1]) == 'b'));
                            double value = (yyvsp[0].real);
                            if (!isHexOrBin
                                    && (strchr(yytext, '.') || strchr(yytext, 'e') || strchr(yytext, 'E')))  // if point or exponential
                            {
                                (yyval.tree) = new RealConstantExpr(value, yytext);
                            }
                            else if (strchr(yytext, 'l') || strchr(yytext, 'L') || value > 65535.0 || value <= -32769.0)
                            {
                                bool uSuffix = (strchr(yytext, 'u') || strchr(yytext, 'U'));
                                (yyval.tree) = new DWordConstantExpr(value, !uSuffix && value <= 0x7FFFFFFFUL);
                            } 
                            else
                            {
                                (yyval.tree) = new WordConstantExpr(value, yytext);
                            }
                        }
#line 3430 "parser.cc" /* yacc.c:1646  */
    break;

  case 226:
#line 871 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new WordConstantExpr((int8_t) (yyvsp[0].character), false, true); }
#line 3436 "parser.cc" /* yacc.c:1646  */
    break;

  case 227:
#line 872 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new StringLiteralExpr((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 3442 "parser.cc" /* yacc.c:1646  */
    break;

  case 228:
#line 873 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 3448 "parser.cc" /* yacc.c:1646  */
    break;

  case 229:
#line 877 "parser.yy" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 3454 "parser.cc" /* yacc.c:1646  */
    break;

  case 230:
#line 878 "parser.yy" /* yacc.c:1646  */
    {
                            (yyval.str) = (char *) malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 1);
                            strcpy((yyval.str), (yyvsp[-1].str));
                            strcat((yyval.str), (yyvsp[0].str));
                            free((yyvsp[-1].str)); free((yyvsp[0].str));
                        }
#line 3465 "parser.cc" /* yacc.c:1646  */
    break;

  case 231:
#line 887 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = NULL; }
#line 3471 "parser.cc" /* yacc.c:1646  */
    break;

  case 232:
#line 888 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = (yyvsp[0].treeSequence); }
#line 3477 "parser.cc" /* yacc.c:1646  */
    break;

  case 233:
#line 892 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3483 "parser.cc" /* yacc.c:1646  */
    break;

  case 234:
#line 893 "parser.yy" /* yacc.c:1646  */
    { (yyval.treeSequence) = (yyvsp[-2].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3489 "parser.cc" /* yacc.c:1646  */
    break;

  case 235:
#line 897 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new IfStmt((yyvsp[-3].tree), (yyvsp[-1].tree), (yyvsp[0].tree)); }
#line 3495 "parser.cc" /* yacc.c:1646  */
    break;

  case 236:
#line 898 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new SwitchStmt((yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3501 "parser.cc" /* yacc.c:1646  */
    break;

  case 237:
#line 902 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3507 "parser.cc" /* yacc.c:1646  */
    break;

  case 238:
#line 906 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 3513 "parser.cc" /* yacc.c:1646  */
    break;

  case 239:
#line 907 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3519 "parser.cc" /* yacc.c:1646  */
    break;

  case 240:
#line 911 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new WhileStmt((yyvsp[-2].tree), (yyvsp[0].tree), false); }
#line 3525 "parser.cc" /* yacc.c:1646  */
    break;

  case 241:
#line 915 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 3531 "parser.cc" /* yacc.c:1646  */
    break;

  case 242:
#line 919 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = new WhileStmt((yyvsp[-2].tree), (yyvsp[-5].tree), true); }
#line 3537 "parser.cc" /* yacc.c:1646  */
    break;

  case 243:
#line 923 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].treeSequence); }
#line 3543 "parser.cc" /* yacc.c:1646  */
    break;

  case 244:
#line 924 "parser.yy" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].declarationSequence); }
#line 3549 "parser.cc" /* yacc.c:1646  */
    break;

  case 245:
#line 932 "parser.yy" /* yacc.c:1646  */
    { if ( (yyvsp[-11].tree))  (yyvsp[-11].tree)->setLineNo((yyvsp[-13].str), (yyvsp[-12].integer));
                                  if ( (yyvsp[-8].tree))  (yyvsp[-8].tree)->setLineNo((yyvsp[-10].str), (yyvsp[-9].integer));
                                  if ((yyvsp[-4].treeSequence)) (yyvsp[-4].treeSequence)->setLineNo((yyvsp[-6].str), (yyvsp[-5].integer));
                                  (yyvsp[0].tree)->setLineNo((yyvsp[-2].str), (yyvsp[-1].integer));
                                  (yyval.tree) = new ForStmt((yyvsp[-11].tree), (yyvsp[-8].tree), (yyvsp[-4].treeSequence), (yyvsp[0].tree));
                                  free((yyvsp[-13].str)); free((yyvsp[-10].str)); free((yyvsp[-6].str)); free((yyvsp[-2].str));
                                }
#line 3561 "parser.cc" /* yacc.c:1646  */
    break;


#line 3565 "parser.cc" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 941 "parser.yy" /* yacc.c:1906  */


#if 0
void _PARSERTRACE(int parserLineNo, const char *fmt, ...)
{
    printf("# P%d U%d: ", parserLineNo, lineno);
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    putchar('\n');
    fflush(stdout);
}
#endif
