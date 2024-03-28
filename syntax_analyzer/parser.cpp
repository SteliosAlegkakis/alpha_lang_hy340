
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Substitute the variable and function names.  */
#define yyparse         alpha_yyparse
#define yylex           alpha_yylex
#define yyerror         alpha_yyerror
#define yylval          alpha_yylval
#define yychar          alpha_yychar
#define yydebug         alpha_yydebug
#define yynerrs         alpha_yynerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include "./symbol_table/symbol_table.hpp"
int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;
FILE* rulesFile = fopen("rules.txt", "w");
int anonymousCounter = 0;
extern bool isFormal;
char* make_anonymous_func();
bool is_libfunc(char* id);
void print_error(const char* msg);
const char* unionType_toString(int union_type);


/* Line 189 of yacc.c  */
#line 98 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
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

/* Line 214 of yacc.c  */
#line 22 "parser.y"

char* stringValue;
int intValue;
double realValue;
 struct SymtabEntry* exprNode;



/* Line 214 of yacc.c  */
#line 239 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 251 "parser.cpp"

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
# if YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   599

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNRULES -- Number of states.  */
#define YYNSTATES  179

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    14,    16,    18,
      20,    23,    26,    28,    30,    32,    34,    38,    42,    46,
      50,    54,    58,    62,    66,    70,    74,    78,    82,    86,
      88,    92,    95,    98,   101,   102,   106,   109,   110,   114,
     116,   117,   122,   124,   126,   128,   132,   134,   136,   139,
     142,   144,   148,   153,   157,   162,   167,   168,   172,   179,
     181,   183,   187,   193,   195,   199,   200,   204,   208,   210,
     214,   220,   221,   226,   227,   228,   229,   239,   240,   241,
     242,   251,   253,   255,   257,   259,   261,   263,   265,   269,
     270,   278,   284,   290,   300,   304
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    51,    52,    -1,    -1,    53,
      23,    -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,
      34,    23,    -1,    35,    23,    -1,    71,    -1,    73,    -1,
      23,    -1,    57,    -1,    53,     3,    53,    -1,    53,     4,
      53,    -1,    53,     5,    53,    -1,    53,     6,    53,    -1,
      53,     9,    53,    -1,    53,    12,    53,    -1,    53,    15,
      53,    -1,    53,    13,    53,    -1,    53,    14,    53,    -1,
      53,    10,    53,    -1,    53,    11,    53,    -1,    53,    36,
      53,    -1,    53,    38,    53,    -1,    54,    -1,    16,    53,
      17,    -1,     4,    53,    -1,    37,    53,    -1,     7,    60,
      -1,    -1,    60,    55,     7,    -1,     8,    60,    -1,    -1,
      60,    56,     8,    -1,    59,    -1,    -1,    60,    58,    40,
      53,    -1,    60,    -1,    62,    -1,    68,    -1,    16,    73,
      17,    -1,    80,    -1,    45,    -1,    39,    45,    -1,    24,
      45,    -1,    61,    -1,    60,    26,    45,    -1,    60,    20,
      53,    21,    -1,    62,    26,    45,    -1,    62,    20,    53,
      21,    -1,    62,    16,    67,    17,    -1,    -1,    60,    63,
      64,    -1,    16,    73,    17,    16,    67,    17,    -1,    65,
      -1,    66,    -1,    16,    67,    17,    -1,    27,    45,    16,
      67,    17,    -1,    53,    -1,    67,    25,    53,    -1,    -1,
      20,    67,    21,    -1,    20,    69,    21,    -1,    70,    -1,
      69,    25,    70,    -1,    18,    53,    22,    53,    19,    -1,
      -1,    18,    72,    51,    19,    -1,    -1,    -1,    -1,    32,
      45,    74,    16,    75,    81,    17,    76,    71,    -1,    -1,
      -1,    -1,    32,    77,    16,    78,    81,    17,    79,    71,
      -1,    46,    -1,    47,    -1,    44,    -1,    41,    -1,    42,
      -1,    43,    -1,    45,    -1,    81,    25,    45,    -1,    -1,
      28,    16,    53,    17,    52,    29,    52,    -1,    28,    16,
      53,    17,    52,    -1,    30,    16,    53,    17,    52,    -1,
      31,    16,    67,    23,    53,    23,    67,    17,    52,    -1,
      33,    53,    23,    -1,    33,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    67,    68,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
     100,   101,   102,   103,   104,   104,   105,   106,   106,   107,
     110,   110,   113,   114,   115,   116,   117,   120,   130,   144,
     153,   156,   157,   158,   159,   162,   163,   163,   164,   167,
     168,   171,   174,   177,   178,   179,   182,   183,   186,   187,
     190,   193,   193,   196,   202,   202,   196,   203,   203,   203,
     203,   206,   207,   208,   209,   210,   211,   214,   231,   248,
     251,   252,   255,   258,   261,   262
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "PLUS_PLUS",
  "MINUS_MINUS", "MODULO", "EQUAL", "NOT_EQUAL", "GREATER", "LESSER",
  "LESSER_EQUAL", "GREATER_EQUAL", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
  "LSQUARE", "RSQUARE", "COLON", "SEMICOLON", "DCOLON", "COMMA", "PERIOD",
  "DPERIOD", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "ASSIGN", "NIL", "TRUE",
  "FALSE", "STRING", "ID", "INTEGER", "REAL", "UMINUS", "$accept",
  "program", "statements", "stmt", "expr", "term", "$@1", "$@2",
  "assignment", "$@3", "primary", "lvalue", "member", "call", "$@4",
  "callsuffix", "normcall", "methodcall", "elist", "objectdef", "indexed",
  "indexedelem", "block", "$@5", "funcdef", "$@6", "$@7", "$@8", "$@9",
  "$@10", "$@11", "const", "idlist", "ifstmt", "whilestmt", "forstmt",
  "returnstmt", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    55,    54,    54,    56,    54,    54,
      58,    57,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    61,    62,    63,    62,    62,    64,
      64,    65,    66,    67,    67,    67,    68,    68,    69,    69,
      70,    72,    71,    74,    75,    76,    73,    77,    78,    79,
      73,    80,    80,    80,    80,    80,    80,    81,    81,    81,
      82,    82,    83,    84,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     0,     3,     2,     0,     3,     1,
       0,     4,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     0,     3,     6,     1,
       1,     3,     5,     1,     3,     0,     3,     3,     1,     3,
       5,     0,     4,     0,     0,     0,     9,     0,     0,     0,
       8,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       7,     5,     5,     9,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,    71,    65,
      14,     0,     0,     0,     0,    77,     0,     0,     0,     0,
       0,    84,    85,    86,    83,    47,    81,    82,     3,     0,
      29,    15,    39,    42,    50,    43,    44,    12,    13,    46,
       6,     7,     8,     9,    31,     0,    33,     0,    36,     0,
       0,     4,     0,    63,     0,     0,    68,    49,     0,     0,
      65,    73,     0,    95,     0,    10,    11,    32,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,     0,     0,    30,    45,     0,     0,    66,     0,    67,
       0,     0,     0,     0,     0,    78,    94,    16,    17,    18,
      19,    20,    25,    26,    21,    23,    24,    22,    27,    28,
       0,    51,    35,    38,     0,    65,     0,    57,    59,    60,
       0,     0,    53,     0,    65,    72,     0,    64,    69,     0,
       0,     0,    74,    89,    52,    41,     0,     0,    55,    54,
       0,     0,    91,    92,     0,    89,    87,     0,    61,    65,
      58,    70,     0,    65,     0,    79,     0,     0,    90,     0,
      75,     0,    88,    62,     0,     0,    80,    93,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    53,    30,    85,    86,    31,    87,
      32,    33,    34,    35,    88,   127,   128,   129,    54,    36,
      55,    56,    37,    51,    38,   104,   155,   175,    62,   143,
     171,    39,   157,    40,    41,    42,    43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -112
static const yytype_int16 yypact[] =
{
    -112,     4,   124,  -112,   235,   158,   158,   169,  -112,   180,
    -112,   -38,     3,    11,    45,   -21,   224,    88,    91,   235,
      74,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,   280,
    -112,  -112,  -112,    75,  -112,    97,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,    58,    38,    97,    38,   295,
     110,  -112,   235,   535,    34,    41,  -112,  -112,   235,   235,
     235,  -112,   113,  -112,   331,  -112,  -112,  -112,  -112,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
    -112,   235,   235,   235,    96,   126,   135,   105,   -15,   235,
     235,   101,   132,  -112,   134,     2,   346,  -112,   235,  -112,
     133,   382,   397,    15,   137,  -112,  -112,   115,   115,  -112,
    -112,  -112,   548,   548,   584,   584,   584,   584,   571,    94,
     433,  -112,  -112,  -112,   235,   235,   117,  -112,  -112,  -112,
     -14,   446,  -112,   134,   235,  -112,   235,   535,  -112,   124,
     124,   235,  -112,   119,  -112,   535,    -9,   159,  -112,  -112,
       6,   482,   149,  -112,   499,   119,  -112,    35,  -112,   235,
    -112,  -112,   124,   235,    67,  -112,   136,    69,  -112,    93,
    -112,   161,  -112,  -112,   124,   161,  -112,  -112,  -112
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,   129,  -111,    -2,  -112,  -112,  -112,  -112,  -112,
    -112,   120,  -112,   130,  -112,  -112,  -112,  -112,   -47,  -112,
    -112,    83,   -86,  -112,     8,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,    31,  -112,  -112,  -112,  -112
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -57
static const yytype_int16 yytable[] =
{
      29,   125,    44,   148,     3,    49,     4,    57,   158,     5,
       6,    98,   126,   103,    64,    50,    98,    67,     7,    58,
       8,   135,     9,   160,    61,    10,    11,    59,   152,   153,
      12,    98,    13,    14,    15,    16,    17,    18,   141,    19,
      98,    20,   130,    21,    22,    23,    24,    25,    26,    27,
      96,   168,   165,    92,   -56,    97,   101,   102,    83,    98,
     166,    60,    99,   177,    84,   -56,   100,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   146,   118,
     119,   120,   -34,   -37,   170,   176,   173,   150,   131,   178,
      15,   -56,   166,    29,    98,    83,   137,    69,    70,    71,
      72,    84,   -56,    73,    74,    75,    76,    77,    78,    79,
     174,    65,   167,    89,    66,   -40,   169,    90,    98,    68,
      71,    72,   145,    91,    73,    46,    48,    94,     4,   105,
      81,     5,     6,   122,   151,    47,    47,    29,    29,   154,
       7,   121,     8,   123,     9,   124,   132,    10,    11,   133,
     134,    52,    12,   142,    13,    14,    15,    16,    17,    18,
      29,    19,   147,    20,   156,    21,    22,    23,    24,    25,
      26,    27,    29,     4,    45,   159,     5,     6,   162,     8,
      95,   172,    11,   138,     4,     7,   164,     5,     6,     9,
       0,     0,     0,    11,     0,     0,     7,    20,    52,     0,
       9,    15,     0,    25,    11,     0,    19,     0,    20,     0,
      21,    22,    23,    24,    25,    26,    27,    19,     0,    20,
       0,    21,    22,    23,    24,    25,    26,    27,     4,     0,
       0,     5,     6,     0,     0,     0,     0,     0,     0,     4,
       7,     0,     5,     6,     9,     0,     0,    63,    11,     0,
       0,     7,     0,     0,     0,     9,     0,     0,     0,    11,
       0,    19,     0,    20,     0,    21,    22,    23,    24,    25,
      26,    27,    19,     0,    20,     0,    21,    22,    23,    24,
      25,    26,    27,    69,    70,    71,    72,     0,     0,    73,
      74,    75,    76,    77,    78,    79,     0,     0,    69,    70,
      71,    72,     0,    80,    73,    74,    75,    76,    77,    78,
      79,     0,    93,     0,     0,     0,    81,     0,    82,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,     0,    82,    69,    70,    71,    72,     0,     0,
      73,    74,    75,    76,    77,    78,    79,     0,     0,    69,
      70,    71,    72,     0,   106,    73,    74,    75,    76,    77,
      78,    79,     0,     0,     0,     0,     0,    81,   136,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    81,     0,    82,    69,    70,    71,    72,     0,
       0,    73,    74,    75,    76,    77,    78,    79,     0,   139,
      69,    70,    71,    72,     0,     0,    73,    74,    75,    76,
      77,    78,    79,     0,   140,     0,     0,     0,    81,     0,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,     0,    82,    69,    70,    71,    72,
       0,     0,    73,    74,    75,    76,    77,    78,    79,    69,
      70,    71,    72,     0,   144,    73,    74,    75,    76,    77,
      78,    79,     0,     0,     0,     0,     0,   149,     0,    81,
       0,    82,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    81,     0,    82,    69,    70,    71,    72,     0,
       0,    73,    74,    75,    76,    77,    78,    79,     0,     0,
       0,   161,    69,    70,    71,    72,     0,     0,    73,    74,
      75,    76,    77,    78,    79,     0,     0,     0,    81,     0,
      82,     0,   163,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,     0,    82,    69,    70,
      71,    72,     0,     0,    73,    74,    75,    76,    77,    78,
      79,    69,    70,    71,    72,     0,     0,    73,   -57,   -57,
      76,    77,    78,    79,     0,     0,     0,     0,     0,     0,
       0,    81,     0,    82,    69,    70,    71,    72,     0,     0,
      73,    74,    75,    76,    77,    78,    79,    69,    70,    71,
      72,     0,     0,    73,     0,     0,   -57,   -57,   -57,   -57
};

static const yytype_int16 yycheck[] =
{
       2,    16,     4,    17,     0,     7,     4,    45,    17,     7,
       8,    25,    27,    60,    16,     7,    25,    19,    16,    16,
      18,    19,    20,    17,    45,    23,    24,    16,   139,   140,
      28,    25,    30,    31,    32,    33,    34,    35,    23,    37,
      25,    39,    89,    41,    42,    43,    44,    45,    46,    47,
      52,   162,    17,    45,    16,    21,    58,    59,    20,    25,
      25,    16,    21,   174,    26,    27,    25,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,   125,    81,
      82,    83,     7,     8,    17,   171,    17,   134,    90,   175,
      32,    16,    25,    95,    25,    20,    98,     3,     4,     5,
       6,    26,    27,     9,    10,    11,    12,    13,    14,    15,
      17,    23,   159,    16,    23,    40,   163,    20,    25,    45,
       5,     6,   124,    26,     9,     5,     6,    17,     4,    16,
      36,     7,     8,     7,   136,     5,     6,   139,   140,   141,
      16,    45,    18,     8,    20,    40,    45,    23,    24,    17,
      16,    18,    28,    16,    30,    31,    32,    33,    34,    35,
     162,    37,    45,    39,    45,    41,    42,    43,    44,    45,
      46,    47,   174,     4,    16,    16,     7,     8,    29,    18,
      51,    45,    24,   100,     4,    16,   155,     7,     8,    20,
      -1,    -1,    -1,    24,    -1,    -1,    16,    39,    18,    -1,
      20,    32,    -1,    45,    24,    -1,    37,    -1,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    37,    -1,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,     4,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,     4,
      16,    -1,     7,     8,    20,    -1,    -1,    23,    24,    -1,
      -1,    16,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,
      -1,    37,    -1,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    37,    -1,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,     6,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,     3,     4,
       5,     6,    -1,    23,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    36,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    38,     3,     4,     5,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,     3,
       4,     5,     6,    -1,    23,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    36,    22,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    38,     3,     4,     5,     6,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    -1,    17,
       3,     4,     5,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    -1,    17,    -1,    -1,    -1,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    38,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,     3,
       4,     5,     6,    -1,    21,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    21,    -1,    36,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    38,     3,     4,     5,     6,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    19,     3,     4,     5,     6,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    36,    -1,
      38,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    38,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,     3,     4,     5,     6,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    38,     3,     4,     5,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,     3,     4,     5,
       6,    -1,    -1,     9,    -1,    -1,    12,    13,    14,    15
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,     0,     4,     7,     8,    16,    18,    20,
      23,    24,    28,    30,    31,    32,    33,    34,    35,    37,
      39,    41,    42,    43,    44,    45,    46,    47,    52,    53,
      54,    57,    59,    60,    61,    62,    68,    71,    73,    80,
      82,    83,    84,    85,    53,    16,    60,    62,    60,    53,
      73,    72,    18,    53,    67,    69,    70,    45,    16,    16,
      16,    45,    77,    23,    53,    23,    23,    53,    45,     3,
       4,     5,     6,     9,    10,    11,    12,    13,    14,    15,
      23,    36,    38,    20,    26,    55,    56,    58,    63,    16,
      20,    26,    73,    17,    17,    51,    53,    21,    25,    21,
      25,    53,    53,    67,    74,    16,    23,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    45,     7,     8,    40,    16,    27,    64,    65,    66,
      67,    53,    45,    17,    16,    19,    22,    53,    70,    17,
      17,    23,    16,    78,    21,    53,    67,    45,    17,    21,
      67,    53,    52,    52,    53,    75,    45,    81,    17,    16,
      17,    19,    29,    23,    81,    17,    25,    67,    52,    67,
      17,    79,    45,    17,    17,    76,    71,    52,    71
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

/* Line 1455 of yacc.c  */
#line 64 "parser.y"
    {fprintf(rulesFile, "program -> statements\n");}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 67 "parser.y"
    {fprintf(rulesFile, "statements -> statements stmt\n");}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 71 "parser.y"
    {fprintf(rulesFile, "stmt -> expr SEMICOLON\n");}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 72 "parser.y"
    {fprintf(rulesFile, "stmt -> ifstmt\n");}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 73 "parser.y"
    {fprintf(rulesFile, "stmt -> whilestmt\n");}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 74 "parser.y"
    {fprintf(rulesFile, "stmt -> forstmt\n");}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 75 "parser.y"
    {fprintf(rulesFile, "stmt -> returnstmt\n");}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 76 "parser.y"
    {fprintf(rulesFile, "stmt -> BREAK SEMICOLON\n");}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 77 "parser.y"
    {fprintf(rulesFile, "stmt -> CONTINUE SEMICOLON\n");}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 78 "parser.y"
    {fprintf(rulesFile, "stmt -> block\n");}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 79 "parser.y"
    {fprintf(rulesFile, "stmt -> funcdef\n");}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 80 "parser.y"
    {fprintf(rulesFile, "stmt -> SEMICOLON\n");}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    {fprintf(rulesFile, "expr -> assignment\n");}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 84 "parser.y"
    {fprintf(rulesFile, "expr -> expr ADD expr\n");}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 85 "parser.y"
    {fprintf(rulesFile, "expr -> expr SUB expr\n");}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    {fprintf(rulesFile, "expr -> expr MUL expr\n");}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 87 "parser.y"
    {fprintf(rulesFile, "expr -> expr DIV expr\n");}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 88 "parser.y"
    {fprintf(rulesFile, "expr -> expr MODULO expr\n");}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 89 "parser.y"
    {fprintf(rulesFile, "expr -> expr GREATER expr\n");}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 90 "parser.y"
    {fprintf(rulesFile, "expr -> expr GREATER_EQUAL expr\n");}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    {fprintf(rulesFile, "expr -> expr LESSER expr\n");}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 92 "parser.y"
    {fprintf(rulesFile, "expr -> expr LESSER_EQUAL expr\n");}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    {fprintf(rulesFile, "expr -> expr EQUAL expr\n");}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 94 "parser.y"
    {fprintf(rulesFile, "expr -> expr NOT_EQUAL expr\n");}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 95 "parser.y"
    {fprintf(rulesFile, "expr -> expr AND expr\n");}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    {fprintf(rulesFile, "expr -> expr OR expr\n");}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    {fprintf(rulesFile, "expr -> term\n");}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 100 "parser.y"
    {fprintf(rulesFile, "term -> LPAREN expr RPAREN\n");}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 101 "parser.y"
    {fprintf(rulesFile, "term -> SUB expr\n");}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 102 "parser.y"
    {fprintf(rulesFile, "term -> NOT expr\n");}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 103 "parser.y"
    {if((yyvsp[(2) - (2)].exprNode)->uniontype == function) print_error("error, function id used as lvalue"); fprintf(rulesFile, "term -> PLUS_PLUS lvalue\n");}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    {if((yyvsp[(1) - (1)].exprNode)->uniontype == function) print_error("error, function id used as lvalue");}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    {fprintf(rulesFile, "term -> lvalue PLUS_PLUS\n");}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    {if((yyvsp[(2) - (2)].exprNode)->uniontype == function) print_error("error, function id used as lvalue");fprintf(rulesFile, "term -> MINUS_MINUS lvalue\n");}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    {if((yyvsp[(1) - (1)].exprNode)->uniontype == function) print_error("error, function id used as lvalue");}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    {fprintf(rulesFile, "term -> lvalue MINUS_MINUS\n");}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    {fprintf(rulesFile, "term -> primary\n");}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    {if((yyvsp[(1) - (1)].exprNode)->uniontype == function) print_error("error, function id used as lvalue");}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    {fprintf(rulesFile, "assignment -> lvalue ASSIGN expr\n");}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    {fprintf(rulesFile, "primary -> lvalue\n");}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    {fprintf(rulesFile, "primary -> call\n");}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {fprintf(rulesFile, "primary -> objectdef\n");}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    {fprintf(rulesFile, "primary -> LPAREN funcdef RPAREN\n");}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 117 "parser.y"
    {fprintf(rulesFile, "primary -> const\n");}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    { 
                if(!symTab_lookup((yyvsp[(1) - (1)].stringValue))) {
                  symTab_insert((yyvsp[(1) - (1)].stringValue), alpha_yylineno, variable, local);
                  (yyval.exprNode) = symTab_lookup((yyvsp[(1) - (1)].stringValue), get_current_scope());
                }
                else{
                  (yyval.exprNode) = symTab_lookup((yyvsp[(1) - (1)].stringValue), get_current_scope());
                }
                 fprintf(rulesFile, "lvalue -> ID\n");
			        }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    {
                if(!symTab_lookup((yyvsp[(2) - (2)].stringValue), get_current_scope())){
                  if(!is_libfunc((yyvsp[(2) - (2)].stringValue))){
                    symTab_insert((yyvsp[(2) - (2)].stringValue), alpha_yylineno, variable, local);
                    (yyval.exprNode) = symTab_lookup((yyvsp[(2) - (2)].stringValue), get_current_scope());
                  }
                  else
                    print_error("error, cannot overide library functions:");
                }
                else {
                  (yyval.exprNode) = symTab_lookup((yyvsp[(2) - (2)].stringValue), get_current_scope());
                }
                fprintf(rulesFile, "lvalue -> LOCAL ID\n");
              }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    {
                if(!symTab_lookup((yyvsp[(2) - (2)].stringValue),0)) {
                  print_error("error, could not find global identifier:");
                }
                else{
                  (yyval.exprNode) = symTab_lookup((yyvsp[(2) - (2)].stringValue), 0);
                }
                fprintf(rulesFile, "lvalue -> DCOLON ID\n");
              }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    {fprintf(rulesFile, "lvalue -> member\n");}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    {fprintf(rulesFile, "member -> lvalue PERIOD ID\n");}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    {fprintf(rulesFile, "member -> lvalue LSQUARE expr RSQUARE\n");}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {fprintf(rulesFile, "member -> call PERIOD ID\n");}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    {fprintf(rulesFile, "member -> call LSQUARE expr RSQUARE\n");}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    {fprintf(rulesFile, "call -> call LPAREN elist RPAREN\n");}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {fprintf(rulesFile, "call -> lvalue callsuffix\n");}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    {fprintf(rulesFile, "call -> LPAREN funcdef RPAREN LPAREN elist RPAREN\n");}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    {fprintf(rulesFile, "callsuffix -> normcall\n");}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    {fprintf(rulesFile, "callsuffix -> methodcall\n");}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    {fprintf(rulesFile, "normcall -> LPAREN elist RPAREN\n");}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    {fprintf(rulesFile, "methodcall -> DPERIOD ID LPAREN elist RPAREN\n");}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    {fprintf(rulesFile, "elist -> expr\n");}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    {fprintf(rulesFile, "elist -> elist COMMA expr\n");}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    {fprintf(rulesFile, "elist -> \n");}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    {fprintf(rulesFile, "objectdef -> LSQUARE elist RSQUARE\n");}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {fprintf(rulesFile, "objectdef -> LSQUARE indexed RSQUARE\n");}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    {fprintf(rulesFile, "indexed -> indexedelem\n");}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    {fprintf(rulesFile, "indexed -> indexed COMMA indexedelem\n");}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    {fprintf(rulesFile, "indexedelem -> LCURLY expr COLON expr RCURLY\n");}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    {increase_scope();}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    {symTab_hide();decrease_scope(); fprintf(rulesFile, "block -> LCURLY statements RCURLY\n");}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {
              if(!symTab_lookup((yyvsp[(2) - (2)].stringValue), get_current_scope())) {
                if(is_libfunc((yyvsp[(2) - (2)].stringValue))) print_error("error, cannot override library functions:");
                else symTab_insert((yyvsp[(2) - (2)].stringValue), alpha_yylineno, function, userfunc);
              }
				      else print_error("error, redefinition of identifier:");
			        }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    {increase_scope(); isFormal = true; }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    {decrease_scope(); isFormal = false;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    {fprintf(rulesFile, "funcdef -> FUNCTION ID LPAREN idlist RPAREN block\n");}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    { symTab_insert(make_anonymous_func(), alpha_yylineno, function, userfunc); }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    {increase_scope(); isFormal = true; }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    {decrease_scope(); isFormal = true; }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    {fprintf(rulesFile, "funcdef -> FUNCTION LPAREN idlist RPAREN block\n");}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    {fprintf(rulesFile, "const -> INTEGER\n");}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    {fprintf(rulesFile, "const -> REAL\n");}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    {fprintf(rulesFile, "const -> STRING\n");}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    {fprintf(rulesFile, "const -> NIL\n");}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    {fprintf(rulesFile, "const -> TRUE\n");}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    {fprintf(rulesFile, "const -> FALSE\n");}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    {
                if(isFormal){
                  if(symTab_lookup((yyvsp[(1) - (1)].stringValue), get_current_scope())) {
                    print_error("error, redifinition of formal argument:");
                  }
                  else if (is_libfunc((yyvsp[(1) - (1)].stringValue))){
                    print_error("error, cannot override library functions:");
                  }
                  else {
                    symTab_insert((yyvsp[(1) - (1)].stringValue), alpha_yylineno, variable, formal);
                  }
                }
                else if(!symTab_lookup((yyvsp[(1) - (1)].stringValue), get_current_scope())) {
                  symTab_insert((yyvsp[(1) - (1)].stringValue), alpha_yylineno, variable, local);
                }
                {fprintf(rulesFile, "idlist -> ID\n");}
              }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    {
                if(isFormal){
                  if(symTab_lookup((yyvsp[(3) - (3)].stringValue), get_current_scope())){
                    print_error("error, redifinition of formal argument:");
                  }
                  else if (is_libfunc((yyvsp[(3) - (3)].stringValue))){
                    print_error("error, cannot override library functions:");
                  }
                  else {
                    symTab_insert((yyvsp[(3) - (3)].stringValue), alpha_yylineno, variable, formal);
                  }
                }
                else if(!symTab_lookup((yyvsp[(3) - (3)].stringValue), get_current_scope())){
                  symTab_insert((yyvsp[(3) - (3)].stringValue), alpha_yylineno, variable, local);
                }
                {fprintf(rulesFile, "idlist -> idlist COMMA ID\n");}
			        }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    {fprintf(rulesFile, "idlist -> \n");}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt ELSE stmt\n");}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt\n");}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 255 "parser.y"
    {fprintf(rulesFile, "whilestmt -> WHILE LPAREN expr RPAREN stmt\n");}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {fprintf(rulesFile, "forstmt -> FOR LPAREN elist SEMICOLON expr SEMICOLON elist RPAREN stmt\n");}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 261 "parser.y"
    {fprintf(rulesFile, "returnstmt -> RETURN expr SEMICOLON\n");}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 262 "parser.y"
    {fprintf(rulesFile, "returnstmt -> RETURN SEMICOLON\n");}
    break;



/* Line 1455 of yacc.c  */
#line 2408 "parser.cpp"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 265 "parser.y"


int alpha_yyerror(const char* yaccProvidedMessage) {
	fprintf(stderr, "\033[1;31m%s: '%s' in line: %d\033[0m\n",yaccProvidedMessage, alpha_yytext, alpha_yylineno);
	return 0;
}

void print_error(const char* msg) { printf("\033[1;31m%s '%s' in line: %d\033[0m\n", msg, alpha_yytext, alpha_yylineno); }

bool is_libfunc(char* id) {
	if(!strcmp(id,"print")) return true;
	if(!strcmp(id,"input")) return true;
	if(!strcmp(id,"objectmemberkeys")) return true;
	if(!strcmp(id,"objectotalmember")) return true;
	if(!strcmp(id,"objectcopy")) return true;
	if(!strcmp(id,"totalarguments"))return true;
	if(!strcmp(id,"argument")) return true;
	if(!strcmp(id,"typeof")) return true;
	if(!strcmp(id,"strtonum")) return true;
	if(!strcmp(id,"sqrt")) return true;
	if(!strcmp(id,"cos")) return true;
	if(!strcmp(id,"sin")) return true;
	return false;
}

char* make_anonymous_func() {

	char* func = (char*)"_anonymousFunc";
	int  length = strlen(func) + snprintf(NULL, 0, "%d", anonymousCounter) + 1;
	char* result = (char*)malloc(length);

	if(result) {
		sprintf(result, "%s%d", func, anonymousCounter++); 
		return result;
	}
	else {
		printf("Out of memmory\n"); 
		exit(EXIT_FAILURE);
	}

}

int main(int argc, char** argv) {
	if(!(alpha_yyin = fopen(argv[1], "r"))){
    printf("Could not open file\n");
    return 1;
  }
	init_library_func();
  yyparse();
  fprintf(rulesFile, "EOF\n");
  fclose(rulesFile);
  return 0;
}
