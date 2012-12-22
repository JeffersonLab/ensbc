/*
 * $Id: solve.c,v 1.2 1996/09/08 17:42:23 edwards Exp $ ($Date: 1996/09/08 17:42:23 $)
 * 
 */
#include "ensbc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000
#define MAXORDER 10

double func(double x, int order, double *coeff)
{
  int i;
  double fnx;

  fnx = coeff[0];

  for(i=1; i<=order; ++i)
  {
    fnx += pow(x,(double)i) * coeff[i];
  }

  printf("func(%f) = %f\n", x, fnx);

  return fnx;
}

double dfunc(double x, int order, double *coeff)
{
  int i;
  double fnx;

  fnx = coeff[1];

  for(i=2; i<=order; ++i)
  {
    fnx += pow(x,(double)(i-1)) * coeff[i] * (double)i;
  }

  printf("dfunc(%f) = %f\n", x, fnx);

  return fnx;
}

double newton(double x, int order, double *coeff)
{
  double  xn = x;
  int  convP = 0;
  int  iter  = 0;

  while (convP == 0)
  {
    ++iter;

    x = xn;
    xn = x - func(x, order, coeff) / dfunc(x, order, coeff);

    printf("iter = %d  x = %f\n", iter, xn);

    if (fabs(x-xn) < 0.00001) convP = 1;
  }
  
  return xn;
}

ensemble_t solve(int order, double r, ensemble_t ens_tmp[MAXORDER])
{
  ensemble_t dst;
  ensemble_t ens[MAXORDER];
  double     coeff[MAXORDER];
  double     guess = 1.0;
  double     factor;
  char crap[MAXLINE];
  int  i, b, nbin;
  FILE *fp;
  
  nbin = ens[0]->nbin;
  factor = rescale_factor(nbin);

  for(i = 0; i <= order; ++i)
  {
    ens[i] = rescale_ensemble(ens_tmp[i], 1./factor);
  }

  dst = new_ensemble(ens[0]);

  for(b = 0; b < nbin; ++b)
  {
    for(i = 0; i <= order; ++i)
    {
      coeff[i] = ens[i]->data[b];
      printf("coeff[%d] = %f\n", i, coeff[i]);
    }

    dst->data[b] = newton(guess, order, coeff);
  }
    
  return dst;
}

int main()
{
  ensemble_t  ens[MAXORDER];
  ensemble_t  xcoord;
  int    nbin, len, i, order;
  double ratio;
  char   file[MAXLINE];
  char   outfile[MAXLINE];

  scanf("%d", &order);
  scanf("%f", &ratio);
  scanf("%s", outfile);

  for(i = 0; i <= order; ++i)
  {
    if (i != 1)
    {
      scanf("%s", file);
      ens[i] = read_ensemble(file);
    }
    else
    {
      nbin = ens[0]->nbin;
      len  = ens[0]->length;
      ens[i] = promote_const_to_ensemble(-ratio, nbin, len);
    }
  }

  xcoord = solve(order, ratio, ens);
  write_ensemble(outfile, xcoord);

  return 0;
}

