/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 215 "parser.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


