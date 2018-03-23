

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





/***************************

  HAIRY.C
  David Small 3/89

  Contains modifications of Russell Greenlee's AA line
  routines to handle hairy brushes a la Steve Strassmann.
  Any confusion in this code is directly atributable to 
  Russell and Straz of course, and problems should be
  directed to /dev/nul

****************************/


#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include "aaline.h"

#define WAIT 0
#define START 1
#define DRAW 2
#define FUDGE 2500
#define MINLEN 1
#define radians(degrees) ((degrees) * M_PI / 180.0)



extern double factor;

extern int red, green, blue, trans;
extern double width1, width2;
extern int fudge, dofudge;
extern double blur;
extern double ax, ay, bx, by, cx, cy, state;      /* the points a, b, c */
extern double len_ab, len_bc;
extern double dx_ab, dy_ab, dx_bc, dy_bc;
extern int delx, dely, delx1, dely1, delx2, dely2;   /* error to sides, near & far end points respectively */
extern double ax_off, ay_off, bx_off, by_off;
extern double a1, a2, b1, b2;

/*void (*pointf)() = NULL;*/

void plot_x_h();                
void plot_y_h();                

extern void (*point1)();
void aa_move_h();
int  aa_draw_h();
void aa_done_h();
 




/* The following 3 routines are tuned to draw a series of connected lines of variable width
   with matching endpoints.  The parameters describing a line and its' end points are global
   variables.
*/




/*  move initializes the first point of a stroke to be drawn, and the line color and width.
*/

void aa_move_h (x, y, w)
double x, y, w;

{ int intensity, ff = 50;
  void point2();


  ax = x;                                                         /* init the first point */
  ay = y;
  a1 = 90.0;
  width1 = w;
  state = START;
  dofudge = TRUE;
}



/*  draw draws an anti-aliased line on the screen, if there are two points previously defined.
*/

int aa_draw_h (x, y, w, p)
double x, y, w;
float p;

{ double v1x, v2x, v1y, v2y, lena, lenb, ang1, ang2;
  
  if ((state == START)                     /* cannot draw the first line until we have the third point */
      && ((fabs (x - ax) > MINLEN) || (fabs (y - ay) > MINLEN))) /* make sure line is a minimum length */
  { bx = x;                                                          /* init the second point */
    by = y;
    width2 = w;
    state = DRAW;
    return (TRUE);
  }

  else if ((state == DRAW) &&                               /* we are in the middle of a series of lines */
	   ((fabs (x - bx) > MINLEN) || (fabs (y - by) > MINLEN))) /* make sure line is a minimum length */
  { cx = x;                                            /* init third point */
    cy = y;

    v1x = ax - bx;                        /* translate point b to the origin */
    v2x = cx - bx;
    v1y = ay - by;
    v2y = cy - by;
    lena = sqrt (v1x * v1x + v1y * v1y);  /* find the lengths of vectors a and b */
    lenb = sqrt (v2x * v2x + v2y * v2y);

    if (fabs (v1x) < 0.0000001)
      ang1 = 90.0;
    else
      if ((ang1 = 180.0 / M_PI * atan2 (v1y, v1x)) < 0.0)
	ang1 += 360.0;

    if (fabs (v2x) < 0.0000001)
      ang2 = 90.0;
    else
      if ((ang2 = 180.0 / M_PI * atan2 (v2y, v2x)) < 0.0)
	ang2 += 360.0;

    a2 = (ang2 - ang1) / 2.0;

    if (a2 < 0.0)
      a2 += 180.0;

    if (a2 < 45.0)
      a2 += 90.0;
    else if (a2 > 135.0)
      a2 -= 90.0;

    b1 = 180.0 - a2;

    aaline_h (ax, ay, bx, by, width1, red, green, blue, trans, a1, a2, p);

    ax = bx;
    ay = by;
    bx = cx;
    by = cy;
    a1 = b1;
    width1 = width2;
    width2 = w;

    return (TRUE);    
  }

  else if (state == DRAW) {                              /* we are in the 
middle of a series of lines */
/*    aablotch_h (x, y, width1 / 2, red, green, blue, trans, p);*/
    return (TRUE);    
  }
  else
    return (FALSE);
}

/* done draw the last segment of the stroke and prepares for the next one.
*/

void aa_done_h ()

{ int temp;

  if (state == DRAW)                                                        /* this should only follow a draw */
  { aaline_h (ax, ay, bx, by, width1, red, green, blue, trans, a1, 90.0, 0.0);
    state = WAIT;                                         /* ready to start the next stroke */
    dofudge = FALSE;
  }
}

/**********************************
  This is the blotch code:
**********************************/

aablotch_h (x, y, wd, r, g, b, t, p)
float x, y, wd;
int r, g, b, t;
float p;
{
  int xc, yc, xend, yend, xstart, ystart, xx, yy;
  int near, far, near2, far2;
  float ink, get_ink();
  float dist, radius;
  int  width;


  xx = (int)x;
  yy = (int)y;
  xstart = (int) (x - wd);
  ystart = (int) (y - wd);
  xend = (int) (x + wd);
  yend = (int) (y + wd);
  radius = (int) (wd - 1);
  width = (int) (wd * 2 * 16.0);

  for (yy = ystart; yy < yend; ++yy)   { 	
    for (xx = xstart; xx < xend; ++xx)	{ 
      near = (int) ((xx - xstart) * 16);
      far = (int) ((xend - xx) * 16);
      near2 = (int) ((yy - ystart) * 16);
      far2 = (int) ((yend - yy) * 16);

      ink = get_ink(near, 16, width, p, 0, &r, &g, &b);
      ink = 1.0;

      if (aa_clip (xx, yy))
	{ (*point1) (xx, yy, near, far, near2, far2, r, g, b, (int) (t * ink));
	}
    }
    remove_ink(1);
  }
}

/**********************************
  This is the actual line drawing code:
**********************************/

aaline_h (x, y, x2, y2, wd, r, g, b, t, a1, a2, p)
double x, y, x2, y2, wd, a1, a2;
int r, g, b, t;
float p;
{ double end1w, angle, temp;
  int swapped = FALSE;
  double ax = 0, ay = 0, bx = 0, by = 0;
  double len_ab = 0, len_bc = 0;
  double dx_ab = 0, dy_ab = 0;
  int delx, dely, delxf, delyf, delx1, dely1, delx2, dely2;  /* error to sides, near & far end points respectively */
  double ax_off = 0.0, ay_off = 0.0, bx_off = 0.0, by_off = 0.0;
  int width, f_factor = 0;

  if (dofudge)
    f_factor = fudge;

  ax = x; ay = y; bx = x2; by = y2;
  dx_ab = bx - ax;
  dy_ab = by - ay;
  len_ab = sqrt (dx_ab * dx_ab + dy_ab * dy_ab);

  if (((fabs (dx_ab) >= fabs (dy_ab)) && (ax > bx)) || ((fabs (dy_ab) > fabs (dx_ab)) && (ay > by)))
  { swap (ax, bx, temp);
    swap (ay, by, temp);
    swap (a1, a2, temp);
    dx_ab = -dx_ab;
    dy_ab = -dy_ab;
    swapped = TRUE;
  }


  width = round (wd * 16.0);

  if (fabs (dx_ab) < 0.0000001)
    angle = 90.0;
  else
    if ((angle = 180.0 / M_PI * atan2 (dy_ab, dx_ab)) < 0.0)
      angle += 360.0;

  dely = round (dx_ab / (len_ab * blur) * 65536);   
  delx = round (dy_ab / (len_ab * blur) * 65536);

  delyf = round (dx_ab / (len_ab * blur) * 65536);  /* get differential steps ( 0 - 65536) */
  delxf = round (dy_ab / (len_ab * blur) * 65536);

  dely1 = round (cos (radians ((180.0 - angle) - a1)) * 65536);
  delx1 = round (sin (radians ((180.0 - angle) - a1)) * 65536);

  dely2 = round (- cos (radians (angle + a2)) * 65536);
  delx2 = round (sin (radians (angle + a2)) * 65536);


  if (((angle >= 0.0) && (angle <= 45)) || ((angle >= 315.0) && (angle <= 360.0)))
  { if (fabs ((angle + a1) - 90.0) < 0.0000001)
    { ax_off = 1.0;
      ay_off = 0.0;
    }
    else
    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
      ax_off = end1w * fabs (sin (radians ((a1 + angle) - 90.0)));
      ay_off = ax_off * fabs (tan (radians (angle)));
    }

    if (fabs ((angle + a2) - 90.0) < .0000001)
    { bx_off = 1.0;
      by_off = 0.0;
    }
    else
    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
      bx_off = end1w * fabs (sin (radians ((a2 + angle) - 90.0)));
      by_off = bx_off * fabs (tan (radians (angle)));
    }

    plot_x_h (ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
	      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, 
	      fudge, swapped, p);
  }
    
  else if ((angle >= 45.0) && (angle <= 135))
  { if (fabs ((angle + a1) - 180.0) < 0.0000001)
    { ax_off = 0.0;
      ay_off = 1.0;
    }
    else
    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
      ay_off = end1w * fabs (sin (radians (180.0 - (a1 + angle))));
      ax_off = ay_off * fabs (tan (radians (90.0 - angle)));
    }

    if (fabs ((angle + a2) - 180.0) < .0000001)
    { bx_off = 0.0;
      by_off = 1.0;
    }
    else
    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
      by_off = end1w * fabs (sin (radians (180.0 - (a2 + angle))));
      bx_off = by_off * fabs (tan (radians (90.0 - angle)));
    }

    plot_y_h (ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
	      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t,
	      fudge, swapped, p);
  }
    
  if (swapped)
  { swap (ax, bx, temp);
    swap (ay, by, temp);
    swap (a1, a2, temp);
    dx_ab = -dx_ab;
    dy_ab = -dy_ab;
  }
}


/*****************************************
  These functions draw the lines:
*****************************************/

/* plots lines with 0 >= slope >= 1
*/

void plot_x_h (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, 
	       width, r, g, b, t, 
	       fudge, swapped, p)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, p;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge, swapped;

{ int error, error2_n, error2_f, s1, y, offset;
  register int xc, yc;
  int err, err2_n, err2_f;
  register int near, near2, far, far2, endx;
  float ink, get_ink();
    
  xc = ax - ax_off;
  if (ay <= by)
    y = ay - ay_off;
  else
    y = ay + ay_off;

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
      ink = get_ink(near, dely, width, p, swapped, &r, &g, &b);

      if ((near2 < far2) && aa_clip (xc, yc))
	{ (*point1) (xc, yc, near, far, near2, far2, r, g, b, 
		     (int) (t * ink));
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
      ink = get_ink(near, -dely, width, p, swapped, &r, &g, &b);

      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, 
		   (int) (t * ink));
      }

      err -= dely;
      err2_n -= dely1;
      err2_f -= dely2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }

    remove_ink(1);
    
    if (ay <= by)
      { if (error > s1)
	  { ++y;
	    error -= dely;
	    error2_n -= dely1;
	    error2_f -= dely2;
	  }
      }
    else
      { if (error < s1)
	  { --y;
	    error += dely;
	    error2_n += dely1;
	    error2_f += dely2;
	  }
      }
    
    error += delx;
    error2_n -= delx1;
    error2_f -= delx2;
  }
}



/* plots lines with slope -1 >= slope 
*/

void plot_y_h (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, 
	       width, r, g, b, t, 
	       fudge, swapped, p)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, p;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge, swapped;

{ int error, error2_n, error2_f, s1, x, offset;
  register int xc, yc;
  int err, err2_n, err2_f;
  register int near, near2, far, far2, endy;
  int temp;
  float ink, get_ink();

  if (ax <= bx)
    x = ax - ax_off;
  else
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
      ink = get_ink(near, delx, width, p, !swapped, &r, &g, &b);

      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, (int) (t * ink));
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
      ink = get_ink(near, -delx, width, p, !swapped, &r, &g, &b);

      if ((near2 < far2) && aa_clip (xc, yc))
      { (*point1) (xc, yc, near, far, near2, far2, r, g, b, (int) (t * ink));
      }

      err -= delx;
      err2_n -= delx1;
      err2_f -= delx2;
      near = (err >>12) + offset;
      far = near + width;
      near2 = err2_n >>12;
      far2 = err2_f >>12;
    }
    
    remove_ink(1);

    if (ax <= bx)
      if (error > s1)
	{ ++x;
	  error -= delx;
	  error2_n -= delx1;
	  error2_f -= delx2;
	}
    else
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

}


