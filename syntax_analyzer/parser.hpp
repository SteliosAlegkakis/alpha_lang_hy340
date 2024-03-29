
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     BREAK = 289,
     CONTINUE = 290,
     AND = 291,
     NOT = 292,
     OR = 293,
     LOCAL = 294,
     ASSIGN = 295,
     NIL = 296,
     TRUE = 297,
     FALSE = 298,
     STRING = 299,
     ID = 300,
     INTEGER = 301,
     REAL = 302,
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
#define BREAK 289
#define CONTINUE 290
#define AND 291
#define NOT 292
#define OR 293
#define LOCAL 294
#define ASSIGN 295
#define NIL 296
#define TRUE 297
#define FALSE 298
#define STRING 299
#define ID 300
#define INTEGER 301
#define REAL 302
#define UMINUS 303




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 13 "parser.y"

  char* stringValue;
  int intValue;
  double realValue;
  struct SymtabEntry* exprNode;



/* Line 1676 of yacc.c  */
#line 157 "parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE alpha_yylval;


