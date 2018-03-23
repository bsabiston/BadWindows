#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>

DoubleBuffer(W,mode)
struct Window *W;
int mode;
{
  if (mode) 
    {
      /* start on the high bank */
      W->display->bits |= DBUFFER; 

/*      leave banks the way they are */
        W->display->bits |= DBANK;
        W->display->bits |= WBANK; 

      double_buffer(W->display->fildes,1|INIT|SUPPRESS_CLEAR|DFRONT,((W->display->bits & BUFBITS)>>8)/2); 
      printf("double buffering on\n");
      
      DrawToInvis(W);
        UpdateWin(W);
      BufSwitch(W);
        UpdateWin(W);
      DrawToVis(W);

    }
  else{
    if (W->display->bits&DBUFFER) {
      /* switch to high bank */
      if (!(W->display->bits&WBANK)) BufSwitch(W);

/*      DrawToInvis(W);
      fill_color(W->display->fildes,0.0,0.0,0.0);
      interior_style(W->display->fildes,INT_SOLID, FALSE);
      dcrectangle(W->display->fildes,0,0,W->display->width-1,W->display->height-1);
      make_picture_current(W->display->fildes);
      DrawToVis(W);
*/
    }

    W->display->bits &= (FULLMASK^(DBUFFER|DBANK|WBANK)); 
    double_buffer(W->display->fildes,0,((W->display->bits & BUFBITS)>>8)/2); 
    }
  return(0);
}



/* double buffering tools */
DrawToInvis(W)
struct Window *W;
{
  /* flips writing to nonvisible bank */
  if (((W->display->bits & WBANK)&&(W->display->bits&DBANK))||
      ((!(W->display->bits & WBANK))&&(!(W->display->bits&DBANK))))
    {
      double_buffer(W->display->fildes,1|SUPPRESS_CLEAR,((W->display->bits & BUFBITS)>>8)/2); 
      W->display->bits ^= WBANK;
    }
}

BufSwitch(W)
struct Window *W;
{
  /* switches writable bank.  doesn't matter which is visible */
    dbuffer_switch(W->display->fildes, (W->display->bits&DBANK)>>BANKSHIFT);
    W->display->bits ^= WBANK;
    W->display->bits ^= DBANK;
}

DrawToVis(W)
struct Window *W;
{
  /* flips writing to visible bank */


    double_buffer(W->display->fildes,1|SUPPRESS_CLEAR|DFRONT,((W->display->bits & BUFBITS)>>8)/2);

    if (W->display->bits & DBANK) W->display->bits |= WBANK;
    else W->display->bits &= (WBANK^FULLMASK);

}


BufUpdateWin(W)
struct Window *W;
{
  if (W->display->bits&DBUFFER){
    DrawToInvis(W);
    UpdateWin(W);
    BufSwitch(W);
    UpdateWin(W);
    DrawToVis(W);
  }
  else UpdateWin(W);
  return(0);
}


BufUp(W,W2)
struct Window *W,*W2;
{
  int BufHalfUpdateWin();
  FunctionCaller(W,DO,BufHalfUpdateWin,W2,JUSTUP);
}


BufHalfUpdateWin(W)
struct Window *W;
{
  if (W->display->bits&DBUFFER){
    DrawToInvis(W);
    UpdateWin(W);
    BufSwitch(W); /* maybe not */
    DrawToVis(W);
  }
  else UpdateWin(W);
  return(0);
}



BufCloseWindow(W)
struct Window *W;
{
  if (W->display->bits&DBUFFER){
    DrawToInvis(W);
    CloseWindow(W);
    BufSwitch(W);
    InstallWin(W);
    CloseWindow(W);
    DrawToVis(W);
  }
  else CloseWindow(W);
  return(0);
}


BufOpenWindow(W)
struct Window *W;
{
  if (W->display->bits&DBUFFER){
    DrawToInvis(W);
    OpenWindow(W);
    BufSwitch(W);
    UnstallWin(W);
    OpenWindow(W);
    DrawToVis(W);
  }
  else OpenWindow(W);
  return(0);
}


BufHalfShowWindow(W,x1,y1,x2,y2)
struct Window *W;
int x1,y1,x2,y2;
{
  if (W->display->bits&DBUFFER){
    DrawToInvis(W);
    ShowWindow(W,x1,y1,x2,y2);
    BufSwitch(W);
/*    ShowWindow(W,x1,y1,x2,y2); */
    DrawToVis(W);
  }
  else ShowWindow(W,x1,y1,x2,y2);
  return(0);
}

BufShowWindow(W,x1,y1,x2,y2)
struct Window *W;
int x1,y1,x2,y2;
{
  if (W->display->bits&DBUFFER){
    DrawToInvis(W);
    ShowWindow(W,x1,y1,x2,y2);
    BufSwitch(W);
    ShowWindow(W,x1,y1,x2,y2);
    DrawToVis(W);
  }
  else ShowWindow(W,x1,y1,x2,y2);
  return(0);
}
