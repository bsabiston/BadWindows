

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





/* File ploty.c

   Written by    Russell Greenlee   at the Visible Language Workshop,  MIT     1987

   Contains the two routines to plot lines with -1 <= slope <= 1.

   See main.c, line.c, plotx.c
*/



#include <math.h>
#include <starbase.c.h>
#include "aaline.h"

extern void (*point1)();
void plot_y();
void plot_y2();



/* plots lines with  1 <= slope
*/

void plot_y (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge;

{ int error, error2_n, error2_f, s1, x, offset;
  register int xc, yc;
  int err, err2_n, err2_f;
  register int near, near2, far, far2, endy;
  int temp;


  x = ax - ax_off;
  yc = ay - ay_off;

  error = round (delx * (ax - x) - dely * (ay - yc));                           /* start at ax + a_off */
  error2_n = round ((ax - x) * delx1 + (ay - yc) * dely1) + 65536 - fudge; 
  error2_f = round ((bx - x) * delx2 + (by - yc) * dely2) + 65536 + fudge;
  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */

  s1 = (delx >> 1) - dely;

  near = (error >>12) + offset;
  near2 = (error2_n >>12);
  far2 = error2_f >>12;

  endy = ceil (by + by_off);
  for (; yc < endy; ++yc)                                      /* fill middle segment of line */
  { err = error;
    err2_n = error2_n;
    err2_f = error2_f;
    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;

    /* fill column to the left of the center line */
    for (xc = x; (near < 32) && ((far2 > -1) || (delx2 > -1)) && ((near2 < 32) || (delx1 < 0)); --xc)
    {
      if ((near2 < far2) && aa_clip (xc, yc))
      {
	(*point1) (xc, yc, near, far, near2, far2, r, g, b, t);
      }

      err += delx;
      err2_n += delx1;
      err2_f += delx2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = (err2_n >>12);
      far2 = err2_f >>12;
    }

    err = error - delx;
    err2_n = error2_n - delx1;
    err2_f = error2_f - delx2;
    
    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;

    /* fill column to the right of the center line */
    for (xc = x + 1; (far > -1) && ((near2 < 32) || (delx1 > -1)) && ((far2 > -1) || (delx2 < 0)); ++xc)
    { 

      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, t);
      }

      err -= delx;
      err2_n -= delx1;
      err2_f -= delx2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }

    if (error > s1)
    { ++x;
      error -= delx;
      error2_n -= delx1;
      error2_f -= delx2;
    }

    error += dely;
    error2_n -= dely1;
    error2_f -= dely2;
  }

  /* restore original order */
/********
  if (temp2) {
  swap(ax, bx, temp);
  swap(ay, by, temp);
  swap(delx1, delx2, temp);
  swap(dely1, dely2, temp);
  }
***********/

}





/* plots lines with slope -1 >= slope 
*/

void plot_y2 (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge;

{ int error, error2_n, error2_f, s1, x, offset;
  register int xc, yc;
  int err, err2_n, err2_f;
  register int near, near2, far, far2, endy;
  int temp;


  x = ax + ax_off;
  yc = ay - ay_off;

  error = round (delx * (ax - x) - dely * (ay - yc));                          /* start at ax + ax_off */
  error2_n = round ((ax - x) * delx1 + (ay - yc) * dely1) + 65536 - fudge; 
  error2_f = round ((bx - x) * delx2 + (by - yc) * dely2) + 65536 + fudge;
  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */

  s1 = (delx >> 1) + dely;

  near = (error >>12) + offset;
  near2 = (error2_n >>12);
  far2 = error2_f >>12;

  endy = ceil (by + by_off);
  for (; yc < endy; ++yc)                                      /* fill middle segment of line */
  { err = error;
    err2_n = error2_n;
    err2_f = error2_f;
    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;
    
    /* fill column to the left of the center line */
    for (xc = x; (near < 32) && ((near2 < 32) || (delx1 < 0)) && ((far2 > -1) || (delx2 > -1)); --xc)
    {
      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, t);
      }

      err += delx;
      err2_n += delx1;
      err2_f += delx2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = (err2_n >>12);
      far2 = err2_f >>12;
    }

    err = error - delx;
    err2_n = error2_n - delx1;
    err2_f = error2_f - delx2;

    near = (err >>12) + offset;
    far = near + width;
    near2 = err2_n >>12;
    far2 = err2_f >>12;

    /* fill column to the right of the center line */
    for (xc = x + 1; (far > -1) && ((near2 < 32) || (delx1 > -1)) && ((far2 > -1) || (delx2 < 0)); ++xc)
    {
      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, t);
      }

      err -= delx;
      err2_n -= delx1;
      err2_f -= delx2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }

    if (error < s1)
    { --x;
      error += delx;
      error2_n += delx1;
      error2_f += delx2;
    }

    error += dely;
    error2_n -= dely1;
    error2_f -= dely2;
  }

  /* restore original order */
/**********
  swap(ax, bx, temp);
  swap(ay, by, temp);
  swap(delx1, delx2, temp);
  swap(dely1, dely2, temp);
  dely = - dely;
  delx = - delx;
**********/

}
