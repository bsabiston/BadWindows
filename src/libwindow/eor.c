#include <starbase.c.h>
#include <stdio.h>

static int ox1, oy1, ox2, oy2, dotmode;



SetDotMode(d)     /* v 1.0b */
{
  dotmode = d; 
}



EorSolidBox(screen, x1, y1, x2, y2)     /* v 1.0b */
     int screen, x1, y1, x2, y2;
{
  drawing_mode(screen, 6);
  fill_color(screen, 1.0, 1.0, 1.0);
  interior_style(screen, INT_SOLID, FALSE);
  rectangle(screen, (float)x1, (float)y1, (float)x2, (float)y2);
  drawing_mode(screen, 3);
  make_picture_current(screen);
  perimeter_type(screen, 0);
}


EorStyledBox(screen, style, x1, y1, x2, y2)     /* v 1.0b */
     int screen, style, x1, y1, x2, y2;
{
  drawing_mode(screen, 6);
  fill_color(screen, 1.0, 1.0, 1.0);
  interior_style(screen, style, FALSE);
  rectangle(screen, (float)x1, (float)y1, (float)x2, (float)y2);
  drawing_mode(screen, 3);
  make_picture_current(screen);
  perimeter_type(screen, 0);
}



EorBox(display, x1, y1, x2, y2)     /* v 1.0b */
     int display, x1, y1, x2, y2;
{
  float fx1, fx2, fy1, fy2;

  if (dotmode)
    {
      perimeter_repeat_length(display, 100.0);
      perimeter_type(display, DOT);

    }

  fx1 = x1; fy1 = y1;fx2 = x2; fy2 =y2;
  rectangle(display, fx1, fy1, fx2, fy2);
  perimeter_type(display, 0);
}



StartEorBox(screen, x1, y1, x2, y2)     /* v 1.0b */
     int screen, x1, y1, x2, y2;
{
  int xs, ys, xe, ye;

  if (x1<x2) {xs = x1; xe = x2;}
  else {xs = x2; xe = x1;}
  if (y1<y2) {ys = y1; ye = y2;}
  else {ys = y2; ye = y1;}
  ox1 = xs;
  oy1 = ys;
  ox2 = xe;
  oy2 = ye;

  interior_style(screen, INT_HOLLOW, TRUE);
  perimeter_color(screen, 1.0, 1.0, 1.0);
  drawing_mode(screen, 6);
  EorBox(screen, xs, ys, xe, ye);
  drawing_mode(screen, 3);
  make_picture_current(screen);
}



UpdateEorBox(screen, x1, y1, x2, y2)     /* v 1.0b */
     int screen, x1, y1, x2, y2;
{
  int xs, ys, xe, ye;

  if (x1<x2) {xs = x1; xe = x2;}
  else { xs = x2; xe = x1;}
  if (y1<y2) {ys = y1; ye = y2;}
  else { ys = y2; ye = y1;}

  interior_style(screen, INT_HOLLOW, TRUE);
  if ((xs != ox1) || (ys != oy1) || (xe!=ox2) || (ye!=oy2))
    {
      drawing_mode(screen, 6);
      EorBox(screen, ox1, oy1, ox2, oy2);
      make_picture_current(screen); 
      EorBox(screen, xs, ys, xe, ye);
      drawing_mode(screen, 3);
      make_picture_current(screen);
      ox1 = xs;
      oy1 = ys;
      ox2 = xe;
      oy2 = ye;
    }
}



EndEorBox(screen)     /* v 1.0b */
     int screen;
{
  drawing_mode(screen, 6);
  interior_style(screen, INT_HOLLOW, TRUE);
  EorBox(screen, ox1, oy1, ox2, oy2);
  drawing_mode(screen, 3);
  make_picture_current(screen);
}



Order(x1, y1, x2, y2)     /* v 1.0b */
     int *x1, *y1, *x2, *y2;
{
  int temp;
  if (*x1>*x2) {temp = *x1; *x1 = *x2; *x2 = temp;}
  if (*y1>*y2) {temp = *y1; *y1 = *y2; *y2 = temp;}
}





dcEorBox(display, x1, y1, x2, y2)     /* v 1.0b */
     int display, x1, y1, x2, y2;
{
  if (dotmode)
    {
      perimeter_type(display, DOT);
      perimeter_repeat_length(display, 100.0);
    }

  dcrectangle(display, x1, y1, x2, y2);
  perimeter_type(display, 0);
}



dcStartEorBox(screen, x1, y1, x2, y2)     /* v 1.0b */
     int screen, x1, y1, x2, y2;
{
  int xs, ys, xe, ye;

  if (x1<x2) {xs = x1; xe = x2;}
  else {xs = x2; xe = x1;}
  if (y1<y2) {ys = y1; ye = y2;}
  else {ys = y2; ye = y1;}
  ox1 = xs;
  oy1 = ys;
  ox2 = xe;
  oy2 = ye;

  interior_style(screen, INT_HOLLOW, TRUE);
  perimeter_color(screen, 1.0, 1.0, 1.0);
  drawing_mode(screen, 6);
  dcEorBox(screen, xs, ys, xe, ye);
  drawing_mode(screen, 3);
  make_picture_current(screen);
}



dcUpdateEorBox(screen, x1, y1, x2, y2)     /* v 1.0b */
     int screen, x1, y1, x2, y2;
{
  int xs, ys, xe, ye;

  if (x1<x2) {xs = x1; xe = x2;}
  else { xs = x2; xe = x1;}
  if (y1<y2) {ys = y1; ye = y2;}
  else { ys = y2; ye = y1;}

  interior_style(screen, INT_HOLLOW, TRUE);
  if ((xs != ox1) || (ys != oy1) || (xe!=ox2) || (ye!=oy2))
    {
      drawing_mode(screen, 6);
      dcEorBox(screen, ox1, oy1, ox2, oy2);
      dcEorBox(screen, xs, ys, xe, ye);
      drawing_mode(screen, 3);
      make_picture_current(screen);
      ox1 = xs;
      oy1 = ys;
      ox2 = xe;
      oy2 = ye;
    }
}



dcEndEorBox(screen)     /* v 1.0b */
     int screen;
{
  drawing_mode(screen, 6);
  interior_style(screen, INT_HOLLOW, TRUE);
  dcEorBox(screen, ox1, oy1, ox2, oy2);
  drawing_mode(screen, 3);
  make_picture_current(screen);
}
