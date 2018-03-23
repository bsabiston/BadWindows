#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>


struct OutDev *ScreenSet24(string, val)     /* v 1.0b */
     char *string;
     int val;
{
  struct OutDev *screen = NULL, *OpenRenaissance();

  if (!(screen = OpenRenaissance("/dev/crt", "hpA1439A", CRX24_FLAGS, val)))
    if (!(screen = OpenRenaissance("/dev/crt", "hpA1454A", CRX24Z_FLAGS, val)))
      if (!(screen = OpenRenaissance("/dev/crt", NULL, SRX24_FLAGS, val)))
	if (!(screen = OpenRenaissance("/dev/graphics", "hp98731", REN24_FLAGS, val)))
	  screen = OpenRenaissance(string, "hp98721", REN24_FLAGS, val);

  return(screen);
}



struct OutDev *OpenCrx24(string1, string2, bits, val)     /* v 1.0b */
     char *string1, *string2;
     int val, bits;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags, ok = 0, odisplay = NULL, type = 0;

  setbuf( stdout, NULL);
  if (val) flags = INIT|THREE_D|MODEL_XFORM;
  else flags = THREE_D|MODEL_XFORM;

  printf("gopen %s %s\n",string1,string2);
  if ((display = gopen(string1, OUTDEV, string2, flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = bits;
      screen->width  = 2048;
      screen->viswidth = 1280;
      screen->visheight = 1024;
      screen->height = 1024;
      mapping_mode(display, FALSE);
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
      vdc_extent(display, (float)0, (float)1023, (float)-5000, (float)1279, (float)0, (float)5000.0);

/*
      arg1.i[0] = 1;
      gescape(display, R_FULL_FRAME_BUFFER, &arg1, &arg2); 
*/

      clip_rectangle(display, (float)0, (float)1279, (float)0, (float)1023);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;
      shade_mode(display, CMAP_FULL|INIT, TRUE);
      
      if (screen->bits == CRX24Z) {
	control [0x0003] = (unsigned char) 0x04;  /* write enable frame buffer */
	control [0x4090] = 0x000000ff;            /* write enable all planes   */
	control [0x4083] = 0x000000ff;            /* display enable all planes */
	control [0x40bf] = 7;                     /* blue                      */
	control [0x40c3] = 2;                     /* turn on 24-bit mode       */
      }
      screen->control = control;
      }
   return(screen);
}




struct OutDev *OpenCrx8(string1, string2, bits, val)     /* v 1.0b */
     char *string1, *string2;
     int val, bits;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags, ok = 0, odisplay = NULL, type = 0;

  setbuf( stdout, NULL);
  if (val) flags = INIT|THREE_D|MODEL_XFORM;
  else flags = THREE_D|MODEL_XFORM;

  printf("gopen %s %s\n",string1,string2);
  if ((display = gopen(string1, OUTDEV, string2, flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = bits;
      screen->width  = 2048;
      screen->viswidth = 1280;
      screen->visheight = 1024;
      screen->height = 1024;
      mapping_mode(display, FALSE);
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0);
      vdc_extent(display, (float)0, (float)1023, (float)-5000, (float)1279, (float)0, (float)5000.0);

      clip_rectangle(display, (float)0, (float)1279, (float)0, (float)1023);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;
      shade_mode(display, CMAP_NORMAL, FALSE);
      screen->control = control;

      InitColorTable16(screen);
      InitColorTable125(screen);
      }
   return(screen);
}



struct OutDev *OpenCrx705(string1, string2, bits, val)     /* v 1.0b */
     char *string1, *string2;
     int val, bits;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags, ok = 0, odisplay = NULL, type = 0;

  setbuf( stdout, NULL);
  if (val) flags = INIT|THREE_D|MODEL_XFORM;
  else flags = THREE_D|MODEL_XFORM;

  printf("gopen %s %s\n",string1,string2);
  if ((display = gopen(string1, OUTDEV, string2, flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = bits;
      screen->width  = 2048;
      screen->viswidth = 1024;
      screen->visheight = 768;
      screen->height = 1024;
      mapping_mode(display, FALSE);
/*      set_p1_p2(display, FRACTIONAL, 0.0, 0.25, 0.0, .8, 1.0, 1.0); */
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0); 
      vdc_extent(display, (float)0, (float)767, (float)-5000, (float)1023, (float)0, (float)5000.0);

      clip_rectangle(display, (float)0, (float)1023, (float)0, (float)767);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;
      shade_mode(display, CMAP_NORMAL, FALSE);
      screen->control = control;

      InitColorTable16(screen);
      InitColorTable125(screen);
    }
   return(screen);
}




struct OutDev *OpenRenaissance(string1, string2, bits, val)     /* v 1.0b */
     char *string1, *string2;
     int val, bits;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags, ok = 0, odisplay = NULL, type = 0;

  setbuf( stdout, NULL);
  if (val) flags = INIT|THREE_D|MODEL_XFORM;
  else flags = THREE_D|MODEL_XFORM;

  printf("gopen %s %s\n",string1,string2);
  if ((display = gopen(string1, OUTDEV, string2, flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = bits;
      screen->width  = 2048;
      screen->viswidth = 1280;
      screen->visheight = 1024;
      screen->height = 1024;
      mapping_mode(display, FALSE);
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
      vdc_extent(display, (float)0, (float)1023, (float)-5000, (float)2047, (float)0, (float)5000.0);

      arg1.i[0] = 1;
      gescape(display, R_FULL_FRAME_BUFFER, &arg1, &arg2);

      clip_rectangle(display, (float)0, (float)1279, (float)0, (float)1023);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      shade_mode(display, CMAP_FULL|INIT, TRUE);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;
      
      control [0x0003] = (unsigned char) 0x04;  /* write enable frame buffer */
      control [0x4090] = 0x000000ff;            /* write enable all planes   */
      control [0x4083] = 0x000000ff;            /* display enable all planes */
      control [0x40bf] = 1;                     /* blue                      */
      control [0x40c3] = 2;                     /* turn on 24-bit mode       */

      screen->control = control;
      }
   return(screen);
}



struct OutDev *ScreenSet4(string, val)     /* v 1.0b */
     char *string;
     int val;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags = 0, color;
  float clist[16][3];

  setbuf( stdout, NULL);
  if (val) flags = INIT;

  if ((display = gopen(string, OUTDEV, "hp300h", flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = TOPCAT;
      screen->width  = 1024;
      screen->viswidth = 1024;
      screen->visheight = 768;
      screen->height = 1024;
      mapping_mode(display, FALSE);

      vdc_extent(display, (float)0, (float)1023, (float)-500, (float)1023, (float)0, (float)500.0);

      arg1.i[0] = 0;
      gescape(display, SWITCH_SEMAPHORE, &arg1, &arg2);

      arg1.i[0] = 1;
      gescape(display, R_FULL_FRAME_BUFFER, &arg1, &arg2);
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

      for(color=0;color<=15;++color)
	{
	  clist[color][0] = (float)color/15.0;
	  clist[color][1] = (float)color/15.0;
	  clist[color][2] = (float)color/15.0;
	}
      define_color_table(display, 0, 16, clist);

      clip_rectangle(display, (float)0, (float)1023, (float)0, (float)1023);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      fill_dither(display, 1);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;

      screen->control = control;
      }

  return(screen);
}



struct OutDev *ScreenSet8(string, val)     /* v 1.0b */
     char *string;
     int val;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags = 0;

  setbuf( stdout, NULL);
  if (val) flags = INIT;

  if ((display = gopen(string, OUTDEV, "hp98710", flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = GATOR;
      screen->width  = 1024;
      screen->viswidth = 1024;
      screen->visheight = 768;
      screen->height = 1024;
      mapping_mode(display, FALSE);

      vdc_extent(display, (float)0, (float)1023, (float)-500, (float)1023, (float)0, (float)500.0);

      arg1.i[0] = 1;
      gescape(display, R_FULL_FRAME_BUFFER, &arg1, &arg2);
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

      clip_rectangle(display, (float)0, (float)1023, (float)0, (float)1023);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;

      screen->control = control;
    }

  return(screen);
}



/* set first sixteen indexes to greyscale */
InitColorTable16(screen)
int screen;
{
  float clist[256][3];
  int color;

  for(color=0;color<=15;++color)
    {
      clist[color][0] = clist[color][1] = clist[color][2] = (float)color/15.0;
      ColorTable[color][0] = ColorTable[color][1] = ColorTable[color][2] = FCON((float)color/15.0); 

      ColorTable[color][0] = (int) ((float)color*(255.0/15.0));
      ColorTable[color][1] = (int) ((float)color*(255.0/15.0));
      ColorTable[color][2] = (int) ((float)color*(255.0/15.0));
    }

  define_color_table(screen, 0, 16, clist);
  return(0);
}


/* create a 5x5x5 color table starting at index 16*/
InitColorTable125(screen)
int screen;
{
  float clist[125][3];
  int color,r,g,b,i;

  i = 0;
  for (r = 0; r < 5; r++)
    for (g = 0; g < 5; g++)
      for (b = 0; b < 5; b++)
	{
	  clist[i][0] = (float)r/4.0;
	  clist[i][1] = (float)g/4.0;
	  clist[i][2] = (float)b/4.0;
	  ColorTable[16+i][0] = (int) ((float)r*(255.0/4.0));
	  ColorTable[16+i][1] = (int) ((float)g*(255.0/4.0));
	  ColorTable[16+i][2] = (int) ((float)b*(255.0/4.0));
/*	  printf("ColorTable %d   %d %d %d    %f %f %f\n",i,ColorTable[i][0],ColorTable[i][1],ColorTable[i][2],
		 clist[i][0],clist[i][1],clist[i][2]); */
	  i++;
	}

  define_color_table(screen, 16, 125, clist);
  return(0);
}


struct OutDev *OpenCrx24X(string1, string2, bits, val)     /* v 1.0b */
     char *string1, *string2;
     int val, bits;
{
  struct OutDev *screen = NULL;
  gescape_arg arg1, arg2;
  unsigned char *cspace, *control;
  int display, flags, ok = 0, odisplay = NULL, type = 0;

  setbuf( stdout, NULL);
  if (val) flags = INIT|THREE_D|MODEL_XFORM;
  else flags = THREE_D|MODEL_XFORM;

  printf("gopen %s %s\n",string1,string2);
  if ((display = gopen(string1, OUTINDEV, string2, flags)) != -1)
    {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = bits;
      screen->width  = 2048;
      screen->viswidth = 1280;
      screen->visheight = 1024;
      screen->height = 1024;
      mapping_mode(display, FALSE); 
      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0);
      vdc_extent(display, (float)0, (float)1023, (float)-5000, (float)1279, (float)0, (float)5000.0);

/*
      arg1.i[0] = 1;
      gescape(display, R_FULL_FRAME_BUFFER, &arg1, &arg2); 
*/

      clip_rectangle(display, (float)0, (float)1279, (float)0, (float)1023);
      clip_depth(display, 0.0, 1000.0);
      clip_indicator(display, CLIP_TO_RECT);
      clear_control(display, CLEAR_VIEWPORT);
      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
      character_height(display, 16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      control = cspace;
      shade_mode(display, CMAP_FULL|INIT, TRUE);
      
      if (screen->bits == CRX24Z) {
	control [0x0003] = (unsigned char) 0x04;  /* write enable frame buffer */
	control [0x4090] = 0x000000ff;            /* write enable all planes   */
	control [0x4083] = 0x000000ff;            /* display enable all planes */
	control [0x40bf] = 7;                     /* blue                      */
	control [0x40c3] = 2;                     /* turn on 24-bit mode       */
      }
      screen->control = control;
      }
   return(screen);
}


