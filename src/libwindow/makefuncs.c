#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>

struct makemessstruct
{
  int x1, y1, x2, y2;
  struct Window *dest;
  int id;
  char *data;
};



Maker(W, x1, y1, x2, y2)     /* v 1.0b */
     struct Window *W;
     int x1, y1, x2, y2;
{
  int MakeWin();
  struct makestruct *params;

  params = (struct makestruct *)malloc(sizeof(struct makestruct));
  params->x1 = x1;
  params->y1 = y1;
  params->x2 = x2;
  params->y2 = y2;

  AttachCommand(W, MAKE, MakeWin, (char *)params);
}



MakerMessage(W, x1, y1, x2, y2, W2, id, data)     /* v 1.0b */
     struct Window *W, *W2;
     int x1, y1, x2, y2, id;
     char *data;
{
  int MakeMessWin();
  struct makemessstruct *params;

  params = (struct makemessstruct *)malloc(sizeof(struct makemessstruct));
  params->x1 = x1;
  params->y1 = y1;
  params->x2 = x2;
  params->y2 = y2;
  params->dest = W2;
  params->id = id;
  params->data = data;

  AttachCommand(W, MAKE, MakeMessWin, (char *)params);
}



MakeWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct makestruct *param;
  int x1, y1, x2, y2;

  param = (struct makestruct *)stuff;

  x1 = param->x1;
  y1 = param->y1;

  if (x1<0) x1 += ((W->parent)->width-1);
  if (y1<0) y1 += ((W->parent)->height-1);

  x2 = param->x2;
  y2 = param->y2;

  if (x2<=0) x2 += ((W->parent)->width-1);
  if (y2<=0) y2 += ((W->parent)->height-1);

  x2 -= (x1-1);
  y2 -= (y1-1);

  TransformCoords(W, x1, y1, x2, y2);
}



PerMaker(W, x1, y1, x2, y2)     /* v 1.0b */
     struct Window *W;
     float x1, y1, x2, y2;
{
  int PerMakeWin();
  struct permakestruct *params;

  params = (struct permakestruct *)malloc(sizeof(struct permakestruct));
  params->x1 = x1;
  params->y1 = y1;
  params->x2 = x2;
  params->y2 = y2;

  AttachCommand(W, MAKE, PerMakeWin, (char *)params);
}



PerMakeWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct permakestruct *param;
  int x1, y1, x2, y2;
  float fx1, fy1, fx2, fy2;

  param = (struct permakestruct *)stuff;

  fx1 = param->x1;
  fy1 = param->y1;

  x1 = fx1*(float)(W->parent->width-1);
  y1 = fy1*(float)(W->parent->height-1);

  if (x1<0) x1 += ((W->parent)->width-1);
  if (y1<0) y1 += ((W->parent)->height-1);

  fx2 = param->x2;
  fy2 = param->y2;

  x2 = fx2*(float)(W->parent->width-1);
  y2 = fy2*(float)(W->parent->height-1);

  if (x2<=0) x2 += (float)((W->parent)->width-1);
  if (y2<=0) y2 += (float)((W->parent)->height-1);

  x2 -= (x1-1);
  y2 -= (y1-1);

  TransformCoords(W, x1, y1, x2, y2);
}



DoubleMaker(W, hx1, hy1, hx2, hy2, vx1, vy1, vx2, vy2)     /* v 1.0b */
     struct Window *W;
     int hx1, hy1, hx2, hy2;
     int vx1, vy1, vx2, vy2;
{
  int DoubleMakeWin();
  int *parms;

  parms = (int *)malloc(8*sizeof(int));
  *(parms+0) = hx1;
  *(parms+1) = hy1;
  *(parms+2) = hx2;
  *(parms+3) = hy2;
  *(parms+4) = vx1;
  *(parms+5) = vy1;
  *(parms+6) = vx2;
  *(parms+7) = vy2;

  AttachCommand(W, MAKE, DoubleMakeWin, (char *)parms);
}



DoubleMakeWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int x1, y1, x2, y2, *parms;

  parms = (int *)stuff;
  if (W->parent->width > W->parent->height)   /* horizontal */
    {
      x1 = *(parms+0);
      y1 = *(parms+1);

      if (x1<0) x1 += ((W->parent)->width-1);
      if (y1<0) y1 += ((W->parent)->height-1);

      x2 = *(parms+2);
      y2 = *(parms+3);

      if (x2<=0) x2 += ((W->parent)->width-1);
      if (y2<=0) y2 += ((W->parent)->height-1);

      x2 -= (x1-1);
      y2 -= (y1-1);
    }

  else
    {
      x1 = *(parms+4);
      y1 = *(parms+5);

      if (x1<0) x1 += ((W->parent)->width-1);
      if (y1<0) y1 += ((W->parent)->height-1);

      x2 = *(parms+6);
      y2 = *(parms+7);

      if (x2<=0) x2 += ((W->parent)->width-1);
      if (y2<=0) y2 += ((W->parent)->height-1);

      x2 -= (x1-1);
      y2 -= (y1-1);
    }

  TransformCoords(W, x1, y1, x2, y2);
}



MakeMessWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct makemessstruct *param;
  int x1, y1, x2, y2;

  param = (struct makemessstruct *)stuff;

  x1 = param->x1;
  y1 = param->y1;

  if (x1<0) x1 += ((W->parent)->width-1);
  if (y1<0) y1 += ((W->parent)->height-1);

  x2 = param->x2;
  y2 = param->y2;

  if (x2<=0) x2 += ((W->parent)->width-1);
  if (y2<=0) y2 += ((W->parent)->height-1);

  x2 -= (x1-1);
  y2 -= (y1-1);
  TransformCoords(W, x1, y1, x2, y2);

  SendMessage(param->dest, param->id, param->data);
}

