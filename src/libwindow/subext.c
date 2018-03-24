

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





/*** subext.c - dead@media-lab.media.mit.edu - 04/03/85 ***/
/*** Subtract extension from fname only if it is there. ***/

char *Subext(fname, ext)     /* v 1.0b */
     char *fname, *ext;
{
  int fl, el;

  for ( fl = strlen(fname), el = strlen(ext);
       --el > -1 && --fl > -1 && fname[fl] == ext[el]; )
    ;
  if (el == -1)
    fname[fl] = '\0';

  return(fname);
}

