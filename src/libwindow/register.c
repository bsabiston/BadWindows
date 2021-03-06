#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>

struct register_struct
{
  int x, y;
  char *font;
  int size;
  int bits;
  int red, green, blue, t;
  int kind;
  char *num;
};

/* buttons that let you change values.

   W is the window to be afflicted
   if do = 0 then only the draw function is changed
   if do = 1 then the register do function is also added.
   num is the address of the variable
   kind INT (0) means that num is an int pointer, FLOAT (1) means float
   the rest is font information */



Register(W, doflag, num, kind, x, y, font, size, bits, red, green, blue, t)     /* v 1.0b */
     struct Window *W;
     int kind, x, y, size, bits, red, green, blue, t, doflag;
     char *font, *num;
{
  struct register_struct *r;
  int Register_Commands();

  r = (struct register_struct *)malloc(sizeof(struct register_struct));
  r->num = num;
  r->kind = kind;
  r->x = x;
  r->y = y;
  r->font = font;
  r->size = size;
  r->bits = bits;
  r->red = red;
  r->green = green;
  r->blue = blue;
  r->t = t;
  
  AttachCommand(W, DRAW, Register_Commands, r);
  AttachCommand(W, NEW_NUMBER, Register_Commands, r);
  AttachCommand(W, UPDATE, Register_Commands, r);
  AttachCommand(W, CHANGE_REGISTER_FONT_COLOR,Register_Commands, r);
  if (doflag) AttachCommand(W, DO, Register_Commands, r);
}



Register_Commands(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct register_struct *r;
  struct clipstruct *cstruct;
  struct pickstruct *pick;
  char string[20], c, C[2], *tempnum;
  int *inum, done = 0, charnum = 0, pos[20], i, len[20];
  int *colors;         /* Added by Ben Dubrovsky */
  float *fnum, f;
  int oldRX;			/* *DKY-23Nov90* */

  r = (struct register_struct *)stuff;
  if (r->kind == FLOAT) fnum = (float *)r->num;
  else inum = (int *)r->num;

  switch(id) {
    case(CHANGE_REGISTER_FONT_COLOR):
      colors = (int *)data;	/* I changed this to take an *int, 12/5/89, dsmall */
      r->red = (colors[0]);
      r->green = (colors[1]);
      r->blue = (colors[2]);
      break;

    case(NEW_NUMBER): r->num = data;
    break;
    case(UPDATE): UpdateWin(W);
    break;
    case(DRAW):
      if (r->num) {
	cstruct = (struct clipstruct *)data;

	if (r->kind) sprintf(string, "%5.2f", *fnum);
	else sprintf(string, "%d", *inum);

	lockdev(W->display->fildes);
	set_font(r->font, r->size, r->bits);
	set_monitor(W->display->bits, W->display->fildes);
	set_font_color(r->red, r->green, r->blue, r->t);
	set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
	
	if( r->x >= 0)
	  display_string(string, W->x1+r->x, W->y1+r->y);
	else {			/* if X is a negative value, it'll be offset from right edge of window -- *DKY-23Nov90* */
	  int width;
	  width = (int)string_width( string);
	  display_string( string, W->x2 - width + r->x, W->y1 + r->y);
	}
	unlockdev(W->display->fildes);
      }

    break;

    case(DO):
      pick = (struct pickstruct *)data;

    if (r->num) {
      if (pick->button == JUSTDOWN)
      {
	if( r->x < 0) {
	  /* We move r->x so it's positive so we can type values in and have them appear in the right place.
	   * This should be a bit smarter about where to start the cursor so it doesn't overlap text that might be* in the window.   *DKY-23Nov90*
	   */
	  oldRX = r->x;
	  r->x = 2*(0 - r->x);
	}
	else oldRX = NULL;

	set_font(r->font, r->size, r->bits);
	set_monitor(W->display->bits, W->display->fildes);
	set_font_color(r->red, r->green, r->blue, r->t);
	set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);

	tempnum = r->num;
	if (r->kind) f = *fnum;
	else i = *inum;
	r->num = NULL;

	UpdateWin(W);		/* clean slate */
	string[0] = string[1] = 0;
	pos[0] = 0;
	len[0] = 0;
        C[0] = C[1] = 0;
	charnum = done = 0;

	drawing_mode(W->display->fildes, 6);
	interior_style(W->display->fildes, INT_SOLID, FALSE);
	fill_color(W->display->fildes, 1.0, 1.0, 1.0);
	rectangle(W->display->fildes, (float)W->x1+r->x, (float)(W->y1+r->y), (float)(W->x1+r->x+2), (float)(W->y2-r->y));
	make_picture_current(W->display->fildes);
	drawing_mode(W->display->fildes, 3);

	while (!done)		/* read characters until you get a return */
	  {
	    while ((c = getchar()) == -1);
	    while (( getchar()) != -1);

	    switch (c)
	      {
	      case '\b':	/* backspace */
		if (charnum)
		  {
		    int tab, dif, ytab;

		    tab  = dif = pos[charnum] + W->x1+r->x;
		    ytab = W->y1+3;

		    string[charnum] = 0;
		    string[charnum-1] = 0; /* *DKY- 8Jun91* This is to fix the backspace bug.  Before erase worked wrong. */
		    charnum--;
		    tab -= len[charnum];

		    ShowWindow(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);
		    ShowTops(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);

		    dif = pos[charnum];
		    drawing_mode(W->display->fildes, 6);
		    interior_style(W->display->fildes, INT_SOLID, FALSE);
		    fill_color(W->display->fildes, 1.0, 1.0, 1.0);
		    rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
			      (float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
		    make_picture_current(W->display->fildes);
		    drawing_mode(W->display->fildes, 3);
		  }

		break;

	      case (13):	/* Return */
	      case '\n':
		done = 1;
		r->num = tempnum;

		if (r->kind) sscanf(string, "%f", r->num);
		else sscanf(string, "%d", r->num);
		if( oldRX)		/* *DKY-23Nov90* */
		  r->x = oldRX;
		UpdateWin(W);
		break;

	      default:
		if (c >= 32)
		  {
		    int tab, dif, ytab;

		    if ((charnum < 19)&&(pos[charnum]< W->width-r->x-15))
		      {
			tab  = dif = pos[charnum] + W->x1+r->x;
			ytab = W->y1+r->y;

			string[charnum] = c;
			string[charnum+1] = 0;

			drawing_mode(W->display->fildes, 6);
			interior_style(W->display->fildes, INT_SOLID, FALSE);
			fill_color(W->display->fildes, 1.0, 1.0, 1.0);
			rectangle(W->display->fildes, (float)tab, (float)(W->y1+r->y), (float)(tab+2), (float)(W->y2-r->y));
			make_picture_current(W->display->fildes);
			drawing_mode(W->display->fildes, 3);
			make_picture_current(W->display->fildes);

			C[0] = c; /* super-kluge way of getting character width */
			lockdev(W->display->fildes);
			display_string(C, tab, ytab);
			unlockdev(W->display->fildes);
			tab = string_width(C);

			len[charnum] = tab;
			charnum++;
			dif = pos[charnum] = pos[charnum-1]+tab;

			drawing_mode(W->display->fildes, 6);
			interior_style(W->display->fildes, INT_SOLID, FALSE);
			fill_color(W->display->fildes, 1.0, 1.0, 1.0);
			rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
				  (float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
			make_picture_current(W->display->fildes);
			drawing_mode(W->display->fildes, 3);

			ShowTops(W, W->x1, W->y1, W->x2, W->y2);
		      }
		  }
		break;
	      }
	  }
      }
    }

    break;
    }

  return(0);
}



/*********************************************
  STRING REGISTER     *DKY-25Apr90*

  This works just like Register but for Strings.
**********************************************/
  
struct string_register_struct
{
  int x, y;
  char *font;
  int size;
  int bits;
  int red, green, blue, t;
  char **string;
};

StringRegister(W, doflag, string, x, y, font, size, bits, red, green, blue, t)     /* v 1.0b */
     struct Window *W;
     int x, y, size, bits, red, green, blue, t, doflag;
     char *font, **string;
{
  struct string_register_struct *r;
  int String_Register_Commands();

  r = (struct string_register_struct *)malloc(sizeof(struct string_register_struct));
  r->string = string;
  r->x = x;
  r->y = y;
  r->font = font;
  r->size = size;
  r->bits = bits;
  r->red = red;
  r->green = green;
  r->blue = blue;
  r->t = t;
  
  AttachCommand(W, DRAW, String_Register_Commands, r);
  AttachCommand(W, NEW_NUMBER, String_Register_Commands, r);
  AttachCommand(W, UPDATE, String_Register_Commands, r);
  if (doflag) AttachCommand(W, DO, String_Register_Commands, r);
}



String_Register_Commands(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct string_register_struct *r;
  struct clipstruct *cstruct;
  struct pickstruct *pick;
  char string[200], c, C[2], *tempnum;
  int *inum, done = 0, charnum = 0, pos[200], i, len[200];
  float *fnum, f;

  r = (struct string_register_struct *)stuff;

  switch(id)
    {
    case (NEW_NUMBER):
      r->string = (char **)data;
      break;
    case (UPDATE):
      UpdateWin(W);
      break;
    case (DRAW):
      if (*(r->string)) {
	cstruct = (struct clipstruct *)data;

	sprintf(string, "%s", *(r->string));

	lockdev(W->display->fildes);
	set_font(r->font, r->size, r->bits);
	set_monitor(W->display->bits, W->display->fildes);
	set_font_color(r->red, r->green, r->blue, r->t);
	set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
	display_string(string, W->x1+r->x, W->y1+r->y);
	unlockdev(W->display->fildes);
      }

      break;

    case (DO):
      pick = (struct pickstruct *)data;

      if ((pick->button == JUSTDOWN) && (r->string))
	{
	  set_font(r->font, r->size, r->bits);
	  set_monitor(W->display->bits, W->display->fildes);
	  set_font_color(r->red, r->green, r->blue, r->t);
	  set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);

	  *(r->string) = NULL;

	  UpdateWin(W);		/* clean slate */
	  string[0] = string[1] = 0;
	  pos[0] = 0;
	  len[0] = 0;
	  C[0] = C[1] = 0;
	  charnum = done = 0;

	  drawing_mode(W->display->fildes, 6);
	  interior_style(W->display->fildes, INT_SOLID, FALSE);
	  fill_color(W->display->fildes, 1.0, 1.0, 1.0);
	  rectangle(W->display->fildes, (float)W->x1+r->x, (float)(W->y1+r->y), (float)(W->x1+r->x+2), (float)(W->y2-r->y));
	  make_picture_current(W->display->fildes);
	  drawing_mode(W->display->fildes, 3);

	  while (!done)		/* read characters until you get a return */
	    {
	      while ((c = getchar()) == -1);
	      while (( getchar()) != -1);

	      switch (c)
		{
		case '\b':	/* backspace */
		  if (charnum)
		    {
		      int tab, dif, ytab;

		      tab  = dif = pos[charnum] + W->x1+r->x;
		      ytab = W->y1+3;

		      string[charnum] = 0;
		      charnum--;
		      tab -= len[charnum];

		      ShowWindow(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);
		      ShowTops(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);

		      dif = pos[charnum];
		      drawing_mode(W->display->fildes, 6);
		      interior_style(W->display->fildes, INT_SOLID, FALSE);
		      fill_color(W->display->fildes, 1.0, 1.0, 1.0);
		      rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
				(float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
		      make_picture_current(W->display->fildes);
		      drawing_mode(W->display->fildes, 3);
		    }

		  break;

		case (13):	/* Return */
		case '\n':
		  done = 1;

		  /* we'd like to free what's previously stored in r->string, but if it's a ""-type string it'll crash */
		  *(r->string) = (char *)CopyString( string);
		  UpdateWin(W);
		  break;

		default:
		  if (c >= 32)
		    {
		      int tab, dif, ytab;

/*		      if ((charnum < 19)&&(pos[charnum]< W->width-r->x-15)) */
		      if ((pos[charnum]< W->width-r->x-15))
			{
			  tab  = dif = pos[charnum] + W->x1+r->x;
			  ytab = W->y1+r->y;

			  string[charnum] = c;
			  string[charnum+1] = 0;

			  drawing_mode(W->display->fildes, 6);
			  interior_style(W->display->fildes, INT_SOLID, FALSE);
			  fill_color(W->display->fildes, 1.0, 1.0, 1.0);
			  rectangle(W->display->fildes, (float)tab, (float)(W->y1+r->y), (float)(tab+2), (float)(W->y2-r->y));
			  make_picture_current(W->display->fildes);
			  drawing_mode(W->display->fildes, 3);

			  C[0] = c; /* super-kluge way of getting character width */
			  lockdev(W->display->fildes);
			  display_string(C, tab, ytab);
			  unlockdev(W->display->fildes);
			  tab = string_width(C);

			  len[charnum] = tab;
			  charnum++;
			  dif = pos[charnum] = pos[charnum-1]+tab;

			  drawing_mode(W->display->fildes, 6);
			  interior_style(W->display->fildes, INT_SOLID, FALSE);
			  fill_color(W->display->fildes, 1.0, 1.0, 1.0);
			  rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
				    (float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
			  make_picture_current(W->display->fildes);
			  drawing_mode(W->display->fildes, 3);

			  ShowTops(W, W->x1, W->y1, W->x2, W->y2);
/*
 * WHO PUT THE FOLLOWING CODE HERE?!  IT DIDN'T WORK, IT CAN'T WORK.  Don't modify system code and leave it in a bad state!
 * *DKY- 5Aug90*
 */
/*
			  if (r->kind == 0)
			    {
			      done = 1;
			      c -= 33;
			    }
*/
			  
			}
		    }
		  break;
		}
	    }
	}

      break;
    }
  return(0);
}


/* toggles the value of the supplied pointer num from TRUE to FALSE */

Toggler(W,num,mask)     /* v 1.0b */
struct Window *W;
int *num, mask;
{
  int ToggleWin();
  struct toggle_struct *parms;

  parms = (struct toggle_struct *)malloc(sizeof(struct toggle_struct));
  parms->mask = mask;
  parms->num = num;

  AttachCommand(W, DO, ToggleWin, (char *)parms);
}



ToggleWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct toggle_struct *parms;
  int flag = 1;

  parms = (struct toggle_struct *)stuff;
  if (id == DO) {
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
    if (*(parms->num) == TRUE)
      *(parms->num) = FALSE;
    else
      *(parms->num) = TRUE;
  }
  return(0);
}
