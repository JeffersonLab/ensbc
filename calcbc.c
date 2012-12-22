/*
 * $Id: calcbc.c,v 1.3 2002/10/18 15:40:38 edwards Exp $ ($Date: 2002/10/18 15:40:38 $)
 * 
 * Calcbc main routine
 *
 * Usage
 *    calcbc "expression"
 *
 * is equivalent to
 *    ensbc  "calc(expression)"
 */
#include "ensbc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTRING 1000

int main(int argc, char *argv[])
{
  char  calc_line[MAXSTRING];

  /* Initialize parser */
  init_parser();

  /* Check arguments */
  if (argc == 2)
  {
    /* Process argument on command line then exit */
    /* NOTE: for calcbc, I wrap a calc( ... ) around the argument */
    int len = strlen(argv[1]);

    if (len > MAXSTRING-6)
    {
      fprintf(stderr,"calcbc: expression too long\n");
      exit(1);
    }

    strcpy(calc_line, "calc(");
    strcat(calc_line, argv[1]);
    strcat(calc_line, ")");

    arg_ptr = calc_line;
    fn_yyinput = arg_yyinput;
    yyparse();
  }
  else
  {
    fprintf(stderr,"Usage: calcbc <arg>\n");
    exit(1);
  }

  return 0;
}
