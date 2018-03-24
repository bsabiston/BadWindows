

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





#include<stdio.h>
#include<cie.h>

#define DEBUG 0





/*Stephanie Houde 7/13/86
        This function takes cie color coordinates and converts them to rgb
        space color coordinates.
        cie boundaries look like this:
                0 <= r <= 255
                0 <= g <= 255
                0 <= b <= 255
        if the rgb values are out of bounds, -1 is returned   */


/*--The folowing definitions sit now in cie.h  DB-8-23-90--*/

#ifdef(0)
/*CIE chromaticity coefficients for graphics monitor primaries*/
#define RX 0.628
#define RY 0.346
#define RZ (1-RX-RY)

#define GX 0.268
#define GY 0.588
#define GZ (1-GX-GY)

#define BX 0.150
#define BY 0.070
#define BZ (1-BX-BY)

/*CIE-to-RGB transformation determinant*/
/*#define KD  (RX*((GY*BZ)-(BY*GZ))+GX*((BZ*RZ)-(RY*BZ))+BX*((RY*GZ)-(GY*RZ)))*/

#define	KD  (RX*((GY*BZ)-(BY*GZ))+GX*((BY*RZ)-(RY*BZ))+BX*((RY*GZ)-(GY*RZ)))

/*CIE-to-RGB transformation constants*/
#define	K1  (((GY*BZ)-(BY*GZ))/KD)
#define	K2  (((BX*GZ)-(GX*BZ))/KD)
#define	K3  (((GX*BY)-(BX*GY))/KD)
#define	K4  (((BY*RZ)-(RY*BZ))/KD)
#define	K5  (((RX*BZ)-(BX*RZ))/KD)
#define	K6  (((BX*RY)-(RX*BY))/KD)
#define	K7  (((RY*GZ)-(GY*RZ))/KD)
#define	K8  (((GX*RZ)-(RX*GZ))/KD)
#define	K9  (((RX*GY)-(GX*RY))/KD)
	
/* total CIE chromacities which would apply to GRAPHICS MONITOR RGB primaries
  when alligned with ILLUMINANT D 6500 (factory alligned standard) */
/*  I changed these numbers for the bobcats -dave small 10/5/88 
#define	XW 0.950
#define YW 1.000
#define ZW 1.089  */

/* total CIE chromaticities which would apply to GRAPHIC MONITOR RGB primaries
   when alligned with illuminant C (overcast sky at midday)*/
#define	XW 0.981
#define YW 1.000
#define ZW 1.182 

#define TR ((K1*XW) + (K2*YW) + (K3*ZW))
#define TG ((K4*XW) + (K5*YW) + (K6*ZW))
#define TB ((K7*XW) + (K8*YW) + (K9*ZW))
 
#endif
    



ciergb(x,y,Y,r,g,b)
float   x,y,Y;  /*CIE specification */
int     *r,*g,*b; /*RGB color values*/
{
 
  register float  xc,zc;    /*(x,y,z)CIE chromaticity values*/
  double  floor();
  int count = 1;

#if DEBUG
  printf ("\n----%d", count);
  count++;
#endif

  /*calculate full set of CIE chromaticity values */
  Y *= (255.0)/(100.0);
  xc = (x/y)*Y;
  zc = (Y/y)-xc-Y;
  
#if DEBUG
  printf ("\n----%d", count);
  count++;
#endif

  /*convert CIE chromaticity values to RGB color data values*/
  *r = (int)floor((((K1/TR)*xc)+((K2/TR)*Y)+((K3/TR)*zc)) + 0.5);
  *g = (int)floor((((K4/TG)*xc)+((K5/TG)*Y)+((K6/TG)*zc)) + 0.5);
  *b = (int)floor((((K7/TB)*xc)+((K8/TB)*Y)+((K9/TB)*zc)) + 0.5);

#if DEBUG
  printf ("\n----%d", count);
  count++;
#endif
  
  if((*r<0)||(*r>255)||(*g<0)||(*g>255)||(*b<0)||(*b>255)) {
    return(-1);
    /*
      if (*r < 0) *r = 0;
      if (*r > 255) *r = 255;
      if (*g < 0) *g = 0;
      if (*g > 255) *g = 255;
      if (*b < 0) *b = 0;
      if (*b > 255) *b = 255;
      */
  }

#if DEBUG
  printf ("\n----%d", count);
  count++;
#endif  
  
  return( 0 );
  
}





ciergb2(x,y,Y,r,g,b)
     float   x,y,Y;  /*CIE specification */
     float    *r,*g,*b; /*RGB color values*/
{
  
  register float  xc,zc;    /*(x,y,z)CIE chromaticity values*/
  double  floor();
  
  /*calculate full set of CIE chromaticity values */
  Y *= (255.0)/(100.0);
  xc = (x/y)*Y;
  zc = (Y/y)-xc-Y;
  
  /*convert CIE chromaticity values to RGB color data values*/
  *r = (((K1/TR)*xc)+((K2/TR)*Y)+((K3/TR)*zc));
  *g = (((K4/TG)*xc)+((K5/TG)*Y)+((K6/TG)*zc));
  *b = (((K7/TB)*xc)+((K8/TB)*Y)+((K9/TB)*zc));
  
  if((*r<0)||(*r>255)||(*g<0)||(*g>255)||(*b<0)||(*b>255)) {
    if (*r < 0) *r = 0;
    if (*g < 0) *g = 0;
    if (*b < 0) *b = 0;
  }
  
  
  return( 0 );
  
}
