/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.yy"

/*  $Id: parser.yy,v 1.94 2023/01/22 03:30:09 sarrazip Exp $

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
#include "FunctionPointerCast.h"

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


#line 143 "parser.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    AUTO = 322,
    FUNC_RECEIVES_FIRST_PARAM_IN_REG = 323
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
#define FUNC_RECEIVES_FIRST_PARAM_IN_REG 323

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 75 "parser.yy"

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
    FunctionPointerCast *funcPtrCast;
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

#line 363 "parser.cc"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1028

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  260
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  425

#define YYUNDEFTOK  2
#define YYMAXUTOK   323


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    90,     2,     2,     2,    89,    83,     2,
      70,    71,    73,    86,    72,    87,    92,    88,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    69,
      84,    76,    85,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    78,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    81,    75,    91,     2,     2,     2,
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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   153,   153,   154,   158,   164,   173,   174,   175,   176,
     180,   210,   230,   231,   236,   237,   245,   246,   251,   252,
     265,   266,   267,   273,   274,   281,   297,   307,   321,   340,
     344,   345,   349,   350,   354,   355,   356,   357,   361,   362,
     363,   364,   368,   373,   374,   380,   384,   393,   395,   397,
     399,   401,   403,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   420,   421,   422,   425,   426,   427,   431,   432,
     436,   437,   441,   454,   471,   472,   476,   482,   487,   496,
     497,   501,   502,   506,   507,   511,   512,   513,   514,   515,
     516,   517,   521,   533,   534,   538,   542,   546,   547,   551,
     552,   558,   559,   563,   567,   571,   577,   580,   586,   591,
     601,   608,   613,   620,   626,   636,   637,   642,   643,   647,
     651,   652,   656,   657,   658,   659,   660,   664,   665,   669,
     670,   674,   684,   697,   701,   702,   707,   708,   716,   725,
     726,   730,   731,   732,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   746,   749,   752,   756,   762,
     763,   767,   771,   772,   776,   777,   781,   782,   796,   797,
     801,   802,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   821,   825,   826,   831,   832,   837,   838,   843,
     844,   848,   849,   853,   854,   858,   859,   864,   865,   869,
     870,   874,   875,   877,   882,   883,   884,   885,   889,   890,
     894,   895,   899,   900,   904,   905,   906,   910,   911,   931,
     932,   933,   934,   938,   939,   940,   941,   942,   943,   947,
     948,   952,   953,   956,   959,   961,   963,   965,   967,   972,
     973,   991,   992,   993,   997,   998,  1007,  1008,  1012,  1013,
    1017,  1018,  1022,  1026,  1027,  1031,  1035,  1039,  1043,  1044,
    1048
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
  "GOTO", "EXTERN", "STATIC", "CONST", "VOLATILE", "AUTO",
  "FUNC_RECEIVES_FIRST_PARAM_IN_REG", "';'", "'('", "')'", "','", "'*'",
  "'{'", "'}'", "'='", "'['", "']'", "':'", "'?'", "'|'", "'^'", "'&'",
  "'<'", "'>'", "'+'", "'-'", "'/'", "'%'", "'!'", "'~'", "'.'", "$accept",
  "goal", "translation_unit", "external_declaration",
  "function_definition", "kr_parameter_name_list_opt",
  "kr_parameter_name_list", "kr_parameter_list_opt", "kr_parameter_list",
  "parameter_type_list", "parameter_list", "parameter_declaration_list",
  "parameter_declaration", "type_name", "abstract_declarator",
  "function_pointer_cast_opt", "function_pointer_cast", "pointer",
  "specifier_qualifier_list", "compound_stmt", "stmt_list_opt",
  "declaration", "declaration_specifiers", "storage_class_specifier",
  "type_specifier", "type_qualifier", "type_qualifier_list",
  "struct_or_union_specifier", "struct_or_union", "enum_specifier",
  "enumerator_list", "enumerator", "comma_opt", "non_void_basic_type",
  "basic_type", "save_src_fn", "save_line_no", "declarator_list",
  "init_declarator_list", "init_declarator", "declarator",
  "direct_declarator", "asterisk_sequence", "subscript_list", "subscript",
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
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,    59,
      40,    41,    44,    42,   123,   125,    61,    91,    93,    58,
      63,   124,    94,    38,    60,    62,    43,    45,    47,    37,
      33,   126,    46
};
# endif

#define YYPACT_NINF (-221)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-96)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     827,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,    17,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,    51,   827,
    -221,  -221,  -221,    73,   960,   960,   960,  -221,    18,  -221,
    -221,  -221,  -221,   -56,    29,  -221,  -221,  -221,  -221,    -4,
     -11,    37,   -13,  -221,    71,   -27,  -221,  -221,  -221,    27,
    -221,   450,    44,    29,    75,    85,  -221,  -221,    12,  -221,
    -221,   -11,  -221,  -221,    37,  -221,   552,  -221,   760,   601,
     450,    16,   450,   450,   104,   450,  -221,   169,    85,   601,
      29,   107,    13,   127,  -221,  -221,  -221,  -221,   123,  -221,
    -221,  -221,  -221,  -221,   650,   650,   675,   527,  -221,   206,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,    -7,   175,
     121,   124,   122,     2,    38,    77,    62,   -28,  -221,   601,
     144,   108,  -221,   203,  -221,   137,  -221,  -221,    84,   145,
     143,  -221,    37,   149,   151,  -221,   154,   601,   153,    -2,
    -221,  -221,  -221,  -221,  -221,   164,   165,   163,  -221,  -221,
    -221,  -221,  -221,   170,   601,    23,  -221,   894,   349,   601,
    -221,  -221,   527,  -221,   171,    32,    91,   166,  -221,  -221,
      40,   601,   601,   601,   601,   601,   601,  -221,  -221,   601,
    -221,  -221,  -221,  -221,   601,   601,   601,  -221,  -221,   601,
    -221,  -221,  -221,   601,  -221,  -221,  -221,  -221,   240,   601,
     241,  -221,  -221,  -221,   960,   242,  -221,   927,  -221,  -221,
     601,  -221,  -221,   601,  -221,    16,   960,  -221,   894,   168,
     177,  -221,  -221,   179,   172,   178,   182,   349,   183,   185,
     187,   215,   188,  -221,   189,   601,   186,   258,  -221,  -221,
     191,  -221,    73,   349,  -221,  -221,  -221,    56,  -221,  -221,
    -221,  -221,   196,   601,    -4,   198,  -221,  -221,  -221,  -221,
    -221,   478,  -221,   175,   -31,   121,   124,   122,     2,    38,
      77,    62,    62,   -28,  -221,   348,  -221,    26,  -221,   201,
    -221,   960,   204,    37,  -221,  -221,  -221,  -221,  -221,  -221,
     200,   211,  -221,   894,  -221,  -221,   601,   601,   253,  -221,
    -221,  -221,  -221,    63,   273,   601,   207,   349,   214,  -221,
    -221,  -221,  -221,  -221,    66,  -221,  -221,  -221,   601,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     601,  -221,   576,   218,  -221,   222,  -221,  -221,  -221,   219,
     216,   151,   233,   151,   236,   238,  -221,  -221,    97,    99,
     349,  -221,  -221,   239,  -221,  -221,  -221,   103,  -221,  -221,
      37,  -221,   349,   349,   349,   601,   438,   245,   173,   349,
    -221,   861,  -221,   601,  -221,  -221,   290,  -221,   244,  -221,
     151,   247,   246,  -221,  -221,   248,   250,  -221,  -221,   251,
    -221,   349,  -221,   254,  -221,   601,  -221,   256,   257,  -221,
    -221,  -221,   151,   601,  -221,  -221,   261,  -221,  -221,   601,
     260,  -221,  -221,   349,  -221
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       3,    95,     8,    67,    85,    86,    87,    90,    91,    92,
      88,    89,    94,    56,    57,    74,    75,    53,    55,     0,
      58,    61,    60,    68,    69,    59,    54,     9,     0,     2,
       4,     6,     7,   106,    47,    49,    51,    63,     0,    66,
      93,    62,    96,    78,     0,     1,     5,   105,    45,     0,
      34,   106,     0,    99,   101,   104,    48,    50,    52,    64,
      65,   129,     0,     0,    81,    84,    79,   115,     0,    36,
      70,    35,   103,    46,   106,    95,     0,    10,     0,   164,
     129,   106,    39,    41,     0,   130,   131,    12,    84,     0,
      83,     0,     0,     0,   116,    37,    71,   100,   101,    96,
     239,   244,   241,   240,     0,     0,     0,     0,   226,     0,
     225,   223,   224,   227,   228,   102,   122,   170,   183,   185,
     187,   189,   191,   193,   195,   199,   201,   208,   229,     0,
     212,   217,   231,   242,    14,    94,    22,   110,     0,     0,
      20,    23,   106,     0,   165,   166,     0,     0,   136,     0,
     134,    38,    40,    73,   132,     0,    13,     0,    82,   161,
     212,    80,    77,     0,   164,     0,   117,   120,    43,     0,
     219,   220,     0,   222,     0,    30,     0,     0,   125,   127,
       0,     0,     0,     0,     0,     0,     0,   197,   198,     0,
     205,   207,   204,   206,     0,     0,     0,   210,   211,     0,
     214,   215,   216,     0,   218,    96,   235,   236,     0,     0,
       0,    96,   245,   111,    16,     0,   108,     0,    26,   107,
       0,    72,   137,     0,   133,   106,    16,    76,   120,     0,
       0,   118,   121,     0,   239,     0,     0,     0,     0,     0,
       0,     0,    56,   157,     0,     0,     0,     0,   162,   143,
       0,   142,   106,    44,   139,   145,   141,     0,   144,   146,
     147,   148,     0,     0,     0,    30,    27,    31,    29,   243,
     126,     0,   123,   186,     0,   188,   190,   192,   194,   196,
     200,   202,   203,   209,   213,     0,   238,     0,   237,     0,
     109,    17,     0,   106,    15,    21,    24,   167,   138,   135,
       0,     0,   119,   120,   113,    96,     0,     0,     0,    95,
     150,   151,   152,     0,     0,     0,     0,     0,     0,    42,
     140,   163,   221,   230,     0,    28,   124,   128,     0,   173,
     174,   175,   176,   177,   181,   182,   178,   179,   180,   172,
       0,   234,     0,     0,    18,    25,    97,    11,   112,     0,
       0,   252,     0,   256,     0,     0,    96,   153,     0,     0,
       0,   160,   149,     0,   184,   171,   232,     0,   168,    19,
     106,   114,     0,     0,     0,     0,   246,     0,     0,     0,
     159,     0,   233,     0,    98,   158,   253,   255,     0,   259,
     248,     0,   247,    95,   156,     0,     0,   251,    33,     0,
     169,     0,   250,     0,   258,     0,    96,     0,     0,    32,
     254,   257,   249,   164,   154,   155,     0,    95,    96,   246,
       0,    95,    96,     0,   260
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -221,  -221,  -221,   288,  -221,  -221,   249,   101,  -221,   -71,
    -221,    41,   116,   162,  -221,    70,  -221,   -34,   -69,   -45,
    -221,     1,     0,  -221,   -36,    -8,  -221,  -221,  -221,  -221,
     275,   252,   259,  -221,  -221,   -73,   -94,  -221,  -221,   265,
     -29,  -221,    76,  -221,   180,  -216,   -98,  -221,   266,  -221,
     264,  -221,   125,  -221,  -220,  -221,   106,  -221,  -156,   -76,
    -221,   -70,  -221,   -79,  -221,   193,   192,   194,   195,   184,
    -221,   190,   160,  -221,   -12,  -221,   202,  -221,   -25,  -221,
     -65,  -221,  -221,  -221,   -43,  -221,  -221,  -221,  -221,  -221,
      25,  -221,  -221,  -221
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    30,    31,   155,   138,   290,   291,   232,
     140,   292,   141,   174,   265,   266,   267,    51,    81,   249,
     250,   251,   252,    34,    35,    36,    71,    37,    38,    39,
      65,    66,    91,    40,    41,    42,    62,   345,    52,    53,
      98,    55,    68,   165,   166,   233,   115,   180,    84,    85,
      86,   149,   150,   253,   254,   255,   158,   256,   143,   257,
     367,   145,   340,   117,   118,   119,   120,   121,   122,   123,
     189,   124,   125,   194,   126,   199,   127,   203,   128,   129,
     130,   131,   132,   133,   391,   392,   258,   352,   402,   259,
     354,   260,   393,   261
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    32,    99,   144,    54,   168,   116,   139,   229,    77,
     159,   179,   301,   151,   152,    92,    69,   308,    63,    47,
      43,    59,    72,   181,   160,    82,    60,   187,   188,    33,
      32,   176,    64,   320,    56,    57,    58,    95,   175,   116,
      47,   220,    70,    78,    82,   200,    82,    82,   328,    82,
      79,    45,   148,    83,    23,    24,    73,   205,   211,    74,
     201,   202,    50,    96,   204,   190,   191,   224,   222,    67,
     225,    82,    83,   182,    83,    83,    47,    83,   142,   170,
     171,   173,   160,    93,   163,    94,    49,   349,   144,    50,
     164,    44,    61,   176,   230,   147,   176,   361,   220,    83,
     164,    80,   264,   175,   341,    50,   274,    49,   195,   196,
      50,   285,   271,   218,    87,   272,   160,   289,   160,   160,
     160,   160,   192,   193,   160,   321,   206,   207,   220,   160,
     160,   160,   357,   287,   160,   220,    82,   363,   284,    94,
     380,   268,    48,    49,   298,    75,    50,    76,   197,   198,
     297,    89,   385,   386,   387,   214,   215,    90,   160,   397,
     208,   305,   269,   220,    83,   313,   159,   142,   377,   378,
     379,   220,   134,   327,   382,   383,   395,   396,   -95,   153,
     160,   410,   162,   281,   282,   209,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   148,   167,   323,    76,
     210,   116,   184,   424,   183,   186,   185,   212,   213,   100,
     101,   350,   102,   103,   293,   217,   216,   142,   100,   101,
     -95,   102,   103,   220,   104,   105,   293,   219,   142,   221,
     351,   353,   223,   104,   105,   226,   356,   215,   227,   359,
     228,   270,   263,   286,   288,   294,   302,   303,   306,   364,
     304,   -95,   307,   309,   310,   347,   311,   416,   314,   315,
     106,   318,   376,   160,   346,   317,   319,   322,   264,   106,
     365,   342,   368,   344,    75,   355,   107,   358,   177,   108,
     109,   178,   348,   362,   312,   107,   360,   369,   108,   110,
     371,   293,   111,   112,   370,   372,   113,   114,   110,   353,
     390,   111,   112,   142,   373,   113,   114,   374,   375,   381,
     399,   401,   413,   400,   394,   403,   404,    46,   405,   407,
     406,   408,   409,   411,   419,   414,   415,   300,   423,   412,
     417,   421,   343,   296,   262,   325,   156,   144,    88,    97,
     324,   384,   161,   390,   418,   231,   146,   157,   422,   154,
     299,   316,   234,   101,   280,   102,   103,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   104,   105,   235,
     278,   236,   237,   238,   273,   275,   420,   389,   276,   279,
     277,   142,   239,   240,   241,   242,    14,   243,    15,    16,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     388,   283,    17,   106,     0,    18,    19,   244,   245,   246,
      20,   247,    21,    22,    23,    24,    25,    26,   248,   107,
       0,     0,   108,    75,   339,     0,     0,     0,     0,     0,
       0,     0,   110,     0,     0,   111,   112,     0,     0,   113,
     114,   100,   101,     0,   102,   103,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,   104,   105,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       0,     0,     0,     0,    13,    14,     0,    15,    16,     0,
       0,   100,   101,     0,   102,   103,     0,     0,     0,    15,
      16,    17,   106,     0,    18,    19,   104,   105,     0,    20,
       0,    21,    22,    23,    24,    25,    26,    19,   107,     0,
       0,   108,     0,     0,     0,    23,    24,     0,     0,     0,
       0,   110,     0,     0,   111,   112,     0,     0,   113,   114,
     100,   101,   106,   102,   103,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,   104,   105,     0,   107,     0,
       0,   108,   109,   326,     0,   100,   101,     0,   102,   103,
       0,   110,     0,     0,   111,   112,    15,    16,   113,   114,
     104,   105,     0,     0,     0,     0,     0,     0,     0,   100,
     101,   106,   102,   103,    19,     0,     0,     0,     0,     0,
       0,     0,    23,    24,   104,   105,     0,   107,     0,     0,
     108,     0,     0,     0,   100,   101,   106,   102,   103,     0,
     110,     0,     0,   111,   112,     0,     0,   113,   114,   104,
     105,     0,   107,     0,     0,   108,   109,     0,     0,     0,
     106,     0,     0,     0,     0,   110,     0,     0,   111,   112,
       0,     0,   113,   114,     0,     0,   107,   366,     0,   108,
       0,     0,     0,   100,   101,   106,   102,   103,     0,   110,
       0,     0,   111,   112,     0,     0,   113,   114,   104,   105,
       0,   107,     0,     0,   108,     0,     0,     0,   100,   101,
       0,   102,   103,     0,   110,     0,     0,   111,   112,     0,
       0,   113,   114,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     169,     0,     0,   108,     0,     0,     0,     0,     0,   106,
       0,     0,     0,   110,     0,     0,   111,   112,     0,     0,
     113,   114,     0,     0,     0,   172,     0,     0,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
       0,   111,   112,   134,     0,   113,   114,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    14,     0,    15,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,   136,    18,    19,     0,     0,
       0,    20,     0,    21,    22,    23,    24,    25,    26,     0,
       1,   137,     2,     0,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,    14,     0,    15,    16,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     0,
      17,     0,     0,    18,    19,     0,     0,     0,    20,     0,
      21,    22,    23,    24,    25,    26,    27,    13,    14,     0,
      15,    16,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     0,     0,    17,     0,   136,    18,    19,     0,
       0,     0,    20,     0,    21,    22,    23,    24,    25,    26,
      13,    14,   398,    15,    16,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    17,     0,   136,
      18,    19,     0,     0,     0,    20,     0,    21,    22,    23,
      24,    25,    26,    13,    14,     0,    15,    16,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
      17,     0,   295,    18,    19,     0,     0,     0,    20,     0,
      21,    22,    23,    24,    25,    26,    13,    14,     0,    15,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,    18,    19,     0,     0,
       0,    20,     0,    21,    22,    23,    24,    25,    26
};

static const yytype_int16 yycheck[] =
{
       0,     0,    75,    79,    33,    99,    76,    78,   164,    54,
      89,   109,   228,    82,    83,     3,    50,   237,    74,     3,
       3,     3,    51,    30,    89,    61,     8,    25,    26,    29,
      29,   107,     3,   253,    34,    35,    36,    71,   107,   109,
       3,    72,    50,    70,    80,    73,    82,    83,    79,    85,
      77,     0,    81,    61,    65,    66,    69,   130,   131,    72,
      88,    89,    73,    71,   129,    27,    28,    69,   147,    73,
      72,   107,    80,    80,    82,    83,     3,    85,    78,   104,
     105,   106,   147,    71,    71,    73,    70,   303,   164,    73,
      77,    74,    74,   169,    71,    79,   172,   317,    72,   107,
      77,    74,    70,   172,    78,    73,   182,    70,    31,    32,
      73,   205,    72,   142,    70,    75,   181,   211,   183,   184,
     185,   186,    84,    85,   189,    69,    18,    19,    72,   194,
     195,   196,    69,   209,   199,    72,   172,    71,   203,    73,
     360,   175,    69,    70,   223,    74,    73,    76,    86,    87,
     220,    76,   372,   373,   374,    71,    72,    72,   223,   379,
      52,   234,    71,    72,   172,   241,   245,   167,    71,    72,
      71,    72,     3,   271,    71,    72,     3,     4,    70,    75,
     245,   401,    75,   195,   196,    77,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,   225,    70,   263,    76,
      92,   271,    81,   423,    29,    83,    82,     4,    71,     3,
       4,   305,     6,     7,   214,    72,    71,   217,     3,     4,
      76,     6,     7,    72,    18,    19,   226,    78,   228,    75,
     306,   307,    79,    18,    19,    71,   309,    72,    75,   315,
      70,    75,    71,     3,     3,     3,    78,    70,    70,   328,
      71,    79,    70,    70,    69,   300,    69,   413,    70,    70,
      54,     3,   356,   328,   293,    79,    75,    71,    70,    54,
     340,    70,   342,    69,    74,    22,    70,     4,    72,    73,
      74,    75,    71,    69,    69,    70,    79,    69,    73,    83,
      71,   291,    86,    87,    72,    79,    90,    91,    83,   375,
     376,    86,    87,   303,    71,    90,    91,    71,    70,    70,
     381,    21,   406,   383,    69,    71,    69,    29,    72,    71,
     393,    71,    71,    69,   418,    69,    69,   226,   422,   405,
      69,    71,   291,   217,   172,   265,    87,   413,    63,    74,
     264,   370,    90,   419,   417,   165,    80,    88,   421,    85,
     225,   245,     3,     4,   194,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     186,    22,    23,    24,   181,   183,   419,   376,   184,   189,
     185,   381,    33,    34,    35,    36,    37,    38,    39,    40,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
     375,   199,    53,    54,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    73,    74,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    86,    87,    -1,    -1,    90,
      91,     3,     4,    -1,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    39,    40,    -1,
      -1,     3,     4,    -1,     6,     7,    -1,    -1,    -1,    39,
      40,    53,    54,    -1,    56,    57,    18,    19,    -1,    61,
      -1,    63,    64,    65,    66,    67,    68,    57,    70,    -1,
      -1,    73,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    86,    87,    -1,    -1,    90,    91,
       3,     4,    54,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    70,    -1,
      -1,    73,    74,    75,    -1,     3,     4,    -1,     6,     7,
      -1,    83,    -1,    -1,    86,    87,    39,    40,    90,    91,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    54,     6,     7,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    18,    19,    -1,    70,    -1,    -1,
      73,    -1,    -1,    -1,     3,     4,    54,     6,     7,    -1,
      83,    -1,    -1,    86,    87,    -1,    -1,    90,    91,    18,
      19,    -1,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    83,    -1,    -1,    86,    87,
      -1,    -1,    90,    91,    -1,    -1,    70,    71,    -1,    73,
      -1,    -1,    -1,     3,     4,    54,     6,     7,    -1,    83,
      -1,    -1,    86,    87,    -1,    -1,    90,    91,    18,    19,
      -1,    70,    -1,    -1,    73,    -1,    -1,    -1,     3,     4,
      -1,     6,     7,    -1,    83,    -1,    -1,    86,    87,    -1,
      -1,    90,    91,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    83,    -1,    -1,    86,    87,    -1,    -1,
      90,    91,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    86,    87,     3,    -1,    90,    91,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    65,    66,    67,    68,    -1,
       3,    71,     5,    -1,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    39,    40,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      53,    -1,    -1,    56,    57,    -1,    -1,    -1,    61,    -1,
      63,    64,    65,    66,    67,    68,    69,    36,    37,    -1,
      39,    40,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    53,    -1,    55,    56,    57,    -1,
      -1,    -1,    61,    -1,    63,    64,    65,    66,    67,    68,
      36,    37,    71,    39,    40,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    53,    -1,    55,
      56,    57,    -1,    -1,    -1,    61,    -1,    63,    64,    65,
      66,    67,    68,    36,    37,    -1,    39,    40,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      53,    -1,    55,    56,    57,    -1,    -1,    -1,    61,    -1,
      63,    64,    65,    66,    67,    68,    36,    37,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    56,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    65,    66,    67,    68
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    36,    37,    39,    40,    53,    56,    57,
      61,    63,    64,    65,    66,    67,    68,    69,    94,    95,
      96,    97,   114,   115,   116,   117,   118,   120,   121,   122,
     126,   127,   128,     3,    74,     0,    96,     3,    69,    70,
      73,   110,   131,   132,   133,   134,   115,   115,   115,     3,
       8,    74,   129,    74,     3,   123,   124,    73,   135,   110,
     118,   119,   133,    69,    72,    74,    76,   112,    70,    77,
      74,   111,   117,   118,   141,   142,   143,    70,   123,    76,
      72,   125,     3,    71,    73,   110,   118,   132,   133,   128,
       3,     4,     6,     7,    18,    19,    54,    70,    73,    74,
      83,    86,    87,    90,    91,   139,   154,   156,   157,   158,
     159,   160,   161,   162,   164,   165,   167,   169,   171,   172,
     173,   174,   175,   176,     3,    17,    55,    71,    99,   102,
     103,   105,   115,   151,   152,   154,   141,    79,   133,   144,
     145,   111,   111,    75,   143,    98,    99,   125,   149,   156,
     173,   124,    75,    71,    77,   136,   137,    70,   129,    70,
     171,   171,    70,   171,   106,   111,   152,    72,    75,   139,
     140,    30,    80,    29,    81,    82,    83,    25,    26,   163,
      27,    28,    84,    85,   166,    31,    32,    86,    87,   168,
      73,    88,    89,   170,   173,   128,    18,    19,    52,    77,
      92,   128,     4,    71,    71,    72,    71,    72,   133,    78,
      72,    75,   156,    79,    69,    72,    71,    75,    70,   151,
      71,   137,   102,   138,     3,    20,    22,    23,    24,    33,
      34,    35,    36,    38,    58,    59,    60,    62,    69,   112,
     113,   114,   115,   146,   147,   148,   150,   152,   179,   182,
     184,   186,   106,    71,    70,   107,   108,   109,   110,    71,
      75,    72,    75,   158,   152,   159,   160,   161,   162,   164,
     165,   167,   167,   169,   173,   129,     3,   152,     3,   129,
     100,   101,   104,   115,     3,    55,   105,   154,   156,   145,
     100,   138,    78,    70,    71,   128,    70,    70,   147,    70,
      69,    69,    69,   152,    70,    70,   149,    79,     3,    75,
     147,    69,    71,   173,   135,   108,    75,   139,    79,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    76,
     155,    78,    70,   104,    69,   130,   133,   112,    71,   138,
     129,   152,   180,   152,   183,    22,   128,    69,     4,   152,
      79,   147,    69,    71,   156,   154,    71,   153,   154,    69,
      72,    71,    79,    71,    71,    70,   129,    71,    72,    71,
     147,    70,    71,    72,   133,   147,   147,   147,   183,   114,
     152,   177,   178,   185,    69,     3,     4,   147,    71,   102,
     154,    21,   181,    71,    69,    72,   128,    71,    71,    71,
     147,    69,   152,   129,    69,    69,   151,    69,   128,   129,
     177,    71,   128,   129,   147
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    94,    95,    95,    96,    96,    96,    96,
      97,    97,    98,    98,    99,    99,   100,   100,   101,   101,
     102,   102,   102,   103,   103,   104,   105,   106,   106,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   111,   111,
     111,   111,   112,   113,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   118,   118,
     119,   119,   120,   120,   121,   121,   122,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   127,   127,   128,   129,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   135,   135,   136,   136,   137,
     138,   138,   139,   139,   139,   139,   139,   140,   140,   141,
     141,   142,   142,   143,   144,   144,   145,   145,   145,   146,
     146,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   148,   148,
     148,   149,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   156,   156,   157,   157,   158,   158,   159,
     159,   160,   160,   161,   161,   162,   162,   163,   163,   164,
     164,   165,   165,   165,   166,   166,   166,   166,   167,   167,
     168,   168,   169,   169,   170,   170,   170,   171,   171,   171,
     171,   171,   171,   172,   172,   172,   172,   172,   172,   173,
     173,   174,   174,   174,   174,   174,   174,   174,   174,   175,
     175,   175,   175,   175,   176,   176,   177,   177,   178,   178,
     179,   179,   180,   181,   181,   182,   183,   184,   185,   185,
     186
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       3,     8,     0,     1,     1,     3,     0,     1,     2,     3,
       1,     3,     1,     1,     3,     2,     2,     2,     3,     1,
       0,     1,     6,     5,     1,     2,     2,     3,     2,     1,
       2,     1,     5,     0,     1,     2,     3,     1,     2,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     2,     5,     4,     1,     1,     6,     5,     2,     1,
       3,     1,     3,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     1,     3,     1,
       3,     1,     3,     2,     1,     1,     0,     4,     4,     5,
       3,     4,     7,     6,     8,     1,     2,     1,     2,     3,
       0,     1,     1,     3,     4,     2,     3,     1,     3,     0,
       1,     1,     2,     3,     1,     3,     1,     2,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     2,     3,     7,     7,     5,     1,     5,     4,
       3,     1,     1,     2,     0,     1,     1,     3,     1,     3,
       1,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     2,     2,
       2,     4,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     5,     6,     4,     2,     2,     3,     3,     1,
       1,     1,     1,     3,     1,     2,     0,     1,     1,     3,
       6,     5,     1,     0,     2,     5,     1,     7,     2,     1,
      16
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 153 "parser.yy"
                                { TranslationUnit::instance().setDefinitionList((yyvsp[0].treeSequence)); }
#line 2005 "parser.cc"
    break;

  case 3:
#line 154 "parser.yy"
                                { TranslationUnit::instance().setDefinitionList(NULL); }
#line 2011 "parser.cc"
    break;

  case 4:
#line 159 "parser.yy"
            {
                (yyval.treeSequence) = new TreeSequence();
                if ((yyvsp[0].tree))
                    (yyval.treeSequence)->addTree((yyvsp[0].tree)); 
            }
#line 2021 "parser.cc"
    break;

  case 5:
#line 165 "parser.yy"
            {
                (yyval.treeSequence) = (yyvsp[-1].treeSequence);
                if ((yyvsp[0].tree))
                    (yyval.treeSequence)->addTree((yyvsp[0].tree));
            }
#line 2031 "parser.cc"
    break;

  case 6:
#line 173 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].functionDef); }
#line 2037 "parser.cc"
    break;

  case 7:
#line 174 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].declarationSequence); }
#line 2043 "parser.cc"
    break;

  case 8:
#line 175 "parser.yy"
                                { (yyval.tree) = new Pragma((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2049 "parser.cc"
    break;

  case 9:
#line 176 "parser.yy"
                                { (yyval.tree) = NULL; }
#line 2055 "parser.cc"
    break;

  case 10:
#line 181 "parser.yy"
            {
                DeclarationSpecifierList *dsl = (yyvsp[-2].declarationSpecifierList);
                Declarator *di = (yyvsp[-1].declarator);

                if (dsl && dsl->hasEnumeratorList())
                {
                    errormsg("enum with enumerated names is not supported in a function's return type");
                    dsl->detachEnumeratorList();
                }
                if (dsl && dsl->isStaticDeclaration() && dsl->isExternDeclaration())
                {
                    errormsg("function definition must not be both static and extern");
                }

                // Example: In byte **f() {}, dsl represents "byte" and
                // di represents **f(). Hence, di contains a pointer level of 2,
                // which is applied to the TypeDesc found in dsl, i.e., "byte".
                // di also contains the name of the function, "f".
                //
                (yyval.functionDef) = new FunctionDef(dsl, *di);
                (yyval.functionDef)->setLineNo(di->getSourceFilename(), di->getLineNo());
                (yyval.functionDef)->setBody((yyvsp[0].compoundStmt));

                if (dsl && dsl->isTypeDefinition() && di->getId().empty())
                    errormsg("invalid typedef (type being defined may already be defined)");

                delete di;
                delete dsl;
            }
#line 2089 "parser.cc"
    break;

  case 11:
#line 211 "parser.yy"
            {
                Declarator di((yyvsp[-7].str), 0, (yyvsp[-6].str), (yyvsp[-5].integer));  // pass ID, save_src_fn, save_line_no
                di.processKAndRFunctionParameters(*(yyvsp[-3].strList), (yyvsp[-1].formalParamList));  // deletes $7, keeps no ref to $5

                (yyval.functionDef) = new FunctionDef(NULL, di);
                (yyval.functionDef)->setLineNo(di.getSourceFilename(), di.getLineNo());
                (yyval.functionDef)->setBody((yyvsp[0].compoundStmt));  // compound_stmt

                delete (yyvsp[-3].strList);  // delete kr_parameter_name_list_opt
                free((yyvsp[-6].str));  // save_src_fn
                free((yyvsp[-7].str));  // ID
            }
#line 2106 "parser.cc"
    break;

  case 12:
#line 230 "parser.yy"
                                        { (yyval.strList) = new std::vector<std::string>(); }
#line 2112 "parser.cc"
    break;

  case 13:
#line 231 "parser.yy"
                                        { (yyval.strList) = (yyvsp[0].strList); }
#line 2118 "parser.cc"
    break;

  case 14:
#line 236 "parser.yy"
                                        { (yyval.strList) = new std::vector<std::string>(); (yyval.strList)->push_back((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2124 "parser.cc"
    break;

  case 15:
#line 237 "parser.yy"
                                        { (yyval.strList) = (yyvsp[-2].strList); (yyval.strList)->push_back((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2130 "parser.cc"
    break;

  case 16:
#line 245 "parser.yy"
                                        { (yyval.formalParamList) = new FormalParamList(); }
#line 2136 "parser.cc"
    break;

  case 17:
#line 246 "parser.yy"
                                        { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2142 "parser.cc"
    break;

  case 18:
#line 251 "parser.yy"
                                        { (yyval.formalParamList) = (yyvsp[-1].formalParamList); }
#line 2148 "parser.cc"
    break;

  case 19:
#line 253 "parser.yy"
                            {
                                (yyval.formalParamList) = (yyvsp[-2].formalParamList); 
                                // Move trees from parameter_declaration_list (a FormalParamList) to $$.
                                for (auto it = (yyvsp[-1].formalParamList)->begin(); it != (yyvsp[-1].formalParamList)->end(); ++it)
                                    (yyval.formalParamList)->addTree(*it);
                                (yyvsp[-1].formalParamList)->clear();  // detach the trees from TreeSequence that is about to get destroyed
                                delete (yyvsp[-1].formalParamList);
                            }
#line 2161 "parser.cc"
    break;

  case 20:
#line 265 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2167 "parser.cc"
    break;

  case 21:
#line 266 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[-2].formalParamList); (yyval.formalParamList)->endWithEllipsis(); }
#line 2173 "parser.cc"
    break;

  case 22:
#line 267 "parser.yy"
                                     { (yyval.formalParamList) = new FormalParamList(); (yyval.formalParamList)->endWithEllipsis(); }
#line 2179 "parser.cc"
    break;

  case 23:
#line 273 "parser.yy"
                                     { (yyval.formalParamList) = new FormalParamList(); if ((yyvsp[0].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[0].formalParameter)); }
#line 2185 "parser.cc"
    break;

  case 24:
#line 275 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[-2].formalParamList); if ((yyvsp[0].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[0].formalParameter)); }
#line 2191 "parser.cc"
    break;

  case 25:
#line 282 "parser.yy"
                {
                    DeclarationSpecifierList *dsl = (yyvsp[-1].declarationSpecifierList);
                    (yyval.formalParamList) = new FormalParamList();
                    std::vector<Declarator *> *declaratorVector = (yyvsp[0].declaratorVector);
                    for (Declarator *declarator : *declaratorVector)
                    {
                        FormalParameter *fp = declarator->createFormalParameter(*dsl);
                        (yyval.formalParamList)->addTree(fp);
                    }
                    delete dsl;
                    delete declaratorVector;
                }
#line 2208 "parser.cc"
    break;

  case 26:
#line 298 "parser.yy"
                {
                    DeclarationSpecifierList *dsl = (yyvsp[-1].declarationSpecifierList);
                    (yyval.formalParameter) = (yyvsp[0].declarator)->createFormalParameter(*dsl);
                    delete dsl;
                    delete (yyvsp[0].declarator);
                }
#line 2219 "parser.cc"
    break;

  case 27:
#line 308 "parser.yy"
                {
                    if ((yyvsp[0].funcPtrCast))  // if func ptr cast, or ptr to ptr to func, etc.
                    {
                        (yyval.typeDesc) = TranslationUnit::getTypeManager().getFunctionPointerType(
                                (yyvsp[-1].declarationSpecifierList)->getTypeDesc(), *(yyvsp[0].funcPtrCast)->getFormalParamList(),
                                (yyvsp[-1].declarationSpecifierList)->isInterruptServiceFunction(), (yyvsp[-1].declarationSpecifierList)->isFunctionReceivingFirstParamInReg());
                        (yyval.typeDesc) = TranslationUnit::getTypeManager().getPointerTo((yyval.typeDesc), (yyvsp[0].funcPtrCast)->getPointerLevel() - 1);
                        delete (yyvsp[0].funcPtrCast);
                    }
                    else
                        (yyval.typeDesc) = (yyvsp[-1].declarationSpecifierList)->getTypeDesc();
                    delete (yyvsp[-1].declarationSpecifierList);
                }
#line 2237 "parser.cc"
    break;

  case 28:
#line 322 "parser.yy"
                {
                    const TypeDesc *td = TranslationUnit::getTypeManager().getPointerTo((yyvsp[-2].declarationSpecifierList)->getTypeDesc(), *(yyvsp[-1].typeQualifierBitFieldVector));
                    if ((yyvsp[0].funcPtrCast))
                    {
                        (yyval.typeDesc) = TranslationUnit::getTypeManager().getFunctionPointerType(
                                td, *(yyvsp[0].funcPtrCast)->getFormalParamList(),
                                (yyvsp[-2].declarationSpecifierList)->isInterruptServiceFunction(), (yyvsp[-2].declarationSpecifierList)->isFunctionReceivingFirstParamInReg());
                        (yyval.typeDesc) = TranslationUnit::getTypeManager().getPointerTo((yyval.typeDesc), (yyvsp[0].funcPtrCast)->getPointerLevel() - 1);
                        delete (yyvsp[0].funcPtrCast);
                    }
                    else
                        (yyval.typeDesc) = td;
                    delete (yyvsp[-1].typeQualifierBitFieldVector);  /* originally created by 'pointer' rule */
                    delete (yyvsp[-2].declarationSpecifierList);
                }
#line 2257 "parser.cc"
    break;

  case 29:
#line 340 "parser.yy"
                        { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); }
#line 2263 "parser.cc"
    break;

  case 30:
#line 344 "parser.yy"
                                                { (yyval.funcPtrCast) = NULL; }
#line 2269 "parser.cc"
    break;

  case 31:
#line 345 "parser.yy"
                                                { (yyval.funcPtrCast) = (yyvsp[0].funcPtrCast); }
#line 2275 "parser.cc"
    break;

  case 32:
#line 349 "parser.yy"
                                                              { (yyval.funcPtrCast) = new FunctionPointerCast((yyvsp[-4].integer), (yyvsp[-1].formalParamList)); }
#line 2281 "parser.cc"
    break;

  case 33:
#line 350 "parser.yy"
                                                              { (yyval.funcPtrCast) = new FunctionPointerCast((yyvsp[-3].integer), new FormalParamList()); }
#line 2287 "parser.cc"
    break;

  case 34:
#line 354 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = new TypeQualifierBitFieldVector(); (yyval.typeQualifierBitFieldVector)->push_back(0); }
#line 2293 "parser.cc"
    break;

  case 35:
#line 355 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = new TypeQualifierBitFieldVector(); (yyval.typeQualifierBitFieldVector)->push_back(TypeQualifierBitField((yyvsp[0].integer))); }
#line 2299 "parser.cc"
    break;

  case 36:
#line 356 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); (yyval.typeQualifierBitFieldVector)->push_back(0); }
#line 2305 "parser.cc"
    break;

  case 37:
#line 357 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); (yyval.typeQualifierBitFieldVector)->push_back((yyvsp[-1].integer)); }
#line 2311 "parser.cc"
    break;

  case 38:
#line 361 "parser.yy"
                                                { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[-1].typeSpecifier)); delete (yyvsp[-1].typeSpecifier); }
#line 2317 "parser.cc"
    break;

  case 39:
#line 362 "parser.yy"
                                                { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[0].typeSpecifier)); delete (yyvsp[0].typeSpecifier); }
#line 2323 "parser.cc"
    break;

  case 40:
#line 363 "parser.yy"
                                                { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2329 "parser.cc"
    break;

  case 41:
#line 364 "parser.yy"
                                                { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2335 "parser.cc"
    break;

  case 42:
#line 369 "parser.yy"
                        { (yyval.compoundStmt) = (yyvsp[-1].compoundStmt); (yyval.compoundStmt)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer)); free((yyvsp[-3].str)); }
#line 2341 "parser.cc"
    break;

  case 43:
#line 373 "parser.yy"
                        { (yyval.compoundStmt) = new CompoundStmt(); }
#line 2347 "parser.cc"
    break;

  case 44:
#line 374 "parser.yy"
                        { (yyval.compoundStmt) = (yyvsp[0].compoundStmt); }
#line 2353 "parser.cc"
    break;

  case 45:
#line 381 "parser.yy"
                        {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[-1].declarationSpecifierList), NULL);  // deletes $1
                        }
#line 2361 "parser.cc"
    break;

  case 46:
#line 385 "parser.yy"
                        {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[-2].declarationSpecifierList), (yyvsp[-1].declaratorVector));  // deletes $1 and $2
                        }
#line 2369 "parser.cc"
    break;

  case 47:
#line 394 "parser.yy"
            { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2375 "parser.cc"
    break;

  case 48:
#line 396 "parser.yy"
            { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2381 "parser.cc"
    break;

  case 49:
#line 398 "parser.yy"
            { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[0].typeSpecifier)); delete (yyvsp[0].typeSpecifier); }
#line 2387 "parser.cc"
    break;

  case 50:
#line 400 "parser.yy"
            { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[-1].typeSpecifier)); delete (yyvsp[-1].typeSpecifier); }
#line 2393 "parser.cc"
    break;

  case 51:
#line 402 "parser.yy"
            { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2399 "parser.cc"
    break;

  case 52:
#line 404 "parser.yy"
            { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2405 "parser.cc"
    break;

  case 53:
#line 408 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::INTERRUPT_SPEC; }
#line 2411 "parser.cc"
    break;

  case 54:
#line 409 "parser.yy"
                                       { (yyval.integer) = DeclarationSpecifierList::FUNC_RECEIVES_FIRST_PARAM_IN_REG_SPEC; }
#line 2417 "parser.cc"
    break;

  case 55:
#line 410 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::TYPEDEF_SPEC; }
#line 2423 "parser.cc"
    break;

  case 56:
#line 411 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::ASSEMBLY_ONLY_SPEC; }
#line 2429 "parser.cc"
    break;

  case 57:
#line 412 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::NO_RETURN_INSTRUCTION; }
#line 2435 "parser.cc"
    break;

  case 58:
#line 413 "parser.yy"
                    { (yyval.integer) = -1; /* not supported, ignored */ }
#line 2441 "parser.cc"
    break;

  case 59:
#line 414 "parser.yy"
                    { (yyval.integer) = -1; /* not supported, ignored */ }
#line 2447 "parser.cc"
    break;

  case 60:
#line 415 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::STATIC_SPEC; }
#line 2453 "parser.cc"
    break;

  case 61:
#line 416 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::EXTERN_SPEC; }
#line 2459 "parser.cc"
    break;

  case 62:
#line 420 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2465 "parser.cc"
    break;

  case 63:
#line 421 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2471 "parser.cc"
    break;

  case 64:
#line 422 "parser.yy"
                                    { const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[0].str), (yyvsp[-1].integer) == UNION, true);
                                      (yyval.typeSpecifier) = new TypeSpecifier(td, "", NULL);
                                      free((yyvsp[0].str)); }
#line 2479 "parser.cc"
    break;

  case 65:
#line 425 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2485 "parser.cc"
    break;

  case 66:
#line 426 "parser.yy"
                                    { (yyval.typeSpecifier) = (yyvsp[0].typeSpecifier); }
#line 2491 "parser.cc"
    break;

  case 67:
#line 427 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2497 "parser.cc"
    break;

  case 68:
#line 431 "parser.yy"
                                    { (yyval.integer) = DeclarationSpecifierList::CONST_QUALIFIER; }
#line 2503 "parser.cc"
    break;

  case 69:
#line 432 "parser.yy"
                                    { (yyval.integer) = DeclarationSpecifierList::VOLATILE_QUALIFIER; TranslationUnit::instance().warnAboutVolatile(); }
#line 2509 "parser.cc"
    break;

  case 70:
#line 436 "parser.yy"
                                            { (yyval.integer) = ((yyvsp[0].integer) == DeclarationSpecifierList::CONST_QUALIFIER ? CONST_BIT : VOLATILE_BIT); }
#line 2515 "parser.cc"
    break;

  case 71:
#line 437 "parser.yy"
                                            { (yyval.integer) = (yyvsp[-1].integer) | ((yyvsp[0].integer) == DeclarationSpecifierList::CONST_QUALIFIER ? CONST_BIT : VOLATILE_BIT); }
#line 2521 "parser.cc"
    break;

  case 72:
#line 442 "parser.yy"
                    {
                        ClassDef *classDef = (yyvsp[-1].classDef);
                        assert(classDef);
                        classDef->setName((yyvsp[-3].str));
                        classDef->setUnion((yyvsp[-4].integer) == UNION);
                        TranslationUnit::instance().getGlobalScope().declareClass(classDef);
                        const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[-3].str), (yyvsp[-4].integer) == UNION, true);
                        assert(td);
                        classDef->setTypeDesc(td);
                        (yyval.typeDesc) = td;
                        free((yyvsp[-3].str));
                    }
#line 2538 "parser.cc"
    break;

  case 73:
#line 455 "parser.yy"
                    {
                        string anonStructName = "AnonStruct_" + (yyvsp[-1].classDef)->getLineNo();
                        ClassDef *classDef = (yyvsp[-1].classDef);
                        assert(classDef);
                        classDef->setName(anonStructName);
                        classDef->setUnion((yyvsp[-3].integer) == UNION);
                        TranslationUnit::instance().getGlobalScope().declareClass(classDef);
                        const TypeDesc *td = TranslationUnit::getTypeManager().getClassType(anonStructName, (yyvsp[-3].integer) == UNION, true);
                        assert(td);
                        classDef->setTypeDesc(td);
                        (yyval.typeDesc) = td;
                    }
#line 2555 "parser.cc"
    break;

  case 74:
#line 471 "parser.yy"
                    { (yyval.integer) = STRUCT; }
#line 2561 "parser.cc"
    break;

  case 75:
#line 472 "parser.yy"
                    { (yyval.integer) = UNION;  }
#line 2567 "parser.cc"
    break;

  case 76:
#line 477 "parser.yy"
                        {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[-4].str), (yyvsp[-2].enumeratorList));
                            free((yyvsp[-4].str));
                        }
#line 2577 "parser.cc"
    break;

  case 77:
#line 483 "parser.yy"
                        {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, "", (yyvsp[-2].enumeratorList));
                        }
#line 2586 "parser.cc"
    break;

  case 78:
#line 488 "parser.yy"
                        {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[0].str), NULL);
                            free((yyvsp[0].str));
                        }
#line 2596 "parser.cc"
    break;

  case 79:
#line 496 "parser.yy"
                                            { (yyval.enumeratorList) = new vector<Enumerator *>(); (yyval.enumeratorList)->push_back((yyvsp[0].enumerator)); }
#line 2602 "parser.cc"
    break;

  case 80:
#line 497 "parser.yy"
                                            { (yyval.enumeratorList) = (yyvsp[-2].enumeratorList); (yyval.enumeratorList)->push_back((yyvsp[0].enumerator)); }
#line 2608 "parser.cc"
    break;

  case 81:
#line 501 "parser.yy"
                                            { (yyval.enumerator) = new Enumerator((yyvsp[0].str), NULL, getSourceLineNo()); free((yyvsp[0].str)); }
#line 2614 "parser.cc"
    break;

  case 82:
#line 502 "parser.yy"
                                            { (yyval.enumerator) = new Enumerator((yyvsp[-2].str), (yyvsp[0].tree),   getSourceLineNo()); free((yyvsp[-2].str)); }
#line 2620 "parser.cc"
    break;

  case 85:
#line 511 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
#line 2626 "parser.cc"
    break;

  case 86:
#line 512 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, true); }
#line 2632 "parser.cc"
    break;

  case 87:
#line 513 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
#line 2638 "parser.cc"
    break;

  case 88:
#line 514 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(true);  }
#line 2644 "parser.cc"
    break;

  case 89:
#line 515 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(false); }
#line 2650 "parser.cc"
    break;

  case 90:
#line 516 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getLongType(true); }
#line 2656 "parser.cc"
    break;

  case 91:
#line 517 "parser.yy"
                {
                    TranslationUnit::instance().warnIfFloatUnsupported();
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getRealType(false);
                }
#line 2665 "parser.cc"
    break;

  case 92:
#line 521 "parser.yy"
                {
                    TranslationUnit::instance().warnIfFloatUnsupported();
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getRealType(false);
                    if (!doubleTypeWarningIssued)
                    {
                        warnmsg("`double' is an alias for `float' for this compiler");
                        doubleTypeWarningIssued = true;
                    }
                }
#line 2679 "parser.cc"
    break;

  case 93:
#line 533 "parser.yy"
                            { (yyval.typeDesc) = (yyvsp[0].typeDesc); }
#line 2685 "parser.cc"
    break;

  case 94:
#line 534 "parser.yy"
                            { (yyval.typeDesc) = TranslationUnit::getTypeManager().getVoidType(); }
#line 2691 "parser.cc"
    break;

  case 95:
#line 538 "parser.yy"
                                { (yyval.str) = strdup(sourceFilename.c_str()); }
#line 2697 "parser.cc"
    break;

  case 96:
#line 542 "parser.yy"
                                { (yyval.integer) = lineno; }
#line 2703 "parser.cc"
    break;

  case 97:
#line 546 "parser.yy"
                                        { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2709 "parser.cc"
    break;

  case 98:
#line 547 "parser.yy"
                                        { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2715 "parser.cc"
    break;

  case 99:
#line 551 "parser.yy"
                                                { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2721 "parser.cc"
    break;

  case 100:
#line 552 "parser.yy"
                                                { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2727 "parser.cc"
    break;

  case 101:
#line 558 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2733 "parser.cc"
    break;

  case 102:
#line 559 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[-2].declarator); (yyval.declarator)->setInitExpr((yyvsp[0].tree)); }
#line 2739 "parser.cc"
    break;

  case 103:
#line 563 "parser.yy"
                                        {
                                            (yyval.declarator) = (yyvsp[0].declarator);
                                            (yyval.declarator)->setPointerLevel((yyvsp[-1].typeQualifierBitFieldVector));  // ownership of $1 transferred to the Declarator
                                        }
#line 2748 "parser.cc"
    break;

  case 104:
#line 567 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2754 "parser.cc"
    break;

  case 105:
#line 572 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[0].str), 0, sourceFilename, lineno);
                free((yyvsp[0].str));
            }
#line 2763 "parser.cc"
    break;

  case 106:
#line 577 "parser.yy"
            {
                (yyval.declarator) = new Declarator(string(), 0, sourceFilename, lineno);
            }
#line 2771 "parser.cc"
    break;

  case 107:
#line 581 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->checkForFunctionReturningArray();
                (yyval.declarator)->addArraySizeExpr((yyvsp[-1].tree));
            }
#line 2781 "parser.cc"
    break;

  case 108:
#line 587 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->setFormalParamList((yyvsp[-1].formalParamList));
            }
#line 2790 "parser.cc"
    break;

  case 109:
#line 592 "parser.yy"
            {
                assert((yyvsp[-2].strList) != NULL);
                assert((yyvsp[0].formalParamList) != NULL);

                (yyval.declarator) = (yyvsp[-4].declarator);
                (yyval.declarator)->processKAndRFunctionParameters(*(yyvsp[-2].strList), (yyvsp[0].formalParamList));  // deletes $5, keeps no ref to $3
                
                delete (yyvsp[-2].strList);  // kr_parameter_name_list [vector<string> *]
            }
#line 2804 "parser.cc"
    break;

  case 110:
#line 602 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-2].declarator);
                FormalParamList *fpl = new FormalParamList();
                fpl->endWithEllipsis(true);  // ellipsis is implied
                (yyval.declarator)->setFormalParamList(fpl);
            }
#line 2815 "parser.cc"
    break;

  case 111:
#line 609 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
#line 2824 "parser.cc"
    break;

  case 112:
#line 614 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[-4].str), (yyvsp[-5].integer), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                free((yyvsp[-4].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2835 "parser.cc"
    break;

  case 113:
#line 621 "parser.yy"
            {
                (yyval.declarator) = new Declarator(string(), (yyvsp[-4].integer), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2845 "parser.cc"
    break;

  case 114:
#line 627 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[-5].str), (yyvsp[-6].integer), sourceFilename, lineno);
                (yyval.declarator)->setAsArrayOfFunctionPointers((yyvsp[-1].formalParamList), (yyvsp[-4].treeSequence));  // takes ownership of FormalParamList ($7), deletes $4
                free((yyvsp[-5].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2856 "parser.cc"
    break;

  case 115:
#line 636 "parser.yy"
                                    { (yyval.integer) = 1; }
#line 2862 "parser.cc"
    break;

  case 116:
#line 637 "parser.yy"
                                    { ++(yyval.integer); }
#line 2868 "parser.cc"
    break;

  case 117:
#line 642 "parser.yy"
                                     { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2874 "parser.cc"
    break;

  case 118:
#line 643 "parser.yy"
                                     { (yyval.treeSequence) = (yyvsp[-1].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2880 "parser.cc"
    break;

  case 119:
#line 647 "parser.yy"
                                     { (yyval.tree) = (yyvsp[-1].tree); }
#line 2886 "parser.cc"
    break;

  case 120:
#line 651 "parser.yy"
                                     { (yyval.formalParamList) = new FormalParamList(); (yyval.formalParamList)->endWithEllipsis(true); /* implied ellipsis */ }
#line 2892 "parser.cc"
    break;

  case 121:
#line 652 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2898 "parser.cc"
    break;

  case 122:
#line 656 "parser.yy"
                                     { (yyval.tree) = (yyvsp[0].tree); }
#line 2904 "parser.cc"
    break;

  case 123:
#line 657 "parser.yy"
                                     { (yyval.tree) = (yyvsp[-1].treeSequence); }
#line 2910 "parser.cc"
    break;

  case 124:
#line 658 "parser.yy"
                                     { (yyval.tree) = (yyvsp[-2].treeSequence); }
#line 2916 "parser.cc"
    break;

  case 125:
#line 659 "parser.yy"
                    { (yyval.tree) = new TreeSequence(); }
#line 2922 "parser.cc"
    break;

  case 126:
#line 660 "parser.yy"
                    { (yyval.tree) = new TreeSequence(); }
#line 2928 "parser.cc"
    break;

  case 127:
#line 664 "parser.yy"
                                            { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2934 "parser.cc"
    break;

  case 128:
#line 665 "parser.yy"
                                            { (yyval.treeSequence) = (yyvsp[-2].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2940 "parser.cc"
    break;

  case 129:
#line 669 "parser.yy"
                                 { (yyval.classDef) = new ClassDef(); }
#line 2946 "parser.cc"
    break;

  case 130:
#line 670 "parser.yy"
                                 { (yyval.classDef) = (yyvsp[0].classDef); }
#line 2952 "parser.cc"
    break;

  case 131:
#line 675 "parser.yy"
                {
                    (yyval.classDef) = new ClassDef();
                    if ((yyvsp[0].classMemberList))
                        for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[0].classMemberList)->begin(); it != (yyvsp[0].classMemberList)->end(); ++it)
                            (yyval.classDef)->addDataMember(*it);
                    else
                        assert(0);
                    delete (yyvsp[0].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
#line 2966 "parser.cc"
    break;

  case 132:
#line 685 "parser.yy"
                {
                    (yyval.classDef) = (yyvsp[-1].classDef);
                    if ((yyvsp[0].classMemberList))
                        for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[0].classMemberList)->begin(); it != (yyvsp[0].classMemberList)->end(); ++it)
                            (yyval.classDef)->addDataMember(*it);
                    else
                        assert(0);
                    delete (yyvsp[0].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
#line 2980 "parser.cc"
    break;

  case 133:
#line 697 "parser.yy"
                                                             { (yyval.classMemberList) = ClassDef::createClassMembers((yyvsp[-2].declarationSpecifierList), (yyvsp[-1].declaratorVector)); }
#line 2986 "parser.cc"
    break;

  case 134:
#line 701 "parser.yy"
                                                    { (yyval.declaratorVector) = new std::vector<Declarator *>(); if ((yyvsp[0].declarator)) (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2992 "parser.cc"
    break;

  case 135:
#line 702 "parser.yy"
                                                    { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); if ((yyvsp[0].declarator)) (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2998 "parser.cc"
    break;

  case 136:
#line 707 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[0].declarator); }
#line 3004 "parser.cc"
    break;

  case 137:
#line 709 "parser.yy"
                {
                    (yyval.declarator) = NULL;
                    Declarator temp("<unnamed>", 0, sourceFilename, lineno);
                    temp.setBitFieldWidth(*(yyvsp[0].tree));
                    temp.checkBitField(NULL);
                    delete (yyvsp[0].tree);
                }
#line 3016 "parser.cc"
    break;

  case 138:
#line 717 "parser.yy"
                {
                    (yyval.declarator) = (yyvsp[-2].declarator);
                    (yyval.declarator)->setBitFieldWidth(*(yyvsp[0].tree));
                    delete (yyvsp[0].tree);
                }
#line 3026 "parser.cc"
    break;

  case 139:
#line 725 "parser.yy"
                        { (yyval.compoundStmt) = new CompoundStmt(); if ((yyvsp[0].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[0].tree)); }
#line 3032 "parser.cc"
    break;

  case 140:
#line 726 "parser.yy"
                        { (yyval.compoundStmt) = (yyvsp[-1].compoundStmt); if ((yyvsp[0].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[0].tree)); }
#line 3038 "parser.cc"
    break;

  case 141:
#line 730 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3044 "parser.cc"
    break;

  case 142:
#line 731 "parser.yy"
                        { (yyval.tree) = ((yyvsp[0].declarationSequence) ? (yyvsp[0].declarationSequence) : new TreeSequence()); }
#line 3050 "parser.cc"
    break;

  case 143:
#line 732 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].compoundStmt); }
#line 3056 "parser.cc"
    break;

  case 144:
#line 733 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3062 "parser.cc"
    break;

  case 145:
#line 734 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3068 "parser.cc"
    break;

  case 146:
#line 735 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3074 "parser.cc"
    break;

  case 147:
#line 736 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3080 "parser.cc"
    break;

  case 148:
#line 737 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3086 "parser.cc"
    break;

  case 149:
#line 738 "parser.yy"
                        { (yyval.tree) = new JumpStmt((yyvsp[-1].str)); free((yyvsp[-1].str)); }
#line 3092 "parser.cc"
    break;

  case 150:
#line 739 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::BRK, NULL); }
#line 3098 "parser.cc"
    break;

  case 151:
#line 740 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::CONT, NULL); }
#line 3104 "parser.cc"
    break;

  case 152:
#line 741 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::RET, NULL); }
#line 3110 "parser.cc"
    break;

  case 153:
#line 742 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::RET, (yyvsp[-1].tree)); }
#line 3116 "parser.cc"
    break;

  case 154:
#line 744 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt((yyvsp[-4].str), (yyvsp[-2].str), true);
                          free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 3123 "parser.cc"
    break;

  case 155:
#line 747 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt((yyvsp[-4].str), (yyvsp[-2].str), false);
                          free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 3130 "parser.cc"
    break;

  case 156:
#line 750 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt((yyvsp[-2].str), "", false);
                          free((yyvsp[-2].str)); }
#line 3137 "parser.cc"
    break;

  case 157:
#line 752 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt(yytext); }
#line 3143 "parser.cc"
    break;

  case 158:
#line 757 "parser.yy"
                                    {
                                      (yyval.tree) = new LabeledStmt((yyvsp[-4].str), TranslationUnit::instance().generateLabel('L'), (yyvsp[0].tree));
                                      (yyval.tree)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer));
                                      free((yyvsp[-4].str)); free((yyvsp[-3].str));
                                    }
#line 3153 "parser.cc"
    break;

  case 159:
#line 762 "parser.yy"
                                        { (yyval.tree) = new LabeledStmt((yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3159 "parser.cc"
    break;

  case 160:
#line 763 "parser.yy"
                                        { (yyval.tree) = new LabeledStmt((yyvsp[0].tree)); }
#line 3165 "parser.cc"
    break;

  case 161:
#line 767 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3171 "parser.cc"
    break;

  case 162:
#line 771 "parser.yy"
                                { (yyval.tree) = new TreeSequence(); }
#line 3177 "parser.cc"
    break;

  case 163:
#line 772 "parser.yy"
                                { (yyval.tree) = (yyvsp[-1].tree); }
#line 3183 "parser.cc"
    break;

  case 164:
#line 776 "parser.yy"
                                { (yyval.tree) = NULL; }
#line 3189 "parser.cc"
    break;

  case 165:
#line 777 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3195 "parser.cc"
    break;

  case 166:
#line 781 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3201 "parser.cc"
    break;

  case 167:
#line 782 "parser.yy"
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
#line 3217 "parser.cc"
    break;

  case 168:
#line 796 "parser.yy"
                                            { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3223 "parser.cc"
    break;

  case 169:
#line 797 "parser.yy"
                                            { (yyvsp[-2].treeSequence)->addTree((yyvsp[0].tree)); (yyval.treeSequence) = (yyvsp[-2].treeSequence); }
#line 3229 "parser.cc"
    break;

  case 170:
#line 801 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3235 "parser.cc"
    break;

  case 171:
#line 807 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-4].tree), (yyvsp[0].tree)); free((yyvsp[-3].str)); }
#line 3241 "parser.cc"
    break;

  case 172:
#line 811 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::ASSIGNMENT; }
#line 3247 "parser.cc"
    break;

  case 173:
#line 812 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::INC_ASSIGN; }
#line 3253 "parser.cc"
    break;

  case 174:
#line 813 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::DEC_ASSIGN; }
#line 3259 "parser.cc"
    break;

  case 175:
#line 814 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::MUL_ASSIGN; }
#line 3265 "parser.cc"
    break;

  case 176:
#line 815 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::DIV_ASSIGN; }
#line 3271 "parser.cc"
    break;

  case 177:
#line 816 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::MOD_ASSIGN; }
#line 3277 "parser.cc"
    break;

  case 178:
#line 817 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::XOR_ASSIGN; }
#line 3283 "parser.cc"
    break;

  case 179:
#line 818 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::AND_ASSIGN; }
#line 3289 "parser.cc"
    break;

  case 180:
#line 819 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::OR_ASSIGN; }
#line 3295 "parser.cc"
    break;

  case 181:
#line 820 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::LEFT_ASSIGN; }
#line 3301 "parser.cc"
    break;

  case 182:
#line 821 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::RIGHT_ASSIGN; }
#line 3307 "parser.cc"
    break;

  case 183:
#line 825 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3313 "parser.cc"
    break;

  case 184:
#line 827 "parser.yy"
                                                { (yyval.tree) = new ConditionalExpr((yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3319 "parser.cc"
    break;

  case 185:
#line 831 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3325 "parser.cc"
    break;

  case 186:
#line 833 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3331 "parser.cc"
    break;

  case 187:
#line 837 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3337 "parser.cc"
    break;

  case 188:
#line 839 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3343 "parser.cc"
    break;

  case 189:
#line 843 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3349 "parser.cc"
    break;

  case 190:
#line 845 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3355 "parser.cc"
    break;

  case 191:
#line 848 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3361 "parser.cc"
    break;

  case 192:
#line 850 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_XOR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3367 "parser.cc"
    break;

  case 193:
#line 853 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3373 "parser.cc"
    break;

  case 194:
#line 855 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3379 "parser.cc"
    break;

  case 195:
#line 858 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3385 "parser.cc"
    break;

  case 196:
#line 860 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3391 "parser.cc"
    break;

  case 197:
#line 864 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::EQUALITY; }
#line 3397 "parser.cc"
    break;

  case 198:
#line 865 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::INEQUALITY; }
#line 3403 "parser.cc"
    break;

  case 199:
#line 869 "parser.yy"
                                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3409 "parser.cc"
    break;

  case 200:
#line 870 "parser.yy"
                                        { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3415 "parser.cc"
    break;

  case 201:
#line 874 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3421 "parser.cc"
    break;

  case 202:
#line 875 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::LEFT_SHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3428 "parser.cc"
    break;

  case 203:
#line 877 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::RIGHT_SHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3435 "parser.cc"
    break;

  case 204:
#line 882 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::INFERIOR; }
#line 3441 "parser.cc"
    break;

  case 205:
#line 883 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::INFERIOR_OR_EQUAL; }
#line 3447 "parser.cc"
    break;

  case 206:
#line 884 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::SUPERIOR; }
#line 3453 "parser.cc"
    break;

  case 207:
#line 885 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::SUPERIOR_OR_EQUAL; }
#line 3459 "parser.cc"
    break;

  case 208:
#line 889 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3465 "parser.cc"
    break;

  case 209:
#line 890 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3471 "parser.cc"
    break;

  case 210:
#line 894 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::ADD; }
#line 3477 "parser.cc"
    break;

  case 211:
#line 895 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::SUB; }
#line 3483 "parser.cc"
    break;

  case 212:
#line 899 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3489 "parser.cc"
    break;

  case 213:
#line 900 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3495 "parser.cc"
    break;

  case 214:
#line 904 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::MUL; }
#line 3501 "parser.cc"
    break;

  case 215:
#line 905 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::DIV; }
#line 3507 "parser.cc"
    break;

  case 216:
#line 906 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::MOD; }
#line 3513 "parser.cc"
    break;

  case 217:
#line 910 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3519 "parser.cc"
    break;

  case 218:
#line 911 "parser.yy"
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
#line 3544 "parser.cc"
    break;

  case 219:
#line 931 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREINC, (yyvsp[0].tree)); }
#line 3550 "parser.cc"
    break;

  case 220:
#line 932 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREDEC, (yyvsp[0].tree)); }
#line 3556 "parser.cc"
    break;

  case 221:
#line 933 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr((yyvsp[-1].typeDesc)); }
#line 3562 "parser.cc"
    break;

  case 222:
#line 934 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::SIZE_OF, (yyvsp[0].tree)); }
#line 3568 "parser.cc"
    break;

  case 223:
#line 938 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::IDENTITY; }
#line 3574 "parser.cc"
    break;

  case 224:
#line 939 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::NEG; }
#line 3580 "parser.cc"
    break;

  case 225:
#line 940 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::ADDRESS_OF; }
#line 3586 "parser.cc"
    break;

  case 226:
#line 941 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::INDIRECTION; }
#line 3592 "parser.cc"
    break;

  case 227:
#line 942 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::BOOLEAN_NEG; }
#line 3598 "parser.cc"
    break;

  case 228:
#line 943 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::BITWISE_NOT; }
#line 3604 "parser.cc"
    break;

  case 229:
#line 947 "parser.yy"
                                    { (yyval.tree) = (yyvsp[0].tree); }
#line 3610 "parser.cc"
    break;

  case 230:
#line 948 "parser.yy"
                                    { (yyval.tree) = new CastExpr((yyvsp[-2].typeDesc), (yyvsp[0].tree)); }
#line 3616 "parser.cc"
    break;

  case 231:
#line 952 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3622 "parser.cc"
    break;

  case 232:
#line 954 "parser.yy"
                        { (yyval.tree) = new FunctionCallExpr((yyvsp[-4].tree), new TreeSequence());
                          free((yyvsp[-3].str)); }
#line 3629 "parser.cc"
    break;

  case 233:
#line 957 "parser.yy"
                        { (yyval.tree) = new FunctionCallExpr((yyvsp[-5].tree), (yyvsp[-1].treeSequence));
                          free((yyvsp[-4].str)); }
#line 3636 "parser.cc"
    break;

  case 234:
#line 960 "parser.yy"
                        { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::ARRAY_REF, (yyvsp[-3].tree), (yyvsp[-1].tree)); }
#line 3642 "parser.cc"
    break;

  case 235:
#line 962 "parser.yy"
                        { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTINC, (yyvsp[-1].tree)); }
#line 3648 "parser.cc"
    break;

  case 236:
#line 964 "parser.yy"
                        { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTDEC, (yyvsp[-1].tree)); }
#line 3654 "parser.cc"
    break;

  case 237:
#line 966 "parser.yy"
                        { (yyval.tree) = new ObjectMemberExpr((yyvsp[-2].tree), (yyvsp[0].str), true); free((yyvsp[0].str)); }
#line 3660 "parser.cc"
    break;

  case 238:
#line 968 "parser.yy"
                        { (yyval.tree) = new ObjectMemberExpr((yyvsp[-2].tree), (yyvsp[0].str), false); free((yyvsp[0].str)); }
#line 3666 "parser.cc"
    break;

  case 239:
#line 972 "parser.yy"
                        { (yyval.tree) = new IdentifierExpr((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 3672 "parser.cc"
    break;

  case 240:
#line 973 "parser.yy"
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
#line 3695 "parser.cc"
    break;

  case 241:
#line 991 "parser.yy"
                        { (yyval.tree) = new WordConstantExpr((int8_t) (yyvsp[0].character), false, true); }
#line 3701 "parser.cc"
    break;

  case 242:
#line 992 "parser.yy"
                        { (yyval.tree) = new StringLiteralExpr((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 3707 "parser.cc"
    break;

  case 243:
#line 993 "parser.yy"
                        { (yyval.tree) = (yyvsp[-1].tree); }
#line 3713 "parser.cc"
    break;

  case 244:
#line 997 "parser.yy"
                        { (yyval.str) = (yyvsp[0].str); }
#line 3719 "parser.cc"
    break;

  case 245:
#line 998 "parser.yy"
                        {
                            (yyval.str) = (char *) malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 1);
                            strcpy((yyval.str), (yyvsp[-1].str));
                            strcat((yyval.str), (yyvsp[0].str));
                            free((yyvsp[-1].str)); free((yyvsp[0].str));
                        }
#line 3730 "parser.cc"
    break;

  case 246:
#line 1007 "parser.yy"
                        { (yyval.treeSequence) = NULL; }
#line 3736 "parser.cc"
    break;

  case 247:
#line 1008 "parser.yy"
                        { (yyval.treeSequence) = (yyvsp[0].treeSequence); }
#line 3742 "parser.cc"
    break;

  case 248:
#line 1012 "parser.yy"
                                { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3748 "parser.cc"
    break;

  case 249:
#line 1013 "parser.yy"
                                { (yyval.treeSequence) = (yyvsp[-2].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3754 "parser.cc"
    break;

  case 250:
#line 1017 "parser.yy"
                                                { (yyval.tree) = new IfStmt((yyvsp[-3].tree), (yyvsp[-1].tree), (yyvsp[0].tree)); }
#line 3760 "parser.cc"
    break;

  case 251:
#line 1018 "parser.yy"
                                                { (yyval.tree) = new SwitchStmt((yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3766 "parser.cc"
    break;

  case 252:
#line 1022 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3772 "parser.cc"
    break;

  case 253:
#line 1026 "parser.yy"
                                { (yyval.tree) = NULL; }
#line 3778 "parser.cc"
    break;

  case 254:
#line 1027 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3784 "parser.cc"
    break;

  case 255:
#line 1031 "parser.yy"
                                        { (yyval.tree) = new WhileStmt((yyvsp[-2].tree), (yyvsp[0].tree), false); }
#line 3790 "parser.cc"
    break;

  case 256:
#line 1035 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3796 "parser.cc"
    break;

  case 257:
#line 1039 "parser.yy"
                                                { (yyval.tree) = new WhileStmt((yyvsp[-2].tree), (yyvsp[-5].tree), true); }
#line 3802 "parser.cc"
    break;

  case 258:
#line 1043 "parser.yy"
                                { (yyval.tree) = (yyvsp[-1].treeSequence); }
#line 3808 "parser.cc"
    break;

  case 259:
#line 1044 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].declarationSequence); }
#line 3814 "parser.cc"
    break;

  case 260:
#line 1052 "parser.yy"
                                { if ( (yyvsp[-11].tree))  (yyvsp[-11].tree)->setLineNo((yyvsp[-13].str), (yyvsp[-12].integer));
                                  if ( (yyvsp[-8].tree))  (yyvsp[-8].tree)->setLineNo((yyvsp[-10].str), (yyvsp[-9].integer));
                                  if ((yyvsp[-4].treeSequence)) (yyvsp[-4].treeSequence)->setLineNo((yyvsp[-6].str), (yyvsp[-5].integer));
                                  (yyval.tree) = new ForStmt((yyvsp[-11].tree), (yyvsp[-8].tree), (yyvsp[-4].treeSequence), (yyvsp[0].tree));
                                  free((yyvsp[-13].str)); free((yyvsp[-10].str)); free((yyvsp[-6].str)); free((yyvsp[-2].str));
                                }
#line 3825 "parser.cc"
    break;


#line 3829 "parser.cc"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 1060 "parser.yy"


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
