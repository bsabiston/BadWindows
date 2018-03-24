

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





/*****************************

  SCRIBLE.C

  Dave Small Sept 27, 89

*****************************/
#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <string.h>
#include <math.h>

#define THIN 0
#define THICK 1
#define MEDIUM 2

struct UPCStruct {
  unsigned long firstfive;
  unsigned long secondfive;
  int r, g, b;
};

static char line_table[] = "/vlw/data/100.tab";

struct Window *MakeUPC(parent, echo, x1, y1, wd, ht, ff, sf)
struct Window *parent;
struct curstruct *echo;
int x1, y1, wd, ht;
unsigned long ff, sf;
{
  struct Window *UPC;
  struct Window *SizerWin;

  UPC = (struct Window *)MakeWindow(parent->display, parent->input, parent,
				       x1, y1, wd, ht, "UPC");
  Mover(UPC, UPC);
  EchoWrap(UPC,echo,1,0,0);
  Rectify(UPC,227,227,227,0,0,0,0,0);
  UPCify(UPC, ff, sf, 0, 0, 0);
  InstallWin(UPC);

  SizerWin = (struct Window *)MakeWindow(parent->display,parent->input,
					 UPC,0,0,15,15,"SizerWin");
  ResizerPlus(SizerWin, UPC, 20,10,1300,1100);
  EchoRect(SizerWin, 200, 200, 200);
  EchoWrap(SizerWin,echo,7,0,0);
  Maker(SizerWin, -20, -20, -1, -1);
  InstallWin(SizerWin);
   
  UpdateSizes(UPC);

  return (UPC);
}

UPCify(W, firstfive, secondfive, r, g, b)
struct Window *W;
unsigned long firstfive;
unsigned long secondfive;
int r, g, b;
{
  struct UPCStruct *fd;
  int UPCWin();
  char *path;

  read_short_table (bw_file(line_table));
  
  if ((fd = (struct UPCStruct *) malloc (sizeof (struct UPCStruct))) == 0)
    printf ("error mallocing UPCStruct\n");
  
  while (firstfive <= 9999) {
      printf("firstfive (%d) too small; multiply by ten \n", firstfive);
      firstfive *= 10;
    }

  while (secondfive <= 9999) {
      printf("secondfive (%d) too small; multiply by ten \n", firstfive);
      secondfive *= 10;
    }

  fd->firstfive = firstfive;
  fd->secondfive = secondfive;
  fd->r = r;
  fd->g = g;
  fd->b = b;

  AttachCommand(W,DRAW,UPCWin,fd);

}

UPCWin(W,id,data,stuff)
struct Window *W;
int id;
char *data,*stuff;
{
  struct clipstruct *cstruct;
  struct UPCStruct *params;
  int cx1,cx2,cy1,cy2;
  int screen;
  int r, g, b, t;
  int i;
  float wd, wid;
  float fx, fy;
  float space;
  char string[20], char_string[10];
  unsigned long firstfive;
  unsigned long secondfive;
  unsigned long number;
  int  font_size, count = 0;
  int  small_size;

  screen = (W->display)->fildes;
  params = (struct UPCStruct *)stuff;

  switch (id) {
  case (DRAW):
    cstruct = (struct clipstruct *)data;
    cx1 = cstruct->x1;  cy1 = cstruct->y1;
    cx2 = cstruct->x2;  cy2 = cstruct->y2;
    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(W->display->fildes);

    W->display->control [3] = 4;
    W->display->control [0x40bf] = 7;
    W->display->control [0x40ef] = 0x33;
    drawing_mode(W->display->fildes, 3);
    
    aa_set_clip (cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
    aa_set_fb (W->display->fildes,(W->display)->bits, (W->display)->buffer, (W->display)->control,W->display->width,W->display->height);
    aa_set_color(params->r, params->g, params->b);
    aa_set_trans(250);
    
    set_monitor(W->display->bits, W->display->fildes);
    set_font_color(params->r, params->g, params->b, 0);
    set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);

    sprintf(string, "%d%d", params->firstfive, params->secondfive);

    space = W->width / 18;

    if (space < 10)
      font_size = 12, small_size = 12;
    else if (space < 14)
      font_size = 16, small_size = 12;
    else if (space < 20)
      font_size = 24, small_size = 16;
    else if (space < 28)
      font_size = 32, small_size = 24;
    else if (space < 32)
      font_size = 36, small_size = 24;
    else if (space < 40)
      font_size = 48, small_size = 32;
    else 
      font_size = 60, small_size = 36;

    for (i = 0; i < 18; i++) {
      switch (i) {
	/* a space */
      case (0):
	break; 
	/* the two small numbers */
      case (1):
	set_font("helv", small_size, 8);
	strcpy(char_string, "0");
	display_string(char_string, 
		       (int) (W->x1 + space*i), W->y2 - small_size);
	break;
      case (17):
	set_font("helv", small_size, 8);
	strcpy(char_string, "9");
	display_string(char_string, 
		       (int) (W->x1 + space*i), W->y2 - small_size);
	break;
	/* the long stripes */
      case (2):
      case (9):
      case (15):
      case (16):
      case (3):
	if (i == 3) 
	  number = 7;
	else if (i == 15) 
	  number = 4;
	else
	  number = 6;
	draw_num(W->x1 + space*i, (float)W->y1 + space*0.5, 
		 W->x1 + space*i + space*0.8, 
		 (float)W->y2 - font_size*0.5, number);
	break;
	/* stripes with numbers */
      default:
	sprintf(char_string,"%c", string[count]);
	sscanf(char_string, "%d", &number);
	count++;

	draw_num(W->x1 + space*i, (float)W->y1 + space*0.5,
		 W->x1 + space*i + space*0.8, 
		 (float)W->y2 - font_size, number);
	set_font("helv", font_size, 8);
	display_string(char_string, 
		       (int) (W->x1 + space*i), W->y2 - font_size);
	break;
      }
      
    }
    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(screen);
    break;
  default:
    printf("Unknown message: %d\n", id);
    break;
  }
  return(0);
}




draw_num(x1, y1, x2, y2, num)
float x1, y1, x2, y2;
int num;
{
  switch (num) {
  case (0):
    stripe(x1, y1, x2, y2, THIN, 0);
    stripe(x1, y1, x2, y2, THIN, 5);
    break;
  case (1):
    stripe(x1, y1, x2, y2, THIN, 0);
    stripe(x1, y1, x2, y2, MEDIUM, 2);
    stripe(x1, y1, x2, y2, MEDIUM, 6);
    break;
  case (2):
    stripe(x1, y1, x2, y2, THIN, 0);
    stripe(x1, y1, x2, y2, MEDIUM, 5);
    break;
  case (3):
    stripe(x1, y1, x2, y2, MEDIUM, 0);
    stripe(x1, y1, x2, y2, THICK, 4);
    break;
  case (4):
    stripe(x1, y1, x2, y2, THICK, 0);
    stripe(x1, y1, x2, y2, MEDIUM, 7);
    break;
  case (5):
    stripe(x1, y1, x2, y2, MEDIUM, 0);
    stripe(x1, y1, x2, y2, MEDIUM, 7);
    break;
  case (6):
    stripe(x1, y1, x2, y2, MEDIUM, 0);
    stripe(x1, y1, x2, y2, MEDIUM, 4);
    break;
  case (7):
    stripe(x1, y1, x2, y2, THICK, 0);
    stripe(x1, y1, x2, y2, THIN, 7);
    break;
  case (8):
    stripe(x1, y1, x2, y2, THIN, 0);
    stripe(x1, y1, x2, y2, THICK, 4);
    break;
  case (9):
    stripe(x1, y1, x2, y2, MEDIUM, 0);
    stripe(x1, y1, x2, y2, THICK, 4);
    break;
  default:
    aa_move(x1 + 0.5*(x2-x1), y1, (x2-x1));
    aa_draw(x1 + 0.5*(x2-x1), y2, (x2-x1));
    aa_done();
    break;
  }
}



stripe(x1, y1, x2, y2, wide, pos)
     float x1, y1, x2, y2;
     int wide, pos;
{
  float wd, line_thick = 0;
  
  wd = x2 - x1;
  
  switch (wide) {
  case (THIN):
    line_thick = wd*0.15;
    break;
  case (MEDIUM):
    line_thick = wd*0.3;
    break;
  case (THICK):
    line_thick = wd*0.6;
    break;
  }

  aa_move(x1 + pos*0.1*wd + 0.5*line_thick, y1, line_thick);
  aa_draw(x1 + pos*0.1*wd + 0.5*line_thick, y2, line_thick);
  aa_done();
}

