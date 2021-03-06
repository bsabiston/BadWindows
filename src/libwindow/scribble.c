

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





/*****************************

  SCRIBLE.C

  Dave Small Sept 27, 89

*****************************/
#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <string.h>
#include <math.h>
#include "sketch.h"

struct ScribbleStruct {
  char *path;
  int x, y;
};

static char line_table[] = "/vlw/data/100.tab";

/******************************************************************

  Scribble window is a window that reads in a drawing
data file and draws it as a draw function.  It opens
the file and reads the data EVERY time it draws.  It might
be faster if you keep the scribble file on a local machine.
MakeScribbleWindow is a higher level funtion which determines
the size needed from a particular drawing file (using the
GetScribbleBoundingBox function), makes a window, attaches Echo
Wrap and Scribblify, and then Opens the window.

Note- the x and y passed to Scribblify are NOT the x and y 
coords of the window.  They are offsets to use when reading in
the drawing file, which is stored in absolute rather than relative
coords.  This puts it into a local coord frame.

******************************************************************/

struct Window *MakeScribbleWindow(Parent, pointer, path)
struct Window *Parent;
struct curstruct *pointer;
char *path;
{
  struct Window *W;
  int x1, y1, x2, y2, xoff=0, yoff=0;

#if 0
  printf("YO!!! I have changed this code (MakeScribbleWindow)! It takes three (3) args!!!!!!! - dsmall 4/25/90\n");
#endif

  /* This returns absolute coords */
  GetScribbleBoundingBox(path, &x1, &y1, &x2, &y2);

/***  GetOffsets(Parent, x1, y1, &xoff, &yoff);***/

  xoff = x1 - Parent->x1;
  yoff = y1 - Parent->y1;
  if (xoff > (Parent->width - (x2-x1))) xoff = Parent->width - (x2-x1);
  if (yoff > (Parent->height - (y2-y1))) yoff = Parent->height - (y2-y1);
  if (xoff < 0) xoff = 0;
  if (yoff < 0) yoff = 0;

  W=(struct Window *)MakeWindow(Parent->display, Parent->input, Parent,
				     xoff, yoff, x2 - x1, y2 - y1, path);
  Mover(W, W);
  EchoWrap(W, pointer, 1, 0, 0);
  EchoRect(W, 255, 50, 50);
  Scribblify(W, path, x1, y1);
  
  OpenWindow(W);
  return(W);
}

struct Window *MakeScribbleWindowII(Parent, pointer, path)
struct Window *Parent;
struct curstruct *pointer;
char *path;
{
  struct Window *W;
  int x1, y1, x2, y2, xoff=0, yoff=0;

  /* This returns absolute coords */
  GetScribbleBoundingBox(path, &x1, &y1, &x2, &y2);
/***  GetOffsets(Parent, x1, y1, &xoff, &yoff);***/

  xoff = x1 - Parent->x1;
  yoff = y1 - Parent->y1;
  if (xoff > (Parent->width - (x2-x1))) xoff = Parent->width - (x2-x1);
  if (yoff > (Parent->height - (y2-y1))) yoff = Parent->height - (y2-y1);
  if (xoff < 0) xoff = 0;
  if (yoff < 0) yoff = 0;

  W=(struct Window *)MakeWindow(Parent->display, Parent->input, Parent,
				     xoff, yoff, x2 - x1, y2 - y1, path);
  EchoWrap(W, pointer, 1, 0, 0);
  Scribblify(W, path, x1, y1);
  
  OpenWindow(W);
  return(W);
}


GetOffsets(Parent, absx, absy, offsetx, offsety)
     struct Window *Parent;
     int absx, absy;
     int *offsetx, *offsety;
{
  int xoff, yoff;
  struct Window *w;

  for(w = Parent, xoff = absx, yoff = absy; w->parent; w = w->parent) {
    xoff -= w->x1;
    yoff -= w->y1;
  }
  *offsetx = absx - xoff;
  *offsety = absy - yoff;
}


Scribblify(W, scribble_path, x, y)
     struct Window *W;
     char *scribble_path;
     int x, y;
{
  struct ScribbleStruct *fd;
  int ScribbleWin();
  char *path;

  path = (char *) malloc(sizeof(char) * strlen(scribble_path) + 1);
  strcpy(path, scribble_path);

  read_short_table (bw_file(line_table));
  
  if ((fd = (struct ScribbleStruct *) malloc (sizeof (struct ScribbleStruct))) == 0)
    printf ("error mallocing ScribbleStruct\n");
  
  fd->path = path;
  fd->x = x;
  fd->y = y;

  AttachCommand(W,DRAW,ScribbleWin,fd);

}

ScribbleWin(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
  struct clipstruct *cstruct;
  struct ScribbleStruct *params;
  int cx1,cx2,cy1,cy2;
  int screen;
  int r, g, b, t;
  float wd, wid;
  float fx, fy;
  int flag, draw_flag = 1;
  FILE *fp, *fopen();
  char *path;
  int xoff, yoff;

  screen = (W->display)->fildes;
  params = (struct ScribbleStruct *)stuff;

  path = params->path;
  xoff = W->x1 - params->x;
  yoff = W->y1 - params->y;

  switch (id) {
  case (DRAW):
    cstruct = (struct clipstruct *)data;
    cx1 = cstruct->x1;  cy1 = cstruct->y1;
    cx2 = cstruct->x2;  cy2 = cstruct->y2;
    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(W->display->fildes);

/*    DrawMask(W, cx1, cy1, cx2, cy2);*/

    W->display->control [3] = 4;
    W->display->control [0x40bf] = 7;
    W->display->control [0x40ef] = 0x33;
    drawing_mode(W->display->fildes, 3);
    
    aa_set_clip (cx1, cy1, cx2, cy2);
    aa_set_fb (W->display->fildes,(W->display)->bits, (W->display)->buffer, (W->display)->control,W->display->width,W->display->height);
    aa_set_color(0, 0, 0);
    aa_set_trans(128);

    W->display->control [3] = 4;
    W->display->control [0x40bf] = 7;
    W->display->control [0x40ef] = 0x33;
    drawing_mode(W->display->fildes, 3);
    make_picture_current(W->display->fildes);
    
    if ((fp = fopen(path, "r")) == 0)
      printf("Error opening %s\n", path);

    while((fread(&flag, sizeof(int), 1, fp))!=0)
      {
	switch (flag)
	  {
	  case (DO_MOVE):
	    fread(&fx, sizeof(float), 1, fp);
	    fread(&fy, sizeof(float), 1, fp);
	    fread(&wid, sizeof(float), 1, fp);
	    fx += xoff;
	    fy += yoff;
	    aa_move(fx, fy, wid);
	    break;
	  case (DO_DRAW):
	    fread(&fx, sizeof(float), 1, fp);
	    fread(&fy, sizeof(float), 1, fp);
	    fread(&wid, sizeof(float), 1, fp);
	    fx += xoff;
	    fy += yoff;
	    aa_draw(fx, fy, wid);
	    break;
	  case (SET_COLOR):
	    fread(&r, sizeof(int), 1, fp);
	    fread(&g, sizeof(int), 1, fp);
	    fread(&b, sizeof(int), 1, fp);
	    aa_set_color(r, g, b);
	    break;
	  case (SET_TRANS):
	    fread(&t, sizeof(int), 1, fp);
	    aa_set_trans(t);
	    break;
	  case (DO_DONE):
	    aa_done();
	    break;
	  default:
	    printf("Duhhh...  Dunno dat one Charly\n");
	  }
      }
    fclose (fp);

    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(screen);
    break;
  default:
    printf("Unknown message: %d\n", id);
    break;
  }
  return(0);
}



GetScribbleBoundingBox(path, x1, y1, x2, y2)
char *path;
int *x1, *y1, *x2, *y2;
{
  float fx, fy, wid, r, g, b, t;
  float minx = 1280.0, miny = 1024.0, maxx = 0.0, maxy = 0.0;
  FILE *fp, *fopen();
  int flag, draw_flag = 1;


  if ((fp = fopen(path, "r")) == 0)
    printf("Error opening %s\n", path);
  else {
    while((fread(&flag, sizeof(int), 1, fp))!=0)
      {
	switch (flag)
	  {
	  case (DO_MOVE):
	    fread(&fx, sizeof(float), 1, fp);
	    fread(&fy, sizeof(float), 1, fp);
	    fread(&wid, sizeof(float), 1, fp);
	    if ((fx - wid) < minx) minx = fx - wid;
	    if ((fy - wid) < miny) miny = fy - wid;
	    if ((fx + wid) > maxx) maxx = fx + wid;
	    if ((fy + wid) > maxy) maxy = fy + wid;
	    break;
	  case (DO_DRAW):
	    fread(&fx, sizeof(float), 1, fp);
	    fread(&fy, sizeof(float), 1, fp);
	    fread(&wid, sizeof(float), 1, fp);
	    if ((fx - wid) < minx) minx = fx - wid;
	    if ((fy - wid) < miny) miny = fy - wid;
	    if ((fx + wid) > maxx) maxx = fx + wid;
	    if ((fy + wid) > maxy) maxy = fy + wid;
	    break;
	  case (SET_COLOR):
	    fread(&r, sizeof(int), 1, fp);
	    fread(&g, sizeof(int), 1, fp);
	    fread(&b, sizeof(int), 1, fp);
	    break;
	  case (SET_TRANS):
	    fread(&t, sizeof(int), 1, fp);
	    break;
	  default:
	    printf("Duhhh...  Dunno dat one Charly\n");
	  }
      }
    fclose (fp);
    
    *x1 = (int) (floor(minx));
    *y1 = (int) (floor(miny));
    *x2 = (int) (ceil(maxx));
    *y2 = (int) (ceil(maxy));
  }
}

