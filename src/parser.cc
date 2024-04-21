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

/*  CMOC - A C-like cross-compiler
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


#line 141 "parser.cc"

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
    AUTO = 321,
    FUNC_RECEIVES_FIRST_PARAM_IN_REG = 322
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
#define FUNC_RECEIVES_FIRST_PARAM_IN_REG 322

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 73 "parser.yy"

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

#line 359 "parser.cc"

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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  95
/* YYNRULES -- Number of rules.  */
#define YYNRULES  266
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  439

#define YYUNDEFTOK  2
#define YYMAXUTOK   322


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
       2,     2,     2,    89,     2,     2,     2,    88,    82,     2,
      69,    70,    72,    85,    71,    86,    91,    87,     2,     2,
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
static const yytype_int16 yyrline[] =
{
       0,   151,   151,   152,   156,   162,   171,   172,   173,   174,
     175,   176,   180,   210,   230,   231,   236,   237,   245,   246,
     251,   252,   265,   266,   267,   273,   274,   281,   298,   308,
     322,   341,   345,   346,   350,   351,   355,   356,   357,   358,
     362,   363,   364,   365,   369,   374,   375,   381,   385,   394,
     396,   398,   400,   402,   404,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   421,   422,   423,   426,   427,   428,
     432,   433,   437,   438,   442,   455,   472,   473,   477,   483,
     488,   497,   498,   499,   503,   504,   508,   509,   513,   514,
     515,   516,   517,   518,   519,   523,   535,   536,   540,   544,
     548,   549,   553,   554,   560,   561,   565,   569,   573,   579,
     582,   588,   593,   603,   610,   615,   622,   628,   635,   641,
     654,   680,   681,   686,   687,   691,   695,   696,   700,   701,
     702,   703,   704,   708,   709,   713,   714,   718,   728,   741,
     745,   746,   751,   752,   760,   769,   770,   774,   775,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   785,   786,
     787,   790,   793,   796,   800,   806,   811,   819,   823,   824,
     828,   829,   833,   834,   848,   849,   853,   854,   863,   864,
     865,   866,   867,   868,   869,   870,   871,   872,   873,   877,
     878,   883,   884,   889,   890,   895,   896,   900,   901,   905,
     906,   910,   911,   916,   917,   921,   922,   926,   927,   929,
     934,   935,   936,   937,   941,   942,   946,   947,   951,   952,
     956,   957,   958,   962,   963,   983,   984,   985,   986,   990,
     991,   992,   993,   994,   995,   999,  1000,  1004,  1005,  1008,
    1011,  1013,  1015,  1017,  1019,  1024,  1025,  1043,  1044,  1045,
    1049,  1050,  1059,  1060,  1064,  1065,  1069,  1070,  1074,  1078,
    1079,  1083,  1087,  1091,  1095,  1096,  1100
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
  "PLUS_EQUALS", "MINUS_EQUALS", "ASTERISK_EQUALS", "SLASH_EQUALS",
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
  "direct_declarator", "kandr_prototype_no_return", "asterisk_sequence",
  "subscript_list", "subscript", "parameter_type_list_opt", "initializer",
  "initializer_list", "struct_declaration_list_opt",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "stmt_list", "stmt",
  "labeled_stmt", "constant_expr", "expr_stmt", "expr_opt", "expr",
  "arg_expr_list", "assignment_expr", "assignment_op", "conditional_expr",
  "logical_or_expr", "logical_and_expr", "inclusive_or_expr",
  "exclusive_or_expr", "and_expr", "equality_expr", "equality_op",
  "rel_expr", "shift_expr", "rel_op", "add_expr", "add_op", "mul_expr",
  "mul_op", "unary_expr", "unary_op", "cast_expr", "postfix_expr",
  "primary_expr", "strlit_seq", "expr_list_opt", "expr_list",
  "selection_stmt", "if_cond", "else_part_opt", "while_stmt", "while_cond",
  "do_while_stmt", "for_init", "for_stmt", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,    59,    40,
      41,    44,    42,   123,   125,    61,    91,    93,    58,    63,
     124,    94,    38,    60,    62,    43,    45,    47,    37,    33,
     126,    46
};
# endif

#define YYPACT_NINF (-229)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-99)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     855,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,
      14,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,    55,
     855,  -229,  -229,  -229,    35,  1050,  1050,  1050,  -229,    20,
    -229,  -229,  -229,  -229,  -229,   -61,    93,  -229,  -229,  -229,
    -229,    12,    -8,    57,   -44,  -229,    46,   -28,  -229,  -229,
    -229,    33,  -229,   181,    40,    93,    61,    69,  -229,    83,
    -229,    16,  -229,  -229,    -8,  -229,  -229,    57,  -229,   561,
    -229,   789,   657,   181,    11,   181,   181,    86,   181,  -229,
     163,    69,   657,    93,   101,   137,    29,   138,  -229,  -229,
    -229,  -229,   133,  -229,  -229,  -229,  -229,  -229,   682,   682,
     705,   536,  -229,   210,  -229,  -229,  -229,  -229,  -229,  -229,
    -229,  -229,    -5,   182,   130,   131,   136,    53,    63,   100,
      64,   -25,  -229,   657,   361,    25,  -229,   219,  -229,   154,
    -229,  -229,   103,   155,   159,  -229,    57,   156,   161,  -229,
     160,   657,   157,   -26,  -229,  -229,  -229,  -229,  -229,   170,
     172,   167,  -229,  -229,  -229,  -229,  -229,   951,   175,   657,
      38,  -229,   984,   360,   657,  -229,  -229,   536,  -229,   178,
      -3,   109,   176,  -229,  -229,    56,   657,   657,   657,   657,
     657,   657,  -229,  -229,   657,  -229,  -229,  -229,  -229,   657,
     657,   657,  -229,  -229,   657,  -229,  -229,  -229,   657,  -229,
    -229,  -229,  -229,   246,   657,   248,  -229,  -229,  -229,  1050,
     249,  -229,  1017,  -229,  -229,   657,  -229,  -229,   657,  -229,
      11,  1050,  -229,   183,  -229,   185,   984,   179,   188,  -229,
     189,   180,   191,   193,   360,   195,   200,   202,   584,   196,
    -229,   203,  -229,  -229,   270,  -229,  -229,   201,  -229,    35,
     360,  -229,  -229,  -229,    73,  -229,  -229,  -229,  -229,   204,
     657,   205,   211,  -229,  -229,  -229,  -229,  -229,   488,  -229,
     182,    24,   130,   131,   136,    53,    63,   100,    64,    64,
     -25,  -229,   427,  -229,    -6,  -229,   216,  -229,  1050,   218,
      57,  -229,  -229,  -229,  -229,  -229,  -229,    45,  -229,  -229,
     220,  -229,   984,  -229,  -229,   657,   657,   266,  -229,  -229,
    -229,  -229,    80,   285,   657,  -229,  -229,   223,  -229,  -229,
    -229,  -229,  -229,    87,  -229,  -229,  -229,   657,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,   657,
    -229,   609,   225,  -229,   226,  -229,  -229,  -229,  -229,   224,
     227,   161,   231,   161,   232,   234,  -229,  -229,   112,   114,
     657,   228,  -229,   238,  -229,  -229,  -229,   117,  -229,  -229,
      57,  -229,   360,   360,   360,   657,   448,   242,   197,   360,
     233,   360,   888,  -229,   657,  -229,  -229,   292,  -229,   244,
    -229,   161,   247,   245,  -229,  -229,   252,   253,  -229,   360,
    -229,  -229,   254,  -229,   360,  -229,   251,  -229,   657,  -229,
     257,   258,  -229,  -229,  -229,  -229,   161,   657,  -229,  -229,
     259,  -229,  -229,   657,   260,  -229,  -229,   360,  -229
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       3,    98,     8,    69,    88,    89,    90,    93,    94,    95,
      91,    92,    97,    58,    59,    10,    76,    77,    55,    57,
       0,    60,    63,    62,    70,    71,    61,    56,     9,     0,
       2,     4,     6,     7,   109,    49,    51,    53,    65,     0,
      68,    96,    64,    11,    99,    80,    81,     1,     5,   108,
      47,     0,    36,   109,     0,   102,   104,   107,    50,    52,
      54,    66,    67,   135,     0,    81,    84,    87,    82,     0,
     121,     0,    38,    72,    37,   106,    48,   109,    98,     0,
      12,     0,   170,   135,   109,    41,    43,     0,   136,   137,
      14,    87,     0,    86,     0,     0,     0,     0,   122,    39,
      73,   103,   104,    99,   245,   250,   247,   246,     0,     0,
       0,     0,   232,     0,   231,   229,   230,   233,   234,   105,
     128,   176,   189,   191,   193,   195,   197,   199,   201,   205,
     207,   214,   235,     0,   218,   223,   237,   248,    16,    97,
      24,   113,     0,     0,    22,    25,   109,     0,   171,   172,
       0,     0,   142,     0,   140,    40,    42,    75,   138,     0,
      15,     0,    85,   167,   218,    83,    79,   126,     0,   170,
       0,   123,   126,    45,     0,   225,   226,     0,   228,     0,
      32,     0,     0,   131,   133,     0,     0,     0,     0,     0,
       0,     0,   203,   204,     0,   211,   213,   210,   212,     0,
       0,     0,   216,   217,     0,   220,   221,   222,     0,   224,
      99,   241,   242,     0,     0,     0,    99,   251,   114,    18,
       0,   111,     0,    28,   110,     0,    74,   143,     0,   139,
     109,    18,    78,    97,   127,     0,   126,     0,     0,   124,
       0,   245,     0,     0,     0,     0,     0,     0,     0,    58,
     163,     0,    98,    98,     0,   168,   149,     0,   148,   109,
      46,   145,   151,   147,     0,   150,   152,   153,   154,     0,
       0,     0,    32,    29,    33,    31,   249,   132,     0,   129,
     192,     0,   194,   196,   198,   200,   202,   206,   208,   209,
     215,   219,     0,   244,     0,   243,     0,   112,    19,     0,
     109,    17,    23,    26,   173,   144,   141,     0,   118,   119,
       0,   125,   126,   116,    99,     0,     0,     0,    98,   156,
     157,   158,     0,     0,     0,    99,    99,     0,    44,   146,
     169,   227,   236,     0,    30,   130,   134,     0,   179,   180,
     181,   182,   183,   187,   188,   184,   185,   186,   178,     0,
     240,     0,     0,    20,    27,   100,   120,    13,   115,     0,
       0,   258,     0,   262,     0,     0,    99,   159,     0,     0,
       0,     0,   155,     0,   190,   177,   238,     0,   174,    21,
     109,   117,     0,     0,     0,     0,   252,     0,     0,     0,
       0,     0,     0,   239,     0,   101,   164,   259,   261,     0,
     265,   254,     0,   253,    98,   162,     0,     0,   257,     0,
     166,    35,     0,   175,     0,   256,     0,   264,     0,    99,
       0,     0,   165,    34,   260,   263,   255,   170,   160,   161,
       0,    98,    99,   252,     0,    98,    99,     0,   266
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -229,  -229,  -229,   287,  -229,  -229,   239,   104,  -229,   -74,
    -229,    34,   116,   162,  -229,    59,  -229,   -41,   -65,   -46,
    -229,     1,     0,  -229,   -34,   -13,  -229,  -229,  -229,  -229,
     269,   243,   255,  -229,  -229,   -76,   -99,  -229,  -229,   263,
     -31,  -229,  -229,    71,  -229,   173,  -154,  -100,  -229,   261,
    -229,   264,  -229,   115,  -229,  -228,  -229,   -23,  -229,  -161,
     -77,  -229,   -73,  -229,   -83,  -229,   165,   166,   164,   158,
     169,  -229,   168,   186,  -229,     2,  -229,   153,  -229,    60,
    -229,   -66,  -229,  -229,  -229,   -75,  -229,  -229,  -229,  -229,
    -229,   -24,  -229,  -229,  -229
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,    31,    32,   159,   142,   297,   298,   234,
     144,   299,   145,   179,   272,   273,   274,    53,    84,   256,
     257,   258,   259,    35,    36,    37,    74,    38,    39,    40,
      67,    68,    94,    41,    42,    44,    64,   354,    54,    55,
     102,    57,    43,    71,   170,   171,   235,   119,   185,    87,
      88,    89,   153,   154,   260,   261,   262,   162,   263,   147,
     264,   377,   149,   349,   121,   122,   123,   124,   125,   126,
     127,   194,   128,   129,   199,   130,   204,   131,   208,   132,
     133,   134,   135,   136,   137,   402,   403,   265,   362,   415,
     266,   364,   267,   404,   268
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    33,   103,    56,   173,   148,   120,   143,   237,   163,
      80,    72,    65,   184,    49,    69,   317,    45,   240,    96,
     155,   156,    75,    61,    76,   186,   164,    77,    62,    85,
      34,    33,   329,    99,   181,    58,    59,    60,    49,    73,
     120,    81,   229,   211,   212,   230,   180,   205,    82,    85,
      86,    85,    85,   152,    85,    47,    24,    25,   210,   216,
      49,   100,   206,   207,    52,   225,   271,   209,   227,    52,
      86,   350,    86,    86,   187,    86,   213,    85,   192,   193,
      51,   146,   310,    52,    70,   164,    97,    46,    98,   151,
     195,   196,   148,    63,   -98,   225,    66,   181,    86,   168,
     181,   214,   337,    50,    51,   169,    83,    52,   238,    90,
     281,   292,   180,   356,   169,   223,   215,   296,    78,    78,
     164,    79,   164,   164,   164,   164,    51,   278,   164,    52,
     279,   200,   201,   164,   164,   164,    92,   294,   164,   275,
      93,   330,   291,    85,   225,   305,   197,   198,   367,   202,
     203,   225,   304,    95,   396,   397,   398,   373,   359,    98,
     157,   408,   164,   410,    86,   314,   138,   146,   175,   176,
     178,   322,   146,   219,   220,   166,   325,   326,   336,   276,
     225,   422,   387,   388,   389,   225,   424,   393,   394,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,   152,
     406,   407,   288,   289,   332,   120,   167,   172,    79,   438,
     189,   188,   190,   104,   105,   360,   106,   107,   191,   300,
      16,    17,   146,   217,   218,   221,   370,   371,   108,   109,
     222,   300,   225,   224,   226,   228,   146,    20,   361,   363,
     231,   232,   366,   220,   236,    24,    25,   369,   270,   293,
     277,   295,   301,   308,   374,   309,   311,   312,   -98,   313,
     315,   357,   316,   110,   318,   323,   430,   386,   319,   355,
     320,   164,   324,   327,   331,   328,   375,    70,   378,   111,
     271,   182,   112,   113,   183,   351,   353,   163,   365,   368,
     358,   372,   114,   379,   381,   115,   116,   380,   300,   117,
     118,   383,   384,   385,   164,   382,   391,   392,   363,   401,
     405,   409,   146,   414,   416,   417,   418,    48,   412,   425,
     427,   413,   420,   421,   423,   428,   429,   431,   419,   160,
     435,   334,   352,   433,    91,   307,   165,   437,   303,   269,
     101,   426,   333,   239,   150,   306,   161,   390,   284,   395,
     148,   280,   158,   283,   282,   432,   401,   290,   434,   436,
     285,   399,   286,   241,   105,     0,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,   108,   109,
     242,     0,   243,   244,   245,   287,     0,   400,     0,     0,
       0,     0,   146,   246,   247,   248,   249,    14,   250,    16,
      17,     0,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,    18,   110,     0,    19,    20,   251,   252,   253,
      21,   254,    22,    23,    24,    25,    26,    27,   255,   111,
       0,     0,   112,    78,     0,     0,   -98,     0,     0,     0,
       0,     0,   114,     0,     0,   115,   116,     0,     0,   117,
     118,   104,   105,     0,   106,   107,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,   108,   109,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,     0,     0,
       0,     0,     0,     0,    13,    14,     0,    16,    17,     0,
       0,   104,   105,     0,   106,   107,     0,     0,     0,     0,
      18,   110,   348,    19,    20,     0,   108,   109,    21,     0,
      22,    23,    24,    25,    26,    27,     0,   111,     0,     0,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,     0,     0,   115,   116,     0,     0,   117,   118,   104,
     105,   110,   106,   107,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   108,   109,     0,   111,     0,     0,
     112,   113,   335,     0,   104,   105,     0,   106,   107,     0,
     114,     0,     0,   115,   116,    16,    17,   117,   118,   108,
     109,     0,     0,     0,     0,     0,     0,   104,   105,   110,
     106,   107,    20,     0,     0,     0,     0,     0,     0,     0,
      24,    25,   108,   109,     0,   111,     0,     0,   112,     0,
       0,     0,   104,   105,   110,   106,   107,     0,   114,     0,
       0,   115,   116,     0,     0,   117,   118,   108,   109,     0,
     111,     0,     0,   112,   113,     0,     0,   110,     0,     0,
       0,     0,     0,   114,     0,     0,   115,   116,     0,     0,
     117,   118,   321,   111,     0,     0,   112,     0,     0,     0,
     104,   105,   110,   106,   107,     0,   114,     0,     0,   115,
     116,     0,     0,   117,   118,   108,   109,     0,   111,   376,
       0,   112,     0,     0,     0,   104,   105,     0,   106,   107,
       0,   114,     0,     0,   115,   116,     0,     0,   117,   118,
     108,   109,     0,     0,     0,     0,     0,     0,   104,   105,
     110,   106,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,     0,   111,     0,     0,   112,
       0,     0,     0,     0,     0,   110,     0,     0,     0,   114,
       0,     0,   115,   116,     0,     0,   117,   118,     0,     0,
       0,   174,     0,     0,   112,     0,     0,     0,   110,     0,
       0,     0,     0,     0,   114,     0,     0,   115,   116,     0,
       0,   117,   118,     0,   177,     0,     0,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114,     0,     0,
     115,   116,   138,     0,   117,   118,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   139,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    14,     0,    16,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,   140,    19,    20,     0,     0,     0,    21,
       0,    22,    23,    24,    25,    26,    27,     0,     1,   141,
       2,     0,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,    14,    15,    16,    17,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,     0,    18,     0,     0,
      19,    20,     0,     0,     0,    21,     0,    22,    23,    24,
      25,    26,    27,    28,    13,    14,     0,    16,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,   140,    19,    20,     0,     0,     0,    21,     0,
      22,    23,    24,    25,    26,    27,     0,     0,   411,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    14,     0,
      16,    17,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     0,    18,     0,   140,    19,    20,     0,     0,
       0,    21,     0,    22,    23,    24,    25,    26,    27,     0,
      13,    14,     0,    16,    17,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,    18,     0,   140,    19,
      20,     0,     0,     0,    21,     0,    22,    23,    24,    25,
      26,    27,     0,    13,    14,     0,    16,    17,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,    18,
       0,   302,    19,    20,     0,     0,     0,    21,     0,    22,
      23,    24,    25,    26,    27,     0,    13,    14,     0,    16,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,     0,    19,    20,     0,     0,     0,
      21,     0,    22,    23,    24,    25,    26,    27
};

static const yytype_int16 yycheck[] =
{
       0,     0,    78,    34,   103,    82,    79,    81,   169,    92,
      56,    52,    73,   113,     3,     3,   244,     3,   172,     3,
      85,    86,    53,     3,    68,    30,    92,    71,     8,    63,
      30,    30,   260,    74,   111,    35,    36,    37,     3,    52,
     113,    69,    68,    18,    19,    71,   111,    72,    76,    83,
      63,    85,    86,    84,    88,     0,    64,    65,   134,   135,
       3,    74,    87,    88,    72,    71,    69,   133,   151,    72,
      83,    77,    85,    86,    79,    88,    51,   111,    25,    26,
      69,    81,   236,    72,    72,   151,    70,    73,    72,    78,
      27,    28,   169,    73,    69,    71,     3,   174,   111,    70,
     177,    76,    78,    68,    69,    76,    73,    72,    70,    69,
     187,   210,   177,    68,    76,   146,    91,   216,    73,    73,
     186,    75,   188,   189,   190,   191,    69,    71,   194,    72,
      74,    31,    32,   199,   200,   201,    75,   214,   204,   180,
      71,    68,   208,   177,    71,   228,    83,    84,    68,    85,
      86,    71,   225,    70,   382,   383,   384,    70,   312,    72,
      74,   389,   228,   391,   177,   241,     3,   167,   108,   109,
     110,   248,   172,    70,    71,    74,   252,   253,   278,    70,
      71,   409,    70,    71,    70,    71,   414,    70,    71,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,   230,
       3,     4,   200,   201,   270,   278,    69,    69,    75,   437,
      80,    29,    81,     3,     4,   314,     6,     7,    82,   219,
      39,    40,   222,     4,    70,    70,   325,   326,    18,    19,
      71,   231,    71,    77,    74,    78,   236,    56,   315,   316,
      70,    74,   318,    71,    69,    64,    65,   324,    70,     3,
      74,     3,     3,    70,   337,    70,    77,    69,    78,    70,
      69,   307,    69,    53,    69,    69,   427,   366,    68,   300,
      68,   337,    69,     3,    70,    74,   349,    72,   351,    69,
      69,    71,    72,    73,    74,    69,    68,   370,    22,     4,
      70,    68,    82,    68,    70,    85,    86,    71,   298,    89,
      90,    70,    70,    69,   370,    78,    78,    69,   385,   386,
      68,    78,   312,    21,    70,    68,    71,    30,   392,    68,
     419,   394,    70,    70,    70,    68,    68,    68,   404,    90,
      70,   272,   298,   432,    65,   231,    93,   436,   222,   177,
      77,   418,   271,   170,    83,   230,    91,   370,   190,   380,
     427,   186,    88,   189,   188,   431,   433,   204,   433,   435,
     191,   385,   194,     3,     4,    -1,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,    24,   199,    -1,   386,    -1,    -1,
      -1,    -1,   392,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    52,    53,    -1,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    72,    73,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    -1,    89,
      90,     3,     4,    -1,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    39,    40,    -1,
      -1,     3,     4,    -1,     6,     7,    -1,    -1,    -1,    -1,
      52,    53,    75,    55,    56,    -1,    18,    19,    60,    -1,
      62,    63,    64,    65,    66,    67,    -1,    69,    -1,    -1,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    -1,    89,    90,     3,
       4,    53,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    69,    -1,    -1,
      72,    73,    74,    -1,     3,     4,    -1,     6,     7,    -1,
      82,    -1,    -1,    85,    86,    39,    40,    89,    90,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    53,
       6,     7,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    18,    19,    -1,    69,    -1,    -1,    72,    -1,
      -1,    -1,     3,     4,    53,     6,     7,    -1,    82,    -1,
      -1,    85,    86,    -1,    -1,    89,    90,    18,    19,    -1,
      69,    -1,    -1,    72,    73,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    -1,
      89,    90,    68,    69,    -1,    -1,    72,    -1,    -1,    -1,
       3,     4,    53,     6,     7,    -1,    82,    -1,    -1,    85,
      86,    -1,    -1,    89,    90,    18,    19,    -1,    69,    70,
      -1,    72,    -1,    -1,    -1,     3,     4,    -1,     6,     7,
      -1,    82,    -1,    -1,    85,    86,    -1,    -1,    89,    90,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      53,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19,    -1,    69,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    -1,    89,    90,    -1,    -1,
      -1,    69,    -1,    -1,    72,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      -1,    89,    90,    -1,    69,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,     3,    -1,    89,    90,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    54,    55,    56,    -1,    -1,    -1,    60,
      -1,    62,    63,    64,    65,    66,    67,    -1,     3,    70,
       5,    -1,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    52,    -1,    -1,
      55,    56,    -1,    -1,    -1,    60,    -1,    62,    63,    64,
      65,    66,    67,    68,    36,    37,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    54,    55,    56,    -1,    -1,    -1,    60,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    70,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      39,    40,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    52,    -1,    54,    55,    56,    -1,    -1,
      -1,    60,    -1,    62,    63,    64,    65,    66,    67,    -1,
      36,    37,    -1,    39,    40,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    52,    -1,    54,    55,
      56,    -1,    -1,    -1,    60,    -1,    62,    63,    64,    65,
      66,    67,    -1,    36,    37,    -1,    39,    40,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    52,
      -1,    54,    55,    56,    -1,    -1,    -1,    60,    -1,    62,
      63,    64,    65,    66,    67,    -1,    36,    37,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,
      60,    -1,    62,    63,    64,    65,    66,    67
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    36,    37,    38,    39,    40,    52,    55,
      56,    60,    62,    63,    64,    65,    66,    67,    68,    93,
      94,    95,    96,   113,   114,   115,   116,   117,   119,   120,
     121,   125,   126,   134,   127,     3,    73,     0,    95,     3,
      68,    69,    72,   109,   130,   131,   132,   133,   114,   114,
     114,     3,     8,    73,   128,    73,     3,   122,   123,     3,
      72,   135,   109,   117,   118,   132,    68,    71,    73,    75,
     111,    69,    76,    73,   110,   116,   117,   141,   142,   143,
      69,   122,    75,    71,   124,    70,     3,    70,    72,   109,
     117,   131,   132,   127,     3,     4,     6,     7,    18,    19,
      53,    69,    72,    73,    82,    85,    86,    89,    90,   139,
     154,   156,   157,   158,   159,   160,   161,   162,   164,   165,
     167,   169,   171,   172,   173,   174,   175,   176,     3,    17,
      54,    70,    98,   101,   102,   104,   114,   151,   152,   154,
     141,    78,   132,   144,   145,   110,   110,    74,   143,    97,
      98,   124,   149,   156,   173,   123,    74,    69,    70,    76,
     136,   137,    69,   128,    69,   171,   171,    69,   171,   105,
     110,   152,    71,    74,   139,   140,    30,    79,    29,    80,
      81,    82,    25,    26,   163,    27,    28,    83,    84,   166,
      31,    32,    85,    86,   168,    72,    87,    88,   170,   173,
     127,    18,    19,    51,    76,    91,   127,     4,    70,    70,
      71,    70,    71,   132,    77,    71,    74,   156,    78,    68,
      71,    70,    74,    17,   101,   138,    69,   151,    70,   137,
     138,     3,    20,    22,    23,    24,    33,    34,    35,    36,
      38,    57,    58,    59,    61,    68,   111,   112,   113,   114,
     146,   147,   148,   150,   152,   179,   182,   184,   186,   105,
      70,    69,   106,   107,   108,   109,    70,    74,    71,    74,
     158,   152,   159,   160,   161,   162,   164,   165,   167,   167,
     169,   173,   128,     3,   152,     3,   128,    99,   100,   103,
     114,     3,    54,   104,   154,   156,   145,    99,    70,    70,
     138,    77,    69,    70,   127,    69,    69,   147,    69,    68,
      68,    68,   152,    69,    69,   127,   127,     3,    74,   147,
      68,    70,   173,   135,   107,    74,   139,    78,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    75,   155,
      77,    69,   103,    68,   129,   132,    68,   111,    70,   138,
     128,   152,   180,   152,   183,    22,   127,    68,     4,   152,
     128,   128,    68,    70,   156,   154,    70,   153,   154,    68,
      71,    70,    78,    70,    70,    69,   128,    70,    71,    70,
     149,    78,    69,    70,    71,   132,   147,   147,   147,   183,
     113,   152,   177,   178,   185,    68,     3,     4,   147,    78,
     147,    70,   101,   154,    21,   181,    70,    68,    71,   127,
      70,    70,   147,    70,   147,    68,   152,   128,    68,    68,
     151,    68,   127,   128,   177,    70,   127,   128,   147
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    94,    94,    95,    95,    95,    95,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   101,   101,   101,   102,   102,   103,   104,   105,
     105,   106,   107,   107,   108,   108,   109,   109,   109,   109,
     110,   110,   110,   110,   111,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   114,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   119,   120,   120,   121,   121,
     121,   122,   122,   122,   123,   123,   124,   124,   125,   125,
     125,   125,   125,   125,   125,   125,   126,   126,   127,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     134,   135,   135,   136,   136,   137,   138,   138,   139,   139,
     139,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     144,   144,   145,   145,   145,   146,   146,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   148,   148,   148,   149,   150,   150,
     151,   151,   152,   152,   153,   153,   154,   154,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   156,
     156,   157,   157,   158,   158,   159,   159,   160,   160,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   165,
     166,   166,   166,   166,   167,   167,   168,   168,   169,   169,
     170,   170,   170,   171,   171,   171,   171,   171,   171,   172,
     172,   172,   172,   172,   172,   173,   173,   174,   174,   174,
     174,   174,   174,   174,   174,   175,   175,   175,   175,   175,
     176,   176,   177,   177,   178,   178,   179,   179,   180,   181,
     181,   182,   183,   184,   185,   185,   186
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     8,     0,     1,     1,     3,     0,     1,
       2,     3,     1,     3,     1,     1,     3,     2,     2,     2,
       3,     1,     0,     1,     6,     5,     1,     2,     2,     3,
       2,     1,     2,     1,     5,     0,     1,     2,     3,     1,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     2,     5,     4,     1,     1,     6,     5,
       2,     0,     1,     3,     1,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       1,     3,     1,     3,     1,     3,     2,     1,     1,     0,
       4,     4,     5,     3,     4,     7,     6,     8,     6,     6,
       8,     1,     2,     1,     2,     3,     0,     1,     1,     3,
       4,     2,     3,     1,     3,     0,     1,     1,     2,     3,
       1,     3,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     2,     3,
       7,     7,     5,     1,     5,     6,     5,     1,     1,     2,
       0,     1,     1,     3,     1,     3,     1,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     2,     2,     2,     4,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     5,     6,
       4,     2,     2,     3,     3,     1,     1,     1,     1,     3,
       1,     2,     0,     1,     1,     3,     6,     5,     1,     0,
       2,     5,     1,     7,     2,     1,    16
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
#line 151 "parser.yy"
                                { TranslationUnit::instance().setDefinitionList((yyvsp[0].treeSequence)); }
#line 2023 "parser.cc"
    break;

  case 3:
#line 152 "parser.yy"
                                { TranslationUnit::instance().setDefinitionList(NULL); }
#line 2029 "parser.cc"
    break;

  case 4:
#line 157 "parser.yy"
            {
                (yyval.treeSequence) = new TreeSequence();
                if ((yyvsp[0].tree))
                    (yyval.treeSequence)->addTree((yyvsp[0].tree)); 
            }
#line 2039 "parser.cc"
    break;

  case 5:
#line 163 "parser.yy"
            {
                (yyval.treeSequence) = (yyvsp[-1].treeSequence);
                if ((yyvsp[0].tree))
                    (yyval.treeSequence)->addTree((yyvsp[0].tree));
            }
#line 2049 "parser.cc"
    break;

  case 6:
#line 171 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].functionDef); }
#line 2055 "parser.cc"
    break;

  case 7:
#line 172 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].declarationSequence); }
#line 2061 "parser.cc"
    break;

  case 8:
#line 173 "parser.yy"
                                { (yyval.tree) = new Pragma((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2067 "parser.cc"
    break;

  case 9:
#line 174 "parser.yy"
                                { (yyval.tree) = NULL; }
#line 2073 "parser.cc"
    break;

  case 10:
#line 175 "parser.yy"
                                { (yyval.tree) = new AssemblerStmt(yytext); }
#line 2079 "parser.cc"
    break;

  case 11:
#line 176 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 2085 "parser.cc"
    break;

  case 12:
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
#line 2119 "parser.cc"
    break;

  case 13:
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
#line 2136 "parser.cc"
    break;

  case 14:
#line 230 "parser.yy"
                                        { (yyval.strList) = new std::vector<std::string>(); }
#line 2142 "parser.cc"
    break;

  case 15:
#line 231 "parser.yy"
                                        { (yyval.strList) = (yyvsp[0].strList); }
#line 2148 "parser.cc"
    break;

  case 16:
#line 236 "parser.yy"
                                        { (yyval.strList) = new std::vector<std::string>(); (yyval.strList)->push_back((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2154 "parser.cc"
    break;

  case 17:
#line 237 "parser.yy"
                                        { (yyval.strList) = (yyvsp[-2].strList); (yyval.strList)->push_back((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2160 "parser.cc"
    break;

  case 18:
#line 245 "parser.yy"
                                        { (yyval.formalParamList) = new FormalParamList(); }
#line 2166 "parser.cc"
    break;

  case 19:
#line 246 "parser.yy"
                                        { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2172 "parser.cc"
    break;

  case 20:
#line 251 "parser.yy"
                                        { (yyval.formalParamList) = (yyvsp[-1].formalParamList); }
#line 2178 "parser.cc"
    break;

  case 21:
#line 253 "parser.yy"
                            {
                                (yyval.formalParamList) = (yyvsp[-2].formalParamList); 
                                // Move trees from parameter_declaration_list (a FormalParamList) to $$.
                                for (auto it = (yyvsp[-1].formalParamList)->begin(); it != (yyvsp[-1].formalParamList)->end(); ++it)
                                    (yyval.formalParamList)->addTree(*it);
                                (yyvsp[-1].formalParamList)->clear();  // detach the trees from TreeSequence that is about to get destroyed
                                delete (yyvsp[-1].formalParamList);
                            }
#line 2191 "parser.cc"
    break;

  case 22:
#line 265 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2197 "parser.cc"
    break;

  case 23:
#line 266 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[-2].formalParamList); (yyval.formalParamList)->endWithEllipsis(); }
#line 2203 "parser.cc"
    break;

  case 24:
#line 267 "parser.yy"
                                     { (yyval.formalParamList) = new FormalParamList(); (yyval.formalParamList)->endWithEllipsis(); }
#line 2209 "parser.cc"
    break;

  case 25:
#line 273 "parser.yy"
                                     { (yyval.formalParamList) = new FormalParamList(); if ((yyvsp[0].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[0].formalParameter)); }
#line 2215 "parser.cc"
    break;

  case 26:
#line 275 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[-2].formalParamList); if ((yyvsp[0].formalParameter)) (yyval.formalParamList)->addTree((yyvsp[0].formalParameter)); }
#line 2221 "parser.cc"
    break;

  case 27:
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
                    deleteVectorElements(*declaratorVector);  // delete the Declarator objects
                    delete declaratorVector;
                }
#line 2239 "parser.cc"
    break;

  case 28:
#line 299 "parser.yy"
                {
                    DeclarationSpecifierList *dsl = (yyvsp[-1].declarationSpecifierList);
                    (yyval.formalParameter) = (yyvsp[0].declarator)->createFormalParameter(*dsl);
                    delete dsl;
                    delete (yyvsp[0].declarator);
                }
#line 2250 "parser.cc"
    break;

  case 29:
#line 309 "parser.yy"
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
#line 2268 "parser.cc"
    break;

  case 30:
#line 323 "parser.yy"
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
#line 2288 "parser.cc"
    break;

  case 31:
#line 341 "parser.yy"
                        { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); }
#line 2294 "parser.cc"
    break;

  case 32:
#line 345 "parser.yy"
                                                { (yyval.funcPtrCast) = NULL; }
#line 2300 "parser.cc"
    break;

  case 33:
#line 346 "parser.yy"
                                                { (yyval.funcPtrCast) = (yyvsp[0].funcPtrCast); }
#line 2306 "parser.cc"
    break;

  case 34:
#line 350 "parser.yy"
                                                              { (yyval.funcPtrCast) = new FunctionPointerCast((yyvsp[-4].integer), (yyvsp[-1].formalParamList)); }
#line 2312 "parser.cc"
    break;

  case 35:
#line 351 "parser.yy"
                                                              { (yyval.funcPtrCast) = new FunctionPointerCast((yyvsp[-3].integer), new FormalParamList()); }
#line 2318 "parser.cc"
    break;

  case 36:
#line 355 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = new TypeQualifierBitFieldVector(); (yyval.typeQualifierBitFieldVector)->push_back(0); }
#line 2324 "parser.cc"
    break;

  case 37:
#line 356 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = new TypeQualifierBitFieldVector(); (yyval.typeQualifierBitFieldVector)->push_back(TypeQualifierBitField((yyvsp[0].integer))); }
#line 2330 "parser.cc"
    break;

  case 38:
#line 357 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); (yyval.typeQualifierBitFieldVector)->push_back(0); }
#line 2336 "parser.cc"
    break;

  case 39:
#line 358 "parser.yy"
                                        { (yyval.typeQualifierBitFieldVector) = (yyvsp[0].typeQualifierBitFieldVector); (yyval.typeQualifierBitFieldVector)->push_back((yyvsp[-1].integer)); }
#line 2342 "parser.cc"
    break;

  case 40:
#line 362 "parser.yy"
                                                { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[-1].typeSpecifier)); delete (yyvsp[-1].typeSpecifier); }
#line 2348 "parser.cc"
    break;

  case 41:
#line 363 "parser.yy"
                                                { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[0].typeSpecifier)); delete (yyvsp[0].typeSpecifier); }
#line 2354 "parser.cc"
    break;

  case 42:
#line 364 "parser.yy"
                                                { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2360 "parser.cc"
    break;

  case 43:
#line 365 "parser.yy"
                                                { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2366 "parser.cc"
    break;

  case 44:
#line 370 "parser.yy"
                        { (yyval.compoundStmt) = (yyvsp[-1].compoundStmt); (yyval.compoundStmt)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer)); free((yyvsp[-3].str)); }
#line 2372 "parser.cc"
    break;

  case 45:
#line 374 "parser.yy"
                        { (yyval.compoundStmt) = new CompoundStmt(); }
#line 2378 "parser.cc"
    break;

  case 46:
#line 375 "parser.yy"
                        { (yyval.compoundStmt) = (yyvsp[0].compoundStmt); }
#line 2384 "parser.cc"
    break;

  case 47:
#line 382 "parser.yy"
                        {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[-1].declarationSpecifierList), NULL);  // deletes $1
                        }
#line 2392 "parser.cc"
    break;

  case 48:
#line 386 "parser.yy"
                        {
                            (yyval.declarationSequence) = TranslationUnit::instance().createDeclarationSequence((yyvsp[-2].declarationSpecifierList), (yyvsp[-1].declaratorVector));  // deletes $1 and $2
                        }
#line 2400 "parser.cc"
    break;

  case 49:
#line 395 "parser.yy"
            { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2406 "parser.cc"
    break;

  case 50:
#line 397 "parser.yy"
            { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2412 "parser.cc"
    break;

  case 51:
#line 399 "parser.yy"
            { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); (yyval.declarationSpecifierList)->add(*(yyvsp[0].typeSpecifier)); delete (yyvsp[0].typeSpecifier); }
#line 2418 "parser.cc"
    break;

  case 52:
#line 401 "parser.yy"
            { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); (yyval.declarationSpecifierList)->add(*(yyvsp[-1].typeSpecifier)); delete (yyvsp[-1].typeSpecifier); }
#line 2424 "parser.cc"
    break;

  case 53:
#line 403 "parser.yy"
            { (yyval.declarationSpecifierList) = new DeclarationSpecifierList(); if ((yyvsp[0].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[0].integer))); }
#line 2430 "parser.cc"
    break;

  case 54:
#line 405 "parser.yy"
            { (yyval.declarationSpecifierList) = (yyvsp[0].declarationSpecifierList); if ((yyvsp[-1].integer) != -1) (yyval.declarationSpecifierList)->add(DeclarationSpecifierList::Specifier((yyvsp[-1].integer))); }
#line 2436 "parser.cc"
    break;

  case 55:
#line 409 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::INTERRUPT_SPEC; }
#line 2442 "parser.cc"
    break;

  case 56:
#line 410 "parser.yy"
                                       { (yyval.integer) = DeclarationSpecifierList::FUNC_RECEIVES_FIRST_PARAM_IN_REG_SPEC; }
#line 2448 "parser.cc"
    break;

  case 57:
#line 411 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::TYPEDEF_SPEC; }
#line 2454 "parser.cc"
    break;

  case 58:
#line 412 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::ASSEMBLY_ONLY_SPEC; }
#line 2460 "parser.cc"
    break;

  case 59:
#line 413 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::NO_RETURN_INSTRUCTION; }
#line 2466 "parser.cc"
    break;

  case 60:
#line 414 "parser.yy"
                    { (yyval.integer) = -1; /* not supported, ignored */ }
#line 2472 "parser.cc"
    break;

  case 61:
#line 415 "parser.yy"
                    { (yyval.integer) = -1; /* not supported, ignored */ }
#line 2478 "parser.cc"
    break;

  case 62:
#line 416 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::STATIC_SPEC; }
#line 2484 "parser.cc"
    break;

  case 63:
#line 417 "parser.yy"
                    { (yyval.integer) = DeclarationSpecifierList::EXTERN_SPEC; }
#line 2490 "parser.cc"
    break;

  case 64:
#line 421 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2496 "parser.cc"
    break;

  case 65:
#line 422 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2502 "parser.cc"
    break;

  case 66:
#line 423 "parser.yy"
                                    { const TypeDesc *td = TranslationUnit::getTypeManager().getClassType((yyvsp[0].str), (yyvsp[-1].integer) == UNION, true);
                                      (yyval.typeSpecifier) = new TypeSpecifier(td, "", NULL);
                                      free((yyvsp[0].str)); }
#line 2510 "parser.cc"
    break;

  case 67:
#line 426 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2516 "parser.cc"
    break;

  case 68:
#line 427 "parser.yy"
                                    { (yyval.typeSpecifier) = (yyvsp[0].typeSpecifier); }
#line 2522 "parser.cc"
    break;

  case 69:
#line 428 "parser.yy"
                                    { (yyval.typeSpecifier) = new TypeSpecifier((yyvsp[0].typeDesc), "", NULL); }
#line 2528 "parser.cc"
    break;

  case 70:
#line 432 "parser.yy"
                                    { (yyval.integer) = DeclarationSpecifierList::CONST_QUALIFIER; }
#line 2534 "parser.cc"
    break;

  case 71:
#line 433 "parser.yy"
                                    { (yyval.integer) = DeclarationSpecifierList::VOLATILE_QUALIFIER; TranslationUnit::instance().enableVolatileWarning(); }
#line 2540 "parser.cc"
    break;

  case 72:
#line 437 "parser.yy"
                                            { (yyval.integer) = ((yyvsp[0].integer) == DeclarationSpecifierList::CONST_QUALIFIER ? CONST_BIT : VOLATILE_BIT); }
#line 2546 "parser.cc"
    break;

  case 73:
#line 438 "parser.yy"
                                            { (yyval.integer) = (yyvsp[-1].integer) | ((yyvsp[0].integer) == DeclarationSpecifierList::CONST_QUALIFIER ? CONST_BIT : VOLATILE_BIT); }
#line 2552 "parser.cc"
    break;

  case 74:
#line 443 "parser.yy"
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
#line 2569 "parser.cc"
    break;

  case 75:
#line 456 "parser.yy"
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
#line 2586 "parser.cc"
    break;

  case 76:
#line 472 "parser.yy"
                    { (yyval.integer) = STRUCT; }
#line 2592 "parser.cc"
    break;

  case 77:
#line 473 "parser.yy"
                    { (yyval.integer) = UNION;  }
#line 2598 "parser.cc"
    break;

  case 78:
#line 478 "parser.yy"
                        {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[-4].str), (yyvsp[-2].enumeratorList));
                            free((yyvsp[-4].str));
                        }
#line 2608 "parser.cc"
    break;

  case 79:
#line 484 "parser.yy"
                        {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, "", (yyvsp[-2].enumeratorList));
                        }
#line 2617 "parser.cc"
    break;

  case 80:
#line 489 "parser.yy"
                        {
                            const TypeDesc *td = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                            (yyval.typeSpecifier) = new TypeSpecifier(td, (yyvsp[0].str), NULL);
                            free((yyvsp[0].str));
                        }
#line 2627 "parser.cc"
    break;

  case 81:
#line 497 "parser.yy"
                                            { (yyval.enumeratorList) = new vector<Enumerator *>(); }
#line 2633 "parser.cc"
    break;

  case 82:
#line 498 "parser.yy"
                                            { (yyval.enumeratorList) = new vector<Enumerator *>(); (yyval.enumeratorList)->push_back((yyvsp[0].enumerator)); }
#line 2639 "parser.cc"
    break;

  case 83:
#line 499 "parser.yy"
                                            { (yyval.enumeratorList) = (yyvsp[-2].enumeratorList); (yyval.enumeratorList)->push_back((yyvsp[0].enumerator)); }
#line 2645 "parser.cc"
    break;

  case 84:
#line 503 "parser.yy"
                                            { (yyval.enumerator) = new Enumerator((yyvsp[0].str), NULL, getSourceLineNo()); free((yyvsp[0].str)); }
#line 2651 "parser.cc"
    break;

  case 85:
#line 504 "parser.yy"
                                            { (yyval.enumerator) = new Enumerator((yyvsp[-2].str), (yyvsp[0].tree),   getSourceLineNo()); free((yyvsp[-2].str)); }
#line 2657 "parser.cc"
    break;

  case 88:
#line 513 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
#line 2663 "parser.cc"
    break;

  case 89:
#line 514 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(BYTE_TYPE, true); }
#line 2669 "parser.cc"
    break;

  case 90:
#line 515 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true); }
#line 2675 "parser.cc"
    break;

  case 91:
#line 516 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(true);  }
#line 2681 "parser.cc"
    break;

  case 92:
#line 517 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getSizelessType(false); }
#line 2687 "parser.cc"
    break;

  case 93:
#line 518 "parser.yy"
                { (yyval.typeDesc) = TranslationUnit::getTypeManager().getLongType(true); }
#line 2693 "parser.cc"
    break;

  case 94:
#line 519 "parser.yy"
                {
                    TranslationUnit::instance().warnIfFloatUnsupported();
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getRealType(false);
                }
#line 2702 "parser.cc"
    break;

  case 95:
#line 523 "parser.yy"
                {
                    TranslationUnit::instance().warnIfFloatUnsupported();
                    (yyval.typeDesc) = TranslationUnit::getTypeManager().getRealType(false);
                    if (!doubleTypeWarningIssued)
                    {
                        warnmsg("`double' is an alias for `float' for this compiler");
                        doubleTypeWarningIssued = true;
                    }
                }
#line 2716 "parser.cc"
    break;

  case 96:
#line 535 "parser.yy"
                            { (yyval.typeDesc) = (yyvsp[0].typeDesc); }
#line 2722 "parser.cc"
    break;

  case 97:
#line 536 "parser.yy"
                            { (yyval.typeDesc) = TranslationUnit::getTypeManager().getVoidType(); }
#line 2728 "parser.cc"
    break;

  case 98:
#line 540 "parser.yy"
                                { (yyval.str) = strdup(sourceFilename.c_str()); }
#line 2734 "parser.cc"
    break;

  case 99:
#line 544 "parser.yy"
                                { (yyval.integer) = lineno; }
#line 2740 "parser.cc"
    break;

  case 100:
#line 548 "parser.yy"
                                        { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2746 "parser.cc"
    break;

  case 101:
#line 549 "parser.yy"
                                        { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2752 "parser.cc"
    break;

  case 102:
#line 553 "parser.yy"
                                                { (yyval.declaratorVector) = new std::vector<Declarator *>(); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2758 "parser.cc"
    break;

  case 103:
#line 554 "parser.yy"
                                                { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 2764 "parser.cc"
    break;

  case 104:
#line 560 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2770 "parser.cc"
    break;

  case 105:
#line 561 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[-2].declarator); (yyval.declarator)->setInitExpr((yyvsp[0].tree)); }
#line 2776 "parser.cc"
    break;

  case 106:
#line 565 "parser.yy"
                                        {
                                            (yyval.declarator) = (yyvsp[0].declarator);
                                            (yyval.declarator)->setPointerLevel((yyvsp[-1].typeQualifierBitFieldVector));  // ownership of $1 transferred to the Declarator
                                        }
#line 2785 "parser.cc"
    break;

  case 107:
#line 569 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2791 "parser.cc"
    break;

  case 108:
#line 574 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[0].str), 0, sourceFilename, lineno);
                free((yyvsp[0].str));
            }
#line 2800 "parser.cc"
    break;

  case 109:
#line 579 "parser.yy"
            {
                (yyval.declarator) = new Declarator(string(), 0, sourceFilename, lineno);
            }
#line 2808 "parser.cc"
    break;

  case 110:
#line 583 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->checkForFunctionReturningArray();
                (yyval.declarator)->addArraySizeExpr((yyvsp[-1].tree));
            }
#line 2818 "parser.cc"
    break;

  case 111:
#line 589 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->setFormalParamList((yyvsp[-1].formalParamList));
            }
#line 2827 "parser.cc"
    break;

  case 112:
#line 594 "parser.yy"
            {
                assert((yyvsp[-2].strList) != NULL);
                assert((yyvsp[0].formalParamList) != NULL);

                (yyval.declarator) = (yyvsp[-4].declarator);
                (yyval.declarator)->processKAndRFunctionParameters(*(yyvsp[-2].strList), (yyvsp[0].formalParamList));  // deletes $5, keeps no ref to $3
                
                delete (yyvsp[-2].strList);  // kr_parameter_name_list [vector<string> *]
            }
#line 2841 "parser.cc"
    break;

  case 113:
#line 604 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-2].declarator);
                FormalParamList *fpl = new FormalParamList();
                fpl->endWithEllipsis(true);  // ellipsis is implied
                (yyval.declarator)->setFormalParamList(fpl);
            }
#line 2852 "parser.cc"
    break;

  case 114:
#line 611 "parser.yy"
            {
                (yyval.declarator) = (yyvsp[-3].declarator);
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
#line 2861 "parser.cc"
    break;

  case 115:
#line 616 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[-4].str), (yyvsp[-5].integer), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                free((yyvsp[-4].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2872 "parser.cc"
    break;

  case 116:
#line 623 "parser.yy"
            {
                (yyval.declarator) = new Declarator(string(), (yyvsp[-4].integer), sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2882 "parser.cc"
    break;

  case 117:
#line 629 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[-5].str), (yyvsp[-6].integer), sourceFilename, lineno);
                (yyval.declarator)->setAsArrayOfFunctionPointers((yyvsp[-1].formalParamList), (yyvsp[-4].treeSequence));  // takes ownership of FormalParamList ($7), deletes $4
                free((yyvsp[-5].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2893 "parser.cc"
    break;

  case 118:
#line 636 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[-4].str), 0, sourceFilename, lineno);
                free((yyvsp[-4].str));
                (yyval.declarator)->setFormalParamList(new FormalParamList());
            }
#line 2903 "parser.cc"
    break;

  case 119:
#line 642 "parser.yy"
            {
                (yyval.declarator) = new Declarator((yyvsp[-4].str), 0, sourceFilename, lineno);
                (yyval.declarator)->setAsFunctionPointer((yyvsp[-1].formalParamList));  // takes ownership of FormalParamList
                free((yyvsp[-4].str));
                TranslationUnit::checkForEllipsisWithoutNamedArgument((yyvsp[-1].formalParamList));
            }
#line 2914 "parser.cc"
    break;

  case 120:
#line 655 "parser.yy"
            {
                // Make a Declarator from the function ID and the parameters.
                auto di = new Declarator((yyvsp[-7].str), 0, (yyvsp[-6].str), (yyvsp[-5].integer));  // pass ID, save_src_fn, save_line_no
                di->processKAndRFunctionParameters(*(yyvsp[-3].strList), (yyvsp[-1].formalParamList));  // deletes $7, keeps no ref to $5

                auto v = new std::vector<Declarator *>();
                v->push_back(di);  // 'v' owns 'di'

                // Make the return type 'int'.
                const TypeDesc *intTD = TranslationUnit::getTypeManager().getIntType(WORD_TYPE, true);
                TypeSpecifier intSpecifier(intTD, "", NULL);
                auto dsl = new DeclarationSpecifierList();
                dsl->add(intSpecifier);

                (yyval.tree) = TranslationUnit::instance().createDeclarationSequence(dsl, v);  // deletes 'dsl' and 'v'

                (yyval.tree)->setLineNo((yyvsp[-6].str), (yyvsp[-5].integer));

                delete (yyvsp[-3].strList);  // delete kr_parameter_name_list_opt
                free((yyvsp[-6].str));  // save_src_fn
                free((yyvsp[-7].str));  // ID
            }
#line 2941 "parser.cc"
    break;

  case 121:
#line 680 "parser.yy"
                                    { (yyval.integer) = 1; }
#line 2947 "parser.cc"
    break;

  case 122:
#line 681 "parser.yy"
                                    { ++(yyval.integer); }
#line 2953 "parser.cc"
    break;

  case 123:
#line 686 "parser.yy"
                                     { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2959 "parser.cc"
    break;

  case 124:
#line 687 "parser.yy"
                                     { (yyval.treeSequence) = (yyvsp[-1].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 2965 "parser.cc"
    break;

  case 125:
#line 691 "parser.yy"
                                     { (yyval.tree) = (yyvsp[-1].tree); }
#line 2971 "parser.cc"
    break;

  case 126:
#line 695 "parser.yy"
                                     { (yyval.formalParamList) = new FormalParamList(); (yyval.formalParamList)->endWithEllipsis(true); /* implied ellipsis */ }
#line 2977 "parser.cc"
    break;

  case 127:
#line 696 "parser.yy"
                                     { (yyval.formalParamList) = (yyvsp[0].formalParamList); }
#line 2983 "parser.cc"
    break;

  case 128:
#line 700 "parser.yy"
                                     { (yyval.tree) = (yyvsp[0].tree); }
#line 2989 "parser.cc"
    break;

  case 129:
#line 701 "parser.yy"
                                     { (yyval.tree) = (yyvsp[-1].treeSequence); }
#line 2995 "parser.cc"
    break;

  case 130:
#line 702 "parser.yy"
                                     { (yyval.tree) = (yyvsp[-2].treeSequence); }
#line 3001 "parser.cc"
    break;

  case 131:
#line 703 "parser.yy"
                    { (yyval.tree) = new TreeSequence(); }
#line 3007 "parser.cc"
    break;

  case 132:
#line 704 "parser.yy"
                    { (yyval.tree) = new TreeSequence(); }
#line 3013 "parser.cc"
    break;

  case 133:
#line 708 "parser.yy"
                                            { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3019 "parser.cc"
    break;

  case 134:
#line 709 "parser.yy"
                                            { (yyval.treeSequence) = (yyvsp[-2].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3025 "parser.cc"
    break;

  case 135:
#line 713 "parser.yy"
                                 { (yyval.classDef) = new ClassDef(); }
#line 3031 "parser.cc"
    break;

  case 136:
#line 714 "parser.yy"
                                 { (yyval.classDef) = (yyvsp[0].classDef); }
#line 3037 "parser.cc"
    break;

  case 137:
#line 719 "parser.yy"
                {
                    (yyval.classDef) = new ClassDef();
                    if ((yyvsp[0].classMemberList))
                        for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[0].classMemberList)->begin(); it != (yyvsp[0].classMemberList)->end(); ++it)
                            (yyval.classDef)->addDataMember(*it);
                    else
                        assert(0);
                    delete (yyvsp[0].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
#line 3051 "parser.cc"
    break;

  case 138:
#line 729 "parser.yy"
                {
                    (yyval.classDef) = (yyvsp[-1].classDef);
                    if ((yyvsp[0].classMemberList))
                        for (std::vector<ClassDef::ClassMember *>::iterator it = (yyvsp[0].classMemberList)->begin(); it != (yyvsp[0].classMemberList)->end(); ++it)
                            (yyval.classDef)->addDataMember(*it);
                    else
                        assert(0);
                    delete (yyvsp[0].classMemberList);  // destroy the std::vector<ClassDef::ClassMember *>
                }
#line 3065 "parser.cc"
    break;

  case 139:
#line 741 "parser.yy"
                                                             { (yyval.classMemberList) = ClassDef::createClassMembers((yyvsp[-2].declarationSpecifierList), (yyvsp[-1].declaratorVector)); }
#line 3071 "parser.cc"
    break;

  case 140:
#line 745 "parser.yy"
                                                    { (yyval.declaratorVector) = new std::vector<Declarator *>(); if ((yyvsp[0].declarator)) (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 3077 "parser.cc"
    break;

  case 141:
#line 746 "parser.yy"
                                                    { (yyval.declaratorVector) = (yyvsp[-2].declaratorVector); if ((yyvsp[0].declarator)) (yyval.declaratorVector)->push_back((yyvsp[0].declarator)); }
#line 3083 "parser.cc"
    break;

  case 142:
#line 751 "parser.yy"
                                        { (yyval.declarator) = (yyvsp[0].declarator); }
#line 3089 "parser.cc"
    break;

  case 143:
#line 753 "parser.yy"
                {
                    (yyval.declarator) = NULL;
                    Declarator temp("<unnamed>", 0, sourceFilename, lineno);
                    temp.setBitFieldWidth(*(yyvsp[0].tree));
                    temp.checkBitField(NULL);
                    delete (yyvsp[0].tree);
                }
#line 3101 "parser.cc"
    break;

  case 144:
#line 761 "parser.yy"
                {
                    (yyval.declarator) = (yyvsp[-2].declarator);
                    (yyval.declarator)->setBitFieldWidth(*(yyvsp[0].tree));
                    delete (yyvsp[0].tree);
                }
#line 3111 "parser.cc"
    break;

  case 145:
#line 769 "parser.yy"
                        { (yyval.compoundStmt) = new CompoundStmt(); if ((yyvsp[0].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[0].tree)); }
#line 3117 "parser.cc"
    break;

  case 146:
#line 770 "parser.yy"
                        { (yyval.compoundStmt) = (yyvsp[-1].compoundStmt); if ((yyvsp[0].tree) != NULL) (yyval.compoundStmt)->addTree((yyvsp[0].tree)); }
#line 3123 "parser.cc"
    break;

  case 147:
#line 774 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3129 "parser.cc"
    break;

  case 148:
#line 775 "parser.yy"
                        { (yyval.tree) = ((yyvsp[0].declarationSequence) ? (yyvsp[0].declarationSequence) : new TreeSequence()); }
#line 3135 "parser.cc"
    break;

  case 149:
#line 776 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].compoundStmt); }
#line 3141 "parser.cc"
    break;

  case 150:
#line 777 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3147 "parser.cc"
    break;

  case 151:
#line 778 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3153 "parser.cc"
    break;

  case 152:
#line 779 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3159 "parser.cc"
    break;

  case 153:
#line 780 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3165 "parser.cc"
    break;

  case 154:
#line 781 "parser.yy"
                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3171 "parser.cc"
    break;

  case 155:
#line 782 "parser.yy"
                        { (yyval.tree) = new JumpStmt((yyvsp[-1].str)); free((yyvsp[-1].str)); }
#line 3177 "parser.cc"
    break;

  case 156:
#line 783 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::BRK, NULL); }
#line 3183 "parser.cc"
    break;

  case 157:
#line 784 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::CONT, NULL); }
#line 3189 "parser.cc"
    break;

  case 158:
#line 785 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::RET, NULL); }
#line 3195 "parser.cc"
    break;

  case 159:
#line 786 "parser.yy"
                        { (yyval.tree) = new JumpStmt(JumpStmt::RET, (yyvsp[-1].tree)); }
#line 3201 "parser.cc"
    break;

  case 160:
#line 788 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt((yyvsp[-4].str), (yyvsp[-2].str), true);
                          free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 3208 "parser.cc"
    break;

  case 161:
#line 791 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt((yyvsp[-4].str), (yyvsp[-2].str), false);
                          free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 3215 "parser.cc"
    break;

  case 162:
#line 794 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt((yyvsp[-2].str), "", false);
                          free((yyvsp[-2].str)); }
#line 3222 "parser.cc"
    break;

  case 163:
#line 796 "parser.yy"
                        { (yyval.tree) = new AssemblerStmt(yytext); }
#line 3228 "parser.cc"
    break;

  case 164:
#line 801 "parser.yy"
                                    {
                                      (yyval.tree) = new LabeledStmt((yyvsp[-4].str), TranslationUnit::instance().generateLabel('L'), (yyvsp[0].tree));
                                      (yyval.tree)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer));
                                      free((yyvsp[-4].str)); free((yyvsp[-3].str));
                                    }
#line 3238 "parser.cc"
    break;

  case 165:
#line 807 "parser.yy"
                                    {
                                      (yyval.tree) = new LabeledStmt((yyvsp[-2].tree), (yyvsp[0].tree));
                                      (yyval.tree)->setLineNo((yyvsp[-4].str), (yyvsp[-3].integer));
                                    }
#line 3247 "parser.cc"
    break;

  case 166:
#line 812 "parser.yy"
                                    {
                                      (yyval.tree) = new LabeledStmt((yyvsp[0].tree));
                                      (yyval.tree)->setLineNo((yyvsp[-3].str), (yyvsp[-2].integer));
                                    }
#line 3256 "parser.cc"
    break;

  case 167:
#line 819 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3262 "parser.cc"
    break;

  case 168:
#line 823 "parser.yy"
                                { (yyval.tree) = new TreeSequence(); }
#line 3268 "parser.cc"
    break;

  case 169:
#line 824 "parser.yy"
                                { (yyval.tree) = (yyvsp[-1].tree); }
#line 3274 "parser.cc"
    break;

  case 170:
#line 828 "parser.yy"
                                { (yyval.tree) = NULL; }
#line 3280 "parser.cc"
    break;

  case 171:
#line 829 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3286 "parser.cc"
    break;

  case 172:
#line 833 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3292 "parser.cc"
    break;

  case 173:
#line 834 "parser.yy"
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
#line 3308 "parser.cc"
    break;

  case 174:
#line 848 "parser.yy"
                                            { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3314 "parser.cc"
    break;

  case 175:
#line 849 "parser.yy"
                                            { (yyvsp[-2].treeSequence)->addTree((yyvsp[0].tree)); (yyval.treeSequence) = (yyvsp[-2].treeSequence); }
#line 3320 "parser.cc"
    break;

  case 176:
#line 853 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3326 "parser.cc"
    break;

  case 177:
#line 859 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-4].tree), (yyvsp[0].tree)); free((yyvsp[-3].str)); }
#line 3332 "parser.cc"
    break;

  case 178:
#line 863 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::ASSIGNMENT; }
#line 3338 "parser.cc"
    break;

  case 179:
#line 864 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::INC_ASSIGN; }
#line 3344 "parser.cc"
    break;

  case 180:
#line 865 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::DEC_ASSIGN; }
#line 3350 "parser.cc"
    break;

  case 181:
#line 866 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::MUL_ASSIGN; }
#line 3356 "parser.cc"
    break;

  case 182:
#line 867 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::DIV_ASSIGN; }
#line 3362 "parser.cc"
    break;

  case 183:
#line 868 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::MOD_ASSIGN; }
#line 3368 "parser.cc"
    break;

  case 184:
#line 869 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::XOR_ASSIGN; }
#line 3374 "parser.cc"
    break;

  case 185:
#line 870 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::AND_ASSIGN; }
#line 3380 "parser.cc"
    break;

  case 186:
#line 871 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::OR_ASSIGN; }
#line 3386 "parser.cc"
    break;

  case 187:
#line 872 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::LEFT_ASSIGN; }
#line 3392 "parser.cc"
    break;

  case 188:
#line 873 "parser.yy"
                                                { (yyval.binop) = BinaryOpExpr::RIGHT_ASSIGN; }
#line 3398 "parser.cc"
    break;

  case 189:
#line 877 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3404 "parser.cc"
    break;

  case 190:
#line 879 "parser.yy"
                                                { (yyval.tree) = new ConditionalExpr((yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3410 "parser.cc"
    break;

  case 191:
#line 883 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3416 "parser.cc"
    break;

  case 192:
#line 885 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3422 "parser.cc"
    break;

  case 193:
#line 889 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3428 "parser.cc"
    break;

  case 194:
#line 891 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::LOGICAL_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3434 "parser.cc"
    break;

  case 195:
#line 895 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3440 "parser.cc"
    break;

  case 196:
#line 897 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3446 "parser.cc"
    break;

  case 197:
#line 900 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3452 "parser.cc"
    break;

  case 198:
#line 902 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_XOR, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3458 "parser.cc"
    break;

  case 199:
#line 905 "parser.yy"
                                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3464 "parser.cc"
    break;

  case 200:
#line 907 "parser.yy"
                { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::BITWISE_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3470 "parser.cc"
    break;

  case 201:
#line 910 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3476 "parser.cc"
    break;

  case 202:
#line 912 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3482 "parser.cc"
    break;

  case 203:
#line 916 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::EQUALITY; }
#line 3488 "parser.cc"
    break;

  case 204:
#line 917 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::INEQUALITY; }
#line 3494 "parser.cc"
    break;

  case 205:
#line 921 "parser.yy"
                                        { (yyval.tree) = (yyvsp[0].tree); }
#line 3500 "parser.cc"
    break;

  case 206:
#line 922 "parser.yy"
                                        { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3506 "parser.cc"
    break;

  case 207:
#line 926 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3512 "parser.cc"
    break;

  case 208:
#line 927 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::LEFT_SHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3519 "parser.cc"
    break;

  case 209:
#line 929 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr(
                                        BinaryOpExpr::RIGHT_SHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3526 "parser.cc"
    break;

  case 210:
#line 934 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::INFERIOR; }
#line 3532 "parser.cc"
    break;

  case 211:
#line 935 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::INFERIOR_OR_EQUAL; }
#line 3538 "parser.cc"
    break;

  case 212:
#line 936 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::SUPERIOR; }
#line 3544 "parser.cc"
    break;

  case 213:
#line 937 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::SUPERIOR_OR_EQUAL; }
#line 3550 "parser.cc"
    break;

  case 214:
#line 941 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3556 "parser.cc"
    break;

  case 215:
#line 942 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3562 "parser.cc"
    break;

  case 216:
#line 946 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::ADD; }
#line 3568 "parser.cc"
    break;

  case 217:
#line 947 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::SUB; }
#line 3574 "parser.cc"
    break;

  case 218:
#line 951 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3580 "parser.cc"
    break;

  case 219:
#line 952 "parser.yy"
                                { (yyval.tree) = new BinaryOpExpr((yyvsp[-1].binop), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3586 "parser.cc"
    break;

  case 220:
#line 956 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::MUL; }
#line 3592 "parser.cc"
    break;

  case 221:
#line 957 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::DIV; }
#line 3598 "parser.cc"
    break;

  case 222:
#line 958 "parser.yy"
                                { (yyval.binop) = BinaryOpExpr::MOD; }
#line 3604 "parser.cc"
    break;

  case 223:
#line 962 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3610 "parser.cc"
    break;

  case 224:
#line 963 "parser.yy"
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
#line 3635 "parser.cc"
    break;

  case 225:
#line 983 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREINC, (yyvsp[0].tree)); }
#line 3641 "parser.cc"
    break;

  case 226:
#line 984 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::PREDEC, (yyvsp[0].tree)); }
#line 3647 "parser.cc"
    break;

  case 227:
#line 985 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr((yyvsp[-1].typeDesc)); }
#line 3653 "parser.cc"
    break;

  case 228:
#line 986 "parser.yy"
                                { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::SIZE_OF, (yyvsp[0].tree)); }
#line 3659 "parser.cc"
    break;

  case 229:
#line 990 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::IDENTITY; }
#line 3665 "parser.cc"
    break;

  case 230:
#line 991 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::NEG; }
#line 3671 "parser.cc"
    break;

  case 231:
#line 992 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::ADDRESS_OF; }
#line 3677 "parser.cc"
    break;

  case 232:
#line 993 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::INDIRECTION; }
#line 3683 "parser.cc"
    break;

  case 233:
#line 994 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::BOOLEAN_NEG; }
#line 3689 "parser.cc"
    break;

  case 234:
#line 995 "parser.yy"
                        { (yyval.unop) = UnaryOpExpr::BITWISE_NOT; }
#line 3695 "parser.cc"
    break;

  case 235:
#line 999 "parser.yy"
                                    { (yyval.tree) = (yyvsp[0].tree); }
#line 3701 "parser.cc"
    break;

  case 236:
#line 1000 "parser.yy"
                                    { (yyval.tree) = new CastExpr((yyvsp[-2].typeDesc), (yyvsp[0].tree)); }
#line 3707 "parser.cc"
    break;

  case 237:
#line 1004 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3713 "parser.cc"
    break;

  case 238:
#line 1006 "parser.yy"
                        { (yyval.tree) = new FunctionCallExpr((yyvsp[-4].tree), new TreeSequence());
                          free((yyvsp[-3].str)); }
#line 3720 "parser.cc"
    break;

  case 239:
#line 1009 "parser.yy"
                        { (yyval.tree) = new FunctionCallExpr((yyvsp[-5].tree), (yyvsp[-1].treeSequence));
                          free((yyvsp[-4].str)); }
#line 3727 "parser.cc"
    break;

  case 240:
#line 1012 "parser.yy"
                        { (yyval.tree) = new BinaryOpExpr(BinaryOpExpr::ARRAY_REF, (yyvsp[-3].tree), (yyvsp[-1].tree)); }
#line 3733 "parser.cc"
    break;

  case 241:
#line 1014 "parser.yy"
                        { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTINC, (yyvsp[-1].tree)); }
#line 3739 "parser.cc"
    break;

  case 242:
#line 1016 "parser.yy"
                        { (yyval.tree) = new UnaryOpExpr(UnaryOpExpr::POSTDEC, (yyvsp[-1].tree)); }
#line 3745 "parser.cc"
    break;

  case 243:
#line 1018 "parser.yy"
                        { (yyval.tree) = new ObjectMemberExpr((yyvsp[-2].tree), (yyvsp[0].str), true); free((yyvsp[0].str)); }
#line 3751 "parser.cc"
    break;

  case 244:
#line 1020 "parser.yy"
                        { (yyval.tree) = new ObjectMemberExpr((yyvsp[-2].tree), (yyvsp[0].str), false); free((yyvsp[0].str)); }
#line 3757 "parser.cc"
    break;

  case 245:
#line 1024 "parser.yy"
                        { (yyval.tree) = new IdentifierExpr((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 3763 "parser.cc"
    break;

  case 246:
#line 1025 "parser.yy"
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
#line 3786 "parser.cc"
    break;

  case 247:
#line 1043 "parser.yy"
                        { (yyval.tree) = new WordConstantExpr((int8_t) (yyvsp[0].character), false, true); }
#line 3792 "parser.cc"
    break;

  case 248:
#line 1044 "parser.yy"
                        { (yyval.tree) = new StringLiteralExpr((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 3798 "parser.cc"
    break;

  case 249:
#line 1045 "parser.yy"
                        { (yyval.tree) = (yyvsp[-1].tree); }
#line 3804 "parser.cc"
    break;

  case 250:
#line 1049 "parser.yy"
                        { (yyval.str) = (yyvsp[0].str); }
#line 3810 "parser.cc"
    break;

  case 251:
#line 1050 "parser.yy"
                        {
                            (yyval.str) = (char *) malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 1);
                            strcpy((yyval.str), (yyvsp[-1].str));
                            strcat((yyval.str), (yyvsp[0].str));
                            free((yyvsp[-1].str)); free((yyvsp[0].str));
                        }
#line 3821 "parser.cc"
    break;

  case 252:
#line 1059 "parser.yy"
                        { (yyval.treeSequence) = NULL; }
#line 3827 "parser.cc"
    break;

  case 253:
#line 1060 "parser.yy"
                        { (yyval.treeSequence) = (yyvsp[0].treeSequence); }
#line 3833 "parser.cc"
    break;

  case 254:
#line 1064 "parser.yy"
                                { (yyval.treeSequence) = new TreeSequence(); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3839 "parser.cc"
    break;

  case 255:
#line 1065 "parser.yy"
                                { (yyval.treeSequence) = (yyvsp[-2].treeSequence); (yyval.treeSequence)->addTree((yyvsp[0].tree)); }
#line 3845 "parser.cc"
    break;

  case 256:
#line 1069 "parser.yy"
                                                { (yyval.tree) = new IfStmt((yyvsp[-3].tree), (yyvsp[-1].tree), (yyvsp[0].tree)); }
#line 3851 "parser.cc"
    break;

  case 257:
#line 1070 "parser.yy"
                                                { (yyval.tree) = new SwitchStmt((yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 3857 "parser.cc"
    break;

  case 258:
#line 1074 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3863 "parser.cc"
    break;

  case 259:
#line 1078 "parser.yy"
                                { (yyval.tree) = NULL; }
#line 3869 "parser.cc"
    break;

  case 260:
#line 1079 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3875 "parser.cc"
    break;

  case 261:
#line 1083 "parser.yy"
                                        { (yyval.tree) = new WhileStmt((yyvsp[-2].tree), (yyvsp[0].tree), false); }
#line 3881 "parser.cc"
    break;

  case 262:
#line 1087 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].tree); }
#line 3887 "parser.cc"
    break;

  case 263:
#line 1091 "parser.yy"
                                                { (yyval.tree) = new WhileStmt((yyvsp[-2].tree), (yyvsp[-5].tree), true); }
#line 3893 "parser.cc"
    break;

  case 264:
#line 1095 "parser.yy"
                                { (yyval.tree) = (yyvsp[-1].treeSequence); }
#line 3899 "parser.cc"
    break;

  case 265:
#line 1096 "parser.yy"
                                { (yyval.tree) = (yyvsp[0].declarationSequence); }
#line 3905 "parser.cc"
    break;

  case 266:
#line 1104 "parser.yy"
                                { if ( (yyvsp[-11].tree))  (yyvsp[-11].tree)->setLineNo((yyvsp[-13].str), (yyvsp[-12].integer));
                                  if ( (yyvsp[-8].tree))  (yyvsp[-8].tree)->setLineNo((yyvsp[-10].str), (yyvsp[-9].integer));
                                  if ((yyvsp[-4].treeSequence)) (yyvsp[-4].treeSequence)->setLineNo((yyvsp[-6].str), (yyvsp[-5].integer));
                                  (yyval.tree) = new ForStmt((yyvsp[-11].tree), (yyvsp[-8].tree), (yyvsp[-4].treeSequence), (yyvsp[0].tree));
                                  free((yyvsp[-13].str)); free((yyvsp[-10].str)); free((yyvsp[-6].str)); free((yyvsp[-2].str));
                                }
#line 3916 "parser.cc"
    break;


#line 3920 "parser.cc"

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
#line 1112 "parser.yy"


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
