#include <stdio.h>
#include <windows.c.h>
#include <structures.h>
#include <messages.h>

extern int errno;

/** BAD WINDOWS MAC VERSION **/

SendMessage(W, id, data)
     struct Window *W;
     int id;
     char *data;
{
  struct Command *C;
  register int val = 0, count;
//  int (*func)();

  C = W->commands;
  while ((C)&&(C->id != id) && (C->id != DEFAULT)) C = C->next;

  if (C) for (count = 0; (count < C->numfuncs)&&(val != STOP); count++)
    val |= (**(C->functions+count))(W, id, data, *(C->arguments+count));
  if (val == STOP) val = 0;

  return(val);
}



AttachCommand (W, id, function, argument)   
     struct Window *W;
     int id;
     int (*function)();
     char *argument;
{
  struct Command *C;
  int (**functions)(), i;
  char **args;

  C = W->commands;
  if (C) {
    while ((C->next)&&(C->id != id)) C = C->next;
    if (C->id != id) {
      C->next = (struct Command *)malloc(sizeof(struct Command));
      C = C->next;
      C->numfuncs = 0;
      C->next = NULL;
    }
  }
  else {
    C = W->commands = (struct Command *)malloc(sizeof(struct Command));
    C->numfuncs = 0;
    C->next = NULL;
  }

  C->id = id;
  C->numfuncs++;
  functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
  args = (char **)malloc(C->numfuncs*sizeof(char *));
  for (i = 0; i < C->numfuncs-1; i++)
    {
      *(functions+i) = *(C->functions+i);
      *(args+i) = *(C->arguments+i);
    }
  *(functions+C->numfuncs-1) = function;
  *(args+C->numfuncs-1) = argument;
  if (C->numfuncs >1) { free(C->functions);   free(C->arguments);}

  C->functions = functions;
  C->arguments = args;

}


/* Remove all attached functions to a command */

DetachCommand (W, id, function)   
     struct Window *W;
     int id, (*function)();
{
  struct Command *C,*prev = NULL;
  int (**functions)(), i,t,done = 0,n;
  char **args;

  C = W->commands;
  if (C) {
    while ((C->next)&&(C->id != id)) prev = C, C = C->next;
    if (C->id == id)
      {
	t = 0;
	while ((t < C->numfuncs)&&(!done))
	  {
	    if (*(C->functions+t) == function) done = 1;
	    else t++;
	  }

	if (done) /* found function, make a new array */
	  {
	    C->numfuncs--;

	    if (C->numfuncs) {
	      functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
	      args = (char **)malloc(C->numfuncs*sizeof(char *));
	      n = 0;
	      for (i = 0; i < C->numfuncs+1; i++)
		{
		  if (i != t) {
		    *(functions+n) = *(C->functions+i);
		    *(args+n) = *(C->arguments+i);
		    n++;
		  }
		}
	      
	      free(C->functions);
	      free(C->arguments);
	    
	      C->functions = functions;
	      C->arguments = args;
	    }
	    else { /* no more functions */
	      if (!prev) W->commands = C->next;
	      else prev->next = C->next;
	      free(C->functions);
	      free(C->arguments);
	      free(C);
	    }
	  }
      } /* found id */
  }
  return (-1);
}



/* check to see if function has been attached already with the same arguments */  

CheckCommand (W, id, function, argument)     
     struct Window *W;
     int id;
     int (*function)();
     char *argument;
{
  struct Command *C;
  int (**functions)(), i;
  char **args;

  C = W->commands;
  if (C) {
    while ((C->next)&&(C->id != id)) C = C->next;
    if (C->id != id) return(0);

    C->numfuncs++;
    functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
    args = (char **)malloc(C->numfuncs*sizeof(char *));

    for (i = 0; i < C->numfuncs; i++)
      {
	if ((*(C->functions+i) == function)&&(*(C->arguments+i) == argument))
	  return(1);
      }
  }
  
  return(0);
}

/** check to see if a fuction is attached with the same ID  **/
/* does not check to see if the arguments are the same */

int CheckCommandB (W, id, function)     
     struct Window *W;
     int id;
     int (*function)();
{
  struct Command *C;
  int (**functions)(), i;
  char **args;

  C = W->commands;
  if (C) {
    while ((C->next)&&(C->id != id)) C = C->next;
    if (C->id != id) return(0);

    C->numfuncs++;
    functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));

    for (i = 0; i < C->numfuncs; i++)
       {
	if (*(C->functions+i) == function)
	  return(1);
      }
  }
  
  return(0);
}




struct Command *GetCommand(W, id)     
     struct Window *W;
     int id;
{
  struct Command *C = NULL;

  C = W->commands;
  while ((C)&&(C->id != id)) C = C->next;

  return(C);
}




char *GetStuff(W, id)     
     struct Window *W;
     int id;
{
  struct Command *C;
  C = GetCommand(W, id);
  if (C)  return(*C->arguments);
  else return(NULL);
}


char *GetArguments(W, id,function)     
     struct Window *W;
     int id, (*function)();
{
  struct Command *C;
  int t;
  C = GetCommand(W, id);

  for (t = 0; t < C->numfuncs; t++)
    if (*(C->functions+t) == function)
      return(*(C->arguments+t));

  return(NULL);
}



struct Window *MakeWindow(fildes, ifildes, owner, subx, suby, winwide, wintall, tag)     
     struct Window *owner;
     struct OutDev *fildes;
     struct InDev  *ifildes;
     int subx, suby, winwide, wintall;
     char *tag;
{
  struct Window *NewMem;
  struct List *MakeList();

  if((NewMem = (struct Window *)malloc(sizeof(struct Window)))==NULL){
    fprintf(stderr, "MakeWindow malloc Window error errno=%d\n", errno);
    fflush(stderr);
  }
  NewMem->display   = fildes;
  NewMem->input     = ifildes;
  NewMem->parent    = owner;
  NewMem->relx      = subx;
  NewMem->rely      = suby;
  NewMem->width     = winwide;
  NewMem->height    = wintall;
  NewMem->stat      = 0;
  NewMem->commands  = NULL;
  NewMem->port      = MakeList();
  NewMem->mask      = MakeList();

  if (tag)
    {
      if ((NewMem->tag = (char *)malloc((strlen(tag)+1)*sizeof(char)))==NULL) {
	fprintf(stderr,"MakeWindow malloc NewMem->tage error errno=%d\n",errno);
	fflush(stderr);
      }
      strcpy(NewMem->tag, tag);
    }
  else NewMem->tag = NULL;

  return(NewMem);
}



OpenWindow(W)     
     struct Window *W;

{
  if( W) {
    InstallWin(W);
    UpdateWin(W);
  }
  else
    printf( "OpenWindow() called on NULL window.\n");
}



UpdateWin(W)     
     struct Window *W;
{
  if(W) {
      ShowWindow(W, W->x1, W->y1, W->x2, W->y2);
      if (W->parent) ShowTops(W, W->x1, W->y1, W->x2, W->y2);
  }
  else
    fprintf( stderr, "UpdateWin: called on NULL window.\n");
  return(0);
}



AreaUpdateWin(W, x1, y1, x2, y2)     
     struct Window *W;
     int x1, y1, x2, y2;
{
  ShowWindow(W, x1, y1, x2, y2);
  if (W->parent) ShowTops(W, x1, y1, x2, y2);
  return(0);
}



InstallWin(W)     
     struct Window *W;
{
  if (W->stat != 1)
    {
      if (W->parent)
	{
	  AddToList((W->parent)->port, W);
	  MakeMask(W);
	  AddMasks(W);
	}
      GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
      TransformCoords(W,W->relx,W->rely,W->width,W->height); /* BS 2/22/91 */
      W->stat = 1;
    }
}

/* Two screen version of install  -- LHR  1/11/90 */
InstallWinII(W)  
     struct Window *W;
{
  if (W->stat != 1)
    {
      if (W->parent)
	{
	  if (W->display != W->parent->display) W->display = W->parent->display;
	  AddToList((W->parent)->port, W);
	  MakeMask(W);
	  AddMasks(W);
	}
      GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
      W->stat = 1;
    }
}


CloseWindow(W)     
     struct Window *W;
{
  if( W) {
/*    if (W->display->bits & DBUFFER) {
      DrawToInvis(W);
       DrawMask(W, W->x1, W->y1, W->x2, W->y2);
       ShowTops(W->parent, W->x1, W->y1, W->x2+1, W->y2+1);
      BufSwitch(W);
       DrawMask(W, W->x1, W->y1, W->x2, W->y2);
       ShowTops(W->parent, W->x1, W->y1, W->x2+1, W->y2+1);
      DrawToVis(W);
      UnstallWin(W);
    }
    else{
*/
      DrawMask(W, W->x1, W->y1, W->x2, W->y2);
      ShowTops(W->parent, W->x1, W->y1, W->x2+1, W->y2+1);
      UnstallWin(W);

  }
  else
    printf( "CloseWindow() called on NULL window.\n");
  
  return(0);
}


CloseAllChildren( window)	/* closes all children of a window -- *DKY- 8Jul90* */
     struct Window *window;
{
  struct List *list;
  
  if( window->port) {
    list = window->port;
    if( list)
      list = list->Front;
    while( list->id != NULL) {
      CloseAllChildren( list->id);
      CloseWindow( list->id);
      list = list->Front;
    }
  }
}



UnstallWin(W)     
     struct Window *W;
{
  if (W->stat) {
    if (GetFromList((W->parent)->port, W))
      {
	StripMask(W);
	W->stat = 0;
	return(1);
      }
    else {
      printf("UnstallWin() -- failed on window '%s'\n", W->tag);
      return(0);
    }
  }
}



RaiseWindow(W)     
     struct Window *W;
{
  UnstallWin(W);
  InstallWin(W);
  UpdateWin(W);
}



RaiseWindowII(W)     
     struct Window *W;
{
  UnstallWin(W);
  InstallWinII(W);
  UpdateWin(W);
}


/* Attach this function to a window if you want it so that
 * when you press down on the window it'll raise up.
 * DKY-19Feb91
 */
Raiseify( W, W2)
     struct Window *W, *W2;
{
  int RaiseWindow();
  FunctionCaller( W, DO, RaiseWindow, W2, JUSTDOWN);
}


SinkWindow(W)     
     struct Window *W;
{
  struct List *L, *Current, *L2;
  struct Window *temp;

  L = (W->parent)->port;
  CopyList(L, &L2);

  UnstallWin(W);
  InstallWin(W);

  for (Current = L2->Front; Current != L2; Current = Current->Front)
    {
      temp = Current->id;
      if (temp != W)
	{
	  UnstallWin(temp);
	  InstallWin(temp);
	}
    }
  UpdateWin(W);
  free(L2);
}


/******************************** Window Mechanics *************************************/



StripMask(W)     
     struct Window *W;
{
  struct List *Temp, *Temp2;

  Temp = (W->mask)->Front;

  while (Temp != W->mask)
    {
      if (Temp->id != W)
	GetFromList((Temp->id)->mask, W);
      Temp2 = Temp;
      Temp = Temp->Front;
      free(Temp2);
    }

  (W->mask)->Front = W->mask;
  (W->mask)->Behind = W->mask;
}



MakeMask(W)     
     struct Window *W;
{
  struct List *L, *Current, *Pad;

  L = (W->parent)->port;

  Pad = W->mask;
  for (Current = L->Front; Current != L; Current = Current->Front)
    {
      if (Current->id != W) {
	if (Project(W, Current->id)) AddToList(Pad, Current->id);
      }
      else AddToList(Pad, W);
    }

}



AddMasks(W)     
     struct Window *W;
{
  struct List *Current, *L;

  L = (W->parent)->port;

  for (Current= L->Front; Current != L; Current = Current->Front)
    if (Current->id != W)
      if (Project(W, Current->id)) AddToList((Current->id)->mask, W);

}



RemoveMasks(W)     
     struct Window *W;
{
  struct List *Current, *L;

  L = (W->parent)->port;

  for (Current = L->Front; Current != L; Current = Current->Front)
    if (Current->id != W)
      GetFromList((Current->id)->mask, W);

}



struct Window *
Windowfind(W, x, y, PastWin)     
     struct Window *W, *PastWin;
     int x, y;
{
  struct Window *Pick;
  struct Window *Win;
  struct List *Current, *L;
  int x1, y1;

  L = W->port;
  Current = L->Behind;

  if ((PastWin)&&(PastWin != W))
    {
      W = PastWin->parent;
      L = W->port;
      Current = L->Behind;
      for(Current; ((Current->id != PastWin)&&(Current != L)); Current= Current->Behind);
      if (Current->id == PastWin) Current = Current->Behind;
      else printf("Windowfind: it should not have printed this\n");
    }

  x1 = W->x1; y1 = W->y1;
  Pick = W;
  while ((Current != L)&&(Pick==W))
    {
      Win = Current->id;
      if ((Win->relx+x1 <= x) && (Win->relx+x1+Win->width-1 >= x) &&
          (Win->rely+y1 <= y) && (Win->rely+y1+Win->height-1 >= y))
	Pick = Win;
      Current = Current->Behind;
    }

  if (Pick != W) return(Windowfind(Pick, x, y, NULL)); /* think about this */
  else return(Pick);
}



Project (W1, W2)     
     struct Window *W1, *W2;
{
  int wx1, wx2, wy1, wy2;
  int px1, px2, py1, py2;

  wx1 = W1->relx;  wx2 = wx1 + W1->width-1;
  wy1 = W1->rely;  wy2 = wy1 + W1->height-1;
  px1 = W2->relx;  px2 = px1 + W2->width-1;
  py1 = W2->rely;  py2 = py1 + W2->height-1;

  if ( (wx1>px2) || (wx2<px1) || (wy1>py2) || (wy2<py1) )
    return(0);

  else return(1);
}



DrawWindow(W, a1, b1, a2, b2)     
     struct Window *W;
     int a1, a2, b1, b2;
{
  struct clipstruct cstruct;

  cstruct.x1 = MAX(a1, W->x1);
  cstruct.y1 = MAX(b1, W->y1);
  cstruct.x2 = MIN(a2, W->x2);
  cstruct.y2 = MIN(b2, W->y2);

  SendMessage(W, DRAW, &cstruct);
}



ShowBottoms(W, x1, y1, x2, y2)     
     struct Window *W;
     int x1, y1, x2, y2;
{
  if (W->parent == NULL)
    ShowWindow(W, x1, y1, x2, y2);
  else
    {
      ShowBottoms(W->parent, x1, y1, x2, y2);
      ShowWindow(W, x1, y1, x2, y2);
    }
}



DrawMask(W, x1, y1, x2, y2)     
     struct Window *W;
     int x1, y1, x2, y2;
{
  struct List *Temp;
  struct Window *Trace;

   if ((W->parent)->parent) 
     GetMostClipped((W->parent)->parent, &x1, &y1, &x2, &y2);

  DrawWindow(W->parent, x1, y1, x2, y2);

  for (Temp = (W->mask)->Front ; (Temp != W->mask) ; Temp = Temp->Front)
    if (Temp->id != W) ShowWindow(Temp->id, x1, y1, x2, y2);
}



/* loop back through parents until you get to the root, getting the smallest */
/* set of clip coordinates...                                                */
GetMostClipped (parent, x1, y1, x2, y2)
     struct Window *parent;
     int *x1, *y1, *x2, *y2;
{
  struct Window *win = NULL;

  for (win = parent; win != NULL; win = win->parent) {
    if (win->x1 > *x1) *x1 = win->x1;
    if (win->y1 > *y1) *y1 = win->y1;
    if (win->x2 < *x2) *x2 = win->x2;
    if (win->y2 < *y2) *y2 = win->y2;
  }
}


ShowWindow(W, x1, y1, x2, y2)     
     struct Window *W;
     int x1, x2, y1, y2;
{
  struct List *L, *Current;
  struct Window *Win;
  int fx1, fx2, fy1, fy2;

  if (W->parent)
    GetMostClipped(W->parent, &x1, &y1, &x2, &y2);

  DrawWindow(W, x1, y1, x2, y2);

  L = W->port;

    for (Current  = L->Front; Current !=L; Current = Current->Front)
      {
	Win = Current->id;

	fx1 = MAX(Win->x1, x1);
	fx2 = MIN(Win->x2, x2);
	fy1 = MAX(Win->y1, y1);
	fy2 = MIN(Win->y2, y2);
	
	if ((fx1 <= fx2) && (fy1 <= fy2))
	ShowWindow(Win, fx1, fy1, fx2, fy2);
      }
}



ShowTops(W, x1, y1, x2, y2)     
     struct Window *W;
     int x1, x2, y1, y2;
{
  struct List *Temp, *L;
  struct Window *NewTop;


  if (W->parent == NULL) {
    return;
  }

  if ((((W->mask)->Behind)->id) == W) {
    ShowTops(W->parent, x1, y1, x2, y2);
    return;
  }
  for(Temp = (W->mask)->Front; ((Temp->id != W)&&(Temp!=W->mask));Temp = Temp->Front);

  if (Temp == W->mask) printf("ShowTops() - oops there's nothing on top of window '%s'!\n", W->tag);

  if (Temp != W->mask) {
    for (Temp = Temp->Front; (Temp != W->mask) ; Temp = Temp->Front)
      {
	if ((x2 >= (Temp->id)->x1) && (x1 <= (Temp->id)->x2) && (y2 >= (Temp->id)->y1) && (y1 <= (Temp->id)->y2))
	  ShowWindow(Temp->id, x1, y1, x2, y2);
      }
  }
  ShowTops(W->parent, x1, y1, x2, y2);
}



GetPoints(W, x1, y1, x2, y2)     
     struct Window *W;
     int *x1, *y1, *x2, *y2;
{
  struct Window *Trace;

  *x1=0;
  *y1=0;

  Trace = W;
  while(Trace!=NULL)
    {
      *x1 += Trace->relx;
      *y1 += Trace->rely;
      Trace = Trace->parent;
    }

  *x2 = *x1+W->width-1;
  *y2 = *y1+W->height-1;
  return;
}


MoveWindow(W, x, y)     
     struct Window *W;
     int x, y;
{
  int ox1, ox2, oy1, oy2;
  int nx1, nx2, ny1, ny2;
  int sx1, sx2, sy1, sy2;

  CloseWindow(W);
  MoveCoords(W, x, y);
  SendMessage(W,MAKE,NULL);
  TransformCoords(W,W->relx,W->rely,W->width,W->height);
  OpenWindow(W);
}



MoveCoords(W, nx, ny)     
     struct Window *W;
     int nx, ny;
{
  int ox, oy, ow, ol;

  GetPoints(W->parent, &ox, &oy, &ow, &ol);

  if (nx+W->width-1<=ow)  W->relx=nx-ox;
  if (ny+W->height-1<=ol) W->rely=ny-oy;
  AdjustCoords(W);
}



AdjustCoords(W)     
     struct Window *W;
{
  struct List *L, *Current;

  GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
  L = W->port;
  for (Current = L->Front; Current != L; Current = Current->Front)
    AdjustCoords(Current->id);

}



ResizeWin(W, wide, tall)     
     struct Window *W;
     int wide, tall;
{
  CloseWindow(W);
  TransformCoords(W, W->relx, W->rely, wide, tall);
  OpenWindow(W);
}



TransformCoords(W, x, y, wide, tall)     
     struct Window *W;
     int x, y, wide, tall;
{
  struct List *Current, *L, *L2;
  struct Window *tempwin;
  int oldwide, oldtall, oldx, oldy;

  L = W->port;

  oldwide = W->width;
  oldtall = W->height;
  oldx = W->relx;
  oldy = W->rely;

  W->relx = x;
  W->rely = y;
  W->width = wide;
  W->height = tall;

/*
  GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
*/

  W->x1 += (x-oldx);
  W->y1 += (y-oldy);
  W->x2 += (x-oldx)+(wide-oldwide);
  W->y2 += (y-oldy)+(tall-oldtall);


  CopyList(L, &L2);

  for (Current = L2->Front; Current != L2; Current = Current->Front)
    {
      tempwin = Current->id;
      UnstallWin(tempwin);
      SendMessage(tempwin, MAKE, NULL);
      InstallWin(tempwin);
    }

  FreeList(L2);

}


struct Window *			/* returns root of window w.  *DKY-23Sep90* */
RootOfWindow( w)
     struct Window *w;
{
  if( w) {
    while( w->parent != NULL)
      w = w->parent;
    return( w);
  }
  else
    printf( "RootOfWindow: NULL window!\n");
}


/**********************************************************************
 
          StretchWin(W,M)
                 struct Window *W, *M;


		 W is the parent of M

		 W is 'stretched' so that it completely contains M

**********************************************************************/
  
StretchWin(W,M)
     struct Window *W, *M;
{
  int Wx1,Wy1,Wx2,Wy2,Wwd,Wht;
  
  Wx1=W->x1;
  Wx2=W->x2;
  Wy1=W->y1;
  Wy2=W->y2;

  Wx1 = MIN( Wx1, M->x1);
  Wy1 = MIN( Wy1, M->y1);
  Wx2 = MAX( Wx2, M->x2);
  Wy2 = MAX( Wy2, M->y2);
  Wwd = Wx2-Wx1;
  Wht = Wy2-Wy1;
  
  TransformCoords( W, Wx1,Wy1,Wwd,Wht);

  return( 0);
}


Dispatch( W, id, data, loop)     
     struct Window *W;
     int id;
     char *data;
     struct loopstruct *loop;
{
  static struct Window *trap = NULL, *last = NULL;  /* loop->Last replaced with just last  7/6/92 */
  static int trapstat = NULL;
  struct Window *NewWin;
  int buttonstat;
  int button;
  struct trapstruct *t;
  struct pickstruct *p;

  switch(id)
    {

    case DO:

      E_lastRoot = W; /* BS 10/16/91 */
      p = (struct pickstruct *)data;
      button = p->button;
      if( loop->button >0) {
	if( button > 0) buttonstat = BEENDOWN;
	else buttonstat = JUSTUP;
      }
      else {
	if( button <= 0) buttonstat = BEENUP;
	else buttonstat = JUSTDOWN;
      }

      loop->button = button;
      p->button = buttonstat;
      p->bnum = button;

      if( (!trap) || (buttonstat == trapstat)) {
	trap = NULL;
	NewWin = Windowfind( W, p->x, p->y, NULL);

	if( last != NewWin) { 
	  if (last) SendMessage( last, NOECHO, NewWin); /* SendMessage(last, NOECHO, data); */
	  last = NewWin;
	  SendMessage( last, ECHO, NewWin); /* SendMessage(last, ECHO, data); */
	}

	while( SendMessage( NewWin, DO, data)) {
	  if( last != NewWin) {
	    SendMessage( last, NOECHO, NewWin); /* SendMessage(last, NOECHO, data); */
	    last = NewWin;
	    SendMessage( last, ECHO, NewWin); /* SendMessage(last, ECHO, data); */
	  }
	  NewWin = last = Windowfind( W, p->x, p->y, NewWin);
	}
      }
      else
	SendMessage( trap, DO, data);
      loop->trap = trap;
      break;

    case NOECHO:
      SendMessage( last, NOECHO, data);
      last = W;
      break;

    case TRAP:
      t = (struct trapstruct *)data;
      trap = t->window;
      trapstat = t->until;
      break;
    }
}



struct List *
MakeList()     
{
  struct List *L;

  L = (struct List *)malloc(sizeof(struct List));
  L->Front = L->Behind = L;
  L->id = NULL;

  return(L);
}



AddToList(L, id)     
     struct List *L;
     struct Window *id;
{
  struct List *Current, *Temp;

  /*
    for (Current = L->Front; (Current != L); Current = Current->Front)
    if (Current->id == id)
    return(0);
    */

  Temp = (struct List *)(malloc(sizeof(struct List)));
  Temp->Front = L;
  Temp->Behind = L->Behind;
  (L->Behind)->Front = Temp;
  L->Behind = Temp;
  Temp->id = id;

  return(1);
}



GetFromList(L, id)     
     struct List *L;
     struct Window *id;
{
  struct List *Current;

  Current = L;
  while (Current->id != id)
    {
      Current = Current ->Front;
      if (Current == L)
	return(0);
    }

  (Current->Behind)->Front = Current->Front;
  (Current->Front)->Behind = Current->Behind;
  free (Current);
  return(1);
}



CopyList(L1, L2)     
     struct List *L1, **L2;
{
  struct List *Current, *MakeList();

  *L2 = MakeList();
  for(Current = L1->Front; Current != L1; Current = Current->Front)
    AddToList(*L2, Current->id);
}



FreeList(L)     
     struct List *L;
{
  struct List *Temp, *Temp2;

  Temp = L->Front;

  while (Temp != L)
    {
      Temp2 = Temp;
      Temp = Temp->Front;
      free(Temp2);
    }
}



struct List *
AskList(L, id)     
     struct List *L;
     struct Window *id;
{
  struct List *Current;

  for (Current = L->Front; (Current->id !=id)&&(Current != L); Current = Current->Front);

  if (Current == L) Current = NULL;

  return (Current);
}


struct List *
AskListByName(L, name)
     struct List *L;
     char *name;
{
  struct List *Current;

  for (Current = L->Front; (Current != L) && (strcmp(Current->id->tag, name)); Current = Current->Front);

  if (Current == L) Current = NULL;

  return (Current);
}




RemoveWindowFromList( L, W)	/* remove element from list whose id == W *DKY-30Apr91* */
     struct List *L;
     struct Window *W;
{
  struct List *start;

  start = L;

  if( !L) {
    printf( "ERROR: RemoveFromList() -- null list.\n");
    return( -1);
  }
  
  while( L->id != W) {
    L = L->Front;
    if( L == start)
      break;
  }

  /* Remove it if we found it. */
  if( L->id == W) {
    L->Front->Behind = L->Behind;
    L->Behind->Front = L->Front;
    free( L);
    return( 1);
  }
  else
    return( NULL);
}


CloseWindowsInList( L)		/* close all windows in list *DKY-30Apr91* */
     struct List *L;
{
  L = L->Front;
  while( L->id) {
    CloseWindow( L->id);
    L = L->Front;
  }
}


UnstallWindowsInList( L)		/* unstall all windows in list *DKY-11May91* */
     struct List *L;
{
  L = L->Front;
  while( L->id) {
    UnstallWin( L->id);
    L = L->Front;
  }
}


OpenWindowsInList( L)		/* open all windows in list *DKY-30Apr91* */
     struct List *L;
{
  L = L->Front;
  while( L->id) {
    OpenWindow( L->id);
    L = L->Front;
  }
}


struct Window *
FindChildByName( W, childName)	/* *DKY- 2Nov90* */
     struct Window *W;
     char *childName;
{
  struct List *list;
  
  list = (struct List *)AskListByName( W->port, childName);
  if( list)
    return( list->id);
  else
    return( NULL);
}



struct trapstruct *
MakeTrap(W, id)     
     struct Window *W;
     int id;
{
  struct trapstruct *t;
  t = (struct trapstruct *)malloc(sizeof(struct trapstruct));
  t->window = W;
  t->until = id;
  return(t);
}



struct pickstruct *
MakePick()     
{
  struct pickstruct *p;
  p = (struct pickstruct *)malloc(sizeof(struct pickstruct));
  return(p);
}



struct Thing *
MakeThingList(id)     
     char *id;
{
  struct Thing *L;

  L = (struct Thing *)malloc(sizeof(struct Thing));
  L->Front = L->Behind = L;
  L->id = id;
  return(L);
}



AddThing(L, T)     
     struct Thing *L;
     char *T;
{
  struct Thing *Current, *Temp;

  for (Current = L->Front; (Current != L); Current = Current->Front);
  Temp = (struct Thing *)(malloc(sizeof(struct Thing)));
  Temp->Front = L;
  Temp->Behind = L->Behind;
  (L->Behind)->Front = Temp;
  L->Behind = Temp;
  Temp->id = T;

}


RemoveThing(L, T)     
     struct Thing *L;
     char *T;
{
  struct Thing *Current;

  Current = L;
  while (Current->id != T)
    {
      Current = Current ->Front;
      if (Current == L)
	return(0);
    }

  (Current->Behind)->Front = Current->Front;
  (Current->Front)->Behind = Current->Behind;
  free (Current);
  return(1);
}



struct Thing *
AskThing(L, T)     
     struct Thing *L;
     char *T;
{
  struct Thing *Current;

  for (Current = L->Front; (Current->id != T)&&(Current != L); Current = Current->Front);

  if (Current == L) Current = NULL;

  return (Current);
}



DestroyThingList(L)     
     struct Thing *L;
{
  struct Thing *Cur, *Cur2;

  Cur = L->Front;
  while (Cur != L)
    {
      Cur2 = Cur;
      Cur = Cur->Front;
      free(Cur2);
    }

  free(L);
}



CopyThingList(L1, L2)     
     struct Thing *L1, **L2;
{
  struct Thing *Current;

  *L2 = MakeThingList(0);
  for(Current = L1->Front; Current != L1; Current = Current->Front)
    AddThing(*L2, Current->id);
}



char *
CopyString(string1)     
     char *string1;
{
  char *newstring = NULL;

  if (string1) {
    newstring = (char *)malloc((strlen(string1)+1)*sizeof(char));
    strcpy(newstring, string1);
  }
  return(newstring);
}



int
string_length(string)    
     char string[];
{
  char *temp;
  int num = 0;

  temp = string;
  while (*(temp++)) num++;
  return (num);
}





