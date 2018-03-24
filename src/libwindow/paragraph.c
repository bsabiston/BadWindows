#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>


struct wordmakestruct {
  /*** used in maker ***/
  int x1, y1, x2, y2;
  int wordx1, wordy1, wordx2, wordy2;
  char *test;
  int number;
};


/*  SUGGESTION:  What about adding the ability to center, fill, or right-justify paragraphs?
 */
/******* good idea... I'll do that next time I have time to dig in the code... --Tim */

ParagraphWin(W, para, offx, offy, font, size, bits, red, green, blue, t)
     struct Window *W;
     char *font, *para;
     int size, bits, red, green, blue, t, offx, offy;
{
  struct parastruct *params;
  int DrawAParagraph();

  params = (struct parastruct *) malloc(sizeof(struct parastruct));
  params->font = font;
  params->para = para;
  params->size = size;
  params->bits = bits;
  params->offx = offx;
  params->offy = offy;
  params->red = red;
  params->green = green;
  params->blue = blue;
  params->t = t;
  params->top = 0;
  params->leading = 0;

  AttachCommand(W, DRAW, DrawAParagraph, (char *)params);
  AttachCommand(W, ATTRIBUTES, DrawAParagraph, (char *)params);
  AttachCommand(W, CHANGECOLOR, DrawAParagraph, (char *)params);
  AttachCommand(W, CHANGECOLOR_NOINSTALL, DrawAParagraph, (char *)params);
  AttachCommand(W, CHANGETRANS, DrawAParagraph, (char *)params);
  AttachCommand(W, CHANGEFONT, DrawAParagraph, (char *)params);
  AttachCommand(W, CHANGESTRING, DrawAParagraph, (char *)params);
  AttachCommand(W, CHANGELEADING, DrawAParagraph, (char *)params);
  AttachCommand(W, GETWORDCOORDS, DrawAParagraph, (char *)params);
  AttachCommand(W, SCROLLUP, DrawAParagraph, (char *)params);
  AttachCommand(W, SCROLLDOWN, DrawAParagraph, (char *)params);
  AttachCommand(W, UPDATE, DrawAParagraph, (char *)params);
}



DrawAParagraph(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *stuff, *data;
{
  struct parastruct *mstruct, *newstruct;
  struct clipstruct *cstruct;
  struct wordmakestruct *wmstruct;
  int screen, cx1, cx2, cy1, cy2;
  int blocktop, blockheight;
  int *colors, *trans, success, *lead;
  int vertical_shift;
  int was_open = FALSE;
  char line[100];
  FILE *fp;

  if (id==DRAW)
    {
      mstruct = (struct parastruct *)stuff;
      cstruct = (struct clipstruct *)data;

      if ((fp=fopen(mstruct->para, "r"))==0) {
	printf("ParagraphWin:  Error opening file '%s'.  Creating...\n", mstruct->para);
	sprintf(line, "touch %s", mstruct->para);
	system (line);
	if ((fp=fopen(mstruct->para, "r"))==0)
	  printf("ParagraphWin:  Error creating file '%s'.  Creating...\n", mstruct->para);
      }

      set_font(mstruct->font, mstruct->size, mstruct->bits);
      set_leading(mstruct->leading);
      set_monitor(W->display->bits, W->display->fildes);
      set_font_color(mstruct->red, mstruct->green, mstruct->blue, mstruct->t);
      set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
      make_picture_current(W->display->fildes);

      display_wrap_clip_file(fp,
			     W->x1+mstruct->offx,
			     W->y1+mstruct->offy
			     -(int)((float)mstruct->size/4320.0*1020.0)
			     -mstruct->top,
			     W->x2, W->y2);
      set_leading(0);

      fclose(fp);
    }

/********************************

     +-----------------------+
     | new stuff drawn here  |
     +-----------------------+
     |                       |
     |         ||            |
     |         ||            |
     |        _||_           |
     |        \  /           |
     |         \/            |  to see earlier text
     +-----------------------+

  *******************************/

  else if (id == SCROLLUP)					      /* call scrollup with a negative number to scroll by lines */
    {
      mstruct = (struct parastruct *)stuff;

      if ((vertical_shift = (int)data) < 0)
	vertical_shift *= -(mstruct->size + mstruct->leading);	      /* scroll by lines */
      if (vertical_shift > mstruct->top) vertical_shift = mstruct->top; /* don't go past top */
      mstruct->top -= vertical_shift;				      /* shift */

      set_font(mstruct->font, mstruct->size, mstruct->bits);
      blocktop = W->y1 + mstruct->offy ;
      blockheight = W->y2 - blocktop - vertical_shift ;
      dcblock_move(W->display->fildes, W->x1, blocktop,
		   W->x2-W->x1, blockheight,
		   W->x1,  blocktop + vertical_shift);
      AreaUpdateWin(W, W->x1, blocktop,
		    W->x2, blocktop+vertical_shift);
    }

/******************************** in order to see later text

before:

     +-----------------------+  W->y1+mstruct->offy
     :  discarded            :
     + - - - - - - - - - - - +  W->y1+mstruct->offy+vertical_shift   ---
     |                       |  			              ^
     |        /\    moved    |				              |
     |       /  \            |
     |        ||             |      			          W->y2 - W->y1 -mstruct->offy - vertical shift
     |        ||             |
     |        ||             |	                                     |
     +-----------------------+  W->y2  . . . . . . . . ............__v




after:

     +-----------------------+  W->y1+mstruct->offy
     |        /\             |
     |       /  \            |
     |        ||    moved    |
     |        ||             |
     |        ||             |
     |                       |
     + - - - - - - - - - - - +  W->y2-vertical shift
     | new stuff drawn here  |
     +-----------------------+  W->y2

  *******************************/
  else if (id == SCROLLDOWN)
    {

      mstruct = (struct parastruct *)stuff;
      if ((vertical_shift = (int)data) < 0)
	vertical_shift *= -(mstruct->size + mstruct->leading);
      
      mstruct->top += vertical_shift;

      set_font(mstruct->font, mstruct->size, mstruct->bits);


      blocktop = W->y1 + mstruct->offy + vertical_shift;
      blockheight = W->y2 - blocktop;
      dcblock_move(W->display->fildes, W->x1, blocktop,
		   W->x2-W->x1, blockheight,
		   W->x1,  blocktop - vertical_shift);
      AreaUpdateWin(W, W->x1, W->y2-vertical_shift-mstruct->size,
		    W->x2,  W->y2);

    }
  else if (id == GETWORDCOORDS)
    {
      mstruct = (struct parastruct *)stuff;
      wmstruct = (struct wordmakestruct *)data;

      if ((fp=fopen(mstruct->para, "r"))==0) {
	printf("ParagraphWin:  Error opening file '%s'.  Creating...\n", mstruct->para);
	sprintf(line, "touch %s", mstruct->para);
	system (line);
	if ((fp=fopen(mstruct->para, "r"))==0)
	  printf("ParagraphWin:  Error creating file '%s'.  Creating...\n", mstruct->para);
      }

      set_font(mstruct->font, mstruct->size, mstruct->bits);
      word_rect_from_wrapped_file(fp, W->x1+mstruct->offx, W->y1+mstruct->offy,
				  W->x2, W->y2, wmstruct->test, wmstruct->number,
				  &(wmstruct->wordx1), &(wmstruct->wordy1),
				  &(wmstruct->wordx2), &(wmstruct->wordy2));

      fclose(fp);
    }
  else if (id == ATTRIBUTES)
    {
      mstruct = (struct parastruct *)stuff;
      mstruct->para = data;
    }
  else if (id == CHANGESTRING)
    {
      mstruct = (struct parastruct *)stuff;
      mstruct->para = data;
      mstruct->top = 0;
      UpdateWin(W);
    }
  else if (id == CHANGECOLOR)
    {
      if (W->stat) {CloseWindow(W); was_open = TRUE;}
      mstruct = (struct parastruct *)stuff;
      colors = (int *)data;
      mstruct->red = colors[0];
      mstruct->green = colors[1];
      mstruct->blue = colors[2];
      if (was_open) OpenWindow(W);
    }
  else if (id == CHANGECOLOR_NOINSTALL)
    {
      mstruct = (struct parastruct *)stuff;
      colors = (int *)data;
      mstruct->red = colors[0];
      mstruct->green = colors[1];
      mstruct->blue = colors[2];
    }
  else if (id == CHANGETRANS)
    {
      mstruct = (struct parastruct *)stuff;
      trans = (int *)data;
      mstruct->t = *trans;
    }
  else if (id == CHANGELEADING)
    {
      mstruct = (struct parastruct *)stuff;
      lead = (int *)data;
      mstruct->leading = *lead;
    }
  else if (id == CHANGEFONT)
    {
      mstruct = (struct parastruct *)stuff;
      newstruct = (struct parastruct *)data;
      mstruct->font = newstruct->font;
      mstruct->size = newstruct->size;
      mstruct->bits = newstruct->bits;
    }
  else if (id == UPDATE)
      UpdateWin(W);
}



WordMaker(W, x1, y1, x2, y2, test, number)     /* v 1.0b */
     struct Window *W;
     int x1, y1, x2, y2;
     char *test;
     int number;
{
  int WordMakeWin();
  struct wordmakestruct *params;
  char *temp;

  params = (struct wordmakestruct *)malloc(sizeof(struct wordmakestruct));
  params->x1 = x1;
  params->y1 = y1;
  params->x2 = x2;
  params->y2 = y2;

  temp = (char *)malloc(sizeof(char)*strlen(test));
  strcpy(temp, test);
  params->test = temp;
  params->number = number;

  AttachCommand(W, MAKE, WordMakeWin, (char *)params);
}


WordMakeWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct wordmakestruct *param;
  int relx, rely, width, height;

  param = (struct wordmakestruct *)stuff;

  SendMessage(W->parent, GETWORDCOORDS, (char *)param);

  relx = W->relx;
  rely = W->rely;
  width = W->width;
  height = W->height;

  if (param->x1 != NOMAKE)
    relx = (param->wordx1 - W->parent->x1) + param->x1;

  if (param->y1 != NOMAKE)
    rely = (param->wordy1 - W->parent->y1) + param->y1;

  if (param->x2 != NOMAKE)
    width = (param->wordx2 - W->parent->x1 - relx) + param->x2;

  if (param->y2 != NOMAKE)
    height = (param->wordy2 - W->parent->y1 - rely) + param->y2;

  TransformCoords(W, relx, rely, width, height);
}


