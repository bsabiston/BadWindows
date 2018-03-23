#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <varargs.h>		/* included for PanelLine() */


struct Window *MakePanel(Root, echo, font, size, bits, fred, fgreen, fblue, t, red, green, blue,sred,sgreen,sblue)
     struct Window *Root;
     struct curstruct *echo;
     char *font;
     int size, bits, red, green, blue, t, fred, fgreen, fblue,sred,sgreen,sblue;
{
  struct Window *menu;
  int DoPanel();
  struct panel_struct *pstruct;

  set_font(font, size, bits);
  pstruct = (struct panel_struct *)malloc(sizeof(struct panel_struct));
  pstruct->line_height = size;   /* I'm assuming the size is a good line_height */
  pstruct->parms.string = NULL;
  pstruct->parms.font   = font;
  pstruct->parms.size   = size;
  pstruct->parms.bits   = bits;
  pstruct->parms.red    = fred;
  pstruct->parms.green  = fgreen;
  pstruct->parms.blue   = fblue;
  pstruct->parms.t      = t;
  pstruct->echo = echo;
  pstruct->red = red;
  pstruct->green = green;
  pstruct->blue = blue;
  pstruct->sred = sred;
  pstruct->sgreen = sgreen;
  pstruct->sblue = sblue;
  pstruct->label_width = 0;

  menu = (struct Window *)MakeWindow(Root->display, Root->input, Root, 0, 0, 30, 4, "menu");
  Rectify(menu, red, green, blue, 1, fred, fgreen, fblue, 2);
  EchoWrap(menu, echo, 0, 0, 0); 
  AttachCommand(menu,ATTRIBUTES,DoPanel,pstruct);
  /* doesn't do anything because all functions are controlled by children */
  return(menu);
}

DoPanel(W,id,data,stuff)
struct Window *W;
int id;
char *data, *stuff;
{ 
}




/* Adds a line to a panel */
/* this function can take a variable number of arguments depending on the value of the 'type' arg 
   numfields = number of data fields for the line;
   type = the type of field, FLOAT, INT, CHAR or CHAR1
   action = type of selection, PSELECT or PEDIT
            PSELECT lets you choose one field from the list, and returns the choice number in the supplied return variable.
	    PEDIT lets you edit the fields individually
    
   va_alist = all the field arguments.  for an EDIT action, this is all the addresses of the field variables.
                                    for a SELECT action, this is the field variables followed by an integer pointer return val.

examples: 
type REG: AddPanelLine(W,"Enter Rotation (0.0-1.0)",1,FLOAT,PEDIT,&rotation);
type ARG: AddPanelLine(W,"Choose Axis:",3,CHAR,PSELECT,"x","y","z",&return);

*/

struct Window *AddPanelLine(W, label, numfields,type,action,va_alist)
     struct Window *W;
     char *label;
     int numfields,type,action;
     va_dcl
{
  va_list ap;
  struct Window *Line;
  struct Command *C;
  struct curstruct *echo;
  struct stringstruct *parms;
  struct wrapstruct *wparms; 
  struct panel_struct *p;
  struct panel_line *pline;
  int Panel_Line_Commands();
  int argno = 0, *iarg;
  float *farg;
  char *carg;

  /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
  p = (struct panel_struct *)GetStuff(W,ATTRIBUTES);
  parms = &p->parms;
  echo = p->echo;
  
  /* attach all the argument shit */
  if (numfields > 10) { 
    printf("ERROR: AddPanelLine() -- To many fields (%d).\n",numfields);
    return (0);
  }

  pline = (struct panel_line *)malloc(sizeof(struct panel_line));
  pline->numfields = numfields;
  pline->fieldtype = type;
  pline->action = action;
  pline->label = label;
  set_font(parms->font,parms->size,parms->bits);
  p->label_width = MAX(p->label_width,string_width(label)+10);
  va_start( ap);
  switch (type) {
  case (FLOAT):
    pline->floats = (float **)malloc(numfields*sizeof(float *));
    while( argno < numfields) {
      farg = va_arg( ap, float *);
      *(pline->floats+argno) = farg;
      argno += 1;
    }
    break;
  case (INT):
    pline->integers = (int **)malloc(numfields*sizeof(int *));
    while( argno < numfields) {
      iarg = va_arg( ap, int *);
      *(pline->integers+argno) = iarg;
      argno += 1;
    }
    break;
  case (CHAR):
  case (CHAR1):
    pline->strings = (char **)malloc(numfields*sizeof(char *));
    while( argno < numfields) {
      carg = va_arg( ap, char *);
      *(pline->strings+argno) = carg;
      argno += 1;
    }
    break;
  }

  if (action == PSELECT) pline->choice = (int *)va_arg( ap, int *);
  va_end( ap);

  Line = (struct Window *)MakeWindow(W->display, W->input, W, 0, 0, 100, 100, label); /* ignore size */
  AttachCommand(Line,DO,Panel_Line_Commands,pline);
  AttachCommand(Line,DRAW,Panel_Line_Commands,pline);
  AttachCommand(Line,GET_PANEL_LINE_WIDTH,Panel_Line_Commands,pline);
  EchoWrap(Line,echo,1,0,1);
  Maker(Line, 1, W->height-3, -3, W->height+16); /* these values will change in AttachPopUpLine */

  AttachPanelLine(Line);
  return(Line);
}


Panel_Line_Commands(W,id,data,stuff)
struct Window *W;
int id;
char *data, *stuff;
{
  struct panel_line *pline;
  struct panel_struct *pstruct;
  struct stringstruct *parms;
  struct clipstruct *cstruct;
  char string[200];
  int t, hedge,wide,done = 0,screen,cval, r = 0;

  pline = (struct panel_line *)stuff;
  pstruct = (struct panel_struct *)GetStuff(W->parent,ATTRIBUTES);
  parms = &pstruct->parms;
  screen = W->display->fildes;

  switch (id) {
  case (GET_PANEL_LINE_WIDTH):
    {    
      set_font(parms->font,parms->size,parms->bits);
      hedge = pstruct->label_width+10;
      for (t = 0; (t < pline->numfields)&&(!done); t++)
	{
	  if (pline->fieldtype == CHAR) strcpy(string,*(pline->strings+t));
	  else if (pline->fieldtype == CHAR1) sprintf(string,"%c",*(pline->strings+t));
	  else if (pline->fieldtype == INT) sprintf(string,"%d",*(*(pline->integers+t)));
	  else if (pline->fieldtype == FLOAT) sprintf(string,"%5.3f",*(*(pline->floats+t)));
	  wide = string_width(string)+10;
	  hedge+= wide;
	}
      return(hedge);
    }
    break;

  case (DO):
    {    
      struct pickstruct *pick;
      pick = (struct pickstruct *)data;
      
      set_font(parms->font,parms->size,parms->bits);
      hedge = W->x1+pstruct->label_width+10;
      for (t = 0; (t < pline->numfields)&&(!done); t++)
	{
	  if (pline->fieldtype == CHAR) strcpy(string,*(pline->strings+t));
	  else if (pline->fieldtype == CHAR1) strcpy(string,"%c",*(pline->strings+t));
	  else if (pline->fieldtype == INT) sprintf(string,"%d",*(*(pline->integers+t)));
	  else if (pline->fieldtype == FLOAT) sprintf(string,"%5.3f",*(*(pline->floats+t)));

	  wide = string_width(string)+10;
	  if ((pline->fieldtype == CHAR)&&(pline->action == PEDIT)) wide = MAX(wide,50);

	  if ((hedge <= pick->x)&&(pick->x <= hedge+wide-1)) {
	    /* GOT A PICK */
	    done = 1;

	    if (pline->action == PSELECT)
	      {
		if (t != *(pline->choice)) {
		  *(pline->choice) = t;
		  BufUpdateWin(W);
		}
	      }
	    else {
	      if (pline->fieldtype == CHAR) {
		cval = 75;
		r = GetString2(Root1,pick->x,pick->y,"Enter new value, PLEEZE",string,cval);
	      }
	      else {
		cval = 20;
		r = GetString(Root1,pick->x,pick->y,"Enter new value, PLEEZE",string,cval);
	      }

	      if (r)
		{
		  if (pline->fieldtype == INT) sscanf(string,"%d",*(pline->integers+t));
		  else if (pline->fieldtype == FLOAT) sscanf(string,"%f",*(pline->floats+t));
		  else if (pline->fieldtype == CHAR) strcpy(*(pline->strings+t),string);
		  else if (pline->fieldtype == CHAR1) sscanf(string,"%c",*(pline->strings+t));
		  done = 1;
		}
	    BufUpdateWin(W);
	    }
	  }
	  hedge += wide;
	}
      
    }
    break;

  case (DRAW):
    cstruct = (struct clipstruct *)data;
    clip_rectangle(screen,(float)cstruct->x1,(float)cstruct->x2,
		   (float)cstruct->y1,(float)cstruct->y2);
	      fill_color(screen,FCON(pstruct->red),FCON(pstruct->green),FCON(pstruct->blue));
	      interior_style(screen,INT_SOLID,FALSE);
	      rectangle(screen,(float)W->x1,(float)W->y1,(float)W->x2,(float)W->y2);
              make_picture_current(screen);

	      set_font(parms->font,parms->size,parms->bits);
	      set_monitor(W->display->bits,screen); 
	      set_font_color(parms->red,parms->green,parms->blue,parms->t);
              set_text_clip_rectangle(cstruct->x1,cstruct->y1,cstruct->x2,cstruct->y2);

    display_string(pline->label,W->x1+5,W->y1);
    display_string(":",W->x1+pstruct->label_width,W->y1);
    
    hedge = W->x1+pstruct->label_width+10;
    for (t = 0; t < pline->numfields; t++)
      {
	if (pline->fieldtype == CHAR) strcpy(string,*(pline->strings+t));
	else if (pline->fieldtype == CHAR1) sprintf(string,"%c",*(*(pline->strings+t)));
	else if (pline->fieldtype == INT) sprintf(string,"%d",*(*(pline->integers+t)));
	else if (pline->fieldtype == FLOAT) sprintf(string,"%5.3f",*(*(pline->floats+t)));

	  display_string(string,hedge,W->y1);
	  if ((pline->action == PSELECT)&&(*(pline->choice) == t)) {
	    set_font_color(pstruct->sred,pstruct->sgreen,pstruct->sblue,parms->t);	    
	    display_string(string,hedge-1,W->y1-1);
	    set_font_color(parms->red,parms->green,parms->blue,parms->t);	    
	  }
	  hedge += string_width(string)+10;
      }

    clip_rectangle(screen,(float)0.0,(float)W->display->width,
		   (float)0.0,(float)W->display->height);
    break;
  }
  return (0);
}




/* construct a panel header and attach it */

struct Window *AddPanelHeader(menu, string,thick)
     struct Window *menu;
     char *string;
     int thick;
{
  struct Command *C;
 struct Window *line;
 struct curstruct *echo;
 struct stringstruct *parms;
  struct stringstruct *sparms;
 struct rstringstruct *rparms;
 struct wrapstruct *wparms; 
 struct makestruct *mstruct;
 struct panel_struct *p;
  int wide;

 /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
 p = (struct panel_struct *)GetStuff(menu,ATTRIBUTES);
 parms = &p->parms;
 echo = p->echo;

 line = (struct Window *)MakeWindow(menu->display, menu->input, menu, 0, 0, 100, 100, string); /* ignore size */
 MoverII(line,menu,0);
 EchoWrap(line, echo, JUSTDOWN, 0, 0);
 RStringWin(line, string, 5, 0, parms);
 HLiner(line,15,thick,0,0,0);
 Maker(line, 1, menu->height-3, -3, menu->height+16); /* these values will change in AttachPopUpLine */
 menu = line->parent;

 /* find proper window width by getting the window's string width */
  C = (struct Command *) GetCommand(line, DRAW);
 rparms = (struct rstringstruct *) *(C->arguments);
 sparms = rparms->parms;
 set_font(sparms->font, sparms->size, sparms->bits);
 wide = MAX(string_width(rparms->string)+24, menu->width);

  /* find makestruct so that position can be altered */
  C = (struct Command *) GetCommand(line, MAKE);
  mstruct = (struct makestruct *) *(C->arguments);
  mstruct->y1 = menu->height-3;
  mstruct->y2 = menu->height+16;

  menu->height += 20;
  menu->width = wide;

  InstallWin(line);
  TransformCoords(menu, menu->relx, menu->rely, menu->width, menu->height);
}




/* This function takes a panel line, which is not installed, and adds it to the end of a menu */

AttachPanelLine(line)     /* v 1.0b */
     struct Window *line;
{
  struct Command *C;
  struct panel_struct *p;
  struct stringstruct *sparms;
  struct makestruct *mstruct;
  struct Window *menu;
  int wide;

  menu = line->parent;

  /* find proper window width by getting the window's string width */
  p = (struct panel_struct *) GetStuff(line->parent, ATTRIBUTES);
  sparms = &p->parms;
  wide = SendMessage(line,GET_PANEL_LINE_WIDTH,NULL);
  wide = MAX(wide, menu->width);

  /* find makestruct so that position can be altered */
  C = (struct Command *) GetCommand(line, MAKE);
  mstruct = (struct makestruct *) *(C->arguments);
  mstruct->y1 = menu->height-3;
  mstruct->y2 = menu->height+16;

  menu->height += 20;
  menu->width = wide;
  InstallWin(line);
  TransformCoords(menu, menu->relx, menu->rely, menu->width, menu->height);
}



/* This function removes an installed panel line and adjusts the menu size
   NOTE: lines must be removed in the order that they were installed       */

RemovePanelLine(line)
     struct Window *line;
{
  struct Window *menu;
  menu = line->parent;
  menu->height -= 20;
  UnstallWin(line);
}



/* construct a panel trailer and attach it */

struct Window *AddPanelTrailer(menu, okstring, abortstring)
     struct Window *menu;
     char *okstring, *abortstring;
{
 struct Window *line;
 struct curstruct *echo;
 struct stringstruct *parms;
 struct stringstruct *sparms;
 struct rstringstruct *rparms;
 struct wrapstruct *wparms; 
 struct makestruct *mstruct;
 struct panel_struct *p;
 struct Command *C;
 char **strings;
 int wide, Panel_Trailer_Commands();

 /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
 p = (struct panel_struct *)GetStuff(menu,ATTRIBUTES);
 parms = &p->parms;
 echo = p->echo;

 strings = (char **)malloc(2*sizeof(char *));
 *(strings) = okstring;
 *(strings+1) = abortstring;

 line = (struct Window *)MakeWindow(menu->display, menu->input, menu, 0, 0, 100, 100, "trailer"); /* ignore size */
 AttachCommand(line,DO,Panel_Trailer_Commands,strings);
 AttachCommand(line,DRAW,Panel_Trailer_Commands,strings);
 AttachCommand(line,GET_PANEL_LINE_WIDTH,Panel_Trailer_Commands,strings);
 EchoWrap(line, echo, JUSTDOWN, 0, 0);
 Maker(line, 1, menu->height-3, -3, menu->height+16); /* these values will change in AttachPopUpLine */
 menu = line->parent;

 /* find proper window width by getting the window's string width */
 wide = SendMessage(line,GET_PANEL_LINE_WIDTH,NULL);
 wide = MAX(wide, menu->width);

  /* find makestruct so that position can be altered */
  C = (struct Command *) GetCommand(line, MAKE);
  mstruct = (struct makestruct *) *(C->arguments);
  mstruct->y1 = menu->height-3;
  mstruct->y2 = menu->height+16;

  menu->height += 20;
  menu->width = wide;

  InstallWin(line);
  TransformCoords(menu, menu->relx, menu->rely, menu->width, menu->height);
}




Panel_Trailer_Commands(W,id,data,stuff)
struct Window *W;
int id;
char *data, *stuff;
{
  struct panel_struct *pstruct;
  struct stringstruct *parms;
  struct clipstruct *cstruct;
  char **strings;
  int t, hedge,wide,done = 0,x,screen;

  screen = W->display->fildes;
  strings = (char **)stuff;
  pstruct = (struct panel_struct *)GetStuff(W->parent,ATTRIBUTES);
  parms = &pstruct->parms;
  switch (id) {
  case (GET_PANEL_LINE_WIDTH):
    {    
      set_font(parms->font,parms->size,parms->bits);
      x = 5 + string_width(*strings)+20;
      x += 5 + string_width(*(strings+1))+20;
      return(x);
    }
    break;

  case (DO):
    {    
      struct pickstruct *pick;
      pick = (struct pickstruct *)data;
      
      set_font(parms->font,parms->size,parms->bits);

      x = W->x1+5 + string_width(*strings)+5;
      if ((x < pick->x)&&(pick->x <x+10)) {
	/* OK */
	CloseWindow(W->parent);
	query_return = (char *)1;
	return(0);
      }
      
      x = W->x2-20;
      if ((x < pick->x)&&(pick->x <x+10)) {
	/* CANCEL */
	CloseWindow(W->parent);
	query_return = (char *)0;
	return(0);
      }
    }
    break;

  case (DRAW):
    cstruct = (struct clipstruct *)data;
    clip_rectangle(screen,(float)cstruct->x1,(float)cstruct->x2,
		   (float)cstruct->y1,(float)cstruct->y2);

	      fill_color(screen,FCON(pstruct->red),FCON(pstruct->green),FCON(pstruct->blue));
	      line_color(screen,FCON(pstruct->parms.red),FCON(pstruct->parms.green),FCON(pstruct->parms.blue));
	      perimeter_color(screen,FCON(pstruct->parms.red),FCON(pstruct->parms.green),FCON(pstruct->parms.blue));
	      interior_style(screen,INT_SOLID,FALSE);
	      rectangle(screen,(float)W->x1,(float)W->y1,(float)W->x2,(float)W->y2);
              move2d(screen,(float)W->x1,(float)W->y1);
              draw2d(screen,(float)W->x2,(float)W->y1);
              make_picture_current(screen);
	      set_font(parms->font,parms->size,parms->bits);
	      set_monitor(W->display->bits,screen); 
	      set_font_color(parms->red,parms->green,parms->blue,parms->t);
              set_text_clip_rectangle(cstruct->x1,cstruct->y1,cstruct->x2,cstruct->y2);

    x = W->x1+5;
    display_string(*strings,x,W->y1+1);
    x += string_width(*strings)+5;
    interior_style(screen,INT_SOLID,TRUE);
    rectangle(screen,(float)x,(float)(W->y1+4),(float)x+10,(float)(W->y1+14));
    make_picture_current(screen);

    x = W->x2-string_width(*(strings+1))-25;
    display_string(*(strings+1),x,W->y1+1);
    x += string_width(*(strings+1))+5;
    interior_style(screen,INT_SOLID,TRUE);
    rectangle(screen,(float)x,(float)(W->y1+4),(float)x+10,(float)(W->y1+14));

    clip_rectangle(screen,(float)0.0,(float)W->display->width,
		   (float)0.0,(float)W->display->height);
    break;
  }
  return (0);
}




/* construct a panel trailer with a middle function button and attach it */

struct Window *AddPanelTripleTrailer(menu, okstring, middlestring, abortstring, middlefunction, middlearg)
     struct Window *menu;
     char *okstring, *abortstring, *middlestring, *middlearg;
     int (*middlefunction)();
{
 struct Window *line;
 struct curstruct *echo;
 struct stringstruct *parms;
 struct stringstruct *sparms;
 struct rstringstruct *rparms;
 struct wrapstruct *wparms; 
 struct makestruct *mstruct;
 struct panel_struct *p;
 struct Command *C;
 char **strings;
 int wide, Panel_TripleTrailer_Commands();

 /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
 p = (struct panel_struct *)GetStuff(menu,ATTRIBUTES);
 parms = &p->parms;
 echo = p->echo;

 strings = (char **)malloc(5*sizeof(char *));
 *(strings) = okstring;
 *(strings+1) = middlestring;
 *(strings+2) = abortstring;
 *(strings+3) = (char *)middlefunction;
 *(strings+4) = middlearg;

 line = (struct Window *)MakeWindow(menu->display, menu->input, menu, 0, 0, 100, 100, "trailer"); /* ignore size */
 AttachCommand(line,DO,Panel_TripleTrailer_Commands,strings);
 AttachCommand(line,DRAW,Panel_TripleTrailer_Commands,strings);
 AttachCommand(line,GET_PANEL_LINE_WIDTH,Panel_TripleTrailer_Commands,strings);
 EchoWrap(line, echo, JUSTDOWN, 0, 0);
 Maker(line, 1, menu->height-3, -3, menu->height+16); /* these values will change in AttachPopUpLine */
 menu = line->parent;

 /* find proper window width by getting the window's string width */
 wide = SendMessage(line,GET_PANEL_LINE_WIDTH,NULL);
 wide = MAX(wide, menu->width);

  /* find makestruct so that position can be altered */
  C = (struct Command *) GetCommand(line, MAKE);
  mstruct = (struct makestruct *) *(C->arguments);
  mstruct->y1 = menu->height-3;
  mstruct->y2 = menu->height+16;

  menu->height += 20;
  menu->width = wide;

  InstallWin(line);
  TransformCoords(menu, menu->relx, menu->rely, menu->width, menu->height);
}




Panel_TripleTrailer_Commands(W,id,data,stuff)
struct Window *W;
int id;
char *data, *stuff;
{
  struct panel_struct *pstruct;
  struct stringstruct *parms;
  struct clipstruct *cstruct;
  char **strings;
  int t, hedge,wide,done = 0,x,screen, (*func)();

  screen = W->display->fildes;
  strings = (char **)stuff;
  pstruct = (struct panel_struct *)GetStuff(W->parent,ATTRIBUTES);
  parms = &pstruct->parms;
  switch (id) {
  case (GET_PANEL_LINE_WIDTH):
    {    
      set_font(parms->font,parms->size,parms->bits);
      x = 5 + string_width(*strings)+20;
      x += 5 + string_width(*(strings+1))+20;
      x += 5 + string_width(*(strings+2))+20+10;
      return(x);
    }
    break;

  case (DO):
    {    
      struct pickstruct *pick;
      pick = (struct pickstruct *)data;
      
      set_font(parms->font,parms->size,parms->bits);

      x = W->x1+5 + string_width(*strings)+5;
      if ((x < pick->x)&&(pick->x <x+10)) {
	/* OK */
	CloseWindow(W->parent);
	query_return = (char *)1;
	return(0);
      }

      x += 20 + string_width(*(strings+1))+5;
      if ((x < pick->x)&&(pick->x <x+10)) {
	/* OK with function */
	func = *(strings+3); /* HA HA HO he HA he ha ha */
	(*func)(*(strings+4));
	CloseWindow(W->parent);
	query_return = (char *)1;
	return(0);
      }
      
      x = W->x2-20;
      if ((x < pick->x)&&(pick->x <x+10)) {
	/* CANCEL */
	CloseWindow(W->parent);
	query_return = (char *)0;
	return(0);
      }
    }
    break;

  case (DRAW):
    cstruct = (struct clipstruct *)data;
    clip_rectangle(screen,(float)cstruct->x1,(float)cstruct->x2,
		   (float)cstruct->y1,(float)cstruct->y2);

	      fill_color(screen,FCON(pstruct->red),FCON(pstruct->green),FCON(pstruct->blue));
	      line_color(screen,FCON(pstruct->parms.red),FCON(pstruct->parms.green),FCON(pstruct->parms.blue));
	      perimeter_color(screen,FCON(pstruct->parms.red),FCON(pstruct->parms.green),FCON(pstruct->parms.blue));
	      interior_style(screen,INT_SOLID,FALSE);
	      rectangle(screen,(float)W->x1,(float)W->y1,(float)W->x2,(float)W->y2);
              move2d(screen,(float)W->x1,(float)W->y1);
              draw2d(screen,(float)W->x2,(float)W->y1);
              make_picture_current(screen);
	      set_font(parms->font,parms->size,parms->bits);
	      set_monitor(W->display->bits,screen); 
	      set_font_color(parms->red,parms->green,parms->blue,parms->t);
              set_text_clip_rectangle(cstruct->x1,cstruct->y1,cstruct->x2,cstruct->y2);

    x = W->x1+5;
    display_string(*strings,x,W->y1+1);
    x += string_width(*strings)+5;
    interior_style(screen,INT_SOLID,TRUE);
    rectangle(screen,(float)x,(float)(W->y1+4),(float)x+10,(float)(W->y1+14));
    make_picture_current(screen);

    x += 20;
    display_string(*(strings+1),x,W->y1+1);
    x += string_width(*(strings+1))+5;
    interior_style(screen,INT_SOLID,TRUE);
    rectangle(screen,(float)x,(float)(W->y1+4),(float)x+10,(float)(W->y1+14));
    make_picture_current(screen);

    x = W->x2-string_width(*(strings+2))-25;
    display_string(*(strings+2),x,W->y1+1);
    x += string_width(*(strings+2))+5;
    interior_style(screen,INT_SOLID,TRUE);
    rectangle(screen,(float)x,(float)(W->y1+4),(float)x+10,(float)(W->y1+14));

    clip_rectangle(screen,(float)0.0,(float)W->display->width,
		   (float)0.0,(float)W->display->height);
    break;
  }
  return (0);
}





SetPanelWidth(W)
struct Window *W;
{
  int t = 0;
  struct Window *kid;
  struct List *L, *Current;
  L = W->port;
  for (Current = L->Front; Current != L; Current = Current->Front)
    {
      t = MAX(SendMessage(Current->id,GET_PANEL_LINE_WIDTH,NULL),t);
    }
  W->width = MAX(100,30+t);
}
