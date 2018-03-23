

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





/*========================================================*/
/* Equilibrium.c --                                       */
/*                                                        */
/*   Make a set of N sliders, such that the slider system maintains a constant total value T...
/*   Function returns a list of slider windows...
/*
/*   NOTE:  This current is only implemented for normalized float slider systems -- 
/*          specifically, range 0.01 - 1.01, and all slider values always sum to 1.0.
	    LHR -- 4/8/90
/*========================================================*/
#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

#define UPDATE_OTHER_SLIDERS 1
#define UPDATE_REGISTERS     2


struct eqmsg_struct {
  char *delta, *remaining_total;
  int kind;
  struct Window *slider;
};

struct sliderupdate_struct {
  char *slider_data;
  struct List *other_sliders;
};

/* kind INT (0) is integer,  kind FLOAT (1) is float */
/* orient HORIZONTAL (0) is horizontal, orient VERTICAL (1) is vertical */

struct List *EquilibriumSliders(root, parent, echo, wd, ht, num_sliders, 
				list_to_update, 
				msg_win, id, 
				slider_data, orient, red, green, blue, 
				shadow, shadowred, shadowgreen, shadowblue, 
				barred, bargreen, barblue, kind, 
				max, min, total)
     struct Window *root, *parent, *msg_win;
     struct curstruct *echo;
     int wd, ht, num_sliders;
     int id;                             /* <-- id of message to pass to "msg_win" on JUSTUP of a slider */
     struct List *list_to_update;        /* <-- list of register wins to update on a JUSTUP of a slider */
     char *slider_data;                  /* <-- array of initial values for each of the sliders in the system */
     int orient;
     int red, green, blue, shadow, shadowred, shadowgreen;
     int shadowblue, barred, bargreen, barblue;
     int kind;
     char *max, *min;
     char *total;
{
  struct equilibriumstruct *params;
  struct sliderupdate_struct *up;
  struct List *Sliders, *MakeList();
  struct Window *W;
  int i, init_xpos = 100, init_ypos = 100;
  int UpdateSliders(), UpdateRegisterList(), EquilibriumSlideDraw(), EquilibriumSlideDo();
  struct Window *Controller;


  Sliders = (struct List *)MakeList();

  /* Make a dummy window which will control message passing for the equilibrium system... */
  Controller = (struct Window *)MakeWindow(root->display, root->input, parent, 0,0,10,10, "controller");

  /* If there is a list of registers to update, tell the controller about them. */
  if (list_to_update) AttachCommand(Controller, UPDATE_REGISTERS, UpdateRegisterList, list_to_update);

  /* Make the sliders */
  for (i=0; i<num_sliders; i++) {

    if (orient == HORIZONTAL)
      W = (struct Window *)MakeWindow(root->display, root->input, parent, 100, init_ypos+(i*(ht+15)), wd, ht, "slider");
    else
      W = (struct Window *)MakeWindow(root->display, root->input, parent, init_xpos+(i*(wd+15)), 100, wd, ht, "slider");

    params = (struct equilibriumstruct *)malloc(sizeof(struct equilibriumstruct));
    params->num_sliders = num_sliders;
    params->kind = kind;
    params->orient = orient;
    params->red = red;
    params->green = green;
    params->blue = blue;
    params->shadow = shadow;
    params->shadowred = shadowred;
    params->shadowgreen = shadowgreen;
    params->shadowblue = shadowblue;
    params->barred = barred;
    params->bargreen = bargreen;
    params->barblue = barblue;
    params->max = max;
    params->min = min;
    params->total = total;
    params->controller = (struct Window *)Controller;
    if (kind) params->number = (char *) (((float *)slider_data)+i);
    else params->number = (char *) (((int *)slider_data)+i);
    
    AttachCommand(W, DRAW, EquilibriumSlideDraw, (char *)params);
    AttachCommand(W, DO, EquilibriumSlideDo, (char *)params);

    /* if there is a list of registers passed in, make sure they get updated when the slider is in action. */
    if (list_to_update) Messenger(W, DO, Controller, UPDATE_REGISTERS, NULL, JUSTDOWN|JUSTUP|BEENDOWN);

    /* if there is a window to update on JUSTUP of a slider, do it. */
    if (msg_win) Messenger(W, DO, msg_win, id, NULL, JUSTUP);

    EchoWrap(W, echo, JUSTUP|JUSTDOWN|BEENDOWN,1,0,0);
    AddToList(Sliders,W);
  }

  /* Tell the controller about the other sliders... */
  up = (struct sliderupdate_struct *)malloc(sizeof(struct sliderupdate_struct));
  up->slider_data = (char *)slider_data;
  up->other_sliders = Sliders;
  AttachCommand(Controller, UPDATE_OTHER_SLIDERS, UpdateSliders, (char *)up);

  return(Sliders);
}


UpdateRegisterList(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{
  struct List *L, *current = NULL;

  L = (struct List *)stuff;
  for (current = L->Front; current->id != NULL; current = current->Front)
    UpdateWin(current->id);
  return(0);
}


UpdateSliders(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{

  struct List *current = NULL;
  struct eqmsg_struct *parms;
  struct sliderupdate_struct *update;
  int i, kind, *delta, *total, *value_array, *val;
  float *fdelta, *ftotal, *fvalue_array, *fval;

  parms = (struct eqmsg_struct *)data;
  update = (struct sliderupdate_struct *)stuff;

  kind = parms->kind;
  if (kind) {
    fdelta = (float *)parms->delta;
    ftotal = (float *)parms->remaining_total;
    fvalue_array = (float *)update->slider_data;
  }
  else {
    delta = (int *)parms->delta;
    total = (int *)parms->remaining_total;
    value_array = (int *)update->slider_data;
  }

  for (current = update->other_sliders->Front, i=0; current->id != NULL; current = current->Front, i++) {
    if (current->id == parms->slider) continue;
    
    /* Set the rest of the sliders to maintain equilibrium */
    if (kind) {
      fval = fvalue_array+i;
      *fval -= (float)(((*fval)/(*ftotal)) * (*fdelta));
    }
    else {
      val = value_array+i;
      *val -= (int)(((*val)/(*total)) * (*delta));
    }
    
    UpdateWin(current->id);
  }

  return(0);
  }


EquilibriumSlideDraw(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct equilibriumstruct *params;
  int x1, x2, y1, y2, screen, shadow, t, x, y;
  int barred, bargreen, barblue;
  float fx1, fx2, fy1, fy2;
  float cx1, cx2, cy1, cy2;
  float red, green, blue;
  struct clipstruct *cstruct;
  int *number, *max, kind, *min;
  float *fnumber, *fmax, ratio, *fmin;

  screen = (W->display)->fildes;
  cstruct = (struct clipstruct *)data;
  cx1 = cstruct->x1;
  cy1 = cstruct->y1;
  cx2 = cstruct->x2;
  cy2 = cstruct->y2;
  clip_rectangle(screen, cx1, cx2, cy1, cy2);

  params = (struct equilibriumstruct *)stuff;
  shadow = params->shadow;
  kind = params->kind;

  max = NULL;    min = NULL;
  fmax = NULL;   fmin = NULL;
  number = NULL; fnumber = NULL;

  if (kind) fnumber=(float *)params->number, fmax=(float *)params->max, fmin=(float *)params->min;
  else number=(int *)params->number, max=(int *)params->max, min=(int *)params->min;

  red = ((float)(params->red)/255.0);
  green = ((float)(params->green)/255.0);
  blue = ((float)(params->blue)/255.0);
  fill_color(screen, red, green, blue);

  red = ((float)(params->shadowred)/255.0);
  green = ((float)(params->shadowgreen)/255.0);
  blue = ((float)(params->shadowblue)/255.0);
  line_color(screen, red, green, blue);
  perimeter_color(screen, red, green, blue);
  interior_style(screen, INT_SOLID, TRUE);

  x1 = W->x1; y1 = W->y1; x2 = W->x2; y2 = W->y2;

  if (x1>x2) {t = x2; x2 = x1; x1 = t;}
  if (y1>y2) {t = y2; y2 = y1; y1 = t;}

  x2 -= (float)shadow; y2 -= (float)shadow;

  fx1=x1; fx2=x2;
  fy1=y1; fy2=y2;

  rectangle(screen, fx1, fy1, fx2, fy2);

  red = ((float)(params->barred)/255.0);
  green = ((float)(params->bargreen)/255.0);
  blue = ((float)(params->barblue)/255.0);
  fill_color(screen, red, green, blue);

  if (kind) ratio = (*fnumber-*fmin)/(*fmax-*fmin);
  else      ratio = ((float)*number - (float)*min)/((float)*max-(float)*min);

  if (params->orient)
    {
      float ratline;
      ratline = fy2-ratio*(fy2-fy1-3.0)-2.0;
      rectangle(screen, fx1, ratline, fx2, ratline+4.0);
    }
  else
    {
      float ratline;
      ratline = fx1+ratio*(fx2-fx1-3.0)-2.0;
      rectangle(screen, ratline, fy1, ratline+4.0, fy2);
    }

  for (t=0; t<shadow; t++)
    {
      fx1 += 1.0;
      fy1 += 1.0;
      fy2 += 1.0;
      fx2 += 1.0;

      move2d(screen, fx1, fy2);
      draw2d(screen, fx2, fy2);
      move2d(screen, fx2, fy1);
      draw2d(screen, fx2, fy2);
    }

  clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1), 
		 0.0, (float)((W->display)->height-1));
  make_picture_current((W->display)->fildes);
}



EquilibriumSlideDo(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  static new = 0;
  struct messenger *mstruct;
  struct eqmsg_struct *eqstruct;
  struct equilibriumstruct *params;
  struct Window *controller;
  float *old_fnum, *fnum=NULL, *fmax=NULL, ratio, *fmin, *ftotal, *fdelta;
  int x, y, button, kind, *old_num, *num=NULL, *max=NULL, *min=NULL, *total=NULL, dx, dy, *delta=NULL;
  struct pickstruct *pick;

  params = (struct equilibriumstruct *)stuff;
  kind = params->kind;
  if (kind) fnum=(float *)params->number, fmax=(float *)params->max, fmin=(float *)params->min;
  else num=(int *)params->number, max = (int *)params->max, min = (int *)params->min;

  controller = params->controller;

  pick = (struct pickstruct *)data;
  x = pick->x;
  y = pick->y;

  dx = MAX(x, W->x1);
  dy = MAX(y, W->y1);
  dx = MIN(dx, W->x2);
  dy = MIN(dy, W->y2);
  button = pick->button;
  switch (button)
    {
    case (JUSTDOWN):
      Dispatch(W, TRAP, MakeTrap(W, BEENUP), NULL);
      new = 1;

    case (JUSTUP):
    case (BEENDOWN):

      if (new)
	{
	  if (params->orient) ratio = (float)(W->y2-dy)/(float)(W->height-params->shadow);
	  else                ratio = (float)(dx-W->x1)/(float)(W->width-params->shadow);

	  eqstruct = (struct eqmsg_struct *)malloc(sizeof(struct eqmsg_struct));
	  eqstruct->kind = kind;
	  eqstruct->slider = W;
	  if (kind) {
	    old_fnum = (float *)malloc(sizeof(float));
	    *old_fnum = *fnum;
	    *fnum = *fmin+ratio*(*fmax-*fmin);
	    *fnum = MAX(*fnum, *fmin);
	    *fnum = MIN(*fnum, *fmax);

	    fdelta = (float *)malloc(sizeof(float));
	    *fdelta = *fnum - *old_fnum;
	    eqstruct->delta = (char *)fdelta;
	    ftotal = (float *)malloc(sizeof(float));
	    *ftotal = (1.0 - *((float *)old_fnum));
	    eqstruct->remaining_total = (char *)ftotal;
	    SendMessage(controller, UPDATE_OTHER_SLIDERS, eqstruct);

	  }
	  else {
	    old_num = (float *)malloc(sizeof(float));
	    *old_num = *num;
	    *num = ((float)*min + ratio*((float)*max-(float)*min));
	    *num = MAX(*num, *min);
	    *num = MIN(*num, *max);
	    *delta = *num - *old_num;
	    eqstruct->delta = (char *)delta;
	    total = (int *)malloc(sizeof(int));
	    *total = (1 - *((int *)old_num));
	    eqstruct->remaining_total = (char *)total;
	    SendMessage(controller, UPDATE_OTHER_SLIDERS, eqstruct);
	  }
	  UpdateWin(W);

	  if (id == JUSTUP) new = 0;
	}
      break;

    }
  return(0);
}
