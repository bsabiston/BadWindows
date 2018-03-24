

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
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

#define UP 7000
#define DOWN 7001



/*** This function makes a display, slider, stepper menu combination.  It takes the ***/
/*** standard parameters.  Does NOT set the functions for stepper->pad, just the size ***/

struct Window *MakeStepper(display, locator, Parent, echo, x, y, width, height, orient, b1, b2, b3, s1, s2, s3, h1, h2, h3)     /* v 1.0b */
     struct OutDev *display;
     struct InDev *locator;
     struct Window *Parent;
     struct curstruct *echo;
     int x, y, width, height, b1, b2, b3, s1, s2, s3, h1, h2, h3, orient;
{
  struct curstruct *upstep_icon, *downstep_icon;
  struct Window *Up, *Down, *slider, *pad, *Stepper;
  int padwidth, padheight, upx, upy, dx, dy;
  struct stepperstruct *s, *StepperDo();

  upstep_icon = (struct curstruct *)malloc(sizeof(struct curstruct));
  upstep_icon->rule = redclear;
  LoadBitMap8to24(bw_file("data/icons/upstep_icon"), &upstep_icon->dx, &upstep_icon->dy, &upstep_icon->source, 125, redclear);

  downstep_icon = (struct curstruct *)malloc(sizeof(struct curstruct));
  downstep_icon->rule = redclear;
  LoadBitMap8to24(bw_file("data/icons/downstep_icon"), &downstep_icon->dx, &downstep_icon->dy, &downstep_icon->source, 125, redclear);

  padwidth = width;
  padheight = height;

  Stepper = MakeWindow(display, locator, Parent, x, y, width, height, "stepper menu");
  s = StepperDo(Stepper, echo);

  if (!orient)
    {
      pad = MakeWindow(display, locator, Stepper, 0, 0, width-20, padheight, "pad");
      Maker(pad, 0, 0, -24, 0);
      InstallWin(pad);
      s->pad = pad;
    }
  else
    {
      pad = MakeWindow(display, locator, Stepper, 0, 0, width, padheight-20, "pad");
      Maker(pad, 0, 0, 0, -24);
      InstallWin(pad);
      s->pad = pad;
    }

  SwapColors(upstep_icon->source, upstep_icon->dx, upstep_icon->dy, VLIGHT, VLIGHT, VLIGHT, s1, s2, s3);
  SwapColors(upstep_icon->source, upstep_icon->dx, upstep_icon->dy, FULL, FULL, FULL, h1, h2, h3);
  SwapColors(downstep_icon->source, downstep_icon->dx, downstep_icon->dy, VLIGHT, VLIGHT, VLIGHT, s1, s2, s3);
  SwapColors(downstep_icon->source, downstep_icon->dx, downstep_icon->dy, FULL, FULL, FULL, h1, h2, h3);
  if (orient)
    {
      RotateIcon24(upstep_icon, 3);
      RotateIcon24(downstep_icon, 3);
    }

  if (!orient)
    {
      Up = MakeWindow(display, locator, Stepper, width-20, 0, 20, 20, "slider");
      Maker(Up, -19, 0, 0, 19);
    }
  else
    {
      Up = MakeWindow(display, locator, Stepper, 0, height-20, 20, 20, "slider");
      Maker(Up, 0, -19, 19, 0);
    }
  AttachIcon(Up, upstep_icon);
  Messenger(Up, DO, Stepper, UP, NULL, 02);
  EchoWrap(Up, echo, 3, 0, 0);
  InstallWin(Up);

  Down = MakeWindow(display, locator, Stepper, width-20, height-20, 20, 20, "slider");
  AttachIcon(Down, downstep_icon);
  Messenger(Down, DO, Stepper, DOWN, NULL, 02);
  EchoWrap(Down, echo, 3, 0, 0);
  Maker(Down, -19, -19, 0, 0);
  InstallWin(Down);

  if (!orient)
    {
      slider = MakeWindow(display, locator, Stepper, 20, height-20, 20, height-40, "slider");
      Maker(slider, -19, 20, 0, -20);
      AreaSlider(slider, 1, b1, b2, b3, 0, 0, 0, 0, s1, s2, s3, 0, &s->line, &s->max, &s->min, &s->area);
      Messenger(slider, DO, Stepper, UPDATE, NULL, 02);
      EchoWrap(slider, echo, 7, 0, 0);
    }
  else
    {
      slider = MakeWindow(display, locator, Stepper, width-20, 20, width-40, 20, "slider");
      Maker(slider, 20, -19, -20, 0);
      AreaSlider(slider, 0, b1, b2, b3, 0, 0, 0, 0, s1, s2, s3, 0, &s->line, &s->max, &s->min, &s->area);
      Messenger(slider, DO, Stepper, UPDATE, NULL, 02);
      EchoWrap(slider, echo, 7, 0, 0);
    }
  InstallWin(slider);
  s->slider = slider;

  return(Stepper);
}



struct stepperstruct *StepperDo(W, echo)     /* v 1.0b */
     struct Window *W;
     struct curstruct *echo;
{
  struct stepperstruct *params;
  int DoStepper();

  params = (struct stepperstruct *) malloc(sizeof(struct stepperstruct));
  params->line = 0;
  params->area =0;
  params->min = 0;
  params->max = 0;
  params->slider = NULL;
  params->pad = NULL;
  AttachCommand(W, DO, DoStepper, (char *)params);
  AttachCommand(W, UPDATE, DoStepper, (char *)params);
  AttachCommand(W, UP, DoStepper, (char *)params);
  AttachCommand(W, DOWN, DoStepper, (char *)params);
  EchoWrap(W, echo, 7, 0, 0);
  return(params);
}



DoStepper(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct stepperstruct *step;

  step = (struct stepperstruct *)stuff;

  switch (id)
    {
    case (DO):
      {
	return(1);
      }
      break;

    case (UPDATE):
      UpdateWin(W);
      break;

    case (UP):
      if (step->line)
	{
	  step->line -= step->area;
	  step->line = MAX(step->min, step->line);
	  UpdateWin(step->slider);
	  UpdateWin(step->pad);
	}
      break;

    case (DOWN):
      if ((step->line + step->area) <= (step->max - step->min))
	{
	  step->line += step->area;
	  step->line = MIN(step->max, step->line);
	  UpdateWin(step->slider);
	  UpdateWin(step->pad);
	}
      break;

    }
  return(0);
}

