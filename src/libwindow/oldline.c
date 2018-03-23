
/* File line.c

   Written by    Russell Greenlee   at the Visible Language Workshop,  MIT     1987

   Contains the top level routines to read in the tables and to plot lines.
*/


#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include "aaline.h"

#define WAIT 0
#define START 1
#define DRAW 2
#define FUDGE 2500
#define MINLEN 1
#define EXCLUSIVE 3

#define radians(degrees) ((degrees) * M_PI / 180.0)



extern double factor;
unsigned char *framebuf, *r_bank, *g_bank, *b_bank, *abuffer;
int xoff, yoff, buf2wd, buf2ht, buf2 = FALSE, abufwd, abufht, abuf;

int red = 0, green = 0, blue = 0, trans = 0;
double width1 = 0, width2 = 0;
int fudge = 0, dofudge = FALSE;
double blur = 1.0;
double ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0, state = WAIT;      /* the points a, b, c */
double len_ab = 0, len_bc = 0;
double dx_ab = 0, dy_ab = 0, dx_bc = 0, dy_bc = 0;
int delx = 0, dely = 0, delx1 = 0, dely1 = 0, delx2 = 0, dely2 = 0;   /* error to sides, near & far end points respectively */
double ax_off = 0.0, ay_off = 0.0, bx_off = 0.0, by_off = 0.0;
double a1, a2, b1, b2;

extern void plot_x();                       /* file plotx.c */
extern void plot_x2();
extern void plot_y();                       /* file ploty.c */
extern void plot_y2();

void read_short_table();
void aa_move();
int  aa_draw();
void aa_done();
void aa_set_width();
void aa_set_color();
void aa_set_blend();
void aa_set_trans();
 

aa_set_fb (bits, buff, ctrl)
int bits;
unsigned char *buff, *ctrl;

{ void point1_32();
  void point1_24();

  framebuf = buff;
  aa_set_ctrl (ctrl);
  if (bits == 32)
    aa_set_blend (point1_32);
  else if (bits == 24)
    aa_set_blend (point1_24);
}

aa_set_bitmap_exclusive()
{
  buf2 = EXCLUSIVE;
}

aa_set_fb_exclusive()
{
  buf2 = FALSE;
}

aa_set_bitmap(x, y, wd, ht, reds, greens, blues)
int x, y, wd, ht;
unsigned char *reds, *greens, *blues;
{
  buf2 = TRUE;
  xoff = x;
  yoff = y;
  buf2wd = wd;
  buf2ht = ht;
  r_bank = reds;
  g_bank = greens;
  b_bank = blues;
}
  
aa_set_abuffer(wd,ht,buffer)
int wd,ht;
unsigned char *buffer;
{
  abuf   = TRUE;
  abufwd = wd;
  abufht = ht;
  abuffer = buffer;
}

aa_reset_abuffer()
{
  abuf = FALSE;
}


aaline (x, y, x2, y2, wd, r, g, b, t, a1, a2)
double x, y, x2, y2, wd, a1, a2;
int r, g, b, t;

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

  delyf = round (dx_ab / (len_ab * blur) * 65536);                   /* get differential steps ( 0 - 65536) */
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

    if (angle >= 315)
      plot_x2 (ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
    else
      plot_x (ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
	      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge); 
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

    if (angle <= 90)
      plot_y (ax, ay, bx, by, ax_off, ay_off + 1, bx_off, by_off + 1, 
	      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
    else
      plot_y2 (ax, ay, bx, by, ax_off, ay_off + 1, bx_off, by_off + 1, 
	       delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
  }
    
  if (swapped)
  { swap (ax, bx, temp);
    swap (ay, by, temp);
    swap (a1, a2, temp);
    dx_ab = -dx_ab;
    dy_ab = -dy_ab;
  }
}




/* The following 3 routines are tuned to draw a series of connected lines of variable width
   with matching endpoints.  The parameters describing a line and its' end points are global
   variables.
*/




/*  move initializes the first point of a stroke to be drawn, and the line color and width.
*/

void aa_move (x, y, w)
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




void aa_set_width (wd)
double wd;

{ if ((wd >= .25) && (wd <= 200.0))
    width1 = width2 = wd;
}



void aa_set_color (r, g, b)
int r, g, b;

{ int intensity, ff = 50;


  if ((r >= 0) && (r <= 255))
    red = r;

  if ((g >= 0) && (g <= 255))
    green = g;

  if ((b >= 0) && (b <= 255))
    blue = b;

  intensity = round (0.3 * r + 0.59 * g + 0.11 * b);

  if (intensity > 64)
  { if (point1 == point1)
      fudge = FUDGE + 2.2 * ff * (((intensity * trans) >>8) - 64);
    else
      fudge = FUDGE + ff * (intensity - 64);
  }
  else
    fudge = FUDGE;
}



aa_set_blur (b)
double b;

{ if (blur > 0)
    blur = b;
}




void aa_set_blend (f)
void (*f)();

{ int intensity, ff = 50;
  void point2();

  point1 = f;

  intensity = round (0.3 * red + 0.59 * green + 0.11 * blue);

  if (intensity > 64)
  { if (point1 == point1)
      fudge = FUDGE + 2.2 * ff * (((intensity * trans) >>8) - 64);
    else
      fudge = FUDGE + ff * (intensity - 64);
  }
  else
    fudge = FUDGE;
}



void aa_set_trans (t)
int t;

{ trans = t;
}




/*  draw draws an anti-aliased line on the screen, if there are two points previously defined.
*/

int aa_draw (x, y, w)
double x, y, w;

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

    aaline (ax, ay, bx, by, width1, red, green, blue, trans, a1, a2);

    ax = bx;
    ay = by;
    bx = cx;
    by = cy;
    a1 = b1;
    width1 = width2;
    width2 = w;

    return (TRUE);    
  }

  else
    return (FALSE);
}





/* done draw the last segment of the stroke and prepares for the next one.
*/

void aa_done ()

{ int temp;

  if (state == DRAW)                                                        /* this should only follow a draw */
  { aaline (ax, ay, bx, by, width1, red, green, blue, trans, a1, 90.0);
    state = WAIT;                                         /* ready to start the next stroke */
    dofudge = FALSE;
  }
}




matherr (x)
struct exception *x;

{

  switch (x->type)
  { case PLOSS:
      printf ("ploss error, %s\n", x->name);
      break;
    case TLOSS:
      printf ("tloss error, %s\n", x->name);
      break;
  }
}
