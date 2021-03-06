#include <stdio.h>
#include <starbase.c.h>
#include <math.h>
#include <windows.c.h>
#include <structures.h>
#include <varargs.h>		/* included for MFunctionCaller() */


struct Window *YesNo = NULL,*Yes,*No,*Headline,*Yback,*Nback;
struct Window *ThreeChoice,*C1,*C2,*C3,*THeadline,*B1,*B2,*B3;
struct Window *NChoice,*NHeadline,*N1;
char *nstrings[10]; /* nmax = 10 */
int answer = 0, nums = 1;

MakeYesNo(W,echo)
     struct Window *W;
     struct curstruct *echo;
{
  int ClickYesNo();
  if( YesNo)			/* *DKY-21Feb91* */
    return( 0);

  YesNo = MakeWindow(W->display,W->input,W,0,0,100,100,"yesno");
  RoundRectify(YesNo,120,120,110,0,0,0,0,.03);
  MoverII(YesNo,YesNo,0);
  EchoWrap(YesNo,echo,1,0,0);

  Headline = MakeWindow(W->display,W->input,YesNo,0,0,100,100,"Headline");
  StringWin(Headline,NULL,0,0,"latin",16,8,0,0,0,0);
  MoverII(Headline,YesNo,0);
  EchoWrap(Headline,echo,1,0,0);
  Maker(Headline,7,2,-5,2+16);
  InstallWin(Headline);

  Yback = MakeWindow(W->display,W->input,YesNo,0,0,100,100,"Yback");
  Rectify(Yback,170,170,170,1,0,0,0,0);
  StringWin(Yback,"YES",CENTERED,0,"latin",16,8,0,0,0,0);
  FunctionCaller(Yback,DO,ClickYesNo,1,JUSTUP);
  EchoWrap(Yback,echo,JUSTUP,0,0);
  PerMaker(Yback,.05,.5,.47,.9);
  InstallWin(Yback);

  Nback = MakeWindow(W->display,W->input,YesNo,0,0,100,100,"Nback");
  Rectify(Nback,170,170,170,1,0,0,0,0);
  StringWin(Nback,"NO",CENTERED,0,"latin",16,8,0,0,0,0);
  FunctionCaller(Nback,DO,ClickYesNo,0,JUSTUP);
  EchoWrap(Nback,echo,JUSTUP,0,0);
  PerMaker(Nback,.5,.5,.95,.9);
  InstallWin(Nback);
  printf( "\n");
}


ClickYesNo(a)
{
  answer = a;
  CloseWindow(YesNo);
  return(0);
}


AskYesNo(Root,x,y,string)
     struct Window *Root;
     int x,y;
     char *string;
{
  struct OutDev *display;
  int height, width,x1,y1;
  struct regstruct *rstruct;
  struct stringstruct *parms;
  struct makestruct *m;

  display = Root->display;
  YesNo->parent = Root;

  parms = (struct stringstruct *) GetStuff(Headline,DRAW);
  set_font(parms->font,parms->size,parms->bits);
/*  set_font("latin",24,8); */   /* Bob 9/17/91 */


  string_rect(string,&height,&width);
  width += 16; 
  height *= 2;
  height += 8;
  if (width<100) width = 100;

  parms = (struct stringstruct *)GetStuff(Headline,DRAW);
  parms->string = string;
  m = (struct makestruct *)GetStuff(THeadline,MAKE);
  m->y2 = height/2;

  if (x+width > display->viswidth) x1 = display->viswidth-width;
  else x1 = x;
  if (y+height > display->visheight) y1 = display->visheight-height;
  else y1 = y;

  YesNo->display = display;
  ChangeDisplay(YesNo);
  TransformCoords(YesNo,x1,y1,width,height);

  Query(YesNo);

  return(answer);
}




/* This constructs a window of three choices */


MakeThreeChoice(W,echo)
     struct Window *W;
     struct curstruct *echo;
{
  int ClickThree();

  ThreeChoice = MakeWindow(W->display,W->input,W,0,0,100,100,"ThreeChoice");
  RoundRectify(ThreeChoice,120,120,110,0,0,0,0,.03);
  MoverII(ThreeChoice,ThreeChoice,0);
  EchoWrap(ThreeChoice,echo,1,0,0);

  THeadline = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"Headline");
  StringWin(THeadline,NULL,0,0,"latin",16,8,0,0,0,0);
  MoverII(THeadline,ThreeChoice,0);
  EchoWrap(THeadline,echo,1,0,0);
  Maker(THeadline,7,2,-5,18);
  InstallWin(THeadline);

  B1 = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"B1");
  Rectify(B1,170,170,170,1,0,0,0,0);
  StringWin(B1,"YES",CENTERED,0,"latin",16,8,0,0,0,0);
  FunctionCaller(B1,DO,ClickThree,1,JUSTUP);
  EchoWrap(B1,echo,JUSTUP,0,0);
  Maker(B1,0,18,10,-6);
  InstallWin(B1);

  B2 = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"B2");
  Rectify(B2,170,170,170,1,0,0,0,0);
  StringWin(B2,"YES",CENTERED,0,"latin",16,8,0,0,0,0);
  FunctionCaller(B2,DO,ClickThree,2,JUSTUP);
  EchoWrap(B2,echo,JUSTUP,0,0);
  Maker(B2,0,18,10,-6);
  InstallWin(B2);

  B3 = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"B3");
  Rectify(B3,170,170,170,1,0,0,0,0);
  StringWin(B3,"YES",CENTERED,0,"latin",16,8,0,0,0,0);
  FunctionCaller(B3,DO,ClickThree,3,JUSTUP);
  EchoWrap(B3,echo,JUSTUP,0,0);
  Maker(B3,0,18,10,-6);
  InstallWin(B3);
}



AskThreeChoice(Root,x,y,string,string1,string2,string3)
     struct Window *Root;
     int x,y;
     char *string,*string1,*string2,*string3;
{
  struct OutDev *display;
  int height, width,x1,y1,twidth,p1,p2,w1,w2,w3,fw;
  struct stringstruct *parms;
  struct makestruct *m;
  struct Command *C;

  display = Root->display;
  ThreeChoice->parent = Root;

  parms = (struct stringstruct *) GetStuff(B1,DRAW);
  set_font(parms->font,parms->size,parms->bits);
/*  set_font("latin",16,8); */

  w1 = string_width(string1);
  w2 = string_width(string2);
  w3 = string_width(string3);
  w1 += 24;
  w2 += 24;
  w3 += 24;
  twidth = w1+w2+w3+10+18;

  string_rect(string,&height,&width);
  width += 10;
  width = MAX(width,twidth);

  if (width<100) width = 100;
  height *= 2;
  height += 18;

/*  height = 38; */

  parms = (struct stringstruct *)GetStuff(THeadline,DRAW);
  parms->string = string;
  C = GetCommand(B1,DRAW);
  parms = (struct stringstruct *)(*(C->arguments+1));
  parms->string = string1;
  C = GetCommand(B2,DRAW);
  parms = (struct stringstruct *)*(C->arguments+1);
  parms->string = string2;
  C = GetCommand(B3,DRAW);
  parms = (struct stringstruct *)*(C->arguments+1);
  parms->string = string3;


  p1 = 8+w1+5;
  if (width > twidth) p1 += (width-twidth)/2;
  p2 = p1+w2+5;
  if (width > twidth) p2 += (width-twidth)/2;

  m = (struct makestruct *)GetStuff(THeadline,MAKE);
  m->y2 = height/2;
  m = (struct makestruct *)GetStuff(B1,MAKE);
  m->x1 = 8;
  m->x2 = p1-5;
  m->y1 = height/2;
  m = (struct makestruct *)GetStuff(B2,MAKE);
  m->x1 = p1;
  m->x2 = p2-5;
  m->y1 = height/2;
  m = (struct makestruct *)GetStuff(B3,MAKE);
  m->x1 = p2;
  m->x2 = p2+w3;
  m->y1 = height/2;

  if (x+width > display->viswidth) x1 = display->viswidth-width;
  else x1 = x;
  if (y+height > display->visheight) y1 = display->visheight-height;
  else y1 = y;

  ThreeChoice->display = display;
  ChangeDisplay(ThreeChoice);
  TransformCoords(ThreeChoice,x1,y1,width,height);

  Query(ThreeChoice);

  return(answer);
}


ClickThree(a)
{
  answer = a;
  CloseWindow(ThreeChoice);
  return(0);
}






/* This constructs a window of n choices */


MakeNChoice(W,echo,r,g,b)
     struct Window *W;
     struct curstruct *echo;
{
  int ClickN();
  NChoice = MakeWindow(W->display,W->input,W,0,0,100,100,"NChoice");
  RoundRectify(NChoice,r,g,b,0,0,0,0,.03);
  MoverII(NChoice,NChoice,0);
  EchoWrap(NChoice,echo,1,0,0);

  NHeadline = MakeWindow(W->display,W->input,NChoice,0,0,100,100,"Headline");
  StringWin(NHeadline,NULL,0,0,"latin",16,8,0,0,0,0);
  MoverII(NHeadline,NChoice,0);
  EchoWrap(NHeadline,echo,1,0,0);
  Maker(NHeadline,7,2,-5,18);
  InstallWin(NHeadline);

  N1 = MakeWindow(W->display,W->input,NChoice,0,0,100,100,"B1");
  AttachCommand(N1,DO,ClickN,NULL);
  AttachCommand(N1,DRAW,ClickN,NULL);
  EchoWrap(N1,echo,JUSTUP,0,0);
  Maker(N1,8,18,-8,-8);
  InstallWin(N1);
}



AskNChoice(Root,x,y,string,num, va_alist)
     struct Window *Root;
     int x,y,num;
     char *string;
{
  va_list ap;
  struct OutDev *display;
  int height, width,x1,y1,twidth,p1,p2,w1,w2,w3,fw;
  char* arg;
  int argno = 0;
  struct stringstruct *parms;
  struct makestruct *m;

  display = Root->display;
  NChoice->parent = Root;

  nums = num;
  parms = (struct stringstruct *) GetStuff(NHeadline,DRAW);
  set_font(parms->font,parms->size,parms->bits);

  if( num > 10) {
    printf( "ERROR: AskNChoice()\n");
    return( 0);
  }
  
  va_start( ap);

  w1 = 18;
  while( argno < num) {
    arg = va_arg( ap, char *);
    w1 += string_width(arg)+15;
    nstrings[argno] = arg;
    argno += 1;
  }
  va_end( ap);

  parms = (struct stringstruct *)GetStuff(NHeadline,DRAW);
  parms->string = string;

  string_rect(string,&height,&width);
  width += 18;
  width = MAX(width,w1);

  if (width<100) width = 100;
  height *= 2;
  height += 18;

  m = (struct makestruct *)GetStuff(NHeadline,MAKE);
  m->y2 = height/2;
  m = (struct makestruct *)GetStuff(N1,MAKE);
  m->y1 = height/2;

  if (x+width > display->viswidth) x1 = display->viswidth-width;
  else x1 = x;
  if (y+height > display->visheight) y1 = display->visheight-height;
  else y1 = y;

  NChoice->display = display;
  ChangeDisplay(NChoice);
  TransformCoords(NChoice,x1,y1,width,height);

  Query(NChoice);

  return(answer);
}


ClickN(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
  struct pickstruct *p;
  struct clipstruct *cstruct;
  int x1,y1,wide,tall,n,screen,w1,extra;
  struct stringstruct *parms;
  parms = (struct stringstruct *) GetStuff(NHeadline,DRAW);
  set_font(parms->font,parms->size,parms->bits);

  switch(id) {
  case DRAW:
    screen = W->display->fildes;
    fill_color(screen,FCON(170),FCON(170),FCON(170));
    perimeter_color(screen,0.0,0.0,0.0);
    interior_style(screen,INT_SOLID,TRUE);
    cstruct = (struct clipstruct *)data;

    set_font(parms->font,parms->size,parms->bits);
    set_monitor(W->display->bits,screen); 
    set_font_color(0,0,0,0);
    set_text_clip_rectangle(cstruct->x1,cstruct->y1,cstruct->x2,cstruct->y2);

    w1 = 0;
    for (n = 0; n < nums; n++)
	w1 += string_width(nstrings[n])+15;
    if (w1 < W->width) extra = (W->width-w1)/n;
    else extra = 0;

    x1 = W->x1;
    for (n = 0; n < nums; n++)
      {
	wide = string_width(nstrings[n])+10 + extra;
	dcrectangle(screen,x1,W->y1,x1+wide,W->y2);
	x1 += wide+5;
      }

    make_picture_current(screen);
    x1 = W->x1;
    for (n = 0; n < nums; n++)
      {
	wide = string_width(nstrings[n])+10+extra;
	display_string(nstrings[n],x1+5+extra/2,W->y1+3);
	x1 += wide+5;
      }

    break;
  case DO:
    p = (struct pickstruct *)data;
    w1 = 0;
    for (n = 0; n < nums; n++)
	w1 += string_width(nstrings[n])+15;
    if (w1 < W->width) extra = (W->width-w1)/n;
    else extra = 0;

    x1 = W->x1;
    for (n = 0; n < nums; n++)
      {
	wide = string_width(nstrings[n])+10+extra;
	if ((p->x >= x1)&&(p->x <= x1+wide)) {
	  answer = n+1;
	  CloseWindow(NChoice);
	}
	x1 += wide+5;
      }
    break;
  }
  return(0);
}

