#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>


struct OutDev *OpenMemDriver(odev)
struct OutDev *odev;
{
   struct OutDev *screen = NULL;
   gescape_arg arg1,arg2;
   unsigned char *cspace,*control;   
   int display,flags,ok = 0,odisplay = NULL,type = 0;

   if (((odev->bits&BUFBITS)>>8) == 24) display = gopen("/dev/null",OUTDEV,"SMDpixel3", INIT|THREE_D|MODEL_XFORM);
   else if (((odev->bits&BUFBITS)>>8) == 8)  display = gopen("/dev/null",OUTDEV,"SMDpixel", INIT|THREE_D|MODEL_XFORM);
   else printf("current membuffer bits not supported\n");

   if (display != -1) {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = MEMBUFF|(odev->bits&BUFBITS);
      screen->width  = odev->width;
      screen->viswidth = odev->viswidth;
      screen->visheight = odev->visheight;
      screen->height = odev->height;
      mapping_mode(display,FALSE);

      vdc_extent(display,(float)0,(float)odev->visheight,(float)-5000,(float)odev->width,(float)0,(float)5000.0);

      arg1.i[0] = 0;
      gescape(display,SWITCH_SEMAPHORE, &arg1,&arg2);
      arg1.i[0] = odev->width;
      arg1.i[1] = odev->height;
      gescape(display,SMD_DEFINE_XY,&arg1,&arg2);

      clip_rectangle(display,(float)0,(float)(odev->viswidth-1),(float)0,(float)(odev->visheight-1));
      clip_depth(display,0.0,1000.0);
      clip_indicator(display,CLIP_TO_RECT);
      clear_control(display,CLEAR_VIEWPORT);
      shade_mode(display,CMAP_FULL|INIT,TRUE);
      text_orientation2d(display,0.0,-1.0,1.0,0.0);
      character_height(display,16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      screen->control = cspace;   
      }
   return(screen);
}




struct OutDev *OpenSmallMemDriver(width,height,bits)
int width, height,bits;
{
   struct OutDev *screen = NULL;
   gescape_arg arg1,arg2;
   unsigned char *cspace,*control;   
   int display,flags,ok = 0,odisplay = NULL,type = 0;

   if (bits == 24) display = gopen("/dev/null",OUTDEV,"SMDpixel3", THREE_D|MODEL_XFORM);
   else if (bits == 8) display = gopen("/dev/null",OUTDEV,"SMDpixel", THREE_D|MODEL_XFORM);

   if (display != -1)
      {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = MEMBUFF|(bits<<8);
      screen->width  = width;
      screen->viswidth = width;
      screen->visheight = height;
      screen->height = height;
      mapping_mode(display,FALSE);
      printf("bits %d\n",bits);

      set_p1_p2(display, FRACTIONAL, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
      vdc_extent(display,(float)0,(float)(height-1),(float)-5000,(float)(width-1),(float)0,(float)5000.0);

      arg1.i[0] = 0;
      gescape(display,SWITCH_SEMAPHORE, &arg1,&arg2);
      arg1.i[0] = width;
      arg1.i[1] = height;
      gescape(display,SMD_DEFINE_XY,&arg1,&arg2);

      clip_rectangle(display,(float)0,(float)1279,(float)0,(float)1023);
      clip_depth(display,0.0,1000.0);
      clip_indicator(display,CLIP_TO_RECT);
      clear_control(display,CLEAR_VIEWPORT);
      if (bits == 24) shade_mode(display,CMAP_FULL|INIT,TRUE);
      else shade_mode(display,CMAP_NORMAL,FALSE);
      fill_dither(display, 1);
      text_orientation2d(display,0.0,-1.0,1.0,0.0);
      character_height(display,16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      screen->control = cspace;   
      }
   return(screen);
}




struct OutDev *OpenAlphaDriver()
{
   struct OutDev *screen = NULL;
   gescape_arg arg1,arg2;
   unsigned char *cspace,*control;   
   int display,flags,ok = 0,odisplay = NULL,type = 0;

   if ((display = gopen("/dev/null",OUTDEV,"SMDpixel", THREE_D|MODEL_XFORM)) != -1)
      {
      screen = (struct OutDev *)malloc(sizeof(struct OutDev));
      screen->bits = -8;
      screen->width  = 2048;
      screen->viswidth = 1280;
      screen->visheight = 1024;
      screen->height = 1024;
      mapping_mode(display,FALSE);

      vdc_extent(display,(float)0,(float)1023,(float)-5000,(float)2047,(float)0,(float)5000.0);

      arg1.i[0] = 0;
      gescape(display,SWITCH_SEMAPHORE, &arg1,&arg2);
      arg1.i[0] = 2048;
      arg1.i[1] = 1024;
      gescape(display,SMD_DEFINE_XY,&arg1,&arg2);

      clip_rectangle(display,(float)0,(float)1279,(float)0,(float)1023);
      clip_depth(display,0.0,1000.0);
      clip_indicator(display,CLIP_TO_RECT);
      clear_control(display,CLEAR_VIEWPORT);
      shade_mode(display,CMAP_FULL|INIT,TRUE);
      text_orientation2d(display,0.0,-1.0,1.0,0.0);
      character_height(display,16.0);
      screen->fildes = display;
      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
      screen->buffer = (unsigned char *) arg2.i[1];
      cspace = (unsigned char *) arg2.i[0];
      screen->control = cspace;   
      }
   return(screen);
}



