

/******************************************************************************
Copyright 1990 by the Massachusetts Institute of Technology.  All 
rights reserved.

Developed by the Visible Language Workshop at the Media Laboratory, MIT, 
Cambridge, Massachusetts, with support from Hewlett Packard, DARPA, and Nynex.

For use by Suguru Ishizaki.  
This distribution is approved by Nicholas Negroponte, Director of 
the Media Laboratory, MIT.

Permission to use, copy, or modify these programs and their 
documentation for educational and research purposes only and 
without fee is hereby granted, provided that this copyright notice 
appears on all copies and supporting documentation.  For any other 
uses of this software, in original or modified form, including but not 
limited to distribution in whole or in part, specific prior permission 
must be obtained from MIT.  These programs shall not be used, 
rewritten, or adapted as the basis of a commercial software or 
hardware product without first obtaining appropriate licenses from 
MIT.  MIT makes no representations about the suitability of this 
software for any purpose.  It is provided "as is" without express or 
implied warranty."
******************************************************************************/





/*
 *      MUNRGB.C
 *
 *	h is Munsell HUE, ranging from 0 to 100
 *	l is Munsell Value, ranging from 0 to 12
 *	s is Munsell Chroma, ranging from 0 to 26
 *
 */

#include <starbase.c.h>
#include <math.h>
#include <munsell.h>

#define GAMMA 1.5

static int gamm_init = 1;
static int gamma_table[256];

int munrgb(h,s,l,r,g,b)
float h, s, l;
int *r, *g, *b;
{
  int Valid;
  float x, y, Y;
  int i;
      
  if (gamm_init) {
    for(i = 0; i < 256; i++)
      gamma_table[i] = ((int) (pow((i / 255.0), (1.0/1.5)) * 255.0));
    gamm_init = FALSE;
  }
  Valid = muncie(h, l, s, &x, &y, &Y);
  if (Valid == BADHVC) {
    /*printf ("\nmunrgb()........muncie() BADHVC");*/
    *r = *g = *b = 0;
    return (FALSE);
  }
  else if (Valid == BADCIE) {
     /*printf ("\nmunrgb()......muncie() BADCIE");*/
     *r = *g = *b = 0;
    return (FALSE);
  }
  else {
    if (ciergb(x, y, Y, r, g, b) == -1) {
      /*printf("\nmunrgb().....ciergb() returned -1");*/
      *r = *g = *b = 0;
      return (FALSE);
    }
    *r = gamma_table[*r];
    *g = gamma_table[*g];
    *b = gamma_table[*b];
    return (TRUE);
  }
}

int munrgb2(h,s,l,r,g,b)
float h, s, l;
float *r, *g, *b;
{
  int Valid;
  float x, y, Y;
  int i;
      
  Valid = muncie(h, l, s, &x, &y, &Y);
  if (Valid == BADHVC) {
    *r = *g = *b = 0;
    return (FALSE);
  }
  else if (Valid == BADCIE) {
    *r = *g = *b = 0;
    return (FALSE);
  }
  else {
    if (ciergb2(x, y, Y, r, g, b) == -1) {
      *r = *g = *b = 0;
      return (FALSE);
    }
    /*** do the gamma correction ***/
    *r = pow((*r / 255.0), (1.0/1.5)) * 255.0;
    *g = pow((*g / 255.0), (1.0/1.5)) * 255.0;
    *b = pow((*b / 255.0), (1.0/1.5)) * 255.0;
    return (TRUE);
  }
}







