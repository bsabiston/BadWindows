#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

#define MOVEBOX -101
/*
  #define BRED 30
  #define BGREEN 30
  #define BBLUE 25
*/
int BRED = 30;
int BGREEN = 30;
int BBLUE = 25;

#define ZOOM 1
#define LINES 2
#define GRID 3
#define PUPDATE 4
#define ZOOM_FACTOR 5
#define PRINT_RGB 6
#define ENTER_RGB 7
#define PRINT_HSV 8

float HueSMax = 108.8, HueMax = 99.0, HueMin = 1.0, HueGap = 9.8;   /* 108.8 = 99.0 + 9.8  */
float SatSMax = 16.5, SatMax = 15.0, SatMin = 0.0, SatGap = 1.2;    /* 16.5  = 15.0 + 1.5  */  
float ValSMax = 9.8, ValMax = 9.0, ValMin = 1.0, ValGap = .8;      /* 9.8   = 9.0  +  .8  */

struct munstruct {
 struct Window *C,*W1,*W2,*S1,*S2;
 int slice;
 float x1,y1,x2,y2,value;
};

static float hmax,smax,vmax,hsmax,hmin,hgap,ssmax,smin,sgap,vsmax,vmin,vgap;
static int gridsize = 8,linestat = 1,updatestat = 0, zoomstat = 0;
static float zoom_factor= 1.8;
static struct Window *menu, *zoom, *size,*lines,*update,*zf,*rgb,*rgbe,*hsv;
static struct Window *Palette, *Current, *resizer, *button;
static struct Window *H,*S,*V,*panel,*sliderpanel,*Hs,*Ss,*Vs;

struct Window *MakeMunsellPalette(Root,echo,x,y)
struct Window *Root;
struct curstruct *echo;
int x,y;
{
  struct Window *MakeMunsellPalette2();
  return(MakeMunsellPalette2(Root,echo,x,y,376,150)); /* changed 375 to 376 so sliders would look right *DKY-21Jan91* */
}

char *MunsellPaletteMenuFont = "latin";	/* *DKY-31Oct90* */
int MunsellPaletteMenuFontSize = 16;

struct Window *MakeMunsellPalette2(Root,echo,x,y,ww,hh)
struct Window *Root;
struct curstruct *echo;
int x,y,ww,hh;
{
  struct OutDev *display;
  struct InDev *locator;
  struct curstruct *icon,*ricon;
  int MunsellSliderMaker(),UpdateWin();
  int Palette_Options(),PalSwitch(),DeselectPalette();

  display = Root->display;
  locator = Root->input;

  icon = (struct curstruct *)LoadIcon("icons/dot_icon",8,82);
  ricon = (struct curstruct *)LoadIcon("icons/resize_icon",8,82);
  munrgb(CurrentHue,CurrentSat,CurrentVal,&CurrentRed,&CurrentGreen,&CurrentBlue); /* set initial rgb */
  Palette = MakeWindow(display,locator,Root,x,y,ww,hh,"Palette");
  MoverII(Palette, Palette,24);
  EchoWrap(Palette,echo,1,0,0);
  RoundRectify(Palette,BRED,BGREEN,BBLUE,2,0,0,0,.015);
  AttachCommand(Palette,DESELECT,DeselectPalette,NULL);

  panel = MakeWindow(display,locator,Palette,10,10,50,50,"colors");
  H = MakeWindow(display,locator,panel,10,10,50,50,"HWin");
  S = MakeWindow(display,locator,panel,0,0,20,20,"SWin");
  V = MakeWindow(display,locator,panel,0,0,20,20,"VWin");
  sliderpanel = MakeWindow(display,locator,Palette,10,10,50,50,"sliders");
  Hs = MakeWindow(display,locator,sliderpanel,10,10,50,50,"Hslider");
  Ss = MakeWindow(display,locator,sliderpanel,0,0,20,20,"Sslider");
  Vs = MakeWindow(display,locator,sliderpanel,0,0,20,20,"Vslider");

  button = MakeWindow(display,locator,Palette,0,0,20,20,"grid");
  Current = MakeWindow(display,locator,Palette,0,0,20,20,"CurrentColor");
  resizer = MakeWindow(display,locator,Palette,0,0,20,20,"resizer");


  /* panel */
  MoverII(panel,Palette,24);
  EchoWrap(panel,echo,1,0,0);
  Rectify(panel,BRED,BGREEN,BBLUE,0,BRED,BGREEN,BBLUE,0);
  Maker(panel,5,5,-7-icon->dx-5,-7-icon->dy-5);
  InstallWin(panel);

  /* color panels */
  Munsell_Win(H,echo,0,Current,S,V,Ss,Vs);
  InstallWin(H);
  Munsell_Win(S,echo,1,Current,H,V,Hs,Vs);
  InstallWin(S);
  Munsell_Win(V,echo,2,Current,H,S,Hs,Ss);
  InstallWin(V);
 
  /* slider panel */;
  MoverII(sliderpanel,Palette,24);
  EchoWrap(sliderpanel,echo,1,0,0);
  DoubleMaker(sliderpanel, 5,-5-icon->dy+1,-7-icon->dx-5,-5,  -7-icon->dx+1,5,-7,-7-icon->dy-5);
  InstallWin(sliderpanel);

  /* color sliders */
  AreaSlider(Hs,0,50,50,45,1,0,0,0,100,100,110,1,&CurrentHue,&HueSMax,&HueMin,&HueGap);
  Messenger(Hs,DO,H,NEWCOLOR,NULL,2);
  Messenger(Hs,DO,V,MOVEBOX,NULL,7);
  Messenger(Hs,DO,S,MOVEBOX,NULL,7);
  FunctionCaller(Hs,DO,UpdateWin,Current,7);
  EchoWrap(Hs,echo,7,0,0);
  AttachCommand(Hs,MAKE,MunsellSliderMaker,0);
  InstallWin(Hs);

  AreaSlider(Ss,0,50,50,45,1,0,0,0,100,100,110,1,&CurrentSat,&SatSMax,&SatMin,&SatGap);
  Messenger(Ss,DO,S,NEWCOLOR,NULL,2);
  Messenger(Ss,DO,V,MOVEBOX,NULL,7);
  Messenger(Ss,DO,H,MOVEBOX,NULL,7);
  FunctionCaller(Ss,DO,UpdateWin,Current,7);
  EchoWrap(Ss,echo,7,0,0);
  AttachCommand(Ss,MAKE,MunsellSliderMaker,1);
  InstallWin(Ss);

  AreaSlider(Vs,0,50,50,45,1,0,0,0,100,100,110,1,&CurrentVal,&ValSMax,&ValMin,&ValGap);
  Messenger(Vs,DO,V,NEWCOLOR,NULL,2);
  Messenger(Vs,DO,H,MOVEBOX,NULL,7);
  Messenger(Vs,DO,S,MOVEBOX,NULL,7);
  FunctionCaller(Vs,DO,UpdateWin,Current,7);
  EchoWrap(Vs,echo,7,0,0);
  AttachCommand(Vs,MAKE,MunsellSliderMaker,2);
  InstallWin(Vs);



  /* button */

  menu =  (struct Window *)MakePopUp(Root,echo,15,MunsellPaletteMenuFont,MunsellPaletteMenuFontSize,8,0,0,0,0,150,150,160);
  zoom = (struct Window *)AddPopUpLine(menu,"Zoom in on current color",Palette_Options,ZOOM);
  zf = (struct Window *)AddPopUpLine(menu,"Change zoom magnification",Palette_Options,ZOOM_FACTOR);
  size = (struct Window *)AddPopUpLine(menu,"Change grid resolution",Palette_Options,GRID);
  lines = (struct Window *)AddPopUpLine(menu,"Hide grid lines",Palette_Options,LINES);
  update = (struct Window *)AddPopUpLine(menu,"Continuous panel update",Palette_Options,PUPDATE);
  rgb = (struct Window *)AddPopUpLine(menu,"Print RGB value",Palette_Options,PRINT_RGB);
  hsv = (struct Window *)AddPopUpLine(menu,"Print HSV value",Palette_Options,PRINT_HSV);
  rgbe = (struct Window *)AddPopUpLine(menu,"Enter RGB value",Palette_Options,ENTER_RGB);

  MakePopUpTriggerNoEor(button,echo,menu,0,-4);
  EchoWrap(button,echo,JUSTDOWN|BEENDOWN,0,0);
  AttachIcon(button,icon);
  DoubleMaker(button,-7-icon->dx+1,5,-7,5+icon->dy-1   ,5,-5-icon->dy+1,5+icon->dx-1,-5);
  InstallWin(button);

  /* current */
  MoverII(Current,Palette,24);
  EchoWrap(Current,echo,1,0,0);
  RemoteRectify(Current,&CurrentRed,&CurrentGreen,&CurrentBlue,1,0,0,0,1);
  DoubleMaker(Current,-7-icon->dx+1,5+icon->dy+3,-7,-7-icon->dy-3,    5+icon->dx+3,-7-icon->dy+1,-7-icon->dx-3,-7);
  InstallWin(Current);

  /* resizer */
  ResizerPlus(resizer,Palette,120,120,3000,3000);
  EchoWrap(resizer,echo,7,0,0);
  AttachIcon(resizer,ricon);
  DoubleMaker(resizer,-5-icon->dx+1,-5-icon->dy+1,-5,-5,  -5-icon->dx+1,-5-icon->dy+1,-5,-5);
  InstallWin(resizer);

  UpdateSizes(Palette);
  return(Palette);
}


ChangeMunsellGridSize(W)
struct Window *W;
{
return(0);
}



Munsell_Win(W,echo,slice,C,W1,W2,S1,S2)
struct Window *W;
struct curstruct *echo;
int slice;
struct Window *W1,*W2,*C,*S1,*S2;
{
  int Munsell();
  struct munstruct *parms;

  parms = (struct munstruct *)malloc(sizeof(struct munstruct));
  parms->slice = slice;
  parms->C = C;
  parms->W1 = W1;
  parms->W2 = W2;
  parms->S1 = S1;
  parms->S2 = S2;

  AttachCommand(W,DO,Munsell,parms);
  EchoWrap(W,echo,7,0,0);
  AttachCommand(W,DRAW,Munsell,parms);
  AttachCommand(W,NEWCOLOR,Munsell,parms);
  AttachCommand(W,MOVEBOX,Munsell,parms);
  AttachCommand(W,MAKE,Munsell,parms);
  AttachCommand(W,DESELECT,Munsell,parms);
}




/*******************************/
/**** Munsell functions   ******/
/*******************************/

Munsell(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
int vert,x1,y1,x2,y2,cx1,cy1,cx2,cy2;
struct munstruct *parms;
float d,gap,hue,sat,val,h,s,v;
struct clipstruct *cstruct;
gescape_arg arg1,arg2;
int wide,tall,x,y,screen,slice,size,stat,r,g,b,value;
struct pickstruct *pick;
static int new = 0;
struct trapstruct T;
unsigned char *buffer,*control;
int *ibuffer, startx, starty;

parms = (struct munstruct *)stuff;
screen = (W->display)->fildes;
slice = parms->slice;
hue = CurrentHue;
sat = CurrentSat;
val = CurrentVal;
size = gridsize;
wide = W->width/gridsize;
tall = W->height/gridsize;


if (id == NEWCOLOR)
  {
  if (slice == 0){
    if (parms->value == hue) id = MOVEBOX;
    else parms->value = hue;}
  if (slice == 1){
    if (parms->value == sat) id = MOVEBOX;
    else parms->value = sat;}
  if (slice == 2){
    if (parms->value == val) id = MOVEBOX;
    else parms->value = val;}
  }

if ((id == NEWCOLOR)||(id == MOVEBOX))  {
  munrgb(hue,sat,val,&CurrentRed,&CurrentGreen,&CurrentBlue);
  if (id == NEWCOLOR)
    if (set_new_color) (*set_new_color)();
}

if ((id == DRAW)||(id == NEWCOLOR))
  {
      startx = W->x1;  starty =  W->y1;     /* 1280, 0 for offscreen action */

      fill_color(screen,BRED/255.0,BGREEN/255.0,BBLUE/255.0);
      drawing_mode(W->display->fildes,3);
      interior_style(screen,INT_SOLID,FALSE);
      rectangle(screen,(float)(startx),(float)(starty),(float)(startx+wide-1),(float)(starty+tall-1));
      perimeter_color(screen,0.0,0.0,0.0);
      interior_style(screen,INT_SOLID,TRUE);
      make_picture_current(screen);

      lockdev(screen);
      
      buffer = W->display->buffer+startx+starty*2048;
      ibuffer = (int *)W->display->buffer+startx+starty*2048;
      control = W->display->control;
      control[0x40bf] = 7;

      for (y = 0; y< tall; y++)
	{
	for (x = 0; x<wide; x++)
	  {
	    if (slice == 0) stat = munrgb(hue,
					      (SatMax-SatMin)*(float)x/(wide-1)+SatMin,
					      (ValMax-ValMin)*(float)y/(tall-1)+ValMin,&r,&g,&b);
	    else if (slice == 1) stat = munrgb((HueMax-HueMin)*(float)y/(tall-1)+HueMin,
						   sat,
						   (ValMax-ValMin)*(float)x/(wide-1)+ValMin,&r,&g,&b);
	    else if (slice == 2) stat = munrgb((HueMax-HueMin)*(float)y/(tall-1)+HueMin,
						   (SatMax-SatMin)*(float)x/(wide-1)+SatMin,
						   val,&r,&g,&b);

	    if (stat) {
	      if ((W->display->bits == SRX)||(W->display->bits == CRX))
		  *ibuffer = (r <<16)|(g<<8)|b;
	      else {
		control[0x40bf] = 4;
		*buffer = r;
		control[0x40bf] = 2;
		*buffer = g;
		control[0x40bf] = 1;
		*buffer = b;
		control[0x40bf] = 7;
	        }
	      }
	    else  {
	      if ((W->display->bits == SRX)||(W->display->bits == CRX))
		  *ibuffer = (BRED <<16)|(BGREEN<<8)|BBLUE;
	      else {
		control[0x40bf] = 4;
		*buffer = BRED;
		control[0x40bf] = 2;
		*buffer = BGREEN;
		control[0x40bf] = 1;
		*buffer = BBLUE;
		control[0x40bf] = 7;
	        }
	      }
	    ibuffer++;
	    buffer++;
	  }
	ibuffer += 2048-wide;
	buffer += 2048-wide;
      }

      unlockdev(screen);

  /* REPLACE THESE THREE CALLS WITH ONE, AND NO BANK SWITCH, FOR 24 BIT BLOCK MOVE */
  bank_switch(W->display->fildes,2,0);
  DamagedFastMag(screen,startx,starty,wide,tall,W->x1,W->y1,gridsize,linestat,BRED,BGREEN,BBLUE);
  bank_switch(W->display->fildes,1,0);
  DamagedFastMag(screen,startx,starty,wide,tall,W->x1,W->y1,gridsize,linestat,BRED,BGREEN,BBLUE);
  bank_switch(W->display->fildes,0,0);
  DamagedFastMag(screen,startx,starty,wide,tall,W->x1,W->y1,gridsize,linestat,BRED,BGREEN,BBLUE);


  make_picture_current(screen);
  
  }

   if (id == MOVEBOX)
     {
     drawing_mode(screen,6);
     perimeter_color(screen,1.0,1.0,1.0);
     interior_style(screen,INT_HOLLOW,TRUE);
     if (parms->x1 != -9999)
       rectangle(screen,(float)W->x1+parms->x1,(float)W->y1+parms->y1,(float)W->x1+parms->x2,(float)W->y1+parms->y2);
     drawing_mode(screen,3);
     }

   if (id == DESELECT)
     {
       if (parms->x1 != -9999)   /* turn off the box if it's there */
	 {
	 drawing_mode(screen,6);
	 perimeter_color(screen,1.0,1.0,1.0);
	 interior_style(screen,INT_HOLLOW,TRUE);
	 rectangle(screen,(float)W->x1+parms->x1,(float)W->y1+parms->y1,(float)W->x1+parms->x2,(float)W->y1+parms->y2);
	 drawing_mode(screen,3);
         }
       parms->x1 = -9999;
     }
   
   if ((id == DRAW)||(id == MOVEBOX)||(id == NEWCOLOR))
     {
     if (slice == 0)
       {
	      parms->x1 = size * (int)(((sat-SatMin)/(SatMax-SatMin))*(float)(wide-1) + .5);
	      parms->x2 = parms->x1+size;
	      parms->y1 = size * (int)(((val-ValMin)/(ValMax-ValMin))*(float)(tall-1) + .5);
	      parms->y2 = parms->y1+size;
       }
     else if (slice == 1)
       {
	      parms->x1 = size * (int)(((val-ValMin)/(ValMax-ValMin))*(float)(wide-1) + .5);
	      parms->x2 = parms->x1+size;
	      parms->y1 = size * (int)(((hue-HueMin)/(HueMax-HueMin))*(float)(tall-1) + .5);
	      parms->y2 = parms->y1+size;
       }
     else if (slice == 2)
       {
	      parms->x1 = size * (int)(((sat-SatMin)/(SatMax-SatMin))*(float)(wide-1) + .5);
	      parms->x2 = parms->x1+size;
	      parms->y1 = size * (int)(((hue-HueMin)/(HueMax-HueMin))*(float)(tall-1) + .5);
	      parms->y2 = parms->y1+size;
       }

     drawing_mode(screen,6);
     perimeter_color(screen,1.0,1.0,1.0);
     interior_style(screen,INT_HOLLOW,TRUE);
     rectangle(screen,(float)W->x1+parms->x1,(float)W->y1+parms->y1,(float)W->x1+parms->x2,(float)W->y1+parms->y2);
     drawing_mode(screen,3);
   }

 if ((id == DRAW)||(id == NEWCOLOR)||(id == MOVEBOX)){
    clip_rectangle(screen, 0.0, (float)(W->display->width-1), 0.0, (float)(W->display->height-1));
    make_picture_current(screen);
  }

if (id == DO)
  {
   pick = (struct pickstruct *)data;
   x = (pick->x-W->x1)/gridsize;
   y = (pick->y-W->y1)/gridsize;
 
   if ((x >= 0)&&(y >= 0)&&(x< wide)&&(y<tall)){
     if ((slice == 0)&&(munrgb(hue,(SatMax-SatMin)*(float)x/(wide-1)+SatMin,
				   (ValMax-ValMin)*(float)y/(tall-1)+ValMin,&r,&g,&b)))
       {
	 if ((pick->button == JUSTDOWN)||(new)){
         if (pick->button == JUSTDOWN) T.window = W,T.until = BEENUP, Dispatch(W,TRAP,&T,NULL);
         new = 1;

	 CurrentVal = (ValMax-ValMin)*(float)y/(tall-1)+ValMin;
	 CurrentSat = (SatMax-SatMin)*(float)x/(wide-1)+SatMin;
	 SendMessage(W,MOVEBOX,NULL);
	 UpdateWin(parms->C);
	 UpdateWin(parms->S1);
	 UpdateWin(parms->S2);
	 
	 if (pick->button == JUSTUP) {
           new = 0;
	   SendMessage(parms->W1,NEWCOLOR,NULL);
	   SendMessage(parms->W2,NEWCOLOR,NULL);
           }
         }
	 return(0);
       }
     
     if ((slice == 1)&&(munrgb((HueMax-HueMin)*(float)y/(tall-1)+HueMin,
			            sat,
				   (ValMax-ValMin)*(float)x/(wide-1)+ValMin,&r,&g,&b)))
       {
	 if ((pick->button == JUSTDOWN)||(new)){
         if (pick->button == JUSTDOWN) T.window = W,T.until = BEENUP, Dispatch(W,TRAP,&T,NULL);
         new = 1;

	 CurrentVal = (ValMax-ValMin)*(float)x/(wide-1)+ValMin;
	 CurrentHue = (HueMax-HueMin)*(float)y/(tall-1)+HueMin;
	 SendMessage(W,MOVEBOX,NULL);
	 UpdateWin(parms->C);
	 UpdateWin(parms->S1);
	 UpdateWin(parms->S2);
	 
	 if (pick->button == JUSTUP) {
           new = 0;
	   SendMessage(parms->W1,NEWCOLOR,NULL);
	   SendMessage(parms->W2,NEWCOLOR,NULL);
           }
         }
	 return(0);
       }
     
     if ((slice == 2)&&(munrgb((HueMax-HueMin)*(float)y/(tall-1)+HueMin,
			      (SatMax-SatMin)*(float)x/(wide-1)+SatMin,
			       val,&r,&g,&b)))
       {
	 if ((pick->button == JUSTDOWN)||(new)){
         if (pick->button == JUSTDOWN) T.window = W,T.until = BEENUP, Dispatch(W,TRAP,&T,NULL);
         new = 1;

	 CurrentHue = (HueMax-HueMin)*(float)y/(tall-1)+HueMin;
	 CurrentSat = (SatMax-SatMin)*(float)x/(wide-1)+SatMin;
	 SendMessage(W,MOVEBOX,NULL);
	 UpdateWin(parms->C);
	 UpdateWin(parms->S1);
	 UpdateWin(parms->S2);
	 
	 if (pick->button == JUSTUP) {
           new = 0;
	   SendMessage(parms->W1,NEWCOLOR,NULL);
	   SendMessage(parms->W2,NEWCOLOR,NULL);
           }
         }
	 return(0);
       }

     }
     return(1);
   }

if (id == MAKE)
  {
    vert =  (W->parent->width < W->parent->height);
    if (vert) gap = ((float)W->parent->height-10.0)/3.0;
    else      gap = ((float)W->parent->width-10.0)/3.0;

    if (slice == 0)
      {
	x1 = 0;
	y1 = 0;
	if (vert) 
	  {
	    x2 = (W->parent->width-1);
	    y2 = gap;
	  }
	else {
	    x2 = gap;
	    y2 = (W->parent->height-1);
	}
      }
    else if (slice == 1)
      {
	if (vert) 
	  {
	    x1 = 0;
	    x2 = (W->parent->width-1);
	    y1 = gap+5;
	    y2 = 2.0*gap+5;
	  }
	else {
	    x1 = gap+5;
	    x2 = 2.0*gap+5;
	    y1 = 0;
	    y2 = (W->parent->height-1);
	    
	}
      }
    else if (slice == 2)
      {
	if (vert) 
	  {
	    x1 = 0;
	    x2 = (W->parent->width-1);
	    y1 = 2.0*gap+10;
	    y2 = 3.0*gap+10;
	  }
	else {
	    x1 = 2.0*gap+10;
	    x2 = 3.0*gap+10;
	    y1 = 0;
	    y2 = (W->parent->height-1);
	}

      }

    x2 -= (x1-1);
    y2 -= (y1-1);

    TransformCoords(W,x1,y1,x2,y2);
  }

return(0);
}


/* make function for the munsell sliders */

MunsellSliderMaker(W,id,data,stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{
  int slice,vert,x1,y1,x2,y2;
  float gap;
  struct Command *C;
  struct ezslidestruct *parms;
  
  C = GetCommand(W,DRAW);
  parms = (struct ezslidestruct *)*C->arguments;
  
  slice = (int)stuff;
  vert =  (W->parent->width < W->parent->height);
  if (vert) 
    gap = ((float)W->parent->height-10.0)/3.0, parms->orient = 1;
  else
    gap = ((float)W->parent->width-10.0)/3.0, parms->orient = 0;
  
    if (slice == 0)
      {
	x1 = 0;
	y1 = 0;
	if (vert) 
	  {
	    x2 = (W->parent->width-1);
	    y2 = gap;
	  }
	else {
	    x2 = gap;
	    y2 = (W->parent->height-1);
	}
      }
    else if (slice == 1)
      {
	if (vert) 
	  {
	    x1 = 0;
	    x2 = (W->parent->width-1);
	    y1 = gap+5;
	    y2 = 2.0*gap+5;
	  }
	else {
	    x1 = gap+5;
	    x2 = 2.0*gap+5;
	    y1 = 0;
	    y2 = (W->parent->height-1);
	    
	}
      }
    else if (slice == 2)
      {
	if (vert) 
	  {
	    x1 = 0;
	    x2 = (W->parent->width-1);
	    y1 = 2.0*gap+10;
	    y2 = 3.0*gap+10;
	  }
	else {
	    x1 = 2.0*gap+10;
	    x2 = 3.0*gap+10;
	    y1 = 0;
	    y2 = (W->parent->height-1);
	}

      }

    x2 -= (x1-1);
    y2 -= (y1-1);

    TransformCoords(W,x1,y1,x2,y2);
  }



Palette_Options(option)
{
struct Command *C;
struct messagestruct *m1,*m2,*m3;
int Palette_Options();
struct ezslidestruct *hs,*ss,*vs;
float h,s,v;
  switch (option)
    {
    case (PRINT_RGB):
        printf("\n");
	printf("Red %d   Green %d  Blue %d\n", CurrentRed, CurrentGreen, CurrentBlue);
      break;

    case (PRINT_HSV):
        printf("\n");
	printf("REAL Hue %f   Sat %f  Val %f\n", CurrentHue, CurrentSat, CurrentVal);
	rgb2mun(CurrentRed,CurrentGreen,CurrentBlue,&h,&s,&v);
	printf("calc hue %f   sat %f  val %f\n", h,s,v);
      break;

    case (ENTER_RGB):
      {
      char reply[40];
      
      if (GetString(Palette->parent, E_lastx,E_lasty,"Enter new RGB",reply,40))
	{
	  sscanf(reply,"%d %d %d",&CurrentRed,&CurrentGreen,&CurrentBlue);
#if 0
	  {			/* *DKY-10Apr91* */
	    int rgb[3];
	    float *hls;
	    
	    rgb[0] = CurrentRed;
	    rgb[1] = CurrentGreen;
	    rgb[2] = CurrentBlue;
	    hls = (float *)rgb_to_hls( rgb); /* didier's code */
	    printf( "values are %f, %f, %f\n", hls[0], hls[1], hls[2]);
	    CurrentHue = 100.0 * hls[0];
	    CurrentSat = 12.0 * hls[1];
	    CurrentVal = 26.0 * hls[2];
	    printf( "final values are %f,%f,%f\n", CurrentHue, CurrentSat, CurrentVal);

	    free( hls);
	  }
#endif
	  UpdateWin(Palette);
	}

      }
      break;

    case (ZOOM_FACTOR):
      {
      char string[100],reply[100];
      
      sprintf(string,"Enter new zoom factor. (it was %f)    ",zoom_factor);
      if (GetString(Palette->parent, E_lastx,E_lasty,string,reply,10))
	{
	  sscanf(reply,"%f",&zoom_factor);
	  if (zoomstat)
	    {
	      RestoreZoom();      /* simple variable saving and calculation */
	      NewZoom();
	      UpdateWin(Palette);
	    }
	}

      }
      break;

    case (ZOOM):

      if (zoomstat) /* unzoom */
	{
          RestoreZoom();
	  ChangePopUpLineAttributes(zoom,"Zoom in on current color",Palette_Options,ZOOM);
	  zoomstat = 0;
	}
      else { /* zoom in */

          NewZoom();
	  ChangePopUpLineAttributes(zoom,"Zoom out",Palette_Options,ZOOM);
	  zoomstat = 1;
      }

      UpdateWin(Palette);
      break;

    case (LINES):

      if (linestat)
	  ChangePopUpLineAttributes(lines,"Show grid lines",Palette_Options,LINES), linestat = 0;
      else 
	  ChangePopUpLineAttributes(lines,"Hide grid lines",Palette_Options,LINES), linestat = 1;

      UpdateWin(panel);
      break;

    case (GRID):
      {
      char string[100],reply[100];
      
      sprintf(string,"Enter new grid size. (it was %d)    ",gridsize);
      if (GetString(Palette->parent, E_lastx,E_lasty,string,reply,10))
	{
	  sscanf(reply,"%d",&gridsize);
	  UpdateWin(panel);
	}
      }
      break;

    case (PUPDATE):

      C = (struct Command *) GetCommand(Hs,DO);
      m1 = (struct messagestruct *)(*(C->arguments+2));
      C = (struct Command *) GetCommand(Vs,DO);
      m2 = (struct messagestruct *)(*(C->arguments+2));
      C = (struct Command *) GetCommand(Ss,DO);
      m3 = (struct messagestruct *)(*(C->arguments+2));

      if (updatestat)
	{
	  updatestat = 0;
	  ChangePopUpLineAttributes(update,"Continous panel update",Palette_Options,PUPDATE);
	  m1->mask = 2;
	  m2->mask = 2;
	  m3->mask = 2;
	}
      else {
	  updatestat = 1;
	  ChangePopUpLineAttributes(update,"Normal panel update",Palette_Options,PUPDATE);
	  m1->mask = 7;
	  m2->mask = 7;
	  m3->mask = 7;
      }

      break;
    }
  return(0);
}


RestoreZoom()
{
	  HueMax = hmax;
	  HueSMax = hsmax;
	  HueMin = hmin;
	  HueGap = hgap;

	  SatMax = smax;
	  SatSMax = ssmax;
	  SatMin = smin;
	  SatGap = sgap;

	  ValMax = vmax;
	  ValSMax = vsmax;
	  ValMin = vmin;
	  ValGap = vgap;

}



NewZoom()
{
	  hmax = HueMax;
	  hsmax = HueSMax;
	  hmin = HueMin;
	  hgap = HueGap;

	  smax = SatMax;
	  ssmax = SatSMax;
	  smin = SatMin;
	  sgap = SatGap;

	  vmax = ValMax;
	  vsmax = ValSMax;
	  vmin = ValMin;
	  vgap = ValGap;

	  HueMax = CurrentHue+(HueMax-HueMin)/(zoom_factor*2);
	  HueMin = CurrentHue-(HueMax-HueMin)/(zoom_factor*2);
	  HueGap = (HueMax-HueMin)/10.0;
	  HueSMax = HueMax+HueGap;

	  SatMax = CurrentSat+(SatMax-SatMin)/(zoom_factor*2);
	  SatMin = CurrentSat-(SatMax-SatMin)/(zoom_factor*2);
	  SatGap = (SatMax-SatMin)/10.0;
	  SatSMax = SatMax+SatGap;

	  ValMax = CurrentVal+(ValMax-ValMin)/(zoom_factor*2);
	  ValMin = CurrentVal-(ValMax-ValMin)/(zoom_factor*2);
	  ValGap = (ValMax-ValMin)/10.0;
	  ValSMax = ValMax+ValGap;

}


DeselectPalette()
{
SendMessage(H,DESELECT,NULL);
SendMessage(S,DESELECT,NULL);
SendMessage(V,DESELECT,NULL);
}

MakeSidePalette(Root,cursor,x,y)
{
MakeHandyPalette(Root,Current,cursor,x,y);
}
