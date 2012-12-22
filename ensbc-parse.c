/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     NUMBER = 259,
     CALC = 260,
     PRINT = 261,
     SHIFT = 262,
     CSHIFT = 263,
     FORWARD_DIFF = 264,
     BACKWARD_DIFF = 265,
     CENTRAL_DIFF = 266,
     EXTRACT = 267,
     CAT = 268,
     REAL = 269,
     IMAG = 270,
     CONJ = 271,
     ATAN2 = 272,
     NORM2 = 273,
     CMPLX = 274,
     TIMESI = 275,
     EXPON = 276,
     UMINUS = 277
   };
#endif
#define NAME 258
#define NUMBER 259
#define CALC 260
#define PRINT 261
#define SHIFT 262
#define CSHIFT 263
#define FORWARD_DIFF 264
#define BACKWARD_DIFF 265
#define CENTRAL_DIFF 266
#define EXTRACT 267
#define CAT 268
#define REAL 269
#define IMAG 270
#define CONJ 271
#define ATAN2 272
#define NORM2 273
#define CMPLX 274
#define TIMESI 275
#define EXPON 276
#define UMINUS 277




/* Copy the first part of user declarations.  */
#line 5 "ensbc-parse.y"

#include "ensbc.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifndef errno
extern int errno;
#endif

void yyerror(char *);

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1


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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 26 "ensbc-parse.y"
typedef union YYSTYPE {
  symtab_t   symp;
  double     dval;
  ensemble_t ensem;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 146 "ensbc-parse.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 158 "ensbc-parse.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   463

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  5
/* YYNRULES -- Number of rules. */
#define YYNRULES  51
/* YYNRULES -- Number of states. */
#define YYNSTATES  152

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,    23,    22,    30,    21,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    27,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    17,    22,    27,    32,
      39,    44,    49,    53,    57,    61,    65,    68,    72,    76,
      78,    83,    87,    91,    95,    99,   103,   107,   111,   115,
     119,   123,   127,   131,   134,   138,   145,   152,   161,   168,
     175,   180,   185,   190,   195,   200,   207,   214,   221,   228,
     232,   234
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      32,     0,    -1,    33,    -1,    32,    33,    -1,     3,    27,
      35,    -1,     5,    28,    35,    29,    -1,     5,    28,    34,
      29,    -1,     6,    28,    35,    29,    -1,     6,    28,    34,
      29,    -1,     3,    27,     1,     3,    27,    35,    -1,     5,
      28,     1,    29,    -1,     6,    28,     1,    29,    -1,    34,
      22,    34,    -1,    34,    21,    34,    -1,    34,    23,    34,
      -1,    34,    24,    34,    -1,    21,    34,    -1,    34,    25,
      34,    -1,    28,    34,    29,    -1,     4,    -1,     3,    28,
      34,    29,    -1,    35,    22,    35,    -1,    34,    22,    35,
      -1,    35,    22,    34,    -1,    35,    21,    35,    -1,    34,
      21,    35,    -1,    35,    21,    34,    -1,    35,    23,    35,
      -1,    34,    23,    35,    -1,    35,    23,    34,    -1,    35,
      24,    35,    -1,    34,    24,    35,    -1,    35,    24,    34,
      -1,    21,    35,    -1,    35,    25,    34,    -1,     7,    28,
      35,    30,    34,    29,    -1,     8,    28,    35,    30,    34,
      29,    -1,    12,    28,    35,    30,    34,    30,    34,    29,
      -1,    12,    28,    35,    30,    34,    29,    -1,    13,    28,
      35,    30,    35,    29,    -1,    14,    28,    35,    29,    -1,
      15,    28,    35,    29,    -1,    16,    28,    35,    29,    -1,
      18,    28,    35,    29,    -1,    20,    28,    35,    29,    -1,
      17,    28,    35,    30,    35,    29,    -1,    19,    28,    35,
      30,    35,    29,    -1,    19,    28,    34,    30,    35,    29,
      -1,    19,    28,    35,    30,    34,    29,    -1,    28,    35,
      29,    -1,     3,    -1,     3,    28,    35,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    58,    58,    59,    62,    67,    72,    76,    81,    85,
      90,    91,    94,    98,   102,   106,   110,   114,   118,   122,
     126,   140,   144,   148,   152,   156,   161,   165,   173,   177,
     181,   189,   197,   201,   205,   212,   216,   220,   224,   228,
     232,   236,   240,   244,   251,   255,   263,   267,   272,   277,
     281,   285
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "NUMBER", "CALC", "PRINT",
  "SHIFT", "CSHIFT", "FORWARD_DIFF", "BACKWARD_DIFF", "CENTRAL_DIFF",
  "EXTRACT", "CAT", "REAL", "IMAG", "CONJ", "ATAN2", "NORM2", "CMPLX",
  "TIMESI", "'-'", "'+'", "'*'", "'/'", "EXPON", "UMINUS", "'='", "'('",
  "')'", "','", "$accept", "statement_list", "statement",
  "const_expression", "expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    45,    43,    42,    47,   276,   277,    61,    40,    41,
      44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    31,    32,    32,    33,    33,    33,    33,    33,    33,
      33,    33,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     3,     4,     4,     4,     4,     6,
       4,     4,     3,     3,     3,     3,     2,     3,     3,     1,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     6,     6,     8,     6,     6,
       4,     4,     4,     4,     4,     6,     6,     6,     6,     3,
       1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     2,     0,     0,     0,     1,
       3,     0,    50,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     6,     5,    11,     8,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,    49,    13,    25,    12,    22,    14,
      28,    15,    31,     0,     0,     0,    17,    26,    24,    23,
      21,    29,    27,    32,    30,    34,     9,    20,    51,     0,
       0,     0,     0,    40,    41,    42,     0,    43,     0,     0,
      44,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    12,    14,
      15,    35,    36,    38,     0,    39,    45,    47,    48,    46,
       0,    37
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     4,     5,    27,    28
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -19
static const short yypact[] =
{
      38,   -18,   -13,    -2,    11,   -19,    54,    77,   164,   -19,
     -19,     7,    14,   -19,    28,    31,    32,    48,    49,    51,
      55,    58,    78,    79,    80,   183,   183,   110,   438,    82,
     231,   240,    84,   249,   258,     1,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   -19,   -19,
     267,   276,   183,   183,   183,   183,    -1,   183,   183,   183,
     183,    -1,   -19,   -19,   -19,   -19,   -19,   -19,   183,   285,
     294,     0,    10,   100,   185,   303,   312,   321,   201,   330,
     211,   221,   339,   -19,   -19,    13,    40,    13,    40,    90,
      91,    90,    91,    98,    -1,    -1,    90,    13,    40,    13,
      40,    90,    91,    90,    91,    90,   438,   -19,   -19,    -1,
      -1,    -1,   183,   -19,   -19,   -19,   183,   -19,   183,   183,
     -19,    -1,   -19,   348,    -1,    -1,    -1,    -1,   357,   366,
     -17,   375,   384,   393,   402,   411,   420,    76,    76,    90,
      90,   -19,   -19,   -19,    -1,   -19,   -19,   -19,   -19,   -19,
     429,   -19
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -19,   -19,   125,    -7,   102
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      30,    33,    93,    13,   124,   125,   126,   127,    56,     6,
      35,     9,   143,   144,     1,     7,     2,     3,    48,    50,
      94,    57,    58,    59,    60,    61,     8,    95,    68,    69,
     109,    57,    58,    59,    60,    61,    54,    55,    56,    80,
     110,     1,    36,     2,     3,    85,    87,    89,    91,    96,
      97,    99,   101,   103,   105,    11,    37,    12,    13,    38,
      39,    14,    15,    59,    60,    61,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    40,    41,    29,    42,
      12,    13,    26,    43,    14,    15,    44,   122,   123,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,   126,
     127,    56,   128,   129,   130,    26,    45,    46,    47,    31,
      34,    62,   134,    65,   136,    56,    61,   137,   138,   139,
     140,    57,    58,    59,    60,    61,   121,    49,    51,    10,
     111,    52,    53,    54,    55,    56,     0,   150,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    81,    82,
       0,     0,     0,     0,    86,    88,    90,    92,     0,    98,
     100,   102,   104,     0,     0,    32,     0,    12,    13,     0,
     106,    14,    15,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    12,    13,     0,     0,
      14,    15,    26,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,    57,    58,    59,    60,
      61,    26,     0,     0,   131,   112,     0,     0,   132,     0,
     133,   135,    57,    58,    59,    60,    61,     0,     0,     0,
       0,   116,    52,    53,    54,    55,    56,     0,     0,     0,
       0,   118,    57,    58,    59,    60,    61,     0,     0,     0,
       0,   119,    52,    53,    54,    55,    56,     0,     0,     0,
      63,    57,    58,    59,    60,    61,     0,     0,     0,    64,
      52,    53,    54,    55,    56,     0,     0,     0,    66,    57,
      58,    59,    60,    61,     0,     0,     0,    67,    52,    53,
      54,    55,    56,     0,     0,     0,    83,    57,    58,    59,
      60,    61,     0,     0,     0,    84,    52,    53,    54,    55,
      56,     0,     0,     0,   107,    57,    58,    59,    60,    61,
       0,     0,     0,   108,    57,    58,    59,    60,    61,     0,
       0,     0,   113,    57,    58,    59,    60,    61,     0,     0,
       0,   114,    57,    58,    59,    60,    61,     0,     0,     0,
     115,    57,    58,    59,    60,    61,     0,     0,     0,   117,
      57,    58,    59,    60,    61,     0,     0,     0,   120,   124,
     125,   126,   127,    56,     0,     0,     0,    83,   124,   125,
     126,   127,    56,     0,     0,     0,   141,   124,   125,   126,
     127,    56,     0,     0,     0,   142,    57,    58,    59,    60,
      61,     0,     0,     0,   145,    57,    58,    59,    60,    61,
       0,     0,     0,   146,    57,    58,    59,    60,    61,     0,
       0,     0,   147,    52,    53,    54,    55,    56,     0,     0,
       0,   148,    57,    58,    59,    60,    61,     0,     0,     0,
     149,   124,   125,   126,   127,    56,     0,     0,     0,   107,
     124,   125,   126,   127,    56,     0,     0,     0,   151,    57,
      58,    59,    60,    61
};

static const short yycheck[] =
{
       7,     8,     3,     4,    21,    22,    23,    24,    25,    27,
       3,     0,    29,    30,     3,    28,     5,     6,    25,    26,
      21,    21,    22,    23,    24,    25,    28,    28,    27,    36,
      30,    21,    22,    23,    24,    25,    23,    24,    25,    46,
      30,     3,    28,     5,     6,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,     1,    28,     3,     4,    28,
      28,     7,     8,    23,    24,    25,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    28,    28,     1,    28,
       3,     4,    28,    28,     7,     8,    28,    94,    95,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    23,
      24,    25,   109,   110,   111,    28,    28,    28,    28,     7,
       8,    29,   119,    29,   121,    25,    25,   124,   125,   126,
     127,    21,    22,    23,    24,    25,    28,    25,    26,     4,
      30,    21,    22,    23,    24,    25,    -1,   144,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    55,    -1,    57,
      58,    59,    60,    -1,    -1,     1,    -1,     3,     4,    -1,
      68,     7,     8,    -1,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     3,     4,    -1,    -1,
       7,     8,    28,    -1,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    21,    22,    23,    24,
      25,    28,    -1,    -1,   112,    30,    -1,    -1,   116,    -1,
     118,   119,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    30,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    30,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    30,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      29,    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    29,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    29,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    29,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    29,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    29,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    29,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    29,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      29,    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    29,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    29,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    29,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    29,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    29,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    29,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    29,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      29,    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    21,
      22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     5,     6,    32,    33,    27,    28,    28,     0,
      33,     1,     3,     4,     7,     8,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    28,    34,    35,     1,
      34,    35,     1,    34,    35,     3,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28,    34,    35,
      34,    35,    21,    22,    23,    24,    25,    21,    22,    23,
      24,    25,    29,    29,    29,    29,    29,    29,    27,    34,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      34,    35,    35,    29,    29,    34,    35,    34,    35,    34,
      35,    34,    35,     3,    21,    28,    34,    34,    35,    34,
      35,    34,    35,    34,    35,    34,    35,    29,    29,    30,
      30,    30,    30,    29,    29,    29,    30,    29,    30,    30,
      29,    28,    34,    34,    21,    22,    23,    24,    34,    34,
      34,    35,    35,    35,    34,    35,    34,    34,    34,    34,
      34,    29,    29,    29,    30,    29,    29,    29,    29,    29,
      34,    29
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
        case 4:
#line 63 "ensbc-parse.y"
    {
		  write_ensemble(yyvsp[-2].symp->name, yyvsp[0].ensem);
		  free_all_ensembles();
		;}
    break;

  case 5:
#line 68 "ensbc-parse.y"
    {
  		  calc_ensemble(yyvsp[-1].ensem);
		  free_all_ensembles();
		;}
    break;

  case 6:
#line 73 "ensbc-parse.y"
    {
  		  printf("%f\n", yyvsp[-1].dval);
		;}
    break;

  case 7:
#line 77 "ensbc-parse.y"
    {
  		  print_ensemble(yyvsp[-1].ensem);
		  free_all_ensembles();
		;}
    break;

  case 8:
#line 82 "ensbc-parse.y"
    {
  		  printf("%f\n", yyvsp[-1].dval);
		;}
    break;

  case 9:
#line 86 "ensbc-parse.y"
    {
		  write_ensemble(yyvsp[-2].symp->name, yyvsp[0].ensem);
		  free_all_ensembles();
		;}
    break;

  case 12:
#line 95 "ensbc-parse.y"
    { 
		  yyval.dval = yyvsp[-2].dval + yyvsp[0].dval;
		;}
    break;

  case 13:
#line 99 "ensbc-parse.y"
    {
		  yyval.dval = yyvsp[-2].dval - yyvsp[0].dval;
		;}
    break;

  case 14:
#line 103 "ensbc-parse.y"
    {
		  yyval.dval = yyvsp[-2].dval * yyvsp[0].dval;
		;}
    break;

  case 15:
#line 107 "ensbc-parse.y"
    {
		  yyval.dval = yyvsp[-2].dval / yyvsp[0].dval;
		;}
    break;

  case 16:
#line 111 "ensbc-parse.y"
    {
		  yyval.dval = -yyvsp[0].dval;
		;}
    break;

  case 17:
#line 115 "ensbc-parse.y"
    {
		  yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval);
 		;}
    break;

  case 18:
#line 119 "ensbc-parse.y"
    {
		  yyval.dval = yyvsp[-1].dval;
		;}
    break;

  case 19:
#line 123 "ensbc-parse.y"
    {
		  yyval.dval = yyvsp[0].dval;
		;}
    break;

  case 20:
#line 127 "ensbc-parse.y"
    {
		  if (yyvsp[-3].symp->funcptr)
	          {
  		    yyval.dval = (yyvsp[-3].symp->funcptr)(yyvsp[-1].dval);
		  }
		  else
		  {
 		    fprintf(stderr,"%s not a function\n", yyvsp[-3].symp->name);
		    exit(1);
		  }
		;}
    break;

  case 21:
#line 141 "ensbc-parse.y"
    { 
		  yyval.ensem = add_two_ensemble(yyvsp[-2].ensem, yyvsp[0].ensem);
		;}
    break;

  case 22:
#line 145 "ensbc-parse.y"
    { 
		  yyval.ensem = add_const_to_ensemble(yyvsp[-2].dval, yyvsp[0].ensem);
		;}
    break;

  case 23:
#line 149 "ensbc-parse.y"
    { 
		  yyval.ensem = add_const_to_ensemble(yyvsp[0].dval, yyvsp[-2].ensem);
		;}
    break;

  case 24:
#line 153 "ensbc-parse.y"
    {
		  yyval.ensem = subtract_two_ensemble(yyvsp[-2].ensem, yyvsp[0].ensem);
		;}
    break;

  case 25:
#line 157 "ensbc-parse.y"
    {
		  ensemble_t src2 = negate_ensemble(yyvsp[0].ensem);
		  yyval.ensem = add_const_to_ensemble(yyvsp[-2].dval, src2);
		;}
    break;

  case 26:
#line 162 "ensbc-parse.y"
    {
		  yyval.ensem = add_const_to_ensemble(-yyvsp[0].dval, yyvsp[-2].ensem);
		;}
    break;

  case 27:
#line 166 "ensbc-parse.y"
    {
		  double factor = rescale_factor(yyvsp[-2].ensem->nbin);
		  ensemble_t src1 = rescale_ensemble(yyvsp[-2].ensem, 1./factor);
		  ensemble_t src2 = rescale_ensemble(yyvsp[0].ensem, 1./factor);
		  ensemble_t dst  = multiply_two_ensemble(src1, src2);
		  yyval.ensem = rescale_ensemble(dst, factor);
		;}
    break;

  case 28:
#line 174 "ensbc-parse.y"
    {
		  yyval.ensem = multiply_const_to_ensemble(yyvsp[-2].dval, yyvsp[0].ensem);
		;}
    break;

  case 29:
#line 178 "ensbc-parse.y"
    {
		  yyval.ensem = multiply_const_to_ensemble(yyvsp[0].dval, yyvsp[-2].ensem);
		;}
    break;

  case 30:
#line 182 "ensbc-parse.y"
    {
		  double factor = rescale_factor(yyvsp[-2].ensem->nbin);
		  ensemble_t src1 = rescale_ensemble(yyvsp[-2].ensem, 1./factor);
		  ensemble_t src2 = rescale_ensemble(yyvsp[0].ensem, 1./factor);
		  ensemble_t dst  = divide_two_ensemble(src1, src2);
		  yyval.ensem = rescale_ensemble(dst, factor);
		;}
    break;

  case 31:
#line 190 "ensbc-parse.y"
    {
		  double factor = rescale_factor(yyvsp[0].ensem->nbin);
		  ensemble_t src1 = promote_const_to_ensemble(yyvsp[-2].dval,yyvsp[0].ensem->nbin,yyvsp[0].ensem->length);
		  ensemble_t src2 = rescale_ensemble(yyvsp[0].ensem, 1./factor);
		  ensemble_t dst  = divide_two_ensemble(src1, src2);
		  yyval.ensem = rescale_ensemble(dst, factor);
		;}
    break;

  case 32:
#line 198 "ensbc-parse.y"
    {
		  yyval.ensem = multiply_const_to_ensemble(1.0/yyvsp[0].dval, yyvsp[-2].ensem);
		;}
    break;

  case 33:
#line 202 "ensbc-parse.y"
    {
		  yyval.ensem = negate_ensemble(yyvsp[0].ensem);
		;}
    break;

  case 34:
#line 206 "ensbc-parse.y"
    {
		  double factor = rescale_factor(yyvsp[-2].ensem->nbin);
		  ensemble_t src = rescale_ensemble(yyvsp[-2].ensem, 1./factor);
  		  ensemble_t dst = apply_pow_ensemble(src, yyvsp[0].dval);
		  yyval.ensem = rescale_ensemble(dst, factor);
 		;}
    break;

  case 35:
#line 213 "ensbc-parse.y"
    {
  		  yyval.ensem = shift_ensemble(yyvsp[-3].ensem,(int)(yyvsp[-1].dval));
		;}
    break;

  case 36:
#line 217 "ensbc-parse.y"
    {
  		  yyval.ensem = cshift_ensemble(yyvsp[-3].ensem,(int)(yyvsp[-1].dval));
		;}
    break;

  case 37:
#line 221 "ensbc-parse.y"
    {
  		  yyval.ensem = extract_ensemble(yyvsp[-5].ensem,(int)(yyvsp[-3].dval),(int)(yyvsp[-1].dval));
		;}
    break;

  case 38:
#line 225 "ensbc-parse.y"
    {
  		  yyval.ensem = extract_ensemble(yyvsp[-3].ensem,(int)(yyvsp[-1].dval),(int)(yyvsp[-1].dval));
		;}
    break;

  case 39:
#line 229 "ensbc-parse.y"
    {
  		  yyval.ensem = concatenate_ensemble(yyvsp[-3].ensem,yyvsp[-1].ensem);
		;}
    break;

  case 40:
#line 233 "ensbc-parse.y"
    {
  		  yyval.ensem = real_part_ensemble(yyvsp[-1].ensem);
		;}
    break;

  case 41:
#line 237 "ensbc-parse.y"
    {
  		  yyval.ensem = imag_part_ensemble(yyvsp[-1].ensem);
		;}
    break;

  case 42:
#line 241 "ensbc-parse.y"
    {
  		  yyval.ensem = conj_ensemble(yyvsp[-1].ensem);
		;}
    break;

  case 43:
#line 245 "ensbc-parse.y"
    {
		  double factor = rescale_factor(yyvsp[-1].ensem->nbin);
		  ensemble_t src = rescale_ensemble(yyvsp[-1].ensem, 1./factor);
  		  ensemble_t dst = norm2_ensemble(src);
		  yyval.ensem = rescale_ensemble(dst, factor);
		;}
    break;

  case 44:
#line 252 "ensbc-parse.y"
    {
  		  yyval.ensem = timesI_ensemble(yyvsp[-1].ensem);
		;}
    break;

  case 45:
#line 256 "ensbc-parse.y"
    {
		  double factor = rescale_factor(yyvsp[-3].ensem->nbin);
		  ensemble_t src1 = rescale_ensemble(yyvsp[-3].ensem, 1./factor);
		  ensemble_t src2 = rescale_ensemble(yyvsp[-1].ensem, 1./factor);
		  ensemble_t dst  = atan2_ensemble(src1,src2);
		  yyval.ensem = rescale_ensemble(dst, factor);
		;}
    break;

  case 46:
#line 264 "ensbc-parse.y"
    {
  		  yyval.ensem = cmplx_ensemble(yyvsp[-3].ensem,yyvsp[-1].ensem);
		;}
    break;

  case 47:
#line 268 "ensbc-parse.y"
    {
		  ensemble_t src1 = promote_const_to_ensemble(yyvsp[-3].dval,yyvsp[-1].ensem->nbin,yyvsp[-1].ensem->length);
  		  yyval.ensem = cmplx_ensemble(src1,yyvsp[-1].ensem);
		;}
    break;

  case 48:
#line 273 "ensbc-parse.y"
    {
		  ensemble_t src2 = promote_const_to_ensemble(yyvsp[-1].dval,yyvsp[-3].ensem->nbin,yyvsp[-3].ensem->length);
  		  yyval.ensem = cmplx_ensemble(yyvsp[-3].ensem,src2);
		;}
    break;

  case 49:
#line 278 "ensbc-parse.y"
    {
		  yyval.ensem = yyvsp[-1].ensem;
		;}
    break;

  case 50:
#line 282 "ensbc-parse.y"
    {
		  yyval.ensem = read_ensemble(yyvsp[0].symp->name);
		;}
    break;

  case 51:
#line 286 "ensbc-parse.y"
    {
		  if (yyvsp[-3].symp->funcptr)
	          {
		    double factor = rescale_factor(yyvsp[-1].ensem->nbin);
		    ensemble_t src = rescale_ensemble(yyvsp[-1].ensem, 1./factor);
  		    ensemble_t dst = apply_func_ensemble(yyvsp[-3].symp->funcptr, src);
		    yyval.ensem = rescale_ensemble(dst, factor);
		  }
		  else
		  {
 		    fprintf(stderr,"%s not a function\n", yyvsp[-3].symp->name);
		    exit(1);
		  }
		;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 1585 "ensbc-parse.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 301 "ensbc-parse.y"


void yyerror(char *errmsg)
{
  fprintf(stderr, "%s\n", errmsg);
}

