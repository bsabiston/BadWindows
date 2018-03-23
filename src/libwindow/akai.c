

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





/***********************************************/
/*                                             */
/*   AKAI.C                                    */
/*                                             */
/*      Helpfull utilities for using the       */
/*       Akai s900                             */
/*                                             */
/*           -robbed from Dave "IO" Small      */
/*              June 20, 1989                  */
/*                                             */
/***********************************************/

/***********************************************/
/*                                             */
/*  int fildes;                                */
/*  fildes = open_akai(dev);                   */
/*           char *dev                         */
/*      opens the port, and initializes the    */
/*      communications                         */
/*                                             */
/***********************************************/

#include <stdio.h>
#include <termio.h>


/*
==========================================================================
open_akai()

Open Akai, get file discriptor, flush the port, set baud rates, etc.

==========================================================================
 */

open_akai(dev)
char *dev;
{
  int fildes;
  char output[100];

  /***** Set up RS232 connection from bobcat *****/
  if ((fildes = ttyutil_open(dev)) == -1)
    return (-1);

  ttyutil_set_speed(fildes, B19200);
  ttyutil_set_no_stopbits(fildes, 2);
  ttyutil_set_charsize(fildes, CS8);
  ttyutil_parity_off(fildes);

  /**** Set up fildes defaults ********/
  ttyutil_clear(fildes);

  return(fildes);
}
/* open_akai */



int close_akai(fildes)
int fildes;
{
  close(fildes);
}
/* close_akai */




















