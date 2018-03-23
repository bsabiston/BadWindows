/* File line.c

   Written by    Russell Greenleeb   at the Visible Language Workshop,  MIT     1987

   Contains the top level routines to read in the tables and to plot lines.
*/


#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include "aaline.h"
#include "hpfbuffers.h"

#define WAIT 0
#define START 1
#define DRAW 2
#define FUDGE 2500
#define MINLEN 1
#define EXCLUSIVE 3

#define ABOVE_WINDOW    1	/* 00001 */
#define BELOW_WINDOW    2	/* 00010 */
#define RIGHT_OF_WINDOW 4	/* 00100 */
#define LEFT_OF_WINDOW  8	/* 01000 */

#define radians(degrees) ((degrees) * M_PI / 180.0)

extern double factor;
unsigned char *framebuf, *r_bank, *g_bank, *b_bank, *abuffer;
int xoff, yoff, buf2wd, buf2ht, buf2 = FALSE, abufwd, abufht, abuf, aa_screen,aa_bankmask,aa_bankshift,aa_otherbank;

int red = 0, green = 0, blue = 0, trans = 0;
double width1 = 0, width2 = 0;
int fudge = 0, dofudge = FALSE, tripledraw = 0, nbits,fbw,fbh;
double blur = 1.0;
double ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0, state = WAIT;      /* the points a, b, c */
double len_ab = 0, len_bc = 0;
double dx_ab = 0, dy_ab = 0, dx_bc = 0, dy_bc = 0;
int delx = 0, dely = 0, delx1 = 0, dely1 = 0, delx2 = 0, dely2 = 0;   /* error to sides, near & far end points respectively */
double ax_off = 0.0, ay_off = 0.0, bx_off = 0.0, by_off = 0.0;
double a1, a2, b1, b2;

void (*point1)();

struct outcode {
    unsigned above : 1;
    unsigned below : 1;
    unsigned right : 1;
    unsigned left : 1;
  }; 

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
 

aa_set_fb (screen,bits, buff, ctrl,w,h)
int bits,screen,w,h;
unsigned char *buff, *ctrl;

{
  void point1_SRX24();
  void point1_REN24();
  void point1_CRX24();
  void point1_CRX8();
  void point1_CRX24_db();

  nbits = bits;
  fbw = w;
  fbh = h;
  tripledraw = 0;
  aa_screen = screen;
  framebuf = buff;
  aa_set_ctrl (ctrl);
  if ((bits&BUFTYPE) == SRX24)
    aa_set_blend (point1_SRX24);
  else if ((bits&BUFTYPE) == REN24)
    aa_set_blend (point1_REN24);
  else if ((bits&BUFTYPE) == CRX8)
    aa_set_blend (point1_CRX8);
  else if ((bits&BUFTYPE) == CRX24)
    {
      tripledraw = 1;
      if (bits&DBUFFER) {
	aa_set_blend (point1_CRX24_db);
	if (bits&WBANK) aa_bankmask = 0xF0, aa_otherbank = 0x0F, aa_bankshift = 0;
	else aa_bankmask = 0x0F, aa_otherbank = 0xF0, aa_bankshift = 4;
      }
      else aa_set_blend (point1_CRX24);
    }
  else if ((bits&BUFTYPE) == MEMBUFF){
    if (((bits&BUFBITS)>>8) == 8) aa_set_blend (point1_CRX8);
    else if (((bits&BUFBITS)>>8) == 24) {
      tripledraw = 1;
      aa_set_blend (point1_CRX24);
    }
  }
  else printf("NO MONITOR! %d\n",bits&BUFTYPE);
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
  gescape_arg arg1,arg2;
  int swapped = FALSE;
  double ax = 0, ay = 0, bx = 0, by = 0;
  double len_ab = 0, len_bc = 0;
  double dx_ab = 0, dy_ab = 0;
  int delx, dely, delxf, delyf, delx1, dely1, delx2, dely2;  /* error to sides, near & far end points respectively */
  double ax_off = 0.0, ay_off = 0.0, bx_off = 0.0, by_off = 0.0;
  int width, f_factor = 0;

  if ((nbits&BUFTYPE)==CRX8)   gescape(aa_screen, R_LOCK_DEVICE, &arg1, &arg2); 

  if (dofudge)
    f_factor = fudge;

  /* clip test added by Bob   10/13/90 */
  if (aa_clip_test(x,y,x2,y2,wd)) return;

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
      {
	if (tripledraw) triplot(plot_x2,ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
				delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
	else plot_x2 (ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
		      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
      }
    else {
      if (tripledraw) triplot(plot_x,ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
			      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
      else plot_x (ax, ay, bx, by, ax_off + 1, ay_off, bx_off + 1, by_off, 
		   delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge); 
    }
  }
    
  else if ((angle >= 45.0) && (angle <= 135))
    {if (fabs ((angle + a1) - 180.0) < 0.0000001)
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

    if (angle <= 90) {
      if (tripledraw) triplot(plot_y, ax, ay, bx, by, ax_off, ay_off+1, bx_off, by_off + 1, 
			      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
      else plot_y (ax, ay, bx, by, ax_off, ay_off + 1, bx_off, by_off + 1, 
		   delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
    }
    else {
      if (tripledraw) triplot(plot_y2, ax, ay, bx, by, ax_off, ay_off+1, bx_off, by_off + 1, 
			      delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
      else plot_y2 (ax, ay, bx, by, ax_off, ay_off + 1, bx_off, by_off + 1, 
	       delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge);
    }
  }
    
    if ((nbits&BUFTYPE)==CRX8)   gescape(aa_screen, R_UNLOCK_DEVICE, &arg1, &arg2); 

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
  gescape_arg arg1,arg2;
  
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



/*
 * aa_clip_test()  from the generous heart of David Young and butchered by Bob S. 10/90
 *    From: Foley & Van Dam, Page 148
 *    Cohen-Sutherland Clipping algorithm for line P1 = (x1, y1) to P2 = (x2, y2)
 */

aa_clip_test(x1,y1,x2,y2,wd)
double x1,y1,x2,y2,wd;
{
  int val;
  val = aacliptest((int)x1,(int)y1,(int)x2,(int)y2);
  return(val);
}

aacliptest(x1, y1, x2, y2)
     int x1, y1, x2, y2;
{
  int rejectCheck();
  int accept = FALSE, reject = FALSE, done = FALSE;
  int outcode1, outcode2, temp,xmin,ymin,xmax,ymax;

  get_aa_clip(&xmin,&ymin,&xmax,&ymax);
  while( !done) {
    outcode1 = outcodes( x1, y1, xmin, xmax, ymin, ymax);
    outcode2 = outcodes( x2, y2, xmin, xmax, ymin, ymax);
    reject = rejectCheck( outcode1, outcode2); /* check trivial reject */
    if( reject)
      done = TRUE;
    else {			/* possible accept */
      if( (outcode1 == 0) && (outcode2 == 0)) {	/* check trivial accept */
	accept = TRUE;
	done = TRUE;
      }
      else {			/* subdivide line since at most one endpoint is inside */
	/* first, if P1 is inside window, exchange points 1 and 2 and their outcodes to
	 * guarantess that P1 is outside window 
	 */
	if( outcode1 == 0) {
	  temp = x1; x1 = x2; x2 = temp;
	  temp = y1; y1 = y2; y2 = temp;
	  temp = outcode1; outcode1 = outcode2; outcode2 = temp;
	}
	/* now perform a subdivision, move P1 to the intersection point; use the formulas
	 * y = y1 + slope * (x - x1), x = x1 + (1/slope) * (y - y1).
	 */
	if( outcode1 & ABOVE_WINDOW) {
	  /* divide line at top of window */
	  x1 = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
	  y1 = ymax;
	}
	else if( outcode1 & BELOW_WINDOW) {
	  /* divide line at bottom of window */
	  x1 = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
	  y1 = ymin;
	}
	else if( outcode1 & RIGHT_OF_WINDOW) {
	  /* divide line at right edge of window */
	  y1 = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
	  x1 = xmax;
	}
	else if( outcode1 & LEFT_OF_WINDOW) { 
	  /* divide line at left edge of window */
	  y1 = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
	  x1 = xmin;
	}
      }
    }
  }
  
  if (accept) return(0);
  else return(1);
}



int
outcodes( x, y, xmin, xmax, ymin, ymax)
     int x, y, xmin, xmax, ymin, ymax;
{
  int result = 0;

  if( x > xmax)
    result = result | RIGHT_OF_WINDOW;
  else if( x < xmin)
    result = result | LEFT_OF_WINDOW;

  if( y > ymax)
    result = result | ABOVE_WINDOW;
  else if( y < ymin)
    result = result | BELOW_WINDOW;

  return( result);
}

/* dky Egetstringwidth, stringrectangle set_string */
rejectCheck( outcode1, outcode2)
     int outcode1, outcode2;
{
  if( (( outcode1 & RIGHT_OF_WINDOW) && ( outcode2 & RIGHT_OF_WINDOW))
     || (( outcode1 & LEFT_OF_WINDOW) && ( outcode2 & LEFT_OF_WINDOW))
     || (( outcode1 & ABOVE_WINDOW) && ( outcode2 & ABOVE_WINDOW))
     || (( outcode1 & BELOW_WINDOW) && ( outcode2 & BELOW_WINDOW)))
    return( TRUE);
  else
    return( FALSE);
}



triplot(func, ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, width, r, g, b, t, fudge)
double ax, ay, bx, by, ax_off, ay_off, bx_off, by_off;
int width, r, g, b, t, delx, dely, delx1, dely1, delx2, dely2, fudge;
void (*func)();
{
  gescape_arg arg1,arg2;

  bank_switch(aa_screen,2,0); 
  gescape(aa_screen, R_LOCK_DEVICE, &arg1, &arg2); 
      (*func) (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, width, r, 0, 1, t, fudge);  /* 1 is for alpha buffering */
  gescape(aa_screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
  bank_switch(aa_screen,1,0); 
  gescape(aa_screen, R_LOCK_DEVICE, &arg1, &arg2); 
      (*func) (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, width, g, 0, 0, t, fudge);
  gescape(aa_screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
  bank_switch(aa_screen,0,0); 
  gescape(aa_screen, R_LOCK_DEVICE, &arg1, &arg2); 
      (*func) (ax, ay, bx, by, ax_off, ay_off, bx_off, by_off, 
	       delx, dely, delx1, dely1, delx2, dely2, width, b, 0, 0, t, fudge);
  gescape(aa_screen, R_UNLOCK_DEVICE, &arg1, &arg2); 

}
