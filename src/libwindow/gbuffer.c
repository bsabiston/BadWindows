/* **************************** */ 
/* GBUFFER                      */
/* bookend draw functions for   */
/* "graphics buffering" windows */
/* **************************** */   


/* WARNING these functions assume that the draw function will only depend on W->x1, W->y1, W->x2, W->y2 
   for window location.  Those are the only variables that get changed. */

#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

struct gb_struct {
  int x, y;
  int width, height;
  int x1,y1,x2,y2;
  int cx1,cy1,cx2,cy2;
  int bufferOn;         /* TRUE or FALSE */
  int gbuf;
  struct OutDev *memdisplay, *windisplay;
};

/* BufferWrap is used to "double-buffer" a window's draw function, so that it doesn't flicker
   with constant update.  This is accomplished by attaching two draw functions, one at the 
   beginning and one at the end (just like EchoWrap).  The beginning DRAW function moves the 
   window's coordinates to the offscreen. The other DRAW functions (Rectify, for example) think
   that the window is offscreen, and all the graphics go there.  The ending DRAW function moves
   the offscreen area to it's proper place, and restores the window's coordinates. 
   Buffer starts at 1280, 0, and is 700 x 1024 pixels

   New option allows starbase to use a memory driver instead of offscreen.  
*/


BufferWrap( W, x, y, width, height, memdriver)
     struct Window *W;
     int x, y, width, height, memdriver;
{
  int GB_On(), GB_Off(), GB_Messages();
  struct gb_struct *gb;
  struct Command *C;
  int (**functions)(), i;
  char **args;

  /* Can't Bufferwrap on CRX */
  gb = (struct gb_struct *)malloc(sizeof(struct gb_struct));
  gb->x = x;
  gb->y = y;
  gb->width = width;
  gb->height = height;
  gb->bufferOn = FALSE;
  gb->gbuf = memdriver;
  gb->memdisplay = NULL;

    C = W->commands;
    if (C)
      {
      while ((C->next)&&(C->id != DRAW)) C = C->next;
      if (C->id != DRAW)
	{
	  AttachCommand(W, DRAW, GB_On, gb); 
	  AttachCommand(W, DRAW, GB_Off, gb);
	}
      else
	{
	  C->numfuncs++;
	  functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
	  args = (char **)malloc(C->numfuncs*sizeof(char *));
	  *(functions) = GB_On;
	  *(args) = (char *)gb;
	  for (i = 0; i < C->numfuncs-1; i++)
	    {
	      *(functions+i+1) = *(C->functions+i);
	      *(args+i+1) = *(C->arguments+i);
	    }
	  if (C->numfuncs >1) { free(C->functions);   free(C->arguments);}
	  
	  C->functions = functions;
	  C->arguments = args;

	  AttachCommand(W, DRAW, GB_Off, gb);
	}
    }
    else {
      AttachCommand(W, DRAW, GB_On, gb); /* no functions at all */
      AttachCommand(W, DRAW, GB_Off, gb); 
    }
    AttachCommand( W, GBUFFER_OFF, GB_Messages, gb ); 
    AttachCommand( W, GBUFFER_ON,  GB_Messages, gb );
  
}



GB_On(W,id,data,stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{
  struct gb_struct *gb;
  gescape_arg arg1,arg2;
  struct clipstruct *c;
  float clist[256][3];
  int x,y,i;

  gb = (struct gb_struct *)stuff;
  c = (struct clipstruct *)data;  

  if (gb->bufferOn == FALSE)   /* S.Librande  9/19/91 */
    return (0);
  
  if( (W->width <= gb->width) && (W->height <= gb->height)) {
    if ((gb->gbuf)&&(gb->memdisplay)) {
      gb->x1 = W->x1;
      gb->y1 = W->y1;
      gb->x2 = W->x2;
      gb->y2 = W->y2;
      gb->cx1 = c->x1;
      gb->cy1 = c->y1;
      gb->cx2 = c->x2;
      gb->cy2 = c->y2;
      gb->windisplay = W->display;

      c->x1 -= W->x1;
      c->x2 -= W->x1;
      c->y1 -= W->y1;
      c->y2 -= W->y1;
      W->x1 = 0;
      W->y1 = 0;
      W->x2 = W->width-1;
      W->y2 = W->height-1;
      W->display = gb->memdisplay;
      
      /* color table update */
      if (((W->display->bits&BUFBITS)>>8) == 8) {
	inquire_color_table(gb->windisplay->fildes, 0, 256, clist);
	define_color_table(W->display->fildes, 0, 256, clist);
      }
    }
    else {
      gb->x1 = W->x1;
      gb->y1 = W->y1;
      gb->x2 = W->x2;
      gb->y2 = W->y2;
      gb->cx1 = c->x1;
      gb->cy1 = c->y1;
      gb->cx2 = c->x2;
      gb->cy2 = c->y2;
      
      c->x1 += gb->x - W->x1;
      c->x2 += gb->x - W->x1;
      c->y1 += gb->y - W->y1;
      c->y2 += gb->y - W->y1;
      W->x1 = gb->x;
      W->y1 = gb->y;
      W->x2 = gb->x+W->width-1;
      W->y2 = gb->y+W->height-1;
    }
  }

  return (0);
}


GB_Off(W,id,data,stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{
  struct gb_struct *gb;
  struct clipstruct *c;
  int x,y,w,h;

  gb = (struct gb_struct *)stuff;
  c = (struct clipstruct *)data;  
  /* move the image */

  if (gb->bufferOn == FALSE)   /* S.Librande  9/19/91 */
    return (0);
  
  if( (W->width <= gb->width) && (W->height <= gb->height)) {
    if (gb->memdisplay) {
      c->x1 = gb->cx1;
      c->y1 = gb->cy1;
      c->x2 = gb->cx2;
      c->y2 = gb->cy2;
      W->x1 = gb->x1;
      W->y1 = gb->y1;
      W->x2 = gb->x2;
      W->y2 = gb->y2;
      W->display = gb->windisplay;

      if ((W->display->bits&BUFTYPE) == CRX8) {
	clip_rectangle(W->display->fildes,(float)c->x1,(float)c->x2,(float)c->y1,(float)c->y2);
	await_retrace(W->display->fildes);
	dcblock_write(W->display->fildes, W->x1, W->y1, gb->width, gb->height,
		      gb->memdisplay->buffer,FALSE);
	make_picture_current( W->display->fildes );
	clip_rectangle(W->display->fildes,(float)0,(float)W->display->viswidth,(float)0,(float)W->display->visheight);
      }
      else {
	clip_rectangle(W->display->fildes,(float)c->x1,(float)c->x2,(float)c->y1,(float)c->y2);
	await_retrace(W->display->fildes);
	bank_switch(W->display->fildes,2,0);
	dcblock_write(W->display->fildes, W->x1, W->y1, gb->width, gb->height,
		      gb->memdisplay->buffer+gb->width*gb->height*2,FALSE);
	bank_switch(W->display->fildes,1,0);
	dcblock_write(W->display->fildes, W->x1, W->y1, gb->width, gb->height,
		      gb->memdisplay->buffer+gb->width*gb->height,FALSE);
	bank_switch(W->display->fildes,0,0);
	dcblock_write(W->display->fildes, W->x1, W->y1, gb->width, gb->height, gb->memdisplay->buffer,FALSE);
	make_picture_current( W->display->fildes );
	clip_rectangle(W->display->fildes,(float)0,(float)W->display->viswidth,(float)0,(float)W->display->visheight);
      }
    }
    else {
      x = MAX(c->x1,gb->x);
      y = MAX(c->y1,gb->y);
      w = MIN(c->x2,gb->x+W->width-1)-x+1;
      h = MIN(c->y2,gb->y+W->height-1)-y+1;
      
      dcblock_move(W->display->fildes, x, y, w, h, gb->x1+(x-gb->x),gb->y1+(y-gb->y));
      make_picture_current( W->display->fildes );
      
      c->x1 = gb->cx1;
      c->y1 = gb->cy1;
      c->x2 = gb->cx2;
      c->y2 = gb->cy2;
      W->x1 = gb->x1;
      W->y1 = gb->y1;
      W->x2 = gb->x2;
      W->y2 = gb->y2;
    }
  }
  return (0);
}



/*
     GB MESSAGES     S.Librande   9/21/91
     These messages allow the double buffering to be turned off and on.
*/     
int GB_Messages(W,id,data,stuff)
     struct Window *W;
     int id;
     char *data,*stuff;
{
  struct gb_struct *gb;
  int fildes;
  gb = (struct gb_struct *)stuff;

  switch (id){
  case (GBUFFER_ON):
    gb->bufferOn = TRUE;
    if (gb->gbuf){
      if (data) {
	gb->memdisplay = (struct OutDev *)data;
	printf("using existing buffer\n");
      }
      else if (!gb->memdisplay) gb->memdisplay = (struct OutDev *)OpenSmallMemDriver(W->width,W->height,(W->display->bits&BUFBITS)>>8);

    }
    break;
  case (GBUFFER_OFF):
    gb->bufferOn = FALSE;
    break;

  default:
    fprintf( stderr, "GB_Messages: unknown id %d\n", id );
    break;
  }
  return (0);
}

















