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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 26 "ensbc-parse.y"
typedef union YYSTYPE {
  symtab_t   symp;
  double     dval;
  ensemble_t ensem;
} YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 87 "ensbc-parse.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



