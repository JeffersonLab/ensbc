/*
 * $Id: calc.c,v 1.6 2002/10/18 15:40:38 edwards Exp $ ($Date: 2002/10/18 15:40:38 $)
 * 
 * Driver routine to call "calc" on a single command line argument
 * If a command line argument is not specified, then read contents
 * from stdin
 */
#include <stdio.h>
#include <stdlib.h>
#include "ensbc.h"

int main(int argc, char **argv)
{
  if (argc == 2)
  {
    calc_ensemble(read_ensemble(argv[1]));
  }
  else if (argc == 1)
  {
    calc_ensemble(read_fileptr_ensemble(stdin, "stdin"));
  }
  else
  {
    fprintf(stderr, "Usage: calc ensemble_file\n");
    exit(1);
  }

  return 0;
}
