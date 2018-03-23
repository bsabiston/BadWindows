#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

int PopUpCallFunction = 1;	/* *DKY-11Mar91* */
int PopUpHighlightLine = 1;	/* *DKY-12Mar91* -- global to determine newly created pop-up lines are highlighted */

/* POP-UP window routines

   These routines allow you to construct a pop-up menu of choices.
   Each line in the menu has an associated function and argument.
   The window is activated by a call to query, which will poll that window until
   you choose something or move out of the active region.

   These pop-ups assume that they are only active when the pen is down, and when you
   are in the active region. The active region includes the menu itself, any or all of
   the areas to each side of the window, and a predefined 'control' rectangle. You specify
   active sides of the menu with an integer mask. The lower 4 bits each correspond to a side
   of the menu. For example, if you set mask=14 (bits 2, 3 &4 set) then the window will stay
   active until you let up the mouse button, or until you move above the window in y.

              BIT 1
       B   ----------   B
       I   |        |   I          setting a bit in the mask means that the pop-up
       T   |  menu  |   T          will stay open on its corresponding side when the
           |        |              locator is in that region.
       3   ----------   4
              BIT 2

     The control rectangle is an additional area that defines the active region.
     In this area the cursor is also 'safe'--i.e, it won't close the menu.

     To make a pop-up, call MakePopUp with the mask you want. The window will be malloced
     with no default control rectangle. Later you can change the pop-up's parameters with

             ChangePopUpAttributes(PopUp, x1, y1, x2, y2);

     There are two main ways of using these windows.  For the typical-mac menu-bar, you have
     a window that triggers a pop-up when it gets pressed. To construct one of these, do
     the following :
             1) use MakeWindow to malloc the window structure.
             2) call MakePopUpTrigger to assign the correct dofunctions to the window.
                  it takes a pop-up as an argument.
             3) attach any Draw function you want the window to have.

     The other way is to open the thing yourself.
             1) assuming you have already made the pop-up, you add all the lines you want (see below).
             2) use TransformCoords(popup, x1, y1, width, height) to set the pop-up's area on the screen.
	     3) call Query(PopUp);


     Pop up lines are windows that can be added to and removed from the menu.
     If you want to add lines to a menu, and do not plan on removing them later, you can
     use AddPopUpLine (or AddCascadingPopUpLine) to permanently install the line in the menu. If you plan to remove
     the things later, you should use MakePopUpLine to get the Line window's address. When
     you want to use the line later, call AttachPopUpLine and then Remove PopUpLine when
     the window has closed.

     Call ChangePopUpLineAttributes to change the parameters of a pop-up line.

*/


struct Window *MakePopUp(Root, echo, mask, font, size, bits, fred, fgreen, fblue, t, red, green, blue)
     struct Window *Root;
     struct curstruct *echo;
     char *font;
     int size, bits, red, green, blue, t, mask, fred, fgreen, fblue;
{
  struct Window *menu;
  int DoPopUp();
  struct popup_struct *pstruct;

  set_font(font, size, bits);
  pstruct = (struct popup_struct *)malloc(sizeof(struct popup_struct));
  pstruct->mask = mask;
  pstruct->x1 = pstruct->y1 = pstruct->x2 = pstruct->y2 = -1; /* no rect */
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

  menu = (struct Window *)MakeWindow(Root->display, Root->input, Root, 0, 0, 30, 4, "menu");
  AttachCommand(menu, DO, DoPopUp, pstruct);
  AttachCommand(menu, ATTRIBUTES, DoPopUp, pstruct);
  Rectify(menu, red, green, blue, 1, fred, fgreen, fblue, 2);
/*  EchoWrap(menu, echo, 2, 0, 0);  was 15 */

  return(menu);
}



MakePopUpTrigger(W, echo, menu, x, y)     /* v 1.0b */
     struct Window *W, *menu;
     struct curstruct *echo;
     int x, y;
{
  int TriggerPopUp();
  struct pop_trigger *pt;

  pt = (struct pop_trigger *)malloc(sizeof(struct pop_trigger));
  pt->menu = menu;
  pt->x = x;
  pt->y = y;
  pt->callFunction = PopUpCallFunction;

  AttachCommand(W, DO, TriggerPopUp, pt);
  EchoWrap(W, echo, 5, 0, 1);
}



TriggerPopUp(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct pickstruct *pick;
  struct pop_trigger *pt;
  struct Window *menu, *triggerroot;
  int x1, y1, x2, y2;
  struct funcstruct *fs;
  struct trapstruct t;

  pt = (struct pop_trigger *)stuff;
  menu = pt->menu;
  pick = (struct pickstruct *)data;
  if ((pick->button == BEENDOWN)||(pick->button == JUSTDOWN))
    {
      menu->display = W->display;
      /* Make sure the menu is on the correct screen --> LHR 1/3/90  */
      triggerroot = menu;
      while(triggerroot->parent) triggerroot = triggerroot->parent;
      menu->parent = triggerroot;
      ChangeDisplay(menu);
      TransformCoords(menu, W->x1+pt->x, W->y2+pt->y, menu->width, menu->height);
      x1 = MIN(W->x1, W->x1+pt->x);
      x2 = MAX(W->x2, W->x1+pt->x);
      y1 = MIN(W->y1, W->y2+pt->y);
      y2 = MAX(W->y2, W->y2+pt->y);
      ChangePopUpAttributes(menu, x1, y1, x2, y2);

      EorSolidBox(W->display->fildes, W->x1, W->y1, W->x2, W->y2);
      fs = (struct funcstruct *)Query(menu);
      EorSolidBox(W->display->fildes, W->x1, W->y1, W->x2, W->y2);

      if( pt->callFunction)	/* *DKY-11Mar91* */
	if( (fs) && (fs->function))
	  {
	    (*fs->function)(fs->arg);

	    /* Block out the remaining JUSTUP message */
	    t.window = W;
	    t.until = BEENUP;
	    Dispatch(W,TRAP,&t,NULL);
	  }
    }
  return(0);
}



/* The following two functions MakePopUpTriggerNoEor() and
 * TriggerPopUpNoEor() are based on the functions MakePopUpTrigger() and
 * TriggerPopUp() above.  The difference is that when the pop-up menu appears it
 * does not eor the window it's attached to.
 * *DKY- 9Jan90*
 */

MakePopUpTriggerNoEor(W, echo, menu, x, y)     /* v 1.0b --- *DKY- 9Jan90**/
     struct Window *W, *menu;
     struct curstruct *echo;
     int x, y;
{
  int TriggerPopUpNoEor();
  struct pop_trigger *pt;

  pt = (struct pop_trigger *)malloc(sizeof(struct pop_trigger));
  pt->menu = menu;
  pt->x = x;
  pt->y = y;
  pt->callFunction = PopUpCallFunction;

  AttachCommand(W, DO, TriggerPopUpNoEor, pt);
}



TriggerPopUpNoEor(W, id, data, stuff)     /* v 1.0b --- *DKY- 9Jan90**/
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct pickstruct *pick;
  struct pop_trigger *pt;
  struct Window *menu, *triggerroot;
  int x1, y1, x2, y2;
  unsigned char stupid[4];
  struct trapstruct t;
  struct funcstruct *fs;

  pt = (struct pop_trigger *)stuff;
  menu = pt->menu;
  pick = (struct pickstruct *)data;
  if ((pick->button == BEENDOWN)||(pick->button == JUSTDOWN))
    {
      menu->display = W->display;
      /* Make sure the menu is on the correct screen --> LHR 1/3/90  */
      triggerroot = menu;
      while( triggerroot->parent) triggerroot = triggerroot->parent;
      menu->parent = triggerroot;
      ChangeDisplay(menu);
      TransformCoords(menu, W->x1+pt->x, W->y2+pt->y, menu->width, menu->height);
      x1 = MIN(W->x1, W->x1+pt->x);
      x2 = MAX(W->x2, W->x1+pt->x);
      y1 = MIN(W->y1, W->y2+pt->y);
      y2 = MAX(W->y2, W->y2+pt->y);
      ChangePopUpAttributes(menu, x1, y1, x2, y2);

      /* EorSolidBox(W->display->fildes, W->x1, W->y1, W->x2, W->y2); */
      fs = (struct funcstruct *)Query(menu);
/*      PopFix(W,DRAW,NULL,NULL); */

      if( pt->callFunction)	/* *DKY-11Mar91* */
	if( (fs) && (fs->function))
	  {
	    (*fs->function)(fs->arg);

	    /* Block out the remaining JUSTUP message */
	    t.window = W;
	    t.until = BEENUP;
	    Dispatch(W,TRAP,&t,NULL);
	  }
    }

  return(0);
}


PopFix(W,id,data,stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  unsigned char stupid[4];

      clip_rectangle(W->display->fildes,0.0,(float)W->display->width,0.0,(float)W->display->height);
      dcblock_read(W->display->fildes,E_lastx,E_lasty,2,2,stupid,FALSE); /* STUPID STUPID STUPID fix to starbase bug */
      fill_color(W->display->fildes,0.0,0.0,0.0);
      interior_style(W->display->fildes,INT_SOLID,FALSE);
      rectangle(W->display->fildes,0.0,0.0,1.0,1.0);
      dcblock_write(W->display->fildes,E_lastx,E_lasty,2,2,stupid,FALSE); /* STUPID STUPID STUPID fix to starbase bug */
      make_picture_current(W->display->fildes);
  return(0);
}



/* Adds a line to a pop-up window  -- also see AddCascadingPopUpLine*/

struct Window *AddPopUpLine(W, string, function, argument)     /* v 1.0b */
     struct Window *W;
     char *string;
     int (*function)();
     char *argument;
{
  struct Window *Line;
  struct Window *MakePopUpLine();

  Line = MakePopUpLine(W, string, function, argument);
  AttachPopUpLine(Line);

  return(Line);
}


int CascadeTriggerWidth = 6;	/* *DKY-11Mar91* - for cascading menus */
int CascadeUseIcon = 1;		/* *DKY-11Mar91* - do we put an icon on cascading menus? */
struct Window *CurrentCascadingIconWindow = NULL;


/*  AddCascadePopUpLine() -- adds a line to a pop-up menu, which will display 'string' and if the pen is released
 *    while over it, will call 'function' with 'argument'.  The special thing is that if you move the pen to the
 *    right edge, a child (cascading or pull-right) menu will appear.  AddCascadePopUpLine() returns a pointer
 *    to that new child menu, which the user can then attach pop-up lines to.
 *  The default is for a triangle icon to appear on the right side of the menu line, but this can be disabled by 
 *    calling SetCascadeUseIcon(0) before calling AddCascadingPopUpLine().  [This icon may not be placed correctly
 *    'cause of some bug that causes pstruct->line_height to be set improperly for large sized fonts.]
 *
 *  *DKY-11Mar91*
 */
struct Window *
AddCascadingPopUpLine( menu, string, function, argument)
     struct Window *menu;
     char *string;
     int (*function)();
     char *argument;
{
  struct Window *newLine, *newTrigger, *menu2, *iconBase; /* menu2 is the child menu */
  struct popup_struct *pstruct;
  struct rectstruct *rectstruct;
  struct wrapstruct *wparms;
  struct curstruct *cascadingTriangleIcon;
  
  pstruct = (struct popup_struct *)GetStuff( menu, ATTRIBUTES);
  rectstruct = (struct rectstruct *)GetStuff( menu, NEWCOLOR);

  
  /* only call the DO function of the first pop-up trigger -- otherwise we'll call the menu's function
   * once for each level of menu indentation.
   */  
  SetPopUpCallFunctionMode( 0);

  newLine = (struct Window *)MakePopUpLine( menu, string, function, argument);

  menu2 = (struct Window *)MakePopUp( newLine, pstruct->echo, 11,
				     pstruct->parms.font, pstruct->parms.size, 8,
				     pstruct->parms.red, pstruct->parms.green, pstruct->parms.blue,
				     pstruct->parms.t,
				     rectstruct->red, rectstruct->green, rectstruct->blue);

  /* make trigger area on right edge of menu line -- to trigger the cascade/pull-right menu */
  newTrigger = (struct Window *)MakeWindow( newLine->display, newLine->input, newLine, 0, 0, 10, 10, "cascading menu trigger");
  Rectify( newTrigger,  rectstruct->red, rectstruct->green, rectstruct->blue,  0, 0,0,0, 0);
  Maker( newTrigger, -CascadeTriggerWidth, 0, 0, 0);

  MakePopUpTriggerNoEor( newTrigger, pstruct->echo, menu2, CascadeTriggerWidth + 2, -pstruct->line_height);
  EchoWrap( newTrigger, pstruct->echo, JUSTDOWN|BEENDOWN, 0, 0);
  InstallWin( newTrigger);



  CurrentCascadingIconWindow = iconBase =
    (struct Window *)MakeWindow( newLine->display, newLine->input, newLine, 0, 0, 1, 1, "cascading menu trigger");
  Rectify( iconBase,  rectstruct->red, rectstruct->green, rectstruct->blue,  0, 0,0,0, 0);
  if( CascadeUseIcon) {
    /* neither icons nor triangles seem to be in the right place for all size menus.  Yech. */
    TriRectify( iconBase, rectstruct->red, rectstruct->green, rectstruct->blue,
	       0, 0,0,0, 0,
	       pstruct->parms.red, pstruct->parms.green, pstruct->parms.blue, RIGHT);
	       
    Maker( iconBase, -(CascadeTriggerWidth + 6), 4, -(CascadeTriggerWidth + 1), -6);
  }

  Wimp( iconBase);
/*  EchoWrap( iconBase, pstruct->echo, JUSTDOWN|BEENDOWN, 0, 0); */
  InstallWin( iconBase);
  
  UpdateSizes( newLine);
  
  AttachPopUpLine( newLine);

  SetPopUpCallFunctionMode( 1);	/* return things to normal. */

  return( menu2);
}


/* construct a pop-up line and assign its functions */

struct Window *MakePopUpLine(menu, string, function, argument)     /* v 1.0b */
     struct Window *menu;
     char *string, *argument;
     int (*function)();

{
 struct Window *line;
 struct Command *C;
 struct curstruct *echo;
 struct stringstruct *parms;
 struct wrapstruct *wparms; 
 struct popup_struct *p;

 /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
 C = (struct Command *) GetCommand(menu, DO);
 p = (struct popup_struct *) *(C->arguments);
 parms = &p->parms;
 echo = p->echo;

 line = (struct Window *)MakeWindow(menu->display, menu->input, menu, 0, 0, 100, 100, string); /* ignore size */
 SetUpPopLine(line, echo, function, argument);
 RStringWin(line, string, 10, 0, parms);
 Maker(line, 1, menu->height-3, -3, menu->height+16); /* these values will change in AttachPopUpLine */

 return(line);
}



/* This function takes a pop-up line, which is not installed, and adds it to the end of a menu */

AttachPopUpLine(line)     /* v 1.0b */
     struct Window *line;
{
  struct Command *C;
  struct rstringstruct *rparms;
  struct stringstruct *sparms;
  struct makestruct *mstruct;
  struct Window *menu;
  int wide;

/*point 18  0.755
point 19  0.853
point 20  0.755
point 21  0.795
point 22  0.107
*/
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



/* construct a pop-up header and attach it */

struct Window *AddPopUpHeader(menu, string,t)     /* v 1.0b */
     struct Window *menu;
     char *string;
     int t;
{
 struct Window *line;
 struct Command *C;
 struct curstruct *echo;
 struct stringstruct *parms;
  struct stringstruct *sparms;
 struct rstringstruct *rparms;
 struct wrapstruct *wparms; 
  struct makestruct *mstruct;
 struct popup_struct *p;
  int wide;

 /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
 C = (struct Command *) GetCommand(menu, DO);
 p = (struct popup_struct *) *(C->arguments);
 parms = &p->parms;
 echo = p->echo;

 line = (struct Window *)MakeWindow(menu->display, menu->input, menu, 0, 0, 100, 100, string); /* ignore size */
 EchoWrap(line, echo, 0, 0, 0);
 RStringWin(line, string, 10, 0, parms);
 HLiner(line,15,t,0,0,0);
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



/* This function removes an installed pop-up line and adjusts the menu size
   NOTE: pop-ups must be removed in the order that they were installed       */

RemovePopUpLine(line)     /* v 1.0b */
     struct Window *line;
{
  struct Window *menu;

  menu = line->parent;
  menu->height -= 20;
  UnstallWin(line);
}



/* This establishes the DO and ECHO functions for a line */

SetUpPopLine(W, echo, function, arg)     /* v 1.0b */
     struct Window *W;
     struct curstruct *echo;
     int (*function)();
     char *arg;
{
  int DoPopLine();
  struct funcstruct *parms;

  parms = (struct funcstruct *)malloc(sizeof(struct funcstruct));
  parms->function = function;
  parms->arg = arg;
  parms->highlightMenuLine = PopUpHighlightLine;
  
  AttachCommand(W, DO, DoPopLine, parms);
  AttachCommand(W, ECHO, DoPopLine, parms);
  AttachCommand(W, NOECHO, DoPopLine, parms);
  EchoWrap(W, echo, JUSTUP, 0, 0);
}



/* This is the DO and ECHO function for a line */
DoPopLine(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int screen, val = 0, val2 = 0;
  struct pickstruct *pick;
  struct funcstruct *parms;

  pick = (struct pickstruct *)data;
  parms = (struct funcstruct *)stuff;

  switch (id)
    {
    case ECHO:
    case NOECHO:
      if( parms->highlightMenuLine) /* Only highlight if we're supposed to. *DKY-12Mar91* */
	if (W->parent->stat == ALIVE) {
	  EchoOff(W->display, 0);
	  screen = W->display->fildes;
	  drawing_mode(screen, 6);
	  fill_color(screen, 1.0, 1.0, 1.0);
	  interior_style(screen, INT_SOLID, FALSE);
/*	  rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);  */
	  dcrectangle(screen, W->x1, W->y1, W->x2, W->y2); 
	  drawing_mode(screen, 3);
	  make_picture_current(screen);
	  EchoOn(E_lastx, E_lasty, W->display);
	}
      break;
    case DO:
      if ((pick->button == JUSTUP)||(pick->button == BEENUP))
	{
	  if (RestoreBackground())
	    CloseWindow(W->parent);
	  else UnstallWin(W->parent);

	  /* This is commented out, because now it is taken care of by
	     query_return.  -ds 3/92

	     if (parms->function)
			 (*parms->function)(parms->arg); */

	  query_return = (char *)parms;
	}
      break;
    }

  return(0);
}



/* Do function for a popup menu background */

DoPopUp(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct pickstruct *pick;
  struct popup_struct *pstruct, *p2;
  int outflag = 0, val = 0;

  pstruct = (struct popup_struct *)stuff;
  switch (id) {
  case DO:
    pick = (struct pickstruct *)data;

    if ((!(pstruct->mask & 1)) &&(pick->y < W->y1)) outflag = 1;
    else if ((!(pstruct->mask & 2)) &&(pick->y > W->y2)) outflag = 1;
    else if ((!(pstruct->mask & 4)) &&(pick->x < W->x1)) outflag = 1;
    else if ((!(pstruct->mask & 8)) &&(pick->x > W->x2)) outflag = 1;


    if (pstruct->x1 != -1)  /* check rectangle */
      if ((pstruct->x1 <= pick->x)&&(pstruct->y1 <= pick->y)&&(pstruct->x2 >= pick->x)&&(pstruct->y2 >= pick->y))
	outflag = 0;

    
    if ((pick->button == JUSTUP)||(pick->button == BEENUP)||(outflag))
      {
	EchoOff(W->display, 1);
	if (RestoreBackground())
	  CloseWindow(W);
	else UnstallWin(W);
	EchoOn(pick->x, pick->y, W->display);
      }
    else {
      UpdateEcho(pick->x, pick->y, W->display, pstruct->echo);
      val = STOP;  /* Do not let the Window System call any more DO functions. */
    }
    break;

  case ATTRIBUTES:
    p2 = (struct popup_struct *)data;
    pstruct->x1 = p2->x1;
    pstruct->x2 = p2->x2;
    pstruct->y1 = p2->y1;
    pstruct->y2 = p2->y2;
    break;

  }
  return (val);
}



ChangePopUpAttributes(W, x1, y1, x2, y2)     /* v 1.0b */
     struct Window *W;
     int x1, y1, x2, y2;
{
  struct popup_struct p;

  p.x1 = x1;
  p.x2 = x2;
  p.y1 = y1;
  p.y2 = y2;
  SendMessage(W, ATTRIBUTES, &p);
}


ChangePopUpLineAttributes(W, string, function, argument)     /* v 1.0b */
     struct Window *W;
     char *string, *argument;
     int (*function)();
{
  struct rstringstruct *rparms;
  struct Command *C;
  struct funcstruct *pstruct;

  /* dissect the line's function commands to get to the relevant data: stringstruct and plinestruct */
  C = (struct Command *) GetCommand(W, DRAW);
  rparms = (struct rstringstruct *) *(C->arguments);
  rparms->string = string;

  /* the ECHO command has the plinestruct as it's stuff */
  C = (struct Command *) GetCommand(W, ECHO);
  pstruct = (struct funcstruct *) *(C->arguments);
  pstruct->function = function;
  pstruct->arg = argument;

  /*
   * The following change checks to make sure the new string will
   * fit in the menu.  If it's too wide, it'll make the window wider.
   * The bug is that if it's narrower and should make the menu narrower
   * it doesn't.
   *
   * DKY-27Jul90
   */
  {
    struct Window *menu;
    struct stringstruct *sparms;
    int wide;
    
    menu = W->parent;
    sparms = rparms->parms;
    set_font( sparms->font, sparms->size, sparms->bits);
    wide = MAX( string_width(rparms->string)+24, menu->width);
    menu->width = wide;
    TransformCoords( menu, menu->relx, menu->rely, menu->width, menu->height);
  }
}


SetPopUpCallFunctionMode( mode)	/* used when using cascading menus. *DKY-11Mar91* */
     int mode;
{
  PopUpCallFunction = mode;
}



SetCascadeTriggerWidth( width)	/* used to set cascading menu trigger width. *DKY-11Mar91* */
     int width;
{
  CascadeTriggerWidth = width;
}


SetCascadeUseIcon( i)	/* used to set if cascading menus have icons on them. *DKY-11Mar91* */
     int i;
{
  CascadeUseIcon = i;
}



/*  When we add a menu line we store the value of this variable.  If it's true then that
 *  menu line will be highlighted when the pen is over it, otherwisse it won't be highlighted.
 *  So, call SetPopUpHighlightMenuLine( 0) if you want future menu items to not be highlighted,
 *  and call SetPopUpHighlightMenuLine( 1) if you want future menu items to be highlighted.
 *  Even if a menu item isn't highlighted it's function will still be called.
 * *DKY-12Mar91*
 */
SetPopUpHighlightMenuLine( mode)
     int mode;
{
  PopUpHighlightLine = mode;
}







