
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
     NUMBER = 258,
     ADD = 259,
     SUB = 260,
     MUL = 261,
     DIV = 262,
     PLUS_PLUS = 263,
     MINUS_MINUS = 264,
     MODULO = 265,
     EQUAL = 266,
     NOT_EQUAL = 267,
     GREATER = 268,
     LESSER = 269,
     LESSER_EQUAL = 270,
     GREATER_EQUAL = 271,
     LPAREN = 272,
     RPAREN = 273,
     LCURLY = 274,
     RCURLY = 275,
     LSQUARE = 276,
     RSQUARE = 277,
     COLON = 278,
     SEMICOLON = 279,
     DCOLON = 280,
     COMMA = 281,
     PERIOD = 282,
     DPERIOD = 283,
     IF = 284,
     ELSE = 285,
     WHILE = 286,
     FOR = 287,
     FUNCTION = 288,
     RETURN = 289,
     BREAK = 290,
     CONTINUE = 291,
     AND = 292,
     NOT = 293,
     OR = 294,
     LOCAL = 295,
     ASSIGN = 296,
     ID = 297,
     INTEGER = 298,
     REAL = 299,
     NIL = 300,
     TRUE = 301,
     FALSE = 302,
     STRING = 303,
     UMINUS = 304
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define ADD 259
#define SUB 260
#define MUL 261
#define DIV 262
#define PLUS_PLUS 263
#define MINUS_MINUS 264
#define MODULO 265
#define EQUAL 266
#define NOT_EQUAL 267
#define GREATER 268
#define LESSER 269
#define LESSER_EQUAL 270
#define GREATER_EQUAL 271
#define LPAREN 272
#define RPAREN 273
#define LCURLY 274
#define RCURLY 275
#define LSQUARE 276
#define RSQUARE 277
#define COLON 278
#define SEMICOLON 279
#define DCOLON 280
#define COMMA 281
#define PERIOD 282
#define DPERIOD 283
#define IF 284
#define ELSE 285
#define WHILE 286
#define FOR 287
#define FUNCTION 288
#define RETURN 289
#define BREAK 290
#define CONTINUE 291
#define AND 292
#define NOT 293
#define OR 294
#define LOCAL 295
#define ASSIGN 296
#define ID 297
#define INTEGER 298
#define REAL 299
#define NIL 300
#define TRUE 301
#define FALSE 302
#define STRING 303
#define UMINUS 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 14 "parser.y"

char* stringValue;
int intValue;
double realValue;



/* Line 1676 of yacc.c  */
#line 158 "parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE alpha_yylval;


