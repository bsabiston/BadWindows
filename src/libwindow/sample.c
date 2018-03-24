

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





#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>



DrawSampleWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct clipstruct *cstruct;
  int screen, cx1, cx2, cy1, cy2;

  printf("draw sample %d %d %d\n", id, data, stuff);

  screen = (W->display)->fildes;

  switch (id) {

    case(DRAW):

      cstruct = (struct clipstruct *)data;

    cx1 = cstruct->x1;
    cy1 = cstruct->y1;
    cx2 = cstruct->x2;
    cy2 = cstruct->y2;

    clip_rectangle(screen, (float)cx1, (float)cx2, (float)cy1, (float)cy2);

  default:

    fill_color(screen, .5, .3, .7);
    interior_style(screen, INT_SOLID, FALSE);
    rectangle(screen, (float)cx1, (float)cy1, (float)cx2, (float)cy2);

    clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1),
		   0.0, (float)((W->display)->height-1));
    make_picture_current((W->display)->fildes);

    break;
  }
}



DoSampleWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int x, y, button;
  struct pickstruct *pick;


  if (id==DO)
    {
      pick = (struct pickstruct *)data;
      x = pick->x;
      y = pick->y;
      button = pick->button;
      switch (button) {
      case (JUSTDOWN):

      case (BEENUP):

      case (JUSTUP):

      case (BEENDOWN):

/* CurrentRed CurrentGreen CurrentBlue */
	line_color(W->display->fildes, 1.0, 1.0, 1.0);
	draw2d(W->display->fildes, (float)x, (float)y);
	make_picture_current(W->display->fildes);
	break;

      }
    }
  return(0);
}

