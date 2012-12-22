/* $Id: ensbc-lex.l,v 1.21 2008/11/17 16:41:23 edwards Exp $ ($Date: 2008/11/17 16:41:23 $) 
 *
 * Ensbc lexer
 */

%{
#include "ensbc.h"
#include "ensbc-parse.h"
#include <math.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#undef  YY_INPUT
#define YY_INPUT(buf,result,max_size) \
        if ( (result = (*fn_yyinput)((char *) buf, max_size)) < 0 ) \
            YY_FATAL_ERROR( "read() in flex scanner failed" );
%}

ws      [ \t]+
dig     ([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?)
name    [A-Za-z][A-Za-z_0-9\-.,/]*
qstr    \"[^\"]*\"

%%
{dig}	{
	  yylval.dval = atof(yytext);
	  return NUMBER;
	}

{ws}	; /* ignore white space */

{qstr}	{ /* Anything in a quoted string is taken as a file name */
          char *name = strdup(yytext);
	  struct symtab *sp;
          name[strlen(yytext)-1] = '\0';
	  sp = symlook(name+1);
	  yylval.symp = sp;
	  return NAME;
	}

calc	{ /* calc is a special operation */
	  return CALC;
	}

print	{ /* print is a special operation */
	  return PRINT;
	}

shift	{ /* shift is a special operation */
	  return SHIFT;
	}

cshift	{ /* cshift is a special operation */
	  return CSHIFT;
	}

extract	{ /* extract_diff is a special operation */
	  return EXTRACT;
	}

cat    	{ /* concatenate is a special operation */
	  return CAT;
	}

real	{ /* real is a special operation */
	  return REAL;
	}

imag	{ /* imag is a special operation */
	  return IMAG;
	}

conj	{ /* conj is a special operation */
	  return CONJ;
	}

atan2	{ /* atan2 is a special operation */
	  return ATAN2;
	}

norm2	{ /* norm2 is a special operation */
	  return NORM2;
	}

timesI	{ /* timesI is a special operation */
	  return TIMESI;
	}

cmplx	{ /* cmplx is a special operation */
	  return CMPLX;
	}

{name}	{ /* return symbol pointer */
	  struct symtab *sp = symlook(yytext);
	  yylval.symp = sp;
	  return NAME;
	}

"^"	{ return EXPON; }

"$"	{ return 0; }

";"     ;
\n	; /* ignore white space */

.	return yytext[0];
%%
/* look up a symbol table entry, add if not present */
symtab_t symlook(char *s)
{
  symtab_t sp;
	
  for(sp = symtab; sp < &symtab[NSYMS]; sp++)
  {
    /* is it already here? */
    if (sp->name && ! strcmp(sp->name, s))
      return sp;
		
    /* is it free */
    if (! sp->name)
    {
      sp->name = strdup(s);
      return sp;
    }
    /* otherwise continue to next */
  }
  yyerror("Too many symbols");
  exit(1);	/* cannot continue */
} /* symlook */

/* Add a function name and pointer to the symbol table */
void addfunc(char *name, double (*func)())
{
  symtab_t sp = symlook(name);
  sp->funcptr = func;
}

/* Used for file input */
int file_yyinput(char *buf, int max_size)
{
  return  read(fileno(yyin), (char *)buf, max_size);
}

/* Used for reading from a string */
int arg_yyinput(char *buf, int max_size)
{
  int  len, copylen;

  len = strlen(arg_ptr);
  if (len >= max_size)
    copylen = max_size -1;
  else
    copylen = len;

  if (len > 0)
  {
    memcpy(buf, arg_ptr, copylen);
    arg_ptr += copylen;
  }

  return copylen;
}

/* Initialize the lexer and parser */
void init_parser()
{
  extern int yydebug;

  yydebug = 0;

  /* Add useful C math library routines */
  addfunc("abs", fabs);
  addfunc("sqrt", sqrt);
  addfunc("exp", exp);
  addfunc("log", log);
  addfunc("log10", log10);
  addfunc("cos", cos);
  addfunc("sin", sin);
  addfunc("tan", tan);
  addfunc("cosh", cosh);
  addfunc("sinh", sinh);
  addfunc("tanh", tanh);
  addfunc("acos", acos);
  addfunc("asin", asin);
  addfunc("atan", atan);
  addfunc("acosh", acosh);
  addfunc("asinh", asinh);
  addfunc("atanh", atanh);
}
