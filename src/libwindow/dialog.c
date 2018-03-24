#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

static struct Window *Dialog = NULL, *LoadBar = NULL;

opendialog(Root,x,y,string)
struct Window *Root;
int x,y;
char *string;
{
  int wide;
  if (!Dialog) {
      Dialog = (struct Window *)MakeWindow(Root->display, Root->input, Root, 0, 0, 30, 4, "menu");
      Rectify(Dialog, 255, 255, 255, 1, 0, 0, 0, 2);
      StringWin(Dialog,NULL,5,5,"Swiss",24,8,0,0,0,0);
      Wimp(Dialog);
  }

  set_font("Swiss",24,8);
  wide = string_width(string) + 20;
  TransformCoords(Dialog, x, y, wide, 40);
  SendMessage(Dialog,CHANGESTRING,string);
  OpenWindow(Dialog);
}

closedialog()
{
  CloseWindow(Dialog);
}




openloadbar(Root,x,y,w,h)
struct Window *Root;
int x,y,w,h;
{
  int wide;
  if (!LoadBar) {
      LoadBar = (struct Window *)MakeWindow(Root->display, Root->input, Root, 0, 0, 30, 4, "menu");
      Rectify(LoadBar, 255, 255, 255, 1, 0, 0, 0, 2);
      StringWin(LoadBar,NULL,5,5,"Swiss",24,8,0,0,0,0);
      Wimp(LoadBar);
  }
  TransformCoords(LoadBar, x, y, w, h);
  OpenWindow(LoadBar);
}

updateloadbar(i,l)
int i, l;
{
  float r;

  if ((int)l)   r = (float)i/(float)l;
  else r = 1.0;
  fill_color(LoadBar->display->fildes, FCON(150), FCON(150), FCON(150));
  interior_style(LoadBar->display->fildes,INT_SOLID,FALSE);
  dcrectangle(LoadBar->display->fildes,LoadBar->x1+4,LoadBar->y1+4,LoadBar->x1+4+(int)((LoadBar->width-12)*r),LoadBar->y2-6);
  make_picture_current(LoadBar->display->fildes);
}

closeloadbar()
{
  CloseWindow(LoadBar);
}


