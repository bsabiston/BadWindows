#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>



struct gridstruct {
  int length, step, num, topmargin, leftmargin;
  int thickness, r, g, b;
  int orient;
};


/* also see Hatchify() */

GridLinify(W, length, step, num, topmargin, leftmargin, orient, thickness, r, g, b)
     struct Window *W;
     int length, step, num, topmargin, leftmargin, orient, thickness, r, g, b;
{
  struct gridstruct *params;
  int DrawGridLines();

  params = (struct gridstruct *) malloc(sizeof(struct gridstruct));

  params->step = step;
  params->length = length;
  params->num = num;
  params->topmargin = topmargin;
  params->leftmargin = leftmargin;
  params->orient = orient;
  params->thickness = thickness;
  params->r = r;
  params->g = g;
  params->b = b;
  AttachCommand(W, DRAW, DrawGridLines, params);
}



DrawGridLines(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct gridstruct *parms;
  struct clipstruct *cstruct;
  int screen, cx1, cx2, cy1, cy2, x1, x2, y1, y2;
  int i, length, step, num, topmargin, leftmargin, orient, thickness;
  float red, green, blue;


  screen = (W->display)->fildes;
  
  if (id == DRAW) {
     
    parms = (struct gridstruct *) stuff;
    cstruct = (struct clipstruct *) data;

    cx1 = cstruct->x1;
    cx2 = cstruct->x2;
    cy1 = cstruct->y1;
    cy2 = cstruct->y2;

    clip_rectangle(screen, (float)cx1, (float)cx2, (float)cy1, (float)cy2);

    length = parms->length;
    step = parms->step;
    topmargin = parms->topmargin + W->rely;
    leftmargin = parms->leftmargin + W->relx;
    num = parms->num;
    thickness = parms->thickness;
    orient = parms->orient;

    red = (float) (parms->r) / 255.0;  
    green = (float) (parms->g) / 255.0;
    blue = (float) (parms->b) / 255.0;
    
    line_color (screen, red, green, blue);

    if (orient == HORIZONTAL) {
      x1 = leftmargin;  x2 = leftmargin + length;
      
      for (i = 0, y1 = topmargin ; i < num ; i++, y1 += step)
	draw_a_line(screen, x1, y1, x2, y1, thickness);
    }

    if (orient == VERTICAL) {
      y1 = topmargin;  y2 = topmargin + length;
      
      for (i = 0, x1 = leftmargin ; i < num ; i++, x1 += step)
	draw_a_line(screen, x1, y1, x1, y2, thickness);
    }

    clip_rectangle (screen, (float)0.0, (float)((W->display)->width-1), (float)0.0, (float)((W->display)->height-1));
    make_picture_current (screen);
  }
  return (0);
}






int draw_a_line (screen, x1, y1, x2, y2, thick)
int screen, x1, y1, x2, y2, thick;
{
  int i;
  

  for (i = 0 ; i < thick ; i++) {
    move2d(screen, (float)(x1+i), (float)(y1+i));
    draw2d(screen, (float)(x2+i), (float)(y2+i));
  }
  return (0);
}
    
    


