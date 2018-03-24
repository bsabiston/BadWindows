#include <stdio.h>
#include <starbase.c.h>
#include <math.h>
#include <windows.c.h>
#include <structures.h>



char *Query(Win)     /* v 1.0b */
     struct Window *Win;
{
  struct pickstruct pick;
  struct loopstruct L;
  int x, y;
  float p;
  char c;

  /* fix sizes */
  if (Win->relx+Win->width >= Win->display->viswidth)
    Win->relx = Win->display->viswidth-10-Win->width;
  if (Win->rely+Win->height >= Win->display->visheight)
    Win->rely = Win->display->visheight-10-Win->height;
  TransformCoords(Win, Win->relx, Win->rely, Win->width, Win->height);

  Dispatch(Win,NOECHO,NULL,NULL); /* force an early no echo */
  EchoOff(Win->display, 1);
  InstallWin(Win);
  SaveBackground(Win);
  UpdateWin(Win);
  L.button = NULL;
  L.trapstat = NULL;
  L.Last = Win; 
  L.trap = NULL;

  query_return = NULL;
  if (!screen_toggle)
    ReadLocII(Win->input->fildes, Win->display, &x, &y, &p);
  else
    ReadLocII(Win->input->fildes, NULL, &x, &y, &p);
  while (Win->stat != DEAD)
    {
      pick.character = getchar();
      if ((CurrentTextWindow)&&(pick.character != -1)) SendMessage(CurrentTextWindow, NEWKEY, &pick);

      if (!screen_toggle) pick.button = ReadLocII(Win->input->fildes, Win->display, &(pick.x), &(pick.y), &(pick.p));
      else pick.button = ReadLocII(Win->input->fildes, NULL, &(pick.x), &(pick.y), &(pick.p));
      Dispatch(Win, DO, &pick, &L);
    }

  EchoOff(Win->display, 1);
  return(query_return);
}

