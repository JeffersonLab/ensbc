/* $Id: ensbc-parse.y,v 1.26 2008/11/18 14:44:15 edwards Exp $ ($Date: 2008/11/18 14:44:15 $)
 *
 * Ensbc parser
 */
%{
#include "ensbc.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifndef errno
extern int errno;
#endif

void yyerror(char *);
int yylex(void);

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1
%}

%union
{
  symtab_t   symp;
  double     dval;
  ensemble_t ensem;
}
%token <symp> NAME
%token <dval> NUMBER
%token CALC
%token PRINT
%token SHIFT
%token CSHIFT
%token FORWARD_DIFF
%token BACKWARD_DIFF
%token CENTRAL_DIFF
%token EXTRACT
%token CAT
%token REAL
%token IMAG
%token CONJ
%token ATAN2
%token NORM2
%token CMPLX
%token TIMESI

%left '-' '+'
%left '*' '/'
%right EXPON
%nonassoc UMINUS

%type <ensem> expression
%type <dval>  const_expression
%%
statement_list:	statement
	|	statement_list statement
	;

statement:	NAME '=' expression
		{
		  write_ensemble($1->name, $3);
		  free_all_ensembles();
		}
	|	CALC '(' expression ')'
		{
  		  calc_ensemble($3);
		  free_all_ensembles();
		}
	|	CALC '(' const_expression ')'
		{
  		  printf("%f\n", $3);
		}
	|	PRINT '(' expression ')'
		{
  		  print_ensemble($3);
		  free_all_ensembles();
		}
	|	PRINT '(' const_expression ')'
		{
  		  printf("%f\n", $3);
		}
	|	NAME '=' error NAME '=' expression
		{
		  write_ensemble($4->name, $6);
		  free_all_ensembles();
		}
	|	CALC '(' error ')'
	|	PRINT '(' error ')'
	;

const_expression: const_expression '+' const_expression 
		{ 
		  $$ = $1 + $3;
		}
	|	const_expression '-' const_expression
		{
		  $$ = $1 - $3;
		}
	|	const_expression '*' const_expression
		{
		  $$ = $1 * $3;
		}
	|	const_expression '/' const_expression
		{
		  $$ = $1 / $3;
		}
	|	'-' const_expression %prec UMINUS
		{
		  $$ = -$2;
		}
	|	const_expression EXPON const_expression
		{
		  $$ = pow($1, $3);
 		}
	|	'(' const_expression ')'
		{
		  $$ = $2;
		}
	|	NUMBER
		{
		  $$ = $1;
		}
	|	NAME '(' const_expression ')'
		{
		  if ($1->funcptr)
	          {
  		    $$ = ($1->funcptr)($3);
		  }
		  else
		  {
 		    fprintf(stderr,"%s not a function\n", $1->name);
		    exit(1);
		  }
		}
	;

expression:	expression '+' expression 
		{ 
		  $$ = add_two_ensemble($1, $3);
		}
	|	const_expression '+' expression 
		{ 
		  $$ = add_const_to_ensemble($1, $3);
		}
	|	expression '+' const_expression 
		{ 
		  $$ = add_const_to_ensemble($3, $1);
		}
	|	expression '-' expression
		{
		  $$ = subtract_two_ensemble($1, $3);
		}
	|	const_expression '-' expression
		{
		  ensemble_t src2 = negate_ensemble($3);
		  $$ = add_const_to_ensemble($1, src2);
		}
	|	expression '-' const_expression
		{
		  $$ = add_const_to_ensemble(-$3, $1);
		}
	|	expression '*' expression
		{
		  double factor = rescale_factor($1->nbin);
		  ensemble_t src1 = rescale_ensemble($1, 1./factor);
		  ensemble_t src2 = rescale_ensemble($3, 1./factor);
		  ensemble_t dst  = multiply_two_ensemble(src1, src2);
		  $$ = rescale_ensemble(dst, factor);
		}
	|	const_expression '*' expression
		{
		  $$ = multiply_const_to_ensemble($1, $3);
		}
	|	expression '*' const_expression
		{
		  $$ = multiply_const_to_ensemble($3, $1);
		}
	|	expression '/' expression
		{
		  double factor = rescale_factor($1->nbin);
		  ensemble_t src1 = rescale_ensemble($1, 1./factor);
		  ensemble_t src2 = rescale_ensemble($3, 1./factor);
		  ensemble_t dst  = divide_two_ensemble(src1, src2);
		  $$ = rescale_ensemble(dst, factor);
		}
	|	const_expression '/' expression
		{
		  double factor = rescale_factor($3->nbin);
		  ensemble_t src1 = promote_const_to_ensemble($1,$3->nbin,$3->length);
		  ensemble_t src2 = rescale_ensemble($3, 1./factor);
		  ensemble_t dst  = divide_two_ensemble(src1, src2);
		  $$ = rescale_ensemble(dst, factor);
		}
	|	expression '/' const_expression
		{
		  $$ = multiply_const_to_ensemble(1.0/$3, $1);
		}
	|	'-' expression %prec UMINUS
		{
		  $$ = negate_ensemble($2);
		}
	|	expression EXPON const_expression
		{
		  double factor = rescale_factor($1->nbin);
		  ensemble_t src = rescale_ensemble($1, 1./factor);
  		  ensemble_t dst = apply_pow_ensemble(src, $3);
		  $$ = rescale_ensemble(dst, factor);
 		}
	|	SHIFT '(' expression ',' const_expression ')'
		{
  		  $$ = shift_ensemble($3,(int)($5));
		}
	|	CSHIFT '(' expression ',' const_expression ')'
		{
  		  $$ = cshift_ensemble($3,(int)($5));
		}
	|	EXTRACT '(' expression ',' const_expression ',' const_expression ')'
		{
  		  $$ = extract_ensemble($3,(int)($5),(int)($7));
		}
	|	EXTRACT '(' expression ',' const_expression ')'
		{
  		  $$ = extract_ensemble($3,(int)($5),(int)($5));
		}
	|	CAT '(' expression ',' expression ')'
		{
  		  $$ = concatenate_ensemble($3,$5);
		}
	|	REAL '(' expression ')'
		{
  		  $$ = real_part_ensemble($3);
		}
	|	IMAG '(' expression ')'
		{
  		  $$ = imag_part_ensemble($3);
		}
	|	CONJ '(' expression ')'
		{
  		  $$ = conj_ensemble($3);
		}
	|	NORM2 '(' expression ')'
		{
		  double factor = rescale_factor($3->nbin);
		  ensemble_t src = rescale_ensemble($3, 1./factor);
  		  ensemble_t dst = norm2_ensemble(src);
		  $$ = rescale_ensemble(dst, factor);
		}
	|	TIMESI '(' expression ')'
		{
  		  $$ = timesI_ensemble($3);
		}
	|	ATAN2 '(' expression ',' expression ')'
		{
		  double factor = rescale_factor($3->nbin);
		  ensemble_t src1 = rescale_ensemble($3, 1./factor);
		  ensemble_t src2 = rescale_ensemble($5, 1./factor);
		  ensemble_t dst  = atan2_ensemble(src1,src2);
		  $$ = rescale_ensemble(dst, factor);
		}
	|	CMPLX '(' expression ',' expression ')'
		{
  		  $$ = cmplx_ensemble($3,$5);
		}
	|	CMPLX '(' const_expression ',' expression ')'
		{
		  ensemble_t src1 = promote_const_to_ensemble($3,$5->nbin,$5->length);
  		  $$ = cmplx_ensemble(src1,$5);
		}
	|	CMPLX '(' expression ',' const_expression ')'
		{
		  ensemble_t src2 = promote_const_to_ensemble($5,$3->nbin,$3->length);
  		  $$ = cmplx_ensemble($3,src2);
		}
	|	'(' expression ')'
		{
		  $$ = $2;
		}
	|	NAME
		{
		  $$ = read_ensemble($1->name);
		}
	|	NAME '(' expression ')'
		{
		  if ($1->funcptr)
	          {
		    double factor = rescale_factor($3->nbin);
		    ensemble_t src = rescale_ensemble($3, 1./factor);
  		    ensemble_t dst = apply_func_ensemble($1->funcptr, src);
		    $$ = rescale_ensemble(dst, factor);
		  }
		  else
		  {
 		    fprintf(stderr,"%s not a function\n", $1->name);
		    exit(1);
		  }
		}
	;
%%

void yyerror(char *errmsg)
{
  fprintf(stderr, "%s\n", errmsg);
}
