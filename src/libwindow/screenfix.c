#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>


lockdev(screen)
     int screen;
{
/*  unsigned char stupid[4]; */
  gescape_arg arg1,arg2;

  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2);

#if 0
  clip_rectangle(screen,0.0,(float)1280,0.0,(float)1024.0); 

/*  dcblock_read(screen,E_lastx,E_lasty,2,2,stupid,FALSE); */
  
  fill_color(screen,0.0,0.0,0.0);
  interior_style(screen,INT_SOLID,FALSE);
  rectangle(screen,0.0,0.0,1.0,1.0); 

  /*      dcblock_write(screen,E_lastx,E_lasty,2,2,stupid,FALSE); STUPID STUPID STUPID fix to starbase bug */
  make_picture_current(screen);
#endif

  return(0);
}


unlockdev(screen)
int screen;
{
  gescape_arg arg1,arg2;
#if 0
  rectangle(screen,0.0,0.0,1.0,1.0);
  make_picture_current(screen);
#endif
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
}


lockdevice(screen)
     int screen;
{
  gescape_arg arg1,arg2;
  gescape(screen, R_LOCK_DEVICE, &arg1, &arg2);
}


unlockdevice(screen)
int screen;
{
  gescape_arg arg1,arg2;
  gescape(screen, R_UNLOCK_DEVICE, &arg1, &arg2); 
}
