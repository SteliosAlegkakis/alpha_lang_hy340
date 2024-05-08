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


/* Substitute the variable and function names.  */
#define yyparse         alpha_yyparse
#define yylex           alpha_yylex
#define yyerror         alpha_yyerror
#define yydebug         alpha_yydebug
#define yynerrs         alpha_yynerrs
#define yylval          alpha_yylval
#define yychar          alpha_yychar

/* First part of user prologue.  */
#line 1 "parser.y"

#include "./parser_lib/parser_lib.hpp"

#line 81 "parser.cpp"

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
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 10 "parser.y"

  char* stringValue;
  int intValue;
  unsigned int uintValue;
  double realValue;
  struct SymtabEntry* symbol;
  struct expr* expr;
  struct call* call;
  struct stmt_t* stmt_stmt;

#line 240 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE alpha_yylval;

int alpha_yyparse (void);

#endif /* !YY_ALPHA_YY_PARSER_HPP_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   617

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    62,    63,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      95,    96,    97,    98,    99,   100,   101,   102,   105,   108,
     109,   110,   111,   112,   115,   116,   117,   118,   121,   122,
     123,   124,   127,   128,   129,   132,   133,   136,   139,   142,
     143,   144,   147,   148,   151,   152,   155,   158,   158,   161,
     162,   165,   168,   171,   174,   177,   178,   179,   180,   181,
     182,   185,   186,   187,   190,   191,   194,   196,   198,   201,
     201,   204,   204,   207,   208
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "PLUS_PLUS",
  "MINUS_MINUS", "MODULO", "EQUAL", "NOT_EQUAL", "GREATER", "LESSER",
  "LESSER_EQUAL", "GREATER_EQUAL", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
  "LSQUARE", "RSQUARE", "COLON", "SEMICOLON", "DCOLON", "COMMA", "PERIOD",
  "DPERIOD", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "AND",
  "NOT", "OR", "LOCAL", "ASSIGN", "NIL", "TRUE", "FALSE", "STRING", "ID",
  "INTEGER", "REAL", "BREAK", "CONTINUE", "UMINUS", "$accept", "program",
  "statements", "stmt", "expr", "term", "assignment", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "indexed", "indexedelem", "block", "$@1", "funcname",
  "funcprefix", "funcargs", "funcbody", "funcdef", "const", "idlist",
  "ifstmt", "loopstart", "loopend", "loopstmt", "whilestmt", "$@2",
  "forstmt", "$@3", "returnstmt", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF (-143)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -143,     4,   190,  -143,   248,   -13,   -13,     2,  -143,    79,
    -143,   -31,     1,     3,    12,   -12,   234,   248,    -5,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,    56,    59,  -143,   122,
    -143,  -143,  -143,   559,  -143,     7,  -143,  -143,    73,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,    58,     9,     7,     9,
     291,    74,  -143,   248,   306,    71,    75,    81,  -143,   248,
     248,   248,  -143,  -143,  -143,   340,  -143,  -143,  -143,  -143,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,  -143,   248,   248,  -143,  -143,   248,   248,    55,    64,
     248,  -143,  -143,  -143,   248,   248,    65,    66,    86,    93,
    -143,    97,   146,   355,   248,  -143,  -143,    94,   389,   404,
      92,  -143,    96,    96,  -143,  -143,  -143,    50,    50,   602,
     602,   602,   602,   589,   550,   100,   438,  -143,   113,   537,
     123,   452,  -143,  -143,    -9,  -143,  -143,    97,   248,  -143,
     248,  -143,  -143,   190,  -143,   248,  -143,  -143,   248,  -143,
    -143,  -143,    87,   125,   486,   110,  -143,   503,   127,  -143,
    -143,  -143,   190,   190,  -143,   248,  -143,  -143,  -143,   129,
    -143,  -143,  -143,  -143
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,    67,    61,
      14,     0,     0,     0,     0,    70,     0,     0,     0,    78,
      79,    80,    77,    44,    75,    76,     0,     0,     3,     0,
      29,    15,    37,    39,    47,    40,    41,    12,     0,    13,
      43,     6,     7,     8,     9,    31,     0,    33,     0,    35,
       0,     0,     4,     0,    59,     0,     0,    64,    46,     0,
       0,    61,    69,    71,    94,     0,    32,    45,    10,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     0,     0,    34,    36,    61,     0,     0,     0,
       0,    53,    55,    56,    61,     0,     0,    83,     0,     0,
      30,    42,     0,     0,    61,    62,    63,     0,     0,     0,
       0,    93,    16,    17,    18,    19,    20,    25,    26,    21,
      23,    24,    22,    27,    28,     0,     0,    48,     0,    38,
       0,     0,    50,    81,     0,    73,    74,     0,    61,    68,
       0,    60,    65,     0,    89,     0,    57,    49,    61,    52,
      51,    72,     0,     0,     0,    85,    86,     0,     0,    82,
      54,    66,     0,     0,    90,    61,    58,    84,    87,     0,
      88,    91,    86,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,    95,  -142,    -2,  -143,  -143,  -143,    43,  -143,
      61,  -143,  -143,  -143,   -54,  -143,    41,  -143,    51,  -143,
    -143,  -143,  -143,  -143,     6,  -143,  -143,  -143,  -143,  -143,
     -21,  -143,  -143,  -143,  -143,  -143
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    54,    30,    31,    32,    33,    34,
      35,    91,    92,    93,    55,    36,    56,    57,    37,    52,
      63,    38,    98,   136,    39,    40,   134,    41,   163,   170,
     164,    42,   156,    43,   172,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   155,    45,    46,     3,    50,     4,   110,   151,     5,
       6,    11,    58,    51,    65,    66,   152,    59,     7,    60,
     167,   168,     9,    94,    18,    86,    11,    95,    61,    87,
      23,    62,   125,    96,    15,    88,    89,    17,    67,    18,
     130,    19,    20,    21,    22,    23,    24,    25,    47,    49,
     141,   103,    99,    70,    71,    72,    73,   108,   109,    74,
      -1,    -1,    77,    78,    79,    80,    48,    48,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    68,
     123,   124,    69,     4,   153,   126,     5,     6,   129,    97,
      15,   101,   105,   131,   158,     7,   106,    53,   127,     9,
      29,    72,    73,    11,     8,    74,   107,   128,   132,   133,
     137,   169,    53,   138,    17,   145,    18,   146,    19,    20,
      21,    22,    23,    24,    25,    70,    71,    72,    73,   148,
     159,    74,    75,    76,    77,    78,    79,    80,   154,   162,
     149,    29,   160,   157,   166,    81,   171,   102,   142,   135,
       4,   173,     0,     5,     6,     0,    82,     0,    83,     0,
      29,    29,     7,     0,     8,   139,     9,     0,     0,    10,
      11,     0,     0,     0,    12,     0,    13,    14,    15,    16,
       0,    17,     0,    18,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,     4,     0,     0,     5,     6,     0,
       0,     0,     0,     0,     0,     0,     7,     0,     8,     0,
       9,     0,     0,    10,    11,     0,     0,     0,    12,     0,
      13,    14,    15,    16,     0,    17,     0,    18,     0,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     4,     0,
       0,     5,     6,     0,     0,     0,     0,     0,     0,     0,
       7,     0,     4,     0,     9,     5,     6,    64,    11,     0,
       0,     0,     0,     0,     7,     0,     0,     0,     9,    17,
       0,    18,    11,    19,    20,    21,    22,    23,    24,    25,
       0,     0,     0,    17,     0,    18,     0,    19,    20,    21,
      22,    23,    24,    25,    70,    71,    72,    73,     0,     0,
      74,    75,    76,    77,    78,    79,    80,     0,   100,    70,
      71,    72,    73,     0,     0,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,    82,     0,    83,     0,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,    70,    71,    72,    73,     0,     0,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    70,    71,
      72,    73,     0,   111,    74,    75,    76,    77,    78,    79,
      80,     0,     0,     0,    82,     0,    83,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    70,    71,    72,    73,     0,     0,    74,    75,
      76,    77,    78,    79,    80,     0,   143,    70,    71,    72,
      73,     0,     0,    74,    75,    76,    77,    78,    79,    80,
       0,   144,     0,    82,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
      83,    70,    71,    72,    73,     0,     0,    74,    75,    76,
      77,    78,    79,    80,     0,    70,    71,    72,    73,   147,
       0,    74,    75,    76,    77,    78,    79,    80,     0,     0,
       0,     0,    82,   150,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,    83,    70,
      71,    72,    73,     0,     0,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,   161,    70,    71,    72,    73,
       0,     0,    74,    75,    76,    77,    78,    79,    80,     0,
      82,     0,    83,     0,     0,     0,   165,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,    83,
      70,    71,    72,    73,     0,     0,    74,    75,    76,    77,
      78,    79,    80,    70,    71,    72,    73,     0,     0,    74,
      75,    76,    77,    78,    79,    80,    84,    85,     0,     0,
       0,    82,     0,    83,     0,    86,     0,     0,     0,    87,
       0,     0,     0,     0,    82,    88,    89,     0,     0,     0,
       0,     0,    70,    71,    72,    73,     0,    90,    74,    75,
      76,    77,    78,    79,    80,    70,    71,    72,    73,     0,
       0,    74,     0,     0,    -1,    -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
       2,   143,     4,    16,     0,     7,     4,    61,    17,     7,
       8,    24,    43,     7,    16,    17,    25,    16,    16,    16,
     162,   163,    20,    16,    37,    16,    24,    20,    16,    20,
      43,    43,    86,    26,    32,    26,    27,    35,    43,    37,
      94,    39,    40,    41,    42,    43,    44,    45,     5,     6,
     104,    53,    46,     3,     4,     5,     6,    59,    60,     9,
      10,    11,    12,    13,    14,    15,     5,     6,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    23,
      82,    83,    23,     4,   138,    87,     7,     8,    90,    16,
      32,    17,    21,    95,   148,    16,    21,    18,    43,    20,
     102,     5,     6,    24,    18,     9,    25,    43,    43,    43,
      17,   165,    18,    16,    35,    23,    37,    17,    39,    40,
      41,    42,    43,    44,    45,     3,     4,     5,     6,    16,
      43,     9,    10,    11,    12,    13,    14,    15,   140,    29,
      17,   143,    17,   145,    17,    23,    17,    52,   107,    98,
       4,   172,    -1,     7,     8,    -1,    34,    -1,    36,    -1,
     162,   163,    16,    -1,    18,    19,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      -1,    35,    -1,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     4,    -1,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    -1,    35,    -1,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     4,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    -1,     4,    -1,    20,     7,     8,    23,    24,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,    35,
      -1,    37,    24,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    35,    -1,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,     3,     4,     5,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,     3,
       4,     5,     6,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    36,     3,     4,     5,     6,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,     3,     4,
       5,     6,    -1,    23,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    34,    -1,    36,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,     3,     4,     5,     6,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    -1,    34,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      36,     3,     4,     5,     6,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    -1,     3,     4,     5,     6,    21,
      -1,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    34,    21,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    36,     3,
       4,     5,     6,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    19,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    -1,
      34,    -1,    36,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    36,
       3,     4,     5,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,     3,     4,     5,     6,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,     7,     8,    -1,    -1,
      -1,    34,    -1,    36,    -1,    16,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    34,    26,    27,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,    38,     9,    10,
      11,    12,    13,    14,    15,     3,     4,     5,     6,    -1,
      -1,     9,    -1,    -1,    12,    13,    14,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,     4,     7,     8,    16,    18,    20,
      23,    24,    28,    30,    31,    32,    33,    35,    37,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    52,    53,
      54,    55,    56,    57,    58,    59,    64,    67,    70,    73,
      74,    76,    80,    82,    84,    53,    16,    57,    59,    57,
      53,    73,    68,    18,    53,    63,    65,    66,    43,    16,
      16,    16,    43,    69,    23,    53,    53,    43,    23,    23,
       3,     4,     5,     6,     9,    10,    11,    12,    13,    14,
      15,    23,    34,    36,     7,     8,    16,    20,    26,    27,
      38,    60,    61,    62,    16,    20,    26,    16,    71,    73,
      17,    17,    51,    53,    25,    21,    21,    25,    53,    53,
      63,    23,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    63,    53,    43,    43,    53,
      63,    53,    43,    43,    75,    67,    72,    17,    16,    19,
      22,    63,    65,    17,    17,    23,    17,    21,    16,    17,
      21,    17,    25,    63,    53,    52,    81,    53,    63,    43,
      17,    19,    29,    77,    79,    23,    17,    52,    52,    63,
      78,    17,    83,    79
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    60,    60,    61,    62,    63,
      63,    63,    64,    64,    65,    65,    66,    68,    67,    69,
      69,    70,    71,    72,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    75,    76,    76,    77,    78,    79,    81,
      80,    83,    82,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     1,
       3,     0,     3,     3,     1,     3,     5,     0,     4,     1,
       0,     2,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     7,     5,     0,     0,     3,     0,
       6,     0,    10,     3,     2
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
#line 59 "parser.y"
                         {fprintf(rulesFile, "program -> statements\n");}
#line 1628 "parser.cpp"
    break;

  case 3:
#line 62 "parser.y"
                              {(yyval.stmt_stmt) =  manage_statements((yyvsp[-1].stmt_stmt), (yyvsp[0].stmt_stmt)); fprintf(rulesFile, "statements -> statements stmt\n");}
#line 1634 "parser.cpp"
    break;

  case 5:
#line 66 "parser.y"
                                  {(yyval.stmt_stmt) = (stmt_t*) 0; fprintf(rulesFile, "stmt -> expr SEMICOLON\n");}
#line 1640 "parser.cpp"
    break;

  case 6:
#line 67 "parser.y"
                                  {(yyval.stmt_stmt) = (yyvsp[0].stmt_stmt); fprintf(rulesFile, "stmt -> ifstmt\n");}
#line 1646 "parser.cpp"
    break;

  case 7:
#line 68 "parser.y"
                                  {(yyval.stmt_stmt) = (stmt_t*) 0; fprintf(rulesFile, "stmt -> whilestmt\n");}
#line 1652 "parser.cpp"
    break;

  case 8:
#line 69 "parser.y"
                                  {(yyval.stmt_stmt) = (stmt_t*) 0; fprintf(rulesFile, "stmt -> forstmt\n");}
#line 1658 "parser.cpp"
    break;

  case 9:
#line 70 "parser.y"
                                  {(yyval.stmt_stmt) = (stmt_t*) 0; fprintf(rulesFile, "stmt -> returnstmt\n");}
#line 1664 "parser.cpp"
    break;

  case 10:
#line 71 "parser.y"
                                  {(yyval.stmt_stmt) = (yyvsp[-1].stmt_stmt);  manage_break(); fprintf(rulesFile, "stmt -> BREAK SEMICOLON\n");}
#line 1670 "parser.cpp"
    break;

  case 11:
#line 72 "parser.y"
                                  {(yyval.stmt_stmt) = (yyvsp[-1].stmt_stmt);  manage_continue(); fprintf(rulesFile, "stmt -> CONTINUE SEMICOLON\n");}
#line 1676 "parser.cpp"
    break;

  case 12:
#line 73 "parser.y"
                                  {(yyval.stmt_stmt) = (yyvsp[0].stmt_stmt); fprintf(rulesFile, "stmt -> block\n");}
#line 1682 "parser.cpp"
    break;

  case 13:
#line 74 "parser.y"
                                  {(yyval.stmt_stmt) = (stmt_t*) 0; fprintf(rulesFile, "stmt -> funcdef\n");}
#line 1688 "parser.cpp"
    break;

  case 14:
#line 75 "parser.y"
                                  {(yyval.stmt_stmt) = (stmt_t*) 0; fprintf(rulesFile, "stmt -> SEMICOLON\n");}
#line 1694 "parser.cpp"
    break;

  case 15:
#line 78 "parser.y"
                                       {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "expr -> assignment\n");}
#line 1700 "parser.cpp"
    break;

  case 16:
#line 79 "parser.y"
                                       {(yyval.expr) = manage_arithmetic_operation(_add, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr ADD expr\n");}
#line 1706 "parser.cpp"
    break;

  case 17:
#line 80 "parser.y"
                                       {(yyval.expr) = manage_arithmetic_operation(_sub, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr SUB expr\n");}
#line 1712 "parser.cpp"
    break;

  case 18:
#line 81 "parser.y"
                                       {(yyval.expr) = manage_arithmetic_operation(_mul, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr MUL expr\n");}
#line 1718 "parser.cpp"
    break;

  case 19:
#line 82 "parser.y"
                                       {(yyval.expr) = manage_arithmetic_operation(_div, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr DIV expr\n");}
#line 1724 "parser.cpp"
    break;

  case 20:
#line 83 "parser.y"
                                       {(yyval.expr) = manage_arithmetic_operation(_mod, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr MODULO expr\n");}
#line 1730 "parser.cpp"
    break;

  case 21:
#line 84 "parser.y"
                                       {(yyval.expr) = manage_relative_operation(_if_greater, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr GREATER expr\n");}
#line 1736 "parser.cpp"
    break;

  case 22:
#line 85 "parser.y"
                                       {(yyval.expr) = manage_relative_operation(_if_greatereq, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr GREATER_EQUAL expr\n");}
#line 1742 "parser.cpp"
    break;

  case 23:
#line 86 "parser.y"
                                       {(yyval.expr) = manage_relative_operation(_if_less, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr LESSER expr\n");}
#line 1748 "parser.cpp"
    break;

  case 24:
#line 87 "parser.y"
                                       {(yyval.expr) = manage_relative_operation(_if_lesseq, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr LESSER_EQUAL expr\n");}
#line 1754 "parser.cpp"
    break;

  case 25:
#line 88 "parser.y"
                                       {(yyval.expr) = manage_relative_operation(_if_eq, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr EQUAL expr\n");}
#line 1760 "parser.cpp"
    break;

  case 26:
#line 89 "parser.y"
                                       {(yyval.expr) = manage_relative_operation(_if_noteq, (yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "expr -> expr NOT_EQUAL expr\n");}
#line 1766 "parser.cpp"
    break;

  case 27:
#line 90 "parser.y"
                                       {(yyval.expr) = manage_bool_operation(_and, (yyvsp[-2].expr), (yyvsp[0].expr));fprintf(rulesFile, "expr -> expr AND expr\n");}
#line 1772 "parser.cpp"
    break;

  case 28:
#line 91 "parser.y"
                                       {(yyval.expr) = manage_bool_operation(_or, (yyvsp[-2].expr), (yyvsp[0].expr));fprintf(rulesFile, "expr -> expr OR expr\n");}
#line 1778 "parser.cpp"
    break;

  case 29:
#line 92 "parser.y"
                                       {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "expr -> term\n");}
#line 1784 "parser.cpp"
    break;

  case 30:
#line 95 "parser.y"
                                     {(yyval.expr) = (yyvsp[-1].expr); fprintf(rulesFile,"term -> LPAREN expr RPAREN\n");}
#line 1790 "parser.cpp"
    break;

  case 31:
#line 96 "parser.y"
                                     {(yyval.expr) = manage_uminus_expr((yyvsp[0].expr)); fprintf(rulesFile,"term -> SUB expr\n");}
#line 1796 "parser.cpp"
    break;

  case 32:
#line 97 "parser.y"
                                     {(yyval.expr) = manage_not_expr((yyvsp[0].expr)); fprintf(rulesFile,"term -> NOT expr\n");}
#line 1802 "parser.cpp"
    break;

  case 33:
#line 98 "parser.y"
                                     {(yyval.expr) = manage_plusplus_lvalue((yyvsp[0].expr)); fprintf(rulesFile,"term -> PLUS_PLUS lvalue\n");}
#line 1808 "parser.cpp"
    break;

  case 34:
#line 99 "parser.y"
                                     {(yyval.expr) = manage_lvalue_plusplus((yyvsp[-1].expr)); fprintf(rulesFile,"term -> lvalue PLUS_PLUS\n");}
#line 1814 "parser.cpp"
    break;

  case 35:
#line 100 "parser.y"
                                     {(yyval.expr) = manage_minusminus_lvalue((yyvsp[0].expr)); fprintf(rulesFile,"term -> MINUS_MINUS lvalue\n");}
#line 1820 "parser.cpp"
    break;

  case 36:
#line 101 "parser.y"
                                     {(yyval.expr) = manage_lvalue_minusminus((yyvsp[-1].expr)); fprintf(rulesFile,"term -> lvalue MINUS_MINUS\n");}
#line 1826 "parser.cpp"
    break;

  case 37:
#line 102 "parser.y"
                                     {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "term -> primary\n");}
#line 1832 "parser.cpp"
    break;

  case 38:
#line 105 "parser.y"
                                 { (yyval.expr) = manage_assignment((yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile,"assignment -> lvalue ASSIGN expr\n");}
#line 1838 "parser.cpp"
    break;

  case 39:
#line 108 "parser.y"
                                      {(yyval.expr) = emit_if_table_item((yyvsp[0].expr)); fprintf(rulesFile, "primary -> lvalue\n");}
#line 1844 "parser.cpp"
    break;

  case 40:
#line 109 "parser.y"
                                      {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "primary -> call\n");}
#line 1850 "parser.cpp"
    break;

  case 41:
#line 110 "parser.y"
                                      {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "primary -> objectdef\n");}
#line 1856 "parser.cpp"
    break;

  case 42:
#line 111 "parser.y"
                                      {(yyval.expr) = manage_primary_funcdef((yyvsp[-1].symbol)); fprintf(rulesFile, "primary -> LPAREN funcdef RPAREN\n");}
#line 1862 "parser.cpp"
    break;

  case 43:
#line 112 "parser.y"
                                      {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "primary -> const\n");}
#line 1868 "parser.cpp"
    break;

  case 44:
#line 115 "parser.y"
                          {(yyval.expr) = manage_lvalue_id((yyvsp[0].stringValue)); fprintf(rulesFile, "lvalue -> ID\n");}
#line 1874 "parser.cpp"
    break;

  case 45:
#line 116 "parser.y"
                          {(yyval.expr) = manage_lvalue_local_id((yyvsp[0].stringValue)); fprintf(rulesFile,"lvalue -> LOCAL ID\n");}
#line 1880 "parser.cpp"
    break;

  case 46:
#line 117 "parser.y"
                          {(yyval.expr) = manage_lvalue_global_id((yyvsp[0].stringValue)); fprintf(rulesFile,"lvalue -> DCOLON ID\n");}
#line 1886 "parser.cpp"
    break;

  case 47:
#line 118 "parser.y"
                          {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile,"lvalue -> member\n");}
#line 1892 "parser.cpp"
    break;

  case 48:
#line 121 "parser.y"
                                           {(yyval.expr) = member_item((yyvsp[-2].expr), (yyvsp[0].stringValue)); fprintf(rulesFile, "member -> lvalue PERIOD ID\n");}
#line 1898 "parser.cpp"
    break;

  case 49:
#line 122 "parser.y"
                                           {(yyval.expr) = manage_member_item_lvalue_lsquare_expr_rsquare((yyvsp[-3].expr), (yyvsp[-1].expr)); fprintf(rulesFile, "member -> lvalue LSQUARE expr RSQUARE\n");}
#line 1904 "parser.cpp"
    break;

  case 50:
#line 123 "parser.y"
                                           {(yyval.expr) = member_item((yyvsp[-2].expr), (yyvsp[0].stringValue)); fprintf(rulesFile, "member -> call PERIOD ID\n");}
#line 1910 "parser.cpp"
    break;

  case 51:
#line 124 "parser.y"
                                           {(yyval.expr) = manage_member_item_lvalue_lsquare_expr_rsquare((yyvsp[-3].expr), (yyvsp[-1].expr)); fprintf(rulesFile, "member -> call LSQUARE expr RSQUARE\n");}
#line 1916 "parser.cpp"
    break;

  case 52:
#line 127 "parser.y"
                                                         {(yyval.expr) = make_call((yyvsp[-3].expr), (yyvsp[-1].expr)); fprintf(rulesFile, "call -> call LPAREN elist RPAREN\n");}
#line 1922 "parser.cpp"
    break;

  case 53:
#line 128 "parser.y"
                                                         {(yyval.expr) = manage_call_lvalue_callsuffix((yyvsp[-1].expr), (yyvsp[0].call)); fprintf(rulesFile, "call -> lvalue callsuffix\n");}
#line 1928 "parser.cpp"
    break;

  case 54:
#line 129 "parser.y"
                                                         {(yyval.expr) = manage_call_funcdef((yyvsp[-4].symbol) ,(yyvsp[-1].expr)); fprintf(rulesFile, "call -> LPAREN funcdef RPAREN LPAREN elist RPAREN\n");}
#line 1934 "parser.cpp"
    break;

  case 55:
#line 132 "parser.y"
                          {(yyval.call) = (yyvsp[0].call); fprintf(rulesFile, "callsuffix -> normcall\n");}
#line 1940 "parser.cpp"
    break;

  case 56:
#line 133 "parser.y"
                          {(yyval.call) = (yyvsp[0].call); fprintf(rulesFile, "callsuffix -> methodcall\n");}
#line 1946 "parser.cpp"
    break;

  case 57:
#line 136 "parser.y"
                                  {(yyval.call) = manage_normcall((yyvsp[-1].expr)); fprintf(rulesFile, "normcall -> LPAREN elist RPAREN\n");}
#line 1952 "parser.cpp"
    break;

  case 58:
#line 139 "parser.y"
                                             {(yyval.call) = manage_methodcall((yyvsp[-1].expr), (yyvsp[-3].stringValue)); fprintf(rulesFile, "methodcall -> DPERIOD ID LPAREN elist RPAREN\n");}
#line 1958 "parser.cpp"
    break;

  case 59:
#line 142 "parser.y"
                                {(yyval.expr) = (yyvsp[0].expr); (yyval.expr)->next = NULL; fprintf(rulesFile, "elist -> expr\n");}
#line 1964 "parser.cpp"
    break;

  case 60:
#line 143 "parser.y"
                                {(yyval.expr) = manage_elist((yyvsp[-2].expr),(yyvsp[0].expr)); fprintf(rulesFile, "elist -> elist COMMA expr\n");}
#line 1970 "parser.cpp"
    break;

  case 61:
#line 144 "parser.y"
                                {(yyval.expr) = (expr*) 0; fprintf(rulesFile, "elist -> \n");}
#line 1976 "parser.cpp"
    break;

  case 62:
#line 147 "parser.y"
                                       {(yyval.expr) = manage_objectdef_elist((yyvsp[-1].expr)); fprintf(rulesFile, "objectdef -> LSQUARE elist RSQUARE\n");}
#line 1982 "parser.cpp"
    break;

  case 63:
#line 148 "parser.y"
                                       {(yyval.expr) = manage_objectdef_indexed((yyvsp[-1].expr)); fprintf(rulesFile, "objectdef -> LSQUARE indexed RSQUARE\n");}
#line 1988 "parser.cpp"
    break;

  case 64:
#line 151 "parser.y"
                                          {(yyval.expr) = (yyvsp[0].expr); fprintf(rulesFile, "indexed -> indexedelem\n");}
#line 1994 "parser.cpp"
    break;

  case 65:
#line 152 "parser.y"
                                          {(yyval.expr) = manage_indexed((yyvsp[-2].expr), (yyvsp[0].expr)); fprintf(rulesFile, "indexed -> indexed COMMA indexedelem\n");}
#line 2000 "parser.cpp"
    break;

  case 66:
#line 155 "parser.y"
                                            {(yyval.expr) = manage_indexedelem((yyvsp[-3].expr), (yyvsp[-1].expr)); fprintf(rulesFile, "indexedelem -> LCURLY expr COLON expr RCURLY\n");}
#line 2006 "parser.cpp"
    break;

  case 67:
#line 158 "parser.y"
                     {if(!block_b) increase_scope();}
#line 2012 "parser.cpp"
    break;

  case 68:
#line 158 "parser.y"
                                                                        {if(!block_b){symTab_hide();decrease_scope();} fprintf(rulesFile, "block -> LCURLY statements RCURLY\n");}
#line 2018 "parser.cpp"
    break;

  case 69:
#line 161 "parser.y"
                 {(yyval.stringValue) = manage_funcname_named((yyvsp[0].stringValue)); assert((yyval.stringValue)); fprintf(rulesFile, "funcname -> ID\n");}
#line 2024 "parser.cpp"
    break;

  case 70:
#line 162 "parser.y"
                 {(yyval.stringValue) = manage_funcname_anonymous(); assert((yyval.stringValue)); fprintf(rulesFile, "funcname -> \n");}
#line 2030 "parser.cpp"
    break;

  case 71:
#line 165 "parser.y"
                                { assert((yyvsp[0].stringValue)); (yyval.symbol) = manage_funcprefix((yyvsp[0].stringValue)); assert((yyval.symbol)); fprintf(rulesFile, "funcprefix -> FUNCTION funcname\n");}
#line 2036 "parser.cpp"
    break;

  case 72:
#line 168 "parser.y"
                                   {manage_funcargs(); fprintf(rulesFile, "funcargs -> LPAREN idlist RPAREN\n");}
#line 2042 "parser.cpp"
    break;

  case 73:
#line 171 "parser.y"
                    {(yyval.uintValue) = manage_funcbody(); fprintf(rulesFile, "funcbody -> block\n");}
#line 2048 "parser.cpp"
    break;

  case 74:
#line 174 "parser.y"
                                           {(yyval.symbol) = manage_funcdef((yyvsp[-2].symbol),(yyvsp[0].uintValue)); assert((yyval.symbol)); assert((yyvsp[-2].symbol)); }
#line 2054 "parser.cpp"
    break;

  case 75:
#line 177 "parser.y"
                        {(yyval.expr) = new_expr_const_num((yyvsp[0].intValue)); fprintf(rulesFile, "const -> INTEGER\n");}
#line 2060 "parser.cpp"
    break;

  case 76:
#line 178 "parser.y"
                        {(yyval.expr) = new_expr_const_num((yyvsp[0].realValue)); fprintf(rulesFile, "const -> REAL\n");}
#line 2066 "parser.cpp"
    break;

  case 77:
#line 179 "parser.y"
                        {(yyval.expr) = new_expr_const_string((yyvsp[0].stringValue)); fprintf(rulesFile, "const -> STRING\n");}
#line 2072 "parser.cpp"
    break;

  case 78:
#line 180 "parser.y"
                        {(yyval.expr) = new_expr(nil_e); fprintf(rulesFile, "const -> NIL\n");}
#line 2078 "parser.cpp"
    break;

  case 79:
#line 181 "parser.y"
                        {(yyval.expr) = new_expr_const_bool(1); fprintf(rulesFile, "const -> TRUE\n");}
#line 2084 "parser.cpp"
    break;

  case 80:
#line 182 "parser.y"
                        {(yyval.expr) = new_expr_const_bool(0); fprintf(rulesFile, "const -> FALSE\n");}
#line 2090 "parser.cpp"
    break;

  case 81:
#line 185 "parser.y"
                                {manage_idlist_id((yyvsp[0].stringValue)); fprintf(rulesFile,"idlist -> ID\n");}
#line 2096 "parser.cpp"
    break;

  case 82:
#line 186 "parser.y"
                                {manage_idlist_comma_id((yyvsp[0].stringValue)); fprintf(rulesFile,"idlist -> idlist COMMA ID\n");}
#line 2102 "parser.cpp"
    break;

  case 83:
#line 187 "parser.y"
                                {fprintf(rulesFile,"idlist -> \n");}
#line 2108 "parser.cpp"
    break;

  case 84:
#line 190 "parser.y"
                                                   {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt ELSE stmt\n");}
#line 2114 "parser.cpp"
    break;

  case 85:
#line 191 "parser.y"
                                          {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt\n");}
#line 2120 "parser.cpp"
    break;

  case 86:
#line 194 "parser.y"
              {++loopCounter;}
#line 2126 "parser.cpp"
    break;

  case 87:
#line 196 "parser.y"
              {--loopCounter;}
#line 2132 "parser.cpp"
    break;

  case 88:
#line 198 "parser.y"
                                     {}
#line 2138 "parser.cpp"
    break;

  case 89:
#line 201 "parser.y"
                                      {block_b = true;}
#line 2144 "parser.cpp"
    break;

  case 90:
#line 201 "parser.y"
                                                                {block_b = false;}
#line 2150 "parser.cpp"
    break;

  case 91:
#line 204 "parser.y"
                                                                     {block_b = true;}
#line 2156 "parser.cpp"
    break;

  case 92:
#line 204 "parser.y"
                                                                                                {block_b = false;}
#line 2162 "parser.cpp"
    break;

  case 93:
#line 207 "parser.y"
                                    { manage_return_expr((yyvsp[-1].expr));  fprintf(rulesFile, "returnstmt -> RETURN expr SEMICOLON\n");}
#line 2168 "parser.cpp"
    break;

  case 94:
#line 208 "parser.y"
                                    { manage_return(); fprintf(rulesFile, "returnstmt -> RETURN SEMICOLON\n");}
#line 2174 "parser.cpp"
    break;


#line 2178 "parser.cpp"

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
#line 211 "parser.y"


int main(int argc, char** argv) {
	if(!(alpha_yyin = fopen(argv[1], "r"))){
    printf("Could not open input file\n");
    return 1;
  }
  if(!(rulesFile = fopen("rules.txt", "w"))){
    printf("Could not open rules file\n");
    return 1;
  }
	init_library_func();
  yyparse();
  fprintf(rulesFile, "EOF\n");
  fclose(rulesFile);
}