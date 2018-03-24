#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

static char *homedir = NULL;

struct transp_icon_struct
{
  struct curstruct *icon;
  int transp;
};

struct dicon_struct
{
  struct curstruct *icon1;
  struct curstruct *icon2;
  int flag;
};


struct ticon_struct    /* triple icons  SL-10/5/90 */
{
  struct curstruct *icon1,
                   *icon2,
                   *icon3;
  int flag;
};


struct cswapstruct
{
  struct curstruct *icon;
  int r1, g1, b1, r2, g2, b2, mask;
};



IconColorSwap(W, id1, icon, r1, g1, b1, r2, g2, b2, mask)     /* v 1.0b */
     struct Window *W;
     int mask, id1;
     int r1, g1, b1, r2, g2, b2;
     struct curstruct *icon;
{
  int Icon_Swap_Colors();
  struct cswapstruct *c;

  c = (struct cswapstruct *)malloc(sizeof(struct cswapstruct));
  c->icon = icon;
  c->r1 = r1;
  c->g1 = g1;
  c->b1 = b1;
  c->r2 = r2;
  c->g2 = g2;
  c->b2 = b2;
  c->mask = mask;
  AttachCommand(W, id1, Icon_Swap_Colors, c);
}



Icon_Swap_Colors(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int flag, val = 0;
  struct cswapstruct *c;

  c = (struct cswapstruct *)stuff;

  switch (((struct pickstruct *)data)->button)
    {
    case (JUSTDOWN): flag = c->mask & 1;
      break;
    case (JUSTUP):   flag = c->mask & 2;
      break;
    case (BEENDOWN): flag = c->mask & 4;
                      break;
    case (BEENUP):   flag = c->mask & 8;
      break;
    }
  if (flag)  SwapColors(c->icon->source, c->icon->dx, c->icon->dy, c->r1, c->g1, c->b1, c->r2, c->g2, c->b2);

  return(0);
}



struct curstruct *LoadIcon(name, bits, color)     /* v 1.0b */
     char *name;
     int bits, color;
{
  struct curstruct *icon;
  int val;
  FILE *fp;
  char path[255];

  icon = (struct curstruct *)malloc(sizeof(struct curstruct));

  fp = fopen(name, "r");
  if ((!fp)&&(homedir))
    {
      sprintf(path, "%s%s", homedir, name);
    }
  else
    {
      strcpy(path, name);
      fclose(fp);
    }

  if (bits == 32)
    val = LoadBlurMap(path, &(icon->dx), &(icon->dy), &(icon->source));
  else if (bits == 24)
    val = LoadFullBitMap(path, &(icon->dx), &(icon->dy), &(icon->source));
  else if (bits == 8)
    val = LoadBitMap8to24(path, &(icon->dx), &(icon->dy), 
			  &(icon->source), color, redclear);

  icon->rule = redclear;
  icon->hotdx = 0;
  icon->hotdy = 0;

  if (!val)
    {
      fprintf(stderr, "LoadIcon; Error loading %s.\n", path);
      return(NULL);
    }

  return(icon);
}

struct curstruct *LoadSuguruIcon(name)     /* v 1.0b */
     char *name;
{
  struct curstruct *icon = NULL;
  int val = FALSE;

  icon = (struct curstruct *)malloc(sizeof(struct curstruct));

  if (!(val = LoadSuguruBitMap(name, &(icon->dx), &(icon->dy), &(icon->source)))) {
    printf("Yow! Could not find file %s.\n", name);
    free(icon);
    icon = NULL;
  }
  else {
    icon->rule = redclear;
    icon->hotdx = 0;
    icon->hotdy = 0;
  }

  return(icon);
}

struct curstruct *LoadDaveIcon(name)     /* v 1.0b */
     char *name;
{
  struct curstruct *icon = NULL;
  int val = FALSE;

  icon = (struct curstruct *)malloc(sizeof(struct curstruct));

  if (!(val = LoadDaveBitMap(name, &(icon->dx), 
			     &(icon->dy), &(icon->source)))) 
    {
      printf("LoadDaveIcon: Yow! Could not find file %s.\n", name);
      free(icon);
      icon = NULL;
    }
  else 
    {
      icon->rule = redclear;
      icon->hotdx = 0;
      icon->hotdy = 0;
    }
  return(icon);
}

struct curstruct *LoadSnakeIcon(name,w,h)     /* v 1.0b */
     char *name;
     int w,h;
{
  struct curstruct *icon = NULL;
  int val = FALSE;

  icon = (struct curstruct *)malloc(sizeof(struct curstruct));

  if (!(val = LoadSnakepitBitmap(name, w, h, &(icon->source)))) {
    printf("Yow! Could not find file %s.\n", name);
    free(icon);
    icon = NULL;
  }
  else {
    icon->rule = redclear;
    icon->dx = w;
    icon->dy = h;
    icon->hotdx = 0;
    icon->hotdy = 0;
  }

  return(icon);
}

struct curstruct *LoadRGBIcon(name,w,h)     /* v 1.0b */
     char *name;
     int w,h;
{
  return(LoadSnakeIcon(name,w,h));
}


LoadSnakepitBitmap(path,x,y,data)
char *path;
int x,y;
unsigned char **data;
{
  FILE *fp;
  int ix,iy;
  unsigned char *buffer, c;
  char *p;

  p = (char *)Compress_Check(path);
  if ((fp = fopen(p,"r")) == NULL) return (0);
  
  *data = buffer = (unsigned char *) malloc(x * y * 3 *sizeof(unsigned char));
printf("loading\n");
  fread(buffer,3*x*y,1,fp);
printf("done\n");
  fclose(fp);
  return(1);
}

CopyIcon24(source, dest)     /* v 1.0b */
     struct curstruct *source, **dest;
{
  unsigned char *matrix;
  int x;

  *dest = (struct curstruct *)malloc(sizeof(struct curstruct));

  matrix = (unsigned char *)malloc(source->dx*source->dy*3*sizeof(unsigned char));
  for (x = 0; x < source->dx*source->dy*3; x++)
    *(matrix+x) = *(source->source+x);

  (*dest)->source = matrix;
  (*dest)->dx = source->dx;
  (*dest)->dy = source->dy;
  (*dest)->rule = source->rule;
}



MakeIcon(W, name, bits, color)     /* v 1.0b */
     struct Window *W;
     char *name;
     int bits, color;
{
  struct curstruct *icon;
  int DrawIcon();

  icon = (struct curstruct *)LoadIcon(name, bits, color);
  AttachCommand(W, DRAW, DrawIcon, icon);
  W->width = icon->dx;
  W->height = icon->dy;
}


MakeSuguruIcon(W, name)     /* v 1.0b */
     struct Window *W;
     char *name;
{
  struct curstruct *icon;
  int DrawIcon();

  icon = (struct curstruct *)LoadSuguruIcon(name);
  AttachCommand(W, DRAW, DrawIcon, icon);
  W->width = icon->dx;
  W->height = icon->dy;
}



AttachIcon(W, icon)     /* v 1.0b */
     struct Window *W;
     struct curstruct *icon;
{
  int DrawIcon(), IconColorSwapDo(),SwitchIcon();

  AttachCommand(W, DRAW, DrawIcon, icon);
  AttachCommand(W, SWITCH_ICON, SwitchIcon, NULL);
  AttachCommand(W, ICON_NEWCOLOR, IconColorSwapDo, icon); /* *DKY-16Oct90* */
  W->width = icon->dx;
  W->height = icon->dy;
}

AttachIconTransparent(W, icon, transparency)     /* v 1.0b */
     struct Window *W;
     struct curstruct *icon;
     int transparency;
{
  int DrawTransparentIcon(), IconColorSwapDo(),SwitchIcon();
  struct transp_icon_struct *t;

  t = (struct transp_icon_struct *)malloc(sizeof(struct transp_icon_struct));
  t->icon = icon;
  t->transp = transparency;

  AttachCommand(W, DRAW, DrawTransparentIcon, t);
  AttachCommand(W, SWITCH_ICON, DrawTransparentIcon, t);
  AttachCommand(W, CHANGETRANS, DrawTransparentIcon, t);
  AttachCommand(W, UPDATE, DrawTransparentIcon, t);
  AttachCommand(W, ICON_NEWCOLOR, IconColorSwapDo, icon); /* *DKY-16Oct90* */
  W->width = icon->dx;
  W->height = icon->dy;
}

/* Send a ICON_NEWCOLOR message with an array of 6 integers as the argument.  
 * The first three ints are the color that you want to swap, and the second
 * three ints are the color you want to swap to.
 */
IconColorSwapDo( W, id, data, stuff) /* *DKY-16Oct90* */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int *colors;
  struct curstruct *icon;

  icon = (struct curstruct *)stuff;
  colors = (int *)data;		/* data is list of 6 colors int */
  SwapColors( icon->source, icon->dx, icon->dy, colors[0], colors[1], colors[2],   colors[3], colors[4], colors[5]);
  return( 0);
}


DetachIcon(W)     /* JSH 17 May 90 */
     struct Window *W;
{
  int DrawIcon(), IconColorSwapDo();
  
  DetachCommand(W, DRAW, DrawIcon);
/*  DetachCommand(W, ICON_NEWCOLOR, IconColorSwapDo); */  /* we can't do this because they share the same stuff. */
}


SwitchIcon(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct Command *C;
  int (**functions)(), i,DrawIcon();
  char **args;
  
  C = W->commands;
  if (C) {
    while ((C->next)&&(C->id != DRAW)) C = C->next;
    if (C->id != DRAW) return(0);

    for (i = 0; i < C->numfuncs; i++)
      {
	if (*(C->functions+i) == DrawIcon)
	  {
	    /* FOUND THE DAMN THING */
	    *(C->arguments+i) = data;
	  }
      }
  }
  
  return(0);
}


DrawIcon(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct clipstruct *cstruct;
  struct curstruct *icon;

  cstruct = (struct clipstruct *)data;
  icon = (struct curstruct *)stuff;

  if ((W->display->bits&BUFTYPE) == REN24)
    shape_write24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
		  W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
  else if ((W->display->bits&BUFTYPE) == CRX24)
    {
      rectangle(W->display->fildes,(float)(W->x1+7),(float)(W->y1+7),(float)(W->x1+7),(float)(W->y1+7));
      make_picture_current(W->display->fildes);
      if (!(W->display->bits&DBUFFER))
	icon_writeCRX24(W, icon,cstruct);
      else {
	if (W->display->bits & WBANK) icon_writeCRX24_high(W, icon,cstruct);
	else icon_writeCRX24_low(W, icon,cstruct);
      }
    }
  else if (((W->display->bits&BUFTYPE) == SRX24)||((W->display->bits&BUFTYPE) == CRX24Z))
    {
      lockdev(W->display->fildes);
      shape_write32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
		    W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
      unlockdev(W->display->fildes);
    }
  else if ((W->display->bits == 4)||((W->display->bits&BUFTYPE) == CRX8)) {
    rectangle(W->display->fildes,(float)(W->x1+7),(float)(W->y1+7),(float)(W->x1+7),(float)(W->y1+7));
    make_picture_current(W->display->fildes);

    lockdevice(W->display->fildes);
    shape_write24to4(icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
		   W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
    unlockdevice(W->display->fildes);
  }
  else if ((W->display->bits&BUFTYPE) == LAME) {
    block_write(W->display->fildes,(float)W->x1,(float)W->y1,icon->dx, icon->dy,icon->source,FALSE);
    make_picture_current(W->display->fildes);
  }
  return(0);
}


DrawTransparentIcon(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct clipstruct *cstruct;
  struct curstruct *icon;
  struct transp_icon_struct *t;
  int transp;
  
  t = (struct transp_icon_struct *)stuff;
  icon = t->icon;
  transp = t->transp;

  switch (id) {
  case (DRAW):
    cstruct = (struct clipstruct *)data;
    
/*    (W->display)->control[0x0003] = 0x04;
    (W->display)->control[0x40bf] = 7; */

    if (W->display->bits == 24)
      shape_write_transp24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
			   W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2, transp);
    else if ((W->display->bits == REN24)||(W->display->bits == CRX24))
      shape_write_transp32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
			   W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2, transp);
    break;
  case (CHANGETRANS):
    /** change transp in transp_icon_struct **/
    t->transp = *((int *) (data));
    printf("trans changed to = %d\n", *((int *)(data)));
    
    /** update window on the screen ***/
    SendMessage(W, UPDATE, NULL);
    break;
  case (SWITCH_ICON):
    /** switch the icon to a new icon ***/
    t->icon = ((struct curstruct *) (data));
    /** resize window to new size ***/
    W->width = icon->dx;
    W->height = icon->dy;
    /** update window on the screen ***/
    SendMessage(W, UPDATE, NULL);
    break;
  case (UPDATE):
    ShowWindow(W->parent, W->x1, W->y1, W->x2, W->y2);
    if (W->parent->parent) ShowTops(W->parent, W->x1, W->y1, W->x2, W->y2);
    break;
  default:
    printf( "Unknown message id %d: DrawTransparentIcon\n", id);
  }
  return(0);
}



AttachDoubleIcon(W, icon, icon2)     /* v 1.0b */
     struct Window *W;
     struct curstruct *icon, *icon2;
{
  int DoubleDrawIcon();
  struct dicon_struct *d;

  d = (struct dicon_struct *)malloc(sizeof(struct dicon_struct));
  d->icon1 = icon;
  d->icon2 = icon2;
  d->flag = 0;

  AttachCommand(W, DRAW, DoubleDrawIcon, d);
  AttachCommand(W, SWITCH_ICON, DoubleDrawIcon, d);
  W->width = icon->dx;
  W->height = icon->dy;
}



DoubleDrawIcon(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct clipstruct *cstruct;
  struct curstruct *icon;
  struct dicon_struct *d;

  d = (struct dicon_struct *)stuff;

  if (id == DRAW)
    {
      cstruct = (struct clipstruct *)data;
      if (d->flag) icon = d->icon2;
      else icon = d->icon1;

      if ((W->display->bits&BUFTYPE) == REN24)
	shape_write24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
		      W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);

      else if ((W->display->bits&BUFTYPE) == CRX24)
	{
	  rectangle(W->display->fildes,(float)(W->x1+7),(float)(W->y1+7),(float)(W->x1+7),(float)(W->y1+7));
	  make_picture_current(W->display->fildes);
	  if (!(W->display->bits&DBUFFER))
	    icon_writeCRX24(W, icon,cstruct);
	  else {
	    if (W->display->bits & WBANK) icon_writeCRX24_high(W, icon,cstruct);
	    else icon_writeCRX24_low(W, icon,cstruct);
	  }
	}
      else if (((W->display->bits&BUFTYPE) == SRX24)||((W->display->bits&BUFTYPE) == CRX24Z))
	{
	  lockdev(W->display->fildes);
	  shape_write32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
			W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
	  unlockdev(W->display->fildes);
	}
      else if ((W->display->bits == 4)||((W->display->bits&BUFTYPE) == CRX8)) {
	lockdevice(W->display->fildes);
	shape_write24to4(icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
			 W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
	unlockdevice(W->display->fildes);
      }
     else if ((W->display->bits&BUFTYPE) == LAME) {
       block_write(W->display->fildes,(float)W->x1,(float)W->y1,icon->dx, icon->dy,icon->source,FALSE);
       make_picture_current(W->display->fildes);
      }
    }

  else if (id == SWITCH_ICON)  { /* switch to right icon */
    d->flag = *((int *)data);
    UpdateWin(W);
  }
  else if (id == SWITCH_ICON_NODRAW)  { /* switch to right icon but don't update window*/
    d->flag = *((int *)data);
  }
}



RotateIcon24(icon, positions)     /* v 1.0b */
     struct curstruct *icon;
     int positions;
{
  int xc, yc, x=0, y=0;
  unsigned char *matrix, *matrix2, *m1, *m2;

  xc = icon->dx;
  yc = icon->dy;
  matrix = icon->source;

  matrix2 = (unsigned char *)malloc(xc*yc*3*sizeof(unsigned char));
  switch (positions)
    {
    case (1):
      for (y = 0; y<yc; y++)
	for (x = 0; x<xc; x++)
	  {
	    m1 = matrix+3*(x+y*xc);
	    m2 = matrix2+3*(yc-y-1+x*yc);
	    *m2 = *m1;
	    *(m2+1) = *(m1+1);
	    *(m2+2) = *(m1+2);
	  }
      icon->source = matrix2;
      free(matrix);
      icon->dx = yc;
      icon->dy = xc;
      break;
    case (2):
      for (y = 0; y<yc; y++)
	for (x = 0; x<xc; x++)
	  {
	    m1 = matrix+3*(x+y*xc);
	    m2 = matrix2+3*((yc-y-1)*xc+xc-x-1);
	    *m2 = *m1;
	    *(m2+1) = *(m1+1);
	    *(m2+2) = *(m1+2);
	  }
      icon->source = matrix2;
      free(matrix);
      break;
    case (3):
      for (y = 0; y<yc; y++)
	for (x = 0; x<xc; x++)
	  {
	    m1 = matrix+3*(x+y*xc);
	    m2 = matrix2+3*(y+(xc-x-1)*yc);
	    *m2 = *m1;
	    *(m2+1) = *(m1+1);
	    *(m2+2) = *(m1+2);
	  }
      icon->source = matrix2;
      free(matrix);
      icon->dx = yc;
      icon->dy = xc;
      break;
    case (4):
      for (y = 0; y<yc; y++)
	for (x = 0; x<xc; x++)
	  {
	    m1 = matrix+3*(x+y*xc);
	    m2 = matrix2+3*(y*xc+xc-x-1);
	    *m2 = *m1;
	    *(m2+1) = *(m1+1);
	    *(m2+2) = *(m1+2);
	  }
      icon->source = matrix2;
      free(matrix);
      break;
    case (5):
      for (y = 0; y<yc; y++)
	for (x = 0; x<xc; x++)
	  {
	    m1 = matrix+3*(x+y*xc);
	    m2 = matrix2+3*((yc-y-1)*xc+x);
	    *m2 = *m1;
	    *(m2+1) = *(m1+1);
	    *(m2+2) = *(m1+2);
	  }
      icon->source = matrix2;
      free(matrix);
      break;
    }
}





AttachIconScalable(W, icon)     /* v 1.0b */
     struct Window *W;
     struct curstruct *icon;
{
  int DrawIconScalable();

  interleaf_to_bank(icon);

  AttachCommand(W, DRAW, DrawIconScalable, icon);
  AttachCommand(W, FILTER, DrawIconScalable, icon);
}


interleaf_to_bank(icon)
     struct curstruct *icon;
{
  unsigned char *temp, *ptr;
  int i;
  
  if ((temp = (unsigned char *)malloc(sizeof(unsigned char)*icon->dx*icon->dy*3)) == NULL)
    printf("AttachIconScalable: Unable to malloc scratch space\n");
  
  ptr = icon->source;
  
  for (i = 0; i < (icon->dx*icon->dy); i++) {
    *(temp+i) = *ptr++;
    *(temp+(i + (icon->dx*icon->dy))) = *ptr++;
    *(temp+(i + (2*icon->dx*icon->dy))) = *ptr++;
  }
  free(icon->source);
  icon->source = temp;
}

DrawIconScalable(W, id, data, stuff)      /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct clipstruct *cstruct;
  struct curstruct *icon;
  int screen;
  int x1, y1, x, y, wd, xpos;
  int bank, banks;
  int cx1, cy1, cx2, cy2;
  unsigned char *rptr, *gptr, *bptr;

  icon = (struct curstruct *)stuff;
  screen = W->display->fildes;

  switch (id) {
  case (DRAW):
    cstruct = (struct clipstruct *)data;
    cx1 = cstruct->x1, cy1 = cstruct->y1;
    cx2 = cstruct->x2, cy2 = cstruct->y2;

    clip_rectangle(screen, 0.0, 2047.0, 0.0, 1023.0);
    make_picture_current(screen);
    
    banks = ((int) (ceil((icon->dx / 256.0))));
    
    for (bank = 0; bank < banks; bank++) {
      if (bank+1 < banks)
	wd = 256;
      else 
	{ wd = icon->dx % 256; if (wd == 0) wd = 256;}

      rptr = icon->source+(bank*256);
      gptr = icon->source+((bank*256)+(icon->dx * icon->dy));
      bptr = icon->source+((bank*256)+(2*icon->dx * icon->dy));
      /********* DRAW ICON *******************************************/
      for (y = 0; y < icon->dy; y++) {
	/*** restore bitmap note ***/
	bank_switch(screen, 2, 0);
	dcblock_write(screen, 1280, y, wd, 1, rptr, FALSE);
	bank_switch(screen, 1, 0);
	dcblock_write(screen, 1280, y, wd, 1, gptr, FALSE);
	bank_switch(screen, 0, 0);
	dcblock_write(screen, 1280, y, wd, 1, bptr, FALSE);
	rptr += icon->dx;
	gptr += icon->dx;
	bptr += icon->dx;
      }
      (W->display)->control[0x40bf] = 7;

      /********* EXPAND IN Y *******************************************/
      for (y = 0; y < W->height; y++) {
	y1 = ((int) ((y * icon->dy) / W->height));
	dcblock_move(screen, 1280, y1, wd, 1, 1536, y);
      }
      /********* EXPAND IN X *******************************************/
      for (x = 0; x < ((int) (wd*W->width/icon->dx)); x++) {
	x1 = ((int) (x * icon->dx / W->width));
	xpos = W->x1 + x + ((int) (bank*256.0*W->width/icon->dx));
	if ((xpos >= cx1) && (xpos <= cx2))
	  dcblock_move(screen, 1536+x1, cy1-W->y1, 
		       1, cy2-cy1, 
		       xpos, cy1);
      }
      make_picture_current(screen);
    }
    (W->display)->control[0x40bf] = 7;
    make_picture_current(screen);
    break;
  case (FILTER):
    printf(" I'm sorry, I dont know how to filter yet.\n");
    break;
  default:
    printf("DrawIconSizable:  Unknown message %d\n", id);
  }
}




AttachTripleIcon(W, icon, icon2, icon3 )     /* v 1.0b S.Librande - 10/05/90 */
     struct Window *W;
     struct curstruct *icon,
                      *icon2,
                      *icon3;
{

  int TripleDrawIcon();
  struct ticon_struct *t;

  t = (struct ticon_struct *)malloc(sizeof(struct ticon_struct));
  t->icon1 = icon;
  t->icon2 = icon2;
  t->icon3 = icon3;
  t->flag = 0;

  AttachCommand( W, DRAW, TripleDrawIcon, t );
  AttachCommand( W, SWITCH_ICON, TripleDrawIcon, t );
  W->width  = icon->dx;
  W->height = icon->dy;
}



TripleDrawIcon( W, id, data, stuff )      /* v 1.0b  S.Librande - 10/05/90 */
     struct Window *W;
     int id;
     char *data,
          *stuff;
{
  struct clipstruct *cstruct;
  struct curstruct *icon;
  struct ticon_struct *t;

  t = (struct ticon_struct *)stuff;

  if (id == DRAW)
    {
      cstruct = (struct clipstruct *)data;
      switch ( t->flag )
      {
	case ( 0 ):
	  icon = t->icon1;
	  break;
	case ( 1 ):
	  icon = t->icon2;
	  break;
	case ( 2 ):
	  icon = t->icon3;
	  break;
      }	  

/*      (W->display)->control[0x0003] = 0x04;
      (W->display)->control[0x40bf] = 7; */

      if (W->display->bits == REN24)
	shape_write24(W->display->control, icon->source,
		                           icon->dx, icon->dy,
		                           W->display->buffer, W->display->width,
		       W->display->height, W->x1, W->y1, icon->rule,
		       cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2 );
      
      else if ((W->display->bits&BUFTYPE) == CRX24)
	{
	  rectangle(W->display->fildes,(float)(W->x1+7),(float)(W->y1+7),(float)(W->x1+7),(float)(W->y1+7));
	  make_picture_current(W->display->fildes);
	  if (!(W->display->bits&DBUFFER))
	    icon_writeCRX24(W, icon,cstruct);
	  else {
	    if (W->display->bits & WBANK) icon_writeCRX24_high(W, icon,cstruct);
	    else icon_writeCRX24_low(W, icon,cstruct);
	  }
	}
      else if (((W->display->bits&BUFTYPE) == SRX24)||((W->display->bits&BUFTYPE) == CRX24Z))
	{
	  lockdev(W->display->fildes);
	  shape_write32(W->display->control, icon->source,icon->dx, icon->dy,
			W->display->buffer, W->display->width,
			W->display->height, W->x1, W->y1, icon->rule,
			cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
	  unlockdev(W->display->fildes);
	}
      else if ((W->display->bits == 4) || ((W->display->bits&BUFTYPE) == CRX8))
	rectangle(W->display->fildes,(float)(W->x1+7),(float)(W->y1+7),(float)(W->x1+7),(float)(W->y1+7));
        make_picture_current(W->display->fildes);
	lockdevice(W->display->fildes);
	shape_write24to4(icon->source, icon->dx, icon->dy,
			 W->display->buffer, W->display->width,
			 W->display->height, W->x1, W->y1, icon->rule,
			 cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
        unlockdevice(W->display->fildes);
    }

  else if (id == SWITCH_ICON)  { /* switch to right icon */
    t->flag = *((int *)data);
    UpdateWin(W);
  }
}


FreeIcon(icon)
struct curstruct *icon;
{
  free(icon->source);
  free(icon);

  icon = NULL;
}


SetIconHomeDirectory(name)
char *name;
{
  if (homedir) free(homedir);
  homedir = CopyString(name);
}





icon_writeCRX24(W,icon,c)
struct Window *W;
struct curstruct *icon;
struct clipstruct *c;
{
  register unsigned char *dpos, *spos, *done;
  register int xcount, xgap, counter, sgap, scount, scounter;
  int xcut, ycut, xoff=0, yoff=0,screen;
  gescape_arg arg1,arg2;

  if ((W->x1>c->x2) || (W->y1>c->y2) || (W->x1+icon->dx <= c->x1) || (W->y1+icon->dy <= c->y1)) return;

  screen = W->display->fildes;
  xcut = icon->dx;
  ycut = icon->dy;
  if (c->x1-W->x1 > 0) xoff = c->x1-W->x1;
  if (c->y1-W->y1 > 0) yoff = c->y1-W->y1;
  if (W->x1+icon->dx-1 - c->x2 >0) xcut = c->x2-W->x1+1;
  if (W->y1+icon->dy-1 - c->y2 >0) ycut = c->y2-W->y1+1;
  xcut -= xoff;
  ycut -= yoff;

  dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
  spos = icon->source+xoff*3+(yoff*icon->dx*3);

  done = icon->source+(xcut+xoff)*3+(yoff+ycut-1)*(icon->dx*3);
  xgap = W->display->width-xcut;
  sgap = icon->dx-xcut;
  counter = xcount = xcut;

  if (counter)
    {
      bank_switch(screen,2,0); 
      make_picture_current(screen);
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      while (spos<done)
	{
	  if (*spos != icon->rule) *dpos = *spos;
	  dpos++;
	  spos += 3;
	  if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	}

      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
      bank_switch(screen,1,0); 
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
      spos = icon->source+xoff*3+(yoff*icon->dx*3);
      counter = xcount = xcut;
	while (spos<done)
	  {
	    if (*spos != icon->rule) *dpos = *(spos+1);
	    dpos++;
	    spos += 3;
	    if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	  }

      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
      bank_switch(screen,0,0); 
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
      spos = icon->source+xoff*3+(yoff*icon->dx*3);
      counter = xcount = xcut;
      while (spos<done)
	  {
	    if (*spos != icon->rule) *dpos = *(spos+2);
	    dpos++;
	    spos += 3;
	    if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	  }
      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
    }
}




icon_writeCRX24_high(W,icon,c)
struct Window *W;
struct curstruct *icon;
struct clipstruct *c;
{
  register unsigned char *dpos, *spos, *done;
  register int xcount, xgap, counter, sgap, scount, scounter;
  int xcut, ycut, xoff=0, yoff=0,screen,high;
  gescape_arg arg1,arg2;

  if ((W->x1>c->x2) || (W->y1>c->y2) || (W->x1+icon->dx <= c->x1) || (W->y1+icon->dy <= c->y1)) return;

  screen = W->display->fildes;
  xcut = icon->dx;
  ycut = icon->dy;
  if (c->x1-W->x1 > 0) xoff = c->x1-W->x1;
  if (c->y1-W->y1 > 0) yoff = c->y1-W->y1;
  if (W->x1+icon->dx-1 - c->x2 >0) xcut = c->x2-W->x1+1;
  if (W->y1+icon->dy-1 - c->y2 >0) ycut = c->y2-W->y1+1;
  xcut -= xoff;
  ycut -= yoff;

  dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
  spos = icon->source+xoff*3+(yoff*icon->dx*3);

  done = icon->source+(xcut+xoff)*3+(yoff+ycut-1)*(icon->dx*3);
  xgap = W->display->width-xcut;
  sgap = icon->dx-xcut;
  counter = xcount = xcut;

  if (counter)
    {
      bank_switch(screen,2,0); 
      make_picture_current(screen);
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      while (spos<done)
	{
	  if (*spos != icon->rule) *dpos = (*dpos & 0x0F) | (*spos&0xF0);
	  dpos++;
	  spos += 3;
	  if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	}

      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
      bank_switch(screen,1,0); 
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
      spos = icon->source+xoff*3+(yoff*icon->dx*3);
      counter = xcount = xcut;
	while (spos<done)
	  {
	    if (*spos != icon->rule) *dpos = (*dpos & 0x0F) | (*(spos+1)&0xF0);
	    dpos++;
	    spos += 3;
	    if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	  }

      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
      bank_switch(screen,0,0); 
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
      spos = icon->source+xoff*3+(yoff*icon->dx*3);
      counter = xcount = xcut;
      while (spos<done)
	  {
	    if (*spos != icon->rule) *dpos = (*dpos & 0x0F) | (*(spos+2)&0xF0);
	    dpos++;
	    spos += 3;
	    if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	  }
      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
    }
}



icon_writeCRX24_low(W,icon,c)
struct Window *W;
struct curstruct *icon;
struct clipstruct *c;
{
  register unsigned char *dpos, *spos, *done;
  register int xcount, xgap, counter, sgap, scount, scounter;
  int xcut, ycut, xoff=0, yoff=0,screen,high;
  gescape_arg arg1,arg2;

  if ((W->x1>c->x2) || (W->y1>c->y2) || (W->x1+icon->dx <= c->x1) || (W->y1+icon->dy <= c->y1)) return;

  screen = W->display->fildes;
  xcut = icon->dx;
  ycut = icon->dy;
  if (c->x1-W->x1 > 0) xoff = c->x1-W->x1;
  if (c->y1-W->y1 > 0) yoff = c->y1-W->y1;
  if (W->x1+icon->dx-1 - c->x2 >0) xcut = c->x2-W->x1+1;
  if (W->y1+icon->dy-1 - c->y2 >0) ycut = c->y2-W->y1+1;
  xcut -= xoff;
  ycut -= yoff;

  dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
  spos = icon->source+xoff*3+(yoff*icon->dx*3);

  done = icon->source+(xcut+xoff)*3+(yoff+ycut-1)*(icon->dx*3);
  xgap = W->display->width-xcut;
  sgap = icon->dx-xcut;
  counter = xcount = xcut;

  if (counter)
    {
      bank_switch(screen,2,0); 
      make_picture_current(screen);
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      while (spos<done)
	{
	  if (*spos != icon->rule) *dpos = (*dpos & 0xF0) | (*spos>>4);
	  dpos++;
	  spos += 3;
	  if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	}

      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
      bank_switch(screen,1,0); 
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
      spos = icon->source+xoff*3+(yoff*icon->dx*3);
      counter = xcount = xcut;
	while (spos<done)
	  {
	    if (*spos != icon->rule) *dpos = (*dpos & 0xF0) | (*(spos+1)>>4);
	    dpos++;
	    spos += 3;
	    if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	  }

      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
      bank_switch(screen,0,0); 
      gescape(screen, R_LOCK_DEVICE, &arg1, &arg2); 
      dpos = W->display->buffer+W->x1+(W->y1+yoff)*W->display->width+xoff;
      spos = icon->source+xoff*3+(yoff*icon->dx*3);
      counter = xcount = xcut;
      while (spos<done)
	  {
	    if (*spos != icon->rule) *dpos = (*dpos & 0xF0) | (*(spos+2)>>4);
	    dpos++;
	    spos += 3;
	    if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
	  }
      gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
    }
}

