

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





/*************************

  POINTX.C

  plots a single point in framebuffer
  and in an optional  bitmap
  and in an optional 8-bit abuffer -- added 10/8/89

***********************/
#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include "aaline.h"

#define EXCLUSIVE 3
#define buf(x, y) (framebuf+x+(y*fbw))
#define buf_32(x, y) (((int *) (framebuf))+x+(y*fbw))
#define bufr(x,y) (r_bank+(x-xoff)+((y-yoff)*buf2wd))
#define bufg(x,y) (g_bank+(x-xoff)+((y-yoff)*buf2wd))
#define bufb(x,y) (b_bank+(x-xoff)+((y-yoff)*buf2wd))

extern unsigned char ColorTable[256][3]; /* from window system, only necessary for 8bit */

extern unsigned char *framebuf, *r_bank, *g_bank, *b_bank, *abuffer;
extern int xoff, yoff, buf2wd, buf2ht, buf2, abufwd, abufht, abuf,fbw,fbh;

extern void (*point1)();
extern int aa_screen, aa_bankmask, aa_otherbank, aa_bankshift;   
static unsigned char *control;
unsigned char aashort [32][32];



aa_set_ctrl (ctrl)
unsigned char *ctrl;

{ control = ctrl;
}


/* read in the table values from a file.
*/

void read_short_table (filename)
char filename[];

{   FILE *f;
    int i, j;
    double tab [32][32];


    if ((f = fopen (filename, "r")) == NULL)
    { perror ("");
      printf ("error opening file %s\n", filename);
      exit (1);
    }

    if ((i = fread ((char *)tab, sizeof (double), 32 * 32, f)) != 32 * 32)
        printf ("error reading file %s\n", filename), exit (1);

    for (i = 0; i < 32; i++)
        for (j = 0; j < 32; j++)
	    aashort [31 - i][31 - j] = (unsigned char)(tab [i][j] * 255);
/*	    aashort [31 - i][31 - j] = (int)(tab [i][j] * 65536 + 0.55555555); */
    fclose(f);
}




void point1_REN24 (x, y, near, far, near2, far2, r, g, b, t)
register int near, far, near2, far2, r, g, b, t;
register int x, y;

{
  register int filter;
  register unsigned char *pixel, *red, *green, *blue, *ab;

  if (near < 0) near = 0;
  if (near2 < 0) near2 = 0;
  if (far < 0) far = 0;
  if (far2 < 0) far2 = 0;

  if (near > 31) near = 31;
  if (near2 > 31) near2 = 31;
  if (far > 31) far = 31;
  if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  filter *= t;

  pixel = buf(x, y);
  control [0x40ef] = 0x33; /* set draw mode to source */

  if (buf2 == TRUE) {
    red = bufr(x, y);
    green = bufg(x, y);
    blue = bufb(x, y);

    control [0x40bf] = 4;
    *red = *pixel += ((r - *pixel) * filter) >>16;
    control [0x40bf] = 2;
    *green = *pixel += ((g - *pixel) * filter) >>16;
    control [0x40bf] = 1;
    *blue = *pixel += ((b - *pixel) * filter) >>16;
  }
  else if (buf2 == EXCLUSIVE) {
    red = bufr(x, y);
    green = bufg(x, y);
    blue = bufb(x, y);

    control [0x40bf] = 4;
    *red += ((r - *red) * filter) >>16;
    control [0x40bf] = 2;
    *green += ((g - *green) * filter) >>16;
    control [0x40bf] = 1;
    *blue += ((b - *blue) * filter) >>16;
  }
  else {
    control [0x40bf] = 4;
    *pixel += ((r - *pixel) * filter) >>16;
    control [0x40bf] = 2;
    *pixel += ((g - *pixel) * filter) >>16;
    control [0x40bf] = 1;
    *pixel += ((b - *pixel) * filter) >>16;
  }
  control [0x40bf] = 7;

  if (abuf == TRUE) {
    ab = (abuffer + x +(y*fbw));
    *ab += ((255 - *ab) * filter) >>16;
  }
}


/* this code works one channel at a time. therefore it gets called three times for each pixel */
void point1_CRX24 (x, y, near, far, near2, far2, r, g, b,t)
register int near, far, near2, far2, r, g, b,t;
register int x, y;

{
  register int filter;
  register unsigned char *pixel, *red, *green, *blue, *ab;
  gescape_arg arg1,arg2;

  if (near < 0) near = 0;
  if (near2 < 0) near2 = 0;
  if (far < 0) far = 0;
  if (far2 < 0) far2 = 0;

  if (near > 31) near = 31;
  if (near2 > 31) near2 = 31;
  if (far > 31) far = 31;
  if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  filter *= t;

  pixel = buf(x, y);

  if (buf2 == TRUE) {
    printf("aaline bitmap option removed.\n");
  }
  else if (buf2 == EXCLUSIVE) {
    printf("aaline bitmap option removed.\n");
  }
  else {
    *pixel += ((r - *pixel) * filter) >>16;
  }

  if (b&&(abuf == TRUE)) {
    ab = (abuffer + x +(y*fbw));
    *ab += ((255 - *ab) * filter) >>16;
  }
}



void point1_CRX8 (x, y, near, far, near2, far2, r, g, b, t)
register int near, far, near2, far2, r, g, b, t;
register int x, y;

{
  register int filter,low,i,ir,ig,ib;
  register unsigned char *pixel, *red, *green, *blue, *ab;
  gescape_arg arg1,arg2;

  if (near < 0) near = 0;
  if (near2 < 0) near2 = 0;
  if (far < 0) far = 0;
  if (far2 < 0) far2 = 0;

  if (near > 31) near = 31;
  if (near2 > 31) near2 = 31;
  if (far > 31) far = 31;
  if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  filter *= t;

  pixel = buf(x, y);
  ir = ColorTable[*pixel][0];  ig = ColorTable[*pixel][1];  ib = ColorTable[*pixel][2];

  ir += ((r-ir)*filter) >> 16;  ig += ((g-ig)*filter) >> 16;  ib += ((b-ib)*filter) >> 16;
  *pixel = (ir*77 + ig*150 + ib*28) >> 12;
    /* (ir>>6)*25 + (ig>>6)*5 + (ib>>6) +16; */

  if (abuf == TRUE) {
    printf("WARNING alpha buffer for lines not enabled when double buffering!!!\n");
  }
}


/* this code works one channel at a time. therefore it gets called three times for each pixel */
void point1_CRX24_db (x, y, near, far, near2, far2, r, g, b, t)
register int near, far, near2, far2, r, g, b, t;
register int x, y;

{
  register int filter,low;
  register unsigned char *pixel, *red, *green, *blue, *ab;
  gescape_arg arg1,arg2;

  if (near < 0) near = 0;
  if (near2 < 0) near2 = 0;
  if (far < 0) far = 0;
  if (far2 < 0) far2 = 0;

  if (near > 31) near = 31;
  if (near2 > 31) near2 = 31;
  if (far > 31) far = 31;
  if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  filter *= t;

  pixel = buf(x, y);

     low = (*pixel & aa_bankmask) << aa_bankshift;
     low += ((r - low)*filter) >>16;
     low = (low&0xF0) >> aa_bankshift;
    *pixel = (*pixel & aa_otherbank) | low;

  if (abuf == TRUE) {
    printf("WARNING alpha buffer for lines not enabled when double buffering!!!\n");
  }
}


void point1_SRX24 (x, y, near, far, near2, far2, r, g, b, t)
register int near, far, near2, far2, r, g, b, t;
register int x, y;

{
  register int filter,*ibuf;
  register unsigned char *pixel;
  register unsigned char red, green, blue, *ab,ired,igreen,iblue;

  if (near < 0) near = 0;
  if (near2 < 0) near2 = 0;
  if (far < 0) far = 0;
  if (far2 < 0) far2 = 0;

  if (near > 31) near = 31;
  if (near2 > 31) near2 = 31;
  if (far > 31) far = 31;
  if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  filter *= t;

  control [0x003] = 4;                  
  control [0x40bf] = 7;                  
  pixel = framebuf+((x+(y*fbw))<<2);

  if (buf2 == TRUE) {
    ired = (unsigned char) ((*ibuf & 0x00ff0000) >> 16);
    igreen = (unsigned char) ((*ibuf & 0x0000ff00) >> 8);
    iblue = (unsigned char) ((*ibuf & 0x000000ff) >> 0);

    *bufr(x,y) = ired += ((r - ired) * filter) >>16;
    *bufg(x,y) = igreen += ((g - igreen) * filter) >>16;
    *bufb(x,y) = iblue += ((b - iblue) * filter) >>16;
    *ibuf = ((int) ((ired << 16) | (igreen << 8) | iblue));

  }
  else if (buf2 == EXCLUSIVE) {

    *bufr(x,y) += ((r - *bufr(x,y)) * filter) >>16;
    *bufg(x,y) += ((g - *bufg(x,y)) * filter) >>16;
    *bufb(x,y) += ((b - *bufb(x,y)) * filter) >>16;
  }
  else {
    ibuf = (int *)pixel;
    if (filter < 64770) {      /* I'm not sure about this filter thing.  Seems like opaque lines have filter 64770 (255*254) */
      ired = (unsigned char) ((*ibuf & 0x00ff0000) >> 16);
      igreen = (unsigned char) ((*ibuf & 0x0000ff00) >> 8);
      iblue = (unsigned char) ((*ibuf & 0x000000ff) >> 0);

      red = ired += ((r-ired)*filter) >> 16;
      green = igreen += ((g-igreen)*filter) >> 16;
      blue = iblue += ((b-iblue)*filter) >> 16;

    }
    else {
      red = r;
      green = g;
      blue = b;
    }
    *ibuf = ((int) ((red << 16) | (green << 8) | blue));
  }

  if (abuf == TRUE) {
    ab = abuffer + x +(y*fbw);
    *ab += ((255 - *ab) * filter) >>16;
  }
}




/*****************

void point2 (pixel, near, far, near2, far2, r, g, b, t)
register int near, far, near2, far2, r, g, b, t;
register unsigned char *pixel;

{
  register int filter;

  if (near < 0) near = 0;
  else if (near > 31) near = 31;

  if (near2 < 0) near2 = 0;
  else if (near2 > 31) near2 = 31;

  if (far < 0) far = 0;
  else if (far > 31) far = 31;

  if (far2 < 0) far2 = 0;
  else if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  
  control [0x40bf] = 4;
  *pixel -= (*pixel * r * filter) >>16;
  control [0x40bf] = 2;
  *pixel -= (*pixel * g * filter) >>16;
  control [0x40bf] = 1;
  *pixel -= (b * *pixel * filter) >>16;
  
  control [0x40bf] = 7;
}




void point3 (pixel, near, far, near2, far2, r, g, b, t)
register int near, far, near2, far2, r, g, b, t;
register unsigned char *pixel;

{
  register int filter;

  if (near < 0) near = 0;
  if (near2 < 0) near2 = 0;
  if (far < 0) far = 0;
  if (far2 < 0) far2 = 0;

  if (near > 31) near = 31;
  if (near2 > 31) near2 = 31;
  if (far > 31) far = 31;
  if (far2 > 31) far2 = 31;

  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
  
  control [0x40bf] = 4;
  *pixel -= ((255 - *pixel) * r * filter) >>16;
  control [0x40bf] = 2;
  *pixel -= ((255 - *pixel) * g * filter) >>16;
  control [0x40bf] = 1;
  *pixel -= ((255 - *pixel) * b * filter) >>16;

  control [0x40bf] = 7;
}
***********/



