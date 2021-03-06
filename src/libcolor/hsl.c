#include <math.h>
#define TRUE 1
#define FALSE 0

/*	XO and io are lookup tables used in calculating the clipping
	of an I,H,S point that is not in the RGB cube to that cube.
	I don't understand them, I just copied them from the old code.
*/
static	double	XO[7] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
static	int	io[7] = { 2, 0, 1, 0, 1, 2, 0 };
static	double	two_thirds = 0.666666666;
static	double	one_third = 0.333333333;
static	double	inv_sqrt_three = 0.577350; /* 1/sqrt(3) */
static	double	pi = 3.1415926;

/*
	ihs_rgb
	a routine to convert colors in the (i,h,s) system to
	the (r,g,b) system.

	I, H, and S are in the range 0 to 1.
	r, g, and b are in the range 0 to 1.

	Stolen from MagicSix code 8/84 by Leo
	ported to the Bobcat 10/87 by dsmall
*/

ihs_to_rgb(hue,sat,inten,r,g,b)
float	inten,hue,sat;
float	*r,*g,*b;
{

  int	face,		/* Which face of the RGB cube we penetrated (ended
			   up on the outside of) */
        p,q,
        ir,ig,ib;	/* Our copies of the output r,g,b */
  float	th,		/* Hue starts in range 0-1, this is hue in radians
			   from 0 to 6.28 */
        cos_th,		/* Cosine thereof */
        sin_th,		/* Sine thereof */
        new_sat,	/* Alternate saturation; when the original I,H,S point
			   was outside the space of the RGB cube, you 
			   recalculate with this as S. */
        ha[3];		/* ha expresses the hue as a vector in
			   RGB space. */

  if (hue >= 1.0) hue = hue - 1.0;
  th = 2*pi*hue;
  cos_th = cos(th);
  sin_th = sin(th);
  ha[0] = two_thirds*cos_th;
  ha[1] = -one_third*cos_th + inv_sqrt_three*sin_th;
  ha[2] = -one_third*cos_th - inv_sqrt_three*sin_th;

/* OK, as I understand this bit we now have ha, which is a vector in RGB
space in the direction of our hue.  Further, ha has a norm of sqrt(two_thirds),
which is so that if we are pointing right at any of the corners of the
RGB cube, the end of the ha vector lands right on the corner.  So what
we do now is go to the point (inten,inten,inten) in the UNIT rgb cube, then
go sat*sqrt(two_thirds) units away from the black/white axis in the direction
of ha, and lastly convert from the unit RGB cube to the 0-255 range.  Later
we have to deal with the case where this point is outside the RGB cube. */

  ir = (inten + sat*ha[0] )*255.0 + 0.5;
  ig = (inten + sat*ha[1] )*255.0 + 0.5;
  ib = (inten + sat*ha[2] )*255.0 + 0.5;

  /* Now see if (ir,ig,ib), which really is the r,g,b corresponding to the
     input ihs, is inside the RGB cube.	*/
  if ((ir < 0)||(ig < 0)||(ib < 0)||(ir > 255)||(ig > 255)||(ib > 255))
    {
      /* The general approach is to reduce the sat so that we just hit
	 the surface of the RGB cube, instead of going outside it.
	 The 6 faces are labelled as so:
	     Name  Vertices				  Value of face
	     "Y" - Black, Red, Green, Yellow		     - 0
	     "C" - Black, Green, Blue, Cyan		     - 1
	     "M" - Black, Blue, Red, Magenta		     - 2
	     "R" - White, Magenta, Yellow, Red	             - 3 or 6
	     "G" - White, Cyan, Yellow, Green	             - 4
	     "B" - White, Cyan, Magenta, Blue	             - 5
	 Now, if the input inten was less than one_third, we're in
	 the black half, and can figure out which of the faces Y, C, or M
	 it penetrated.  If the inten was more than two_third, we
	 went through R, G, or B.  If it was in the middle, it could be
	 any of the six. */

      if (inten < one_third)
	face = 3.0*hue; /* Y, C, or M face */
      else
	if (inten > two_thirds)
	  face = 3.0 * hue + 3.5; /* R, G, or B face */
	else
	  {
	    p = 3.0*hue + 1.5*inten - 0.5;
	    q = 3.0*hue - 1.5*inten + 1.5;
	    if (p == q)
	      face = p + 3;
	    else
	      face = p;
	  }
      /* OK, now we know which face it was.  Find new_sat such that it is
	 the saturation which exactly reaches the face. */
      new_sat = (XO[face]-inten)/ha[io[face]];
      /* and repeat calculations with new saturation */
      ir = (inten + new_sat*ha[0] )*255.0 + 0.5;
      ig = (inten + new_sat*ha[1] )*255.0 + 0.5;
      ib = (inten + new_sat*ha[2] )*255.0 + 0.5;

      /* And clip that sucker to 0-255 anyway */
      if (ir < 0)
	ir = 0;
      if (ig < 0)
	ig = 0;
      if (ib < 0)
	ib = 0;
      if (ir > 255)
	ir = 255;
      if (ig > 255)
	ig = 255;
      if (ib > 255)
	ib = 255;
    } /* end of check to see if we penetrated a surface of the RGB cube */

  *r = ((float) ir) / 255.0;
  *g = ((float) ig) / 255.0;
  *b = ((float) ib) / 255.0;

} /* ihs_rgb */


/********hsl to rgb routine**************************/
int hslrgb(h,s,l,r,g,b)
float h,s,l;
int *r,*g,*b;
{
  int valid;
  float R, G, B;

  hsl_to_rgb(h,s,l,&R, &G, &B, &valid);
  *r = (int) (R * 255); 
  *g = (int) (G * 255); 
  *b = (int) (B * 255); 

  return (valid);
}

hsl_to_rgb(hue, saturation, luminosity, red, green, blue, valid)
float hue, saturation, luminosity;
float *red, *green, *blue;
int *valid;
{
  float x, y, Y;
  if (hue >= 1.0) hue = hue - 1.0;

  Y = luminosity;
  x = 0.3 * saturation * cos(hue * 2 * M_PI) + 0.313034;
  y = 0.3 * saturation * sin(hue * 2 * M_PI) + 0.328835;
    
/*  cie_to_rgb(x, y, Y, red, green, blue); kanarick made this change */

  ciergb2(x, y, Y, red, green, blue);
  if ((*red > 1.0) || (*red <= 0.0) ||
      (*green > 1.0) || (*green <= 0.0) ||
      (*blue > 1.0) || (*blue <= 0.0)) *valid = FALSE;
  else *valid = TRUE;
}


