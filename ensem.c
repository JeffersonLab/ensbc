/*
 * $Id: ensem.c,v 1.30 2008/11/17 16:41:23 edwards Exp $ ($Date: 2008/11/17 16:41:23 $)
 *
 * Ensbc - Routines to manipulate ensembles
 */
 
#include "ensbc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXENSEM  1000
static ensemble_t ensemble_stack[MAXENSEM];
static int  ensemble_stack_ptr = 0;

int MAX(int x, int y)
{
  return ((x < y) ? y: x);
}

int MIN(int x, int y)
{
  return ((x < y) ? x: y);
}


/* Promote type of data */
datatype_t promote_type(datatype_t src1, datatype_t src2)
{
  datatype_t type = RealType;  /* just to make compiler happy */

  if (src1 == RealType && src2 == RealType)
    type = RealType;
  else if (src1 == RealType && src2 == ComplexType)
    type = ComplexType;
  else if (src1 == ComplexType && src2 == RealType)
    type = ComplexType;
  else if (src1 == ComplexType && src2 == ComplexType)
    type = ComplexType;
  else
  {
    fprintf(stderr, "some unknown types in concatenate\n");
    exit(1);
  }

  return type;
}


/* Return the proper rescaling factor */
double rescale_factor(int num)
{
  double factor;

  /* Rescaling factor */
#ifdef JACKKNIFE
  factor = -(num - 1);
#else
  factor = sqrt(num - 1);
#endif

  return factor;
}


/* Push an ensemble onto the stack */
void push_ensemble(ensemble_t src)
{
  if (src == NULL)
  {
    fprintf(stderr, "pointer is NULL in free_ensemble\n");
    exit(1);
  }

  if (ensemble_stack_ptr == MAXENSEM)
  {
    fprintf(stderr, "too many ensembles allocated: %d\n", ensemble_stack_ptr);
    exit(1);
  }

  ensemble_stack[ensemble_stack_ptr++] = src;
}

/* Create a new ensemble of some given number of bins and length */
static ensemble_t malloc_ensemble(datatype_t type, int nbin, int length)
{
  ensemble_t dst = (ensemble_t)malloc(sizeof(struct ensemble));

  if (dst == NULL)
  {
    fprintf(stderr, "malloc returned NULL in malloc_ensemble\n");
    exit(1);
  }

  if (nbin <= 0 || length <= 0) 
  {
    fprintf(stderr, "malloc returned NULL in malloc_ensemble\n");
    exit(1);
  }

  dst->data = (complex_t *)malloc(sizeof(complex_t)*nbin*length);
  if (dst == NULL)
  {
    fprintf(stderr, "malloc returned NULL in malloc_ensemble\n");
    exit(1);
  }

  dst->type   = type;
  dst->nbin   = nbin;
  dst->length = length;

  return dst;
}

/* Create a new ensemble using parameters from source */
ensemble_t new_ensemble(ensemble_t src)
{
  ensemble_t dst = malloc_ensemble(src->type, src->nbin, src->length);

  push_ensemble(dst);

  return dst;
}

/* Create a new ensemble of length 1 using the src as input */
ensemble_t new_len1_ensemble(ensemble_t src)
{
  ensemble_t dst = malloc_ensemble(src->type, src->nbin, 1);

  push_ensemble(dst);

  return dst;
}

/* Free an ensemble */
void free_ensemble(ensemble_t src)
{
  if (src == NULL)
  {
    fprintf(stderr, "pointer is NULL in free_ensemble\n");
    exit(1);
  }

  if (src->data == NULL)
  {
    fprintf(stderr, "ensemble is fouled up in free_ensemble\n");
    exit(1);
  }

  free((void *)(src->data));
  free((void *)src);
}

/* Free all registered ensemble */
void free_all_ensembles(void)
{
  while(ensemble_stack_ptr > 0)
    free_ensemble(ensemble_stack[--ensemble_stack_ptr]);
}

/* Promote constant to ensemble */
ensemble_t promote_const_to_ensemble(double dval, int nbin, int len)
{
  ensemble_t dst = malloc_ensemble(RealType, nbin, len);
  int  n, k;

  for(n = 0; n < nbin; ++n)
  {
    for(k = 0; k < len; ++k)
    {
      dst->data[k+n*len].real = dval;
      dst->data[k+n*len].imag = 0.0;
    }
  }

  return dst;
}


/* Check if two ensemble have the same parameters */
int check_two_ensemble(ensemble_t src1, ensemble_t src2)
{
  if (src1->nbin != src2->nbin)
  {
    return -1;
  }

  if (src1->length == src2->length)
  {
    return 0;
  }
  else if (src1->length == 1 || src2->length > 1) 
  {
    return 1;
  }
  else if (src1->length > 1 || src2->length == 1) 
  {
    return 2;
  }
  else
  {
    return -1;
  }
}

/* Return a new rescaled ensemble */
ensemble_t rescale_ensemble(ensemble_t src, double factor)
{
  ensemble_t dst = new_ensemble(src);
  complex_t  avg;
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  for(k = 0; k < len; ++k)
  {
    avg.real = 0.0;
    avg.imag = 0.0;

    for(n = 0; n < num; ++n)
    {
      avg.real += src->data[k+len*n].real;
      avg.imag += src->data[k+len*n].imag;
    }

    avg.real /= (double)num;
    avg.imag /= (double)num;

    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = avg.real + (src->data[k+len*n].real - avg.real)*factor;
      dst->data[k+len*n].imag = avg.imag + (src->data[k+len*n].imag - avg.imag)*factor;
    }
  }

  return dst;
}

/* Add constant on an ensemble */
ensemble_t add_const_to_ensemble(double val, ensemble_t src2)
{
  ensemble_t dst = new_ensemble(src2);
  int  num = src2->nbin;
  int  len = src2->length;
  int  n, k;

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = val + src2->data[k+len*n].real;
      dst->data[k+len*n].imag = src2->data[k+len*n].imag;
    }
  }

  return dst;
}

/* Add two ensembles */
ensemble_t add_two_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  num = src1->nbin;
  int  len1 = src1->length;
  int  len2 = src2->length;
  int  len, n, k, k1, k2;

  switch (check_two_ensemble(src1, src2))
  {
  case 0:
  case 2:
    dst = new_ensemble(src1);
    break;

  case 1:
    dst = new_ensemble(src2);
    break;
    
  default:
    fprintf(stderr, "ensembles not compatible\n");
    exit(1);
  }

  dst->type = promote_type(src1->type, src2->type);

  len = MAX(len1,len2);

  for(k = 0; k < len; ++k)
  {
    k1 = MIN(k,len1-1);
    k2 = MIN(k,len2-1);

    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = src1->data[k1+len1*n].real + src2->data[k2+len2*n].real;
      dst->data[k+len*n].imag = src1->data[k1+len1*n].imag + src2->data[k2+len2*n].imag;
    }
  }

  return dst;
}

/* Subtract two ensembles */
ensemble_t subtract_two_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  num = src1->nbin;
  int  len1 = src1->length;
  int  len2 = src2->length;
  int  len, n, k, k1, k2;

  switch (check_two_ensemble(src1, src2))
  {
  case 0:
  case 2:
    dst = new_ensemble(src1);
    break;

  case 1:
    dst = new_ensemble(src2);
    break;
    
  default:
    fprintf(stderr, "ensembles not compatible\n");
    exit(1);
  }

  dst->type = promote_type(src1->type, src2->type);

  len = MAX(len1,len2);

  for(k = 0; k < len; ++k)
  {
    k1 = MIN(k,len1-1);
    k2 = MIN(k,len2-1);

    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = src1->data[k1+len1*n].real - src2->data[k2+len2*n].real;
      dst->data[k+len*n].imag = src1->data[k1+len1*n].imag - src2->data[k2+len2*n].imag;
    }
  }

  return dst;
}

/* Multiply a constant on an ensemble */
ensemble_t multiply_const_to_ensemble(double val, ensemble_t src2)
{
  ensemble_t dst = new_ensemble(src2);
  int  num = src2->nbin;
  int  len = src2->length;
  int  n, k;

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = val * src2->data[k+len*n].real;
      dst->data[k+len*n].imag = val * src2->data[k+len*n].imag;
    }
  }

  return dst;
}

/* Multiply two ensembles */
ensemble_t multiply_two_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  num = src1->nbin;
  int  len1 = src1->length;
  int  len2 = src2->length;
  int  len, n, k, k1, k2;

  switch (check_two_ensemble(src1, src2))
  {
  case 0:
  case 2:
    dst = new_ensemble(src1);
    break;

  case 1:
    dst = new_ensemble(src2);
    break;
    
  default:
    fprintf(stderr, "ensembles not compatible\n");
    exit(1);
  }

  dst->type = promote_type(src1->type, src2->type);

  len = MAX(len1,len2);

  for(k = 0; k < len; ++k)
  {
    k1 = MIN(k,len1-1);
    k2 = MIN(k,len2-1);

    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = 
	  src1->data[k1+len1*n].real * src2->data[k2+len2*n].real
	- src1->data[k1+len1*n].imag * src2->data[k2+len2*n].imag;
      dst->data[k+len*n].imag = 
          src1->data[k1+len1*n].real * src2->data[k2+len2*n].imag
	+ src1->data[k1+len1*n].imag * src2->data[k2+len2*n].real;
    }
  }

  return dst;
}

/* Divide two ensembles */
ensemble_t divide_two_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  num = src1->nbin;
  int  len1 = src1->length;
  int  len2 = src2->length;
  int  len, n, k, k1, k2;

  switch (check_two_ensemble(src1, src2))
  {
  case 0:
  case 2:
    dst = new_ensemble(src1);
    break;

  case 1:
    dst = new_ensemble(src2);
    break;
    
  default:
    fprintf(stderr, "add: ensembles not compatible\n");
    exit(1);
  }

  dst->type = promote_type(src1->type, src2->type);

  len = MAX(len1,len2);

  for(k = 0; k < len; ++k)
  {
    k1 = MIN(k,len1-1);
    k2 = MIN(k,len2-1);

    /* For efficiency, split into real and complex */
    switch (src2->type)
    {
    case RealType:
      for(n = 0; n < num; ++n)
      {
	dst->data[k+len*n].real = src1->data[k1+len1*n].real / src2->data[k2+len2*n].real;
	dst->data[k+len*n].imag = src1->data[k1+len1*n].imag / src2->data[k2+len2*n].real;
      }
      break;

    case ComplexType:
      for(n = 0; n < num; ++n)
      {
	double denom = 1.0 / 
	   (src2->data[k2+len2*n].real * src2->data[k2+len2*n].real
	  + src2->data[k2+len2*n].imag * src2->data[k2+len2*n].imag);
	
	dst->data[k+len*n].real = 
	  (src1->data[k1+len1*n].real * src2->data[k2+len2*n].real
	 + src1->data[k1+len1*n].imag * src2->data[k2+len2*n].imag) * denom;
	dst->data[k+len*n].imag = 
	  (src1->data[k1+len1*n].imag * src2->data[k2+len2*n].real
	 - src1->data[k1+len1*n].real * src2->data[k2+len2*n].imag) * denom;
      }
      break;
    
    default:
      fprintf(stderr, "something wrong with src2 type: type=%d\n", src2->type);
      exit(1);
    }
  }

  return dst;
}

/* Negate ensemble */
ensemble_t negate_ensemble(ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = - src->data[k+len*n].real;
      dst->data[k+len*n].imag = - src->data[k+len*n].imag;
    }
  }

  return dst;
}


/* Real part ensemble */
ensemble_t real_part_ensemble(ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  dst->type = RealType;

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = src->data[k+len*n].real;
      dst->data[k+len*n].imag = 0.0;
    }
  }

  return dst;
}

/* Imag part ensemble */
ensemble_t imag_part_ensemble(ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  dst->type = RealType;

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = src->data[k+len*n].imag;
      dst->data[k+len*n].imag = 0.0;
    }
  }

  return dst;
}

/* Conjugate the ensemble */
ensemble_t conj_ensemble(ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  /* Decide based on the input type */
  switch (src->type)
  {
  case RealType:
    dst->type = RealType;
    
    for(k = 0; k < len; ++k)
    {
      for(n = 0; n < num; ++n)
      {
	dst->data[k+len*n].real =  src->data[k+len*n].real;
	dst->data[k+len*n].imag =  0.0;
      }
    }
    break;

  case ComplexType:
    dst->type = ComplexType;

    for(k = 0; k < len; ++k)
    {
      for(n = 0; n < num; ++n)
      {
	dst->data[k+len*n].real =  src->data[k+len*n].real;
	dst->data[k+len*n].imag = -src->data[k+len*n].imag;
      }
    }
    break;
    
  default:
    fprintf(stderr, "something wrong with src type: type=%d\n", src->type);
    exit(1);
  }

  return dst;
}

/* Norm2 the ensemble */
ensemble_t norm2_ensemble(ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  /* Decide based on the input type */
  switch (src->type)
  {
  case RealType:
    dst->type = RealType;
    
    for(k = 0; k < len; ++k)
    {
      for(n = 0; n < num; ++n)
      {
	double re = src->data[k+len*n].real;

	dst->data[k+len*n].real = re*re;
	dst->data[k+len*n].imag = 0.0;
      }
    }
    break;

  case ComplexType:
    dst->type = RealType;

    for(k = 0; k < len; ++k)
    {
      for(n = 0; n < num; ++n)
      {
	double re = src->data[k+len*n].real;
	double im = src->data[k+len*n].imag;

	dst->data[k+len*n].real = re*re + im*im;
	dst->data[k+len*n].imag = 0.0;
      }
    }
    break;
    
  default:
    fprintf(stderr, "something wrong with src type: type=%d\n", src->type);
    exit(1);
  }

  return dst;
}

/* Call atan2 on two real ensembles */
ensemble_t atan2_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  num = src1->nbin;
  int  len1 = src1->length;
  int  len2 = src2->length;
  int  len, n, k, k1, k2;

  switch (check_two_ensemble(src1, src2))
  {
  case 0:
  case 2:
    dst = new_ensemble(src1);
    break;

  case 1:
    dst = new_ensemble(src2);
    break;
    
  default:
    fprintf(stderr, "cmplx: ensembles not compatible\n");
    exit(1);
  }

  if (! (src1->type == RealType && src2->type == RealType))
  {
    fprintf(stderr, "atan2 requires both ensembles real\n");
    exit(1);
  }
  dst->type = RealType;

  len = MAX(len1,len2);

  for(k = 0; k < len; ++k)
  {
    k1 = MIN(k,len1-1);
    k2 = MIN(k,len2-1);

    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = atan2(src1->data[k1+len1*n].real, src2->data[k2+len2*n].real);
      dst->data[k+len*n].imag = 0.0;
    }
  }

  return dst;
}

/* Build complex from two real ensembles */
ensemble_t cmplx_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  num = src1->nbin;
  int  len1 = src1->length;
  int  len2 = src2->length;
  int  len, n, k, k1, k2;

  switch (check_two_ensemble(src1, src2))
  {
  case 0:
  case 2:
    dst = new_ensemble(src1);
    break;

  case 1:
    dst = new_ensemble(src2);
    break;
    
  default:
    fprintf(stderr, "cmplx: ensembles not compatible\n");
    exit(1);
  }

  if (! (src1->type == RealType && src2->type == RealType))
  {
    fprintf(stderr, "cmplx requires both ensembles real\n");
    exit(1);
  }
  dst->type = ComplexType;

  len = MAX(len1,len2);

  for(k = 0; k < len; ++k)
  {
    k1 = MIN(k,len1-1);
    k2 = MIN(k,len2-1);

    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = src1->data[k1+len1*n].real;
      dst->data[k+len*n].imag = src2->data[k2+len2*n].real;
    }
  }

  return dst;
}

/* Multiply ensemble by I */
ensemble_t timesI_ensemble(ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  dst->type = ComplexType;

  switch (src->type)
  {
  case RealType:
    for(k = 0; k < len; ++k)
    {
      for(n = 0; n < num; ++n)
      {
	dst->data[k+len*n].real = 0.0;
	dst->data[k+len*n].imag = src->data[k+len*n].real;
      }
    }
    break;

  case ComplexType:
    for(k = 0; k < len; ++k)
    {
      for(n = 0; n < num; ++n)
      {
	dst->data[k+len*n].real = - src->data[k+len*n].imag;
	dst->data[k+len*n].imag =   src->data[k+len*n].real;
      }
    }
    break;

  default:
    fprintf(stderr, "something wrong with ensemble: type=%d\n", src->type);
    exit(1);
  }

  return dst;
}


/* Read ensemble */
ensemble_t read_fileptr_ensemble(FILE *fp, char *name)
{
  ensemble_t dst;
  int  num;
  int  len;
  int  n, k;
  int  junk, ncol, ttype;
  datatype_t type;
#define MAXLINE 1000
  char crap[MAXLINE];
  
  n = 0;
  while((crap[n++]=fgetc(fp)) != '\n')
  {
    if (n == MAXLINE)
    {
      fprintf(stderr, "Header line too long\n");
      exit(1);
    }
  }

  if (sscanf(crap, "%d %d %d %d %d", &num, &len, &ttype, &junk, &ncol) != 5)
  {
    fprintf(stderr, "error reading parameters from %s\n", name);
    exit(1);
  }
  type = ttype;

  if (ncol != 1)
  {
    fprintf(stderr, "only support 1 column in %s\n", name);
    exit(1);
  }

  if (type != RealType && type != ComplexType)
  {
    fprintf(stderr, "error in type for file %s\n", name);
    exit(1);
  }

  dst = malloc_ensemble(type, num, len);

  for(n = 0; n < num; ++n)
  {
    int t;

    switch (type)
    {
    case RealType:
      for(k = 0; k < len; ++k)
      {
	if (fscanf(fp, "%d %lf", &t, &(dst->data[k+len*n].real)) != 2)
	{
	  fprintf(stderr, "error reading data from %s\n", name);
	  exit(1);
	}

	if (k != t)
	{
	  fprintf(stderr, "error reading time slice data from %s\n", name);
	  exit(1);
	}

	dst->data[k+len*n].imag = 0.0;
      }
      break;

    case ComplexType:
      for(k = 0; k < len; ++k)
      {
	if (fscanf(fp, "%d %lf %lf", &t, &(dst->data[k+len*n].real), &(dst->data[k+len*n].imag)) != 3)
	{
	  fprintf(stderr, "error reading data from %s\n", name);
	  exit(1);
	}

	if (k != t)
	{
	  fprintf(stderr, "error reading time slice data from %s\n", name);
	  exit(1);
	}
      }
      break;

    default:
      fprintf(stderr, "something wrong with ensemble: type=%d\n", type);
      exit(1);
    }
  }

  return dst;
}


/* Read ensemble from named file */
ensemble_t read_ensemble(char *name)
{
  ensemble_t dst;
  FILE *fp;
  
  fp = fopen(name, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "file %s does not exist\n", name);
    exit(1);
  }

  dst = read_fileptr_ensemble(fp, name);

  fclose(fp);

  return dst;
}

/* Write ensemble */
void write_ensemble(char *name, ensemble_t src)
{
  datatype_t type = src->type;
  int        num = src->nbin;
  int        len = src->length;
  int  n, k;
  FILE *fp;
  
  fp = fopen(name, "w");
  if (fp == NULL)
  {
    fprintf(stderr, "error opening file %s\n", name);
    exit(1);
  }

  fprintf(fp, "%d %d %d 0 1\n", num, len, type);

  for(n = 0; n < num; ++n)
  {
    switch (type)
    {
    case RealType:
      for(k = 0; k < len; ++k)
      {
	fprintf(fp, "%d %.12g\n", k, src->data[k+len*n].real);
      }
      break;

    case ComplexType:
      for(k = 0; k < len; ++k)
      {
	fprintf(fp, "%d %.12g %.12g\n", k, src->data[k+len*n].real, src->data[k+len*n].imag);
      }
      break;
 
    default:
      fprintf(stderr, "something wrong with ensemble: type=%d\n", type);
      exit(1);
    }
  }

  fclose(fp);
}


/* Apply function to ensemble */
ensemble_t apply_func_ensemble(double (*funcptr)(), ensemble_t src)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  if (src->type != RealType)
  {
    fprintf(stderr, "only func(real) not supported\n");
    exit(1);
  }

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = (funcptr)(src->data[k+len*n].real);
      dst->data[k+len*n].imag = 0.0;
    }
  }

  return dst;
}

/* Apply pow(src,const) to ensemble */
ensemble_t apply_pow_ensemble(ensemble_t src, double val)
{
  ensemble_t dst = new_ensemble(src);
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;

  if (src->type != RealType)
  {
    fprintf(stderr, "only func(real) not supported\n");
    exit(1);
  }

  for(k = 0; k < len; ++k)
  {
    for(n = 0; n < num; ++n)
    {
      dst->data[k+len*n].real = pow(src->data[k+len*n].real, val);
      dst->data[k+len*n].imag = 0.0;
    }
  }

  return dst;
}

/* Calculate mean, err and err/mean for data */
void calc_real_ensemble(ensemble_t src)
{
  double  avg;
  double  err;
  double  rat;
  double  diff;
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;
  static char *fmt[] = {"%d   %g %g   %g\n", "%4d   %- 13.6g %- 13.6g   %- 13.6g\n"};
  int  dofmt;

  dofmt = (len > 1) ? 1: 0;

  for(k = 0; k < len; ++k)
  {
    avg = 0.0;
    err = 0.0;
    
    for(n = 0; n < num; ++n)
    {
      avg += src->data[k+len*n].real;
    }

    avg /= (double)num;

    for(n = 0; n < num; ++n)
    {
      diff = (src->data[k+len*n].real - avg);
      err += diff * diff;
    }

    err = sqrt(err / (double)((num - 1) * num));
    if (avg != 0.0)
      rat = err / avg;
    else
      rat = 0.0;

    printf(fmt[dofmt], k, avg, err, rat);
  }
}

/* Calculate mean, err and err/mean for data */
void calc_complex_ensemble(ensemble_t src)
{
  complex_t  avg;
  double     err;
  complex_t  diff;
  int  num = src->nbin;
  int  len = src->length;
  int  n, k;
  static char *fmt[] = {"%d   ( %g , %g )   %g\n", "%4d   ( %- 13.6g , %- 13.6g )   %- 13.6g\n"};
  int  dofmt;

  dofmt = (len > 1) ? 1: 0;

  for(k = 0; k < len; ++k)
  {
    avg.real = avg.imag = 0.0;
    err = 0.0;
    
    for(n = 0; n < num; ++n)
    {
      avg.real += src->data[k+len*n].real;
      avg.imag += src->data[k+len*n].imag;
    }

    avg.real /= (double)num;
    avg.imag /= (double)num;

    for(n = 0; n < num; ++n)
    {
      diff.real = (src->data[k+len*n].real - avg.real);
      diff.imag = (src->data[k+len*n].imag - avg.imag);
      err += diff.real * diff.real  +  diff.imag * diff.imag;
    }

    err = sqrt(err / (double)((num - 1) * num));

    printf(fmt[dofmt], k, avg.real, avg.imag, err);
  }
}

/* Calculate mean, err and err/mean for data */
void calc_ensemble(ensemble_t src)
{
  switch (src->type)
  {
  case RealType:
    calc_real_ensemble(src);
    break;

  case ComplexType:
    calc_complex_ensemble(src);
    break;

  default:
    fprintf(stderr, "something wrong with ensemble: type=%d\n", src->type);
    exit(1);
  }
}

/* Print the ensemble (maybe for a pipe??) */
void print_ensemble(ensemble_t src)
{
  datatype_t type = src->type;
  int        num = src->nbin;
  int        len = src->length;
  int  n, k;
  FILE *fp;
  
  fp = stdout;
  if (fp == NULL)
  {
    fprintf(stderr, "something wrong with stdout\n");
    exit(1);
  }

  fprintf(fp, "%d %d %d 0 1\n", num, len, type);

  switch (type)
  {
  case RealType:
    for(n = 0; n < num; ++n)
    {
      for(k = 0; k < len; ++k)
      {
	fprintf(fp, "%d %.12g\n", k, src->data[k+len*n].real);
      }
    }
    break;

  case ComplexType:
    for(n = 0; n < num; ++n)
    {
      for(k = 0; k < len; ++k)
      {
	fprintf(fp, "%d %.12g %.12g\n", k, src->data[k+len*n].real, src->data[k+len*n].imag);
      }
    }
    break;

  default:
    fprintf(stderr, "something wrong with ensemble: type=%d\n", type);
    exit(1);
  }
}

/* Shift an ensemble in some direction dropping bits from the end */
ensemble_t shift_ensemble(ensemble_t src, int sh)
{
  ensemble_t dst = new_ensemble(src);
  int        num = src->nbin;
  int        len = src->length;
  int  n, k, kk;

  if (abs(sh) > len)
  {
    fprintf(stderr, "shift: do not allow the shift greater than the length\n");
    exit(1);
  }

  for(n = 0; n < num; ++n)
  {
    for(k = 0; k < len; ++k)
    {
      kk = (k + len + sh) % len;

      dst->data[k+len*n].real = src->data[kk+len*n].real;
      dst->data[k+len*n].imag = src->data[kk+len*n].imag;
    }

    /* Clean out the ends */
    if (sh > 0)
    {
      for(k = len-sh; k < len; ++k)
      {
	dst->data[k+len*n].real = 0.0;
	dst->data[k+len*n].imag = 0.0;
      }
    }
    else if (sh < 0)
    {
      for(k = 0; k < -sh; ++k)
      {
	dst->data[k+len*n].real = 0.0;
	dst->data[k+len*n].imag = 0.0;
      }
    }
  }

  return dst;
}

/* Periodic (circular) shift an ensemble in some direction */
ensemble_t cshift_ensemble(ensemble_t src, int sh)
{
  ensemble_t dst = new_ensemble(src);
  int        num = src->nbin;
  int        len = src->length;
  int  n, k, kk;

  for(n = 0; n < num; ++n)
  {
    for(k = 0; k < len; ++k)
    {
      kk = (k + len + sh) % len;

      dst->data[k+len*n].real = src->data[kk+len*n].real;
      dst->data[k+len*n].imag = src->data[kk+len*n].imag;
    }
  }

  return dst;
}

/* Extract a range of time slices from an ensemble */
ensemble_t extract_ensemble(ensemble_t src, int elem_i, int elem_f)
{
  ensemble_t dst;
  datatype_t type = src->type;
  int  num  = src->nbin;
  int  len  = src->length;
  int  dlen = elem_f - elem_i;
  int  k, n;

  if (elem_i < 0 || elem_i >= len)
  {
    fprintf(stderr, "index element out of bounds of ensemble: %d\n", elem_i);
    exit(1);
  }

  if (elem_f < 0 || elem_f >= len)
  {
    fprintf(stderr, "index element out of bounds of ensemble: %d\n", elem_f);
    exit(1);
  }

  if (elem_f < elem_i)
  {
    fprintf(stderr, "index element out of order in ensemble: %d %d\n", 
	    elem_i, elem_f);
    exit(1);
  }

  dlen = elem_f - elem_i + 1;
  dst = malloc_ensemble(type, num, dlen);

  for(n = 0; n < num; ++n)
    for(k = 0; k < dlen; ++k)
    {
      dst->data[k+dlen*n].real = src->data[k+elem_i+len*n].real;
      dst->data[k+dlen*n].imag = src->data[k+elem_i+len*n].imag;
    }

  return dst;
}


/* Concatenate two ensembles */
ensemble_t concatenate_ensemble(ensemble_t src1, ensemble_t src2)
{
  ensemble_t dst;
  int  k, n;
  int  len, num;
  datatype_t  type;

  if (src1->nbin != src2->nbin) {
    fprintf(stderr, "Ensembles not compatible for concatenation.\n");
    exit(1);
  }

  len  = src1->length + src2->length;
  num  = src1->nbin;
  type = promote_type(src1->type, src2->type);
  dst  = malloc_ensemble(type, num, len);

  for(n = 0; n < num; ++n) 
  {
    for(k = 0; k < src1->length; ++k) 
    {
      dst->data[k + n*len].real = src1->data[k + n*src1->length].real;
      dst->data[k + n*len].imag = src1->data[k + n*src1->length].imag;
    }
    for(k = 0; k < src2->length; ++k) 
    {
      dst->data[k+src1->length + n*len].real = src2->data[k + n*src2->length].real;
      dst->data[k+src1->length + n*len].imag = src2->data[k + n*src2->length].imag;
    }
  }

  return dst;
}

