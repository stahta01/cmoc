/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.yy"

/*  $Id: parser.yy,v 1.37 2016/10/08 18:15:06 sarrazip Exp $

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

void rejectTypeKeyword(const char *keyword)
{
    errormsg("unsupported type keyword `%s'", keyword);
}



/* Line 268 of yacc.c  */
#line 142 "parser.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     VERBATIM_ASM = 292,
     STRUCT = 293,
     UNION = 294,
     THIS = 295,
     PLUS_EQUALS = 296,
     MINUS_EQUALS = 297,
     ASTERISK_EQUALS = 298,
     SLASH_EQUALS = 299,
     PERCENT_EQUALS = 300,
     LT_LT_EQUALS = 301,
     GT_GT_EQUALS = 302,
     CARET_EQUALS = 303,
     AMP_EQUALS = 304,
     PIPE_EQUALS = 305,
     RIGHT_ARROW = 306,
     INTERRUPT = 307,
     SIZEOF = 308,
     ELLIPSIS = 309,
     TYPEDEF = 310,
     ENUM = 311,
     SWITCH = 312,
     CASE = 313,
     DEFAULT = 314,
     REGISTER = 315,
     GOTO = 316,
     EXTERN = 317,
     STATIC = 318,
     CONST = 319,
     VOLATILE = 320,
     AUTO = 321
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
#define VERBATIM_ASM 292
#define STRUCT 293
#define UNION 294
#define THIS 295
#define PLUS_EQUALS 296
#define MINUS_EQUALS 297
#define ASTERISK_EQUALS 298
#define SLASH_EQUALS 299
#define PERCENT_EQUALS 300
#define LT_LT_EQUALS 301
#define GT_GT_EQUALS 302
#define CARET_EQUALS 303
#define AMP_EQUALS 304
#define PIPE_EQUALS 305
#define RIGHT_ARROW 306
#define INTERRUPT 307
#define SIZEOF 308
#define ELLIPSIS 309
#define TYPEDEF 310
#define ENUM 311
#define SWITCH 312
#define CASE 313
#define DEFAULT 314
#define REGISTER 315
#define GOTO 316
#define EXTERN 317
#define STATIC 318
#define CONST 319
#define VOLATILE 320
#define AUTO 321




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 73 "parser.yy"

    char *str;
    char character;
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
    Declaration *declaration;
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



/* Line 293 of yacc.c  */
#line 343 "parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 355 "parser.cc"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   956

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  81
/* YYNRULES -- Number of rules.  */
#define YYNRULES  217
/* YYNRULES -- Number of states.  */
#define YYNSTATES  354

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    88,     2,     2,     2,    87,    81,     2,
      75,    76,    68,    84,    67,    85,    90,    86,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    71,
      82,    72,    83,    78,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    74,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    79,    70,    89,     2,     2,     2,
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
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    20,
      22,    26,    28,    30,    34,    37,    39,    42,    44,    46,
      49,    52,    54,    60,    61,    63,    66,    70,    72,    75,
      77,    80,    82,    84,    86,    88,    90,    92,    94,    96,
      98,   101,   103,   105,   111,   116,   118,   120,   127,   133,
     136,   138,   142,   144,   148,   150,   151,   153,   155,   157,
     159,   161,   163,   165,   167,   169,   171,   173,   174,   175,
     177,   181,   183,   187,   190,   192,   194,   195,   200,   205,
     209,   214,   222,   229,   230,   232,   234,   238,   243,   245,
     249,   250,   252,   254,   257,   261,   263,   267,   269,   271,
     274,   276,   278,   280,   282,   284,   286,   288,   290,   294,
     297,   300,   303,   307,   315,   323,   329,   331,   337,   342,
     346,   348,   350,   353,   354,   356,   358,   360,   366,   368,
     370,   372,   374,   376,   378,   380,   382,   384,   386,   388,
     390,   396,   398,   402,   404,   408,   410,   414,   416,   420,
     422,   426,   428,   432,   434,   436,   438,   442,   444,   448,
     452,   454,   456,   458,   460,   462,   466,   468,   470,   472,
     476,   478,   480,   482,   484,   487,   490,   493,   498,   501,
     503,   505,   507,   509,   511,   513,   515,   520,   522,   528,
     535,   540,   543,   546,   550,   554,   556,   558,   560,   562,
     564,   568,   570,   573,   574,   576,   578,   582,   589,   595,
     597,   598,   601,   607,   609,   617,   620,   622
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      92,     0,    -1,    93,    -1,    94,    -1,    93,    94,    -1,
      95,    -1,   105,    -1,     5,    -1,   106,   122,   103,    -1,
      97,    -1,    97,    67,    54,    -1,    54,    -1,    98,    -1,
      97,    67,    98,    -1,   106,   122,    -1,   102,    -1,   102,
     100,    -1,   101,    -1,    68,    -1,    68,   101,    -1,   108,
     102,    -1,   108,    -1,    69,   118,   119,   104,    70,    -1,
      -1,   132,    -1,   106,    71,    -1,   106,   120,    71,    -1,
     107,    -1,   107,   106,    -1,   108,    -1,   108,   106,    -1,
      52,    -1,    55,    -1,    36,    -1,    60,    -1,    66,    -1,
      63,    -1,    62,    -1,   117,    -1,   109,    -1,   110,     3,
      -1,   111,    -1,     8,    -1,   110,     3,    69,   127,    70,
      -1,   110,    69,   127,    70,    -1,    38,    -1,    39,    -1,
      56,     3,    69,   112,   114,    70,    -1,    56,    69,   112,
     114,    70,    -1,    56,     3,    -1,   113,    -1,   112,    67,
     113,    -1,     3,    -1,     3,    72,   138,    -1,    67,    -1,
      -1,     9,    -1,    10,    -1,    11,    -1,    15,    -1,    16,
      -1,   116,    -1,    12,    -1,    13,    -1,    14,    -1,   115,
      -1,    17,    -1,    -1,    -1,   121,    -1,   120,    67,   121,
      -1,   122,    -1,   122,    72,   125,    -1,   101,   122,    -1,
     123,    -1,     3,    -1,    -1,   123,    73,   137,    74,    -1,
     123,    75,    96,    76,    -1,   123,    75,    76,    -1,   123,
      75,    17,    76,    -1,    75,    68,     3,    76,    75,   124,
      76,    -1,    75,    68,    76,    75,   124,    76,    -1,    -1,
      96,    -1,   139,    -1,    69,   126,    70,    -1,    69,   126,
      67,    70,    -1,   125,    -1,   126,    67,   125,    -1,    -1,
     128,    -1,   129,    -1,   128,   129,    -1,   102,   130,    71,
      -1,   131,    -1,   130,    67,   131,    -1,   122,    -1,   133,
      -1,   132,   133,    -1,   136,    -1,   105,    -1,   103,    -1,
     164,    -1,   134,    -1,   167,    -1,   169,    -1,   171,    -1,
      61,     3,    71,    -1,    33,    71,    -1,    34,    71,    -1,
      35,    71,    -1,    35,   138,    71,    -1,    36,    75,     4,
      67,     3,    76,    71,    -1,    36,    75,     4,    67,     4,
      76,    71,    -1,    36,    75,     4,    76,    71,    -1,    37,
      -1,     3,   118,   119,    77,   133,    -1,    58,   135,    77,
     133,    -1,    59,    77,   133,    -1,   141,    -1,    71,    -1,
     138,    71,    -1,    -1,   138,    -1,   139,    -1,   141,    -1,
     156,   118,   119,   140,   139,    -1,    72,    -1,    41,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,    48,    -1,
      49,    -1,    50,    -1,    46,    -1,    47,    -1,   142,    -1,
     142,    78,   138,    77,   141,    -1,   143,    -1,   142,    30,
     143,    -1,   144,    -1,   143,    29,   144,    -1,   145,    -1,
     144,    79,   145,    -1,   146,    -1,   145,    80,   146,    -1,
     147,    -1,   146,    81,   147,    -1,   149,    -1,   147,   148,
     149,    -1,    25,    -1,    26,    -1,   150,    -1,   149,   151,
     150,    -1,   152,    -1,   150,    31,   152,    -1,   150,    32,
     152,    -1,    82,    -1,    27,    -1,    83,    -1,    28,    -1,
     154,    -1,   152,   153,   154,    -1,    84,    -1,    85,    -1,
     158,    -1,   154,   155,   158,    -1,    68,    -1,    86,    -1,
      87,    -1,   159,    -1,   157,   158,    -1,    18,   156,    -1,
      19,   156,    -1,    53,    75,    99,    76,    -1,    53,   156,
      -1,    84,    -1,    85,    -1,    81,    -1,    68,    -1,    88,
      -1,    89,    -1,   156,    -1,    75,    99,    76,   158,    -1,
     160,    -1,   159,   118,   119,    75,    76,    -1,   159,   118,
     119,    75,   163,    76,    -1,   159,    73,   138,    74,    -1,
     159,    18,    -1,   159,    19,    -1,   159,    90,     3,    -1,
     159,    51,     3,    -1,     3,    -1,    40,    -1,     7,    -1,
       6,    -1,   161,    -1,    75,   138,    76,    -1,     4,    -1,
     161,     4,    -1,    -1,   163,    -1,   138,    -1,   163,    67,
     138,    -1,    20,    75,   165,    76,   133,   166,    -1,    57,
      75,   138,    76,   133,    -1,   138,    -1,    -1,    21,   133,
      -1,    22,    75,   168,    76,   133,    -1,   138,    -1,    23,
     133,    22,    75,   168,    76,    71,    -1,   162,    71,    -1,
     105,    -1,    24,    75,   118,   119,   170,   118,   119,   137,
      71,   118,   119,   162,    76,   118,   119,   133,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   145,   145,   149,   155,   164,   165,   166,   170,   195,
     196,   197,   203,   204,   209,   219,   220,   228,   232,   233,
     237,   238,   242,   247,   248,   254,   258,   267,   269,   271,
     273,   278,   279,   280,   281,   282,   283,   284,   288,   289,
     290,   293,   294,   298,   310,   326,   327,   331,   337,   342,
     351,   352,   356,   357,   361,   362,   366,   367,   368,   369,
     370,   371,   376,   377,   378,   382,   383,   387,   391,   395,
     396,   402,   403,   407,   412,   416,   422,   425,   430,   435,
     440,   446,   454,   464,   465,   469,   470,   471,   475,   476,
     480,   481,   485,   492,   502,   506,   507,   511,   517,   518,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   538,   541,   544,   548,   554,   555,
     559,   563,   564,   568,   569,   573,   577,   578,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   597,
     598,   603,   604,   609,   610,   615,   616,   620,   621,   625,
     626,   630,   631,   636,   637,   641,   642,   646,   647,   649,
     654,   655,   656,   657,   661,   662,   666,   667,   671,   672,
     676,   677,   678,   682,   683,   684,   685,   686,   687,   691,
     692,   693,   694,   695,   696,   700,   701,   705,   706,   709,
     712,   714,   716,   718,   720,   725,   726,   727,   728,   729,
     730,   734,   735,   744,   745,   749,   750,   754,   755,   759,
     763,   764,   768,   772,   776,   780,   781,   785
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRLIT", "PRAGMA", "CHARLIT",
  "REAL", "TYPE_NAME", "INT", "CHAR", "SHORT", "LONG", "FLOAT", "DOUBLE",
  "SIGNED", "UNSIGNED", "VOID", "PLUS_PLUS", "MINUS_MINUS", "IF", "ELSE",
  "WHILE", "DO", "FOR", "EQUALS_EQUALS", "BANG_EQUALS", "LOWER_EQUALS",
  "GREATER_EQUALS", "AMP_AMP", "PIPE_PIPE", "LT_LT", "GT_GT", "BREAK",
  "CONTINUE", "RETURN", "ASM", "VERBATIM_ASM", "STRUCT", "UNION", "THIS",
  "PLUS_EQUALS", "MINUS_EQUALS", "ASTERISK_EQUALS", "SLASH_EQUALS",
  "PERCENT_EQUALS", "LT_LT_EQUALS", "GT_GT_EQUALS", "CARET_EQUALS",
  "AMP_EQUALS", "PIPE_EQUALS", "RIGHT_ARROW", "INTERRUPT", "SIZEOF",
  "ELLIPSIS", "TYPEDEF", "ENUM", "SWITCH", "CASE", "DEFAULT", "REGISTER",
  "GOTO", "EXTERN", "STATIC", "CONST", "VOLATILE", "AUTO", "','", "'*'",
  "'{'", "'}'", "';'", "'='", "'['", "']'", "'('", "')'", "':'", "'?'",
  "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'/'", "'%'", "'!'",
  "'~'", "'.'", "$accept", "goal", "translation_unit",
  "external_declaration", "function_definition", "parameter_type_list",
  "parameter_list", "parameter_declaration", "type_name",
  "abstract_declarator", "pointer", "specifier_qualifier_list",
  "compound_stmt", "stmt_list_opt", "declaration",
  "declaration_specifiers", "storage_class_specifier", "type_specifier",
  "struct_or_union_specifier", "struct_or_union", "enum_specifier",
  "enumerator_list", "enumerator", "comma_opt", "non_void_basic_type",
  "unsupported_basic_type", "basic_type", "save_src_fn", "save_line_no",
  "init_declarator_list", "init_declarator", "declarator",
  "direct_declarator", "parameter_type_list_opt", "initializer",
  "initializer_list", "struct_declaration_list_opt",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "stmt_list", "stmt",
  "labeled_stmt", "constant_expr", "expr_stmt", "expr_opt", "expr",
  "assignment_expr", "assignment_op", "conditional_expr",
  "logical_or_expr", "logical_and_expr", "inclusive_or_expr",
  "exclusive_or_expr", "and_expr", "equality_expr", "equality_op",
  "rel_expr", "shift_expr", "rel_op", "add_expr", "add_op", "mul_expr",
  "mul_op", "unary_expr", "unary_op", "cast_expr", "postfix_expr",
  "primary_expr", "strlit_seq", "expr_list_opt", "expr_list",
  "selection_stmt", "if_cond", "else_part_opt", "while_stmt", "while_cond",
  "do_while_stmt", "for_init", "for_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,    44,    42,   123,
     125,    59,    61,    91,    93,    40,    41,    58,    63,   124,
      94,    38,    60,    62,    43,    45,    47,    37,    33,   126,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    93,    93,    94,    94,    94,    95,    96,
      96,    96,    97,    97,    98,    99,    99,   100,   101,   101,
     102,   102,   103,   104,   104,   105,   105,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   108,   108,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   115,   115,
     115,   115,   116,   116,   116,   117,   117,   118,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   125,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   130,   130,   131,   132,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   134,   134,   134,
     135,   136,   136,   137,   137,   138,   139,   139,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   150,
     151,   151,   151,   151,   152,   152,   153,   153,   154,   154,
     155,   155,   155,   156,   156,   156,   156,   156,   156,   157,
     157,   157,   157,   157,   157,   158,   158,   159,   159,   159,
     159,   159,   159,   159,   159,   160,   160,   160,   160,   160,
     160,   161,   161,   162,   162,   163,   163,   164,   164,   165,
     166,   166,   167,   168,   169,   170,   170,   171
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     3,     1,
       3,     1,     1,     3,     2,     1,     2,     1,     1,     2,
       2,     1,     5,     0,     1,     2,     3,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     5,     4,     1,     1,     6,     5,     2,
       1,     3,     1,     3,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     0,     1,
       3,     1,     3,     2,     1,     1,     0,     4,     4,     3,
       4,     7,     6,     0,     1,     1,     3,     4,     1,     3,
       0,     1,     1,     2,     3,     1,     3,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     2,     3,     7,     7,     5,     1,     5,     4,     3,
       1,     1,     2,     0,     1,     1,     1,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     2,     2,     2,     4,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     5,     6,
       4,     2,     2,     3,     3,     1,     1,     1,     1,     1,
       3,     1,     2,     0,     1,     1,     3,     6,     5,     1,
       0,     2,     5,     1,     7,     2,     1,    16
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    42,    56,    57,    58,    62,    63,    64,    59,
      60,    66,    33,    45,    46,    31,    32,     0,    34,    37,
      36,    35,     0,     2,     3,     5,     6,    76,    27,    29,
      39,     0,    41,    65,    61,    38,    49,     0,     1,     4,
      75,    18,    25,     0,    76,     0,    69,    71,    74,    28,
      30,    40,    90,     0,    52,    55,    50,    19,     0,    73,
      76,    26,    67,     0,     8,   123,     0,    90,    76,    21,
       0,    91,    92,    55,     0,    54,     0,     0,     0,    70,
      71,    68,   195,   201,   198,   197,     0,     0,   196,     0,
     182,     0,     0,   181,   179,   180,   183,   184,    72,    85,
     126,   139,   141,   143,   145,   147,   149,   151,   155,   157,
     164,   185,     0,   168,   173,   187,   199,     0,   124,   125,
      66,    11,    79,     0,     9,    12,    76,     0,    97,     0,
      95,    20,    44,    93,     0,    53,    51,    48,     0,    83,
      23,     0,   175,   176,     0,   178,    88,     0,     0,    15,
       0,     0,     0,     0,     0,     0,     0,   153,   154,     0,
     161,   163,   160,   162,     0,     0,     0,   166,   167,     0,
     170,   171,   172,     0,    68,   185,   174,   191,   192,     0,
       0,     0,    68,   202,    77,    80,    78,     0,    14,    43,
      76,    94,    47,    83,    84,     0,   195,     0,     0,     0,
       0,     0,     0,     0,    33,   116,     0,     0,     0,     0,
     121,   102,     0,   101,    76,    24,    98,   104,   100,     0,
     103,   105,   106,   107,     0,     0,    86,     0,    16,    17,
     200,   142,     0,   144,   146,   148,   150,   152,   156,   158,
     159,   165,   169,     0,   194,     0,   193,     0,    10,    13,
      96,     0,    82,    68,     0,     0,     0,    67,   109,   110,
     111,     0,     0,     0,     0,   120,     0,     0,    22,    99,
     122,   177,    87,    89,   186,     0,   129,   130,   131,   132,
     133,   137,   138,   134,   135,   136,   128,     0,   190,     0,
      81,     0,   209,     0,   213,     0,     0,    68,   112,     0,
       0,     0,   119,   108,   140,   127,   188,   205,     0,     0,
       0,     0,     0,   203,     0,     0,     0,   118,     0,   189,
     117,   210,   212,     0,   216,     0,   204,    67,     0,     0,
     115,   208,   206,     0,   207,     0,   215,    68,     0,     0,
     211,   214,   123,   113,   114,     0,    67,    68,   203,     0,
      67,    68,     0,   217
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    24,    25,   194,   124,   125,   148,   228,
      44,    68,   211,   212,   213,   214,    28,    29,    30,    31,
      32,    55,    56,    76,    33,    34,    35,    81,   140,    45,
      46,    80,    48,   195,    98,   147,    70,    71,    72,   129,
     130,   215,   216,   217,   264,   218,   117,   219,   119,   287,
     100,   101,   102,   103,   104,   105,   106,   159,   107,   108,
     164,   109,   169,   110,   173,   111,   112,   113,   114,   115,
     116,   325,   326,   220,   293,   334,   221,   295,   222,   327,
     223
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -194
static const yytype_int16 yypact[] =
{
     745,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,    10,  -194,  -194,
    -194,  -194,    32,   745,  -194,  -194,  -194,    30,   868,   868,
    -194,    31,  -194,  -194,  -194,  -194,   -12,    43,  -194,  -194,
    -194,    -5,  -194,     3,    34,   -49,  -194,    -7,    -1,  -194,
    -194,    23,   900,    43,    -4,    37,  -194,  -194,    21,  -194,
      34,  -194,  -194,   474,  -194,   589,   713,   900,    34,   900,
      36,   900,  -194,    37,   589,    43,    38,    51,    54,  -194,
      40,  -194,  -194,  -194,  -194,  -194,   613,   613,  -194,   631,
    -194,   474,   456,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,    -9,   101,    52,    53,    55,    14,    28,    20,    35,
     -39,   166,   589,  -194,    42,  -194,   130,    66,  -194,  -194,
      65,  -194,  -194,    67,    75,  -194,    34,    74,  -194,   -13,
    -194,  -194,  -194,  -194,    77,  -194,  -194,  -194,    76,   804,
     282,   589,  -194,  -194,   456,  -194,  -194,    -3,    73,    -5,
      78,   589,   589,   589,   589,   589,   589,  -194,  -194,   589,
    -194,  -194,  -194,  -194,   589,   589,   589,  -194,  -194,   589,
    -194,  -194,  -194,   589,  -194,  -194,  -194,  -194,  -194,   147,
     589,   149,  -194,  -194,  -194,  -194,  -194,   836,  -194,  -194,
      34,  -194,  -194,   804,  -194,    79,    81,    84,    85,   282,
      86,    82,    91,   498,    88,  -194,    92,   589,    89,   153,
    -194,  -194,    98,  -194,    30,   282,  -194,  -194,  -194,    99,
    -194,  -194,  -194,  -194,    93,   177,  -194,   589,  -194,  -194,
    -194,   101,    95,    52,    53,    55,    14,    28,    20,    35,
      35,   -39,  -194,   283,  -194,   100,  -194,   102,  -194,  -194,
    -194,    97,  -194,  -194,   589,   589,   154,  -194,  -194,  -194,
    -194,   107,   175,   589,   105,  -194,   282,   115,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,   589,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,   589,  -194,   571,
    -194,   110,  -194,   112,  -194,   116,   118,  -194,  -194,   -23,
     121,   282,  -194,  -194,  -194,  -194,  -194,  -194,   -17,   282,
     282,   282,   589,   369,    72,   127,   282,  -194,   589,  -194,
    -194,   180,  -194,   126,  -194,   132,   137,  -194,   143,   144,
    -194,  -194,  -194,   282,  -194,   135,  -194,  -194,   150,   151,
    -194,  -194,   589,  -194,  -194,   152,  -194,  -194,   589,   148,
    -194,  -194,   282,  -194
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,  -194,   203,  -194,   162,  -194,    44,    90,  -194,
     -35,   -54,   182,  -194,     0,     7,  -194,   -26,  -194,  -194,
    -194,   179,   158,   163,  -194,  -194,  -194,  -109,  -162,  -194,
     183,   -19,  -194,    46,   -87,  -194,   168,  -194,   169,  -194,
      60,  -194,  -188,  -194,  -194,  -194,  -100,   -64,   -60,  -194,
    -193,  -194,   104,   103,   106,    96,   108,  -194,    94,    80,
    -194,   -40,  -194,   111,  -194,   -70,  -194,  -103,  -194,  -194,
    -194,   -91,   -30,  -194,  -194,  -194,  -194,   -45,  -194,  -194,
    -194
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -68
static const yytype_int16 yytable[] =
{
      26,   118,   174,    99,   146,   182,    57,    27,    47,   176,
     135,   256,   243,    36,   265,   131,   142,   143,    60,   145,
     247,   151,    61,    26,    77,    59,    69,   269,   150,   170,
      27,    99,    38,    40,    51,    49,    50,    40,   149,   157,
     158,    69,   175,    69,   314,    69,    54,   171,   172,   128,
     318,   165,   166,   315,   190,   160,   161,    53,   191,   319,
     177,   178,    62,    41,   225,    63,    69,   226,    74,   152,
     242,    58,    65,   126,    66,   328,   329,   150,   302,    37,
     150,   175,   304,   175,   175,   175,   175,   253,   232,   175,
     149,   291,    67,   179,   175,   175,   175,    78,    41,   175,
      52,    42,    41,   175,    75,    43,   132,   188,   137,    43,
     162,   163,    63,   317,   229,   180,   245,   -67,    69,   167,
     168,   320,   321,   322,   274,   239,   240,   138,   331,   139,
     153,   154,   181,   155,   183,   313,   156,   175,   273,   261,
     184,   185,   187,   186,   189,   340,   126,   192,   297,   227,
     244,   193,   246,   258,   230,   252,   267,   175,   -67,   254,
     255,   257,   259,   262,   353,    99,   266,   263,   268,   271,
     270,   128,   275,   290,   288,   342,   296,   289,   298,   299,
      82,    83,   301,    84,    85,   348,   303,   309,   310,   352,
     292,   294,   311,   312,   126,    86,    87,   316,   330,   300,
     126,   333,   335,   336,   318,   175,   341,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,    88,   337,   338,
     339,   343,   344,   346,   350,   307,    39,   305,   123,    64,
      89,   249,    73,   136,   224,   127,   134,   347,   -67,   251,
     133,   351,   345,    79,   238,    90,    91,   272,   294,   307,
     250,   235,    92,   237,   332,   231,   233,   349,    93,   308,
     234,    94,    95,     0,   236,    96,    97,   323,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,     0,
     241,     0,     0,     0,   307,   196,    83,     0,    84,    85,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      86,    87,   197,     0,   198,   199,   200,     0,     0,     0,
       0,     0,     0,   324,     0,   201,   202,   203,   204,   205,
      13,    14,    88,     0,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,    15,    89,     0,    16,    17,   206,
     207,   208,    18,   209,    19,    20,     0,     0,    21,     0,
      90,    62,     0,   210,     0,   286,     0,    92,     0,     0,
       0,     0,     0,    93,     0,     0,    94,    95,     0,     0,
      96,    97,    82,    83,     0,    84,    85,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    86,    87,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,    13,    14,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    89,     0,    16,    17,     0,     0,     0,    18,
       0,    19,    20,     0,     0,    21,     0,    90,     0,     0,
       0,     0,     0,     0,    92,     0,     0,     0,     0,     0,
      93,     0,     0,    94,    95,     0,     0,    96,    97,    82,
      83,     0,    84,    85,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    86,    87,     0,    82,    83,     0,
      84,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    87,    13,    14,    88,     0,     0,     0,
       0,    82,    83,     0,    84,    85,     0,     0,     0,    89,
       0,     0,    17,     0,    88,     0,    86,    87,     0,     0,
       0,     0,     0,     0,    90,     0,     0,    89,     0,     0,
       0,    92,     0,     0,     0,     0,     0,    93,    88,     0,
      94,    95,    90,    91,    96,    97,     0,     0,     0,    92,
       0,    89,     0,     0,     0,    93,     0,     0,    94,    95,
       0,     0,    96,    97,     0,     0,    90,     0,     0,   260,
       0,     0,     0,    92,    82,    83,     0,    84,    85,    93,
       0,     0,    94,    95,     0,     0,    96,    97,     0,    86,
      87,     0,    82,    83,     0,    84,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    86,    87,     0,
       0,    88,     0,     0,     0,     0,    82,    83,     0,    84,
      85,     0,     0,     0,    89,     0,     0,     0,     0,    88,
       0,    86,    87,     0,    82,    83,     0,    84,    85,    90,
       0,     0,    89,     0,     0,     0,    92,   306,     0,    86,
      87,     0,    93,    88,     0,    94,    95,    90,     0,    96,
      97,     0,     0,     0,    92,     0,    89,     0,     0,     0,
      93,    88,     0,    94,    95,     0,     0,    96,    97,     0,
       0,    90,     0,     0,    89,     0,     0,     0,   141,     0,
       0,     0,     0,     0,    93,     0,     0,    94,    95,    90,
       0,    96,    97,     0,     0,     0,   144,     0,     0,     0,
       0,     0,    93,     0,     0,    94,    95,     0,     0,    96,
      97,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       1,    13,    14,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,    15,     0,   121,    16,    17,
       0,     0,     0,    18,     0,    19,    20,     0,     0,    21,
       0,    12,     0,    13,    14,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,    15,     0,     0,
      16,    17,     0,     0,     0,    18,     0,    19,    20,     0,
       0,    21,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,    13,    14,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,    15,     0,   121,    16,
      17,     0,     0,     0,    18,     0,    19,    20,     0,     0,
      21,     0,    12,     0,    13,    14,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,    15,     0,
     248,    16,    17,     0,     0,     0,    18,     0,    19,    20,
       0,     0,    21,     0,    12,     0,    13,    14,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
      15,     0,     0,    16,    17,     0,     0,     0,    18,     0,
      19,    20,     0,     0,    21,     0,     0,     0,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-194))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    65,   111,    63,    91,   114,    41,     0,    27,   112,
      74,   199,   174,     3,   207,    69,    86,    87,    67,    89,
     182,    30,    71,    23,     3,    44,    52,   215,    92,    68,
      23,    91,     0,     3,     3,    28,    29,     3,    92,    25,
      26,    67,   112,    69,    67,    71,     3,    86,    87,    68,
      67,    31,    32,    76,    67,    27,    28,    69,    71,    76,
      18,    19,    69,    68,    67,    72,    92,    70,    72,    78,
     173,    68,    73,    66,    75,     3,     4,   141,   266,    69,
     144,   151,   275,   153,   154,   155,   156,   196,   152,   159,
     144,   253,    69,    51,   164,   165,   166,    76,    68,   169,
      69,    71,    68,   173,    67,    75,    70,   126,    70,    75,
      82,    83,    72,   301,   149,    73,   180,    75,   144,    84,
      85,   309,   310,   311,   227,   165,   166,    76,   316,    75,
      29,    79,    90,    80,     4,   297,    81,   207,   225,   203,
      74,    76,    67,    76,    70,   333,   139,    70,   257,    76,
       3,    75,     3,    71,    76,    76,     3,   227,    77,    75,
      75,    75,    71,    75,   352,   225,    77,    75,    70,    76,
      71,   190,    77,    76,    74,   337,    22,    75,    71,     4,
       3,     4,    77,     6,     7,   347,    71,    77,    76,   351,
     254,   255,    76,    75,   187,    18,    19,    76,    71,   263,
     193,    21,    76,    71,    67,   275,    71,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    40,   327,    76,
      76,    71,    71,    71,    76,   289,    23,   287,    66,    47,
      53,   187,    53,    75,   144,    67,    73,   346,    72,   193,
      71,   350,   342,    60,   164,    68,    69,    70,   312,   313,
     190,   155,    75,   159,   318,   151,   153,   348,    81,   289,
     154,    84,    85,    -1,   156,    88,    89,   312,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,    -1,
     169,    -1,    -1,    -1,   348,     3,     4,    -1,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,   313,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    52,    53,    -1,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    66,    -1,
      68,    69,    -1,    71,    -1,    72,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    84,    85,    -1,    -1,
      88,    89,     3,     4,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    55,    56,    -1,    -1,    -1,    60,
      -1,    62,    63,    -1,    -1,    66,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    84,    85,    -1,    -1,    88,    89,     3,
       4,    -1,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,     3,     4,    -1,
       6,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    19,    38,    39,    40,    -1,    -1,    -1,
      -1,     3,     4,    -1,     6,     7,    -1,    -1,    -1,    53,
      -1,    -1,    56,    -1,    40,    -1,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    53,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    81,    40,    -1,
      84,    85,    68,    69,    88,    89,    -1,    -1,    -1,    75,
      -1,    53,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,
      -1,    -1,    88,    89,    -1,    -1,    68,    -1,    -1,    71,
      -1,    -1,    -1,    75,     3,     4,    -1,     6,     7,    81,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    18,
      19,    -1,     3,     4,    -1,     6,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,    -1,
      -1,    40,    -1,    -1,    -1,    -1,     3,     4,    -1,     6,
       7,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    40,
      -1,    18,    19,    -1,     3,     4,    -1,     6,     7,    68,
      -1,    -1,    53,    -1,    -1,    -1,    75,    76,    -1,    18,
      19,    -1,    81,    40,    -1,    84,    85,    68,    -1,    88,
      89,    -1,    -1,    -1,    75,    -1,    53,    -1,    -1,    -1,
      81,    40,    -1,    84,    85,    -1,    -1,    88,    89,    -1,
      -1,    68,    -1,    -1,    53,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    68,
      -1,    88,    89,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    84,    85,    -1,    -1,    88,
      89,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       5,    38,    39,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    52,    -1,    54,    55,    56,
      -1,    -1,    -1,    60,    -1,    62,    63,    -1,    -1,    66,
      -1,    36,    -1,    38,    39,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    -1,    -1,    -1,    60,    -1,    62,    63,    -1,
      -1,    66,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    38,    39,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    52,    -1,    54,    55,
      56,    -1,    -1,    -1,    60,    -1,    62,    63,    -1,    -1,
      66,    -1,    36,    -1,    38,    39,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    52,    -1,
      54,    55,    56,    -1,    -1,    -1,    60,    -1,    62,    63,
      -1,    -1,    66,    -1,    36,    -1,    38,    39,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      52,    -1,    -1,    55,    56,    -1,    -1,    -1,    60,    -1,
      62,    63,    -1,    -1,    66,    -1,    -1,    -1,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    36,    38,    39,    52,    55,    56,    60,    62,
      63,    66,    92,    93,    94,    95,   105,   106,   107,   108,
     109,   110,   111,   115,   116,   117,     3,    69,     0,    94,
       3,    68,    71,    75,   101,   120,   121,   122,   123,   106,
     106,     3,    69,    69,     3,   112,   113,   101,    68,   122,
      67,    71,    69,    72,   103,    73,    75,    69,   102,   108,
     127,   128,   129,   112,    72,    67,   114,     3,    76,   121,
     122,   118,     3,     4,     6,     7,    18,    19,    40,    53,
      68,    69,    75,    81,    84,    85,    88,    89,   125,   139,
     141,   142,   143,   144,   145,   146,   147,   149,   150,   152,
     154,   156,   157,   158,   159,   160,   161,   137,   138,   139,
      17,    54,    76,    96,    97,    98,   106,   127,   122,   130,
     131,   102,    70,   129,   114,   138,   113,    70,    76,    75,
     119,    75,   156,   156,    75,   156,   125,   126,    99,   102,
     138,    30,    78,    29,    79,    80,    81,    25,    26,   148,
      27,    28,    82,    83,   151,    31,    32,    84,    85,   153,
      68,    86,    87,   155,   118,   156,   158,    18,    19,    51,
      73,    90,   118,     4,    74,    76,    76,    67,   122,    70,
      67,    71,    70,    75,    96,   124,     3,    20,    22,    23,
      24,    33,    34,    35,    36,    37,    57,    58,    59,    61,
      71,   103,   104,   105,   106,   132,   133,   134,   136,   138,
     164,   167,   169,   171,    99,    67,    70,    76,   100,   101,
      76,   143,   138,   144,   145,   146,   147,   149,   150,   152,
     152,   154,   158,   119,     3,   138,     3,   119,    54,    98,
     131,   124,    76,   118,    75,    75,   133,    75,    71,    71,
      71,   138,    75,    75,   135,   141,    77,     3,    70,   133,
      71,    76,    70,   125,   158,    77,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    72,   140,    74,    75,
      76,   119,   138,   165,   138,   168,    22,   118,    71,     4,
     138,    77,   133,    71,   141,   139,    76,   138,   163,    77,
      76,    76,    75,   119,    67,    76,    76,   133,    67,    76,
     133,   133,   133,   168,   105,   162,   163,   170,     3,     4,
      71,   133,   138,    21,   166,    76,    71,   118,    76,    76,
     133,    71,   119,    71,    71,   137,    71,   118,   119,   162,
      76,   118,   119,   133
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 145 "parser.yy"
    { TranslationUnit::instance().setDefinitionList((yyvsp[(1) - (1)].treeSequence)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 150 "parser.yy"
    {
                (yyval.treeSequence) = new TreeSequence();
                if ((yyvsp[(1) - (1)].tree))
                    (yyval.treeSequence)->addTree((yyvsp[(1) - (1)].tree)); 
            }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 156 "parser.yy"
    {
                (yyval.treeSequence) = (yyvsp[(1) - (2)].treeSequence);
                if ((yyvsp[(2) - (2)].tree))
                    (yyval.treeSequence)->addTree((yyvsp[(2) - (2)].tree));
            }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 164 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].functionDef); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 165 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].declarationSequence); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 166 "parser.yy"
    { (yyval.tree) = new Pragma((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 171 "parser.yy"
    {
                DeclarationSpecifierList *dsl = (yyvsp[(1) - (3)].declarationSpecifierList);
                Declarator *di = (yyvsp[(2) - (3)].declarator);

                if (dsl->hasEnumeratorList())
                {
                    errormsg("enum with enumerated names is not supported in a function's return type");
                    dsl->detachEnumeratorList();
                }

                // Example: In byte **f() {}, dsl represents "byte" and
                // di represents **f. Hence, di contains a pointer level of 2,
                // which is applied to the TypeDesc found in dsl, i.e., "byte".
                // di also contains the name of the function, "f".
                //
                (yyval.functionDef) = new FunctionDef(*dsl, *di);
                (yyval.functionDef)->setLineNo(di->getSourceFilename(), di->getLineNo());
                (yyval.functionDef)->setBody((yyvsp[(3) - (3)].compoundStmt));
                delete di;
                delete dsl;
            }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 195 "parser.yy"
    { (yyval.formalParamList) = (yyvsp[(1) - (1)].formalParamList); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 196 "parser.yy"
    { (yyval.formalParamList) = (yyvsp[(1) - (3)].formalParamList); (yyval.formalParamList)->endWithEllipsis(); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 197 "parser.yy"
    { (yyval.formalParamList) = new FormalParamList(); (yyval.formalParamList)->endWithEllipsis(); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 203 "parser.yy"
    { (yyval.formalParamList) = new FormalParamList(); if ((yyvsp[(1) - (1)].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[(1) - (1)].formalParameter)); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 205 "parser.yy"
    { (yyval.formalParamList) = (yyvsp[(1) - (3)].formalParamList); if ((yyvsp[(3) - (3)].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[(3) - (3)].formalParameter)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 210 "parser.yy"
    {
                    DeclarationSpecifierList *dsl = (yyvsp[(1) - (2)].declarationSpecifierList);
                    (yyval.formalParameter) = (yyvsp[(2) - (2)].declarator)->createFormalParameter(*dsl);
                    delete dsl;
                    delete (yyvsp[(2) - (2)].declarator);
                }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 219 "parser.yy"
    { (yyval.typeDesc) = (yyvsp[(1) - (1)].declarationSpecifierList)->getTypeDesc(); delete (yyvsp[(1) - (1)].declarationSpecifierList); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 221 "parser.yy"
    {
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getPointerTo((yyvsp[(1) - (2)].declarationSpecifierList)->getTypeDesc(), size_t((yyvsp[(2) - (2)].integer)));
                    delete (yyvsp[(1) - (2)].declarationSpecifierList);
                }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 228 "parser.yy"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 232 "parser.yy"
    { (yyval.integer) = 1; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 233 "parser.yy"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer) + 1; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 237 "parser.yy"
    { (yyval.declarationSpecifierList) = (yyvsp[(2) - (2)].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[(1) - (2)].typeSpecifier)); delete (yyvsp[(1) - (2)].typeSpecifier); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 238 "parser.yy"
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[(1) - (1)].typeSpecifier)); delete (yyvsp[(1) - (1)].typeSpecifier); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 243 "parser.yy"
    { (yyval.compoundStmt) = (yyvsp[(4) - (5)].compoundStmt); (yyval.compoundStmt)->setLineNo((yyvsp[(2) - (5)].str), (yyvsp[(3) - (5)].integer)); free((yyvsp[(2) - (5)].str)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 247 "parser.yy"
    { (yyval.compoundStmt) = new CompoundStmt(); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 248 "parser.yy"
    { (yyval.compoundStmt) = (yyvsp[(1) - (1)].compoundStmt); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 255 "parser.yy"
    {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[(1) - (2)].declarationSpecifierList), NULL);  // deletes $1
                        }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 259 "parser.yy"
    {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[(1) - (3)].declarationSpecifierList), (yyvsp[(2) - (3)].declaratorVector));  // deletes $1 and $2
                        }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 268 "parser.yy"
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[(1) - (1)].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[(1) - (1)].integer))); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 270 "parser.yy"
    { (yyval.declarationSpecifierList) = (yyvsp[(2) - (2)].declarationSpecifierList); if ((yyvsp[(1) - (2)].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[(1) - (2)].integer))); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 272 "parser.yy"
    { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[(1) - (1)].typeSpecifier)); delete (yyvsp[(1) - (1)].typeSpecifier); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 274 "parser.yy"
    { (yyval.declarationSpecifierList) = (yyvsp[(2) - (2)].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[(1) - (2)].typeSpecifier)); delete (yyvsp[(1) - (2)].typeSpecifier); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 278 "parser.yy"
    { (yyval.integer) = DeclarationSpecifierList::INTERRUPT_SPEC; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 279 "parser.yy"
    { (yyval.integer) = DeclarationSpecifierList::TYPEDEF_SPEC; }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 280 "parser.yy"
    { (yyval.integer) = DeclarationSpecifierList::ASSEMBLY_ONLY_SPEC; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 281 "parser.yy"
    { (yyval.integer) = -1; /* not supported, ignored */ }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 282 "parser.yy"
    { (yyval.integer) = -1; /* not supported, ignored */ }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 283 "parser.yy"
    { (yyval.integer) = DeclarationSpecifierList::STATIC_SPEC; }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 284 "parser.yy"
    { (yyval.integer) = DeclarationSpecifierList::EXTERN_SPEC; }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 288 "parser.yy"
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[(1) - (1)].typeDesc), "", NULL); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 289 "parser.yy"
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[(1) - (1)].typeDesc), "", NULL); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 290 "parser.yy"
    { const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[(2) - (2)].str), (yyvsp[(1) - (2)].integer) == UNION, true);
                                      (yyval.typeSpecifier) = new TypeSpecifier(td, "", NULL);
                                      free((yyvsp[(2) - (2)].str)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 293 "parser.yy"
    { (yyval.typeSpecifier) = (yyvsp[(1) - (1)].typeSpecifier); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 294 "parser.yy"
    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[(1) - (1)].typeDesc), "", NULL); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 299 "parser.yy"
    {
                        ClassDef *classDef = (yyvsp[(4) - (5)].classDef);
                        assert(classDef);
                        classDef->setName((yyvsp[(2) - (5)].str));
                        classDef->setUnion((yyvsp[(1) - (5)].integer) == UNION);
                        TranslationUnit::instance().getGlobalScope().declareClass(classDef);
                        const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[(2) - (5)].str), (yyvsp[(1) - (5)].integer) == UNION, true);
                        assert(td);
                        (yyval.typeDesc) = td;
                        free((yyvsp[(2) - (5)].str));
                    }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 311 "parser.yy"
    {
                        string anonStructName = "AnonStruct_" + (yyvsp[(3) - (4)].classDef)->getLineNo();
                        ClassDef *classDef = (yyvsp[(3) - (4)].classDef);
                        assert(classDef);
                        classDef->setName(anonStructName);
                        classDef->setUnion((yyvsp[(1) - (4)].integer) == UNION);
                        TranslationUnit::instance().getGlobalScope().declareClass(classDef);
                        const TypeDesc *td = TranslationUnit::getTypeManager().getClassType(anonStructName, (yyvsp[(1) - (4)].integer) == UNION, true);
                        assert(td);
                        (yyval.typeDesc) = td;
                    }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 326 "parser.yy"
    { (yyval.integer) = STRUCT; }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 327 "parser.yy"
    { (yyval.integer) = UNION;  }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 332 "parser.yy"
    {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].enumeratorList));
                            free((yyvsp[(2) - (6)].str));
                        }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 338 "parser.yy"
    {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, "", (yyvsp[(3) - (5)].enumeratorList));
                        }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 343 "parser.yy"
    {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[(2) - (2)].str), NULL);
                            free((yyvsp[(2) - (2)].str));
                        }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 351 "parser.yy"
    { (yyval.enumeratorList) = new vector<Enumerator *>(); (yyval.enumeratorList)->push_back((yyvsp[(1) - (1)].enumerator)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 352 "parser.yy"
    { (yyval.enumeratorList) = (yyvsp[(1) - (3)].enumeratorList); (yyval.enumeratorList)->push_back((yyvsp[(3) - (3)].enumerator)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 356 "parser.yy"
    { (yyval.enumerator) = new Enumerator((yyvsp[(1) - (1)].str), NULL, getSourceLineNo()); free((yyvsp[(1) - (1)].str)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 357 "parser.yy"
    { (yyval.enumerator) = new Enumerator((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].tree),   getSourceLineNo()); free((yyvsp[(1) - (3)].str)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 366 "parser.yy"
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 367 "parser.yy"
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, true); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 368 "parser.yy"
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 369 "parser.yy"
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(true);  }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 370 "parser.yy"
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(false); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 376 "parser.yy"
    { rejectTypeKeyword("long");   (yyval.typeDesc) = TranslationUnit::getTypeManager().getLongType(true);   }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 377 "parser.yy"
    { rejectTypeKeyword("float");  (yyval.typeDesc) = TranslationUnit::getTypeManager().getFloatType(false); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 378 "parser.yy"
    { rejectTypeKeyword("double"); (yyval.typeDesc) = TranslationUnit::getTypeManager().getFloatType(true);  }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 382 "parser.yy"
    { (yyval.typeDesc) = (yyvsp[(1) - (1)].typeDesc); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 383 "parser.yy"
    { (yyval.typeDesc) = TranslationUnit::getTypeManager().getVoidType(); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 387 "parser.yy"
    { (yyval.str) = strdup(sourceFilename.c_str()); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 391 "parser.yy"
    { (yyval.integer) = lineno; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 395 "parser.yy"
    { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[(1) - (1)].declarator)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 396 "parser.yy"
    { (yyval.declaratorVector) = (yyvsp[(1) - (3)].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[(3) - (3)].declarator)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 402 "parser.yy"
    { (yyval.declarator) = (yyvsp[(1) - (1)].declarator); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 403 "parser.yy"
    { (yyval.declarator) = (yyvsp[(1) - (3)].declarator); (yyval.declarator)->setInitExpr((yyvsp[(3) - (3)].tree)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 407 "parser.yy"
    {
                                            (yyval.declarator) = (yyvsp[(2) - (2)].declarator);
                                            for (int i = 0; i < (yyvsp[(1) - (2)].integer); ++i)
                                                (yyval.declarator)->incPointerLevel();
                                        }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 412 "parser.yy"
    { (yyval.declarator) = (yyvsp[(1) - (1)].declarator); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 417 "parser.yy"
    {
                (yyval.declarator) = new Declarator((yyvsp[(1) - (1)].str), sourceFilename, lineno);
                free((yyvsp[(1) - (1)].str));
            }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 422 "parser.yy"
    {
                (yyval.declarator) = new Declarator(string(), sourceFilename, lineno);
            }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 426 "parser.yy"
    {
                (yyval.declarator) = (yyvsp[(1) - (4)].declarator);
                (yyval.declarator)->addArraySizeExpr((yyvsp[(3) - (4)].tree));
            }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 431 "parser.yy"
    {
                (yyval.declarator) = (yyvsp[(1) - (4)].declarator);
                (yyval.declarator)->setFormalParamList((yyvsp[(3) - (4)].formalParamList));
            }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 436 "parser.yy"
    {
                (yyval.declarator) = (yyvsp[(1) - (3)].declarator);
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 442 "parser.yy"
    {
                (yyval.declarator) = (yyvsp[(1) - (4)].declarator);
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 447 "parser.yy"
    {
                (yyval.declarator) = new Declarator((yyvsp[(3) - (7)].str), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer();
                free((yyvsp[(3) - (7)].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[(6) - (7)].formalParamList));
                delete (yyvsp[(6) - (7)].formalParamList);
            }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 455 "parser.yy"
    {
                (yyval.declarator) = new Declarator(string(), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer();
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[(5) - (6)].formalParamList));
                delete (yyvsp[(5) - (6)].formalParamList);
            }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 464 "parser.yy"
    { (yyval.formalParamList) = new FormalParamList(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 465 "parser.yy"
    { (yyval.formalParamList) = (yyvsp[(1) - (1)].formalParamList);   }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 469 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 470 "parser.yy"
    { (yyval.tree) = (yyvsp[(2) - (3)].treeSequence); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 471 "parser.yy"
    { (yyval.tree) = (yyvsp[(2) - (4)].treeSequence); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 475 "parser.yy"
    { (yyval.treeSequence) = new TreeSequence((yyvsp[(1) - (1)].tree)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 476 "parser.yy"
    { (yyval.treeSequence) = (yyvsp[(1) - (3)].treeSequence); (yyval.treeSequence)->addTree((yyvsp[(3) - (3)].tree)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 480 "parser.yy"
    { (yyval.classDef) = new ClassDef(); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 481 "parser.yy"
    { (yyval.classDef) = (yyvsp[(1) - (1)].classDef); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 486 "parser.yy"
    {
                    (yyval.classDef) = new ClassDef();
                    for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[(1) - (1)].classMemberList)->begin(); it != (yyvsp[(1) - (1)].classMemberList)->end(); ++it)
                        (yyval.classDef)->addDataMember(*it);
                    delete (yyvsp[(1) - (1)].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 493 "parser.yy"
    {
                    (yyval.classDef) = (yyvsp[(1) - (2)].classDef);
                    for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[(2) - (2)].classMemberList)->begin(); it != (yyvsp[(2) - (2)].classMemberList)->end(); ++it)
                        (yyval.classDef)->addDataMember(*it);
                    delete (yyvsp[(2) - (2)].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 502 "parser.yy"
    { (yyval.classMemberList) = ClassDef::createClassMembers((yyvsp[(1) - (3)].declarationSpecifierList), (yyvsp[(2) - (3)].declaratorVector)); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 506 "parser.yy"
    { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[(1) - (1)].declarator)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 507 "parser.yy"
    { (yyval.declaratorVector) = (yyvsp[(1) - (3)].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[(3) - (3)].declarator)); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 511 "parser.yy"
    { (yyval.declarator) = (yyvsp[(1) - (1)].declarator); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 517 "parser.yy"
    { (yyval.compoundStmt) = new CompoundStmt(); if ((yyvsp[(1) - (1)].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[(1) - (1)].tree)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 518 "parser.yy"
    { (yyval.compoundStmt) = (yyvsp[(1) - (2)].compoundStmt); if ((yyvsp[(2) - (2)].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[(2) - (2)].tree)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 522 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 523 "parser.yy"
    { (yyval.tree) = ((yyvsp[(1) - (1)].declarationSequence) ? (yyvsp[(1) - (1)].declarationSequence) : new TreeSequence()); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 524 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].compoundStmt); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 525 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 526 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 527 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 528 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 529 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 530 "parser.yy"
    { (yyval.tree) = new JumpStmt((yyvsp[(2) - (3)].str)); free((yyvsp[(2) - (3)].str)); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 531 "parser.yy"
    { (yyval.tree) = new JumpStmt(JumpStmt::BRK, NULL); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 532 "parser.yy"
    { (yyval.tree) = new JumpStmt(JumpStmt::CONT, NULL); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 533 "parser.yy"
    { (yyval.tree) = new JumpStmt(JumpStmt::RET, NULL); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 534 "parser.yy"
    { (yyval.tree) = new JumpStmt(JumpStmt::RET, (yyvsp[(2) - (3)].tree)); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 536 "parser.yy"
    { (yyval.tree) = new AssemblerStmt((yyvsp[(3) - (7)].str), (yyvsp[(5) - (7)].str), true);
                          free((yyvsp[(3) - (7)].str)); free((yyvsp[(5) - (7)].str)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 539 "parser.yy"
    { (yyval.tree) = new AssemblerStmt((yyvsp[(3) - (7)].str), (yyvsp[(5) - (7)].str), false);
                          free((yyvsp[(3) - (7)].str)); free((yyvsp[(5) - (7)].str)); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 542 "parser.yy"
    { (yyval.tree) = new AssemblerStmt((yyvsp[(3) - (5)].str), "", false);
                          free((yyvsp[(3) - (5)].str)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 544 "parser.yy"
    { (yyval.tree) = new AssemblerStmt(yytext); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 549 "parser.yy"
    {
                                      (yyval.tree) = new LabeledStmt((yyvsp[(1) - (5)].str), TranslationUnit::instance().generateLabel('L'), (yyvsp[(5) - (5)].tree));
                                      (yyval.tree)->setLineNo((yyvsp[(2) - (5)].str), (yyvsp[(3) - (5)].integer));
                                      free((yyvsp[(1) - (5)].str)); free((yyvsp[(2) - (5)].str));
                                    }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 554 "parser.yy"
    { (yyval.tree) = new LabeledStmt((yyvsp[(2) - (4)].tree), (yyvsp[(4) - (4)].tree)); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 555 "parser.yy"
    { (yyval.tree) = new LabeledStmt((yyvsp[(3) - (3)].tree)); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 559 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 563 "parser.yy"
    { (yyval.tree) = new TreeSequence(); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 564 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (2)].tree); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 568 "parser.yy"
    { (yyval.tree) = NULL; }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 569 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 573 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 577 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 579 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr((yyvsp[(4) - (5)].binop), (yyvsp[(1) - (5)].tree), (yyvsp[(5) - (5)].tree)); free((yyvsp[(2) - (5)].str)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 583 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::ASSIGNMENT; }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 584 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::INC_ASSIGN; }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 585 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::DEC_ASSIGN; }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 586 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::MUL_ASSIGN; }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 587 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::DIV_ASSIGN; }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 588 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::MOD_ASSIGN; }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 589 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::XOR_ASSIGN; }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 590 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::AND_ASSIGN; }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 591 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::OR_ASSIGN; }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 592 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::LEFT_ASSIGN; }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 593 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::RIGHT_ASSIGN; }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 597 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 599 "parser.yy"
    { (yyval.tree) = new ConditionalExpr((yyvsp[(1) - (5)].tree), (yyvsp[(3) - (5)].tree), (yyvsp[(5) - (5)].tree)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 603 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 605 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_OR, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 609 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 611 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_AND, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 615 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 617 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_OR, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 620 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 622 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_XOR, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 625 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 627 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_AND, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 630 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 632 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr((yyvsp[(2) - (3)].binop), (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 636 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::EQUALITY; }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 637 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::INEQUALITY; }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 641 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 642 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr((yyvsp[(2) - (3)].binop), (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 646 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 647 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::LEFT_SHIFT, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 649 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::RIGHT_SHIFT, (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 654 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::INFERIOR; }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 655 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::INFERIOR_OR_EQUAL; }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 656 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::SUPERIOR; }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 657 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::SUPERIOR_OR_EQUAL; }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 661 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 662 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr((yyvsp[(2) - (3)].binop), (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 666 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::ADD; }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 667 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::SUB; }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 671 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 672 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr((yyvsp[(2) - (3)].binop), (yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].tree)); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 676 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::MUL; }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 677 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::DIV; }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 678 "parser.yy"
    { (yyval.binop) = BinaryOpExpr::MOD; }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 682 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 683 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr((yyvsp[(1) - (2)].unop), (yyvsp[(2) - (2)].tree)); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 684 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREINC, (yyvsp[(2) - (2)].tree)); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 685 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREDEC, (yyvsp[(2) - (2)].tree)); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 686 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr((yyvsp[(3) - (4)].typeDesc)); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 687 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::SIZE_OF, (yyvsp[(2) - (2)].tree)); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 691 "parser.yy"
    { (yyval.unop) = UnaryOpExpr::IDENTITY; }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 692 "parser.yy"
    { (yyval.unop) = UnaryOpExpr::NEG; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 693 "parser.yy"
    { (yyval.unop) = UnaryOpExpr::ADDRESS_OF; }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 694 "parser.yy"
    { (yyval.unop) = UnaryOpExpr::INDIRECTION; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 695 "parser.yy"
    { (yyval.unop) = UnaryOpExpr::BOOLEAN_NEG; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 696 "parser.yy"
    { (yyval.unop) = UnaryOpExpr::BITWISE_NOT; }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 700 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 701 "parser.yy"
    { (yyval.tree) = new CastExpr((yyvsp[(2) - (4)].typeDesc), (yyvsp[(4) - (4)].tree)); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 705 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 707 "parser.yy"
    { (yyval.tree) = new FunctionCallExpr((yyvsp[(1) - (5)].tree), new TreeSequence());
                          free((yyvsp[(2) - (5)].str)); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 710 "parser.yy"
    { (yyval.tree) = new FunctionCallExpr((yyvsp[(1) - (6)].tree), (yyvsp[(5) - (6)].treeSequence));
                          free((yyvsp[(2) - (6)].str)); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 713 "parser.yy"
    { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::ARRAY_REF, (yyvsp[(1) - (4)].tree), (yyvsp[(3) - (4)].tree)); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 715 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTINC, (yyvsp[(1) - (2)].tree)); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 717 "parser.yy"
    { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTDEC, (yyvsp[(1) - (2)].tree)); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 719 "parser.yy"
    { (yyval.tree) = new ObjectMemberExpr((yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].str), true); free((yyvsp[(3) - (3)].str)); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 721 "parser.yy"
    { (yyval.tree) = new ObjectMemberExpr((yyvsp[(1) - (3)].tree), (yyvsp[(3) - (3)].str), false); free((yyvsp[(3) - (3)].str)); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 725 "parser.yy"
    { (yyval.tree) = new IdentifierExpr((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 726 "parser.yy"
    { (yyval.tree) = new IdentifierExpr("this"); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 727 "parser.yy"
    { (yyval.tree) = new WordConstantExpr((yyvsp[(1) - (1)].real), true, (yyvsp[(1) - (1)].real) <= 0x7FFF); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 728 "parser.yy"
    { (yyval.tree) = new WordConstantExpr((int8_t) (yyvsp[(1) - (1)].character), false, true); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 729 "parser.yy"
    { (yyval.tree) = new StringLiteralExpr((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 730 "parser.yy"
    { (yyval.tree) = (yyvsp[(2) - (3)].tree); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 734 "parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 735 "parser.yy"
    {
                            (yyval.str) = (char *) malloc(strlen((yyvsp[(1) - (2)].str)) + strlen((yyvsp[(2) - (2)].str)) + 1);
                            strcpy((yyval.str), (yyvsp[(1) - (2)].str));
                            strcat((yyval.str), (yyvsp[(2) - (2)].str));
                            free((yyvsp[(1) - (2)].str)); free((yyvsp[(2) - (2)].str));
                        }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 744 "parser.yy"
    { (yyval.treeSequence) = NULL; }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 745 "parser.yy"
    { (yyval.treeSequence) = (yyvsp[(1) - (1)].treeSequence); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 749 "parser.yy"
    { (yyval.treeSequence) = new TreeSequence((yyvsp[(1) - (1)].tree)); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 750 "parser.yy"
    { (yyval.treeSequence) = (yyvsp[(1) - (3)].treeSequence); (yyval.treeSequence)->addTree((yyvsp[(3) - (3)].tree)); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 754 "parser.yy"
    { (yyval.tree) = new IfStmt((yyvsp[(3) - (6)].tree), (yyvsp[(5) - (6)].tree), (yyvsp[(6) - (6)].tree)); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 755 "parser.yy"
    { (yyval.tree) = new SwitchStmt((yyvsp[(3) - (5)].tree), (yyvsp[(5) - (5)].tree)); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 759 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 763 "parser.yy"
    { (yyval.tree) = NULL; }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 764 "parser.yy"
    { (yyval.tree) = (yyvsp[(2) - (2)].tree); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 768 "parser.yy"
    { (yyval.tree) = new WhileStmt((yyvsp[(3) - (5)].tree), (yyvsp[(5) - (5)].tree), false); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 772 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 776 "parser.yy"
    { (yyval.tree) = new WhileStmt((yyvsp[(5) - (7)].tree), (yyvsp[(2) - (7)].tree), true); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 780 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (2)].treeSequence); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 781 "parser.yy"
    { (yyval.tree) = (yyvsp[(1) - (1)].declarationSequence); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 789 "parser.yy"
    { if ( (yyvsp[(5) - (16)].tree))  (yyvsp[(5) - (16)].tree)->setLineNo((yyvsp[(3) - (16)].str), (yyvsp[(4) - (16)].integer));
                                  if ( (yyvsp[(8) - (16)].tree))  (yyvsp[(8) - (16)].tree)->setLineNo((yyvsp[(6) - (16)].str), (yyvsp[(7) - (16)].integer));
                                  if ((yyvsp[(12) - (16)].treeSequence)) (yyvsp[(12) - (16)].treeSequence)->setLineNo((yyvsp[(10) - (16)].str), (yyvsp[(11) - (16)].integer));
                                  (yyvsp[(16) - (16)].tree)->setLineNo((yyvsp[(14) - (16)].str), (yyvsp[(15) - (16)].integer));
                                  (yyval.tree) = new ForStmt((yyvsp[(5) - (16)].tree), (yyvsp[(8) - (16)].tree), (yyvsp[(12) - (16)].treeSequence), (yyvsp[(16) - (16)].tree));
                                  free((yyvsp[(3) - (16)].str)); free((yyvsp[(6) - (16)].str)); free((yyvsp[(10) - (16)].str)); free((yyvsp[(14) - (16)].str));
                                }
    break;



/* Line 1806 of yacc.c  */
#line 3700 "parser.cc"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 798 "parser.yy"


