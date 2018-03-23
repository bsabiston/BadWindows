#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>

#include <varargs.h>		/* included for MFunctionCaller() */


/** NOTE: The description below is no longer relevant. Echo Wrap is now 2 DO functions, one at the
    beginning of the list and one at the end.    -Bob 3/9/90 **/

/***
  Echo Wrap is a very important do function. It takes care of the cursor updates for
  a window's DO function. The reason it's called echo-wrap is that it "wraps" itself
  around whatever DO function is already present in a window. Whenever the mouse is over
  a window with EchoWrap installed, the cursor will updated, and then the window's old
  do function(s) will be called. Basically this function eliminates the need to have all
  DO functions include the same little piece of cursor code. You can write a DO function
  which just does a simple task, like sending a message or lighting up a button. Then
  you can "wrap" echo-wrap around the DO function, and the cursor stuff will be taken
  care of.

  whenmask:
      bit 0: call the window's do function(s) on JUSTDOWN
      bit 1: call the window's do function(s) on JUSTUP
      bit 2: call the window's do function(s) on BEENDOWN
      bit 3: call the window's do function(s) on BEENUP

  if the trapflag is set, a trap will be added to the window. that means that once you press
  down on the window, all the do messages will keep going to it until you lift up--even if the cursor
  is not over the window.
***/


 
EchoWrap(W, echo, whenmask, trapflag, now)  
     struct Window *W;
     struct curstruct *echo;
     int whenmask, now, trapflag;
{
  struct wrapstruct *parms;
  struct Command *C;
  int BeforeEchoWrap(),AfterEchoWrap();
  int (**functions)(), i;
  char **args;

  parms = (struct wrapstruct *)malloc(sizeof(struct wrapstruct));
  parms->echo = echo;
  parms->whenmask = whenmask;
  parms->now = now;
  parms->trapflag = trapflag;

/*** Notes on the whenmask:

     the whenmask is a four-bit value. each bit represents a mouse button condition in the do function.
         Bit 1: JUSTDOWN
®         Bit 2: JUSTUP
         Bit 3: BEENDOWN
         Bit 4: BEENUP

     setting a bit means that echo-wrap will call it's subcommands on that mouse condition.
     for example, a value of 7 means that the window's  real do-function will be called all the
     time except for BEENUP.  A value of 15 will call the Do function all the time but it might
     look bad.

     use now=0 if the action taking place in the real do-function is all starbase. Use 1
     if it's direct frame-buffer access. This variable tells the cursor routines when to
     use make_picture_current.  Now = 0 looks much, much better, but it can screw up when
     you're using direct access.
***/

  C = W->commands;
  if (C)
    {
      while ((C->next)&&(C->id != DO)) C = C->next;
      if (C->id != DO)
	{
	  AttachCommand(W, DO, BeforeEchoWrap, parms);   /* no DO function */
	  AttachCommand(W, DO, AfterEchoWrap, parms);
	}
      else
	{
	  C->numfuncs++;
	  functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
	  args = (char **)malloc(C->numfuncs*sizeof(char *));
	  *(functions) = BeforeEchoWrap;
	  *(args) = (char *)parms;
	  for (i = 0; i < C->numfuncs-1; i++)
	    {
	      *(functions+i+1) = *(C->functions+i);
	      *(args+i+1) = *(C->arguments+i);
	    }
	  if (C->numfuncs >1) { free(C->functions);   free(C->arguments);}
	  
	  C->functions = functions;
	  C->arguments = args;

	  AttachCommand(W, DO, AfterEchoWrap, parms);
	}
    }
  else {
    AttachCommand(W, DO, BeforeEchoWrap, parms);  /* no functions at all */
    AttachCommand(W, DO, AfterEchoWrap, parms); 
  }
}



BeforeEchoWrap(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int flag = 0, val = 0, i;
  struct pickstruct *pick;
  struct wrapstruct *parms;
  struct trapstruct T;
  static int new = 0;

  parms = (struct wrapstruct *)stuff;
  pick = (struct pickstruct *)data;
  switch (pick->button)
    {
    case (JUSTDOWN):
      flag = parms->whenmask & 1;
      if (parms->trapflag)  T.window = W, T.until = BEENUP, Dispatch(W, TRAP, &T, NULL), new = 1;
      break;
    case (JUSTUP):
      flag = (parms->whenmask & 2) && (!parms->trapflag||new);
      new = 0;
      break;
    case (BEENDOWN):
      flag = (parms->whenmask & 4) && (!parms->trapflag||new);
      break;
    case (BEENUP):
      flag = parms->whenmask & 8;
      break;
    }

  if (flag)
    {
      EchoOff(W->display, parms->now);
    }
  else
    {
      UpdateEcho(pick->x, pick->y, W->display, parms->echo);
      val = STOP;  /* Do not let the Window System call any more DO functions. */
    }

  return(val);
}


AfterEchoWrap(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct pickstruct *pick;
  pick = (struct pickstruct *)data;
  EchoOn(pick->x, pick->y, W->display);
  return(0);
}


Quitter(W)     /* v 1.0b */
     struct Window *W;
{
  int QuitWin();
  AttachCommand(W, DO, QuitWin, NULL);
}



QuitWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  if (((struct pickstruct *)data)->button == JUSTDOWN) Quit();
  return(0);
}

AskQuitter(W)     /* v 1.0b */
     struct Window *W;
{
  int AskQuitWin();
  AttachCommand(W, DO, AskQuitWin, NULL);
}



AskQuitWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct Window *R;
  if (((struct pickstruct *)data)->button == JUSTDOWN)
    {
      R = W;
      while (R->parent) R = R->parent;
       if (AskYesNo(R,E_lastx,E_lasty,"Are you sure you want to quit?")) Quit();
    }
  return(0);
}


Quit()     /* v 1.0b */
{
  ClearScreenII();
  reset1c();

  /** here you might want to put some code to close the MIDIC and AKAI someday ***/
  exit(0);
}



Closer(W, M)     /* v 1.0b */
     struct Window *W, *M;
{
  int CloseAWindow();
  AttachCommand(W, DO, CloseAWindow, M);
}


CloseAWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  if (W->stat) CloseWindow(stuff); 
  return(0);
}


Opener(W, M)     /* v 1.0b */
     struct Window *W, *M;
{
  int OpenAWindow();
  AttachCommand(W, DO, OpenAWindow, M);
}


OpenAWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  if ((((struct pickstruct *)data)->button == JUSTUP)&&(W->stat)) OpenWindow(stuff);
  return(0);
}

Updater(W, M)     /* v 1.0b */
     struct Window *W, *M;
{
  int UpdateAWindow();
  AttachCommand(W, DO, UpdateAWindow, M);
}


UpdateAWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  if ((((struct pickstruct *)data)->button == JUSTUP)&&(W->stat)) BufUpdateWin(stuff);
  return(0);
}


Messenger(W, id1, M, id, data, mask)     /* v 1.0b */
     struct Window *W, *M;
     int id, mask, id1;
     char *data;
{
  int PassMessage(), UpdateMessenger();
  struct messagestruct *parms;

  parms = (struct messagestruct *)malloc(sizeof(struct messagestruct));
  parms->W = M;
  parms->id = id;
  parms->data = data;
  parms->mask = mask;
  AttachCommand(W, id1, PassMessage, parms);
  AttachCommand(W, CHANGEDESTINATION, UpdateMessenger, parms); /* Tim */
  if(e_value)
    MessengerDebug(W, id1, M, id, data, mask,parms,"Messenger");
}

int
UpdateMessenger(W, id, data, stuff)  /* Tim */
     struct Window *W;                    /* takes a window, and changes the */
     int id;                              /* messenger to talk to that window */
     char *data, *stuff;
{
  struct messagestruct *parms;
  struct Window *M;

  parms = (struct messagestruct *)stuff;

  M = (struct Window *)data;

  parms->W = M;

  return (0);
}


PassMessage(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct messagestruct *parms;
  int flag, val = 0;

  parms = (struct messagestruct *)stuff;
  if (id == DO)
    switch (((struct pickstruct *)data)->button)
      {
      case (JUSTDOWN): flag = parms->mask & 1;
	break;
      case (JUSTUP):   flag = parms->mask & 2;
	break;
      case (BEENDOWN): flag = parms->mask & 4;
	break;
      case (BEENUP):   flag = parms->mask & 8;
	break;
      }
  else flag = 1;

  if (flag) val = SendMessage(parms->W, parms->id, parms->data);

  return(val);
}




FunctionCaller(W, id, function, argument, mask)     /* v 1.0b */
     struct Window *W;
     int (*function)();
     char *argument;
     int id, mask;
{
  int CallFunction();
  struct function_struct *parms;

  parms = (struct function_struct *)malloc(sizeof(struct function_struct));
  parms->function = function;
  parms->argument = argument;
  parms->mask = mask;
  AttachCommand(W, id, CallFunction, parms);
}


CallFunction(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct function_struct *parms;
  int flag = 1, val = 0;

  parms = (struct function_struct *)stuff;
  if ((id == DO)||(id == ECHO)||(id == NOECHO)) {
    switch (((struct pickstruct *)data)->button)
      {
      case (JUSTDOWN): flag = parms->mask & 1;
	break;
      case (JUSTUP):   flag = parms->mask & 2;
	break;
      case (BEENDOWN): flag = parms->mask & 4;
	break;
      case (BEENUP):   flag = parms->mask & 8;
	break;
      }
  }
  if (flag) val = (*parms->function)(parms->argument);

  return(val);
}


/*
 * MFunctionCaller()
 *    This function works just like FunctionCaller() except that you can specify an arbitrary
 *    number of arguments to be passed to the function.  The format of this function is:
 *        MFunctionCaller( W, id, function, numArgs, arg1, arg2, ..., argN, mask)
 *    where numArgs is the number of arguments to follow in the list.  As examples:
 *        MFunctionCaller( myWin, DO, DoQuit, 1, Root1, JUSTDOWN);
 *        MFunctionCaller( myWin, DO, DoSillyQuit, 3, Root1, &foo, 72, JUSTDOWN);
 *    Each arg in the arglist should be the size of a char *.
 *
 *    Currently you can not have more than 10 arguments -- but feel free to change that.
 *
 *    *DKY-13Feb91*
 */

MFunctionCaller(W, id, function, numArgs, va_alist)
     struct Window *W;
     int id, numArgs;
     int (*function)();
     va_dcl			/* we don't really need to do this with va_args, but it's more fun. */
{
  va_list ap;
  int Multi_CallFunction();
  struct m_function_struct *parms;
  char* arg;
  int argno = 0;

  parms = (struct m_function_struct *)malloc(sizeof(struct m_function_struct));
  parms->function = function;
  parms->numArgs = numArgs;

  if( numArgs > 10) {
    printf( "ERROR: MFunctionCaller() -- Too many arguments (%d).  No command attached.\n", numArgs);
    return( 0);
  }
  
  va_start( ap);

  while( argno < numArgs) {
    arg = va_arg( ap, char *);
    parms->args[argno] = arg;
    argno += 1;
  }
  parms->mask = (int)va_arg( ap, char *);

  va_end( ap);

  AttachCommand(W, id, Multi_CallFunction, parms);
}


Multi_CallFunction(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct m_function_struct *parms;
  int flag = 1, val = 0;

  parms = (struct m_function_struct *)stuff;
  if ((id == DO)||(id == ECHO)||(id == NOECHO)) {
    switch (((struct pickstruct *)data)->button)
      {
      case (JUSTDOWN): flag = parms->mask & 1;
	break;
      case (JUSTUP):   flag = parms->mask & 2;
	break;
      case (BEENDOWN): flag = parms->mask & 4;
	break;
      case (BEENUP):   flag = parms->mask & 8;
	break;
      }
  }
  if (flag) {
    switch( parms->numArgs)	/* gross, but how else can it be done? */
      {
      case 0:
	val = (*parms->function)();
	break;
      case 1:
	val = (*parms->function)(parms->args[0]);
	break;
      case 2:
	val = (*parms->function)(parms->args[0], parms->args[1]);
	break;
      case 3:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2]);
	break;
      case 4:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3]);
	break;
      case 5:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4]);
	break;
      case 6:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
				 parms->args[5]);
	break;
      case 7:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
				 parms->args[5], parms->args[6]);
	break;
      case 8:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
				 parms->args[5], parms->args[6], parms->args[7]);
	break;
      case 9:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
				 parms->args[5], parms->args[6], parms->args[7], parms->args[8]);
	break;
      case 10:
	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
				 parms->args[5], parms->args[6], parms->args[7], parms->args[8], parms->args[9]);
	break;
      default:
	printf( "ERROR: Multi_CallFunction() -- can't deal with %d arguments.\n", parms->numArgs);
      }
  }

  return( val);
}





/*** NOTE: an alternate version of mover which uses two screens is in twoscreen.c   It's called MoverII. ***/

Mover(W, M)     /* v 1.0b */
     struct Window *W, *M;
{
  int MoveAWindow();
  AttachCommand(W, DO, MoveAWindow, M);
}



MoveAWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int x, y, dx, dy;
  struct pickstruct *pick;

  pick = (struct pickstruct *)data;
  x = pick->x;
  y = pick->y;
  dx = x-W->x1;
  dy = y-W->y1;

  if  (pick->button == JUSTDOWN)
    {
      Move((struct Window *)stuff, &x, &y);
      pick->x = W->x1+dx;
      pick->y = W->y1+dy;
      /* printf( "new position: x=%d y=%d width=%d height=%d\n", W->x1, W->y1, W->width, W->height); */
    }

  return(0);
}



Move(W, x, y)     /* v 1.0b */
     struct Window *W;
     int *x, *y;
{
  int dx, dy, x1, x2, y1, y2, ox, oy, width, height, xs, ys, xe, ye;
  float fx1, fx2, fy1, fy2, fx, fy, fz, p;
  int value, valid, display, locator;
  struct Window *parent;

  parent = W->parent;

  dx = *x - W->x1;
  dy = *y - W->y1;

  value = 1;
  width = W->width;
  height = W->height;
  display = (W->display)->fildes;
  locator = (W->input)->fildes;

  x1 = parent->x1;
  y1 = parent->y1;
  x2 = parent->x2;
  y2 = parent->y2;

  interior_style(display, INT_HOLLOW, TRUE);
  perimeter_color(display, 1.0, 1.0, 1.0);
  line_color(display, 1.0, 1.0, 1.0);
  drawing_mode(display, 6);

  xs = *x-dx; ys = *y-dy; xe = xs+width-1; ye = ys+height-1;
  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
  make_picture_current(display);

  while (value >0)
    {
      if (!screen_toggle) value = ReadLocII(locator, W->display, x, y, &p);
      else value = ReadLocII(locator, NULL, x, y, &p);

      if ((*x-dx)<x1) *x= x1+dx;
      if ((*y-dy)<y1) *y= y1+dy;
      if (*x-dx+width-1>x2) *x = x2-(width-1)+dx;
      if (*y-dy+height-1>y2) *y = y2-(height-1)+dy;
      *x -= dx; *y -= dy;

      if ((*x != xs)||(*y != ys)||(*x+width-1 != xe)||(*y+height-1 != ye))
	{
	  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
	  make_picture_current(display);
	  xs = *x; ys = *y; xe = *x+width-1; ye = *y+height-1;
	  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
	  make_picture_current(display);
	}
    }

  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
  drawing_mode(display, 3);
  make_picture_current(display);


  if (!(W->display->bits & DBUFFER))
    MoveWindow(W, *x, *y);
  else {
    /* special double buffered move command */
    ox = W->x1;  oy = W->y1;
    DrawToInvis(W);
    MoveWindow(W, *x, *y);
    BufSwitch(W);
     UnstallWin(W);
     MoveCoords(W, ox,oy);
     InstallWin(W);
     MoveWindow(W, *x, *y);
    DrawToVis(W);
  }
  
  return;
}


SnapMover(W, M, hgrid, vgrid)
     struct Window *W, *M;
     int hgrid, vgrid;
{
  int SnapMoveAWindow();
  struct snapstruct *params;

  params = (struct snapstruct *) malloc(sizeof(struct snapstruct));
  params->movewin = M;
  if (!hgrid) hgrid = 1;
  if (!vgrid) vgrid = 1;
  params->hgrid   = hgrid;
  params->vgrid   = vgrid;
  AttachCommand(W, DO, SnapMoveAWindow, params);
}



SnapMoveAWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int x, y, dx, dy;
  struct pickstruct *pick;
  struct snapstruct *snap;
  struct Window *movewin;
  int hgrid, vgrid;

  snap = (struct snapstruct *)stuff;
  movewin = snap->movewin;
  hgrid = snap->hgrid;
  vgrid = snap->vgrid;

  pick = (struct pickstruct *)data;
  x = pick->x;
  y = pick->y;
  dx = x-W->x1;
  dy = y-W->y1;

  if (pick->button == JUSTDOWN)
    {
      SnapMove(movewin, &x, &y, hgrid, vgrid);
      pick->x = W->x1+dx;
      pick->y = W->y1+dy;
    }

  return(0);
}



SnapMove(W, x, y, hgrid, vgrid)
     struct Window *W;
     int *x, *y;
     int hgrid, vgrid;
{
  int dx, dy, x1, x2, y1, y2, ox, oy, width, height, xs, ys, xe, ye;
  float fx1, fx2, fy1, fy2, fx, fy, fz, p;
  int value, valid, display, locator;
  struct Window *parent;

  parent = W->parent;

  dx = *x - W->x1;
  dy = *y - W->y1;

  value = 1;
  width = W->width;
  height = W->height;
  display = (W->display)->fildes;
  locator = (W->input)->fildes;

  x1 = parent->x1;
  y1 = parent->y1;
  x2 = parent->x2;
  y2 = parent->y2;

  interior_style(display, INT_HOLLOW, TRUE);
  perimeter_color(display, 1.0, 1.0, 1.0);
  line_color(display, 1.0, 1.0, 1.0);
  drawing_mode(display, 6);

  xs = *x-dx; ys = *y-dy; xe = xs+width-1; ye = ys+height-1;
  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
  make_picture_current(display);

  while (value >0)
    {
      if (!screen_toggle) value = ReadLocII(locator, W->display, x, y, &p);
      else value = ReadLocII(locator, NULL, x, y, &p);

      if ((*x-dx)<x1) *x= x1+dx;
      if ((*y-dy)<y1) *y= y1+dy;
      if (*x-dx+width-1>x2) *x = x2-(width-1)+dx;
      if (*y-dy+height-1>y2) *y = y2-(height-1)+dy;
      *x -= dx; *y -= dy;

      if ((*x != xs)||(*y != ys)||(*x+width-1 != xe)||(*y+height-1 != ye))
	{
	  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
	  make_picture_current(display);
	  xs = *x; ys = *y; xe = *x+width-1; ye = *y+height-1;
	  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
	  make_picture_current(display);
	}
    }

  rectangle(display, (float)xs, (float)ys, (float)xe, (float)ye);
  drawing_mode(display, 3);
  make_picture_current(display);
  CloseWindow(W);
  SnapMoveCoords(W, *x, *y, hgrid, vgrid);
  OpenWindow(W);

  return;
}


SnapMoveCoords(W,nx,ny,hgrid,vgrid)
     struct Window *W;
     int nx,ny, hgrid, vgrid;
{
  int x1,y1,x2,y2;
  int xpos, ypos, hd, vd;

  GetPoints(W->parent,&x1,&y1,&x2,&y2);

  if (nx+W->width-1<=x2)  xpos = nx-x1;
  else                    xpos = W->relx;
  if (ny+W->height-1<=y2) ypos = ny-y1;
  else                    ypos = W->rely;

  hd = xpos % hgrid;
  vd = ypos % vgrid;
    
  if(hd < hgrid/2)
    xpos -= hd;
  else{
    if(hgrid!=1){
      if ((xpos+hgrid-hd) < W->parent->width)
	xpos += (hgrid - hd);
      else
	xpos -= hd;
    }
  }
  if(vd < vgrid/2)
    ypos -= vd;
  else{
    if(vgrid!=1) {
      if ((ypos+vgrid-vd) < W->parent->height)
	ypos += (vgrid - vd);
      else
	ypos -= vd;
    }
  }

  W->relx = xpos;
  W->rely = ypos;

  AdjustCoords(W);
}



/*
 * GracefulMover() just like Mover() but a normal DO function that doesn't have it's own loop.
 * It also updates the window being moved every time the pen moves while JUSTDOWN rather than
 * drawing an EOR box.
 *
 * Named after our own lovely Grace.
 *
 * *DKY-13Sep90*
 */




GracefulMover( W, M)
     struct Window *W, *M;
{
  int GracefulMoveAWindow();
  struct GracefulMoverStruct *parms;

  parms = (struct GracefulMoverStruct *)malloc( sizeof( struct GracefulMoverStruct));
  parms->windowToMove = M;

  AttachCommand( W, DO, GracefulMoveAWindow, parms);
}


GracefulMoveAWindow( W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct pickstruct *pick;
  struct GracefulMoverStruct *parms;
  static int didJustdown = NULL;

  pick = (struct pickstruct *)data;
  parms = (struct GracefulMoverStruct *)stuff;

  switch (pick->button)
    {
    case JUSTDOWN:
      parms->lastX = pick->x;
      parms->lastY = pick->y;
      didJustdown = 1;
      break;

    case BEENDOWN:
      if( !didJustdown)	{
	parms->lastX = pick->x;
	parms->lastY = pick->y;
	didJustdown = 1;
      }
    case JUSTUP:
      if( (pick->x != parms->lastX) || (pick->y != parms->lastY)) {
	struct Window *moveMe;
	int deltaX, deltaY, newX, newY;

	moveMe = parms->windowToMove;
	deltaX = parms->lastX - pick->x;
	deltaY = parms->lastY - pick->y;

	newX = moveMe->x1 - deltaX;
	newY = moveMe->y1 - deltaY;

	/* make sure new position is within parent window */
	if( newX < moveMe->parent->x1)
	  newX = moveMe->parent->x1;
	else if( (newX + moveMe->width) > moveMe->parent->x2)
	  newX = moveMe->parent->x2 - moveMe->width + 1;

	if( newY < moveMe->parent->y1)
	  newY = moveMe->parent->y1;
	else if( (newY + moveMe->height) > moveMe->parent->y2)
	  newY = moveMe->parent->y2 - moveMe->height + 1;

	MoveWindow( moveMe, newX, newY);

	parms->lastX = pick->x;
	parms->lastY = pick->y;
      }
      break;

    case BEENUP:
      break;
    }

  if( (pick->button == JUSTUP) ||  (pick->button == BEENUP)) {
    didJustdown = NULL;
  }
  return( 0);
}



/*--- W: Window to which the function is attach, R: Window to be resized, coordinates are the min and max position
      of the right bottom corner of the window to be resized
-----------------------------------------------------------------------------------------------------------------*/
struct resizestruct *
ResizerPlus(W, R, xmin, ymin, xmax, ymax)     /* v 1.0b */
     struct Window *W, *R;
     int xmax, ymax, xmin, ymin;
{
  struct resizestruct *params;
  int ResizeAWindowPlus();

  params = (struct resizestruct *) malloc(sizeof(struct resizestruct));
  params->movewin = R;
  params->xmin = xmin;
  params->ymin = ymin;
  params->xmax = xmax;
  params->ymax = ymax;
  AttachCommand(W, DO, ResizeAWindowPlus, (char *)params);
  return(params);
}



ResizeAWindowPlus(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  static int rootx, rooty, new= 0, ox, oy, cx, cy, tx, ty;
  struct Window *RWindow, *SWindow;
  int x, y, button, xlim, ylim,x1,y1,x2,y2;
  struct pickstruct *pick;
  struct resizestruct *mstruct;
  struct message *trap;

  mstruct = (struct resizestruct *)stuff;

  switch (id)
    {
    case (DO):

      RWindow = mstruct->movewin;

      pick = (struct pickstruct *)data;
      x = pick->x;
      y = pick->y;
      button = pick->button;

      switch (button)
	{
	case (JUSTDOWN):
	  cx = RWindow->x2-x; cy = RWindow->y2-y;
	  x += cx;
	  y += cy;
	  rootx = RWindow->x1; rooty = RWindow->y1;
	  StartEorBox(W->display->fildes, rootx, rooty, x, y);
	  Dispatch(W, TRAP, MakeTrap(W, BEENUP), NULL);
	  ox = x;
	  oy = y;
	  new = 1;
	  break;
	case (BEENUP):
	  break;
	case (JUSTUP):
	  if (new)
	    {
	      x = ox;
	      y = oy;
	      EndEorBox(W->display->fildes);
	      Order(&rootx, &rooty, &x, &y);
	      x -= (rootx-1);
	      y -= (rooty-1);

	      if (!(W->display->bits & DBUFFER)) {
		CloseWindow(RWindow);
		TransformCoords(RWindow, rootx-(RWindow->parent)->x1, rooty-(RWindow->parent)->y1, x, y);
		OpenWindow(RWindow);
	      }
	      else {
		x1 = RWindow->x1; y1 = RWindow->y1; x2 = RWindow->x2;	y2 = RWindow->y2;
		DrawToInvis(RWindow);
		 CloseWindow(RWindow);
		 TransformCoords(RWindow, rootx-(RWindow->parent)->x1, rooty-(RWindow->parent)->y1, x, y);
		 OpenWindow(RWindow);
		BufSwitch(RWindow);
		  TransformCoords(RWindow, x1-(RWindow->parent)->x1, y1-(RWindow->parent)->y1, x2-x1+1, y2-y1+1);
		  DrawMask(RWindow, x1, y1, x2, y2);
		  ShowTops(RWindow->parent, x1, y1, x2, y2);
		  TransformCoords(RWindow, rootx-(RWindow->parent)->x1, rooty-(RWindow->parent)->y1, x, y);
		  UpdateWin(RWindow);
		DrawToVis(RWindow);
	      }

	      /* printf("x %d  y %d  w %d  h %d\n", RWindow->x1, RWindow->y1, x, y); */
	      new = 0;
	      x += (rootx-1);
	      y += (rooty-1);
	    }
	  break;
	case (BEENDOWN):
	  if (new)
	    {
	      x += cx; y += cy;
	      if ((x <= (RWindow->parent)->x2)&&(y<= (RWindow->parent)->y2) &&
		  (x >= (RWindow->parent)->x1) && (y >= (RWindow->parent)->y1))
		{
		  if (x-rootx+1 < mstruct->xmin) x = rootx+mstruct->xmin-1;
		  if (x-rootx+1 > mstruct->xmax) x = rootx+mstruct->xmax-1;
		  if (y-rooty+1 < mstruct->ymin) y = rooty+mstruct->ymin-1;
		  if (y-rooty+1 > mstruct->ymax) y = rooty+mstruct->ymax-1;

		  UpdateEorBox(W->display->fildes, rootx, rooty, x, y);
		  ox = x;
		  oy = y;
		}
	    }
	  break;

	}
      break;
    }

  return(0);
}


/*Following is a quick and dirty modification of ResizerPlus that constrain square windows to stay square
 when resized 
 Note: xmax should be no bigger than 1024 and the window to resize should be square to begin with.
-----------------------------------------------------------------------------------------------------------*/


struct resizestruct *
ResizerPlusSquare(W, R, xmin, xmax)     /* DB 8-23-91 */
     struct Window *W, *R;
     int xmax, xmin;
{
  struct resizestruct *params;
  int ResizeASquareWindowPlus();

  params = (struct resizestruct *) malloc(sizeof(struct resizestruct));
  params->movewin = R;
  params->xmin = xmin;
  params->ymin = xmin;
  params->xmax = xmax;
  params->ymax = xmax;
  AttachCommand(W, DO, ResizeASquareWindowPlus, (char *)params);
  return(params);
}



ResizeASquareWindowPlus(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  static int rootx, rooty, new= 0, ox, oy, cx, cy, tx, ty;
  struct Window *RWindow, *SWindow;
  int x, y, button, xlim, ylim;
  struct pickstruct *pick;
  struct resizestruct *mstruct;
  struct message *trap;

  mstruct = (struct resizestruct *)stuff;

  switch (id)
    {
    case (DO):

      RWindow = mstruct->movewin;

      pick = (struct pickstruct *)data;
      x = pick->x;
      y = pick->x;
      button = pick->button;

      switch (button)
	{
	case (JUSTDOWN):
	  cx = RWindow->x2-x; cy = RWindow->x2-x;
	  x += cx;
	  y += cx;
	  rootx = RWindow->x1; rooty = RWindow->y1;
	  StartEorBox(W->display->fildes, rootx, rooty, x, y);
	  Dispatch(W, TRAP, MakeTrap(W, BEENUP), NULL);
	  ox = x;
	  oy = x;
	  new = 1;
	  break;
	case (BEENUP):
	  break;
	case (JUSTUP):
	  if (new)
	    {
	      x = ox;
	      y = ox;
	      EndEorBox(W->display->fildes);
	      Order(&rootx, &rooty, &x, &y);
	      x -= (rootx-1);
	      y -= (rootx-1);

	      CloseWindow(RWindow);
	      TransformCoords(RWindow, rootx-(RWindow->parent)->x1, rootx-(RWindow->parent)->x1, x, x);
	      OpenWindow(RWindow);
	      /* printf("x %d  y %d  w %d  h %d\n", RWindow->x1, RWindow->y1, x, y); */
	      new = 0;
	      x += (rootx-1);
	      y += (rootx-1);
	    }
	  break;
	case (BEENDOWN):
	  if (new)
	    {
	      x += cx; y += cx;
	      if ((x <= (RWindow->parent)->x2)&&(y<= (RWindow->parent)->x2) &&
		  (x >= (RWindow->parent)->x1) && (y >= (RWindow->parent)->x1))
		{
		  if (x-rootx+1 < mstruct->xmin) x = rootx+mstruct->xmin-1;
		  if (x-rootx+1 > mstruct->xmax) x = rootx+mstruct->xmax-1;
		  if (y-rooty+1 < mstruct->ymin) y = rooty+mstruct->xmin-1;
		  if (y-rooty+1 > mstruct->ymax) y = rooty+mstruct->xmax-1;

		  UpdateEorBox(W->display->fildes, rootx, rooty, x, y);
		  ox = x;
		  oy = x;
		}
	    }
	  break;

	}
      break;
    }

  return(0);
}
/***/

/*--- W: Window to which the function is attach, the same as the window to be resized. Margin is the active distance
      from the corners, in pixels. Coordinates are the min and max window size 
-----------------------------------------------------------------------------------------------------------------*/
struct resizestruct *
CornerResizer(W, margin, xmin, ymin, xmax, ymax)     /* v 1.0b */
     struct Window *W;
     int xmax, ymax, xmin, ymin;
{
  int *nums;
  int CornerResizeAWindow();

  nums = (int *)malloc(5*sizeof(int));
  *(nums+0) = margin;
  *(nums+1) = xmin;
  *(nums+2) = ymin;
  *(nums+3) = xmax;
  *(nums+4) = ymax;
  AttachCommand(W, DO, CornerResizeAWindow, (char *)nums);
}


CornerResizeAWindow(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  static int rootx, rooty, new= 0, ox, oy, cx, cy, tx, ty, corner = 0;
  int x, y, button, xlim, ylim, margin;
  struct pickstruct *pick;
  int *nums, val = 0,x1,y1,x2,y2;
  struct message *trap;

  nums = (int *)stuff;

  switch (id)
    {
    case (DO):

      pick = (struct pickstruct *)data;
      x = pick->x;
      y = pick->y;
      button = pick->button;

      switch (button)
	{
	case (JUSTDOWN):
	  /* check to see if in a valid point */
	  margin = *nums;
	  if (x< W->x1+margin)
	    {
	      if (y<W->y1+margin) corner = 1;
	      else if (y> W->y2-margin) corner = 3;
	      else corner = 0;
	    }
	  else if (x > W->x2-margin){
	      if (y<W->y1+margin) corner = 2;
	      else if (y> W->y2-margin) corner = 4;
	      else corner = 0;
	  }
	  else corner = 0;

	  if (corner) {
	    val = STOP; /* stop the window system from calling any DO functions after this one */
	    switch (corner)
	      {
	      case (1):
		cx = W->x1-x; cy = W->y1-y;
		x += cx;
		y += cy;
		rootx = W->x2; rooty = W->y2;
		break;
	      case (2):
		cx = W->x2-x; cy = W->y1-y;
		x += cx;
		y += cy;
		rootx = W->x1; rooty = W->y2;
		break;
	      case (3):
		cx = W->x1-x; cy = W->y2-y;
		x += cx;
		y += cy;
		rootx = W->x2; rooty = W->y1;
		break;
	      case (4):
		cx = W->x2-x; cy = W->y2-y;
		x += cx;
		y += cy;
		rootx = W->x1; rooty = W->y1;
		break;
	      }
		StartEorBox(W->display->fildes, rootx, rooty, x, y);
		Dispatch(W, TRAP, MakeTrap(W, BEENUP), NULL);
		ox = x;
		oy = y;
		new = 1;
	  }
	  break;
	case (BEENUP):
	  break;
	case (JUSTUP):
	  if (new)
	    {
	      x = ox;
	      y = oy;
	      EndEorBox(W->display->fildes);
	      Order(&rootx, &rooty, &x, &y);
	      x -= (rootx-1);
	      y -= (rooty-1);

	      if (!(W->display->bits & DBUFFER)) {
		CloseWindow(W);
		TransformCoords(W, rootx-(W->parent)->x1, rooty-(W->parent)->y1, x, y);
		OpenWindow(W);
	      }
	      else {
		x1 = W->x1; y1 = W->y1; x2 = W->x2;	y2 = W->y2;
		DrawToInvis(W);
		CloseWindow(W);
		TransformCoords(W, rootx-(W->parent)->x1, rooty-(W->parent)->y1, x, y);
		OpenWindow(W);
		BufSwitch(W);
		TransformCoords(W, x1-(W->parent)->x1, y1-(W->parent)->y1, x2-x1+1, y2-y1+1);
		DrawMask(W, x1, y1, x2, y2);
		ShowTops(W->parent, x1, y1, x2, y2);
		TransformCoords(W, rootx-(W->parent)->x1, rooty-(W->parent)->y1, x, y);
		UpdateWin(W);
		DrawToVis(W);
	      }

	      new = 0;
	      x += (rootx-1);
	      y += (rooty-1);
	      corner = 0;
	      val = STOP; /* stop the window system from calling any DO functions after this one */
	    }
	  break;
	case (BEENDOWN):
	  if (new)
	    {
	      val = STOP; /* stop the window system from calling any DO functions after this one */
	      x += cx; y += cy;
	      if ((x <= (W->parent)->x2)&&(y<= (W->parent)->y2) &&
		  (x >= (W->parent)->x1) && (y >= (W->parent)->y1))
		{
		  if (abs(x-rootx+1) < *(nums+1)) x = ox;
		  if (abs(x-rootx+1) > *(nums+3)) x = ox;
		  if (abs(y-rooty+1) < *(nums+2)) y = oy;
		  if (abs(y-rooty+1) > *(nums+4)) y = oy;

		  UpdateEorBox(W->display->fildes, rootx, rooty, x, y);
		  ox = x;
		  oy = y;
		}
	    }
	  break;

	}
      break;
    }

  return(val);
}



Sucker(W, CWin, OWin)     /* v 1.0b */
     struct Window *W, *CWin, *OWin;
{
  struct suckstruct *params;
  int SuckAWindow();

  params = (struct suckstruct *) malloc(sizeof(struct suckstruct));
  params->closewin = CWin;
  params->openwin = OWin;

  AttachCommand(W, DO, SuckAWindow, (char *)params);
}



SuckAWindow(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct Window *CWindow, *OWindow;
  struct pickstruct *pick;
  struct suckstruct *mstruct;


  mstruct = (struct suckstruct *)stuff;
  CWindow = mstruct->closewin;
  OWindow = mstruct->openwin;

  pick = (struct pickstruct *)data;
  if (pick->button ==JUSTDOWN) {
    CloseWindow(CWindow);
    GetPoints(OWindow, &(OWindow->x1), &(OWindow->y1), &(OWindow->x2),
	      &(OWindow->y2));
    UpdateSizes(OWindow);
    SuckCoords(CWindow, OWindow);
    OpenWindow(OWindow);
  }
  return(0);
}



SuckCoords(W1, W2)     /* v 1.0b */
     struct Window *W1, *W2;
{
  int screen, x1, y1, x2, y2, t;

  screen = (W1->display)->fildes;
  x1 = W1->x1;
  y1 = W1->y1;
  x2 = W1->x2;
  y2 = W1->y2;

  StartEorBox(screen, x1, y1, x2, y2);

  for (t = 1; t<50; t++)
    {
      Ipoint(W1->x1, W2->x1, &x1, t, 50);
      Ipoint(W1->x2, W2->x2, &x2, t, 50);
      Ipoint(W1->y1, W2->y1, &y1, t, 50);
      Ipoint(W1->y2, W2->y2, &y2, t, 50);
      UpdateEorBox(screen, x1, y1, x2, y2);
    }

  EndEorBox(screen);

  return;
}



Ipoint(from, to, into, step, total)     /* v 1.0b */
     int from, to, *into, step, total;
{
  int diff;
  float ratio;

  diff = to-from;
  ratio = (float)diff/(float)total;
  *into = ((float)step)*ratio+from;
}



Wimp(W)     /* v 1.0b */
     struct Window *W;
{
  int WimpWin();
  AttachCommand(W, DO, WimpWin, NULL);
}



WimpWin(W, id, data, stuff)     /* v 1.0b */
     struct WIndow *W;
     int id;
     char *data, *stuff;
{
  return(1);
}




#if 0 

 /* THIS IS THE OLD VERSION OF ECHOWRAP. THAT WEIRD IF THING ABOVE IS JUST TO COMMENT OUT THIS CODE */
 
EchoWrap(W, echo, whenmask, trapflag, now)  
     struct Window *W;
     struct curstruct *echo;
     int whenmask, now, trapflag;
{
  struct wrapstruct *parms;
  struct Command *C;
  int EchoWrapWin();

  parms = (struct wrapstruct *)malloc(sizeof(struct wrapstruct));
  parms->echo = echo;
  parms->functions = NULL;
  parms->arguments = NULL;
  parms->numfuncs = 0;
  parms->whenmask = whenmask;
  parms->now = now;
  parms->trapflag = trapflag;

/*** Notes on the whenmask:

     the whenmask is a four-bit value. each bit represents a mouse button condition in the do function.
         Bit 1: JUSTDOWN
         Bit 2: JUSTUP
         Bit 3: BEENDOWN
         Bit 4: BEENUP

     setting a bit means that echo-wrap will call it's subcommands on that mouse condition.
     for example, a value of 7 means that the window's  real do-function will be called all the
     time except for BEENUP.  A value of 15 will call the Do function all the time but it might
     look bad.

     use now=0 if the action taking place in the real do-function is all starbase. Use 1
     if it's direct frame-buffer access. This variable tells the cursor routines when to
     use make_picture_current.  Now = 0 looks much, much better, but it can screw up when
     you're using direct access.
***/

  C = W->commands;
  if (C)
    {
      while ((C->next)&&(C->id != DO)) C = C->next;
      if (C->id != DO) AttachCommand(W, DO, EchoWrapWin, parms);   /* no DO function */
      else
	{
	  parms->functions = C->functions;
	  parms->arguments = C->arguments;
	  parms->numfuncs = C->numfuncs;

	  C->numfuncs = 1;
	  C->functions = (int (**)())malloc(sizeof(int (*)()));
	  C->arguments = (char **)malloc(sizeof(char *));
	  *C->functions = EchoWrapWin;
	  *C->arguments = (char *)parms;
	}
    }
  else AttachCommand(W, DO, EchoWrapWin, parms);  /* no functions at all */
}



EchoWrapWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int flag = 0, val = 0, i;
  struct pickstruct *pick;
  struct wrapstruct *parms;
  struct trapstruct T;
  static int new = 0;

  parms = (struct wrapstruct *)stuff;
  pick = (struct pickstruct *)data;
  switch (pick->button)
    {
    case (JUSTDOWN):
      flag = parms->whenmask & 1;
      if (parms->trapflag)  T.window = W, T.until = BEENUP, Dispatch(W, TRAP, &T, NULL), new = 1;
      break;
    case (JUSTUP):
      flag = (parms->whenmask & 2) && (!parms->trapflag||new);
      new = 0;
      break;
    case (BEENDOWN):
      flag = (parms->whenmask & 4) && (!parms->trapflag||new);
      break;
    case (BEENUP):
      flag = parms->whenmask & 8;
      break;
    }

  if (flag)
    {
      EchoOff(W->display, parms->now);
      for(i = 0; i < parms->numfuncs; i++)
	if (*(parms->functions+i))
	  val = (**(parms->functions+i))(W, id, data, *(parms->arguments+i));
      EchoOn(pick->x, pick->y, W->display);
    }
  else UpdateEcho(pick->x, pick->y, W->display, parms->echo);

  return(val);
}

#endif 


