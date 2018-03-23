/* clipping functions for aa line routines 
*/

#define FALSE 0
#define TRUE 1


static int x1, x2, y1, y2, clipon = FALSE;


/* sets the clip rectangle for aa line drawing
*/

aa_set_clip (xs, ys, xe, ye)
int xs, xe, ys, ye;

{
  if (xs < xe)
  { x1 = xs - 1;
    x2 = xe + 1;
  }
  else
  { x1 = xe - 1;
    x2 = xs + 1;
  }

  if (ys < ye)
  { y1 = ys - 1;
    y2 = ye + 1;
  }
  else
  { y1 = ye - 1;
    y2 = ys + 1;
  }

  clipon = TRUE;
}


/* turns off clipping for aa line drawing
*/

aa_set_clip_off ()

{ clipon = FALSE;
}



aa_clip (x, y)
int x, y;

{ 
  if ((x > x1) && (x < x2) && (y > y1) && (y < y2))
    return (TRUE);
  else
    return (FALSE);
}


get_aa_clip(cx1,cy1,cx2,cy2)
int *cx1,*cy1,*cx2,*cy2;
{
  if (clipon = TRUE)
    {
      *cx1 = x1;
      *cy1 = y1;
      *cx2 = x2;
      *cy2 = y2;
    }
  else {
      *cx1 = 0;
      *cy1 = 0;
      *cx2 = 1280;
      *cy2 = 1024;
  }
}

