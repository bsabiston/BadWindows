#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <ctype.h>

#define USA 1

/*
     Color Selector Window
     Bob Sabiston
     June 11 '89

     NOTE:  To use this window you must have a global variable in your program called Palette.
     Set Palette equal to the Munsell Palette Window, and this chooser will update the palette
     when you select a new color.

*/


extern struct Window *Palette;

extern char *MunsellPaletteMenuFont;	/* *DKY-31Oct90* */
extern int MunsellPaletteMenuFontSize;

int NextColorIndex, propagate = 0;

#define UPDATE_CHOOSER 9000
static int line_spacing = 18, movestartindex, movestartpalette;
static char default_palette_directory[200] = "/"; 
static struct Window *PaletteBrowser = NULL; 

struct color_entry {
  int red,green,blue;
  float hue,sat,val;
  char *tag;
  struct color_entry *next;
};


struct chooser_struct {
  struct color_entry *colors, *current;
  int num_colors,column_width,font_size;
  int chains_changed;
  char *name, *basename, *font;
  struct chooser_struct *next;
  struct Window *nameline;
};

struct master_chooser {
  struct chooser_struct *palettes, *current;
  struct Window *slider, *palette, *ok, *menu,*namebar, *copy;
  int min_line,vis_lines,start_line,num_lines, num_colors;
  char *name;
};

static struct master_chooser *chooser = NULL;
static struct chooser_struct *tempchooser = NULL;
static struct color_entry *tempcolor = NULL;
static struct Window *Cslideline, *Cslider, *pad, *Propline, *pluswin, *minuswin, *Plusline;

struct Window *MakeChooser(Root,echo,x,y,w,h, disable_chooser)
struct Window *Root;
struct curstruct *echo;
int x,y,w,h, disable_chooser;
{
   struct curstruct *icon,*ricon,*plicon,*micon;
   struct Window *base, *slider, *temp, *menu, *button, *resizer,*s,*name,*nmenu;
   struct OutDev *display;
   struct InDev *locator;
   struct chooser_struct *cstruct;
   struct master_chooser *mstruct;
   int Load_Chooser(), Save_Chooser(), Move_Color(), ChooserDo(), UpdateWin(),Add_Chooser_Color(), Delete_Chooser_Color();
   int Change_Color_Name(), Change_Chooser_Attributes(), Load_Chooser_Old(), Move_Ok(), Trash_Palette_2(), Copy_Color();
   int ToggleCslider(), Append_Chooser(), SwitchToPalette(), Add_Palette(), Save_Whole_Chooser(), Trash_All_Palettes();
   int Copy_Ok(), TogglePropagate(), TogglePlusKeys(), Move_Palette();

   display = Root->display;
   locator = Root->input;
   ricon = (struct curstruct *)LoadIcon("icons/resize_icon",8,82);
   plicon = (struct curstruct *)LoadIcon("icons/plus_icon",8,82);
   micon = (struct curstruct *)LoadIcon("icons/minus_icon",8,82);
   icon = (struct curstruct *)LoadIcon("icons/dot_icon",8,82);
   /*
     SwapColors(ricon->source,ricon->dx,ricon->dy,DARK,DARK,DARK,120,120,140);
     SwapColors(plicon->source,plicon->dx,plicon->dy,DARK,DARK,DARK,120,120,140);
     SwapColors(micon->source,micon->dx,micon->dy,DARK,DARK,DARK,120,120,140);
     SwapColors(icon->source,icon->dx,icon->dy,DARK,DARK,DARK,120,120,140);
     */
   
   mstruct = chooser = (struct master_chooser *)malloc(sizeof(struct master_chooser));
   mstruct->palette = NULL;
   mstruct->min_line = 0;
   mstruct->vis_lines = 4;
   mstruct->start_line = 0;
   mstruct->num_lines = 0;
   mstruct->num_colors = 0;
   mstruct->name = malloc(200);
   *mstruct->name = 0;
   nmenu =  (struct Window *)MakePopUp(Root1,echo,15,"Swiss",12,8,0,0,0,0,210,210,210);
   mstruct->menu = nmenu;

   cstruct = mstruct->palettes = mstruct->current = (struct chooser_struct *)malloc(sizeof(struct chooser_struct));
   cstruct->colors = NULL;
   cstruct->chains_changed = 0;
   cstruct->current = NULL;
   cstruct->column_width = 50;
   cstruct->font_size = 12;
   cstruct->num_colors = 0;
   cstruct->name = malloc(200);
   cstruct->basename = malloc(100);
   *cstruct->name = *cstruct->basename = 0;
   cstruct->nameline = (struct Window *)AddPopUpLine(mstruct->menu,cstruct->basename,SwitchToPalette,cstruct); 
   cstruct->font = CopyString("Swiss");
   line_spacing = cstruct->font_size+6;
   cstruct->next = NULL;


   PaletteBrowser = (struct Window *) MakeFileBrowser(Root,echo,"Swiss",12,100,100,100,
						      130,130,130,0,0,0,FULL,FULL,FULL);

   base = MakeWindow(display,locator,Root,x,y,w,h,"color selector");
   RoundRectify(base,30,30,25,2,0,0,0,.015);
   CornerResizer(base,20,80,80,8000,8000);
   MoverII(base,base,24);
   EchoWrap(base,echo,7,0,0); 

   pad = (struct Window *)MakeWindow(Root->display,Root->input,base, 0,0,10,10,"portal");
   Rectify(pad,30,30,25,0,30,30,25,0);
   AttachCommand(pad,DO,ChooserDo,mstruct);             
   EchoWrap(pad,echo,7,0,0);
   AttachCommand(pad,UPDATE_CHOOSER,ChooserDo,mstruct);	/* search for xmax,ymax values when an object is added or removed */
   Maker(pad,3,24+icon->dy,-14,-5);
   AttachCommand(pad,MAKE,ChooserDo,mstruct); /* so the script can change the slider parameters */
   AttachCommand(pad,DRAW,ChooserDo,mstruct); /* Draw it */
   InstallWin(pad);


   temp = MakeWindow(Root->display,Root->input,base,0,0,20,20,"grid");
   MakePopUpTriggerNoEor(temp,echo,nmenu,0,0);
   EchoWrap(temp,echo,1,0,1);
   Rectify(temp,DARK,DARK,DARK,1,0,0,0,1);
   StringWin(temp,NULL,2,0,"Swiss",12,8,0,0,0,0);
   Maker(temp,3,3,-3,20);
   InstallWin(temp);
   mstruct->namebar = temp;

   slider = (struct Window *)MakeWindow(Root->display,Root->input,base, 0,0,10,10,"slider");
   AreaSlider(slider,1,120,120,130,0,0,0,0,DARK,DARK,DARK,0,
              &mstruct->start_line,&mstruct->num_lines,&mstruct->min_line,&mstruct->vis_lines);
   FunctionCaller(slider,DO,UpdateWin,pad,7);
   EchoWrap(slider,echo,7,0,0);
   Maker(slider,-3-10,27+icon->dy,-3,-8);
   InstallWin(slider);
   mstruct->slider = slider;

   /* buttons */

      temp = MakeWindow(Root->display,Root->input,base,0,0,20,20,"grid");
      FunctionCaller(temp,DO,Add_Chooser_Color,pad,1);
      EchoWrap(temp,echo,1,0,0);
      AttachIcon(temp,plicon);
      Maker(temp,-3-icon->dx-plicon->dx - micon->dx - 6+1,24,-3-icon->dx-1,24+plicon->dy-1);
      InstallWin(temp);
      pluswin = temp;
      
      temp = MakeWindow(Root->display,Root->input,base,0,0,20,20,"grid");
      FunctionCaller(temp,DO,Delete_Chooser_Color,pad,1);
      EchoWrap(temp,echo,1,0,0);
      AttachIcon(temp,micon);
      Maker(temp,-3-icon->dx- micon->dx - 3+1,24,-3-icon->dx-1,24+plicon->dy-1);
      InstallWin(temp);
      minuswin = temp;

   if (disable_chooser) {
      UnstallWin(pluswin);
      UnstallWin(minuswin);
   }

   Cslider = MakeColorSlider(Root,echo,800,MAX(y - 200,0));

   menu =  (struct Window *)MakePopUp(Root,echo,15,MunsellPaletteMenuFont,MunsellPaletteMenuFontSize,8,0,0,0,0,150,150,160);
   AddPopUpLine(menu,"Change Name",Change_Color_Name,pad);
   AddPopUpLine(menu,"Copy Current Color Into Another Cel",Copy_Color,pad);
   AddPopUpLine(menu,"Move Current Color",Move_Color,pad);
   AddPopUpLine(menu,"Move THIS Palette to Top",Move_Palette,pad);
   AddPopUpLine(menu,"Trash THIS Palette",Trash_Palette_2,pad);
   AddPopUpLine(menu,"Trash ALL Palettes",Trash_All_Palettes,pad);
   AddPopUpLine(menu,"Add a Blank Color Palette",Add_Palette,pad);
   AddPopUpLine(menu,"Append Color Palette",Load_Chooser,pad);
   /*   AddPopUpLine(menu,"Load Old Color Palette",Load_Chooser_Old,pad); */
   AddPopUpLine(menu,"Change Attributes",Change_Chooser_Attributes, pad);
   Propline = (struct Window *)AddPopUpLine(menu,"Turn color propagate ON",TogglePropagate,NULL);
   AddPopUpLine(menu,"Save THIS Color Palette",Save_Chooser,pad);
   AddPopUpLine(menu,"Save ALL Color Palettes",Save_Whole_Chooser,pad);
   Cslideline = (struct Window *)AddPopUpLine(menu,"Open color slider",ToggleCslider,NULL);
   if (disable_chooser) Plusline = (struct Window *)AddPopUpLine(menu,"Attach Plus/Minus Keys",TogglePlusKeys,NULL);
   else  Plusline = (struct Window *)AddPopUpLine(menu,"Remove Plus/Minus Keys",TogglePlusKeys,NULL);
   
   button = MakeWindow(Root->display,Root->input,base,0,0,20,20,"grid");
   MakePopUpTrigger(button,echo,menu,0,-4);
   AttachIcon(button,icon);
   Maker(button,-3-icon->dx+1,24,-3,24+icon->dy-1);
   InstallWin(button);

   /*   resizer = (struct Window *)MakeWindow(Root->display,Root->input,base, 0,0,10,10,"resizer");
	EchoWrap(resizer,echo,7,0,0);
	AttachIcon(resizer,ricon);
	Maker(resizer,-5-ricon->dx+1,-5-ricon->dy+1,-5,-5);
	InstallWin(resizer);
	*/

   temp = (struct Window *)MakeWindow(base->display,base->input,Root,10,10,10,10,"draw");
   FunctionCaller(temp,DO,Move_Ok,pad,1); /* strange window.  */
   EchoWrap(temp,echo,1,0,1);
   RoundRectify(temp,170,170,170,1,0,0,0,.02);
   StringWin(temp,"blah",5,1,"Swiss",12,8,0,0,0,0);
   mstruct->ok = temp;

   temp = (struct Window *)MakeWindow(base->display,base->input,Root,10,10,10,10,"draw");
   FunctionCaller(temp,DO,Copy_Ok,pad,1); /* strange window.  */
   EchoWrap(temp,echo,1,0,1);
   RoundRectify(temp,170,170,170,1,0,0,0,.02);
   StringWin(temp,"blah",5,1,"Swiss",12,8,0,0,0,0);
   mstruct->copy = temp;

   UpdateSizes(base);
   InstallWin(base);
   return (pad);
}



Change_Color_Name(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct;
  char string[50];
  struct color_entry *color;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;

  color = cstruct->current;
  if (color) 
    {
      string[0] = 0;
      if (GetString(pad->parent->parent,E_lastx,E_lasty,"Enter a new name for this color.",string,30))
	{
	   if (strcmp(string,"")) {
	      if (color->tag) free(color->tag);
	      color->tag = (char *)CopyString(string);
	      cstruct->chains_changed = 1;
	      UpdateWin(pad);
	   }
	}
    }
}



Change_Chooser_Attributes(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct;
  char string[20], command[50];
  int x,y;

  x = pad->x2; y = pad->y1;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  string[0] = 0;
  sprintf(command,"Enter font name (was %s).",cstruct->font);
  if (GetString(pad->parent->parent,x,y,command,string,30))
    {
      if (cstruct->font) free(cstruct->font);
      cstruct->font = (char *)CopyString(string);
      cstruct->chains_changed = 1;
    }

  string[0] = 0;
  sprintf(command,"Enter font size (was %d).",cstruct->font_size);
  if (GetString(pad->parent->parent,x,y,command,string,30))
    {
      sscanf(string,"%d",&cstruct->font_size);
      cstruct->chains_changed = 1;
    }
  line_spacing = cstruct->font_size+6;

  string[0] = 0;
  sprintf(command,"Enter minimum column width (was %d).",cstruct->column_width);
  if (GetString(pad->parent->parent,x,y,command,string,30))
    {
      sscanf(string,"%d",&cstruct->column_width);
      cstruct->chains_changed = 1;
    }

  UpdateSizes(pad);
  UpdateWin(pad);
  UpdateWin(mstruct->slider);
  return(0);
}


Save_Chooser(pad)
     struct Window *pad;
{
  char string[150];
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct,*c;
  int SwitchToPalette();
  
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;

  strcpy(string,cstruct->name);
/*
  if (FileBrowser(PaletteBrowser,string,"",500,500,string))
    {
*/
  if( GetString2( pad->parent->parent, E_lastx, E_lasty, "Enter palette filename. (full path)", string, 150)) 
    {
      printf("saving at %s\n",string);
      Save_Chooser_Internal( pad, string);
      strcpy(cstruct->name,string);
      Basename(cstruct->name,".pal",cstruct->basename);
      ChangePopUpLineAttributes(cstruct->nameline,cstruct->basename,SwitchToPalette,cstruct);
      BufUpdateWin(mstruct->namebar);
    }

  return(0);
}


Save_Whole_Chooser(pad)
     struct Window *pad;
{
  Save_Whole_Chooser_I(pad, 0);
}

Save_Named_Whole_Chooser_I(pad,esave,name)
   struct Window *pad;
   char *name;
   int esave;
{
  struct master_chooser *mstruct;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  strcpy(mstruct->name,name);
  Save_Whole_Chooser_I(pad,esave);
}

Save_Whole_Chooser_I(pad,esave)
     struct Window *pad;
     int esave;
{
  FILE *fp, *fp2, *fopen();
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct,*c;
  int SwitchToPalette();
  char string[200];

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  c = mstruct->current;
  cstruct = mstruct->palettes;
  while (cstruct) {
    mstruct->current = cstruct; 
    SendMessage(mstruct->namebar,CHANGESTRING,cstruct->basename);
    BufUpdateWin(pad);
    BufUpdateWin(mstruct->namebar);

    if (strcmp(cstruct->name,"")) {
      /* has a name */
      printf("saving %s...\n",cstruct->name);
      if (esave) {
	sprintf(string,"%s.esave",cstruct->name);
	strcpy(cstruct->name,string);
   	Save_Chooser_Internal(pad,string);
      }
      Save_Chooser_Internal(pad,cstruct->name);
    }
    else {
      while(!GetString2( pad->parent->parent, E_lastx, E_lasty, "Please enter a full pathname for this palette. ", cstruct->name, 100)); 
      
      Basename(cstruct->name,".pal",cstruct->basename); 
      Save_Chooser_Internal( pad, cstruct->name);
      ChangePopUpLineAttributes(cstruct->nameline,cstruct->basename,SwitchToPalette,cstruct);
      BufUpdateWin(mstruct->namebar);
    }
    cstruct = cstruct->next;
  }

  
  if (!esave) strcpy(string,mstruct->name);
  else sprintf(string,"%s.esave",mstruct->name);

  if (!strcmp(string,""))
    GetString2( pad->parent->parent, E_lastx, E_lasty, "If desired, enter a pathname for the palette list file. ",string,100);

  if (strcmp(string,"")) {
      if (fp = fopen(string,"r")) {
	fclose(fp); 
 	sprintf(wdefstring,"mv %s %s~", string,string);
	system(wdefstring);
	printf("%s\n",wdefstring);
      }
  
      if ( !(fp = fopen(string,"w")) ) {
	printf("Can't open %s for output text. Sorry.\n", string);
      }

      fprintf(fp,"Palette Version 2\n");

      cstruct = mstruct->palettes;
      while (cstruct) {
	fprintf(fp,"%s\n",cstruct->name);
	cstruct = cstruct->next;
      }
      fclose(fp);
   }

  mstruct->current = c;
  return(0);
}


Save_Chooser_Internal( pad, string) /* new function *DKY-19Jun91* -- so we can save a chooser w/o GetString */
     struct Window *pad;
     char *string;		/* filename */
{
  struct chooser_struct *cstruct;
  struct master_chooser *mstruct;
  FILE *fp, *fp2, *fopen();
  struct color_entry *color, *oc = NULL;
  int num,i,numread;
  
  mstruct = (struct chooser_struct *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;

  if (fp = fopen(string,"r")) {
    fclose(fp); 
    sprintf(wdefstring,"mv %s %s~", string,string);
    system(wdefstring);
    printf("%s\n",wdefstring);
  }

  if ( !(fp = fopen(string,"w")) ) {
    printf("Can't open %s for input text. Sorry.\n", string);
  }
  else {
    cstruct->chains_changed = 0;

    /* info */
    fprintf(fp,"Palette Version 1\n");
    fprintf(fp,"%d colors\n",cstruct->num_colors);
    fprintf(fp,"window stats %d %d %d %d\n",pad->parent->relx,pad->parent->rely,pad->parent->width,pad->parent->height);
    fprintf(fp,"column width: %d   font_size: %d  font_name: %s\n",cstruct->column_width,
	    cstruct->font_size, cstruct->font);
    fprintf(fp,"======================================================\n");
    color = cstruct->colors;
    while (color)
      {
	fprintf(fp,"  %d %d %d %f %f %f ",color->red,color->green,color->blue,color->hue,color->sat,color->val);
	if (color->tag) fprintf(fp,"%s\n",color->tag);
	else  fprintf(fp,"*\n");
	color = color->next;
      }

    fclose(fp);
  }
  return(0);
}


Load_Chooser(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  mstruct = (struct chooser_struct *) GetStuff(pad, UPDATE_CHOOSER);
  if (mstruct->current->colors) Add_Palette(pad);
  return(Load_Chooser_I(pad,0));
}
/*
Append_Chooser(pad)
struct Window *pad;
{
  Add_Palette(pad);
  return(Load_Chooser_I(pad,0));
}
*/
Add_Palette(pad)
struct Window *pad;
{
  /* malloc new color table space */
  struct chooser_struct *cstruct,*lstruct;
  struct master_chooser *mstruct;
  int SwitchToPalette();

  mstruct = (struct chooser_struct *) GetStuff(pad, UPDATE_CHOOSER);
  lstruct = mstruct->palettes;
  while (lstruct->next) lstruct = lstruct->next;

  cstruct = mstruct->current = lstruct->next = (struct chooser_struct *)malloc(sizeof(struct chooser_struct));
  cstruct->colors = NULL;
  cstruct->chains_changed = 0;
  cstruct->current = NULL;
  cstruct->column_width = 50;
  cstruct->font_size = 12;
  cstruct->num_colors = 0;
  cstruct->name = malloc(200);
  cstruct->basename = malloc(100);
  *cstruct->name = *cstruct->basename = 0;
  cstruct->nameline = (struct Window *)AddPopUpLine(mstruct->menu,cstruct->basename,SwitchToPalette,cstruct); 
  SendMessage(mstruct->namebar,CHANGESTRING,cstruct->basename);
  BufUpdateWin(mstruct->namebar);
  cstruct->font = CopyString("Swiss");
  line_spacing = cstruct->font_size+6;
  cstruct->next = NULL;

  BufUpdateWin(pad);
  BufUpdateWin(mstruct->namebar);
}

Load_Chooser_I(pad,append)
struct Window *pad;
int append;
{
  char string[200];
  if (GetString(pad->parent->parent, E_lastx,E_lasty,"Enter palette filename. (full path)",string,150)) 

/*   if (FileBrowser(PaletteBrowser,default_palette_directory,"",500,500,string)) */
    {
      strcpy(default_palette_directory,string);
      Read_Chooser(string,pad,append);
      CloseWindow(pad->parent);
      UpdateSizes(pad->parent);
      OpenWindow(pad->parent);
    }
  return(0);
}


SetPaletteDirectory(string)
char *string;
{
  printf("setting palette directory to %s\n",string);
  if (!strcmp(string,"")) strcpy(default_palette_directory,"/pic3/USA_DB_DEVELOPMENT/jobs/simpson2/palette-library/");
  else strcpy(default_palette_directory,string);
}

GetPaletteDirectory(pad,string)
struct Window *pad;
char *string;
{
  struct master_chooser *mstruct;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  strcpy(string,mstruct->name);
}

Read_Chooser(name,pad,append)
     char *name;
     struct Window *pad;
     int append;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct;
  FILE *fp, *fp2, *fopen();
  struct color_entry *color, *oc = NULL;
  int num,i,numread,version,dummy;
  struct Window *W;
  char string[200];
  
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  W = pad->parent;

  if ( !(fp = fopen(name,"r")) ) {
    printf("Read_Chooser() - Can't open \"%s\" for input text. Sorry.\n", name);
    return( -1);		/* *DKY-19Jun91* */
  }
  else {

#if 0
    if (!append) {
      TrashChooser(mstruct);  /* NEW: having it trash the old palette */
      cstruct->chains_changed = 0;
    }
#endif

    /* info */
    fscanf(fp,"Palette Version %d\n", &version);
    if (version == 1) {
      strcpy(cstruct->name,name);
      Basename(name,".pal",cstruct->basename);
      ChangePopUpLineAttributes(cstruct->nameline,cstruct->basename,SwitchToPalette,cstruct);
      SendMessage(mstruct->namebar,CHANGESTRING,cstruct->basename);
      if (pad->parent->parent->stat) BufUpdateWin(mstruct->namebar);

      fscanf(fp,"%d colors\n",&num);

      if ((pad->display->bits&BUFTYPE) == CRX8)
	if (mstruct->num_colors + num > 115) {
	  num = 115-mstruct->num_colors;
	  printf("Your palette can only have 115 user-defined colors.  There are already %d. Only loading %d.\n",
		 mstruct->num_colors,num);
	}

      fscanf(fp,"window stats %d %d %d %d\n",&dummy,&dummy,&dummy,&dummy);
      fscanf(fp,"column width: %d   font_size: %d  font_name: ",&dummy,&dummy);
      fgets(string, 50, fp);
      *(string+strlen(string)-1) = 0;

      if (cstruct->font) free (cstruct->font);
      cstruct->font = (char *)CopyString(string);
      fscanf(fp,"======================================================\n");
      oc = cstruct->colors;
      if (oc) while (oc->next) oc = oc->next;
      for (i = 0; i < num; i++)
	{
	  color = (struct color_entry *)malloc(sizeof(struct color_entry));
	  color->next = NULL;
	  fscanf(fp,"  %d %d %d %f %f %f ",&color->red,&color->green,&color->blue,&color->hue,&color->sat,&color->val);
	  fgets(string,50,fp);
	  *(string+strlen(string)-1) = 0;
	  if (strcmp(string,"*"))
	    {
	      color->tag = (char *)CopyString(string);
	    }
	  else color->tag = NULL;
	  if (oc)
	    {
	      oc->next = color;
	      oc = color;
	    }
	  else {
	    cstruct->colors = color;
	    oc = color;
	  }
	  cstruct->num_colors++;
	  mstruct->num_colors++;
	}
      fclose(fp);
    }
    else if (version ==  2) {
      int i;
      strcpy(mstruct->name, name);
      /* this signifies a multiple palette list file */
      i = 0;
      while (fgets(string,200,fp) > 0) 
	{
	  *(string+strlen(string)-1) = 0;
	  if (i) Add_Palette(pad); 
	  printf("reading palette %s...\n",string);
	  Read_Chooser(string,pad,0);
	  i++;
	}
    }

    if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
  }

  return(0);
}



Load_Chooser_Old(pad)
struct Window *pad;
{
  struct chooser_struct *cstruct;
  struct master_chooser *mstruct;
  FILE *fp, *fp2, *fopen();
  struct color_entry *color, *oc = NULL;
  char string[100], *nstring;
  int num,i,numread;
  
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  cstruct->chains_changed = 0;

  TrashChooser(mstruct);
  if (GetString(pad->parent->parent, E_lastx,E_lasty,"Enter palette filename. (full path)",string,100))
    {
      if ( !(fp = fopen(string,"r")) ) {
	printf("Can't open %s for input text. Sorry.\n", string);
      }
      else {
	/* info */
        
	fscanf(fp,"%d colors\n",&num);
	
	for (i = 0; i< num; i++) {
	  fgets(string, 100, fp);
	  color = (struct color_entry *)malloc(sizeof(struct color_entry));
	  color->next = NULL;

	  numread = (sscanf(string,"%d %d %d  ",&(color->red), &(color->green),&(color->blue)));
	    color->hue = 0.5;
	    color->sat = 0.0;
	    color->val = 0.0;
/*
	  numread = (sscanf(string,"%d %d %d %f %f %f\n",&(color->red), &(color->green),&(color->blue)
			 &(color->hue), &(color->sat),&(color->val)));
	  if (numread < 6) {
	    color->hue = 0.5;
	    color->sat = 0.0;
	    color->val = 0.0;
	  }
*/

	      *(string+strlen(string)-1) = 0;
	      nstring = string;
	      while ((*nstring)&&(!isalpha(*nstring))) nstring++;

	      if (*nstring)
		{
		  color->tag = (char *)CopyString(nstring);
		}
	      else color->tag = NULL;

	  if (!oc)
	    {
	      cstruct->colors = color;
	      oc = color;
	    }
	  else {
	    oc->next = color;
	    oc = color;
	    }
	}
	cstruct->num_colors = num;
	mstruct->num_colors += num;
	fclose(fp);
	UpdateSizes(pad);
	UpdateWin(pad);
      }
    }
  return(0);
}



Move_Color(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct;
  int i;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  tempcolor = cstruct->current;
  tempchooser = cstruct;
  if (tempcolor) {
    movestartindex = CurrentSubIndex;
    movestartpalette = CurrentPaletteIndex;
    set_font("Swiss",12,8);
    SendMessage(mstruct->ok,CHANGESTRING," Put current color after what other color? ");
    mstruct->ok->width = string_width("  Put current color after what other color?  ");
    mstruct->ok->height = 20;
    mstruct->ok->relx = MIN(pad->x2 +30, 1280-mstruct->ok->width-10);
    mstruct->ok->rely = MIN(pad->y1 +5, 1024-mstruct->ok->height-10);
    mstruct->ok->display= pad->display;
    UpdateSizes(mstruct->ok);
    OpenWindow(mstruct->ok);
    }
  return(0);
}


Move_Ok(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct, *ocstruct;
  struct color_entry *start;
  int i;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  cstruct->chains_changed = 1;

  CloseWindow(mstruct->ok);
      if ((cstruct->current)&&(tempcolor)&&(tempcolor != cstruct->current)&&(tempchooser))
	{
	  /* do the move */
	    /* detach old color */
	    start = tempchooser->colors;
	    if (start == tempcolor)
		tempchooser->colors = tempcolor->next;
	    else {
	      while (start->next != tempcolor) start = start->next;
	      start->next = tempcolor->next;
	      } 

	    tempchooser->num_colors--;
	    cstruct->num_colors++;

  	    /* paste it back */
	    start = cstruct->colors;
	    while (start != cstruct->current) start = start->next;
	    tempcolor->next = start->next;
	    start->next = tempcolor;
	    if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
	    UpdateWin(pad);


#ifdef USA
	    if (propagate) PaintPaletteModify(0,movestartindex,CurrentSubIndex, movestartpalette, CurrentPaletteIndex);
#endif
	}
  tempcolor = NULL;

return (0);
}





Copy_Color(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct;
  int i;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  tempcolor = cstruct->current;
  tempchooser = cstruct;
  if (tempcolor) {
    movestartindex = CurrentSubIndex;
    movestartpalette = CurrentPaletteIndex;
    set_font("Swiss",12,8);
    SendMessage(mstruct->copy,CHANGESTRING," Copy current color into what other color? ");
    mstruct->copy->width = string_width("  Copy current color into what other color?  ");
    mstruct->copy->height = 20;
    mstruct->copy->relx = MIN(pad->x2 +30, 1280-mstruct->copy->width-10);
    mstruct->copy->rely = MIN(pad->y1 +5, 1024-mstruct->copy->height-10);
    mstruct->copy->display= pad->display;
    UpdateSizes(mstruct->copy);
    OpenWindow(mstruct->copy);
    }
  return(0);
}


Copy_Ok(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cstruct;
  struct color_entry *start;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  cstruct->chains_changed = 1;

  CloseWindow(mstruct->copy);
  if ((cstruct->current)&&(tempcolor)&&(tempcolor != cstruct->current)&&(tempchooser))
    {
      /* do the move */
      /* copy tempcolor into cstruct->current */

	  cstruct->current->red   = tempcolor->red;
	  cstruct->current->green = tempcolor->green;
   	  cstruct->current->blue  = tempcolor->blue;
	  cstruct->current->hue   = tempcolor->hue;
	  cstruct->current->sat   = tempcolor->sat;
 	  cstruct->current->val   = tempcolor->val;

	  if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
	  UpdateWin(pad);

#ifdef USA
	  if (propagate) PaintPaletteModify(0,movestartindex,CurrentSubIndex,NULL,NULL);
#endif
	}
  tempcolor = NULL;

return (0);
}

Add_Chooser_Color(pad)
struct Window *pad;
{
  struct chooser_struct *cstruct;
  struct color_entry *color, *c2;
  struct master_chooser *mstruct;
  int pp;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;

  if (mstruct->num_colors >= 115) printf("WARNING: This color is beyond the maximum for paint mode.\n You will not be able to use it for 8-bit painting\n");
  cstruct->num_colors++;
  mstruct->num_colors++;
  cstruct->chains_changed = 1;
  SendMessage(pad, UPDATE_CHOOSER, NULL);
  mstruct->start_line = mstruct->num_lines-mstruct->vis_lines;
  if (mstruct->start_line < 0) mstruct->start_line = 0;

  color = (struct color_entry *)malloc(sizeof(struct color_entry));
  color->red = CurrentRed;
  color->blue = CurrentBlue;
  color->green = CurrentGreen;

  for (cstruct = mstruct->palettes,pp = 0; cstruct != mstruct->current; cstruct = cstruct->next,pp++);
  CurrentPaletteIndex = pp;
  printf("currentpalette index %d\n",pp);
  CurrentSubIndex = cstruct->num_colors-1;
  CurrentIndex = GetTrueColorIndex(CurrentPaletteIndex,CurrentSubIndex);
  color->hue = CurrentHue;
  color->sat = CurrentSat;
  color->val = CurrentVal;
  color->tag = NULL;
  color->next = NULL;
  if (cstruct->colors) 
    {
      c2 = cstruct->colors;
      while (c2->next) c2 = c2->next;
      c2->next = color;
    }
  else cstruct->colors = color;

  cstruct->current = color;

  if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
  
  if (Cslider->stat) {
    NewCsliderColor();
    UpdateWin(Cslider);
  }

#ifdef USA
  if (propagate) PaintPaletteModify(1,CurrentSubIndex,CurrentPaletteIndex,NULL,NULL);
#endif
  UpdateWin(pad);
  UpdateWin(mstruct->slider);
  return(0);
}


Delete_Chooser_Color(pad)
struct Window *pad;
{
  struct chooser_struct *cstruct;
  struct color_entry *color, *cstart;
  struct master_chooser *mstruct;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;

  if (cstruct->current) 
    {
      cstruct->chains_changed = 1;
      cstruct->num_colors--;
      mstruct->num_colors--;
      SendMessage(pad, UPDATE_CHOOSER, NULL);
      if (cstruct->current == cstruct->colors)
	  cstruct->colors = cstruct->colors->next;
      else {
	cstart = cstruct->colors;
	color = cstruct->colors;
	while (color != cstruct->current) 
	  {
	    cstart = color;
	    color = color->next;
	  }
	cstart->next = color->next;
      }

      if (cstruct->current->tag) free (cstruct->current->tag);
      free (cstruct->current);
      cstruct->current = NULL;
    }

  if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);

#ifdef USA
  if (propagate) PaintPaletteModify(2,CurrentSubIndex,CurrentPaletteIndex,NULL,NULL);
#endif
  CurrentRed = cstruct->colors->red;
  CurrentGreen = cstruct->colors->green;
  CurrentBlue = cstruct->colors->blue;
  Select_New_Color();

  UpdateWin(pad);
  UpdateWin(mstruct->slider);
  return(0);
}




ChooserDo(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
struct clipstruct *cstruct;
struct master_chooser *mparms;
struct chooser_struct *parms,*cc;
int f, maxwide,maxtall,val = 0;
int xx,x,y,n,l,flag,screen;
int columns, col,cw, cstart,ii = 0;
static float far;
float frame;
struct trapstruct T;
struct color_entry *color;

screen = W->display->fildes;
mparms = (struct master_chooser *)stuff;
parms = mparms->current;

switch (id) {
 case (UPDATE_CHOOSER):
              /* is this all that goes here? I really just don't know */
              columns = W->width/parms->column_width;
              cw = W->width/columns;
              cstart = W->width%columns;
              mparms->num_lines = (parms->num_colors+columns)/columns;
              mparms->vis_lines = (W->height-4)/line_spacing+1;
              break;

 case (DO):
              {    
		static int x1,y1,x2,y2,m_id,update;
		struct pickstruct *pick;
		struct funcstruct *fs;
		static struct color_entry *scolor,*color;

		pick = (struct pickstruct *)data;
		switch (pick->button) {
		case (JUSTDOWN):
		  scolor = parms->current;
		case (BEENDOWN):
		         /* find color you're pointing at */
		  columns = W->width/parms->column_width;
		  cw = W->width/columns;
		  cstart = W->width%columns;
		  ii = 141;
		  for (cc = mparms->palettes; cc != parms; cc = cc->next) ii += cc->num_colors;

		         x = (pick->x-W->x1-cstart)/cw;
		         y = (pick->y-W->y1-2)/line_spacing+ mparms->start_line;
		         color =parms->colors;
		         y *= columns;
		         y += x;
		         while ((color) && (y--))		           
			     color = color->next, ii++;
			 if (color) 
			   {
			     parms->current = color;
			     CurrentIndex = ii; 
			     SetColorLookups(ii);
			     CurrentHue = color->hue;
			     CurrentSat = color->sat;
			     CurrentVal = color->val;
			     CurrentRed = color->red;
			     CurrentGreen = color->green;
			     CurrentBlue = color->blue;
			     if (scolor != color)
			       UpdateWin(W);
			     val = 0;
			   }
		         else val = 1;
		       break;

		       case (JUSTUP):
			 if ((scolor != color)&&(Palette))
			   UpdateWin(Palette);
		         if (Cslider->stat) {
			   NewCsliderColor();
			   UpdateWin(Cslider);
			 }
			 break;
		       }
	      } 
              break;

 case (DRAW):
              if (parms->num_colors == 0) break;
              cstruct = (struct clipstruct *)data;
	      set_font(parms->font,parms->font_size,8);
	      set_monitor(W->display->bits,screen); 
	      if (MIN(cstruct->y2,W->y2-3) >= cstruct->y1)
		{
		set_text_clip_rectangle(cstruct->x1,cstruct->y1,cstruct->x2,MIN(cstruct->y2,W->y2-1));
		clip_rectangle(screen,(float)cstruct->x1,(float)cstruct->x2,
			       (float)cstruct->y1,(float)cstruct->y2);
	        }

	      columns = W->width/parms->column_width;
	      cw = W->width/columns;
	      cstart = W->width%columns;
	      l = mparms->start_line;
	      perimeter_color(screen,0.0,0.0,0.0);
	      interior_style(screen,INT_SOLID,TRUE);
	      color = parms->colors;

	      ii = 141;
	      for (cc = mparms->palettes; cc != parms; cc = cc->next) ii += cc->num_colors;

	      if (l)
		while (l--)
		  {
		    for (xx = 0; xx < columns; xx++)
		      if (color) {
			color = color->next;
			ii++;
		      }
		  }
	      /* colors */
	      x = W->x1+cstart;
              y = W->y1+2+line_spacing;
	      while (y < W->y2-2)
		{
		  for (col = 0; col < columns; col++)
		    {
		      if (color)
			{
			  if ((W->display->bits&BUFTYPE) == CRX8)
			    fill_color_index(screen,ii);
			  else fill_color(screen,FCON(color->red),FCON(color->green),FCON(color->blue));
			  rectangle(screen,(float)(x+col*cw),(float)(y-line_spacing),
				    (float)(x+col*cw+cw-2),(float)(y-1));
			  if (color == parms->current)
			    {
			      perimeter_color(screen,1.0,1.0,1.0);
			      interior_style(screen, INT_HOLLOW,TRUE);
			      rectangle(screen,(float)(x+col*cw),(float)(y-line_spacing),
				    (float)(x+col*cw+cw-2),(float)(y-1));
			      interior_style(screen, INT_SOLID,TRUE);
			      perimeter_color(screen,0.0,0.0,0.0);
			    }
			  color = color->next;
			  ii++;
			}
		    }
		  y += line_spacing;
		}
	      make_picture_current(screen);

	      /* names */
	      columns = W->width/parms->column_width;
	      cw = W->width/columns;
	      cstart = W->width%columns;
	      set_font_color(10,10,20,0);
	      l = mparms->start_line;
	      color = parms->colors;
	      if (l)
		while (l--)
		  {
		    for (xx = 0; xx < columns; xx++)
		      if (color)
			color = color->next;
		  }
              y = W->y1+2+line_spacing;

	      while (y < W->y2-2)
		{
		  for (col = 0; col < columns; col++)
		    {
		      x = W->x1+cstart+col*cw;
		      if (color)
			{
			  if (color->tag)
			    {
			      xx = x + cw/2 - string_width(color->tag)/2;
			      if (xx < x) xx = x;
			      set_font_color(10,10,20,0);
			      display_string(color->tag,xx,y-line_spacing+3);
			      set_font_color(200,200,200,0);
			      display_string(color->tag,xx-2,y-1-line_spacing+2);
			    }
			  color = color->next;
			}
		    }
		  y += line_spacing;
		}

	      clip_rectangle(screen,(float)0.0,(float)W->display->width,
			       (float)0.0,(float)W->display->height);
	      break;
 case (MAKE):

              columns = W->width/parms->column_width;
              mparms->vis_lines = (W->height-4)/line_spacing;
              mparms->num_lines = (parms->num_colors+columns)/columns;
	      break;

 }
return(val);
}


Trash_Palette_2(pad)
struct Window *pad;
{
  struct master_chooser *mstruct;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  if (AskYesNo(pad->parent->parent,E_lastx,E_lasty,"Are you sure?"))
    TrashChooser(mstruct);
  UpdateWin(pad->parent);
}


Trash_Palette_WithoutConfirmation(pad) /* WINNER! Long Function name of the month club! tell him what he's won Jim*/
     struct Window *pad;
{
  struct master_chooser *mstruct;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  TrashChooser(mstruct);
  UpdateWin(pad->parent);
}

Trash_All_Palettes(pad) 
     struct Window *pad;
{
  struct master_chooser *mstruct;
  struct chooser_struct *cparms, *cn;
  struct color_entry *color,*c2;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  
  mstruct->num_colors = 0;

  cparms = mstruct->palettes;
  while (cparms) {
    RemovePopUpLine(cparms->nameline);
    cparms->chains_changed = 1;
    color = cparms->colors;
    while (color)
      {
	if (color->tag) free(color->tag);
	c2 = color;
	color = color->next;
	free(c2);
      }
    cn = cparms->next;
    free(cparms->name);
    free(cparms->basename);
    free(cparms);
    cparms = cn;
  }

  cparms = mstruct->palettes = mstruct->current = (struct chooser_struct *)malloc(sizeof(struct chooser_struct));
  cparms->colors = NULL;
  cparms->chains_changed = 0;
  cparms->current = NULL;
  cparms->column_width = 50;
  cparms->font_size = 12;
  cparms->num_colors = 0;
  cparms->name = malloc(200);
  cparms->basename = malloc(100);
  *cparms->name = *cparms->basename = 0;
  cparms->nameline = (struct Window *)AddPopUpLine(mstruct->menu,cparms->basename,SwitchToPalette,cparms); 
  cparms->font = CopyString("Swiss");
  line_spacing = cparms->font_size+6;
  cparms->next = NULL;
  SendMessage(mstruct->namebar,CHANGESTRING,cparms->basename);

  mstruct->start_line = 0;
  mstruct->num_lines = 0;
  mstruct->min_line = 0;
  mstruct->vis_lines = 4;

  UpdateWin(pad->parent);
}



TrashChooser(parms)
struct master_chooser *parms;
{
  struct chooser_struct *cparms, *cn, *next, *cstruct;
  struct color_entry *color,*c2;
  int pp;

  cparms = parms->current;

  /* fix the menu */
  for (cn = parms->palettes; cn; cn = cn->next) 
    RemovePopUpLine(cn->nameline);
  for (cn = parms->palettes; cn; cn = cn->next) 
    if (cn != cparms) AttachPopUpLine(cn->nameline);

  /* get new palette address */
  if (parms->current == parms->palettes) next = parms->current->next;
  else if ((next = cparms->next) == NULL) {
    next = parms->palettes;
    while (next->next != cparms) next = next->next;
  }

  /* take this palette out of the list */
  if (parms->current == parms->palettes)
    parms->palettes = parms->palettes->next; 
  else {
    cstruct = parms->palettes;
    while (cstruct->next != parms->current) cstruct = cstruct->next;
    cstruct->next = parms->current->next;
  }

  parms->num_colors -= cparms->num_colors;

  cparms->chains_changed = 1;
  color = cparms->colors;
  while (color)
    {
      if (color->tag) free(color->tag);
      c2 = color;
      color = color->next;
      free(c2);
    }
  free(cparms->name);
  free(cparms->basename);
  free(cparms);

  if (!parms->palettes) {
    CurrentPaletteIndex = 0;
    cparms = parms->palettes = parms->current = (struct chooser_struct *)malloc(sizeof(struct chooser_struct));
    cparms->colors = NULL;
    cparms->chains_changed = 0;
    cparms->current = NULL;
    cparms->column_width = 50;
    cparms->font_size = 12;
    cparms->num_colors = 0;
    cparms->name = malloc(200);
    cparms->basename = malloc(100);
    *cparms->name = *cparms->basename = 0;
    cparms->nameline = (struct Window *)AddPopUpLine(parms->menu,cparms->basename,SwitchToPalette,cparms); 
    cparms->font = CopyString("Swiss");
    line_spacing = cparms->font_size+6;
    cparms->next = NULL;
    SendMessage(parms->namebar,CHANGESTRING,cparms->basename);

    parms->start_line = 0;
    parms->num_lines = 0;
    parms->min_line = 0;
    parms->vis_lines = 4;
    
    if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
    UpdateWin(pad->parent);
  }
  else {
    for (cstruct = parms->palettes,pp = 0; cstruct != next; cstruct = cstruct->next,pp++);
    CurrentPaletteIndex = pp;
    if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
    SwitchToPalette(next);
  }
}



Move_Palette(pad)
struct Window *pad;
{
  struct chooser_struct *cparms, *cn, *next, *cstruct;
  struct color_entry *color,*c2;
  struct master_chooser *parms;
  int pp,oldindex;

  parms = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cparms = parms->current;

  /* fix the menu */
  for (cn = parms->palettes; cn; cn = cn->next) 
    RemovePopUpLine(cn->nameline);
  AttachPopUpLine(cparms->nameline);
  for (cn = parms->palettes; cn; cn = cn->next) 
    if (cn != cparms) AttachPopUpLine(cn->nameline);

  oldindex = 0;
  if (parms->current != parms->palettes) {
    for (cn = parms->palettes, oldindex = 1; cn->next != parms->current; cn = cn->next,oldindex++); 

    cn->next = parms->current->next; /* cut out the current from the list */
    parms->current->next = parms->palettes; /* tack on to the beginning */
    parms->palettes = parms->current;
  }

    if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
    UpdateWin(pad);

#ifdef USA
    if (propagate) PaintPaletteModify(3,CurrentSubIndex,CurrentSubIndex,oldindex,0);
#endif
    CurrentPaletteIndex = 0;
  
    return (0);
  }



Save_Chooser_Binary( pad, fp) /* new function *DKY-19Jun91* -- so we can save a chooser w/o GetString */
  struct Window *pad;
  FILE *fp;
{
  struct chooser_struct *cstruct;
  struct color_entry *color, *oc = NULL;
  int num,i,numread,v = 1;
  struct master_chooser *mstruct;
  
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  cstruct->chains_changed = 0;
    /* info */
    fwrite(&v,sizeof(int),1,fp);
    fwrite(&cstruct->num_colors,sizeof(int),1,fp);

    fwrite(&cstruct->column_width,sizeof(int),1,fp);
    fwrite(&cstruct->font_size,sizeof(int),1,fp);
    fprintf(fp,"%s\n",cstruct->font);
    color = cstruct->colors;
    while (color)
      {
	fwrite(&color->red,sizeof(int),1,fp);
	fwrite(&color->green,sizeof(int),1,fp);
	fwrite(&color->blue,sizeof(int),1,fp);
	fwrite(&color->hue,sizeof(float),1,fp);
	fwrite(&color->sat,sizeof(float),1,fp);
	fwrite(&color->val,sizeof(float),1,fp);
	if (color->tag) fprintf(fp,"%s\n",color->tag);
	else  fprintf(fp,"*\n");
	color = color->next;
      }
  return(0);
}



Load_Chooser_Binary(pad,fp)
     struct Window *pad;
     FILE *fp;
{
  struct chooser_struct *cstruct;
  struct color_entry *color, *oc = NULL;
  int num,i,numread,version,dummy;
  struct Window *W;
  char string[50];
  struct master_chooser *mstruct;
  
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;

  TrashChooser(mstruct);
  cstruct->chains_changed = 0;
  W = pad->parent;

    /* info */

    fread(&version,sizeof(int),1,fp);
    if (version == 1) {
      fread(&num,sizeof(int),1,fp);
      fread(&dummy,sizeof(int),1,fp);
      fread(&dummy,sizeof(int),1,fp);
      fgets(string, 50, fp);
      *(string+strlen(string)-1) = 0;

      if (cstruct->font) free (cstruct->font);
      cstruct->font = (char *)CopyString(string);

      oc = cstruct->colors;
      if (oc) while (oc->next) oc = oc->next;
      for (i = 0; i < num; i++)
	{
	  color = (struct color_entry *)malloc(sizeof(struct color_entry));
	  color->next = NULL;
	  fread(&color->red,sizeof(int),1,fp);
	  fread(&color->green,sizeof(int),1,fp);
	  fread(&color->blue,sizeof(int),1,fp);
	  fread(&color->hue,sizeof(float),1,fp);
	  fread(&color->sat,sizeof(float),1,fp);
	  fread(&color->val,sizeof(float),1,fp);

	  fgets(string,50,fp);
	  *(string+strlen(string)-1) = 0;
	  if (strcmp(string,"*"))
	    {
	      color->tag = (char *)CopyString(string);
	    }
	  else color->tag = NULL;
	  if (oc)
	    {
	      oc->next = color;
	      oc = color;
	    }
	  else {
	    cstruct->colors = color;
	    oc = color;
	  }
	  cstruct->num_colors++;
	  mstruct->num_colors++;
	}
    }

  if ((pad->display->bits&BUFTYPE) == CRX8) BuildColorTable8(pad);
  return(0);
}



BuildColorTable8(pad)
struct Window *pad;
{
  struct chooser_struct *cstruct;
  struct color_entry *color, *oc = NULL;
  int num,i,numread,version,c,ii;
  struct Window *W;
  float clist[115][3];
  char string[50];
  struct master_chooser *mstruct;
  
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);

  W = pad->parent;
/*  printf("building 8bit colortable..."); */

  if (mstruct->num_colors > 115) {
    printf("ERROR in Color Table. There are %d in this color table.  The maximum is 115.\n");
  }

  c = 0;
  for (cstruct = mstruct->palettes; cstruct; cstruct = cstruct->next) {
    color = cstruct->colors;
    ii = c;
    for (c; c< MIN(115,ii+cstruct->num_colors); c++)
      {
	clist[c][0] = FCON(color->red); clist[c][1] = FCON(color->green);  clist[c][2] = FCON(color->blue);
	ColorTable[c+141][0] = color->red; ColorTable[c+141][1] = color->green; ColorTable[c+141][2] = color->blue;
	color = color->next;
      }
    /*  printf("done %d colors\n",cstruct->num_colors);*/
  }
  define_color_table(W->display->fildes,141,MIN(115,mstruct->num_colors),clist);

  NextColorIndex = mstruct->current->num_colors;
  return(0);
}



ToggleCslider()
{

  if (Cslider->stat)
    {
      CloseWindow(Cslider);
      ChangePopUpLineAttributes(Cslideline,"Open color slider",ToggleCslider,NULL);
    }
  else {
    NewCsliderColor();
    OpenWindow(Cslider);
    ChangePopUpLineAttributes(Cslideline,"Close color slider",ToggleCslider,NULL);
  }

  return(0);
}

TogglePropagate()
{

   propagate = !propagate;
  if (propagate)
    {
      ChangePopUpLineAttributes(Propline,"Turn color propagate OFF",TogglePropagate,NULL);
    }
  else {
     ChangePopUpLineAttributes(Propline,"Turn color propagate ON",TogglePropagate,NULL);
  }

  return(0);
}

TogglePlusKeys()
{
  if (pluswin->stat)
    {
       ChangePopUpLineAttributes(Plusline,"Attach Plus/Minus Keys",TogglePlusKeys,NULL);
       UnstallWin(pluswin);
       UnstallWin(minuswin);
       UpdateSizes(pluswin->parent);
       UpdateWin(pluswin->parent);
    }
  else {
     ChangePopUpLineAttributes(Plusline,"Remove Plus/Minus Keys",TogglePlusKeys,NULL);
     InstallWin(pluswin);
     InstallWin(minuswin);
     UpdateSizes(pluswin->parent);
     UpdateWin(pluswin->parent);
  }

  return(0);
}


Select_New_Color()
{
  struct color_entry *c;
  struct chooser_struct *cstruct;
  int done = 0,ii,pp,bi = 141;

  for (cstruct = chooser->palettes,pp = 0; cstruct != chooser->current; cstruct = cstruct->next, pp++)
    bi += cstruct->num_colors;
  cstruct = chooser->current;
  for (c = cstruct->colors,ii= 0; c&&(!done);c = c->next,ii++,bi++) {
    if ((c->red == CurrentRed)&&(c->green == CurrentGreen)&&(c->blue == CurrentBlue)) {
      chooser->current->current = c;
      CurrentIndex = bi;
      CurrentSubIndex = ii;
      CurrentPaletteIndex = pp;
      done = 1;
    }
  }

  if (!done)
    for (cstruct = chooser->palettes,pp = 0, bi = 141; cstruct&&(!done);cstruct = cstruct->next,pp++) {
      for (c = cstruct->colors,ii= 0; c&&(!done);c = c->next,ii++,bi++) {
	if ((c->red == CurrentRed)&&(c->green == CurrentGreen)&&(c->blue == CurrentBlue)) {
	  chooser->current->current = c;
	  CurrentIndex = bi;
	  CurrentSubIndex = ii;
	  CurrentPaletteIndex = pp;
	  done = 1;
	}
      }
    }
  printf("Select_New_Color: %d %d %d\n",CurrentIndex, CurrentSubIndex, CurrentPaletteIndex);
  if (!done) chooser->current->current = NULL;
  if ((pad->parent->stat)&&(pad->parent->parent->stat))  BufUpdateWin(pad);

  if (Cslider->stat) {
    NewCsliderColor();
    BufUpdateWin(Cslider);
  }
}


GetPaletteIndex(r,g,b)
unsigned char r,g,b;
{
  struct chooser_struct *cstruct;
  struct color_entry *c;
  struct master_chooser *mstruct;
  int pi,ii,tt,bi;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  bi = 0;
  for (cstruct = mstruct->palettes, pi = 0; cstruct; cstruct = cstruct->next, pi++) {
    for (c = cstruct->colors,ii = 0; c; c = c->next, ii++, bi++) {
	if ((c->red == r)&&(c->green == g)&&(c->blue == b)) {
	  bi += 141;
	  return(bi);
	}
    }
  }
  return(-1);
}



ChooserColorUpdate(p,i,r,g,b,h,s,v)
int p,i,r,g,b;
float h,s,v;
{
  struct chooser_struct *cstruct;
  struct master_chooser *mstruct;
  struct color_entry *c;
  int ii = 0,pp;
  int done = 0;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->palettes;
  pp = p;
  while (pp--) cstruct = cstruct->next;

  c = cstruct->colors;
  while (c&&(!done)) {
    if (ii == i) {
      c->red = r;  
      c->green = g;  
      c->blue = b;  
      c->hue = h;  
      c->sat = s;  
      c->val = v;  
      done = 1;
    }
    c = c->next;
    ii++;
  }
}



ChooserChanged()
{
  struct chooser_struct *cstruct;
  struct master_chooser *mstruct;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  cstruct = mstruct->current;
  return(cstruct->chains_changed);
}


SetColorLookups(i)
unsigned char i;
{
  struct chooser_struct *cstruct;
  struct color_entry *c;
  struct master_chooser *mstruct;
  int p,ii,tt;

  ii = i - 141;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  if (ii >= 0) {
    for (cstruct = mstruct->palettes, p = 0; cstruct; cstruct = cstruct->next, p++)
      {
	if (ii - cstruct->num_colors < 0) {
	  CurrentSubIndex = ii;
	  CurrentPaletteIndex = p;
	  printf(" for index %d, got subindex %d in palette %d\n",i,CurrentSubIndex,CurrentPaletteIndex);
	  return(1);
	}
	else ii -= cstruct->num_colors;
      }
  }
  
  return(-1);
}


GetPaletteIndices(r,g,b,p,i)
unsigned char r,g,b,*p,*i;
{
  struct chooser_struct *cstruct;
  struct color_entry *c;
  struct master_chooser *mstruct;
  int pi,ii,tt,bi;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  bi = 0;
  for (cstruct = mstruct->palettes, pi = 0; cstruct; cstruct = cstruct->next, pi++) {
    for (c = cstruct->colors,ii = 0; c; c = c->next, ii++, bi++) {
	if ((c->red == r)&&(c->green == g)&&(c->blue == b)) {
	  *p = pi;
	  *i = ii;
	  bi += 141;
	  return(bi);
	}
    }
  }
  return(-1);
}


GetTrueColorIndex(p,i)
unsigned char p,i;
{
  struct chooser_struct *cstruct;
  struct color_entry *c;
  struct master_chooser *mstruct;
  int pi,ii,tt,bi,pp;

  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  bi = 141;
  pp = p;
  cstruct = mstruct->palettes;
  for (pi = 0; (pi < pp) && (cstruct) ; pi++,cstruct = cstruct->next)
      bi += cstruct->num_colors;
  bi += i;

  return(bi);
}



SwitchToNumberedPalette(p)
int p;
{
  int t;
  struct chooser_struct *cstruct;
  struct master_chooser *mstruct;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);

  for (t = 0, cstruct = mstruct->palettes; (t < p)&&cstruct; t++) cstruct = cstruct->next;
  if (cstruct) SwitchToPalette(cstruct);
  return(0);
}

SwitchToPalette(cstruct)
struct chooser_struct *cstruct;
{
  struct master_chooser *mstruct;
  mstruct = (struct master_chooser *) GetStuff(pad, UPDATE_CHOOSER);
  if (cstruct != mstruct->current) {
    mstruct->current->current = NULL;
    mstruct->current = cstruct;
    SendMessage(mstruct->namebar,CHANGESTRING,cstruct->basename);
    SendMessage(pad,UPDATE_CHOOSER,NULL);
    BufUpdateWin(mstruct->namebar);
    BufUpdateWin(pad);
    Select_New_Color();
  }
  return(0);
}





SetACTColor(r,g,b)
int r,g,b;
{
  float h,s,v, cl[3];
  rgb2hsv(r,g,b,&h,&s,&v);
  cl[0] = FCON(r);	cl[1] = FCON(g);	cl[2] = FCON(b);
  define_color_table(Cslider->display->fildes,141,1,cl);
  ColorTable[141][0] = r;
  ColorTable[141][1] = g;
  ColorTable[141][2] = b;
  ChooserColorUpdate(0,0,r,g,b,h,s,v);
  return(0);
}



