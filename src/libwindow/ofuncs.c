#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>



EchoRect(W, color1, color2, color3)     /* v 1.0b */
     struct Window *W;
     int color1, color2, color3;
{
  int OutlineWin(), *colors;
  colors = (int *)malloc(4*sizeof(int));
  *colors = color1;
  *(colors+1) = color2;
  *(colors+2) = color3;
  *(colors+3) = 0;
  AttachCommand(W, ECHO, OutlineWin, (char *)colors);
  AttachCommand(W, NOECHO, OutlineWin, (char *)colors);
  AttachCommand(W, DRAW, OutlineWin, (char *)colors);
}


OutlineWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{

  int screen, *colors;
  float fcolor1, fcolor2, fcolor3;
  struct pickstruct *pick;

  colors = (int *)stuff;
  if (id == ECHO) *(colors+3) = 1;
  else if (id == NOECHO) *(colors+3) = 0;

  if ((W->stat)&&(W->parent->stat)&&((id != DRAW)||(*(colors+3))))
    {
      fcolor1 = (float)(*colors)/255.0;
      fcolor2 = (float)(*(colors+1))/255.0;
      fcolor3 = (float)(*(colors+2))/255.0;
      if (id != DRAW) EchoOff(W->display, 0);

      screen = W->display->fildes;
      drawing_mode(screen, 6);
      perimeter_color(screen, fcolor1, fcolor2, fcolor3);
      interior_style(screen, INT_HOLLOW, TRUE);
      rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
      drawing_mode(screen, 3);
      make_picture_current(screen);

      if (id != DRAW) EchoOn(E_lastx, E_lasty, W->display);
    }

  return(0);
}


EchoText(W, color1, color2, color3)     /* v 1.0b */
     struct Window *W;
     int color1, color2, color3;
{
  int *colors;
  struct stringstruct *stuff;
  int EchoTextWin();

  colors = (int *)malloc(6*sizeof(int));
  *colors = color1;
  *(colors+1) = color2;
  *(colors+2) = color3;
  stuff = (struct stringstruct *)GetStuff(W, SETWORDSPACE);
  *(colors+3) = stuff->red;
  *(colors+4) = stuff->green;
  *(colors+5) = stuff->blue;

  AttachCommand(W, ECHO, EchoTextWin, (char *)colors);
  AttachCommand(W, NOECHO, EchoTextWin, (char *)colors);
}



EchoTextWin(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{

  int screen, *colors, *color;
  float fcolor1, fcolor2, fcolor3;
  struct pickstruct *pick;

  colors = (int *)stuff;
  if (id == ECHO) color = colors;
  else if (id == NOECHO) color = (colors+3);

  if ((W->stat)&&(W->parent->stat)&&(id != DRAW))
    {
      if (id != DRAW) EchoOff(W->display, 0);

      SendMessage(W, CHANGECOLOR, color);

      if (id != DRAW) EchoOn(E_lastx, E_lasty, W->display);
    }

  return(0);
}



