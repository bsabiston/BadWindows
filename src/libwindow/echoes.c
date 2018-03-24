#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

/*** New Echo Routines for the Window System ***/
/* These routines are for the brain-damaged CRX24's.  They do not use offscreen memory. */
/* E_lastx and E_lasty are the last cursor position
/* background holds the background for the current cursor.  The malloced size of the space is
   ->w and ->h, the size of the current cursor is ->hotdx and ->hotdy                           */

static struct curstruct *background = NULL, *lastcursor;
static struct OutDev *oldscreen = NULL;
static int E_oldx,E_oldy;



/* old routine used to set space on the offscreen.  */
ReserveCursorSpace(O, x1, y1, x2, y2)
     struct OutDev *O;
     int x1, y1, x2, y2;
{
  int orientation,wide,tall;
  orientation =  (x2-x1 > y2-y1);     /*** find out whether to divide up horizontally or vertically ***/
  if (!orientation) wide = x2-x1+1, tall = (y2-y1+1)/4;
  else wide = (x2-x1+1)/4, tall = y2-y1+1;
  ReserveEchoBackground(wide,tall);
}


/* new cursor space reserve function */
ReserveEchoBackground(w,h)
     int w,h;
{
  if (background)  free(background->source);
  else background = (struct curstruct *)malloc(sizeof(struct curstruct));
  background->dx = w;
  background->dy = h;
  background->id = 0;
  background->source = malloc(w*h*3*3);  /* 3 slots--background, mask, cursor on black */ 
}



InstallCursor(cursor)
     struct curstruct *cursor;
{
  int x, y, dx, dy;
  unsigned char *spos, *back,*mask,*shape;

  if (!background)
    ReserveEchoBackground(cursor->dx,cursor->dy);
  else if ((cursor->dx > background->dx)||(cursor->dy > background->dy))
    ReserveEchoBackground(MAX(cursor->dx,background->dx),MAX(cursor->dy,background->dy));
  
  dx = cursor->dx;
  dy = cursor->dy;
  spos = cursor->source;
  lastcursor  = cursor;
  back = background->source;
  mask = back+dx*dy*3;
  shape = mask+dx*dy*3;

  for (x = 0; x< dx; x++)
    for (y = 0; y< dy; y++)
      {
	if (*(spos+3*(x+y*dx)) == cursor->rule)
	  {
	    *(shape+x+y*dx) = *(shape+x+y*dx+dx*dy) = *(shape+x+y*dx+dx*dy*2) = 0;
	    *(mask+x+y*dx) = *(mask+x+y*dx+dx*dy) = *(mask+x+y*dx+dx*dy*2) = 255;
	  }
	else
	  {
	    *(mask+x+y*dx) = *(mask+x+y*dx+dx*dy) = *(mask+x+y*dx+dx*dy*2) = 0;
	    *(shape+x+y*dx) =  *(spos+3*(x+y*cursor->dx));
	    *(shape+x+y*dx+dx*dy) =  *(spos+3*(x+y*cursor->dx)+1);
	    *(shape+x+y*dx+dx*dy*2) =  *(spos+3*(x+y*cursor->dx)+2);
	  }
      }
}


InstallCursor4(cursor)
     struct curstruct *cursor;
{
  int x, y, dx, dy;
  unsigned char *spos, *back,*mask,*shape;

  if (!background)
    ReserveEchoBackground(cursor->dx,cursor->dy);
  else if ((cursor->dx > background->dx)||(cursor->dy > background->dy))
    ReserveEchoBackground(MAX(cursor->dx,background->dx),MAX(cursor->dy,background->dy));
  
  dx = cursor->dx;
  dy = cursor->dy;
  spos = cursor->source;
  lastcursor  = cursor;
  back = background->source;
  mask = back+dx*dy*3;
  shape = mask+dx*dy*3;

  for (x = 0; x< dx; x++)
    for (y = 0; y< dy; y++)
      {
	if (*(spos+3*(x+y*dx)) == cursor->rule)
	  {
	    *(shape+x+y*dx) = 0;
	    *(mask+x+y*dx) = 255;
	  }
	else
	  {
	    *(mask+x+y*dx) = 0;
/*	    *(shape+x+y*dx) = ((((*spos)+1) >> 6)*25+
			       ((*(spos+1)+1) >> 6)*5+
			       ((*(spos+2)+1) >> 6)) + 16;  */
	    *(shape+x+y*dx) =   ( (((*(spos+3*(x+y*cursor->dx)))>>6)*25) +
				  (((*(spos+3*(x+y*cursor->dx)+1))>>6)*5) +
				  (((*(spos+3*(x+y*cursor->dx)+2))>>6))+16);
	  }
      }
}




UpdateEcho(x, y, fildes, echo) 
     int x, y;
     struct OutDev *fildes;
     struct curstruct *echo;
{
  int display, i,dx,dy, bit24 = 1;

  if ((fildes->bits&BUFTYPE) == CRX8) bit24 = 0;

  if (!lastcursor)
    if (bit24) InstallCursor(echo);
    else InstallCursor4(echo);

  if (!background->id) EchoOn(x, y, fildes);
  else if (oldscreen != fildes)
    {
      EchoOff(oldscreen, 1);
      EchoOn(x, y, fildes);
    }
  else {
    display = fildes->fildes;
    if (lastcursor != echo) ChangeEcho(fildes,echo);
    else if ((x!= E_oldx) || (y!=E_oldy))
      {
	dx = lastcursor->dx;  dy = lastcursor->dy;
	await_retrace(display);
	
	if (bit24) bank_switch(display,2,0);
	dcblock_write(display, E_oldx-lastcursor->hotdx, E_oldy-lastcursor->hotdy, dx, dy, background->source,FALSE);
	dcblock_read(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source,FALSE);
	if (bit24) {
	  bank_switch(display,1,0);
	  dcblock_write(display, E_oldx-lastcursor->hotdx, E_oldy-lastcursor->hotdy, dx, dy, background->source+dx*dy,FALSE);
	  dcblock_read(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy,FALSE);
	  bank_switch(display,0,0);
	  dcblock_write(display, E_oldx-lastcursor->hotdx, E_oldy-lastcursor->hotdy, dx, dy, background->source+dx*dy*2,FALSE);
	  dcblock_read(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+2*dx*dy,FALSE);
	}

	/* draw shape */
	drawing_mode(display, 1); /* AND */
	if (bit24) bank_switch(display,2,0);
	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*3,FALSE);
	if (bit24) {
	  bank_switch(display,1,0);
	  dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*4,FALSE);
	  bank_switch(display,0,0);
	  dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*5,FALSE);
	}

	drawing_mode(display, 7); /* OR */
	if (bit24) bank_switch(display,2,0);
	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*6,FALSE);
	if (bit24) {
	  bank_switch(display,1,0);
	  dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*7,FALSE);
	  bank_switch(display,0,0);
	  dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*8,FALSE);
	}

	drawing_mode(display, 3); /* NORMAL */
	E_oldx = E_lastx = x; E_oldy = E_lasty = y;
	make_picture_current(display);
      }
  }
}


EchoOff(fildes, now) 
     struct OutDev *fildes;
     int now;
{
  int i,w,h,x,y, bit24 = 1;

  if ((fildes->bits&BUFTYPE) == CRX8) bit24 = 0;
  if (fildes != oldscreen) printf("ERROR EchoOff called on the wrong screen!\n");
  else if (background->id) {
    w = lastcursor->dx;
    h = lastcursor->dy;
    x = E_oldx-lastcursor->hotdx;
    y = E_oldy-lastcursor->hotdy;
    if (bit24) bank_switch(fildes->fildes,2,0);
    dcblock_write(fildes->fildes, x,y, w, h, background->source, FALSE);
    if (bit24) {
      bank_switch(fildes->fildes,1,0);
      dcblock_write(fildes->fildes, x,y, w, h, background->source+w*h, FALSE);
      bank_switch(fildes->fildes,0,0);
      dcblock_write(fildes->fildes, x,y, w, h, background->source+w*h*2, FALSE);
    }
    if (now) make_picture_current(fildes->fildes);
    background->id = 0;
  }
}



SecretEchoOff(fildes, now) 
     struct OutDev *fildes;
     int now;
{
  int i,w,h,x,y, bit24 = 1;

  if ((fildes->bits&BUFTYPE) == CRX8) bit24 = 0;


  if (fildes != oldscreen) printf("ERROR EchoOff called on the wrong screen!\n");
  else if (background->id) {
    w = lastcursor->dx;
    h = lastcursor->dy;
    x = E_oldx-lastcursor->hotdx;
    y = E_oldy-lastcursor->hotdy;
    if (bit24) bank_switch(fildes->fildes,2,0);
    dcblock_write(fildes->fildes, x,y, w, h, background->source, FALSE);
    if (bit24) {
      bank_switch(fildes->fildes,1,0);
      dcblock_write(fildes->fildes, x,y, w, h, background->source+w*h, FALSE);
      bank_switch(fildes->fildes,0,0);
      dcblock_write(fildes->fildes, x,y, w, h, background->source+w*h*2, FALSE);
    }
    if (now) make_picture_current(fildes->fildes);
  }
}



EchoOn(x, y, fildes)
     int x, y;
     struct OutDev *fildes;
{
  unsigned char *control,*spos,*buffer;
  int display, dx,dy,nx,ny, bit24 = 1;

  if ((fildes->bits&BUFTYPE) == CRX8) bit24 = 0;

  nx = x-lastcursor->hotdx;
  ny = y-lastcursor->hotdy;
  if (x == 123456) {	/* *TIM-19Apr91* */
    printf("WHOA!! Tim's EchoOn change called.\n");
    nx = E_oldx-lastcursor->hotdx;
    ny = E_oldy-lastcursor->hotdy;
  }
  
  display = fildes->fildes;
  if (!background->id)
    {
      /* save background */
      background->id = 1;
      dx = lastcursor->dx;  dy = lastcursor->dy;
      if (bit24) bank_switch(display,2,0);
      dcblock_read(fildes->fildes, nx, ny, dx, dy, background->source, FALSE);
      if (bit24) {
	bank_switch(display,1,0);
	dcblock_read(fildes->fildes, nx, ny, dx, dy, background->source+dx*dy, FALSE);
	bank_switch(display,0,0);
	dcblock_read(fildes->fildes, nx, ny, dx, dy, background->source+dx*dy*2, FALSE);
      }

      /* draw shape */
      drawing_mode(display, 1); /* AND */
      if (bit24) bank_switch(display,2,0);
      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*3,FALSE);
      if (bit24) {
	bank_switch(display,1,0);
	dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*4,FALSE);
	bank_switch(display,0,0);
	dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*5,FALSE);
      }

      drawing_mode(display, 7); /* OR */
      if (bit24) bank_switch(display,2,0);
      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*6,FALSE);
      if (bit24) {
	bank_switch(display,1,0);
	dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*7,FALSE);
	bank_switch(display,0,0);
	dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*8,FALSE);
      }
      drawing_mode(display, 3); /* NORMAL */

      E_oldx = E_lastx = x; E_oldy = E_lasty = y;
      oldscreen = fildes;
    }
  else printf("EchoOn called when cursor is already on!!\n");
}



ChangeEcho(fildes,echo)
     struct OutDev *fildes;
     struct curstruct *echo;
{
  int bit24 = 1;
  
  if (lastcursor != echo) {
    
    if ((fildes->bits&BUFTYPE) == CRX8) bit24 = 0;
    
    if (background->id)
      {
	EchoOff(fildes, 0);
      if (bit24) InstallCursor(echo);
      else  InstallCursor4(echo);
	EchoOn(E_oldx, E_oldy, fildes);
	return;
      }
    else InstallCursor(echo);
  }
}











