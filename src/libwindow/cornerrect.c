#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <math.h>

int _Filler1()
{

  printf("I dont understand the linker.\n");
}

int _Filler2()
{

  printf("I dont understand the compiler.\n");
}


/*****************************************************************************
 * CornerRectify()
 * 
 * OVERVIEW
 *    This procedure allows for the caller to control the roundness
 *    of each of the four corners of a window.
 *
 * REQUIRES
 *    This procedures expects that the "curve" values are in pixels,
 *    NOT in percent, which is different from RoundRectify
 *
 * MESSAGES
 *    CHANGE_UL_ROUND
 *    CHANGE_UR_ROUND
 *    CHANGE_LR_ROUND
 *    CHANGE_LL_ROUND
 *    
 ****************************************************************************/

CornerRectify(W, 
	      red, green, blue, 
	      shadow, 
	      shadowred, shadowgreen, shadowblue, 
	      ul_curve, ur_curve, lr_curve, ll_curve)
     struct Window *W;
     int red, green, blue, shadow, shadowred, shadowgreen, shadowblue;
     int ul_curve, ur_curve, lr_curve, ll_curve;
{
  int CornerRectWin();
  struct cornerrectstruct *params;

  params = (struct cornerrectstruct *)malloc(sizeof(struct cornerrectstruct));
  params->red = red;
  params->green = green;
  params->blue = blue;
  params->shadow = shadow;
  params->shadowred = shadowred;
  params->shadowgreen = shadowgreen;
  params->shadowblue = shadowblue;
  params->ul_curve = ul_curve;
  params->ur_curve = ur_curve;
  params->lr_curve = lr_curve;
  params->ll_curve = ll_curve;
  
  AttachCommand(W, DRAW, CornerRectWin, (char *)params);
  AttachCommand(W, NEWCOLOR, CornerRectWin, (char *)params);
  
  AttachCommand(W, CHANGE_UL_ROUND, CornerRectWin, (char *)params);
  AttachCommand(W, CHANGE_UR_ROUND, CornerRectWin, (char *)params);
  AttachCommand(W, CHANGE_LR_ROUND, CornerRectWin, (char *)params);
  AttachCommand(W, CHANGE_LL_ROUND, CornerRectWin, (char *)params);

}


CornerRectWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct cornerrectstruct *params;
  int x1, x2, y1, y2, screen, shadow, t;
  int uld, urd, lrd, lld;
  float fx1, fx2, fy1, fy2;
  float cx1, cx2, cy1, cy2;
  float red, green, blue;
  struct clipstruct *cstruct;
  int *colors;

  params = (struct cornerrectstruct *) stuff;

  switch (id)
    {
    case (NEWCOLOR):
      colors = (int *)data;
      params = (struct cornerrectstruct *)stuff;
    
      params->red = *(colors);
      params->green = *(colors+1);
      params->blue = *(colors+2);
      break;

    case (CHANGE_UL_ROUND):
      params->ul_curve = *((int *)data);
      break;

    case (CHANGE_UR_ROUND):
      params->ur_curve = *((int *)data);
      break;

    case (CHANGE_LR_ROUND):
      params->lr_curve = *((int *)data);
      break;

    case (CHANGE_LL_ROUND):
      params->ll_curve = *((int *)data);
      break;

    case (DRAW):
      /* get the clip struct */
      cstruct = (struct clipstruct *)data;
      cx1 = cstruct->x1;  
      cy1 = cstruct->y1;
      cx2 = cstruct->x2;  
      cy2 = cstruct->y2;
      clip_rectangle((W->display)->fildes, cx1, cx2, cy1, cy2);

      /* get a pointer to the screen */
      screen = (W->display)->fildes;

      /* get out the curves */
      uld = params->ul_curve;
      urd = params->ur_curve;
      lrd = params->lr_curve;
      lld = params->ll_curve;

      x1 = W->x1; 
      x2 = W->x2;
      y1 = W->y1; 
      y2 = W->y2;
    
      vertex_format(screen, 0, 0, 0, 0, 0);
      interior_style(screen, INT_SOLID, TRUE);

      /* check if there is to be a shadow */
      shadow = params->shadow;

      if (shadow != 0)
	{
	  red = ((float) (params->shadowred)/255.0);
	  green = ((float) (params->shadowgreen)/255.0);
	  blue = ((float) (params->shadowblue)/255.0);
	  
	  line_color(screen, red, green, blue);
	  perimeter_color(screen, red, green, blue);
	  fill_color(screen, red, green, blue);
	  
	  /* if negative shadow, reverse it */
	  shadow = abs(shadow);

	  x2 -= shadow;
	  y2 -= shadow;

	  /* coerce the types */
	  fx1 = (float) x1; 
	  fx2 = (float) x2;
	  fy1 = (float) y1; 
	  fy2 = (float) y2;
	  
	  /* draw the shadow */
	  for (t = 0; t < shadow; t++)
	    {
	      fx1 += 1.0;
	      fx2 += 1.0;
	      fy1 += 1.0;
	      fy2 += 1.0;
	      
	      move2d(screen, fx1 + (float) lld, fy2); 
	      draw2d(screen, fx2 - (float) lrd, fy2);
	      move2d(screen, fx2, fy1 + (float) urd); 
	      draw2d(screen, fx2, fy2 - (float) lrd);
	      
	      if (lrd != 0)
		arc(screen, (float) lrd, (float) lrd, 
		    fx2 - (float) lrd, fy2 - (float) lrd, 
		    0.0, M_PI / 2.0, 0.0, 0);
	      
	      if (urd != 0)
		arc(screen, (float) urd, (float) urd,
		    fx2 - (float) urd, fy1 + (float) urd,
		    0.0, -M_PI/2.0, 0.0, 0);
	      
	      if (lld != 0)
		arc(screen, (float) lld, (float) lld,
		    fx1 + (float) lld, fy2 - (float) lld, 
		    M_PI, M_PI/2.0, 0.0, 0);
	    }
	}
      
      /* fill the box */
      red = ((float) (params->red) / 255.0);
      green = ((float) (params->green) / 255.0);
      blue = ((float) (params->blue) / 255.0);
      
      perimeter_color(screen, red, green, blue);
      line_color(screen, red, green, blue);
      fill_color(screen, red, green, blue);
      
      CorneredBox(screen, x1, y1, x2, y2, uld, urd, lrd, lld);
      
      /* reset the clip rect */
      clip_rectangle((W->display)->fildes, 
		     (float)0.0, (float)((W->display)->width-1),
		     0.0, (float)((W->display)->height-1));
      make_picture_current((W->display)->fildes);
      break;

    default:
      printf("CornerRectWin: unknown message %d\n", id);
    }
}




CorneredBox(fildes, x1, y1, x2, y2, uld, urd, lrd, lld) 
     int fildes, x1, y1, x2, y2, uld, urd, lrd, lld;
{
  float line[12];
  int c;

  if (x2 < x1) 
    {
      c = x1;
      x1 = x2;
      x2 = c;
    }
  if (y2 < y1) 
    {
      c = y1;
      y1 = y2;
      y2 = c;
    }
  
  /* error check */
  if (((uld + urd) >= (x2 - x1)) ||
      ((uld + lld) >= (y2 - y1)) ||
      ((lld + lrd) >= (x2 - x1)) ||
      ((lrd + urd) >= (y2 - y1)))
    {
      fprintf(stderr, "Error: Corner box: too round.\n");
      uld = 0;
      urd = 0;
      lld = 0;
      lrd = 0;
      return(1);
    }
  
  vertex_format(fildes, 0, 0, 0, 0, 0);
  
  if (uld != 0)
    partial_arc(fildes, 
		(float) uld, (float) uld, 
		(float) (x1 + uld), (float) (y1 + uld), 
		M_PI, 1.5 * M_PI, 0.0, 0, 0);
  else
    {
      line[0] = (float) x1;
      line[1] = (float) y1;
      line[2] = 1;
      partial_polygon2d(fildes, line, 1, 1);
    }
  
  if (urd != 0)
    partial_arc(fildes, 
		(float) urd, (float) urd, 
		(float) (x2 - urd), (float) (y1 + urd), 
		-M_PI / 2.0, 0.0, 0.0, 0, 0);
  else
    {
      line[0] = (float) x2;
      line[1] = (float) y1;
      line[2] = 1;
      partial_polygon2d(fildes, line, 1, 1);
    }
  
  if (lrd != 0)
    partial_arc(fildes, 
		(float) lrd, (float) lrd, 
		(float) (x2 - lrd), (float)(y2 - lrd),
		0.0, M_PI / 2.0, 0.0, 0, 0);
  else
    {
      line[0] = (float) x2;
      line[1] = (float) y2;
      line[2] = 1;
      partial_polygon2d(fildes, line, 1, 1);
    }
  
  if (lld != 0)
    partial_arc(fildes, 
		(float) lld, (float) lld, 
		(float) (x1 + lld), (float) (y2 - lld), 
		M_PI / 2.0, M_PI, 0.0, 0, 0);
  else
    {
      line[0] = (float) x1;
      line[1] = (float) y2;
      line[2] = 1;
      partial_polygon2d(fildes, line, 1, 1);
    }
  
  line[0] = (float)(x2 - x1) / 2.0;
  line[1] = (float)(y2 - y1) / 2.0;
  line[2] = 1;
  line[3] = (float)(x2 - x1) / 2.0;
  line[4] = (float)(y2 - y1) / 2.0;
  line[5] = 1;

  polygon2d(fildes, line, 2, 1); 
  return (0);
}



