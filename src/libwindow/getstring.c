#include <stdio.h>
#include <starbase.c.h>
#include <math.h>
#include <windows.c.h>
#include <structures.h>

#define BRED  140
#define BGREEN 140
#define BBLUE 155

struct Window *Stringer = NULL; /* unstatic'ed by Bob 9/17/91 */
static struct Window *SHeadline, *FunkWin, *Line;    /* Windows */
static int sanswer = 0, alim, s_size, s_bits;                   /* reply stat, character limit */
static char *str, *astring, *s_font;                           /* message, reply */

static int *len, *pos, charnum =0, xoffset =8;
static int fontheight, Mwide;
extern struct Window *CurrentTextWindow;



MakeStringer(W, echo, font, size, bits)     /* v 1.0b */
     struct Window *W;
     struct curstruct *echo;
     char *font;
     int size, bits;
{
  int KeyReader();

  s_font = font;
  s_bits = bits;
  s_size = size;
  set_font(font, size, bits);
  string_rect("M", &Mwide, &fontheight);
  Mwide = string_width("a");
  fontheight += 5;

  if (Stringer)
    printf("note: MakeStringer() -- stringer already created.  not remade.\n");
  else
    {
      str = (char *) malloc(300*sizeof(char)); /* maximum string size */
      len = (int *) malloc(300*sizeof(int));
      pos = (int *) malloc(300*sizeof(int));
      
      Stringer = MakeWindow(W->display, W->input, W, 0, 0, 100, 100, 
			    "Stringer");
      MoverII(Stringer,Stringer,24);
      RoundRectify(Stringer, 80, 87, 101, 0, 0, 0, 0, .01);
      EchoWrap(Stringer, echo,1, 0, 0);


      SHeadline = MakeWindow(W->display, W->input, Stringer, 0, 0, 100, 100, 
			     "Headline");
      StringWin(SHeadline, NULL, 0, 0, font, size, bits, 0, 0, 0, 0);
      EchoWrap(SHeadline, echo, 0, 0, 0);
      Maker(SHeadline, 15, 5, -15, 5+fontheight+4);
      InstallWin(SHeadline);


      FunkWin = MakeWindow(W->display, W->input, Stringer, 0, 0, 100, 100, 
			   "funkwin");
      Rectify(FunkWin, BRED, BGREEN, BBLUE, 2, 0, 0, 0, 0);
      StringWin(FunkWin, NULL, xoffset, 4, font, size, bits, 0, 0, 0, 0);
      EchoWrap(FunkWin, echo, 0, 0, 0);
      AttachCommand(FunkWin, NEWKEY, KeyReader, NULL);
      Maker(FunkWin, 15, 10+fontheight, -15, -5);
      InstallWin(FunkWin);
      
      Line = MakeWindow(W->display, W->input, Stringer, 0, 0, 100, 100,
			"back");
      Rectify(Line, 0, 0, 0, 0, 0, 0, 0, 0);
      EchoWrap(Line, echo, 0, 0, 0);
      Maker(Line, 15+xoffset, 14+fontheight, 15+xoffset+2, -10);
      InstallWin(Line);
    }
}


/* *DKY-27Jul90-03:53* */
struct betterStringerStruct {
  struct Window *base, *sheadline, *funkwin, *line;
};

/*
 * MakeStringerPlus
 * have curve == 0 for non-rounded window.
 * There's a semi-uglyness if you don't use the same font and size for the label and input
 * 
 * MakeStringerPlus( w, echo, "latin", 24, 8, 0,0,0, "latin", 24, 8, 140,140,155, 0,0,0, 0.01, 80,87,101)
 *
 */

struct Window *
MakeStringerPlus(W, echo, labelFont, labelSize, labelBits, 
		 labelR, labelG, labelB,
		 inputFont, inputSize, inputBits, 
		 inputBaseR, inputBaseG, inputBaseB, 
		 inputTextR, inputTextG, inputTextB,
		 curve, baseR, baseG, baseB)     /* v 1.0b */
     struct Window *W;
     struct curstruct *echo;
     char *labelFont, *inputFont;
     int labelSize, labelBits, inputSize, inputBits;
     float curve;
     int baseR, baseG, baseB, labelR, labelG, labelB, inputBaseR, inputBaseG, inputBaseB, inputTextR, inputTextG, inputTextB;
{
  int KeyReader(), StringerPlusDo();
  struct betterStringerStruct *parms;
  int titlefontheight;

  if(Stringer) 
    printf("note: MakeStringerPlus() -- stringer already created, not remade.\n");
  else {

    parms = (struct betterStringerStruct *)malloc(sizeof(struct betterStringerStruct));

    s_font = labelFont;
    s_bits = labelBits;
    s_size = labelSize;
    set_font(labelFont, labelSize, labelBits);
    string_rect("M", &Mwide, &titlefontheight);
    Mwide = string_width("a");
    titlefontheight += 5;


    s_font = inputFont;
    s_bits = inputBits;
    s_size = inputSize;
    set_font(inputFont, inputSize, inputBits);
    string_rect("M", &Mwide, &fontheight);
    Mwide = string_width("a");
    fontheight += 5;

    fontheight = MAX( fontheight, titlefontheight);

    str = (char *) malloc(300*sizeof(char)); /* maximum string size */
    len = (int *) malloc(300*sizeof(int));
    pos = (int *) malloc(300*sizeof(int));

    parms->base = Stringer = MakeWindow(W->display, W->input, W, 0, 0, 100, 100, "Stringer");
    if( curve > 0.0)
      RoundRectify( Stringer, baseR, baseG, baseB, 1, 0, 0, 0, curve);
    else
      Rectify( Stringer, baseR, baseG, baseB, 1, 0,0,0, 0);
    MoverII(Stringer,Stringer,24);
    EchoWrap( Stringer, echo, 0, 0, 0);

    parms->sheadline = SHeadline = MakeWindow( W->display, W->input, Stringer, 0, 0, 100, 100, "Headline");
    StringWin( SHeadline, NULL, 0, 0, labelFont, labelSize, labelBits, labelR, labelG, labelB, 0);
    EchoWrap( SHeadline, echo, 0, 0, 0);
    Maker( SHeadline, 15, 5, -15, 5+fontheight+4);
    InstallWin( SHeadline);

    parms->funkwin = FunkWin = MakeWindow( W->display, W->input, Stringer, 0, 0, 100, 100, "funkwin");
    Rectify( FunkWin, inputBaseR, inputBaseG, inputBaseB, 2, 0, 0, 0, 0);
    StringWin( FunkWin, NULL, xoffset, 4, inputFont, inputSize, inputBits, inputTextR, inputTextG, inputTextB, 0);
    EchoWrap( FunkWin, echo, 0, 0, 0);
    AttachCommand( FunkWin, NEWKEY, KeyReader, NULL);
    Maker( FunkWin, 15, 10+fontheight, -15, -5);
    InstallWin( FunkWin);

    parms->line = Line = MakeWindow( W->display, W->input, Stringer, 0, 0, 100, 100, "back");
    Rectify( Line, 0, 0, 0, 0, 0, 0, 0, 0);
    EchoWrap( Line, echo, 0, 0, 0); /* was FunkWin -- a bug? */
    Maker( Line, 15+xoffset, 14+fontheight, 15+xoffset+2, -10);
    InstallWin( Line);

    /* I'm sure there are other messages you'd like to send, but I'm too lazy to define them.*/
    AttachCommand( Stringer, CHANGE_BASE_COLOR,     StringerPlusDo, parms);
    AttachCommand( Stringer, CHANGE_HEADLINE_COLOR, StringerPlusDo, parms);
    AttachCommand( Stringer, CHANGE_INPUTWIN_BASE_COLOR, StringerPlusDo, parms);
    AttachCommand( Stringer, CHANGE_INPUTWIN_TEXT_COLOR, StringerPlusDo, parms);
  }
  return( Stringer);
}

StringerPlusDo( W, ID, data, stuff)
     struct Window *W;
     int ID;
     char *data, *stuff;
{
  struct betterStringerStruct *parms;

  parms = (struct betterStringerStruct *)stuff;

  switch( ID)
    {
    case ( CHANGE_BASE_COLOR):
      SendMessage( parms->base, NEWCOLOR, data);
      break;

    case ( CHANGE_HEADLINE_COLOR):
      SendMessage( parms->sheadline, CHANGECOLOR, data);
      break;
      
    case ( CHANGE_INPUTWIN_BASE_COLOR):
      SendMessage( parms->funkwin, NEWCOLOR, data);
      break;

    case ( CHANGE_INPUTWIN_TEXT_COLOR):
      SendMessage( parms->funkwin, CHANGECOLOR, data);
      break;

    default:
      fprintf( stderr, "StringerPlusDo: Unknown message--> %d\n", ID);
    }
  return( 0);
}

/**********************************************************************

  GetString(Root,x,y,string,string2,lim)


          Root       the root window of your program

	  x,y,       coordinates on the Root

	  string     the title on the dialog box

	  string2    string where the answer will be placed

	  lim        the number of characters that can be entered
	  

**********************************************************************/
  

GetString(Base, x, y, string, string2, lim)      /* v 1.0b */
     struct Window *Base;
     int x, y, lim;
     char *string;
     char *string2;
{
  struct OutDev *display;
  int height, width, x1, y1, width2, height2;
  struct stringstruct *parms;
  struct Command *C;
  struct Window *CT;

  display = Base->display;
  Stringer->parent = Base;

  set_font(s_font, s_size, s_bits);

  astring = string2;
  SendMessage(FunkWin,CHANGESTRING,NULL);
  InstallWin(Line);

  alim = lim;
  width = string_width(string);
  width += 20;

  width2 = Mwide*lim+20;

  width = MAX(100, MAX(width, width2));
  height = fontheight*2+25;

  C = (struct Command *) GetCommand(SHeadline, DRAW);
  parms = (struct stringstruct *) *(C->arguments);
  parms->string = string;

  if (x+width > display->viswidth) x1 = display->viswidth-width;
  else x1 = x;
  if (y+height > display->visheight) y1 = display->visheight-height;
  else y1 = y;

  if (x1 < 0) {
    x1 = 0;
    width = display->viswidth;
  }

  Stringer->display = display;
  ChangeDisplay(Stringer);
  TransformCoords(Stringer, x1, y1, width, height);
  str[0] = 0;
  pos[0] = 0;
  len[0] = 0;
  charnum = 0;
  CT = CurrentTextWindow;
  CurrentTextWindow = FunkWin;

  Query(Stringer);

  CurrentTextWindow = CT;
  return(sanswer);
}



/* getstring2 leaves the given answer string in the box */
GetString2(Base, x, y, string, string2, lim)      /* v 1.0b */
     struct Window *Base;
     int x, y, lim;
     char *string;
     char *string2;
{
  struct OutDev *display;
  char Char[2];
  int height, width, x1, y1, width2, height2,n,tab;
  struct stringstruct *parms;
  struct Command *C;
  struct Window *CT;

  display = Base->display;
  Stringer->parent = Base;

  set_font(s_font, s_size, s_bits);

  astring = string2;
  SendMessage(FunkWin,CHANGESTRING,astring);
  alim = lim;
  width = string_width(string);
  width += 20;

  width2 = Mwide*lim+20;

  width = MAX(100, MAX(width, width2));
  height = fontheight*2+25;

  C = (struct Command *) GetCommand(SHeadline, DRAW);
  parms = (struct stringstruct *) *(C->arguments);
  parms->string = string;

  if (x+width > display->viswidth) x1 = display->viswidth-width;
  else x1 = x;
  if (y+height > display->visheight) y1 = display->visheight-height;
  else y1 = y;

  if (x1 < 0) {
    x1 = 0;
    width = display->viswidth;
  }

  Stringer->display = display;
  ChangeDisplay(Stringer);
  TransformCoords(Stringer, x1, y1, width, height);

  str[0] = 0;
  pos[0] = 0;
  len[0] = 0;
  charnum = 0;

  Char[1] = 0;
  strcpy(str,astring);
  for (n = 0; n < strlen(str); n++) {
    Char[0] = str[n];
    len[charnum] = string_width(Char);
    charnum++;
    pos[charnum] = pos[charnum-1]+len[charnum-1];
  }
  TransformCoords(Line,xoffset+15+pos[charnum],14+fontheight,Line->width,Line->height);
UnstallWin(Line);

  CT = CurrentTextWindow;
  CurrentTextWindow = FunkWin;

  Query(Stringer);

  CurrentTextWindow = CT;
  return(sanswer);
}



KeyReader(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct pickstruct *pick;
  char c, C[2];
  int color[3];
  float lo = 0.0;

  interior_style(W->display->fildes,INT_SOLID,FALSE);
  if (W->display->bits&STARBUG) lo = 1.0;
  SendMessage( W, GETCOLOR, color); /* *DKY-27Jul90* */
  
  C[1] = 0;               /* character will go in C[0] */
  pick = (struct pickstruct *)data;
  c = pick->character;
  EchoOff(W->display);
  switch (c)
    {
    case '\b':   /* backspace */
      if (charnum)
	{
	  int tab, dif, ytab;

	  tab  = dif = pos[charnum] + W->x1+xoffset;
	  ytab = W->y1+3;

	  charnum--;
	  str[charnum] = 0;
	  tab -= len[charnum];

/*	  fill_color(W->display->fildes, BRED/255.0, BGREEN/255.0, BBLUE/225.0); *DKY-27Jul90* */
	  fill_color(W->display->fildes, color[0]/255.0, color[1]/255.0, color[2]/225.0); /* *DKY-27Jul90* */
	  rectangle(W->display->fildes, (float)tab-lo, (float)(W->y1+4)-lo,
		    (float)(tab+2+len[charnum]), (float)(W->y2-5));

	  dif = pos[charnum];
	  fill_color(W->display->fildes, 0.0, 0.0, 0.0);
	  rectangle(W->display->fildes, (float)(W->x1+xoffset+dif)-lo, (float)(W->y1+4)-lo,
		    (float)(W->x1+xoffset+dif+2), (float)(W->y2-5));
	  make_picture_current(W->display->fildes);
	}

       break;

    case (13):   /* Return */
    case '\n':
      sanswer = 1;
      EchoOff(W->display, 1);
      if (RestoreBackground())
	CloseWindow(W->parent);
      else UnstallWin(W->parent);
      if (!charnum) str[0] = 0;
      strcpy(astring, str);
      break;

    default:
       if (c >= 32)
	 {
	   int tab, dif, ytab;
	   
	   /** I added the following four lines.  I'm not sure why they were not there - dave small 8/90 **/
	   set_current_font(s_font, s_size);
	   set_monitor(W->display->bits, W->display->fildes);
	   set_font_color(0,0,0,0);
	   set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);

	   interior_style(W->display->fildes, INT_SOLID, FALSE);
	   if ((charnum < alim)&&(pos[charnum]< W->width-xoffset*2-15))
	     {
	       tab  = dif = pos[charnum] + W->x1+xoffset;
	       ytab = W->y1+4;

	       str[charnum] = c;
	       str[charnum+1] = 0;

	       /*  fill_color(W->display->fildes, BRED/255.0, BGREEN/255.0, BBLUE/225.0); *DKY-27Jul90* */
	       fill_color(W->display->fildes, color[0]/255.0, color[1]/255.0, color[2]/225.0); /* *DKY-27Jul90* */
	       rectangle(W->display->fildes, (float)tab-lo, (float)(W->y1+4)-lo, (float)(tab+2), (float)(W->y2-5));
	       make_picture_current(W->display->fildes);

               C[0] = c;                   /* super-kluge way of getting character width */
	       display_string(C, tab, ytab);
               tab = string_width(C);

	       len[charnum] = tab;
	       charnum++;
	       dif = pos[charnum] = pos[charnum-1]+tab;

	       fill_color(W->display->fildes, 0.0, 0.0, 0.0);
	       rectangle(W->display->fildes, (float)(W->x1+xoffset+dif), (float)(W->y1+4),
			 (float)(W->x1+xoffset+dif+2), (float)(W->y2-5));
	       make_picture_current(W->display->fildes);
	     }
	 }
       break;
     }

   EchoOn(pick->x, pick->y, W->display);
return (0);
}



 
