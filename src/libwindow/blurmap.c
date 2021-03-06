#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

/* code for anti-aliased icons   4/90 */

char *Compress_Check();

struct curstruct *LoadBlurMap(path,x,y)
char *path;
int x,y;
{
  FILE *fp;
  char *p;
  struct curstruct *echo;

  p = (char *)Compress_Check(path);
  if ((fp = fopen(p,"r")) == NULL)
    {
      printf("Yikes! Couldn't open file %s.\n",p);
      return (NULL);
    }

  echo = (struct curstruct *)malloc(sizeof(struct curstruct));
  echo->dx = x;
  echo->dy = y;
  echo->hotdx = 0;
  echo->hotdy = 0;
  echo->rule = 255;  /* for blur maps, rule will be the transparency of the bitmap */
  echo->id = 1;      /* for blur maps, the never-used id variable will stand for pixel-rep */
  echo->source = (unsigned char *) malloc(x * y * 4 *sizeof(unsigned char)); 
  fread (echo->source+x*y*3, sizeof(unsigned char), x * y, fp);
  fread (echo->source, sizeof(unsigned char), x * y*3, fp);
  fclose(fp);

  return(echo);
}


Blurmapify(W, icon)
     struct Window *W;
     struct curstruct *icon;
{
  int DrawBlurmap();

  AttachCommand(W, DRAW, DrawBlurmap, icon);
  W->width = icon->dx*icon->id;   /* pixel rep is id */
  W->height = icon->dy*icon->id;  /* pixel rep is id */
}


DrawBlurmap(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct clipstruct *c;
  struct curstruct *icon;

  c = (struct clipstruct *)data;
  icon = (struct curstruct *)stuff;

  if ((W->display->bits&BUFTYPE) == SRX24)
    {
      lockdev(W->display->fildes);
      Mat_Blurmap32(W->display->bits,W->display->buffer,W->display->control,icon->id,W->x1,W->y1,
		    icon->dx,icon->dy,icon->source,icon->source+icon->dx*icon->dy*3,icon->rule,c->x1,c->y1,c->x2,c->y2);
      unlockdev(W->display->fildes);
    }
  else if ((W->display->bits&BUFTYPE) == CRX24) {
    if (W->display->bits&DBUFFER)
      {
	if (W->display->bits&WBANK) Mat_BlurmapCRX24_db(W,icon,c,0xF0,0,0x0F);
	else Mat_BlurmapCRX24_db(W,icon,c,0x0F,4,0xF0);
      }
    else Mat_BlurmapCRX24(W,icon,c);
  }
  else if ((W->display->bits&BUFTYPE) == CRX8) Mat_BlurmapCRX8(W,icon,c);

  return(0);
}



/* Draw a anti-aliased bitmap on the screen.

   bits:       OutDev bit number.  Used to distinguish between turbo and renaissance
   buffer:     frame buffer address
   control:    frame buffer control space adress
   rep:        pixel-rep
   x:          x offset
   y:          y offset
   width       width of bitmap
   height      height of bitmap
   data        pixel data in banks
   adata       alpha buffer
   trans       overall bitmap transparency (0 is transparent, 255 is opaque)

   x1,y1,x2,y2 clip coordinates
*/


Mat_BlurmapRen24(bits,buffer,control,rep,x,y,width,height,data,adata,trans,x1,y1,x2,y2)
int rep,width,height,bits,trans;
unsigned char *data,*control,*adata,*buffer;
int x,y,x1,y1,x2,y2;
{
  int xoff,yoff,w,h,ex,ey,sx,sy,tx,ty,r,g,b,t,*ibuf,red,green,blue;
  int xx,yy;
  unsigned char *buf;

  w = width*rep;
  h = height*rep;

  sx = (int)(MAX(x,x1));
  sy = (int)(MAX(y,y1));
  ex = MIN(x+w-1,x2);
  ey = MIN(y+h-1,y2);

  control [0x003] = 4;                  
  control [0x40bf] = 7;                  

  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	xx = (tx - x)/rep;
	yy = (ty - y)/rep;

	t = (*(adata+xx+yy*width)*trans)>>8;
	r = ((*(data+xx+yy*width))*trans)>>8;
	g = ((*(data+width*height+xx+yy*width))*trans)>>8;
	b = ((*(data+width*height*2+xx+yy*width))*trans)>>8;

       if (t) {
		 buf = buffer + tx + ty*2048;
		 
		 if (t != 255) {
		   control [0x40bf] = 4;                  
		   *buf = r+(((255-t)* *buf) >> 8);
		   control [0x40bf] = 2;                  
		   *buf = g+(((255-t)* *buf) >> 8);
		   control [0x40bf] = 1;                  
		   *buf = b+(((255-t)* *buf) >> 8);
		 }
		 else {
		   control [0x40bf] = 4;                  
		   *buf = r;
		   control [0x40bf] = 2;                  
		   *buf = g;
		   control [0x40bf] = 1;                  
		   *buf = b;
		 }
	   } /* if (t) */

      }
}



Mat_Blurmap32(bits,buffer,control,rep,x,y,width,height,data,adata,trans,x1,y1,x2,y2)
int rep,width,height,bits,trans;
unsigned char *data,*control,*adata,*buffer;
int x,y,x1,y1,x2,y2;
{
  int xoff,yoff,w,h,ex,ey,sx,sy,tx,ty,r,g,b,t,*ibuf,red,green,blue;
  int xx,yy;
  unsigned char *buf;

  w = width*rep;
  h = height*rep;

  sx = (int)(MAX(x,x1));
  sy = (int)(MAX(y,y1));
  ex = MIN(x+w-1,x2);
  ey = MIN(y+h-1,y2);

  control [0x003] = 4;                  
  control [0x40bf] = 7;                  

  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	xx = (tx - x)/rep;
	yy = (ty - y)/rep;

	t = (*(adata+xx+yy*width)*trans)>>8;
	r = ((*(data+xx+yy*width))*trans)>>8;
	g = ((*(data+width*height+xx+yy*width))*trans)>>8;
	b = ((*(data+width*height*2+xx+yy*width))*trans)>>8;

       if (t) {
		 ibuf = (int *)buffer + tx + ty*2048;
		 if (t != 255) {
		   red = (unsigned char) ((*ibuf & 0x00ff0000) >> 16);
		   green = (unsigned char) ((*ibuf & 0x0000ff00) >> 8);
		   blue = (unsigned char) ((*ibuf & 0x000000ff) >> 0);
		   
		   red = r + (((255-t) * red)>>8);
		   green = g + (((255-t) * green)>>8);
		   blue = b + (((255-t) * blue)>>8);
		 }
		 else {
		   red = r;
		   green = g;
		   blue = b;
		 }
		 
		 *ibuf = ((int) ((red << 16) | (green << 8) | blue));

	   } /* if (t) */

      }
}


Mat_BlurmapCRX24(W,icon,c)
struct Window *W;
struct curstruct *icon;
struct clipstruct *c;
{
  gescape_arg arg1,arg2;
  int sx,sy,ex,ey,tx,ty,w,h,trans,t,screen,r;
  unsigned char *buf, *buffer,*data,*adata;

  w = icon->dx;
  h = icon->dy;
  trans = icon->rule;
  buffer = W->display->buffer;
  screen = W->display->fildes;

  sx = (int)(MAX(W->x1,c->x1)) - W->x1;
  sy = (int)(MAX(W->y1,c->y1)) - W->y1;
  ex = MIN(W->x1+w-1,c->x2) - W->x1;
  ey = MIN(W->y1+h-1,c->y2) - W->y1;

  bank_switch(screen,2,0); 
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 

  adata = icon->source+w*h*3;
  data = icon->source;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = ((*(data+tx+ty*w))*trans)>>8;
	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) *buf = r+(((255-t)* *buf) >> 8);
		 else *buf = r;
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
  bank_switch(screen,1,0); 
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
  data = icon->source+w*h*1;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = ((*(data+tx+ty*w))*trans)>>8;
	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) *buf = r+(((255-t)* *buf) >> 8);
		 else *buf = r;
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
  bank_switch(screen,0,0); 
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
  data = icon->source+w*h*2;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = ((*(data+tx+ty*w))*trans)>>8;
	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) *buf = r+(((255-t)* *buf) >> 8);
		 else *buf = r;
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
}



Mat_BlurmapCRX24_db(W,icon,c,bankmask,bankshift,otherbank)
struct Window *W;
struct curstruct *icon;
struct clipstruct *c;
int bankmask,bankshift,otherbank;
{
  gescape_arg arg1,arg2;
  int sx,sy,ex,ey,tx,ty,w,h,trans,t,screen,r;
  unsigned char *buf, *buffer,*data,*adata,low;

  w = icon->dx;
  h = icon->dy;
  trans = icon->rule;
  buffer = W->display->buffer;
  screen = W->display->fildes;

  sx = (int)(MAX(W->x1,c->x1)) - W->x1;
  sy = (int)(MAX(W->y1,c->y1)) - W->y1;
  ex = MIN(W->x1+w-1,c->x2) - W->x1;
  ey = MIN(W->y1+h-1,c->y2) - W->y1;

  bank_switch(screen,2,0); 
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 

  adata = icon->source+w*h*3;
  data = icon->source;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = ((*(data+tx+ty*w))*trans)>>8;
	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) {
		   low = (*buf & bankmask) << bankshift;
		   low = (0xF0 & (r+(((255-t)* low) >> 8)));
		   low = low >> bankshift;
		   *buf = (*buf & otherbank) | low;
		 }
		 else *buf = (*buf & otherbank) | ((r>>bankshift)&bankmask);
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
  bank_switch(screen,1,0); 
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
  data = icon->source+w*h*1;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = ((*(data+tx+ty*w))*trans)>>8;
	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) {
		   low = (*buf & bankmask) << bankshift;
		   low = (0xF0 & (r+(((255-t)* low) >> 8)));
		   low = low >> bankshift;
		   *buf = (*buf & otherbank) | low;
		 }
		 else *buf = (*buf & otherbank) | ((r>>bankshift)&bankmask);
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
  bank_switch(screen,0,0); 
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
  data = icon->source+w*h*2;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = ((*(data+tx+ty*w))*trans)>>8;
	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) {
		   low = (*buf & bankmask) << bankshift;
		   low = (0xF0 & (r+(((255-t)* low) >> 8)));
		   low = low >> bankshift;
		   *buf = (*buf & otherbank) | low;
		 }
		 else *buf = (*buf & otherbank) | ((r>>bankshift)&bankmask);
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
}



Mat_BlurmapCRX8(W,icon,c)
struct Window *W;
struct curstruct *icon;
struct clipstruct *c;
{
  gescape_arg arg1,arg2;
  int sx,sy,ex,ey,tx,ty,w,h,trans,t,screen,r;
  unsigned char *buf, *buffer,*data,*adata;

  w = icon->dx;
  h = icon->dy;
  trans = icon->rule;
  buffer = W->display->buffer;
  screen = W->display->fildes;

  sx = (int)(MAX(W->x1,c->x1)) - W->x1;
  sy = (int)(MAX(W->y1,c->y1)) - W->y1;
  ex = MIN(W->x1+w-1,c->x2) - W->x1;
  ey = MIN(W->y1+h-1,c->y2) - W->y1;

  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 

  adata = icon->source+w*h*3;
  data = icon->source;
  for (ty = sy; ty <= ey; ty++)
    for (tx = sx; tx <= ex; tx++)
      {
	t = (*(adata+tx+ty*w)*trans)>>8;
	r = (((((*(data+tx+ty*w))*trans)>>8)*77)+
	     ((((*(data+tx+ty*w+w*h))*trans)>>8)*150)+
	     ((((*(data+tx+ty*w+w*h*2))*trans)>>8)*28)) >> 12;

	if (t) {
		 buf = buffer + tx + W->x1+ (W->y1+ty)*2048;
		 if (t != 255) *buf = r+(((255-t)* *buf) >> 12);
		 else *buf = r;
	   }
      }
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
}

