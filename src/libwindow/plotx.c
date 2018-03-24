

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





/* File plotx.c

   Written by    Russell Greenlee   at the Visible Language Workshop,  MIT     1987


   Contains the two routines to plot lines with -1 <= slope <= 1.

   See files main.c, line.c, and ploty.c
*/



#include <math.h>
#include <starbase.c.h>
#include "aaline.h"

extern void (*point1)();
void plot_x();
void plot_x2();


/* plots lines with 0 >= slope >= 1
*/

void plot_x (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, delx, dely, delx1, dely1, delx2, dely2, 
	     width, r, g, b, t, fudge)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge;

{ int error, error2_n, error2_f, s1, y, offset;
  register int xc, yc;
  int err, err2_n, err2_f;
  register int near, near2, far, far2, endx;

    
  xc = ax - ax_off;
  y = ay - ay_off;

  error = round (- delx * (ax - xc) + dely * (ay - y));        /* start at ax + a_off */
  error2_n = round ((ax - xc) * delx1 + (ay - y) * dely1) + 65536 - fudge; 
  error2_f = round ((bx - xc) * delx2 + (by - y) * dely2) + 65536 + fudge;

  offset = 16 - (width >>1); /* computes dist from edge of pixel to near edge of line */

  s1 = (dely >> 1) - delx;

  endx = ceil (bx + bx_off);
  for (; xc < endx; ++xc)                                 /* fill middle segment of line */
  { err = error;
    err2_n = error2_n;
    err2_f = error2_f;
    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;
    
    /* fill column above center line */
    for (yc = y; (near < 32) && ((far2 > -1) || (dely2 > -1)) && ((near2 < 32) || (dely1 < 0)); --yc)
    { 	
      if ((near2 < far2) && aa_clip (xc, yc))
	{ (*point1) (xc, yc, near, far, near2, far2, r, g, b, t);
	}

      err += dely;
      err2_n += dely1;
      err2_f += dely2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = (err2_n >>12);
      far2 = err2_f >>12;
    }
    
    err = error - dely;
    err2_n = error2_n - dely1;
    err2_f = error2_f - dely2;
    
    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;
    
    /* fill column below center line */
    for (yc = y + 1; (far > -1) && ((near2 < 32) || (dely1 > -1)) && ((far2 > -1) || (dely2 < 0)); ++yc) 
    {
      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, t);
      }

      err -= dely;
      err2_n -= dely1;
      err2_f -= dely2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }
    
    if (error > s1)
    { ++y;
      error -= dely;
      error2_n -= dely1;
      error2_f -= dely2;
    }
    
    error += delx;
    error2_n -= delx1;
    error2_f -= delx2;
  }
}


/* plots lines with -1 <= slope <= 0 
*/

void plot_x2 (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge;

{ int error, error2_n, error2_f, s1, y, offset;
  register int xc, yc;
  int err, err2_n, err2_f;
  register int near, near2, far, far2, endx;

  y = ay + ay_off;
  xc = ax - ax_off;

  error = round (- delx * (ax - xc) + dely * (ay - y));                               /* start at ax + 1 */
  error2_n = round ((ax - xc) * delx1 + (ay - y) * dely1) + 65536 - fudge;            /* fudge ends for proper overlap */
  error2_f = round ((bx - xc) * delx2 + (by - y) * dely2) + 65536 + fudge;

  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */
  
  s1 = - (dely >> 1) - delx;

  endx = round (bx + bx_off);
  for (; xc < endx; ++xc)                                      /* fill middle segment of line */
  { err = error;
    err2_n = error2_n;
    err2_f = error2_f;
    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;

    /* fill column above center line */
    for (yc = y; (near < 32) && ((far2 > -1) || (dely2 > -1)) && ((near2 < 32) || (dely1 < 0)) ; --yc)  
    { 
      if ((near2 < far2) && aa_clip (xc, yc))
	(*point1) (xc, yc, near, far, near2, far2, r, g, b, t);

      err += dely;
      err2_n += dely1;
      err2_f += dely2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }

    err = error - dely;
    err2_n = error2_n - dely1;
    err2_f = error2_f - dely2;

    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;

    /* fill column below center line */
    for (yc = y + 1; (far > -1) && ((near2 < 32) || (dely1 > -1)) && ((far2 > -1) || (dely2 < 0)); ++yc)
    {
      if ((near2 < far2) && aa_clip (xc, yc))
	(*point1) (xc, yc, near, far, near2, far2, r, g, b, t);

      err -= dely;
      err2_n -= dely1;
      err2_f -= dely2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }

    if (error < s1)
    { --y;
      error += dely;
      error2_n += dely1;
      error2_f += dely2;
    }

    error += delx;
    error2_n -= delx1;
    error2_f -= delx2;
  }
}
