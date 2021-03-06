

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





/************************************
*                                   *
* INDICATOR.C                       *
*                                   *
* by David Small                    *
* date:  23 Sep 1989                *
* version:  1.0                     *
*                                   *
************************************/

#include <stdio.h>
#include <starbase.c.h>
#include <string.h>
#include <windows.c.h>
#include <structures.h>

/*****************************************************************************
*                                                                            *
* External variables:                                                        *
* W         (struct Window *)              The Window                        *
* stat      int                            initial state: ON or OFF (1 or 0) *
* r, g, b   int                            color of indicator box            *
* thick     int                            thicknes of indicator box         *
*****************************************************************************/

IndicatorWin(W, stat, r, g, b, thick)
struct Window *W;
int stat, r, g, b, thick;
{

/*****************************************************************************
*                                                                            *
* Internal variables:                                                        *
* DoIndicator() (int)                      The DO/DRAW functions             *
* params    (struct IndicatorStruct *)     The parameters to pass to DO/DRAW *
*                                                                            *
*****************************************************************************/

  int DoIndicator();
  struct IndicatorStruct *params;

/* Load the parameter structure */

  params = (struct IndicatorStruct *) malloc(sizeof(struct IndicatorStruct));
  params->stat = stat;
  params->r = r;
  params->g = g;
  params->b = b;
  params->thick = thick;

/* Drag in appropriate commands */

  AttachCommand(W,DRAW,DoIndicator,(char *)params);
  AttachCommand(W,TOGGLE,DoIndicator,(char *)params);
  AttachCommand(W,TURN_ON,DoIndicator,(char *)params);
  AttachCommand(W,TURN_OFF,DoIndicator,(char *)params);
}


/*************************************************
* This takes the standard do-function arguements *
*************************************************/

DoIndicator(W,id,data,stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{

/****************************************************************************
*                                                                           *
* Internal variables:                                                       *
* The standard button, cx1, cy1, cx2, cy2, cstruct, pick                    *
* fildes (int)    The ever-present file descriptor                          *
*                                                                           *
****************************************************************************/

  int button;
  struct pickstruct *pick;
  struct clipstruct *cstruct;
  int cx1,cx2,cy1,cy2;
  int fildes;
  int stat, r, g, b, thick;
  struct IndicatorStruct *params;
  int bd;
  float red, green, blue;

  params = (struct IndicatorStruct *)stuff;   /* unpacking the windows stuff */
  stat = params->stat;
  fildes = (W->display)->fildes;

  switch (id) {
  case (DRAW):
    if (params->stat) {
      r = params->r;
      g = params->g;
      b = params->b;
      thick = params->thick;
      
      cstruct = (struct clipstruct *)data;
      cx1 = cstruct->x1;  cy1 = cstruct->y1;
      cx2 = cstruct->x2;  cy2 = cstruct->y2;
      clip_rectangle(fildes, 0.0, 2047.0, 0.0, 1023.0);
      
      red = ((float)r)/255.0;
      green = ((float)g)/255.0;
      blue = ((float)b)/255.0;
      perimeter_color(fildes, red, green, blue);
      line_color(fildes, red, green, blue);
      
      interior_style(fildes, INT_HOLLOW, TRUE);
      for (bd = 1; bd < abs(thick); bd++)
	rectangle(fildes, (float)(W->x1 + bd), (float)(W->y1 + bd), (float)(W->x2 - bd), (float)(W->y2 - bd));
      
      clip_rectangle(fildes, 0.0, 2047.0, 0.0, 1023.0);
      make_picture_current(fildes);
    }
    break;
  case (DO):
    pick = (struct pickstruct *)data;
    button = pick->button;

    switch (button) {
    case (JUSTDOWN):  
      break;
    case (BEENUP): 
      break;
    case (JUSTUP): 
      break;
    case (BEENDOWN):
      break;
    }
    break;
  case (TOGGLE):
/******************* --Tim, 3/27/91, so that the resulting turn-on/off message can be used by my window ********/
    /******* it shouldn't effect much else... see my knobs code to see why this is useful ***************/
#define TIMVERSION 1
#if TIMVERSION

    if (stat == ON)
      SendMessage(W, TURN_OFF, data);
    else
      SendMessage(W, TURN_ON, data);
#else
    if (stat == ON)
      params->stat = OFF; 
    else
      params->stat = ON;
#endif
    UpdateWin(W);
    break;
  case (TURN_ON):
    if (stat == OFF) {
      params->stat = ON;
      UpdateWin(W);
    }
    break;
  case (TURN_OFF):
    if (stat == ON) {
      params->stat = OFF;
      UpdateWin(W);
    }
    break;
  default:
    printf("Unknown id: %d\n", id);
    break;
  }
  
  return(0);
}
/**********************************************************************

  int ReadIndicator(W)

            W      Window being read.


	    Given a window with an idicator attached to it, the
	    function will return the indicator's status
	    or a -1 if the window is not an indicator

	    Tim Kukulski - July 18, 1990

**********************************************************************/
  
int ReadIndicator(W)
     struct Window *W;
{
  struct IndicatorStruct *I;
  if(I = (struct IndicatorStruct *)GetStuff(W,TOGGLE))
    {
      if (I->stat == ON)
	return (TRUE);
      else if (I->stat == OFF) return (FALSE);
    }
  else return (-1);
}




