/*
 * $Id: ensbc.c,v 1.10 2002/10/18 15:40:38 edwards Exp $ ($Date: 2002/10/18 15:40:38 $)
 * 
 * Ensbc main routine
 */
#include "ensbc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  /* Initialize parser */
  init_parser();

  /* Check arguments */
  if (argc == 2)
  {
    /* Process argument on command line then exit */
    arg_ptr = argv[1];
    fn_yyinput = arg_yyinput;
    yyparse();
  }
  else if (argc == 1)
  {
    /* Read standard input */
    fn_yyinput = file_yyinput;
    yyparse();
  }
  else
  {
    fprintf(stderr,"Usage: ensbc <arg>\n");
    fprintf(stderr,"  or   STDIN | ensbc\n");
    exit(1);
  }

  return 0;
}
