#include <stdio.h>
#include <dq.h>
#include <cie.h>
 
    
#include <starbase.c.h>
#include <math.h>
#include <munsell.h>


int rgbmun (r, g, b, H, V, S)
int r, g, b;
float *H, *V, *S;
{
  int Valid;
  float x, y, Y, h, v, s;

/*  printf ("\nRGBMUN  r %d  g %d  b %d", r, g, b); */

  rgbcie (r, g, b, &x, &y, &Y);

  Valid = ciemun ((float)x, (float)y, (float)Y, &h, &v, &s);

/*  if (Valid == BADCIE) {
    *H = *V = *S = 0;
    printf ("\nrgbmun() BADCIE!");
    return (FALSE);
  }
  else {
    *H = h;  *V = v;  *S = s;
    return (TRUE);
  }*/

    *H = h;  *V = v;  *S = s;
    return (0);

}



