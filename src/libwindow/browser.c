#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

struct browser_struct
{
  struct curstruct *echo;
  int *start_line, *vis_lines, *min_line, *num_lines, selected;
  int r,g,b,dr,dg,db,sr,sg,sb,fr,fg,fb;
  struct Window *headline;
  char **text, directory[200], *suffix;
  char *font;
  int size, label_width, line_height;
};


FileBrowser(mat, directory, suffix, x, y, returnstring)
     struct Window *mat;
     int x, y;
     char *directory, *suffix, *returnstring;
{
  int viswidth, visheight, width, height;
  struct browser_struct *bstruct;
  struct Window *Browser;

  Browser = mat->parent->parent;
  if (Browser->stat)
    {
      printf("Sorry, this browser is already open\n");
      return(-1);
    }

  bstruct = (struct browser_struct *)GetStuff(mat, DO);
  bstruct->suffix = suffix;
  BrowseDirectory(bstruct, directory, suffix);

  /* Have the mat resize itself and adjust all the line values */
  InstallWin(Browser);
  Browser->relx = x;
  Browser->rely = y;
  SendMessage(mat,UPDATE,NULL);
  UnstallWin(Browser);
  Query(Browser); /* The ok and cancel buttons on the scroller will close it later */
  
  printf("filebrowser returning %s\n",wdefstring);
  strcpy(returnstring,wdefstring);
  return((int)query_return);
}


BrowseDirectory(bstruct,string,suffix)
char *string, *suffix;
struct browser_struct *bstruct;
{
  FILE *fopen(), *fp;
  int i, n, dir;
  /* open up the directory, and create the text array of information */
  
  set_font(bstruct->font, bstruct->size, 8);
  bstruct->label_width = string_width(string)+60;

  /* get rid of old directory info */

  if (bstruct->text) {
    for (i = 0; i < *bstruct->num_lines; i++)
      free(*(bstruct->text+i));
    free(bstruct->text);
    bstruct->text = NULL;
  }

  if ((strlen(string) > 1)||(string[0] != '/'))
    while (string[strlen(string)-1] == '/') string[strlen(string)-1] = 0;
  
  /* check whether it's a directory */
  sprintf(wdefstring,"ls -1dp %s > temp.directory", string);
  system(wdefstring);
  fp = fopen("temp.directory", "r");
  fgets(wdefstring,500,fp);
  wdefstring[strlen(wdefstring)-1] = 0;
  fclose(fp);
  
  if (wdefstring[strlen(wdefstring)-1] == '/') {
    /* it is a directory */
    strcpy(bstruct->directory,wdefstring);
    bstruct->directory[strlen(bstruct->directory)-1] = 0;
    dir = 1;
    printf("given a directory, %s\n",bstruct->directory);
  }
  else {
    /* its a file */
    strcpy(wdefstring,string);

    while ((strlen(wdefstring))&&(wdefstring[strlen(wdefstring)-1] != '/')) wdefstring[strlen(wdefstring)-1] = 0;
    if (strlen(wdefstring)) wdefstring[strlen(wdefstring)-1] = 0;
    strcpy(bstruct->directory,wdefstring);

    sprintf(wdefstring,"ls -1d %s/ > temp.directory", bstruct->directory);
    system(wdefstring);
    fp = fopen("temp.directory", "r");
    fscanf(fp, "%s", wdefstring);
    fclose(fp);
    strcpy(bstruct->directory,wdefstring);
    bstruct->directory[strlen(bstruct->directory)-1] = 0;
    printf("given a file in directory %s\n", bstruct->directory);
    dir = 0;
  }

  /* open the directory and read all the info */
  sprintf(wdefstring,"ls -1p %s > temp.directory", bstruct->directory);
  system(wdefstring);
  
  n = 0;
  fp = fopen("temp.directory", "r");
  while (fscanf(fp, "%s", wdefstring) != EOF) n++;
  fclose(fp);

  bstruct->selected = -1;
  *bstruct->num_lines = n;
  bstruct->text = (char **)malloc(n*sizeof(char *));

  n = 0;
  fp = fopen("temp.directory", "r");
  while (fscanf(fp, "%s", wdefstring) != EOF)
    {
      *(bstruct->text+n) = CopyString(wdefstring);
      /* 
	Basename(*(bstruct->text+n), suffix, wdefstring);
	*(bstruct->text+n) = CopyString(wdefstring);
      */
      bstruct->label_width = MAX(bstruct->label_width,string_width(*(bstruct->text+n)));

      if (!dir) {
	/* check to see if this was the given file */
	Basename(string, suffix, wdefstring);
	if (!strcmp(wdefstring,*(bstruct->text+n))) bstruct->selected = n;
      }
      n++;
    }

  fclose(fp);
  system("rm temp.directory");
  printf("ended the browse with directory %s and selected = %d\n",bstruct->directory,bstruct->selected);
  return(dir);
}


/* non-global file browser */

struct Window *MakeFileBrowser(Root, echo, vfont, size, r, g, b, dr, dg, db, fr, fg, fb, sr, sg, sb) 
     struct Window *Root;
     struct curstruct *echo;
{
  struct Window *Browser, *BrowseMat, *pad, *headback, *mover;
  struct Window *resizer, *headline, *OKwin, *Cancel, *Oback, *Cback;
  struct stepperstruct *s;
  struct Window *Up, *Down;
  struct curstruct *upstep_icon, *downstep_icon;
  int p1, p2, p3, sp;
  struct Window *MakeStepper();
  int DoBrowser(), DrawBrowser(), GetBrowseFile();
  char *OKString, *CancelString;
  struct roundrectstruct *rstruct;
  struct browser_struct *bstruct;
  struct curstruct *back;

  Browser = MakeWindow(Root->display, Root->input, Root, 0, 0, 100, 100, "file browser");
  RoundRectify(Browser, r, g, b, 2, NONE, NONE, NONE, .01);
  MoverII(Browser, Browser, 0);
  EchoWrap(Browser, echo, 1, 0, 0);
  InstallWin(Browser);

  mover = MakeWindow(Root->display, Root->input, Browser, 0, 0, 100, 100, "file browser");
  MoverII(mover, Browser, 0);
  EchoWrap(mover, echo, 1, 0, 0);
  RoundRectify(mover, dr, dg, db, 0, NONE, NONE, NONE, .48);
  Maker(mover, 2, 2, -4, 7);
  InstallWin(mover);

  resizer = MakeWindow(Root->display, Root->input, Browser, 0, 0, 100, 100, "file browser");
  ResizerPlus(resizer, Browser, 120, 160, 800, 1000);
  EchoWrap(resizer, echo, 7, 0, 0);
  RoundRectify(resizer, dr, dg, db, 0, NONE, NONE, NONE, .48);
  Maker(resizer, -20, -25, -5, -10);
  InstallWin(resizer);

  BrowseMat = MakeStepper(Root->display, Root->input, Browser, echo, 100, 100, 100, 100, 0,
			  fr, fg, fb, dr, dg, db, sr, sg,sb);
  s = (struct stepperstruct *)GetStuff(BrowseMat, UPDATE);
  pad = s->pad;  /* THIS is the inner window that will be returned to the caller */


  bstruct = (struct browser_struct *)malloc(sizeof(struct browser_struct));
  bstruct->echo = echo;
  bstruct->fr = fr;
  bstruct->fg = fg;
  bstruct->fb = fb;
  bstruct->sr = sr;
  bstruct->sg = sg;
  bstruct->sb = sb;
  bstruct->db = db;
  bstruct->dr = dr;
  bstruct->dg = dg;
  bstruct->r = r;
  bstruct->g = g;
  bstruct->b = b;
  bstruct->text = NULL;
  bstruct->label_width = 0;
  bstruct->line_height = 20;
  bstruct->font = vfont;
  bstruct->size = size;
  bstruct->selected = -1;
  bstruct->start_line = &s->line;
  bstruct->vis_lines = &s->area;
  bstruct->min_line = &s->min;
  bstruct->num_lines = &s->max;

  AttachCommand(pad, DRAW, DrawBrowser, (char *)bstruct);
  AttachCommand(pad, UPDATE, DoBrowser, (char *)bstruct);
  AttachCommand(pad, DO, DoBrowser, (char *)bstruct);
  AttachCommand(pad, MAKE, DoBrowser, (char *)bstruct);
  AttachCommand(pad, OK, DoBrowser, (char *)bstruct);
  AttachCommand(pad, UP, DoBrowser, (char *)bstruct);
  AttachCommand(pad, DOWN, DoBrowser, (char *)bstruct);
  AttachCommand(pad, CANCEL, DoBrowser, (char *)bstruct);
  Maker(BrowseMat, 4, 35, -4, -30);
  InstallWin(BrowseMat);

  /* THE BIG GUYS */
  set_font(vfont,size,8);
  p1 = string_width(" OK ");
  p2 = string_width(" CANCEL ");

  upstep_icon = (struct curstruct *)malloc(sizeof(struct curstruct));
  upstep_icon->rule = redclear;
  LoadBitMap8to24(bw_file("data/icons/upstep_icon"), &upstep_icon->dx, &upstep_icon->dy, &upstep_icon->source, 125, redclear);
  downstep_icon = (struct curstruct *)malloc(sizeof(struct curstruct));
  downstep_icon->rule = redclear;
  LoadBitMap8to24(bw_file("data/icons/downstep_icon"), &downstep_icon->dx, &downstep_icon->dy, &downstep_icon->source, 125, redclear);
  SwapColors(upstep_icon->source, upstep_icon->dx, upstep_icon->dy, VLIGHT, VLIGHT, VLIGHT, fr, fg, fb);
  SwapColors(upstep_icon->source, upstep_icon->dx, upstep_icon->dy, FULL, FULL, FULL, sr, sg, sb);
  SwapColors(downstep_icon->source, downstep_icon->dx, downstep_icon->dy, VLIGHT, VLIGHT, VLIGHT, fr, fg, fb);
  SwapColors(downstep_icon->source, downstep_icon->dx, downstep_icon->dy, FULL, FULL, FULL, sr, sg, sb);

  Up = MakeWindow(Root->display, Root->input, Browser, 20, 0, 20, 20, "slider");
  AttachIcon(Up, upstep_icon);
  Messenger(Up, DO, pad, UP, NULL, JUSTDOWN);
  EchoWrap(Up, echo, JUSTDOWN, 0, 0);
  Maker(Up, 2, 8, 21, 27);
  InstallWin(Up);

  Down = MakeWindow(Root->display, Root->input, Browser, 20, 20, 20, 20, "slider");
  AttachIcon(Down, downstep_icon);
  Messenger(Down, DO, pad, DOWN, NULL, JUSTDOWN);
  EchoWrap(Down, echo, JUSTDOWN, 0, 0);
  Maker(Down, 23, 8, 42, 27);
  InstallWin(Down);


  headback = MakeWindow(Root->display, Root->input, Browser, 0, 0, 100, 100, "background");
  RoundRectify(headback, sr, sg, sb, 0, 0, 0, 0, .03);
  StringWin(headback, bstruct->directory, 9, 1, vfont, size, 8, fr, fg, fb, 0);
  StringWin(headback, bstruct->directory, 8, 0, vfont, size, 8, sr, sg, sb, 0);
  FunctionCaller(headback,DO,GetBrowseFile,pad,1);
  EchoWrap(headback, echo, 1, 0, 0);
  Maker(headback, 50, 11, -7, 11+size+4);
  InstallWin(headback);
  bstruct->headline = headback;

  Oback = MakeWindow(Root->display, Root->input, Browser, 0, 0, 100, 100, "background");
  RoundRectify(Oback, dr, dg, db, 0, 0, 0, 0, .03);
  StringWin(Oback, " OK ", 1, 1, vfont, size, 8, fr, fg, fb, 0);
  StringWin(Oback, " OK ", 0, 0, vfont, size, 8, sr, sg, sb, 0);
  Messenger(Oback, DO, pad, OK, NULL, 1);
  EchoWrap(Oback, echo, 1, 0, 0);
  Maker(Oback, 5, -7-size-4-5, p1+5, -7);
  InstallWin(Oback);

  Cback = MakeWindow(Root->display, Root->input, Browser, 0, 0, 100, 100, "background");
  RoundRectify(Cback, dr, dg, db, 0, 0, 0, 0, .03);
  StringWin(Cback, " CANCEL ", 1, 1, vfont, size, 8, fr, fg, fb, 0);
  StringWin(Cback, " CANCEL ", 0, 0, vfont, size, 8, sr, sg, sb, 0);
  Messenger(Cback, DO, pad, CANCEL, NULL, 1);
  EchoWrap(Cback, echo, 1, 0, 0);
  Maker(Cback, -p2-36, -7-size-4-5, -36, -7);
  InstallWin(Cback);

  /* Fix Sizes */
  TransformCoords(Browser, Browser->relx, Browser->rely, 400, 300);
  UnstallWin(Browser);

  return(pad); /* the opening routine will know to open pad's parent's parent */
}






DrawBrowser(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  int cx1, cy1, cx2, cy2;
  struct clipstruct *cstruct;
  struct browser_struct *parms;
  int startline, length, leftedge, ygap, y, xspace, yspace, xgap, line, maxline;
  float onred, ongreen, onblue, offred, offgreen, offblue;
  char **text;
  int *selection, screen;

  screen = W->display->fildes;

  if (id == DRAW)
    {
      cstruct = (struct clipstruct *)data;
      cx1 = cstruct->x1;  cy1 = cstruct->y1;
      cx2 = cstruct->x2;  cy2 = cstruct->y2;
    }
  else
    {
      cx1 = 0; cy1 = 0;
      cx2 = W->display->viswidth;
      cy2 = W->display->visheight;
    }

  clip_rectangle(screen, (float)cx1, (float)cx2, (float)cy1, (float)cy2);
  set_text_clip_rectangle(cx1, cy1, cx2, cy2);

  parms = (struct browser_struct *)stuff;
  text = parms->text;

  startline = *parms->start_line;
  maxline = MIN(startline+*parms->vis_lines, *parms->num_lines);
  offred = (float)parms->fr/255.0;
  offgreen = (float)parms->fg/255.0;
  offblue = (float)parms->fb/255.0;
  onred = (float)parms->sr/255.0;
  ongreen = (float)parms->sg/255.0;
  onblue = (float)parms->sb/255.0;

  yspace = 3;
  xspace = 3;
  ygap = parms->size;
  leftedge = W->x1+5;
  xgap = 40;
  y = W->y1+5;

  set_font(parms->font, parms->size, 8);
  set_monitor(W->display->bits, W->display->fildes);
  perimeter_color(screen, 0.0, 0.0, 0.0);
  interior_style(screen, INT_SOLID, TRUE);
  fill_color(screen, (float)parms->dr/255.0, (float)parms->dg/255.0, (float)parms->db/255.0);
  line_color(screen, 0.0, 0.0, 0.0);
  rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);

  for (line = startline; line<maxline; line++)
    {
      if (parms->selected == line) fill_color(screen, onred, ongreen, onblue);
      else fill_color(screen, offred, offgreen, offblue);
      rectangle(screen, (float)leftedge, (float)y, (float)(leftedge+xgap-1), (float)(y+ygap-1));
      move2d(screen, (float)(leftedge+xgap), (float)(y+1));
      draw2d(screen, (float)(leftedge+xgap), (float)y+ygap);
      move2d(screen, (float)(leftedge+1), (float)y+ygap);
      draw2d(screen, (float)(leftedge+xgap), (float)y+ygap);
      y += ygap + yspace;
    }
  make_picture_current(screen);
  y = W->y1+3;
  for (line = startline; line<maxline; line++)
    {
      if (parms->selected == line)
	{
	  set_font_color(parms->sr, parms->sg, parms->sb, 0);
	  display_string(*(text+line), leftedge+xgap+xspace, y);
        }
      else
	{
	  set_font_color(parms->fr, parms->fg, parms->fb, 0);
	  display_string(*(text+line), leftedge+xgap+xspace, y);
	}
      y += ygap + yspace;
    }

  clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
		 0.0, (float)((W->display)->height-1));
  make_picture_current(screen);
}



DoBrowser(W, id, data, stuff)     /* v 1.0b */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  FILE *fopen(), *fp;
  int cx1, cy1, cx2, cy2;
  struct clipstruct *cstruct;
  static new=0, mode, doubleclick = 0;
  int x, y, button;
  struct curstruct *echo;
  struct pickstruct *pick;
  struct trapstruct T;
  struct browser_struct *parms;
  int startline, length, leftedge, ygap, ys, yspace, xgap, line, xspace, maxline, t;
  float onred, ongreen, onblue, offred, offgreen, offblue;
  char **text;
  int *selection, notdone, screen, notdone2;

  parms = (struct browser_struct *)stuff;
  echo = parms->echo;
  screen = W->display->fildes;

  text = parms->text;

  startline = *parms->start_line;
  maxline = MIN(startline+*parms->vis_lines, *parms->num_lines);
  offred = (float)parms->fr/255.0;
  offgreen = (float)parms->fg/255.0;
  offblue = (float)parms->fb/255.0;
  onred = (float)parms->sr/255.0;
  ongreen = (float)parms->sg/255.0;
  onblue = (float)parms->sb/255.0;
  set_font(parms->font, parms->size, 8);
  set_monitor(W->display->bits, W->display->fildes);
  set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);

  yspace = 3;
  ygap = parms->size;
  leftedge = W->x1+5;
  xgap = 40;
  xspace = 3;
  perimeter_color(screen, 0.0, 0.0, 0.0);
  interior_style(screen, INT_SOLID, FALSE);
  line_color(screen, 0.0, 0.0, 0.0);

  switch (id) {

  case (DO):

    pick = (struct pickstruct *)data;
    x = pick->x;
    y = pick->y;
    button = pick->button;

    switch (button) {
    case (JUSTDOWN):
      T.window = W, T.until = BEENUP;
      Dispatch(W, TRAP, &T, NULL);
      new = 1;
      doubleclick = 0;
    case (BEENDOWN):
      EchoOff(W->display, 1);
      if (new) {
	notdone = 1;
	ys = W->y1+5;
	for (line = startline; (line< maxline)&&(notdone); line++)
	  {
	    if ((x>W->x1)&&(x<W->x2)&&(y>ys)&&(y<ys+ygap))
	      {
		mode = TRUE;
		fill_color(screen, (float)parms->dr/255.0, (float)parms->dg/255.0, (float)parms->db/255.0);

		/* get rid of lighted object if there is one and if mode is 0 */
		t = parms->selected;
		if ((t>= startline)&&(t<maxline))
		  {
		    int ytop, ybot;
		    
		    ytop = W->y1+5+(t-startline)*(ygap+yspace);
		    ybot = ytop+ygap;
		    rectangle(screen, (float)leftedge+xgap+1, (float)(ytop),
			      (float)(W->x2-1), (float)(ybot+yspace));
		    
		    interior_style(screen, INT_SOLID, TRUE);
		    fill_color(screen, offred, offgreen, offblue);
		    rectangle(screen, (float)leftedge, (float)ytop,
			      (float)(leftedge+xgap-1), (float)ybot-1);
		    make_picture_current(screen);
		    set_font_color(parms->fr, parms->fg, parms->fb, 0);
		    display_string(*(text+t), leftedge+xgap+xspace, ytop-2);
		    ShowTops(W, W->x1, ytop, W->x2, ybot);
		    interior_style(screen, INT_SOLID, FALSE);
		    fill_color(screen, (float)parms->dr/255.0, (float)parms->dg/255.0,
			       (float)parms->db/255.0);
		  }

		rectangle(screen, (float)leftedge+xgap+1, (float)ys, (float)(W->x2-1), (float)(ys+ygap));
		interior_style(screen, INT_SOLID, TRUE);

		
		if (parms->selected == line) fill_color(screen, onred, ongreen, onblue);
		else fill_color(screen, offred, offgreen, offblue);
		rectangle(screen, (float)leftedge, (float)ys, (float)(leftedge+xgap-1), (float)(ys+ygap-1));
		make_picture_current(screen);

		if (parms->selected == line) {
		  if (button == JUSTDOWN) doubleclick = 1;
		  set_font_color(parms->sr, parms->sg, parms->sb, 0);
		  display_string(*(text+line), leftedge+xgap+xspace, ys-2);
		}
		else  {
		  printf("select\n");
		  set_font_color(parms->fr, parms->fg, parms->fb, 0);
		  display_string(*(text+line), leftedge+xgap+xspace, ys-2);
		}
		ShowTops(W, W->x1, ys, W->x2, ys+ygap);
		parms->selected = line;
		notdone = 0;
	      }
	    ys += ygap + yspace;
	  }
	
      } /* if new */
      EchoOn(x, y, W->display);
      break;

    case (JUSTUP):    new = 0;
    case (BEENUP):    UpdateEcho(x, y, W->display, echo);
      break;

    }
    
    if (doubleclick) {
      EchoOff(W->display, 1);
      doubleclick = 0;
      SendMessage(W,DOWN,NULL);
    }
    break;

  case (MAKE):
    {
      int width, lines, dy;

      dy = (W->height-10)/(parms->size+3);
      *parms->vis_lines = MAX(dy, 1);
      *parms->start_line = 0;
    }
    break;

  case (UPDATE):
    {
      int viswidth, visheight, width, height;
      viswidth = W->display->viswidth-20;
      visheight = W->display->height-20;

      width = MIN(MAX(100, parms->label_width+40), viswidth);
      height = MIN(500,*parms->num_lines * parms->line_height+60);
      if (W->parent->parent->relx+width > viswidth) W->parent->parent->relx = viswidth-width;
      if (W->parent->parent->rely+height > visheight) W->parent->parent->rely = visheight-height;
      UpdateSizes(W->parent->parent);
    }
    break;

  case (OK):
  case (CANCEL):
    {
      if (id == OK) query_return = 1;
      else query_return = 0;
      
      if (parms->selected != -1) {
	sprintf(wdefstring,"%s/%s",parms->directory,*(parms->text+parms->selected));
      }

      CloseWindow(W->parent->parent);
    }
    break;

  case (UP):
    {
      int sl;
      printf("up directory\n");
      
      sprintf(wdefstring,"cd %s/../; pwd > %s;",parms->directory, bw_file("temp.directory"));
      printf("%s\n",wdefstring);
      system(wdefstring);
      fp = fopen(bw_file("temp.directory"), "r");
      fscanf(fp, "%s", parms->directory);
      fclose(fp);
      sprintf(wdefstring,"rm %s",bw_file("temp.directory"));
      system(wdefstring);
/*
      sl = strlen(parms->directory);
      parms->directory[sl] = '/';
      parms->directory[sl+1] = 0;
*/
      
      printf("given a file in directory %s\n", parms->directory);
      BrowseDirectory(parms,parms->directory,parms->suffix);
      SendMessage(W,UPDATE,NULL,stuff);
      CloseWindow(W->parent->parent); /* fix this */
      OpenWindow(W->parent->parent);
      
    }
    break;
  case (DOWN):
    {
      int sl;
      printf("down directory\n");

      if (parms->selected != -1) {
	sprintf(wdefstring,"%s/%s",parms->directory,*(parms->text+parms->selected));
	strcpy(parms->directory,wdefstring);
      }
      printf("given a file in directory %s\n", parms->directory);
      if (BrowseDirectory(parms,parms->directory,parms->suffix)) {
	SendMessage(W,UPDATE,NULL,stuff);
	CloseWindow(W->parent->parent); /* fix this */
	OpenWindow(W->parent->parent);
      }
      else {
	query_return = 1;
	sprintf(wdefstring,"%s/%s",parms->directory,*(parms->text+parms->selected));
 	CloseWindow(W->parent->parent);
      }
    }
    break;
  }

  return(0);
}


GetBrowseFile(pad)
struct Window *pad;
{
  struct browser_struct *bstruct;
  char string[150];

  bstruct = (struct browser_struct *)GetStuff(pad,OK);
  strcpy(string,bstruct->directory);
  if (GetString2(pad->parent->parent->parent,E_lastx,E_lasty,"Enter a filename.",string,150))
    {
      if (BrowseDirectory(bstruct,string,bstruct->suffix)) {
	SendMessage(pad,UPDATE,NULL,bstruct);
	CloseWindow(pad->parent->parent); /* fix this */
	OpenWindow(pad->parent->parent);
      }
      else {
	if (bstruct->selected != -1) {
	  printf ("bstruct directory = %s\n",bstruct->directory);
 	  sprintf(wdefstring,"%s/%s",bstruct->directory,*(bstruct->text+bstruct->selected));
	}
	else {
	  printf("-1 browse, returning with original %s\n",string);
	  strcpy(wdefstring,string);
	}
	query_return = 1;
 	CloseWindow(pad->parent->parent);
      }
    }
  return(0);
}
