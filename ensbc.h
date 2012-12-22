/* $Id: ensbc.h,v 1.21 2008/11/17 16:41:23 edwards Exp $ ($Date: 2008/11/17 16:41:23 $)
 *
 * Ensbc  header
 */
 
#ifndef _ENSBC_
#define _ENSBC_

#include <stdio.h>
#include <math.h>

#define NSYMS 100	/* maximum number of symbols */

#define   JACKKNIFE
#undef   BOOTSTRAP

typedef enum
{
  RealType = 0,
  ComplexType = 1
} datatype_t;

typedef struct complex
{
  double real;
  double imag;
} complex_t;

typedef struct ensemble
{
  complex_t *data;
  datatype_t type;      /* 0 if real and 1 if complex */
  int  nbin;            /* Number of bins, or data samples, configs, etc. */
  int  length;          /* Number of columns. E.g., time slices of a prop. */
} *ensemble_t;

typedef struct symtab
{
  char   *name;
  double (*funcptr)();
} *symtab_t;

struct symtab symtab[NSYMS];

/* Symbol table routines */
symtab_t symlook();

/* Initialize parser */
void init_parser();

/* Return the proper rescaling factor */
double rescale_factor(int num);

/* Create a new ensemble using parameters from source */
ensemble_t new_ensemble(ensemble_t src);

/* Push an ensemble onto the stack */
void push_ensemble(ensemble_t src);

/* Free an ensemble */
void free_ensemble(ensemble_t src);

/* Free all registered ensemble */
void free_all_ensembles(void);

/* Promote constant to ensemble */
ensemble_t promote_const_to_ensemble(double val, int nbin, int len);

/* Check if two ensemble have the same parameters */
int check_two_ensemble(ensemble_t src1, ensemble_t src2);

/* Return a new rescaled ensemble */
ensemble_t rescale_ensemble(ensemble_t src, double factor);

/* Add constant to an ensemble */
ensemble_t add_const_to_ensemble(double val, ensemble_t src2);

/* Add two ensembles */
ensemble_t add_two_ensemble(ensemble_t src1, ensemble_t src2);

/* Subtract two ensembles */
ensemble_t subtract_two_ensemble(ensemble_t src1, ensemble_t src2);

/* Multiply constant on an ensemble */
ensemble_t multiply_const_to_ensemble(double val, ensemble_t src2);

/* Multiply two ensembles */
ensemble_t multiply_two_ensemble(ensemble_t src1, ensemble_t src2);

/* Divide two ensembles */
ensemble_t divide_two_ensemble(ensemble_t src1, ensemble_t src2);

/* Negate ensemble */
ensemble_t negate_ensemble(ensemble_t src1);

/* Real part ensemble */
ensemble_t real_part_ensemble(ensemble_t src);

/* Imag part ensemble */
ensemble_t imag_part_ensemble(ensemble_t src);

/* Conjugate the ensemble */
ensemble_t conj_ensemble(ensemble_t src);

/* Call atan2 on two real ensembles */
ensemble_t atan2_ensemble(ensemble_t src1, ensemble_t src2);

/* Norm-sq of the ensemble. Will always be real. */
ensemble_t norm2_ensemble(ensemble_t src);

/* Build complex from two real ensembles */
ensemble_t cmplx_ensemble(ensemble_t src1, ensemble_t src2);

/* Multiply ensemble by I */
ensemble_t timesI_ensemble(ensemble_t src);

/* Read ensemble from file ptr */
ensemble_t read_fileptr_ensemble(FILE *fp, char *name);

/* Read ensemble from named file*/
ensemble_t read_ensemble(char *name);

/* Write ensemble */
void write_ensemble(char *name, ensemble_t src);

/* Apply function to ensemble */
ensemble_t apply_func_ensemble(double (*funcptr)(), ensemble_t src1);

/* Apply pow(src,const) to ensemble */
ensemble_t apply_pow_ensemble(ensemble_t src, double val);

/* Calculate mean, err and err/mean for data */
void calc_ensemble(ensemble_t src);

/* Print the ensemble (maybe for a pipe??) */
void print_ensemble(ensemble_t src);

/* Take the forward difference of the ensemble */
ensemble_t forward_diff_ensemble(ensemble_t src);

/* Take the backward difference of the ensemble */
ensemble_t backward_diff_ensemble(ensemble_t src);

/* Take the central difference of the ensemble */
ensemble_t central_diff_ensemble(ensemble_t src);

/* Extract a rangle of time slices from an ensemble */
ensemble_t extract_ensemble(ensemble_t src, int elem_i, int elem_f);

/* Shift an ensemble in some direction dropping bits from the back */
ensemble_t shift_ensemble(ensemble_t src, int sh);

/* Periodic (circular) shift an ensemble */
ensemble_t cshift_ensemble(ensemble_t src, int sh);

/* Concatenate two ensembles. */
ensemble_t concatenate_ensemble(ensemble_t src1, ensemble_t src2) ;

/* Input routines for flex */
char *arg_ptr;
int (*fn_yyinput)(char *buf, int max_size);
int file_yyinput(char *buf, int max_size);
int arg_yyinput(char *buf, int max_size);

int yyparse(void);
void yyerror(char *errmsg);

#endif
