/*** New Echo Routines for the Window System ***/

#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

static struct OutDev *screen[2] = {NULL, NULL}, *oldscreen;
static int E_maxwide[2] = {NULL, NULL}, F_maxwide;
static int E_maxtall[2] = {NULL, NULL}, F_maxtall;
static int E_sourcex[2], E_sourcey[2], F_sourcex, F_sourcey;
static int E_maskx[2], E_masky[2], F_maskx, F_masky;
static int E_backx[2], E_backy[2], F_backx, F_backy;
static int E_finalx[2], E_finaly[2], F_finalx, F_finaly;
static int E_wide[2], E_tall[2], F_wide, F_tall;
static int E_stat[2] = {NULL, NULL}, E_x[2], E_y[2], E_oldx[2], E_oldy[2], E_hotdx[2], E_hotdy[2];
static struct curstruct *E_cursor[2];



ReserveCursorSpace(O, x1, y1, x2, y2)     /* v 1.0b */
     struct OutDev *O;
     int x1, y1, x2, y2;
{
  int i, orientation;

  if (!screen[0]) i = 0;     /*** if one screen's taken, fill in the other ***/
  else i = 1;

  orientation =  (x2-x1 > y2-y1);     /*** find out whether to divide up horizontally or vertically ***/
  screen[i] = O;
  oldscreen = O;
  if (!orientation)
    {
      E_maxwide[i] = x2-x1+1;
      E_maxtall[i] = (y2-y1+1)/4;
      if (E_maxtall[i] < 1) printf("ERROR not enough cursor space.\n");
      E_sourcex[i] = E_maskx[i] = E_backx[i] = E_finalx[i] = x1;
      E_sourcey[i] = y1;
      E_masky[i] = E_sourcey[i]+E_maxtall[i];
      E_backy[i] = E_masky[i]+E_maxtall[i];
      E_finaly[i] = E_backy[i]+E_maxtall[i];
    }
  else
    {
      E_maxwide[i] = (x2-x1+1)/4;
      E_maxtall[i] = y2-y1+1;
      if (E_maxwide[i] < 1) printf("ERROR not enough cursor space.\n");
      E_sourcey[i] = E_masky[i] = E_backy[i] = E_finaly[i] = y1;
      E_sourcex[i] = x1;
      E_maskx[i] = E_sourcex[i]+E_maxwide[i];
      E_backx[i] = E_maskx[i]+E_maxwide[i];
      E_finalx[i] = E_backx[i]+E_maxwide[i];
    }
}



InstallCursor(O, cursor)     /* v 1.0b */
     struct OutDev *O;
     struct curstruct *cursor;
{
  int x, y, dx, dy, bits, i = -1, color;
  gescape_arg arg1,arg2;
  unsigned char *spos, *buffer, *control;
  int *ibuf;

  buffer = O->buffer;
  ibuf = (int *)O->buffer;
  control = O->control;
  bits = O->bits;

  if (O == screen[0]) i = 0;
  else if (O == screen[1]) i = 1;
  else printf("ERROR: screen value not known\n");

  if ((i>=0)&&(cursor->dx > E_maxwide[i])||(cursor->dy > E_maxtall[i]))
    printf("ERROR: InstallCursor() - Not enough space.\n                       - Your cursor is probably an illegal value\n");
  else
    {
      dx = cursor->dx;
      dy = cursor->dy;
      spos = cursor->source;
      E_cursor[i]  = cursor;
      E_wide[i] = cursor->dx;
      E_tall[i] = cursor->dy;
      E_hotdx[i] = cursor->hotdx;
      E_hotdy[i] = cursor->hotdy;

      fill_color(O->fildes, 0.0, 0.0, 0.0);
      drawing_mode(O->fildes, 3);
      interior_style(O->fildes, INT_SOLID, FALSE);
      rectangle(O->fildes, (float)E_sourcex[i], (float)E_sourcey[i],
		           (float)(E_sourcex[i]+dx-1), (float)(E_sourcey[i]+dy-1));
      make_picture_current(O->fildes);

      control[0x40bf] = 7;

      for (x = 0; x< dx; x++)
	for (y = 0; y< dy; y++)
	  {
	    if (*(spos+3*(x+y*dx)) == cursor->rule)
	      {
		if (bits == 24)
		  {
		    control[0x40bf] = 4;
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = 0;
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*2048) = 255;
		    control[0x40bf] = 2;
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = 0;
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*2048) = 255;
		    control[0x40bf] = 1;
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = 0;
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*2048) = 255;
		  }
		else if (bits == 32)
		  {
		    *(ibuf+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = 0;
		    *(ibuf+E_maskx[i]+x+(E_masky[i]+y)*2048) = 0x00ffffff;
		  }
		else if (bits == 4)
		  {
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*1024) = 0;
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*1024) = 15;
		  }

	      }

	    else
	      {
		if (bits == 24)
		  {
		    control[0x40bf] = 4;
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = *(cursor->source+3*(x+y*cursor->dx));
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*2048) = 0;
		    control[0x40bf] = 2;
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = *(cursor->source+3*(x+y*cursor->dx)+1);
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*2048) = 0;
		    control[0x40bf] = 1;
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = *(cursor->source+3*(x+y*cursor->dx)+2);
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*2048) = 0;
		  }
		else if (bits == 32)
		  {
		    color = *(cursor->source+3*(x+y*cursor->dx))<<16 |
		      (*(cursor->source+3*(x+y*cursor->dx)+1))<<8 |
			(*(cursor->source+3*(x+y*cursor->dx)+2));
		    *(ibuf+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = color;
		    *(ibuf+E_maskx[i]+x+(E_masky[i]+y)*2048) = 0;
		  }
		else if (bits == 4)
		  {
		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*1024) = (*(cursor->source+3*(x+y*cursor->dx))) >>4;
		    *(buffer+E_maskx[i]+x+(E_masky[i]+y)*1024) = 0;
		  }
	      }
	  }

      if (bits == 24) control[0x40bf] = 7;
    }
}



/*
  ViewCursorSpace(screen, x, y)
{
  drawing_mode(screen, 3);
  dcblock_move(screen, E_sourcex[i], E_sourcey[i], E_wide[i], E_maxtall[i]*4, x, y);
  make_picture_current(screen);
}
*/



UpdateEcho(x, y, fildes, echo)     /* v 1.0b */
     int x, y;
     struct OutDev *fildes;
     struct curstruct *echo;
{
  int display, i;

  if (fildes == screen[0]) i = 0;
  else if (fildes == screen[1]) i = 1;
  else printf("ERROR: UpdateEcho() - screen value not known\n");

  if (oldscreen != fildes)
    {
      EchoOff(oldscreen, 1);
      oldscreen = screen[i];
    }

  display = fildes->fildes;
  if (E_cursor[i] != echo) ChangeEcho(echo, fildes);
  if (!E_stat[i]) EchoOn(x, y, fildes);
  else if ((x!=E_oldx[i]) || (y!=E_oldy[i]))
    {
      await_retrace(display);
      fildes->control [0x40c3] = 2;
      fildes->control[0x40bf] = 7;
      dcblock_move(display, E_backx[i], E_backy[i], E_wide[i], E_tall[i], E_oldx[i]-E_hotdx[i], E_oldy[i]-E_hotdy[i]);
      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_backx[i], E_backy[i]);
      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);

      /* draw shape */
      drawing_mode(display, 1); /* AND */
      dcblock_move(display, E_maskx[i], E_masky[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);
      drawing_mode(display, 7); /* OR */
      dcblock_move(display, E_sourcex[i], E_sourcey[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);
      drawing_mode(display, 3); /* NORMAL */
      dcblock_move(display, E_finalx[i], E_finaly[i], E_wide[i], E_tall[i], x-E_hotdx[i], y-E_hotdy[i]);

      E_oldx[i] = E_lastx = x; E_oldy[i] = E_lasty = y;
    }
  make_picture_current(display);
}



EchoOff(fildes, now)     /* v 1.0b */
     struct OutDev *fildes;
     int now;
{
  int i;

  if (fildes == screen[0]) i = 0;
  else if (fildes == screen[1]) i = 1;
  else printf("ERROR: screen value not known\n");

  if (E_stat[i])
    {
      E_stat[i] = 0;
      fildes->control[0x40bf] = 7;
      fildes->control [0x40c3] = 2;         
      dcblock_move(fildes->fildes, E_backx[i], E_backy[i], E_wide[i], E_tall[i],
		                   E_oldx[i]-E_hotdx[i], E_oldy[i]-E_hotdy[i]);

      if (now) make_picture_current(fildes->fildes);
    }
}



EchoOn(x, y, fildes)     /* v 1.0b */
     int x, y;
     struct OutDev *fildes;
{
  unsigned char *control;
  int display, i;

  if (fildes == screen[0]) i = 0;
  else if (fildes == screen[1]) i = 1;
  else printf("ERROR: EchoOn() - screen value not known\n");

  if (oldscreen != fildes)
    {
      EchoOff(oldscreen, 1);
      oldscreen = fildes;
    }

  
  if (x == 123456) {	/* *TIM-19Apr91* */
    x = E_oldx[i];
    y = E_oldy[i];
  }
  
  display = fildes->fildes;
  if (!E_stat[i])
    {
      E_stat[i] = 1;
      fildes->control [0x40c3] = 2; 
      fildes->control[0x40bf] = 7;
      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_backx[i], E_backy[i]);
      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);

      drawing_mode(display, 1); /* AND */
      dcblock_move(display, E_maskx[i], E_masky[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);
      drawing_mode(display, 7); /* OR */
      dcblock_move(display, E_sourcex[i], E_sourcey[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);
      drawing_mode(display, 3); /* NORMAL */
      dcblock_move(display, E_finalx[i], E_finaly[i], E_wide[i], E_tall[i], x-E_hotdx[i], y-E_hotdy[i]);

      E_oldx[i] = E_lastx = x; E_oldy[i] = E_lasty = y;
    }
}



ChangeEcho(echo, fildes)     /* v 1.0b */
     struct curstruct *echo;
     struct OutDev *fildes;
{
  int i;

  if (fildes == screen[0]) i = 0;
  else if (fildes == screen[1]) i = 1;
  else printf("ERROR: ChangeEcho() - screen value not known\n");

  if (oldscreen != fildes)
    {
      EchoOff(oldscreen, 1);
      oldscreen = fildes;
    }

  if (E_stat[i])
    {
      EchoOff(fildes, 0);
      E_cursor[i] = echo;
      InstallCursor(fildes, echo);
      EchoOn(E_oldx[i], E_oldy[i], fildes);
      return;
    }
  E_cursor[i] = echo;
  InstallCursor(fildes, echo);
}











