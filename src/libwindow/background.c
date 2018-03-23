/* New in-memory background storage for braindead CRX machines */
/* Off-screen background storage for two-screens */

#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

static int defsize = 300*700, backx, backy, backwide, backtall,backsize, backflag, backfildes, bit8;
static unsigned char *back = NULL;

/* old offscreen function */
ReserveBackgroundSpace(O, x1, y1, x2, y2) 
struct OutDev *O;
int x1, y1, x2, y2;
{
  if (back) free (back);
  back = malloc((x2-x1+1)*(y2-y1+1)*3);
  backsize = (x2-x1+1)*(y2-y1+1);
}


SaveBackground(W)  
struct Window *W;
{
  int val;
  if (!back) {
    back = malloc(defsize*3);
    backsize = defsize;
  }

  if (W->width*W->height > backsize)
    {
      printf("window is bigger than background\n");
      backflag = 0;
    }
  else
    {
      backfildes = W->display->fildes;
      backflag = 1;
      backx = W->x1;
      backy = W->y1;
      backwide = W->width;
      backtall = W->height;
      
      if (((W->display->bits&BUFBITS)>>8) == 24) {
	bank_switch(W->display->fildes,2,0);
	dcblock_read(W->display->fildes, W->x1, W->y1,  W->width, W->height, back,FALSE);
	bank_switch(W->display->fildes,1,0);
	dcblock_read(W->display->fildes, W->x1, W->y1,  W->width, W->height, back+backwide*backtall,FALSE);
	bank_switch(W->display->fildes,0,0);
	dcblock_read(W->display->fildes, W->x1, W->y1,  W->width, W->height, back+backwide*backtall*2,FALSE);
	bit8 = 0;
      }
      else {
	dcblock_read(W->display->fildes, W->x1, W->y1,  W->width, W->height, back,FALSE);
	bit8 = 1;
      }
    }
}


RestoreBackground() 
{
  int val;
  if (!bit8) {
    bank_switch(backfildes,2,0);
    dcblock_write(backfildes, backx, backy,  backwide, backtall, back,FALSE);
    bank_switch(backfildes,1,0);
    dcblock_write(backfildes, backx, backy,  backwide, backtall, back+backwide*backtall,FALSE);
    bank_switch(backfildes,0,0);
    dcblock_write(backfildes, backx, backy,  backwide, backtall, back+backwide*backtall*2,FALSE);
    make_picture_current(backfildes);
  }
  else {
    dcblock_write(backfildes, backx, backy,  backwide, backtall, back,FALSE);
  }
  backflag = 0;
  val = 0;
  return (val);
}

