/********************************************************************************************/
/* ONECHAR.C -- By Chris Crowley (VLW)  (cajc@media-lab.media.mit.edu or @leo)              */
/*                                                                                          */
/*              These functions will alter stdin so that a single character can be read.    */
/*											    */
/*		By calling set1c(1, x) before calling getchar, the program will wait until  */
/*		   a key is pressed and then return that character without waiting for a    */
/*		   carriage return.							    */
/*		By calling set1c(0, x) before calling getchar, the program won't even wait  */
/*		   for a key to be pressed.						    */
/*		In other words, getchar will work the same except that it will either       */
/*		   not wait for a carrige return [set1c(1, x)], or it will not wait for     */
/*		   a key stroke [set1c(0, x)].						    */
/*	NOTE:  Always use reset1c() afterwards to set stdin back to its original state!     */
/*											    */
/*		The function kbhit() returns 1 if a key has been pressed, else 0.	    */
/*		Afterwards, a getchar() will return the key that was pressed without        */
/*		   waiting for a carriage return.					    */
/*											    */
/*	ALSO:  these functions won't work for the arrow keys and other simillar keys.	    */
/*											    */
/********************************************************************************************/

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/termio.h>

/*** these types were not included in the 300's -dave small 8/90 ****/
/*** they are in hp-ux 8.0 -- craig kanarick, Mon 27 Jan 93 1:54 am ***/

#ifdef HP-UX.300.7.0
typedef unsigned char cc_t;
typedef unsigned int tcflag_t;
#endif

cc_t save_min, save_time;
tcflag_t save_lflag;

set1c(mode, echo)     /* v 1.0b */
     int mode, echo;
     /***  mode:  1 = wait, 0 = no wait (non-blocking)  ***/
     /***  echo:  1 = echo, 0 = no echo                 ***/
{
  struct termio    termbuf;

  ioctl(0, TCGETA, &termbuf);
  save_lflag = termbuf.c_lflag;
  termbuf.c_lflag &= ~(ICANON | (1-echo)*ECHO);
  save_min = termbuf.c_cc[VMIN];
  save_time = termbuf.c_cc[VTIME];
  if (mode == 0) {
    termbuf.c_cc[VMIN] = 0;
    termbuf.c_cc[VTIME] = 0;
  } else {
    termbuf.c_cc[VMIN] = 4;
    termbuf.c_cc[VTIME] = 255;
  }
  ioctl(0, TCSETA, &termbuf);
}



reset1c()     /* v 1.0b */
{
  struct termio     termbuf;

  ioctl(0, TCGETA, &termbuf);
/*  termbuf.c_lflag |= (ICANON | ECHO); */
  termbuf.c_lflag = save_lflag;
  termbuf.c_cc[VMIN] = save_min;
  termbuf.c_cc[VTIME] = save_time;
  ioctl(0, TCSETA, &termbuf);
}



kbhit()     /* v 1.0b */
{
  char c;

  set1c(0, 0);
  c = getchar();
  if (c!=-1)
    {
      ungetc(c, stdin);
      reset1c();
      return(1);
    }
  reset1c();
  return(0);
}



char get1c(echo)     /* v 1.0b */
     int echo;
{
  char c;

  set1c(1, echo);
  c = getchar();
  if (c == -1) c = 0;
  reset1c();
  return(c);
}

