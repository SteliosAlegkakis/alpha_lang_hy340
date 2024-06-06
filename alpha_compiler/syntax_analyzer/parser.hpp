/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_ALPHA_YY_PARSER_HPP_INCLUDED
# define YY_ALPHA_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int alpha_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    PLUS_PLUS = 262,
    MINUS_MINUS = 263,
    MODULO = 264,
    EQUAL = 265,
    NOT_EQUAL = 266,
    GREATER = 267,
    LESSER = 268,
    LESSER_EQUAL = 269,
    GREATER_EQUAL = 270,
    LPAREN = 271,
    RPAREN = 272,
    LCURLY = 273,
    RCURLY = 274,
    LSQUARE = 275,
    RSQUARE = 276,
    COLON = 277,
    SEMICOLON = 278,
    DCOLON = 279,
    COMMA = 280,
    PERIOD = 281,
    DPERIOD = 282,
    IF = 283,
    ELSE = 284,
    WHILE = 285,
    FOR = 286,
    FUNCTION = 287,
    RETURN = 288,
    AND = 289,
    NOT = 290,
    OR = 291,
    LOCAL = 292,
    ASSIGN = 293,
    NIL = 294,
    TRUE = 295,
    FALSE = 296,
    STRING = 297,
    ID = 298,
    INTEGER = 299,
    REAL = 300,
    BREAK = 301,
    CONTINUE = 302,
    UMINUS = 303
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define PLUS_PLUS 262
#define MINUS_MINUS 263
#define MODULO 264
#define EQUAL 265
#define NOT_EQUAL 266
#define GREATER 267
#define LESSER 268
#define LESSER_EQUAL 269
#define GREATER_EQUAL 270
#define LPAREN 271
#define RPAREN 272
#define LCURLY 273
#define RCURLY 274
#define LSQUARE 275
#define RSQUARE 276
#define COLON 277
#define SEMICOLON 278
#define DCOLON 279
#define COMMA 280
#define PERIOD 281
#define DPERIOD 282
#define IF 283
#define ELSE 284
#define WHILE 285
#define FOR 286
#define FUNCTION 287
#define RETURN 288
#define AND 289
#define NOT 290
#define OR 291
#define LOCAL 292
#define ASSIGN 293
#define NIL 294
#define TRUE 295
#define FALSE 296
#define STRING 297
#define ID 298
#define INTEGER 299
#define REAL 300
#define BREAK 301
#define CONTINUE 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "parser.y"

  char* stringValue;
  int intValue;
  unsigned int uintValue;
  double realValue;
  struct SymtabEntry* symbol;
  struct expr* expr;
  struct call* call;
  struct stmt_t* stmt_stmt;
  struct forprefix* _forprefix;

#line 165 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE alpha_yylval;

int alpha_yyparse (void);

#endif /* !YY_ALPHA_YY_PARSER_HPP_INCLUDED  */
