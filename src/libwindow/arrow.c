/************************************
*                                   *
* ARROW.C                           *
*                                   *
* by Dave Small                     *
*    Laura  H. Robin                *
* date: 29 Nov  1989                *
* version 1.0B                      *
*                                   *
************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <sketch.h>

#define ADJUSTSIZES 1007
#define CHANGEPOINT 1008
#define CHANGEPOINTONLY 1009

extern unsigned char *ctable,*mcontrol;
extern int CurrentRed, CurrentGreen, CurrentBlue;

static char line_table[] = "data/100.tab";

struct ArrowStruct {
  int x1, y1, x2, y2;
  float width;
  int arrow_flag;
  int arrow_length;
  int arrow_wd;
  int r, g, b, t;
};

struct ConnectStruct {
  struct Window *W, *Arrow;
  int xoff, yoff, endpoint;
};

Connectify(W, Arrow, xoff, yoff, endpoint)
struct Window *W, *Arrow;
int xoff, yoff, endpoint;
{
  struct ConnectStruct *fd;
  int ConnectWin();
  
  if ((fd = (struct ConnectStruct *) malloc (sizeof (struct ConnectStruct))) == 0)
    printf ("error mallocing ConnectStruct\n");
  
  fd->W = W;
  fd->Arrow = Arrow;
  fd->xoff = xoff;
  fd->yoff = yoff;
  fd->endpoint = endpoint;

  AttachCommand(W,MAKE,ConnectWin,(char *)fd);

  SendMessage(Arrow, CHANGEPOINTONLY, (char *)fd);
}

UnConnectify(W)
struct Window *W;
{
  struct ConnectStruct *fd;
  int ConnectWin();
  
  fd = (struct ConnectStruct *)GetArguments(W,MAKE,ConnectWin);
  if (fd) free(fd);
  DetachCommand(W,MAKE,ConnectWin);
}

ConnectWin(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
  struct ConnectStruct *params;

  params = (struct ConnectStruct *)stuff;
  switch (id) {
  case (MAKE):
    SendMessage(params->Arrow, CHANGEPOINT, (char *)params);
    break;
  default:
    printf("Unknown message: %d\n", id);
    break;
  }
  return(0);
}


Arrowify(W, x1, y1, x2, y2, width, arrow_flag, arrow_length, arrow_wd, r, g, b, t)
     struct Window *W;
     int x1, y1, x2, y2;
     float width;
     int arrow_flag, arrow_length, arrow_wd;
     int r, g, b, t;
{
  struct ArrowStruct *fd;
  int ArrowWin();
  
  read_short_table (bw_file(line_table));
  aa_set_fb (W->display->fildes,(W->display)->bits, (W->display)->buffer, (W->display)->control,W->display->width,W->display->height);
  
  if ((fd = (struct ArrowStruct *) malloc (sizeof (struct ArrowStruct))) == 0)
    printf ("error mallocing ArrowStruct\n");
  
  fd->x1 = x1;
  fd->y1 = y1;
  fd->x2 = x2;
  fd->y2 = y2;
  fd->width = width;
  fd->arrow_flag = arrow_flag;
  fd->arrow_length = arrow_length;
  fd->arrow_wd = arrow_wd;
  fd->r = r;
  fd->g = g;
  fd->b = b;
  fd->t = 255 - t;

  AttachCommand(W,DO,ArrowWin,fd);
  AttachCommand(W,DRAW,ArrowWin,fd);
  AttachCommand(W,ADJUSTSIZES,ArrowWin,fd);
  AttachCommand(W,CHANGEPOINT,ArrowWin,fd);
  AttachCommand(W,CHANGEPOINTONLY,ArrowWin,fd);

  SendMessage(W,ADJUSTSIZES,NULL);
}

ArrowWin(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
  struct clipstruct *cstruct;
  struct ArrowStruct *params;
  int cx1,cx2,cy1,cy2;
  int screen;
  struct pickstruct *pick;
  float p, fx, fy;
  int x, y, button;
  int r, g, b, t;
  static int selected = 0;
  int minx, miny, maxx, maxy;
  static int init, lastx1 = 0, lasty1 = 0, lastx2 = 0, lasty2 = 0;
  float x1, y1, x2, y2, px, py, l1, l2;
  struct ConnectStruct *Connect;

  screen = (W->display)->fildes;
  params = (struct ArrowStruct *)stuff;

  switch (id) {
  case (DRAW):
    cstruct = (struct clipstruct *)data;
    cx1 = cstruct->x1;  cy1 = cstruct->y1;
    cx2 = cstruct->x2;  cy2 = cstruct->y2;

    W->display->control [3] = 4;
    W->display->control [0x40bf] = 7;
    W->display->control [0x40ef] = 0x33;
    drawing_mode(W->display->fildes, 3);
    make_picture_current(W->display->fildes);

    x1 = (float) params->x1;
    y1 = (float) params->y1;
    x2 = (float) params->x2;
    y2 = (float) params->y2;

    aa_set_clip (cx1, cy1, cx2, cy2);
    aa_set_fb (W->display->fildes,(W->display)->bits, (W->display)->buffer, (W->display)->control,W->display->width,W->display->height);
    aa_set_color (params->r, params->g, params->b);
    aa_set_trans (params->t);
    aa_move (x1, y1, params->width);
    aa_draw (x2, y2, params->width);
    aa_done ();

    if (params->arrow_flag)
      l1 = params->arrow_length/sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
      l2 = params->arrow_wd/sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    if (params->arrow_flag == BEGIN || params->arrow_flag == BOTH) {
      /** draw arrow at begining **/
      aa_move (x1, y1, params->width);
      px = x1 + l1*(x2-x1) - l2*(y2-y1);
      py = y1 + l1*(y2-y1) + l2*(x2-x1);
      aa_draw (px, py, params->width);
      aa_done ();
      
      aa_move (x1, y1, params->width);
      px = x1 + l1*(x2-x1) + l2*(y2-y1);
      py = y1 + l1*(y2-y1) - l2*(x2-x1);
      aa_draw (px, py, params->width);
      aa_done ();
    }
    if (params->arrow_flag == END || params->arrow_flag == BOTH) {
      /** draw arrow at end **/
      aa_move (x2, y2, params->width);
      px = x2 - l1*(x2-x1) + l2*(y2-y1);
      py = y2 - l1*(y2-y1) - l2*(x2-x1);
      aa_draw (px, py, params->width);
      aa_done ();
      
      aa_move (x2, y2, params->width);
      px = x2 - l1*(x2-x1) - l2*(y2-y1);
      py = y2 - l1*(y2-y1) + l2*(x2-x1);
      aa_draw (px, py, params->width);
      aa_done ();
    }
    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(screen);
    break;
  case (DO):
    pick = (struct pickstruct *)data;
    x = pick->x;
    y = pick->y;
    p = pick->p;
    button = pick->button;

    switch (button) {
    case (JUSTDOWN):
      selected = 0;
      if ( abs(params->x1 - x) < 10 )
	if ( abs(params->y1 - y) < 10 ) 
	  selected = 1;
      if ( abs(params->x2 - x) < 10 )
	if ( abs(params->y2 - y) < 10 ) 
	  selected = 2;
      if (selected)
	init = TRUE;
      break;
    case (BEENDOWN):
      if (selected) {
	if (selected == 1) {
	  params->x1 = x;
	  params->y1 = y;
	}
	else {
	  params->x2 = x;
	  params->y2 = y;
	}
	line_color(screen, 1.0, 1.0, 1.0);
	drawing_mode(screen, 6);
	make_picture_current(screen);
	
	if (init)
	  init = FALSE;
	else {
	  move2d(screen, (float)lastx1, (float)lasty1);
	  draw2d(screen, (float)lastx2, (float)lasty2);
	}
	
	move2d(screen, (float)params->x1, (float)params->y1);
	draw2d(screen, (float)params->x2, (float)params->y2);
	
	lastx1 = params->x1;
	lasty1 = params->y1;
	lastx2 = params->x2;
	lasty2 = params->y2;
	make_picture_current(screen);
	drawing_mode(screen, 3);
	make_picture_current(screen);
      }
      break;
    case (JUSTUP):
      if (selected) {
	line_color(screen, 1.0, 1.0, 1.0);
	drawing_mode(screen, 6);
	move2d(screen, (float)lastx1, (float)lasty1);
	draw2d(screen, (float)lastx2, (float)lasty2);
	drawing_mode(screen, 3);
	make_picture_current(screen);

	CloseWindow(W);
	SendMessage(W, ADJUSTSIZES, NULL);
	OpenWindow(W);
      }
      break;
    case (BEENUP):
      break;
    }
    break;
  case (ADJUSTSIZES):
    if (params->x1 < params->x2) {
      minx = (params->x1 - params->width) - 10.0;
      maxx = (params->x2 + params->width) + 10.0;
    }
    else {
      minx = (params->x2 - params->width) - 10.0;
      maxx = (params->x1 + params->width) + 10.0;
    }

    if (params->y1 < params->y2) {
      miny = (params->y1 - params->width) - 10.0;
      maxy = (params->y2 + params->width) + 10.0;
    }
    else {
      miny = (params->y2 - params->width) - 10.0;
      maxy = (params->y1 + params->width) + 10.0;
    }
    TransformCoords(W, minx, miny, maxx - minx, maxy - miny);
    break;
  case (CHANGEPOINT):
    Connect = (struct ConnectStruct *)data;
    CloseWindow(W);
    if (Connect->endpoint == BEGIN) {
      params->x1 = Connect->W->x1 + Connect->xoff;
      params->y1 = Connect->W->y1 + Connect->yoff;
    }
    else {
      params->x2 = Connect->W->x1 + Connect->xoff;
      params->y2 = Connect->W->y1 + Connect->yoff;
    }
    SendMessage(W, ADJUSTSIZES, NULL);
    OpenWindow(W);
    break;
  case (CHANGEPOINTONLY):
    Connect = (struct ConnectStruct *)data;
    if (Connect->endpoint == BEGIN) {
      params->x1 = Connect->W->x1 + Connect->xoff;
      params->y1 = Connect->W->y1 + Connect->yoff;
    }
    else {
      params->x2 = Connect->W->x1 + Connect->xoff;
      params->y2 = Connect->W->y1 + Connect->yoff;
    }
    SendMessage(W, ADJUSTSIZES, NULL);
    break;
  default:
    printf("Unknown message: %d\n", id);
    break;
  }
  return(0);
}

/***************************/
/* a line draw function    */
/***************************/

struct LineStruct {
  int x1, y1, x2, y2;
  int r, g, b;
};

Lineify(W, x1, y1, x2, y2, r, g, b)
struct Window *W;
int x1, y1, x2, y2;
int r, g, b;
{
  struct LineStruct *fd;
  int LineWin();
  
  if ((fd = (struct LineStruct *) malloc (sizeof (struct LineStruct))) == 0)
    printf ("error mallocing LineStruct\n");
  
  fd->x1 = x1;
  fd->x2 = x2;
  fd->y1 = y1;
  fd->y2 = y2;
  fd->r = r;
  fd->g = g;
  fd->b = b;

  AttachCommand(W,DRAW,LineWin,(char *)fd);
}

LineWin(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
  struct LineStruct *params;
  struct clipstruct *cstruct;
  int cx1,cx2,cy1,cy2;
  int screen;
  float x1, y1, x2, y2;

  screen = (W->display)->fildes;

  params = (struct LineStruct *)stuff;

  switch (id) {
  case (DRAW):
    cstruct = (struct clipstruct *)data;
    cx1 = cstruct->x1;  cy1 = cstruct->y1;
    cx2 = cstruct->x2;  cy2 = cstruct->y2;

    x1 = (float) (W->x1 + params->x1);
    y1 = (float) (W->y1 + params->y1);
    x2 = (float) (W->x1 + params->x2);
    y2 = (float) (W->y1 + params->y2);

    line_color(screen, params->r / 255.0, 
	       params->g / 255.0,
	       params->b / 255.0);

    move2d(screen, x1, y1);
    draw2d(screen, x2, y2);

    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(screen);
    break;

    break;
  default:
    printf("Unknown message: %d\n", id);
    break;
  }
  return(0);
}
