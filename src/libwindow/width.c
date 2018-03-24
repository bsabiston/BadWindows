akai.c:/*           -robbed from Dave "IO" Small      */
akai.c:  if ((fildes = ttyutil_open(dev)) == -1)
akai.c:    return (-1);
arrow.c:  fd->W = W;
arrow.c:  fd->Arrow = Arrow;
arrow.c:  fd->xoff = xoff;
arrow.c:  fd->yoff = yoff;
arrow.c:  fd->endpoint = endpoint;
arrow.c:    SendMessage(params->Arrow, CHANGEPOINT, (char *)params);
arrow.c:  aa_set_fb ((W->display)->bits, (W->display)->buffer, (W->display)->control);
arrow.c:  fd->x1 = x1;
arrow.c:  fd->y1 = y1;
arrow.c:  fd->x2 = x2;
arrow.c:  fd->y2 = y2;
arrow.c:  fd->width = width;
arrow.c:  fd->arrow_flag = arrow_flag;
arrow.c:  fd->arrow_length = arrow_length;
arrow.c:  fd->arrow_wd = arrow_wd;
arrow.c:  fd->r = r;
arrow.c:  fd->g = g;
arrow.c:  fd->b = b;
arrow.c:  fd->t = 255 - t;
arrow.c:  screen = (W->display)->fildes;
arrow.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
arrow.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
arrow.c:    W->display->control [3] = 4;
arrow.c:    W->display->control [0x40bf] = 7;
arrow.c:    W->display->control [0x40ef] = 0x33;
arrow.c:    drawing_mode(W->display->fildes, 3);
arrow.c:    make_picture_current(W->display->fildes);
arrow.c:    x1 = (float) params->x1;
arrow.c:    y1 = (float) params->y1;
arrow.c:    x2 = (float) params->x2;
arrow.c:    y2 = (float) params->y2;
arrow.c:    aa_set_fb((W->display)->bits, (W->display)->buffer, (W->display)->control);
arrow.c:    aa_set_color (params->r, params->g, params->b);
arrow.c:    aa_set_trans (params->t);
arrow.c:    aa_move (x1, y1, params->width);
arrow.c:    aa_draw (x2, y2, params->width);
arrow.c:    if (params->arrow_flag)
arrow.c:      l1 = params->arrow_length/sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
arrow.c:      l2 = params->arrow_wd/sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
arrow.c:    if (params->arrow_flag == BEGIN || params->arrow_flag == BOTH) {
arrow.c:      aa_move (x1, y1, params->width);
arrow.c:      px = x1 + l1*(x2-x1) - l2*(y2-y1);
arrow.c:      py = y1 + l1*(y2-y1) + l2*(x2-x1);
arrow.c:      aa_draw (px, py, params->width);
arrow.c:      aa_move (x1, y1, params->width);
arrow.c:      px = x1 + l1*(x2-x1) + l2*(y2-y1);
arrow.c:      py = y1 + l1*(y2-y1) - l2*(x2-x1);
arrow.c:      aa_draw (px, py, params->width);
arrow.c:    if (params->arrow_flag == END || params->arrow_flag == BOTH) {
arrow.c:      aa_move (x2, y2, params->width);
arrow.c:      px = x2 - l1*(x2-x1) + l2*(y2-y1);
arrow.c:      py = y2 - l1*(y2-y1) - l2*(x2-x1);
arrow.c:      aa_draw (px, py, params->width);
arrow.c:      aa_move (x2, y2, params->width);
arrow.c:      px = x2 - l1*(x2-x1) - l2*(y2-y1);
arrow.c:      py = y2 - l1*(y2-y1) + l2*(x2-x1);
arrow.c:      aa_draw (px, py, params->width);
arrow.c:    x = pick->x;
arrow.c:    y = pick->y;
arrow.c:    p = pick->p;
arrow.c:    button = pick->button;
arrow.c:      if ( abs(params->x1 - x) < 10 )
arrow.c:	if ( abs(params->y1 - y) < 10 ) 
arrow.c:      if ( abs(params->x2 - x) < 10 )
arrow.c:	if ( abs(params->y2 - y) < 10 ) 
arrow.c:	  params->x1 = x;
arrow.c:	  params->y1 = y;
arrow.c:	  params->x2 = x;
arrow.c:	  params->y2 = y;
arrow.c:	move2d(screen, (float)params->x1, (float)params->y1);
arrow.c:	draw2d(screen, (float)params->x2, (float)params->y2);
arrow.c:	lastx1 = params->x1;
arrow.c:	lasty1 = params->y1;
arrow.c:	lastx2 = params->x2;
arrow.c:	lasty2 = params->y2;
arrow.c:    if (params->x1 < params->x2) {
arrow.c:      minx = (params->x1 - params->width) - 10.0;
arrow.c:      maxx = (params->x2 + params->width) + 10.0;
arrow.c:      minx = (params->x2 - params->width) - 10.0;
arrow.c:      maxx = (params->x1 + params->width) + 10.0;
arrow.c:    if (params->y1 < params->y2) {
arrow.c:      miny = (params->y1 - params->width) - 10.0;
arrow.c:      maxy = (params->y2 + params->width) + 10.0;
arrow.c:      miny = (params->y2 - params->width) - 10.0;
arrow.c:      maxy = (params->y1 + params->width) + 10.0;
arrow.c:    TransformCoords(W, minx, miny, maxx - minx, maxy - miny);
arrow.c:    if (Connect->endpoint == BEGIN) {
arrow.c:      params->x1 = Connect->W->x1 + Connect->xoff;
arrow.c:      params->y1 = Connect->W->y1 + Connect->yoff;
arrow.c:      params->x2 = Connect->W->x1 + Connect->xoff;
arrow.c:      params->y2 = Connect->W->y1 + Connect->yoff;
arrow.c:    if (Connect->endpoint == BEGIN) {
arrow.c:      params->x1 = Connect->W->x1 + Connect->xoff;
arrow.c:      params->y1 = Connect->W->y1 + Connect->yoff;
arrow.c:      params->x2 = Connect->W->x1 + Connect->xoff;
arrow.c:      params->y2 = Connect->W->y1 + Connect->yoff;
arrow.c:  fd->x1 = x1;
arrow.c:  fd->x2 = x2;
arrow.c:  fd->y1 = y1;
arrow.c:  fd->y2 = y2;
arrow.c:  fd->r = r;
arrow.c:  fd->g = g;
arrow.c:  fd->b = b;
arrow.c:  screen = (W->display)->fildes;
arrow.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
arrow.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
arrow.c:    x1 = (float) (W->x1 + params->x1);
arrow.c:    y1 = (float) (W->y1 + params->y1);
arrow.c:    x2 = (float) (W->x1 + params->x2);
arrow.c:    y2 = (float) (W->y1 + params->y2);
arrow.c:    line_color(screen, params->r / 255.0, 
arrow.c:	       params->g / 255.0,
arrow.c:	       params->b / 255.0);
background.c:/* Off-screen background storage for two-screens */
background.c:  E_maxwide[i] = x2-x1+1;
background.c:  E_maxtall[i] = y2-y1+1;
background.c:  O = W->display;
background.c:  if ((W->width > E_maxwide[i]) || (W->height > E_maxtall[i]))
background.c:      E_oldx[i] = W->x1;
background.c:      E_oldy[i] = W->y1;
background.c:      E_wide[i] = W->width;
background.c:      E_tall[i] = W->height;
background.c:      dcblock_move(O->fildes,
background.c:		   W->x1, W->y1,
background.c:		   W->width, W->height,
background.c:      dcblock_move(O->fildes, E_sourcex[i], E_sourcey[i],
background.c:      make_picture_current(O->fildes);
basename.c:/*** basename.c --- dead@media-lab --- 11/25/85 ***/
bevelwin.c:  parms->red = red;
bevelwin.c:  parms->green = green;
bevelwin.c:  parms->blue = blue;
bevelwin.c:  parms->border = border;
bevelwin.c:  parms->bred = bred;
bevelwin.c:  parms->bgreen = bgreen;
bevelwin.c:  parms->bblue = bblue;
bevelwin.c:  parms->shadow = shadow;
bevelwin.c:  parms->bevel = bevel;
bevelwin.c:  parms->light = light;		/* *DKY-25Apr90* */
bevelwin.c:  parms->lred = MIN(MAX(red + light,0),255);
bevelwin.c:  parms->lgreen = MIN(MAX(green + light,0),255);
bevelwin.c:  parms->lblue = MIN(MAX(blue + light,0),255);
bevelwin.c:  parms->rred = MIN(MAX(red - light,0),255);
bevelwin.c:  parms->rgreen = MIN(MAX(green - light,0),255);
bevelwin.c:  parms->rblue = MIN(MAX(blue - light,0),255);
bevelwin.c:  AttachCommand(W, FLIP_BEVEL, BevelRectWin, parms); /* *DKY-25Apr90* */
bevelwin.c:  AttachCommand(W, SET_LIGHT, BevelRectWin, parms); /* *DKY-25Mar91* */
bevelwin.c:  AttachCommand(W, NEWCOLOR, BevelRectWin, parms); /* *DKY-25Mar91* */
bevelwin.c:  screen = (W->display)->fildes;
bevelwin.c:    case FLIP_BEVEL:		/* *DKY-25Apr90* */
bevelwin.c:      parms->light = -parms->light;
bevelwin.c:      parms->lred = MIN(MAX(parms->red + parms->light,0),255);
bevelwin.c:      parms->lgreen = MIN(MAX(parms->green + parms->light,0),255);
bevelwin.c:      parms->lblue = MIN(MAX(parms->blue + parms->light,0),255);
bevelwin.c:      parms->rred = MIN(MAX(parms->red - parms->light,0),255);
bevelwin.c:      parms->rgreen = MIN(MAX(parms->green - parms->light,0),255);
bevelwin.c:      parms->rblue = MIN(MAX(parms->blue - parms->light,0),255);
bevelwin.c:    case SET_LIGHT:		/* *DKY-25Mar91* */
bevelwin.c:      parms->light = (int)data;;
bevelwin.c:      parms->lred = MIN(MAX(parms->red + parms->light,0),255);
bevelwin.c:      parms->lgreen = MIN(MAX(parms->green + parms->light,0),255);
bevelwin.c:      parms->lblue = MIN(MAX(parms->blue + parms->light,0),255);
bevelwin.c:      parms->rred = MIN(MAX(parms->red - parms->light,0),255);
bevelwin.c:      parms->rgreen = MIN(MAX(parms->green - parms->light,0),255);
bevelwin.c:      parms->rblue = MIN(MAX(parms->blue - parms->light,0),255);
bevelwin.c:    case NEWCOLOR:		/* *DKY-25Mar91* */
bevelwin.c:	parms->red = *(colors);
bevelwin.c:	parms->green = *(colors+1);
bevelwin.c:	parms->blue = *(colors+2);
bevelwin.c:      cx1 = cstruct->x1;
bevelwin.c:      cy1 = cstruct->y1;
bevelwin.c:      cx2 = cstruct->x2;
bevelwin.c:      cy2 = cstruct->y2;
bevelwin.c:      cx1 = W->x1;
bevelwin.c:      cy1 = W->y1;
bevelwin.c:      cx2 = W->x2;
bevelwin.c:      cy2 = W->y2;
bevelwin.c:      bevel = parms->bevel;
bevelwin.c:      shadow = parms->shadow;
bevelwin.c:      border = parms->border;
bevelwin.c:      parms->lred = MIN(MAX(parms->red + parms->light,0),255);
bevelwin.c:      parms->lgreen = MIN(MAX(parms->green + parms->light,0),255);
bevelwin.c:      parms->lblue = MIN(MAX(parms->blue + parms->light,0),255);
bevelwin.c:      parms->rred = MIN(MAX(parms->red - parms->light,0),255);
bevelwin.c:      parms->rgreen = MIN(MAX(parms->green - parms->light,0),255);
bevelwin.c:      parms->rblue = MIN(MAX(parms->blue - parms->light,0),255);
bevelwin.c:      cx2 -= shadow; cy2 -= shadow;
bevelwin.c:      red = ((float)parms->red)/255.0;
bevelwin.c:      green = ((float)parms->green)/255.0;
bevelwin.c:      blue = ((float)parms->blue)/255.0;
bevelwin.c:      if (parms->bred == -1)
bevelwin.c:      else red = ((float)parms->bred)/255.0;
bevelwin.c:      green = ((float)parms->bgreen)/255.0;
bevelwin.c:      blue = ((float)parms->bblue)/255.0;
bevelwin.c:      if ((cx1+bevel != cx2-bevel)&&(cy1+bevel != cy2-bevel))
bevelwin.c:		  (float)(cx2-bevel-border),(float)(cy2-bevel-border));
bevelwin.c:      red = ((float)parms->lred)/255.0;
bevelwin.c:      green = ((float)parms->lgreen)/255.0;
bevelwin.c:      blue = ((float)parms->lblue)/255.0;
bevelwin.c:	  draw2d(screen, (float)(cx2-border-s), (float)(cy1+border+s));
bevelwin.c:	  draw2d(screen, (float)(cx1+border+s), (float)(cy2-border-s));
bevelwin.c:      red = ((float)parms->rred)/255.0;
bevelwin.c:      green = ((float)parms->rgreen)/255.0;
bevelwin.c:      blue = ((float)parms->rblue)/255.0;
bevelwin.c:	  move2d(screen, (float)(cx2-border-s), (float)(cy2-border-s));
bevelwin.c:	  draw2d(screen, (float)(cx2-border-s), (float)(cy1+border+s));
bevelwin.c:	  move2d(screen, (float)(cx2-border-s), (float)(cy2-border-s));
bevelwin.c:	  draw2d(screen, (float)(cx1+border+s), (float)(cy2-border-s));
bevelwin.c:      if (parms->bred == -1)
bevelwin.c:      else red = ((float)parms->bred)/255.0;
bevelwin.c:      green = ((float)parms->bgreen)/255.0;
bevelwin.c:      blue = ((float)parms->bblue)/255.0;
bevelwin.c:	move2d(screen, (float)(cx2-border), (float)(cy1+border));
bevelwin.c:	draw2d(screen, (float)(cx2-border-bevel), (float)(cy1+border+bevel));
bevelwin.c:	move2d(screen, (float)(cx2-border), (float)(cy2-border));
bevelwin.c:	draw2d(screen, (float)(cx2-border-bevel), (float)(cy2-border-bevel));
bevelwin.c:	draw2d(screen, (float)(cx1+border+bevel), (float)(cy2-border-bevel));
bevelwin.c:      for (bd = 0; bd < abs(parms->border); bd++)
bevelwin.c:	rectangle(screen, (float)(cx1+bd), (float)(cy1+bd), (float)(cx2-bd), (float)(cy2-bd));
bevelwin.c:      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
bevelwin.c:		     0.0, (float)((W->display)->height-1));
bevelwin.c: * *DKY-30Jul90*
bevelwin.c:  parms->type = type;
bevelwin.c:  parms->shadow = shadow;
bevelwin.c:  parms->border = border;
bevelwin.c:  parms->hatchR = hatchR;
bevelwin.c:  parms->hatchG = hatchG;
bevelwin.c:  parms->hatchB = hatchB;
bevelwin.c:  parms->spacing = spacing;
bevelwin.c:  parms->xvector = xvector;
bevelwin.c:  parms->yvector = yvector;
bevelwin.c:  screen = (W->display)->fildes;
bevelwin.c:    cx1 = cstruct->x1;
bevelwin.c:    cy1 = cstruct->y1;
bevelwin.c:    cx2 = cstruct->x2;
bevelwin.c:    cy2 = cstruct->y2;
bevelwin.c:    cx1 = W->x1;
bevelwin.c:    cy1 = W->y1;
bevelwin.c:    cx2 = W->x2;
bevelwin.c:    cy2 = W->y2;
bevelwin.c:    hatch_type( screen, parms->type);
bevelwin.c:    hatch_spacing( screen, (float)(parms->spacing), VDC_UNITS);
bevelwin.c:    hatch_orientation( screen, (float)(parms->xvector), (float)(parms->yvector));
bevelwin.c:    fill_color(screen, (float)(parms->hatchR) / 255.0, (float)(parms->hatchG) / 255.0, (float)(parms->hatchB) / 255.0);
bevelwin.c:    rectangle(screen, (float)W->x1 + (float)parms->border, (float)W->y1 + (float)parms->border,
bevelwin.c:	      (float)W->x2 - (float)parms->border - (float)parms->shadow,
bevelwin.c:	      (float)W->y2 - (float)parms->border - (float)parms->shadow);
bevelwin.c:    clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
bevelwin.c:		   0.0, (float)((W->display)->height-1));
bitwrite.c:  if (x1-dx > 0) xoff = x1-dx;
bitwrite.c:  if (y1-dy > 0) yoff = y1-dy;
bitwrite.c:  if (dx+sbufw-1 - x2 >0) xcut = x2-dx+1;
bitwrite.c:  if (dy+sbufh-1 - y2 >0) ycut = y2-dy+1;
bitwrite.c:  xcut -= xoff;
bitwrite.c:  ycut -= yoff;
bitwrite.c:  done = sbuf+(xoff+xcut)*3+(yoff+ycut-1)*(sbufw*3);
bitwrite.c:  xgap = dbufw-xcut;
bitwrite.c:  sgap = sbufw-xcut;
bitwrite.c:	if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
bitwrite.c:  if (x1-dx > 0) xoff = x1-dx;
bitwrite.c:  if (y1-dy > 0) yoff = y1-dy;
bitwrite.c:  if (dx+sbufw-1 - x2 >0) xcut = x2-dx+1;
bitwrite.c:  if (dy+sbufh-1 - y2 >0) ycut = y2-dy+1;
bitwrite.c:  xcut -= xoff;
bitwrite.c:  ycut -= yoff;
bitwrite.c:  done = sbuf+(xcut+xoff)*3+(yoff+ycut-1)*(sbufw*3);
bitwrite.c:  xgap = dbufw-xcut;
bitwrite.c:  sgap = sbufw-xcut;
bitwrite.c:	if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
bitwrite.c:  if (x1-dx > 0) xoff = x1-dx;
bitwrite.c:  if (y1-dy > 0) yoff = y1-dy;
bitwrite.c:  if (dx+sbufw-1 - x2 >0) xcut = x2-dx+1;
bitwrite.c:  if (dy+sbufh-1 - y2 >0) ycut = y2-dy+1;
bitwrite.c:  xcut -= xoff;
bitwrite.c:  ycut -= yoff;
bitwrite.c:  done = sbuf+(xcut+xoff)*3+(yoff+ycut-1)*(sbufw*3);
bitwrite.c:  xgap = dbufw-xcut;
bitwrite.c:  sgap = sbufw-xcut;
bitwrite.c:	if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
bitwrite.c:  if (x1-dx > 0) xoff = x1-dx;
bitwrite.c:  if (y1-dy > 0) yoff = y1-dy;
bitwrite.c:  if (dx+sbufw-1 - x2 >0) xcut = x2-dx+1;
bitwrite.c:  if (dy+sbufh-1 - y2 >0) ycut = y2-dy+1;
bitwrite.c:  xcut -= xoff;
bitwrite.c:  ycut -= yoff;
bitwrite.c:  done = sbuf+(xoff+xcut)*3+(yoff+ycut-1)*(sbufw*3);
bitwrite.c:  xgap = dbufw-xcut;
bitwrite.c:  sgap = sbufw-xcut;
bitwrite.c:	if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
bitwrite.c:/*** Some new functions, like the old shapewrites, but with transparency - dave small 9/91 ******/
bitwrite.c:  inv_t = 255 - t;
bitwrite.c:  if (x1-dx > 0) xoff = x1-dx;
bitwrite.c:  if (y1-dy > 0) yoff = y1-dy;
bitwrite.c:  if (dx+sbufw-1 - x2 >0) xcut = x2-dx+1;
bitwrite.c:  if (dy+sbufh-1 - y2 >0) ycut = y2-dy+1;
bitwrite.c:  xcut -= xoff;
bitwrite.c:  ycut -= yoff;
bitwrite.c:  done = sbuf+(xcut+xoff)*3+(yoff+ycut-1)*(sbufw*3);
bitwrite.c:  xgap = dbufw-xcut;
bitwrite.c:  sgap = sbufw-xcut;
bitwrite.c:	    *dpos += (*spos - *dpos) * inv_t >> 8;
bitwrite.c:	    *dpos += (*(spos+1) - *dpos) * inv_t >> 8;
bitwrite.c:	    *dpos += (*(spos+2) - *dpos) * inv_t >> 8;
bitwrite.c:	if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
bitwrite.c:  inv_t = 255 - t;
bitwrite.c:  if (x1-dx > 0) xoff = x1-dx;
bitwrite.c:  if (y1-dy > 0) yoff = y1-dy;
bitwrite.c:  if (dx+sbufw-1 - x2 >0) xcut = x2-dx+1;
bitwrite.c:  if (dy+sbufh-1 - y2 >0) ycut = y2-dy+1;
bitwrite.c:  xcut -= xoff;
bitwrite.c:  ycut -= yoff;
bitwrite.c:  done = sbuf+(xcut+xoff)*3+(yoff+ycut-1)*(sbufw*3);
bitwrite.c:  xgap = dbufw-xcut;
bitwrite.c:  sgap = sbufw-xcut;
bitwrite.c:	    red += ((*spos - red ) * inv_t) >> 8;
bitwrite.c:	    green += (((*spos+1) - green ) * inv_t) >> 8;
bitwrite.c:	    blue += (((*spos+2) - blue ) * inv_t) >> 8;
bitwrite.c:	if (!(--xcount)) {dpos += xgap; spos += sgap*3; xcount = counter;}
blurmap.c:/* code for anti-aliased icons   4/90 */
blurmap.c:  echo->dx = x;
blurmap.c:  echo->dy = y;
blurmap.c:  echo->hotdx = 0;
blurmap.c:  echo->hotdy = 0;
blurmap.c:  echo->rule = 255;  /* for blur maps, rule will be the transparency of the bitmap */
blurmap.c:  echo->id = 1;      /* for blur maps, the never-used id variable will stand for pixel-rep */
blurmap.c:  echo->source = (unsigned char *) malloc(x * y * 4 *sizeof(unsigned char)); 
blurmap.c:  fread (echo->source+x*y*3, sizeof(unsigned char), x * y, fp);
blurmap.c:  fread (echo->source, sizeof(unsigned char), x * y*3, fp);
blurmap.c:  W->width = icon->dx*icon->id;   /* pixel rep is id */
blurmap.c:  W->height = icon->dy*icon->id;  /* pixel rep is id */
blurmap.c:  gescape(W->display->fildes, R_LOCK_DEVICE, &arg1, &arg2);
blurmap.c:      clip_rectangle(W->display->fildes,0.0,(float)W->display->width,0.0,(float)W->display->height);
blurmap.c:/*      dcblock_read(W->display->fildes,E_lastx,E_lasty,2,2,stupid,FALSE);  */
blurmap.c:      fill_color(W->display->fildes,0.0,0.0,0.0);
blurmap.c:      interior_style(W->display->fildes,INT_SOLID,FALSE);
blurmap.c:      rectangle(W->display->fildes,0.0,0.0,1.0,1.0);
blurmap.c:/*      dcblock_write(W->display->fildes,E_lastx,E_lasty,2,2,stupid,FALSE); */
blurmap.c:      make_picture_current(W->display->fildes);
blurmap.c:  Mat_Blurmap(W->display->bits,W->display->buffer,W->display->control,icon->id,W->x1,W->y1,
blurmap.c:	      icon->dx,icon->dy,icon->source,icon->source+icon->dx*icon->dy*3,icon->rule,c->x1,c->y1,c->x2,c->y2);
blurmap.c:  rectangle(W->display->fildes,0.0,0.0,1.0,1.0);
blurmap.c:  make_picture_current(W->display->fildes);
blurmap.c:  gescape(W->display->fildes, R_UNLOCK_DEVICE, &arg1, &arg2);
blurmap.c:/* Draw a anti-aliased bitmap on the screen.
blurmap.c:   rep:        pixel-rep
blurmap.c:  ex = MIN(x+w-1,x2);
blurmap.c:  ey = MIN(y+h-1,y2);
blurmap.c:	xx = (tx - x)/rep;
blurmap.c:	yy = (ty - y)/rep;
blurmap.c:		   *buf = r+(((255-t)* *buf) >> 8);
blurmap.c:		   *buf = g+(((255-t)* *buf) >> 8);
blurmap.c:		   *buf = b+(((255-t)* *buf) >> 8);
blurmap.c:		   red = r + (((255-t) * red)>>8);
blurmap.c:		   green = g + (((255-t) * green)>>8);
blurmap.c:		   blue = b + (((255-t) * blue)>>8);
clip.c:  { x1 = xs - 1;
clip.c:  { x1 = xe - 1;
clip.c:  { y1 = ys - 1;
clip.c:  { y1 = ye - 1;
compresschk.c:   if ((path[strlen(path)-2] == '.')&&(path[strlen(path)-1] == 'Z'))
compresschk.c:       sprintf(command,"uncompress -c <%s>/tmp/temp_bitmap",path);
cornerrect.c:  params->red = red;
cornerrect.c:  params->green = green;
cornerrect.c:  params->blue = blue;
cornerrect.c:  params->shadow = shadow;
cornerrect.c:  params->shadowred = shadowred;
cornerrect.c:  params->shadowgreen = shadowgreen;
cornerrect.c:  params->shadowblue = shadowblue;
cornerrect.c:  params->ul_curve = ul_curve;
cornerrect.c:  params->ur_curve = ur_curve;
cornerrect.c:  params->lr_curve = lr_curve;
cornerrect.c:  params->ll_curve = ll_curve;
cornerrect.c:      params->red = *(colors);
cornerrect.c:      params->green = *(colors+1);
cornerrect.c:      params->blue = *(colors+2);
cornerrect.c:      params->ul_curve = *((int *)data);
cornerrect.c:      params->ur_curve = *((int *)data);
cornerrect.c:      params->lr_curve = *((int *)data);
cornerrect.c:      params->ll_curve = *((int *)data);
cornerrect.c:      cx1 = cstruct->x1;  
cornerrect.c:      cy1 = cstruct->y1;
cornerrect.c:      cx2 = cstruct->x2;  
cornerrect.c:      cy2 = cstruct->y2;
cornerrect.c:      clip_rectangle((W->display)->fildes, cx1, cx2, cy1, cy2);
cornerrect.c:      screen = (W->display)->fildes;
cornerrect.c:      uld = params->ul_curve;
cornerrect.c:      urd = params->ur_curve;
cornerrect.c:      lrd = params->lr_curve;
cornerrect.c:      lld = params->ll_curve;
cornerrect.c:      x1 = W->x1; 
cornerrect.c:      x2 = W->x2;
cornerrect.c:      y1 = W->y1; 
cornerrect.c:      y2 = W->y2;
cornerrect.c:      shadow = params->shadow;
cornerrect.c:	  red = ((float) (params->shadowred)/255.0);
cornerrect.c:	  green = ((float) (params->shadowgreen)/255.0);
cornerrect.c:	  blue = ((float) (params->shadowblue)/255.0);
cornerrect.c:	  x2 -= shadow;
cornerrect.c:	  y2 -= shadow;
cornerrect.c:	      draw2d(screen, fx2 - (float) lrd, fy2);
cornerrect.c:	      draw2d(screen, fx2, fy2 - (float) lrd);
cornerrect.c:		    fx2 - (float) lrd, fy2 - (float) lrd, 
cornerrect.c:		    fx2 - (float) urd, fy1 + (float) urd,
cornerrect.c:		    0.0, -M_PI/2.0, 0.0, 0);
cornerrect.c:		    fx1 + (float) lld, fy2 - (float) lld, 
cornerrect.c:      red = ((float) (params->red) / 255.0);
cornerrect.c:      green = ((float) (params->green) / 255.0);
cornerrect.c:      blue = ((float) (params->blue) / 255.0);
cornerrect.c:      clip_rectangle((W->display)->fildes, 
cornerrect.c:		     (float)0.0, (float)((W->display)->width-1),
cornerrect.c:		     0.0, (float)((W->display)->height-1));
cornerrect.c:      make_picture_current((W->display)->fildes);
cornerrect.c:  if (((uld + urd) >= (x2 - x1)) ||
cornerrect.c:      ((uld + lld) >= (y2 - y1)) ||
cornerrect.c:      ((lld + lrd) >= (x2 - x1)) ||
cornerrect.c:      ((lrd + urd) >= (y2 - y1)))
cornerrect.c:		(float) (x2 - urd), (float) (y1 + urd), 
cornerrect.c:		-M_PI / 2.0, 0.0, 0.0, 0, 0);
cornerrect.c:		(float) (x2 - lrd), (float)(y2 - lrd),
cornerrect.c:		(float) (x1 + lld), (float) (y2 - lld), 
cornerrect.c:  line[0] = (float)(x2 - x1) / 2.0;
cornerrect.c:  line[1] = (float)(y2 - y1) / 2.0;
cornerrect.c:  line[3] = (float)(x2 - x1) / 2.0;
cornerrect.c:  line[4] = (float)(y2 - y1) / 2.0;
cpanel.c:  base = MakeWindow(parent->display, parent->input,  parent, startx, starty, 
cpanel.c:  title_bar = MakeWindow(parent->display, parent->input, base,
cpanel.c:			 sizex-(3*CPANEL_WINDOW_TAB)-CPANEL_TITLE_BAR_HEIGHT,
cpanel.c:  close_box = MakeWindow(parent->display, parent->input, base,
cpanel.c:		    sizex-(CPANEL_WINDOW_TAB+CPANEL_TITLE_BAR_HEIGHT), 
cpanel.c:  retval->base = base;
cpanel.c:  retval->title_bar = title_bar;
cpanel.c:  retval->close_box = close_box;
dbuffer.c:/* WARNING these functions assume that the draw function will only depend on W->x1, W->y1, W->x2, W->y2 
dbuffer.c:/* BufferWrap is used to "double-buffer" a window's draw function, so that it doesn't flicker
dbuffer.c:  db->x = x;
dbuffer.c:  db->y = y;
dbuffer.c:  db->width = width;
dbuffer.c:  db->height = height;
dbuffer.c:  db->bufferOn = TRUE;
dbuffer.c:  C = W->commands;
dbuffer.c:      while ((C->next)&&(C->id != DRAW)) C = C->next;
dbuffer.c:      if (C->id != DRAW)
dbuffer.c:	  C->numfuncs++;
dbuffer.c:	  functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
dbuffer.c:	  args = (char **)malloc(C->numfuncs*sizeof(char *));
dbuffer.c:	  for (i = 0; i < C->numfuncs-1; i++)
dbuffer.c:	      *(functions+i+1) = *(C->functions+i);
dbuffer.c:	      *(args+i+1) = *(C->arguments+i);
dbuffer.c:	  if (C->numfuncs >1) { free(C->functions);   free(C->arguments);}
dbuffer.c:	  C->functions = functions;
dbuffer.c:	  C->arguments = args;
dbuffer.c:  db->x = x;
dbuffer.c:  db->y = y;
dbuffer.c:  if (db->bufferOn == FALSE)   /* S.Librande  9/19/91 */
dbuffer.c:  if( (W->width <= db->width) && (W->height <= db->height)) {
dbuffer.c:    db->x1 = W->x1;
dbuffer.c:    db->y1 = W->y1;
dbuffer.c:    db->x2 = W->x2;
dbuffer.c:    db->y2 = W->y2;
dbuffer.c:    db->cx1 = c->x1;
dbuffer.c:    db->cy1 = c->y1;
dbuffer.c:    db->cx2 = c->x2;
dbuffer.c:    db->cy2 = c->y2;
dbuffer.c:    c->x1 += db->x - W->x1;
dbuffer.c:    c->x2 += db->x - W->x1;
dbuffer.c:    c->y1 += db->y - W->y1;
dbuffer.c:    c->y2 += db->y - W->y1;
dbuffer.c:    W->x1 = db->x;
dbuffer.c:    W->y1 = db->y;
dbuffer.c:    W->x2 = db->x+W->width-1;
dbuffer.c:    W->y2 = db->y+W->height-1;
dbuffer.c:  if (db->bufferOn == FALSE)   /* S.Librande  9/19/91 */
dbuffer.c:  if( (W->width <= db->width) && (W->height <= db->height)) {
dbuffer.c:    x = MAX(c->x1,db->x);
dbuffer.c:    y = MAX(c->y1,db->y);
dbuffer.c:    w = MIN(c->x2,db->x+W->width-1)-x+1;
dbuffer.c:    h = MIN(c->y2,db->y+W->height-1)-y+1;
dbuffer.c:    dcblock_move(W->display->fildes, x, y, w, h, db->x1+(x-db->x),db->y1+(y-db->y));
dbuffer.c:    make_picture_current( W->display->fildes );
dbuffer.c:    c->x1 = db->cx1;
dbuffer.c:    c->y1 = db->cy1;
dbuffer.c:    c->x2 = db->cx2;
dbuffer.c:    c->y2 = db->cy2;
dbuffer.c:    W->x1 = db->x1;
dbuffer.c:    W->y1 = db->y1;
dbuffer.c:    W->x2 = db->x2;
dbuffer.c:    W->y2 = db->y2;
dbuffer.c:    db->bufferOn = TRUE;
dbuffer.c:    db->bufferOn = FALSE;
decorate.c:               +----+----------------------+----+
decorate.c:	       +----+----------------------+----+
decorate.c:	       +----+----------------------+----+
decorate.c:	       +----+----------------------+----+
decorate.c:               x-border-size, y-border-size
decorate.c:	       ul-bitmap-file      optional comments
decorate.c:	       ur-bitmap-file
decorate.c:	       lr-bitmap-file
decorate.c:	       ll-bitmap-file
decorate.c:	       top-bitmap-file
decorate.c:	       right-bitmap-file
decorate.c:	       bottom-bitmap-file
decorate.c:	       left-bitmap-file
decorate.c:	       center-bitmap-file
decorate.c:     This file is read in, parsed and the appropriate bitmaps are Patternify-ed
decorate.c:     onto child windows.  The children are automatically Maker-ed, so if the window
decorate.c:     If the x-border-size is less than 1, then only 3 windows will be made: the
decorate.c:     top, center and bottom.  If the y-border-size is less than 1, only 3 windows
decorate.c:     If the x-border-size or y-border-size are greater than the window size then
decorate.c:    if ( result == -1 )
decorate.c:  x_edgesize = W->width - ( 2 * x_border );
decorate.c:  y_edgesize = W->height - ( 2 * y_border );
decorate.c:    ul = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:    /* Maker( ul, 0,0, x_border - 1, y_border - 1); */ /* No need to Maker this corner*/
decorate.c:    ur = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:				    W->width - x_border, 0,
decorate.c:    Maker( ur, -x_border + 1, 0, 0, y_border - 1 );
decorate.c:    lr = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:				    W->width - x_border, W->height - y_border,
decorate.c:    Maker( lr, -x_border + 1, -y_border + 1, 0, 0 );
decorate.c:    ll = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:				    0, W->height - y_border,
decorate.c:    Maker( ll, 0, -y_border + 1, x_border - 1, 0 );
decorate.c:    top = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:    Maker( top, x_border, 0, -x_border, y_border - 1 );
decorate.c:    bottom = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:				        x_border, W->height - y_border,
decorate.c:    Maker( bottom, x_border, -y_border + 1, -x_border, 0 );
decorate.c:    right = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:				       W->width - x_border, y_border,
decorate.c:    Maker( right, -x_border + 1, y_border, 0, -y_border );
decorate.c:    left = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:    Maker( left, 0, y_border, x_border - 1, -y_border );
decorate.c:  center = (struct Window *)MakeWindow( W->display, W->input, W,
decorate.c:  Maker( center, x_border, y_border, -x_border, -y_border );
decorate.c:     Returns 0 if successful, -1 if the file cannot be opened, or the line
decorate.c:    return( -1 );
decorate.c:    return( -1 );
decorate.c:  for ( index = n - 1; index >= 0; index-- ) {
directory.c:  DirectoryWin = (struct Window *)MakeScroller(Root->display, Root->input, Root, echo, font, size, x, y,
directory.c:  if (! *(commands+numstrings-1))
directory.c:    for (i = 0; i < numstrings-1; i++) if (*(commands+i)) strcpy(title, *(files+i));
directory.c:  if (! *(commands+numstrings-1))
directory.c:  for (i = 0; i < numstrings-1; i++)
directory.c:  if (! *(commands+numstrings-1)) {
directory.c:    for (i = 0; i < numstrings-1; i++)
directory.c:/* strcpy( options, "-1 -t -r" ); */ /* one column, time order, reverse */
directory.c:  strcpy( options, "-1");            /* one column, alphabetic order    */
directory.c:  *(*(files)+*numstrings-1) = CopyString("Type a filename");
directory.c:  *(*(bases)+*numstrings-1) = CopyString("Type a filename");
display.c:  if ((display = gopen(string1, OUTDEV, string2, flags)) != -1)
display.c:      screen->bits = bits;
display.c:      screen->width  = 2048;
display.c:      screen->viswidth = 1280;
display.c:      screen->visheight = 1024;
display.c:      screen->height = 1024;
display.c:      vdc_extent(display, (float)0, (float)1023, (float)-5000, (float)1279.0, (float)0, (float)5000.0);
display.c:      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
display.c:      screen->fildes = display;
display.c:      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
display.c:      screen->buffer = (unsigned char *) arg2.i[1];
display.c:      control [0x40c3] = 2;                     /* turn on 24-bit mode       */
display.c:      screen->control = control;
display.c:  if ((display = gopen(string1, OUTDEV, string2, flags)) != -1)
display.c:      screen->bits = bits;
display.c:      screen->width  = 2048;
display.c:      screen->viswidth = 1280;
display.c:      screen->visheight = 1024;
display.c:      screen->height = 1024;
display.c:      vdc_extent(display, (float)0, (float)1023, (float)-5000, (float)2047, (float)0, (float)5000.0);
display.c:      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
display.c:      screen->fildes = display;
display.c:      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
display.c:      screen->buffer = (unsigned char *) arg2.i[1];
display.c:      control [0x40c3] = 2;                     /* turn on 24-bit mode       */
display.c:      screen->control = control;
display.c:  if ((display = gopen(string, OUTDEV, "hp300h", flags)) != -1)
display.c:      screen->bits = 4;
display.c:      screen->width  = 1024;
display.c:      screen->viswidth = 1024;
display.c:      screen->visheight = 768;
display.c:      screen->height = 1024;
display.c:      vdc_extent(display, (float)0, (float)1023, (float)-500, (float)1023, (float)0, (float)500.0);
display.c:      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
display.c:      screen->fildes = display;
display.c:      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
display.c:      screen->buffer = (unsigned char *) arg2.i[1];
display.c:      screen->control = control;
display.c:  if ((display = gopen(string, OUTDEV, "hp98710", flags)) != -1)
display.c:      screen->bits = 8;
display.c:      screen->width  = 1024;
display.c:      screen->viswidth = 1024;
display.c:      screen->visheight = 768;
display.c:      screen->height = 1024;
display.c:      vdc_extent(display, (float)0, (float)1023, (float)-500, (float)1023, (float)0, (float)500.0);
display.c:      text_orientation2d(display, 0.0, -1.0, 1.0, 0.0);
display.c:      screen->fildes = display;
display.c:      gescape(screen->fildes, R_GET_FRAME_BUFFER, &arg1, &arg2);
display.c:      screen->buffer = (unsigned char *) arg2.i[1];
display.c:      screen->control = control;
dofuncs.c:    beginning of the list and one at the end.    -Bob 3/9/90 **/
dofuncs.c:  a window's DO function. The reason it's called echo-wrap is that it "wraps" itself
dofuncs.c:  you can "wrap" echo-wrap around the DO function, and the cursor stuff will be taken
dofuncs.c:  down on the window, all the do messages will keep going to it until you lift up--even if the cursor
dofuncs.c:  parms->echo = echo;
dofuncs.c:  parms->whenmask = whenmask;
dofuncs.c:  parms->now = now;
dofuncs.c:  parms->trapflag = trapflag;
dofuncs.c:     the whenmask is a four-bit value. each bit represents a mouse button condition in the do function.
dofuncs.c:     setting a bit means that echo-wrap will call it's subcommands on that mouse condition.
dofuncs.c:     for example, a value of 7 means that the window's  real do-function will be called all the
dofuncs.c:     use now=0 if the action taking place in the real do-function is all starbase. Use 1
dofuncs.c:     if it's direct frame-buffer access. This variable tells the cursor routines when to
dofuncs.c:  C = W->commands;
dofuncs.c:      while ((C->next)&&(C->id != DO)) C = C->next;
dofuncs.c:      if (C->id != DO)
dofuncs.c:	  C->numfuncs++;
dofuncs.c:	  functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
dofuncs.c:	  args = (char **)malloc(C->numfuncs*sizeof(char *));
dofuncs.c:	  for (i = 0; i < C->numfuncs-1; i++)
dofuncs.c:	      *(functions+i+1) = *(C->functions+i);
dofuncs.c:	      *(args+i+1) = *(C->arguments+i);
dofuncs.c:	  if (C->numfuncs >1) { free(C->functions);   free(C->arguments);}
dofuncs.c:	  C->functions = functions;
dofuncs.c:	  C->arguments = args;
dofuncs.c:  switch (pick->button)
dofuncs.c:      flag = parms->whenmask & 1;
dofuncs.c:      if (parms->trapflag)  T.window = W, T.until = BEENUP, Dispatch(W, TRAP, &T, NULL), new = 1;
dofuncs.c:      flag = (parms->whenmask & 2) && (!parms->trapflag||new);
dofuncs.c:      flag = (parms->whenmask & 4) && (!parms->trapflag||new);
dofuncs.c:      flag = parms->whenmask & 8;
dofuncs.c:      EchoOff(W->display, parms->now);
dofuncs.c:      UpdateEcho(pick->x, pick->y, W->display, parms->echo);
dofuncs.c:  EchoOn(pick->x, pick->y, W->display);
dofuncs.c:  if (((struct pickstruct *)data)->button == JUSTDOWN) Quit();
dofuncs.c:  if (((struct pickstruct *)data)->button == JUSTDOWN)
dofuncs.c:      while (R->parent) R = R->parent;
dofuncs.c:  if (W->stat) CloseWindow(stuff); 
dofuncs.c:  if ((((struct pickstruct *)data)->button == JUSTUP)&&(W->stat)) OpenWindow(stuff);
dofuncs.c:  if ((((struct pickstruct *)data)->button == JUSTUP)&&(W->stat)) UpdateWin(stuff);
dofuncs.c:  parms->W = M;
dofuncs.c:  parms->id = id;
dofuncs.c:  parms->data = data;
dofuncs.c:  parms->mask = mask;
dofuncs.c:  parms->W = M;
dofuncs.c:    switch (((struct pickstruct *)data)->button)
dofuncs.c:      case (JUSTDOWN): flag = parms->mask & 1;
dofuncs.c:      case (JUSTUP):   flag = parms->mask & 2;
dofuncs.c:      case (BEENDOWN): flag = parms->mask & 4;
dofuncs.c:      case (BEENUP):   flag = parms->mask & 8;
dofuncs.c:  if (flag) val = SendMessage(parms->W, parms->id, parms->data);
dofuncs.c:  parms->function = function;
dofuncs.c:  parms->argument = argument;
dofuncs.c:  parms->mask = mask;
dofuncs.c:    switch (((struct pickstruct *)data)->button)
dofuncs.c:      case (JUSTDOWN): flag = parms->mask & 1;
dofuncs.c:      case (JUSTUP):   flag = parms->mask & 2;
dofuncs.c:      case (BEENDOWN): flag = parms->mask & 4;
dofuncs.c:      case (BEENUP):   flag = parms->mask & 8;
dofuncs.c:  if (flag) val = (*parms->function)(parms->argument);
dofuncs.c: *    Currently you can not have more than 10 arguments -- but feel free to change that.
dofuncs.c: *    *DKY-13Feb91*
dofuncs.c:  parms->function = function;
dofuncs.c:  parms->numArgs = numArgs;
dofuncs.c:    printf( "ERROR: MFunctionCaller() -- Too many arguments (%d).  No command attached.\n", numArgs);
dofuncs.c:    parms->args[argno] = arg;
dofuncs.c:  parms->mask = (int)va_arg( ap, char *);
dofuncs.c:    switch (((struct pickstruct *)data)->button)
dofuncs.c:      case (JUSTDOWN): flag = parms->mask & 1;
dofuncs.c:      case (JUSTUP):   flag = parms->mask & 2;
dofuncs.c:      case (BEENDOWN): flag = parms->mask & 4;
dofuncs.c:      case (BEENUP):   flag = parms->mask & 8;
dofuncs.c:    switch( parms->numArgs)	/* gross, but how else can it be done? */
dofuncs.c:	val = (*parms->function)();
dofuncs.c:	val = (*parms->function)(parms->args[0]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
dofuncs.c:				 parms->args[5]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
dofuncs.c:				 parms->args[5], parms->args[6]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
dofuncs.c:				 parms->args[5], parms->args[6], parms->args[7]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
dofuncs.c:				 parms->args[5], parms->args[6], parms->args[7], parms->args[8]);
dofuncs.c:	val = (*parms->function)(parms->args[0], parms->args[1], parms->args[2], parms->args[3], parms->args[4],
dofuncs.c:				 parms->args[5], parms->args[6], parms->args[7], parms->args[8], parms->args[9]);
dofuncs.c:	printf( "ERROR: Multi_CallFunction() -- can't deal with %d arguments.\n", parms->numArgs);
dofuncs.c:  x = pick->x;
dofuncs.c:  y = pick->y;
dofuncs.c:  dx = x-W->x1;
dofuncs.c:  dy = y-W->y1;
dofuncs.c:  if  (pick->button == JUSTDOWN)
dofuncs.c:      pick->x = W->x1+dx;
dofuncs.c:      pick->y = W->y1+dy;
dofuncs.c:      /* printf( "new position: x=%d y=%d width=%d height=%d\n", W->x1, W->y1, W->width, W->height); */
dofuncs.c:  parent = W->parent;
dofuncs.c:  dx = *x - W->x1;
dofuncs.c:  dy = *y - W->y1;
dofuncs.c:  width = W->width;
dofuncs.c:  height = W->height;
dofuncs.c:  display = (W->display)->fildes;
dofuncs.c:  locator = (W->input)->fildes;
dofuncs.c:  x1 = parent->x1;
dofuncs.c:  y1 = parent->y1;
dofuncs.c:  x2 = parent->x2;
dofuncs.c:  y2 = parent->y2;
dofuncs.c:  xs = *x-dx; ys = *y-dy; xe = xs+width-1; ye = ys+height-1;
dofuncs.c:      if (!screen_toggle) value = ReadLocII(locator, W->display, x, y, &p);
dofuncs.c:      if ((*x-dx)<x1) *x= x1+dx;
dofuncs.c:      if ((*y-dy)<y1) *y= y1+dy;
dofuncs.c:      if (*x-dx+width-1>x2) *x = x2-(width-1)+dx;
dofuncs.c:      if (*y-dy+height-1>y2) *y = y2-(height-1)+dy;
dofuncs.c:      *x -= dx; *y -= dy;
dofuncs.c:      if ((*x != xs)||(*y != ys)||(*x+width-1 != xe)||(*y+height-1 != ye))
dofuncs.c:	  xs = *x; ys = *y; xe = *x+width-1; ye = *y+height-1;
dofuncs.c:  params->movewin = M;
dofuncs.c:  params->hgrid   = hgrid;
dofuncs.c:  params->vgrid   = vgrid;
dofuncs.c:  movewin = snap->movewin;
dofuncs.c:  hgrid = snap->hgrid;
dofuncs.c:  vgrid = snap->vgrid;
dofuncs.c:  x = pick->x;
dofuncs.c:  y = pick->y;
dofuncs.c:  dx = x-W->x1;
dofuncs.c:  dy = y-W->y1;
dofuncs.c:  if (pick->button == JUSTDOWN)
dofuncs.c:      pick->x = W->x1+dx;
dofuncs.c:      pick->y = W->y1+dy;
dofuncs.c:  parent = W->parent;
dofuncs.c:  dx = *x - W->x1;
dofuncs.c:  dy = *y - W->y1;
dofuncs.c:  width = W->width;
dofuncs.c:  height = W->height;
dofuncs.c:  display = (W->display)->fildes;
dofuncs.c:  locator = (W->input)->fildes;
dofuncs.c:  x1 = parent->x1;
dofuncs.c:  y1 = parent->y1;
dofuncs.c:  x2 = parent->x2;
dofuncs.c:  y2 = parent->y2;
dofuncs.c:  xs = *x-dx; ys = *y-dy; xe = xs+width-1; ye = ys+height-1;
dofuncs.c:      if (!screen_toggle) value = ReadLocII(locator, W->display, x, y, &p);
dofuncs.c:      if ((*x-dx)<x1) *x= x1+dx;
dofuncs.c:      if ((*y-dy)<y1) *y= y1+dy;
dofuncs.c:      if (*x-dx+width-1>x2) *x = x2-(width-1)+dx;
dofuncs.c:      if (*y-dy+height-1>y2) *y = y2-(height-1)+dy;
dofuncs.c:      *x -= dx; *y -= dy;
dofuncs.c:      if ((*x != xs)||(*y != ys)||(*x+width-1 != xe)||(*y+height-1 != ye))
dofuncs.c:	  xs = *x; ys = *y; xe = *x+width-1; ye = *y+height-1;
dofuncs.c:  GetPoints(W->parent,&x1,&y1,&x2,&y2);
dofuncs.c:  if (nx+W->width-1<=x2)  xpos = nx-x1;
dofuncs.c:  else                    xpos = W->relx;
dofuncs.c:  if (ny+W->height-1<=y2) ypos = ny-y1;
dofuncs.c:  else                    ypos = W->rely;
dofuncs.c:    xpos -= hd;
dofuncs.c:      if ((xpos+hgrid-hd) < W->parent->width)
dofuncs.c:	xpos += (hgrid - hd);
dofuncs.c:	xpos -= hd;
dofuncs.c:    ypos -= vd;
dofuncs.c:      if ((ypos+vgrid-vd) < W->parent->height)
dofuncs.c:	ypos += (vgrid - vd);
dofuncs.c:	ypos -= vd;
dofuncs.c:  W->relx = xpos;
dofuncs.c:  W->rely = ypos;
dofuncs.c: * *DKY-13Sep90*
dofuncs.c:  parms->windowToMove = M;
dofuncs.c:  switch (pick->button)
dofuncs.c:      parms->lastX = pick->x;
dofuncs.c:      parms->lastY = pick->y;
dofuncs.c:	parms->lastX = pick->x;
dofuncs.c:	parms->lastY = pick->y;
dofuncs.c:      if( (pick->x != parms->lastX) || (pick->y != parms->lastY)) {
dofuncs.c:	moveMe = parms->windowToMove;
dofuncs.c:	deltaX = parms->lastX - pick->x;
dofuncs.c:	deltaY = parms->lastY - pick->y;
dofuncs.c:	newX = moveMe->x1 - deltaX;
dofuncs.c:	newY = moveMe->y1 - deltaY;
dofuncs.c:	if( newX < moveMe->parent->x1)
dofuncs.c:	  newX = moveMe->parent->x1;
dofuncs.c:	else if( (newX + moveMe->width) > moveMe->parent->x2)
dofuncs.c:	  newX = moveMe->parent->x2 - moveMe->width + 1;
dofuncs.c:	if( newY < moveMe->parent->y1)
dofuncs.c:	  newY = moveMe->parent->y1;
dofuncs.c:	else if( (newY + moveMe->height) > moveMe->parent->y2)
dofuncs.c:	  newY = moveMe->parent->y2 - moveMe->height + 1;
dofuncs.c:	parms->lastX = pick->x;
dofuncs.c:	parms->lastY = pick->y;
dofuncs.c:  if( (pick->button == JUSTUP) ||  (pick->button == BEENUP)) {
dofuncs.c:/*--- W: Window to which the function is attach, R: Window to be resized, coordinates are the min and max position
dofuncs.c:-----------------------------------------------------------------------------------------------------------------*/
dofuncs.c:  params->movewin = R;
dofuncs.c:  params->xmin = xmin;
dofuncs.c:  params->ymin = ymin;
dofuncs.c:  params->xmax = xmax;
dofuncs.c:  params->ymax = ymax;
dofuncs.c:      RWindow = mstruct->movewin;
dofuncs.c:      x = pick->x;
dofuncs.c:      y = pick->y;
dofuncs.c:      button = pick->button;
dofuncs.c:	  cx = RWindow->x2-x; cy = RWindow->y2-y;
dofuncs.c:	  rootx = RWindow->x1; rooty = RWindow->y1;
dofuncs.c:	  StartEorBox(W->display->fildes, rootx, rooty, x, y);
dofuncs.c:	      EndEorBox(W->display->fildes);
dofuncs.c:	      x -= (rootx-1);
dofuncs.c:	      y -= (rooty-1);
dofuncs.c:	      TransformCoords(RWindow, rootx-(RWindow->parent)->x1, rooty-(RWindow->parent)->y1, x, y);
dofuncs.c:	      /* printf("x %d  y %d  w %d  h %d\n", RWindow->x1, RWindow->y1, x, y); */
dofuncs.c:	      x += (rootx-1);
dofuncs.c:	      y += (rooty-1);
dofuncs.c:	      if ((x <= (RWindow->parent)->x2)&&(y<= (RWindow->parent)->y2) &&
dofuncs.c:		  (x >= (RWindow->parent)->x1) && (y >= (RWindow->parent)->y1))
dofuncs.c:		  if (x-rootx+1 < mstruct->xmin) x = rootx+mstruct->xmin-1;
dofuncs.c:		  if (x-rootx+1 > mstruct->xmax) x = rootx+mstruct->xmax-1;
dofuncs.c:		  if (y-rooty+1 < mstruct->ymin) y = rooty+mstruct->ymin-1;
dofuncs.c:		  if (y-rooty+1 > mstruct->ymax) y = rooty+mstruct->ymax-1;
dofuncs.c:		  UpdateEorBox(W->display->fildes, rootx, rooty, x, y);
dofuncs.c:-----------------------------------------------------------------------------------------------------------*/
dofuncs.c:ResizerPlusSquare(W, R, xmin, xmax)     /* DB 8-23-91 */
dofuncs.c:  params->movewin = R;
dofuncs.c:  params->xmin = xmin;
dofuncs.c:  params->ymin = xmin;
dofuncs.c:  params->xmax = xmax;
dofuncs.c:  params->ymax = xmax;
dofuncs.c:      RWindow = mstruct->movewin;
dofuncs.c:      x = pick->x;
dofuncs.c:      y = pick->x;
dofuncs.c:      button = pick->button;
dofuncs.c:	  cx = RWindow->x2-x; cy = RWindow->x2-x;
dofuncs.c:	  rootx = RWindow->x1; rooty = RWindow->y1;
dofuncs.c:	  StartEorBox(W->display->fildes, rootx, rooty, x, y);
dofuncs.c:	      EndEorBox(W->display->fildes);
dofuncs.c:	      x -= (rootx-1);
dofuncs.c:	      y -= (rootx-1);
dofuncs.c:	      TransformCoords(RWindow, rootx-(RWindow->parent)->x1, rootx-(RWindow->parent)->x1, x, x);
dofuncs.c:	      /* printf("x %d  y %d  w %d  h %d\n", RWindow->x1, RWindow->y1, x, y); */
dofuncs.c:	      x += (rootx-1);
dofuncs.c:	      y += (rootx-1);
dofuncs.c:	      if ((x <= (RWindow->parent)->x2)&&(y<= (RWindow->parent)->x2) &&
dofuncs.c:		  (x >= (RWindow->parent)->x1) && (y >= (RWindow->parent)->x1))
dofuncs.c:		  if (x-rootx+1 < mstruct->xmin) x = rootx+mstruct->xmin-1;
dofuncs.c:		  if (x-rootx+1 > mstruct->xmax) x = rootx+mstruct->xmax-1;
dofuncs.c:		  if (y-rooty+1 < mstruct->ymin) y = rooty+mstruct->xmin-1;
dofuncs.c:		  if (y-rooty+1 > mstruct->ymax) y = rooty+mstruct->xmax-1;
dofuncs.c:		  UpdateEorBox(W->display->fildes, rootx, rooty, x, y);
dofuncs.c:/*--- W: Window to which the function is attach, the same as the window to be resized. Margin is the active distance
dofuncs.c:-----------------------------------------------------------------------------------------------------------------*/
dofuncs.c:      x = pick->x;
dofuncs.c:      y = pick->y;
dofuncs.c:      button = pick->button;
dofuncs.c:	  if (x< W->x1+margin)
dofuncs.c:	      if (y<W->y1+margin) corner = 1;
dofuncs.c:	      else if (y> W->y2-margin) corner = 3;
dofuncs.c:	  else if (x > W->x2-margin){
dofuncs.c:	      if (y<W->y1+margin) corner = 2;
dofuncs.c:	      else if (y> W->y2-margin) corner = 4;
dofuncs.c:		cx = W->x1-x; cy = W->y1-y;
dofuncs.c:		rootx = W->x2; rooty = W->y2;
dofuncs.c:		cx = W->x2-x; cy = W->y1-y;
dofuncs.c:		rootx = W->x1; rooty = W->y2;
dofuncs.c:		cx = W->x1-x; cy = W->y2-y;
dofuncs.c:		rootx = W->x2; rooty = W->y1;
dofuncs.c:		cx = W->x2-x; cy = W->y2-y;
dofuncs.c:		rootx = W->x1; rooty = W->y1;
dofuncs.c:		StartEorBox(W->display->fildes, rootx, rooty, x, y);
dofuncs.c:	      EndEorBox(W->display->fildes);
dofuncs.c:	      x -= (rootx-1);
dofuncs.c:	      y -= (rooty-1);
dofuncs.c:	      TransformCoords(W, rootx-(W->parent)->x1, rooty-(W->parent)->y1, x, y);
dofuncs.c:	      x += (rootx-1);
dofuncs.c:	      y += (rooty-1);
dofuncs.c:	      if ((x <= (W->parent)->x2)&&(y<= (W->parent)->y2) &&
dofuncs.c:		  (x >= (W->parent)->x1) && (y >= (W->parent)->y1))
dofuncs.c:		  if (abs(x-rootx+1) < *(nums+1)) x = ox;
dofuncs.c:		  if (abs(x-rootx+1) > *(nums+3)) x = ox;
dofuncs.c:		  if (abs(y-rooty+1) < *(nums+2)) y = oy;
dofuncs.c:		  if (abs(y-rooty+1) > *(nums+4)) y = oy;
dofuncs.c:		  UpdateEorBox(W->display->fildes, rootx, rooty, x, y);
dofuncs.c:  params->closewin = CWin;
dofuncs.c:  params->openwin = OWin;
dofuncs.c:  CWindow = mstruct->closewin;
dofuncs.c:  OWindow = mstruct->openwin;
dofuncs.c:  if (pick->button ==JUSTDOWN) {
dofuncs.c:    GetPoints(OWindow, &(OWindow->x1), &(OWindow->y1), &(OWindow->x2),
dofuncs.c:	      &(OWindow->y2));
dofuncs.c:  screen = (W1->display)->fildes;
dofuncs.c:  x1 = W1->x1;
dofuncs.c:  y1 = W1->y1;
dofuncs.c:  x2 = W1->x2;
dofuncs.c:  y2 = W1->y2;
dofuncs.c:      Ipoint(W1->x1, W2->x1, &x1, t, 150);
dofuncs.c:      Ipoint(W1->x2, W2->x2, &x2, t, 150);
dofuncs.c:      Ipoint(W1->y1, W2->y1, &y1, t, 150);
dofuncs.c:      Ipoint(W1->y2, W2->y2, &y2, t, 150);
dofuncs.c:  diff = to-from;
dofuncs.c:  parms->echo = echo;
dofuncs.c:  parms->functions = NULL;
dofuncs.c:  parms->arguments = NULL;
dofuncs.c:  parms->numfuncs = 0;
dofuncs.c:  parms->whenmask = whenmask;
dofuncs.c:  parms->now = now;
dofuncs.c:  parms->trapflag = trapflag;
dofuncs.c:     the whenmask is a four-bit value. each bit represents a mouse button condition in the do function.
dofuncs.c:     setting a bit means that echo-wrap will call it's subcommands on that mouse condition.
dofuncs.c:     for example, a value of 7 means that the window's  real do-function will be called all the
dofuncs.c:     use now=0 if the action taking place in the real do-function is all starbase. Use 1
dofuncs.c:     if it's direct frame-buffer access. This variable tells the cursor routines when to
dofuncs.c:  C = W->commands;
dofuncs.c:      while ((C->next)&&(C->id != DO)) C = C->next;
dofuncs.c:      if (C->id != DO) AttachCommand(W, DO, EchoWrapWin, parms);   /* no DO function */
dofuncs.c:	  parms->functions = C->functions;
dofuncs.c:	  parms->arguments = C->arguments;
dofuncs.c:	  parms->numfuncs = C->numfuncs;
dofuncs.c:	  C->numfuncs = 1;
dofuncs.c:	  C->functions = (int (**)())malloc(sizeof(int (*)()));
dofuncs.c:	  C->arguments = (char **)malloc(sizeof(char *));
dofuncs.c:	  *C->functions = EchoWrapWin;
dofuncs.c:	  *C->arguments = (char *)parms;
dofuncs.c:  switch (pick->button)
dofuncs.c:      flag = parms->whenmask & 1;
dofuncs.c:      if (parms->trapflag)  T.window = W, T.until = BEENUP, Dispatch(W, TRAP, &T, NULL), new = 1;
dofuncs.c:      flag = (parms->whenmask & 2) && (!parms->trapflag||new);
dofuncs.c:      flag = (parms->whenmask & 4) && (!parms->trapflag||new);
dofuncs.c:      flag = parms->whenmask & 8;
dofuncs.c:      EchoOff(W->display, parms->now);
dofuncs.c:      for(i = 0; i < parms->numfuncs; i++)
dofuncs.c:	if (*(parms->functions+i))
dofuncs.c:	  val = (**(parms->functions+i))(W, id, data, *(parms->arguments+i));
dofuncs.c:      EchoOn(pick->x, pick->y, W->display);
dofuncs.c:  else UpdateEcho(pick->x, pick->y, W->display, parms->echo);
drawfuncs.c:  parms->red = red;
drawfuncs.c:  parms->green = green;
drawfuncs.c:  parms->blue = blue;
drawfuncs.c:  parms->border = border;
drawfuncs.c:  parms->bred = bred;
drawfuncs.c:  parms->bgreen = bgreen;
drawfuncs.c:  parms->bblue = bblue;
drawfuncs.c:  parms->shadow = shadow;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:  case (GETCOLOR):		/* *DKY-12May90* */
drawfuncs.c:    *colors = parms->red;
drawfuncs.c:    *(colors+1) = parms->green;
drawfuncs.c:    *(colors+2) = parms->blue;
drawfuncs.c:    parms->red = *(colors);
drawfuncs.c:    parms->green = *(colors+1);
drawfuncs.c:    parms->blue = *(colors+2);
drawfuncs.c:    /* UpdateWin(W); removed 11/13/89 - dsmall */
drawfuncs.c:  case SET_SHADOW:		/* *DKY- 2Nov90* */
drawfuncs.c:    parms->shadow = (int)data;
drawfuncs.c:    parms->bred = *(colors);
drawfuncs.c:    parms->bgreen = *(colors + 1);
drawfuncs.c:    parms->bblue = *(colors +2);
drawfuncs.c:    cx1 = cstruct->x1;
drawfuncs.c:    cy1 = cstruct->y1;
drawfuncs.c:    cx2 = cstruct->x2;
drawfuncs.c:    cy2 = cstruct->y2;
drawfuncs.c:    cx1 = W->x1;
drawfuncs.c:    cy1 = W->y1;
drawfuncs.c:    cx2 = W->x2;
drawfuncs.c:    cy2 = W->y2;
drawfuncs.c:    DrawRect(screen, (float)cx1, (float)cy1, (float)cx2, (float)cy2, parms->red, parms->green, parms->blue,
drawfuncs.c:	     parms->border, parms->bred, parms->bgreen, parms->bblue, parms->shadow);
drawfuncs.c:    clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		   0.0, (float)((W->display)->height-1));
drawfuncs.c:  x2 -= shadow; y2 -= shadow;
drawfuncs.c:    rectangle(screen, (float)(x1+bd), (float)(y1+bd), (float)(x2-bd), (float)(y2-bd));
drawfuncs.c:  midw = x1 + ((x2-x1+1)/2.0);  midh = y1 + ((y2-y1+1)/2.0);
drawfuncs.c:  if ((d*2 > x2-x1+1) || (d*2 > y2-y1+1))
drawfuncs.c:      printf("error in roundbox -- too round\n");
drawfuncs.c:  partial_arc(fildes, (float)d, (float)d, (float)(x2-d), (float)(y1+d), -M_PI/2.0, 0.0, 0.0, 0, 0);
drawfuncs.c:  partial_arc(fildes, (float)d, (float)d, (float)(x2-d), (float)(y2-d), 0.0, M_PI/2.0, 0.0, 0, 0);
drawfuncs.c:  partial_arc(fildes, (float)d, (float)d, (float)(x1+d), (float)(y2-d), M_PI/2.0, M_PI, 0.0, 0, 0);
drawfuncs.c:  line[0] = (float)(x2-x1)/2.0;
drawfuncs.c:  line[1] = (float)(y2-y1)/2.0;
drawfuncs.c:  line[3] = (float)(x2-x1)/2.0;
drawfuncs.c:  line[4] = (float)(y2-y1)/2.0;
drawfuncs.c:SetRoundRectifyMode( mode)	/* *DKY-15Sep90* -- cause sometimes I don't want things round rectify-ed. */
drawfuncs.c:      params->red = red;
drawfuncs.c:      params->green = green;
drawfuncs.c:      params->blue = blue;
drawfuncs.c:      params->shadow = shadow;
drawfuncs.c:      params->shadowred = shadowred;
drawfuncs.c:      params->shadowgreen = shadowgreen;
drawfuncs.c:      params->shadowblue = shadowblue;
drawfuncs.c:      params->curvature = curve;
drawfuncs.c:  control = W->display->control;
drawfuncs.c:      params->red = *(colors);
drawfuncs.c:      params->green = *(colors+1);
drawfuncs.c:      params->blue = *(colors+2);
drawfuncs.c:      params->curvature = *((float *)data);
drawfuncs.c:      cx1 = cstruct->x1;  cy1 = cstruct->y1;
drawfuncs.c:      cx2 = cstruct->x2;  cy2 = cstruct->y2;
drawfuncs.c:      clip_rectangle((W->display)->fildes, cx1, cx2, cy1, cy2);
drawfuncs.c:      screen = (W->display)->fildes;
drawfuncs.c:      shadow = params->shadow;
drawfuncs.c:      if (shadow <0) shadow *= -1, way =1;
drawfuncs.c:      curve = params->curvature;
drawfuncs.c:      red = ((float)(params->shadowred)/255.0);
drawfuncs.c:      green = ((float)(params->shadowgreen)/255.0);
drawfuncs.c:      blue = ((float)(params->shadowblue)/255.0);
drawfuncs.c:      x1 = W->x1; x2 = W->x2;
drawfuncs.c:      y1 = W->y1; y2 = W->y2;
drawfuncs.c:	x2 -= (float)shadow, y2 -= (float)shadow;
drawfuncs.c:      d = curve*(fx2-fx1);
drawfuncs.c:	  move2d(screen, fx1+fd, fy2); draw2d(screen, fx2-fd, fy2);
drawfuncs.c:	  move2d(screen, fx2, fy1+fd); draw2d(screen, fx2, fy2-fd);
drawfuncs.c:	  arc(screen, fd, fd, fx2-fd, fy2-fd, 0.0, M_PI/2.0, 0.0, 0);
drawfuncs.c:	  arc(screen, fd, fd, fx2-fd, fy1+fd, 0.0, -M_PI/2.0, 0.0, 0);
drawfuncs.c:	  arc(screen, fd, fd, fx1+fd, fy2-fd, M_PI, M_PI/2.0, 0.0, 0);
drawfuncs.c:      red = ((float)(params->red)/255.0);
drawfuncs.c:      green = ((float)(params->green)/255.0);
drawfuncs.c:      blue = ((float)(params->blue)/255.0);
drawfuncs.c:      RoundedBox(screen, x1+1, y1+1, x2-1, y2-1, MAX(d-3, 1));
drawfuncs.c:      clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		     0.0, (float)((W->display)->height-1));
drawfuncs.c:      make_picture_current((W->display)->fildes);
drawfuncs.c:  direction of the point -- either UP, DOWN, LEFT, or RIGHT... ===========*/
drawfuncs.c:  parms->red = red;
drawfuncs.c:  parms->green = green;
drawfuncs.c:  parms->blue = blue;
drawfuncs.c:  parms->border = border;
drawfuncs.c:  parms->bred = bred;
drawfuncs.c:  parms->bgreen = bgreen;
drawfuncs.c:  parms->bblue = bblue;
drawfuncs.c:  parms->shadow = shadow;
drawfuncs.c:  parms->trired = trired;
drawfuncs.c:  parms->trigreen = trigreen;
drawfuncs.c:  parms->triblue = triblue;
drawfuncs.c:  parms->direction = direction;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:      parms->red = *(colors);
drawfuncs.c:      parms->green = *(colors+1);
drawfuncs.c:      parms->blue = *(colors+2);
drawfuncs.c:      parms->trired = *(colors);
drawfuncs.c:      parms->trigreen = *(colors+1);
drawfuncs.c:      parms->triblue = *(colors+2);
drawfuncs.c:      cx1 = cstruct->x1;
drawfuncs.c:      cy1 = cstruct->y1;
drawfuncs.c:      cx2 = cstruct->x2;
drawfuncs.c:      cy2 = cstruct->y2;
drawfuncs.c:      cx1 = W->x1;
drawfuncs.c:      cy1 = W->y1;
drawfuncs.c:      cx2 = W->x2;
drawfuncs.c:      cy2 = W->y2;
drawfuncs.c:      DrawRect(screen, (float)cx1, (float)cy1, (float)cx2, (float)cy2, parms->red, parms->green, parms->blue,
drawfuncs.c:	       parms->border, parms->bred, parms->bgreen, parms->bblue, parms->shadow);
drawfuncs.c:		   parms->trired, parms->trigreen, parms->triblue, parms->direction);
drawfuncs.c:      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		     0.0, (float)((W->display)->height-1));
drawfuncs.c:  params->ulred = ulred;  params->ulgreen = ulgreen;  params->ulblue = ulblue;
drawfuncs.c:  params->urred = urred;  params->urgreen = urgreen;  params->urblue = urblue;
drawfuncs.c:  params->lrred = lrred;  params->lrgreen = lrgreen;  params->lrblue = lrblue;
drawfuncs.c:  params->llred = llred;  params->llgreen = llgreen;  params->llblue = llblue;
drawfuncs.c:  params->shadow = shadow;
drawfuncs.c:  params->shadowred = shadowred;
drawfuncs.c:  params->shadowgreen = shadowgreen;
drawfuncs.c:  params->shadowblue = shadowblue;
drawfuncs.c:  params->border = border;
drawfuncs.c:  control = W->display->control;
drawfuncs.c:  cx1 = cstruct->x1;  cy1 = cstruct->y1;
drawfuncs.c:  cx2 = cstruct->x2;  cy2 = cstruct->y2;
drawfuncs.c:  clip_rectangle((W->display)->fildes, cx1, cx2, cy1, cy2);
drawfuncs.c:  x1 = (float)(W->x1);  x2 = (float)(W->x2);
drawfuncs.c:  y1 = (float)(W->y1);  y2 = (float)(W->y2);
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:    params->ulred = *(colors);
drawfuncs.c:    params->ulgreen = *(colors+1);
drawfuncs.c:    params->ulblue = *(colors+2);
drawfuncs.c:    params->urred = *(colors+3);
drawfuncs.c:    params->urgreen = *(colors+4);
drawfuncs.c:    params->urblue = *(colors+5);
drawfuncs.c:    params->lrred = *(colors+6);
drawfuncs.c:    params->lrgreen = *(colors+7);
drawfuncs.c:    params->lrblue = *(colors+8);
drawfuncs.c:    params->llred = *(colors+9);
drawfuncs.c:    params->llgreen = *(colors+10);
drawfuncs.c:    params->llblue = *(colors+11);
drawfuncs.c:    shadow = params->shadow;
drawfuncs.c:    border = params->border;
drawfuncs.c:    ulr = ((float)(params->ulred)/255.0);  
drawfuncs.c:    ulg = ((float)(params->ulgreen)/255.0);  
drawfuncs.c:    ulb = ((float)(params->ulblue)/255.0);
drawfuncs.c:    llr = ((float)(params->llred)/255.0);  
drawfuncs.c:    llg = ((float)(params->llgreen)/255.0);  
drawfuncs.c:    llb = ((float)(params->llblue)/255.0);
drawfuncs.c:    urr = ((float)(params->urred)/255.0);  
drawfuncs.c:    urg = ((float)(params->urgreen)/255.0);  
drawfuncs.c:    urb = ((float)(params->urblue)/255.0);
drawfuncs.c:    lrr = ((float)(params->lrred)/255.0);  
drawfuncs.c:    lrg = ((float)(params->lrgreen)/255.0);  
drawfuncs.c:    lrb = ((float)(params->lrblue)/255.0);
drawfuncs.c:    x2 -= shadow; y2 -= shadow;
drawfuncs.c:    red = ((float)(params->shadowred)/255.0);
drawfuncs.c:    green = ((float)(params->shadowgreen)/255.0);
drawfuncs.c:    blue = ((float)(params->shadowblue)/255.0);
drawfuncs.c:      rectangle(screen, (float)(x1+bd), (float)(y1+bd), (float)(x2-bd), (float)(y2-bd));
drawfuncs.c:    clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		   0.0, (float)((W->display)->height-1));
drawfuncs.c:/*------------This is used for adaptive text. It will fill the window with---------DB-12/27/90-------*/
drawfuncs.c:/*------------a gamma corrected gradation from white to black, top to bottom------------------------*/
drawfuncs.c:  parms->rect = (struct rectstruct *) malloc (sizeof (struct rectstruct));
drawfuncs.c:  parms->rect->red = 0;
drawfuncs.c:  parms->rect->green = 0;
drawfuncs.c:  parms->rect->blue = 0;
drawfuncs.c:  parms->rect->border = border;
drawfuncs.c:  parms->rect->bred = bred;
drawfuncs.c:  parms->rect->bgreen = bgreen;
drawfuncs.c:  parms->rect->bblue = bblue;
drawfuncs.c:  parms->rect->shadow = shadow;
drawfuncs.c:  parms->grad = grad_arrays;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:    cx1 = cstruct->x1;
drawfuncs.c:    cy1 = cstruct->y1;
drawfuncs.c:    cx2 = cstruct->x2;
drawfuncs.c:    cy2 = cstruct->y2;
drawfuncs.c:    cx1 = W->x1;
drawfuncs.c:    cy1 = W->y1;
drawfuncs.c:    cx2 = W->x2;
drawfuncs.c:    cy2 = W->y2;
drawfuncs.c:	     parms->rect->border, parms->rect->bred, parms->rect->bgreen, parms->rect->bblue, parms->rect->shadow, parms->grad);
drawfuncs.c:    clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		   0.0, (float)((W->display)->height-1));
drawfuncs.c:  x2 -= shadow; y2 -= shadow;
drawfuncs.c:  height = y2 - y1;
drawfuncs.c:      r = grad_arrays->redvals [val_index] / 255.0;
drawfuncs.c:      g = grad_arrays->greenvals [val_index] / 255.0;
drawfuncs.c:      b = grad_arrays->bluevals [val_index] / 255.0;
drawfuncs.c:    rectangle(screen, (float)(x1+bd), (float)(y1+bd), (float)(x2-bd), (float)(y2-bd));
drawfuncs.c:/*-------------------------------------------------------------------------------------------------------*/
drawfuncs.c:  parms->red = red;
drawfuncs.c:  parms->green = green;
drawfuncs.c:  parms->blue = blue;
drawfuncs.c:  parms->border = border;
drawfuncs.c:  parms->bred = bred;
drawfuncs.c:  parms->bgreen = bgreen;
drawfuncs.c:  parms->bblue = bblue;
drawfuncs.c:  parms->shadow = shadow;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:      cx1 = W->x1; cy1 = W->y1; cx2 = W->x2; cy2 = W->y2;
drawfuncs.c:      cx1 = cstruct->x1; cy1 = cstruct->y1; cx2 = cstruct->x2; cy2 = cstruct->y2;
drawfuncs.c:      cx1 = W->x1; cy1 = W->y1; cx2 = W->x2; cy2 = W->y2;
drawfuncs.c:  cx2 -= parms->shadow; cy2 -= parms->shadow;
drawfuncs.c:  red = ((float)*parms->red)/255.0;
drawfuncs.c:  green = ((float)*parms->green)/255.0;
drawfuncs.c:  blue = ((float)*parms->blue)/255.0;
drawfuncs.c:  red = ((float)parms->bred)/255.0;
drawfuncs.c:  green = ((float)parms->bgreen)/255.0;
drawfuncs.c:  blue = ((float)parms->bblue)/255.0;
drawfuncs.c:  if (parms->border<=0) interior_style(screen, INT_SOLID, FALSE);
drawfuncs.c:  for (border = 1; border < abs(parms->border); border++)
drawfuncs.c:    rectangle(screen, (float)(cx1+border), (float)(cy1+border), (float)(cx2-border), (float)(cy2-border));
drawfuncs.c:  for (shadow = 0; shadow < parms->shadow; shadow++)
drawfuncs.c:  clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		 0.0, (float)((W->display)->height-1));
drawfuncs.c:  cx1 = W->x1; cy1 = W->y1; cx2 = W->x2; cy2 = W->y2;
drawfuncs.c:      cx1 = cstruct->x1;  cy1 = cstruct->y1;
drawfuncs.c:      cx2 = cstruct->x2;  cy2 = cstruct->y2;
drawfuncs.c:      screen = (W->display)->fildes;
drawfuncs.c:      rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
drawfuncs.c:      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		     0.0, (float)((W->display)->height-1));
drawfuncs.c:  parms->red = r;
drawfuncs.c:  parms->green = g;
drawfuncs.c:  parms->blue = b;
drawfuncs.c:  parms->indent = indent;
drawfuncs.c:  parms->thickness = thickness;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:      cx1 = cstruct->x1;
drawfuncs.c:      cy1 = cstruct->y1;
drawfuncs.c:      cx2 = cstruct->x2;
drawfuncs.c:      cy2 = cstruct->y2;
drawfuncs.c:      cx1 = W->x1;
drawfuncs.c:      cy1 = W->y1;
drawfuncs.c:      cx2 = W->x2;
drawfuncs.c:      cy2 = W->y2;
drawfuncs.c:      red = (float)(parms->red) / 255.0;
drawfuncs.c:      green = (float)(parms->green) / 255.0;
drawfuncs.c:      blue = (float)(parms->blue) / 255.0;
drawfuncs.c:      indent = parms->indent;
drawfuncs.c:      for( i = 0; i < parms->thickness; i++) {
drawfuncs.c:	draw2d(screen, (float)(cx1 + indent + i), (float)(cy2 - indent - i));
drawfuncs.c:	draw2d(screen, (float)(cx2 - indent - i), (float)(cy1 + indent + i));
drawfuncs.c:	move2d(screen, (float)(cx2 - indent - i), (float)(cy2 - indent - i));
drawfuncs.c:	draw2d(screen, (float)(cx1 + indent + i), (float)(cy2 - indent - i));
drawfuncs.c:	move2d(screen, (float)(cx2 - indent - i), (float)(cy2 - indent - i));
drawfuncs.c:	draw2d(screen, (float)(cx2 - indent - i), (float)(cy1 + indent + i));
drawfuncs.c:      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		     0.0, (float)((W->display)->height-1));
drawfuncs.c:/*----Will draw an axis from top to bottom of the window at a distance from left edge equal to indent in pixels---*/
drawfuncs.c:  parms->red = r;
drawfuncs.c:  parms->green = g;
drawfuncs.c:  parms->blue = b;
drawfuncs.c:  parms->indent = indent;
drawfuncs.c:  parms->thickness = thickness;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:      cx1 = cstruct->x1;
drawfuncs.c:      cy1 = cstruct->y1;
drawfuncs.c:      cx2 = cstruct->x2;
drawfuncs.c:      cy2 = cstruct->y2;
drawfuncs.c:      cx1 = W->x1;
drawfuncs.c:      cy1 = W->y1;
drawfuncs.c:      cx2 = W->x2;
drawfuncs.c:      cy2 = W->y2;
drawfuncs.c:      red = (float)(parms->red) / 255.0;
drawfuncs.c:      green = (float)(parms->green) / 255.0;
drawfuncs.c:      blue = (float)(parms->blue) / 255.0;
drawfuncs.c:      indent = parms->indent;
drawfuncs.c:      for( i = 0; i < parms->thickness; i++) {
drawfuncs.c:	draw2d(screen, (float)(cx1 + indent + i), (float)(cy2 - indent));
drawfuncs.c:      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
drawfuncs.c:		     0.0, (float)((W->display)->height-1));
drawfuncs.c:  params->red = red;
drawfuncs.c:  params->green = green;
drawfuncs.c:  params->blue = blue;
drawfuncs.c:  params->shadow = shadow;
drawfuncs.c:  params->border = border;
drawfuncs.c:  params->bred = shadowred;
drawfuncs.c:  params->bgreen = shadowgreen;
drawfuncs.c:  params->bblue = shadowblue;
drawfuncs.c:  params->trans = trans;
drawfuncs.c:  screen = (W->display)->fildes;
drawfuncs.c:  shadow = params->shadow;
drawfuncs.c:  border = params->border;
drawfuncs.c:  trans  = params->trans;
drawfuncs.c:  x1=W->x1;  x2=W->x2;  y1=W->y1;  y2=W->y2;
drawfuncs.c:  cx1=0;  cx2=W->width-1;  cy1=0;  cy2=W->height-1;
drawfuncs.c:    if ((cstruct->x1 <= x2) && (cstruct->y1 <= y2) &&
drawfuncs.c:	(cstruct->x2 >= x1) && (cstruct->y2 >= y1)) {
drawfuncs.c:      if (cstruct->x1 >= W->x1) 
drawfuncs.c:	cx1 = cstruct->x1 - W->x1;
drawfuncs.c:      if (cstruct->y1 >= W->y1)
drawfuncs.c:	cy1 = cstruct->y1 - W->y1;
drawfuncs.c:      if (cstruct->x2 <= W->x2)
drawfuncs.c:	cx2 = cstruct->x2 - W->x1;
drawfuncs.c:      else cx2 = W->width - 1;
drawfuncs.c:      if (cstruct->y2 <= W->y2)
drawfuncs.c:	cy2 = cstruct->y2 - W->y1;
drawfuncs.c:      else cy2 = W->height - 1;
drawfuncs.c:      red   = ((unsigned char)params->red);
drawfuncs.c:      green = ((unsigned char)params->green);
drawfuncs.c:      blue  = ((unsigned char)params->blue);
drawfuncs.c:      bred = ((float)(params->bred)/255.0);
drawfuncs.c:      bgreen = ((float)(params->bgreen)/255.0);
drawfuncs.c:      bblue = ((float)(params->bblue)/255.0);
drawfuncs.c:      x2 -= shadow; y2 -= shadow;
drawfuncs.c:	/* if we're just dealing with a line -- draw it... */
drawfuncs.c:	  if (params->red >= 0)
drawfuncs.c:	      DrawTranslucentRect(red, green, blue, W->width, W->height, (W->display)->control,(W->display)->bits,
drawfuncs.c:				  (W->display)->buffer, (W->display)->width, (W->display)->height, x1, y1,
drawfuncs.c:	  for (t = 0; t < border; t++, x1++, y1++, x2--, y2--) {
drawfuncs.c:	      rectangle(screen, (float)x1, (float)y1, (float)(x2 - 1280), (float)y2);
drawfuncs.c:    params->trans = (int) data;
drawfuncs.c:    params->trans = *(tran);
drawfuncs.c:      params->red = *(colors);
drawfuncs.c:      params->green = *(colors+1);
drawfuncs.c:      params->blue = *(colors+2);
drawfuncs.c:     unsigned char *dbuf;                              /* ptr to upper-left of frame buffer */
drawfuncs.c:     int dx,dy;                                        /* upper-left position of source */
drawfuncs.c:     int bits,T;                                       /* translucency factor (0 - 255, 0 is opaque) */
drawfuncs.c:  invT = 255 - T;
drawfuncs.c:  if( T == 255)			/* clear -- do nothing */
drawfuncs.c:    xgap = dbufw-(x2-x1+1);
drawfuncs.c:    counter = xcount = x2-x1+1;
drawfuncs.c:	if (!(--xcount)) {
drawfuncs.c:    xgap = dbufw-(x2-x1+1);
drawfuncs.c:    counter = xcount = x2-x1+1;
drawfuncs.c:	if (!(--xcount)) {
drawfuncs.c:  icon->hotdx = offscreenx;
drawfuncs.c:  icon->hotdy = offscreeny;
drawfuncs.c:  screen = W->display->fildes;
drawfuncs.c:  (W->display)->control[0x0003] = 0x04;
drawfuncs.c:  (W->display)->control[0x40bf] = 7;
drawfuncs.c:  if (W->display->bits == 24)
drawfuncs.c:    shape_write24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
drawfuncs.c:		  W->display->height, offscreenx, offscreeny, icon->rule, 0, 0, W->display->width, W->display->height);
drawfuncs.c:  else if (W->display->bits == 32)
drawfuncs.c:    shape_write32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
drawfuncs.c:		  W->display->height, offscreenx, offscreeny, icon->rule, 0, 0, W->display->width, W->display->height);
drawfuncs.c:  FastScale(W->display->fildes,icon->hotdx,icon->hotdy,1280,0,W->x1,W->y1,icon->dx,icon->dy,W->width,W->height);
echoes.c:/* These routines are for the brain-damaged CRX24's.  They do not use offscreen memory. */
echoes.c:   ->w and ->h, the size of the current cursor is ->hotdx and ->hotdy                           */
echoes.c:  orientation =  (x2-x1 > y2-y1);     /*** find out whether to divide up horizontally or vertically ***/
echoes.c:  if (!orientation) wide = x2-x1+1, tall = (y2-y1+1)/4;
echoes.c:  else wide = (x2-x1+1)/4, tall = y2-y1+1;
echoes.c:  if (background)  free(background->source);
echoes.c:  background->dx = w;
echoes.c:  background->dy = h;
echoes.c:  background->id = 0;
echoes.c:  background->source = malloc(w*h*3*3);  /* 3 slots--background, mask, cursor on black */ 
echoes.c:    ReserveEchoBackground(cursor->dx,cursor->dy);
echoes.c:  else if ((cursor->dx > background->dx)||(cursor->dy > background->dy))
echoes.c:    ReserveEchoBackground(MAX(cursor->dx,background->dx),MAX(cursor->dy,background->dy));
echoes.c:  dx = cursor->dx;
echoes.c:  dy = cursor->dy;
echoes.c:  spos = cursor->source;
echoes.c:  back = background->source;
echoes.c:	if (*(spos+3*(x+y*dx)) == cursor->rule)
echoes.c:	    *(shape+x+y*dx) =  *(spos+3*(x+y*cursor->dx));
echoes.c:	    *(shape+x+y*dx+dx*dy) =  *(spos+3*(x+y*cursor->dx)+1);
echoes.c:	    *(shape+x+y*dx+dx*dy*2) =  *(spos+3*(x+y*cursor->dx)+2);
echoes.c:  if (!background->id) EchoOn(x, y, fildes);
echoes.c:    display = fildes->fildes;
echoes.c:	dx = lastcursor->dx;  dy = lastcursor->dy;
echoes.c:	dcblock_write(display, E_oldx, E_oldy, dx, dy, background->source,FALSE);
echoes.c:	dcblock_read(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source,FALSE);
echoes.c:	dcblock_write(display, E_oldx, E_oldy, dx, dy, background->source+dx*dy,FALSE);
echoes.c:	dcblock_read(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy,FALSE);
echoes.c:	dcblock_write(display, E_oldx, E_oldy, dx, dy, background->source+dx*dy*2,FALSE);
echoes.c:	dcblock_read(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+2*dx*dy,FALSE);
echoes.c:	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*3,FALSE);
echoes.c:	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*4,FALSE);
echoes.c:	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*5,FALSE);
echoes.c:	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*6,FALSE);
echoes.c:	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*7,FALSE);
echoes.c:	dcblock_write(display,x-lastcursor->hotdx,y-lastcursor->hotdy, dx, dy, background->source+dx*dy*8,FALSE);
echoes.c:    w = lastcursor->dx;
echoes.c:    h = lastcursor->dy;
echoes.c:    bank_switch(fildes->fildes,2,0);
echoes.c:    dcblock_write(fildes->fildes, E_oldx, E_oldy, w, h, background->source, FALSE);
echoes.c:    bank_switch(fildes->fildes,1,0);
echoes.c:    dcblock_write(fildes->fildes, E_oldx, E_oldy, w, h, background->source+w*h, FALSE);
echoes.c:    bank_switch(fildes->fildes,0,0);
echoes.c:    dcblock_write(fildes->fildes, E_oldx, E_oldy, w, h, background->source+w*h*2, FALSE);
echoes.c:    if (now) make_picture_current(fildes->fildes);
echoes.c:    background->id = 0;
echoes.c:  nx = x-lastcursor->hotdx;
echoes.c:  ny = y-lastcursor->hotdy;
echoes.c:  if (x == 123456) {	/* *TIM-19Apr91* */
echoes.c:  display = fildes->fildes;
echoes.c:  if (!background->id)
echoes.c:      background->id = 1;
echoes.c:      dx = lastcursor->dx;  dy = lastcursor->dy;
echoes.c:      dcblock_read(fildes->fildes, nx, ny, dx, dy, background->source, FALSE);
echoes.c:      dcblock_read(fildes->fildes, nx, ny, dx, dy, background->source+dx*dy, FALSE);
echoes.c:      dcblock_read(fildes->fildes, nx, ny, dx, dy, background->source+dx*dy*2, FALSE);
echoes.c:      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*3,FALSE);
echoes.c:      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*4,FALSE);
echoes.c:      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*5,FALSE);
echoes.c:      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*6,FALSE);
echoes.c:      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*7,FALSE);
echoes.c:      dcblock_write(display,nx,ny, dx, dy, background->source+dx*dy*8,FALSE);
echoes.c:  if (background->id)
equilibrium.c:/* Equilibrium.c --                                       */
equilibrium.c:/*   NOTE:  This current is only implemented for normalized float slider systems -- 
equilibrium.c:/*          specifically, range 0.01 - 1.01, and all slider values always sum to 1.0.
equilibrium.c:	    LHR -- 4/8/90
equilibrium.c:     int id;                             /* <-- id of message to pass to "msg_win" on JUSTUP of a slider */
equilibrium.c:     struct List *list_to_update;        /* <-- list of register wins to update on a JUSTUP of a slider */
equilibrium.c:     char *slider_data;                  /* <-- array of initial values for each of the sliders in the system */
equilibrium.c:  Controller = (struct Window *)MakeWindow(root->display, root->input, parent, 0,0,10,10, "controller");
equilibrium.c:      W = (struct Window *)MakeWindow(root->display, root->input, parent, 100, init_ypos+(i*(ht+15)), wd, ht, "slider");
equilibrium.c:      W = (struct Window *)MakeWindow(root->display, root->input, parent, init_xpos+(i*(wd+15)), 100, wd, ht, "slider");
equilibrium.c:    params->num_sliders = num_sliders;
equilibrium.c:    params->kind = kind;
equilibrium.c:    params->orient = orient;
equilibrium.c:    params->red = red;
equilibrium.c:    params->green = green;
equilibrium.c:    params->blue = blue;
equilibrium.c:    params->shadow = shadow;
equilibrium.c:    params->shadowred = shadowred;
equilibrium.c:    params->shadowgreen = shadowgreen;
equilibrium.c:    params->shadowblue = shadowblue;
equilibrium.c:    params->barred = barred;
equilibrium.c:    params->bargreen = bargreen;
equilibrium.c:    params->barblue = barblue;
equilibrium.c:    params->max = max;
equilibrium.c:    params->min = min;
equilibrium.c:    params->total = total;
equilibrium.c:    params->controller = (struct Window *)Controller;
equilibrium.c:    if (kind) params->number = (char *) (((float *)slider_data)+i);
equilibrium.c:    else params->number = (char *) (((int *)slider_data)+i);
equilibrium.c:  up->slider_data = (char *)slider_data;
equilibrium.c:  up->other_sliders = Sliders;
equilibrium.c:  for (current = L->Front; current->id != NULL; current = current->Front)
equilibrium.c:    UpdateWin(current->id);
equilibrium.c:  kind = parms->kind;
equilibrium.c:    fdelta = (float *)parms->delta;
equilibrium.c:    ftotal = (float *)parms->remaining_total;
equilibrium.c:    fvalue_array = (float *)update->slider_data;
equilibrium.c:    delta = (int *)parms->delta;
equilibrium.c:    total = (int *)parms->remaining_total;
equilibrium.c:    value_array = (int *)update->slider_data;
equilibrium.c:  for (current = update->other_sliders->Front, i=0; current->id != NULL; current = current->Front, i++) {
equilibrium.c:    if (current->id == parms->slider) continue;
equilibrium.c:      *fval -= (float)(((*fval)/(*ftotal)) * (*fdelta));
equilibrium.c:      *val -= (int)(((*val)/(*total)) * (*delta));
equilibrium.c:    UpdateWin(current->id);
equilibrium.c:  screen = (W->display)->fildes;
equilibrium.c:  cx1 = cstruct->x1;
equilibrium.c:  cy1 = cstruct->y1;
equilibrium.c:  cx2 = cstruct->x2;
equilibrium.c:  cy2 = cstruct->y2;
equilibrium.c:  shadow = params->shadow;
equilibrium.c:  kind = params->kind;
equilibrium.c:  if (kind) fnumber=(float *)params->number, fmax=(float *)params->max, fmin=(float *)params->min;
equilibrium.c:  else number=(int *)params->number, max=(int *)params->max, min=(int *)params->min;
equilibrium.c:  red = ((float)(params->red)/255.0);
equilibrium.c:  green = ((float)(params->green)/255.0);
equilibrium.c:  blue = ((float)(params->blue)/255.0);
equilibrium.c:  red = ((float)(params->shadowred)/255.0);
equilibrium.c:  green = ((float)(params->shadowgreen)/255.0);
equilibrium.c:  blue = ((float)(params->shadowblue)/255.0);
equilibrium.c:  x1 = W->x1; y1 = W->y1; x2 = W->x2; y2 = W->y2;
equilibrium.c:  x2 -= (float)shadow; y2 -= (float)shadow;
equilibrium.c:  red = ((float)(params->barred)/255.0);
equilibrium.c:  green = ((float)(params->bargreen)/255.0);
equilibrium.c:  blue = ((float)(params->barblue)/255.0);
equilibrium.c:  if (kind) ratio = (*fnumber-*fmin)/(*fmax-*fmin);
equilibrium.c:  else      ratio = ((float)*number - (float)*min)/((float)*max-(float)*min);
equilibrium.c:  if (params->orient)
equilibrium.c:      ratline = fy2-ratio*(fy2-fy1-3.0)-2.0;
equilibrium.c:      ratline = fx1+ratio*(fx2-fx1-3.0)-2.0;
equilibrium.c:  clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1), 
equilibrium.c:		 0.0, (float)((W->display)->height-1));
equilibrium.c:  make_picture_current((W->display)->fildes);
equilibrium.c:  kind = params->kind;
equilibrium.c:  if (kind) fnum=(float *)params->number, fmax=(float *)params->max, fmin=(float *)params->min;
equilibrium.c:  else num=(int *)params->number, max = (int *)params->max, min = (int *)params->min;
equilibrium.c:  controller = params->controller;
equilibrium.c:  x = pick->x;
equilibrium.c:  y = pick->y;
equilibrium.c:  dx = MAX(x, W->x1);
equilibrium.c:  dy = MAX(y, W->y1);
equilibrium.c:  dx = MIN(dx, W->x2);
equilibrium.c:  dy = MIN(dy, W->y2);
equilibrium.c:  button = pick->button;
equilibrium.c:	  if (params->orient) ratio = (float)(W->y2-dy)/(float)(W->height-params->shadow);
equilibrium.c:	  else                ratio = (float)(dx-W->x1)/(float)(W->width-params->shadow);
equilibrium.c:	  eqstruct->kind = kind;
equilibrium.c:	  eqstruct->slider = W;
equilibrium.c:	    *fnum = *fmin+ratio*(*fmax-*fmin);
equilibrium.c:	    *fdelta = *fnum - *old_fnum;
equilibrium.c:	    eqstruct->delta = (char *)fdelta;
equilibrium.c:	    *ftotal = (1.0 - *((float *)old_fnum));
equilibrium.c:	    eqstruct->remaining_total = (char *)ftotal;
equilibrium.c:	    *num = ((float)*min + ratio*((float)*max-(float)*min));
equilibrium.c:	    *delta = *num - *old_num;
equilibrium.c:	    eqstruct->delta = (char *)delta;
equilibrium.c:	    *total = (1 - *((int *)old_num));
equilibrium.c:	    eqstruct->remaining_total = (char *)total;
ez3d.c:				0.0, 0.0, -1.0,0.0,
ez3d.c:  screen = (W->display)->fildes;
ez3d.c:    cx1 = cstruct->x1;
ez3d.c:    cy1 = cstruct->y1;
ez3d.c:    cx2 = cstruct->x2;
ez3d.c:    cy2 = cstruct->y2;
ez3d.c:    cx1 = W->x1;
ez3d.c:    cy1 = W->y1;
ez3d.c:    cx2 = W->x2;
ez3d.c:    cy2 = W->y2;
ez3d.c:    view_port(screen,(float)W->x1,(float)W->y2,(float)W->x2,(float)W->y1); 
ez3d.c:  screen = (W->display)->fildes;
ez3d.c:      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
ez3d.c:		     0.0, (float)((W->display)->height-1));
ez3d.c:  cam->refx = refx;
ez3d.c:  cam->refy = refy;
ez3d.c:  cam->refz = refz;
ez3d.c:  cam->camx = camx;
ez3d.c:  cam->camy = camy;
ez3d.c:  cam->camz = camz;
ez3d.c:  cam->upx = upx;
ez3d.c:  cam->upy = upy;
ez3d.c:  cam->upz = upz;
ez3d.c:  cam->field_of_view = field_of_view;
ez3d.c:  cam->front = front;
ez3d.c:  cam->back = back;
ez3d.c:  cam->projection = projection;
ez3d.c:  cam->refx = 0.0;
ez3d.c:  cam->refy = 0.0;
ez3d.c:  cam->refz = 0.0;
ez3d.c:  cam->camx = 0.0;
ez3d.c:  cam->camy = 0.0;
ez3d.c:  cam->camz = 10.0; 
ez3d.c:  cam->upx = 0.0;
ez3d.c:  cam->upy = 1.0;
ez3d.c:  cam->upz = 0.0;
ez3d.c:  cam->field_of_view = 45.0;
ez3d.c:  cam->front = -20.0;
ez3d.c:  cam->back = 200.0;
ez3d.c:  cam->projection = CAM_PERSPECTIVE;
ez3d.c:/* Attach front-end to camera model, for doing circular pivots around reference point */
ez3d.c:  p->scam = scam;
ez3d.c:  p->tilt = 0.0;
ez3d.c:  scam = p->scam;
ez3d.c:      p->theta += f;
ez3d.c:      p->phi += f;
ez3d.c:      p->tilt += f;
ez3d.c:      if (p->distance + f)
ez3d.c:	p->distance += f;
ez3d.c:      p->theta = f;
ez3d.c:      p->phi = f;
ez3d.c:      p->tilt = f;
ez3d.c:      if (p->distance)
ez3d.c:	p->distance = f;
ez3d.c:  cam = parms->scam;
ez3d.c:      cam->camx = parms->distance*cos(parms->phi*M_PI/180.0)*sin(parms->theta*M_PI/180.0);
ez3d.c:      cam->camy = parms->distance*sin(parms->phi*M_PI/180.0);
ez3d.c:      cam->camz = parms->distance*cos(parms->phi*M_PI/180.0)*cos(parms->theta*M_PI/180.0);
ez3d.c:      cam->upx = parms->distance*cos(parms->phi*M_PI/180.0+M_PI/2.0)*sin(parms->theta*M_PI/180.0);
ez3d.c:      cam->upy = parms->distance*sin(parms->phi*M_PI/180.0+M_PI/2.0);
ez3d.c:      cam->upz = parms->distance*cos(parms->phi*M_PI/180.0+M_PI/2.0)*cos(parms->theta*M_PI/180.0);
ez3d.c:      NoVectorCross(cam->camx,cam->camy,cam->camz,cam->upx,cam->upy,cam->upz,&cx,&cy,&cz);
ez3d.c:      Normalize(&cam->upx,&cam->upy,&cam->upz);
ez3d.c:      cval = cos(parms->tilt*M_PI/180.0);
ez3d.c:      sval = sin(parms->tilt*M_PI/180.0);
ez3d.c:      cam->upx = (cval*cam->upx+sval*cx);
ez3d.c:      cam->upy = (cval*cam->upy+sval*cy);
ez3d.c:      cam->upz = (cval*cam->upz+sval*cz);
ez3d.c:      cam->camx += cam->refx;
ez3d.c:      cam->camy += cam->refy;
ez3d.c:      cam->camz += cam->refz;
ez3d.c:  cam = parms->scam;
ez3d.c:  newx = (double)(cam->camx-cam->refx);
ez3d.c:  newy = (double)(cam->camy-cam->refy);
ez3d.c:  newz = (double)(cam->camz-cam->refz);
ez3d.c:  parms->theta = (atan2(newx,newz))*180/M_PI;
ez3d.c:  parms->phi = (asin(newy/length))*180/M_PI;
ez3d.c:  parms->distance = length;
ez3d.c:  light_source(display, 1, DIRECTIONAL, Gray(1.0), -10.0, 10.0, 10.0);  
ez3d.c:/*  light_source(display, 2, DIRECTIONAL, Gray(0.8), -5.0, -12.0, -10.0);  
ez3d.c:  light_source(display, 4, DIRECTIONAL, Gray(0.8), -20.0, -20.0, 20.0);
ez3d.c:  move3d(screen,tx-300.0,ty,tz);
ez3d.c:  move3d(screen,tx,ty-300.0,tz);
ez3d.c:  move3d(screen,tx,ty,tz-300.0);
ez3d.c:  if (t->new)
ez3d.c:      Scale(t->mat,t->sx,t->sy,t->sz,0);
ez3d.c:      Rotate(t->mat,t->rx,t->ry,t->rz,1);
ez3d.c:      Translate(t->mat,t->x,t->y,t->z,1);
ez3d.c:      t->new = 0;
ez3d.c:  concat_transformation3d(W->display->fildes,t->mat,PRE,PUSH);
ez3d.c:  pop_matrix(W->display->fildes);
ez3d.c:      t->x = t->y = t->z = 0.0;
ez3d.c:      t->rx = t->ry = t->rz = 0.0;
ez3d.c:      t->sx = t->sy = t->sz = 1.0;
ez3d.c:      MakeIdentity(t->mat);
ez3d.c:      t->new = 0;
ez3d.c:      CopyMatrix(M, t->mat);
ez3d.c:       Scale(t->mat,t->sx,t->sy,t->sz,0);
ez3d.c:       Rotate(t->mat,t->rx,t->ry,t->rz,1);
ez3d.c:       Translate(t->mat,t->x,t->y,t->z,1);
ez3d.c:       t->new = 0;
ez3d.c:      t->x += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->y += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->z += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->rx += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->ry += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->rz += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->sx += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->sy += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->sz += f;
ez3d.c:      t->new = 1;
ez3d.c:      t->x = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->y = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->z = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->rx = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->ry = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->rz = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->sx = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->sy = f;
ez3d.c:      t->new = 1;
ez3d.c:      t->sz = f;
ez3d.c:      t->new = 1;
ez3d.c:  display = W->display->fildes;
ez3d.c:  CullVector(scam->camx,scam->camy,scam->camz,0.0,0.0,0.0,scam->upx,scam->upy,scam->upz,&x,&y,&z);
ez3d.c:  cx = scam->camx;
ez3d.c:  cy = scam->camy;
ez3d.c:  cz = scam->camz;
ez3d.c:  nx = (cx*3+scam->upx*4+x*2)/9.0;
ez3d.c:  ny = (cy*3+scam->upy*4+y*2)/9.0;
ez3d.c:  nz = (cz*3+scam->upz*4+z*2)/9.0;
ez3d.c:  light_source(display, 2, DIRECTIONAL, Gray(.5), -nx, -ny,-nz);
ez3d.c:  light_source(display, 3, DIRECTIONAL, Gray(.3), -nx, -ny,nz);
fastmag.c:  x = x2+bigwide-1;
fastmag.c:  for (xindex = width-1; xindex >=0 ; xindex--)
fastmag.c:      for (xx = 0; xx< pixelsize-linestat; xx++)
fastmag.c:	dcblock_move(screen, x1+xindex, y1, 1, height+1, x--, y2);
fastmag.c:	dcblock_move(screen, x2+bigwide, y2, 1, height+1, x--, y2);
fastmag.c:  y = y2+bigtall-1;;
fastmag.c:  for (yindex = height-1; yindex >=0 ; yindex--)
fastmag.c:      for (yy = 0; yy< pixelsize-linestat; yy++)
fastmag.c:	dcblock_move(screen, x2, y2+yindex, bigwide, 1, x2, y--);
fastmag.c:	dcblock_move(screen, x2, y2+bigtall, bigwide, 1, x2, y--);
fastmag.c:  x = x1+bigwide-1;
fastmag.c:  for (xindex = width-1; xindex >=0 ; xindex--)
fastmag.c:      for (xx = 0; xx< pixelsize-linestat; xx++)
fastmag.c:	dcblock_move(screen, x1+xindex, y1, 1, height+1, x--, y1);
fastmag.c:	dcblock_move(screen, x2+bigwide, y2, 1, height+1, x--, y1);
fastmag.c:  y = y2+bigtall-1;;
fastmag.c:  for (yindex = height-1; yindex >=0 ; yindex--)
fastmag.c:      for (yy = 0; yy< pixelsize-linestat; yy++)
fastmag.c:	dcblock_move(screen, x1, y1+yindex, bigwide, 1, x2, y--);
fastmag.c:	dcblock_move(screen, x2, y2+bigtall, bigwide, 1, x2, y--);
fastmag.c:  tr = (finalwidth-1)*r;
fastmag.c:  for (x = finalwidth-1; x >= 0; x--)
fastmag.c:      tr -= r;
fontfuncs.c:  params->font = font;
fontfuncs.c:  params->string = string;
fontfuncs.c:  params->size = size;
fontfuncs.c:  params->bits = bits;
fontfuncs.c:  params->x = x;
fontfuncs.c:  params->y = y;
fontfuncs.c:  params->red = red;
fontfuncs.c:  params->green = green;
fontfuncs.c:  params->blue = blue;
fontfuncs.c:  params->t = t;
fontfuncs.c:  params->char_space = 0;
fontfuncs.c:  params->word_space = 0;
fontfuncs.c:  AttachCommand(W, FREESTRING, DrawAString, params); /* *DKY-30Aug90* */
fontfuncs.c:  AttachCommand(W, CHANGE_X_POS, DrawAString, params); /* *DKY-13May90* */
fontfuncs.c:  AttachCommand(W, CHANGE_Y_POS, DrawAString, params); /* *DKY-13May90* */
fontfuncs.c:  AttachCommand(W, SET_SIZE, DrawAString, params); /* *DKY-13May90* */
fontfuncs.c:  AttachCommand(W, GET_STRINGWIN_COLOR, DrawAString, params); /* *DKY-15May90* */
fontfuncs.c:  params->font = font;
fontfuncs.c:  params->string = string;
fontfuncs.c:  params->size = size;
fontfuncs.c:  params->bits = bits;
fontfuncs.c:  params->x = x;
fontfuncs.c:  params->y = y;
fontfuncs.c:  params->red = red;
fontfuncs.c:  params->green = green;
fontfuncs.c:  params->blue = blue;
fontfuncs.c:  params->t = t;
fontfuncs.c:  params->char_space = char_space;
fontfuncs.c:  params->word_space = word_space;
fontfuncs.c:  AttachCommand(W, FREESTRING, DrawAString, params); /* *DKY-30Aug90* */
fontfuncs.c:  AttachCommand(W, CHANGE_X_POS, DrawAString, params); /* *DKY-13May90* */
fontfuncs.c:  AttachCommand(W, CHANGE_Y_POS, DrawAString, params); /* *DKY-13May90* */
fontfuncs.c:  AttachCommand(W, SET_SIZE, DrawAString, params); /* *DKY-13May90* */
fontfuncs.c:  AttachCommand(W, GET_STRINGWIN_COLOR, DrawAString, params); /* *DKY-15May90* */
fontfuncs.c:      set_font(mstruct->font, mstruct->size, mstruct->bits);
fontfuncs.c:      set_monitor(W->display->bits, W->display->fildes);
fontfuncs.c:      set_font_color(mstruct->red, mstruct->green, mstruct->blue, mstruct->t);
fontfuncs.c:      set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
fontfuncs.c:      set_char_space(mstruct->char_space);
fontfuncs.c:      set_word_space(mstruct->word_space);
fontfuncs.c:      if (mstruct->string)
fontfuncs.c:	  if (mstruct->x == CENTERED)
fontfuncs.c:	    xx = (W->width - string_width(mstruct->string))/2;
fontfuncs.c:	  else if (mstruct->x < 0)
fontfuncs.c:	    xx = W->width + mstruct->x - string_width(mstruct->string);
fontfuncs.c:	  else xx = mstruct->x;
fontfuncs.c:	  if (mstruct->y == CENTERED)
fontfuncs.c:	    yy = W->height/2 - string_height(mstruct->string)/2;
fontfuncs.c:	  else if (mstruct->y < 0)
fontfuncs.c:	    yy = W->height + mstruct->y - string_height(mstruct->string);
fontfuncs.c:	  else yy = mstruct->y;
fontfuncs.c:	  display_string(mstruct->string, W->x1+xx, W->y1+yy);
fontfuncs.c:      set_char_space( 0);	/* *DKY-18Mar90-17:29* */
fontfuncs.c:      set_word_space( 0);	/* *DKY-18Mar90-17:29* */
fontfuncs.c:      mstruct->string = data;
fontfuncs.c:      mstruct->string = data;
fontfuncs.c:  else if (id == FREESTRING)	/* optional argument is a new string *DKY-30Aug90* */
fontfuncs.c:      if( mstruct->string)
fontfuncs.c:	free( mstruct->string);
fontfuncs.c:      mstruct->string = data;
fontfuncs.c:      mstruct->red = (colors[0]);
fontfuncs.c:      mstruct->green = (colors[1]);
fontfuncs.c:      mstruct->blue = (colors[2]);
fontfuncs.c:      mstruct->t = *trans;
fontfuncs.c:      mstruct->char_space = *temp;
fontfuncs.c:      mstruct->word_space = *temp;
fontfuncs.c:      mstruct->font = newstruct->font;
fontfuncs.c:      mstruct->size = newstruct->size;
fontfuncs.c:      mstruct->bits = newstruct->bits;
fontfuncs.c:  else if (id == CHANGE_X_POS)	/* *DKY-13May90* */
fontfuncs.c:      mstruct->x = *temp;
fontfuncs.c:  else if (id == CHANGE_Y_POS)	/* *DKY-13May90* */
fontfuncs.c:      mstruct->y = *temp;
fontfuncs.c:  else if (id == SET_SIZE)	/* *DKY-13May90* */
fontfuncs.c:      mstruct->size = *temp;
fontfuncs.c:  else if (id == GET_STRINGWIN_COLOR) {	/* *DKY-15May90* */
fontfuncs.c:    *colors = (int *)&(mstruct->red);
fontfuncs.c:    *(colors+1) = (int *)&(mstruct->green);
fontfuncs.c:    *(colors+2) = (int *)&(mstruct->blue);
fontfuncs.c:  rparms->string = string;
fontfuncs.c:  rparms->parms = parms;
fontfuncs.c:  rparms->x = x;
fontfuncs.c:  rparms->y = y;
fontfuncs.c:	mstruct = rparms->parms;
fontfuncs.c:	set_font(mstruct->font, mstruct->size, mstruct->bits);
fontfuncs.c:	set_monitor(W->display->bits, W->display->fildes);
fontfuncs.c:	set_font_color(mstruct->red, mstruct->green, mstruct->blue, mstruct->t);
fontfuncs.c:	set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
fontfuncs.c:	display_string(rparms->string, W->x1+rparms->x, W->y1+rparms->y);
fontfuncs.c:	rparms->x = *temp;
fontfuncs.c:	rparms->y = *temp;
fontfuncs.c:      printf( "WARNING: DrawRString() - unknown message id: %d\n", id);
fontreq.c:             MakeFontRequester(root,echo,   <---- just like in MakeWindow
fontreq.c:                               font,size,   <---- just like in stringwin
fontreq.c:			       x,y,         <---- x and y coordinates of
fontreq.c:			       c1,c2,c3,    <---- background color
fontreq.c:			       b1,b2,b3,    <---- button color
fontreq.c:			       t1,t2,t3,    <---- text color
fontreq.c:			       h1,h2,h3);   <---- indicator color
fontreq.c:             DelayedMakeFontRequester( <with the same arguments> )            *DKY- 8Oct90*
fontreq.c:	     it is first used -- thus saving time when starting your program, but causing a delay
fontreq.c:  and then when you want the requester, call-
fontreq.c:	             call with size = -1 to get the pointsize requester
fontreq.c:int FontRequesterMade = NULL, UsingDelayedFontRequester = NULL;	/* *DKY- 8Oct90* */
fontreq.c:  if( UsingDelayedFontRequester)					  /* *DKY- 8Oct90* */
fontreq.c:GetFontAt( root, x, y, size)	/* Same as GetFont, but you give it a location to put up the requestor. *DKY- 4Jun91* */
fontreq.c:  TransformCoords( FontReqWin, x, y, FontReqWin->width, FontReqWin->height);
fontreq.c:  FontReqWin->parent = root;
fontreq.c:  FontReqWin->display = root->display;
fontreq.c:  if( UsingDelayedFontRequester)					  /* *DKY- 8Oct90* */
fontreq.c:  if((string = GetFont(mstruct->size)) == NULL) return (-1);
fontreq.c:  if((string = GetFont(-1)) == NULL) return (-1);
fontreq.c:  if((mstruct->size = GetPointSize(FindRoot(W),W->x2, W->y1,mstruct->font)) == 0) return (-1);
fontreq.c:  size=mstruct->size;
fontreq.c:  if( FontReqWin) 		/* *DKY-15Feb91* */
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:  W = (struct Window *) MakeCancelThingy(FontReqWin, echo,font,0,FontReqWin->width,c1,c2,c3,t1,t2,t3);
fontreq.c:  FontRequesterMade = 1;	/* *DKY- 8Oct90* */
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:  rht = root->y2 - root->y1 +1;
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:  M = (struct Window *)MakeFlavors(root,echo, displayfont, root->x2,root->y1, font,c1,c2,c3,b1,b2,b3,t1,t2,t3,h1,h2,h3);
fontreq.c:  TransformCoords(M, W->parent->x2+5, W->parent->y1,M->width,M->height); 
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:  Button = (struct Window *)MakeLoadButton(W,echo,displayfont,0,W->width /2, c1,c2,c3,t1,t2,t3);
fontreq.c:  Button = (struct Window *)MakeCancelThingy(W,echo,displayfont,W->width /2 , W->width /2,c1,c2,c3,t1,t2,t3);
fontreq.c:  ChildrenMessenger(Button,DO,Button->parent,TURN_OFF,NULL,JUSTUP);
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:      TransformCoords(root,root->x1,root->y1,root->width,W->y2-root->y1);
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:  ht = root->y2 - root->y1;
fontreq.c:  Maker(W,x1,-35,x1+wd-1,-0);
fontreq.c:  display = root->display;
fontreq.c:  locator = root->input;
fontreq.c:  ht = root->y2 - root->y1;
fontreq.c:  Maker(W,x1,-35,x1+wd-1,-0);
fontreq.c:    mstruct->font = strdup(line);
fontreq.c:    mstruct->size = size;
fontreq.c:    pstruct->font = strdup(line);
fontreq.c:    pstruct->size = size;
fontreq.c:  L = P->port;
fontreq.c:  for (Current = L2->Front; Current != L2 ; Current = Current->Front)
fontreq.c:      tempwin = Current->id;
fontreq.c:      fontrequesterreturnvalue=strdup(tempwin->tag);
fontreq.c:      fontrequesterreturnvalue=strdup(tempwin->tag);
fontreq.c:	  if ((size = GetPointSize(FindRoot(W),W->x1, W->y2 + 10, fontrequesterreturnvalue)) == 0) return (0);
fontreq.c:  if( UsingDelayedFontRequester)	/* *DKY- 8Oct90* */
fontreq.c:  display = Root->display;
fontreq.c:  SizeReqWin->parent = Root;
fontreq.c:  SizeReqWin->display = display;
fontreq.c:  newstruct->listbase = font;
fontreq.c:  TransformCoords(SizeReqWin, x, y, SizeReqWin->width, SizeReqWin->height);
fontreq.c:  display = root->display;
fontreq.c:  locater = root->input;
fontreq.c:  W = (struct Window *) MakeCancelThingy(SizeReqWin, echo,font,0,SizeReqWin->width,c1,c2,c3,t1,t2,t3);
fontreq.c:  params->Root = root;
fontreq.c:  params->echo = echo;
fontreq.c:  params->list = NULL;
fontreq.c:  params->listbase = NULL;
fontreq.c:  params->no_of_items = 0;
fontreq.c:  params->displayfont = strdup(displayfont);
fontreq.c:  params->size = size;
fontreq.c:  params->bits = bits;
fontreq.c:  params->x = x, params->y = y;
fontreq.c:  params->c1 = c1,  params->c2 = c2, params->c3 = c3;
fontreq.c:  params->b1 = b1,  params->b2 = b2, params->b3 = b3;
fontreq.c:  params->t1 = t1,  params->t2 = t2, params->t3 = t3;
fontreq.c:  params->h1 = h1,  params->h2 = h2, params->h3 = h3;
fontreq.c:  screen = (W->display)->fildes;
fontreq.c:  size = params->size * 3 / 2;
fontreq.c:      cx1 = cstruct->x1;  cy1 = cstruct->y1;
fontreq.c:      cx2 = cstruct->x2;  cy2 = cstruct->y2;
fontreq.c:      set_font(params->displayfont, params->size, params->bits);
fontreq.c:      set_monitor(W->display->bits, W->display->fildes);
fontreq.c:      set_font_color(params->t1,params->t2,params->t3,0);
fontreq.c:      set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
fontreq.c:      fill_color(screen, FCON(params->b1), FCON(params->b2), FCON(params->b3));
fontreq.c:      for(i=0; i <= params->no_of_items ; i++)
fontreq.c:	  rectangle(screen, (float)(W->x1+params->x), (float)(W->y1+params->y+size*i), 
fontreq.c:		    (float)(W->x2 - 5), (float)(W->y1+params->y+size*(i+1)));
fontreq.c:	  make_picture_current(screen);	/* *DKY- 4Oct90* */
fontreq.c:	  xx = W->x1+W->width/2 - string_width(*(params->list+i))/2;
fontreq.c:	  display_string(params->list[i], xx, W->y1+params->y+size*i+size/4);
fontreq.c:	  make_picture_current(screen);	/* *DKY- 4Oct90* */
fontreq.c:      button = pick->button;
fontreq.c:	  if( BETWEEN((y = (pick->y - params->y - W->y1)/size),0,params->no_of_items))
fontreq.c:	      sscanf(*(params->list + y),"%d",&sizerequesterreturnvalue);
fontreq.c:      params->listbase = newstruct->listbase;
fontreq.c:      if(params->list)						  /* clears old list */
fontreq.c:	  for(i = 0; params->list [i] ; i++)
fontreq.c:	    free(params->list[i]);
fontreq.c:	  free(params->list);
fontreq.c:      params->list = GetPointSizeList(params->listbase);		  /* gets new list */
fontreq.c:      for(i = 0; *(params->list + i) != NULL ; i++);			  /* counts items */
fontreq.c:      i--;
fontreq.c:      TransformCoords(W, 0,0, W->width, W->height - params->no_of_items*size + i*size);	/* sizes window */
fontreq.c:      params->no_of_items = i;
fontreq.c:      for(i = 0; i < params->no_of_items ; i++)				  /*  sorts the list  */
fontreq.c:	for(j = i; j <= params->no_of_items ; j++)
fontreq.c:	  if(atoi(*(params->list+j)) < atoi(*(params->list+i)))
fontreq.c:	    SWAP(*(params->list+j),*(params->list+i),pointer);
fontreq.c:      else if(strcmp( (pointer = GetFamily(familylist[entry-1])),(pointer2 = GetFamily(line))))  /* if original */
fontreq.c:	  sprintf(returnlist[j],"%d",sizelist[i-1]);
fontreq.c:  sprintf(line,"ls -1 %s | sed '/^\\./d' | sed  >%s 's/.*\\///'",VLWFONTDIR,POINTSIZELIST);
fontreq.c:  sprintf(line,"ls -1 %s/*.rfnt | sed '/\\..*\\./d' | sed 's/.*\\///' | sed > tempfile 's/\\.rfnt//'",RFONTDIR);
fontreq.c:      if(strcmp((pointer = GetFamily(*(familylist+i-1))) ,(pointer2 = GetFamily(line))) != 0)
fontreq.c:/* *DKY- 8Oct90* */
fontreq.c:DelayedMakeFontRequester( root, echo, font, size, x, y,  c1, c2, c3,  b1, b2, b3,  t1, t2, t3,  h1, h2, h3) /* *DKY- 8Oct90* */
fontreq.c:MakeDelayedFontRequester()	/* *DKY- 8Oct90* */
getstring.c:    printf("note: MakeStringer() -- stringer already created.  not remade.\n");
getstring.c:      Stringer = MakeWindow(W->display, W->input, W, 0, 0, 100, 100, 
getstring.c:      SHeadline = MakeWindow(W->display, W->input, Stringer, 0, 0, 100, 100, 
getstring.c:      Maker(SHeadline, 15, 5, -15, 5+fontheight+4);
getstring.c:      FunkWin = MakeWindow(W->display, W->input, Stringer, 0, 0, 100, 100, 
getstring.c:      Maker(FunkWin, 15, 10+fontheight, -15, -5);
getstring.c:      Line = MakeWindow(W->display, W->input, Stringer, 0, 0, 100, 100,
getstring.c:      Maker(Line, 15+xoffset, 14+fontheight, 15+xoffset+2, -10);
getstring.c:/* *DKY-27Jul90-03:53* */
getstring.c: * have curve == 0 for non-rounded window.
getstring.c: * There's a semi-uglyness if you don't use the same font and size for the label and input
getstring.c:    printf("note: MakeStringerPlus() -- stringer already created, not remade.\n");
getstring.c:    parms->base = Stringer = MakeWindow(W->display, W->input, W, 0, 0, 100, 100, "Stringer");
getstring.c:    parms->sheadline = SHeadline = MakeWindow( W->display, W->input, Stringer, 0, 0, 100, 100, "Headline");
getstring.c:    Maker( SHeadline, 15, 5, -15, 5+fontheight+4);
getstring.c:    parms->funkwin = FunkWin = MakeWindow( W->display, W->input, Stringer, 0, 0, 100, 100, "funkwin");
getstring.c:    Maker( FunkWin, 15, 10+fontheight, -15, -5);
getstring.c:    parms->line = Line = MakeWindow( W->display, W->input, Stringer, 0, 0, 100, 100, "back");
getstring.c:    EchoWrap( Line, echo, 0, 0, 0); /* was FunkWin -- a bug? */
getstring.c:    Maker( Line, 15+xoffset, 14+fontheight, 15+xoffset+2, -10);
getstring.c:      SendMessage( parms->base, NEWCOLOR, data);
getstring.c:      SendMessage( parms->sheadline, CHANGECOLOR, data);
getstring.c:      SendMessage( parms->funkwin, NEWCOLOR, data);
getstring.c:      SendMessage( parms->funkwin, CHANGECOLOR, data);
getstring.c:      fprintf( stderr, "StringerPlusDo: Unknown message--> %d\n", ID);
getstring.c:  display = Base->display;
getstring.c:  Stringer->parent = Base;
getstring.c:  parms = (struct stringstruct *) *(C->arguments);
getstring.c:  parms->string = string;
getstring.c:  if (x+width > display->viswidth) x1 = display->viswidth-width;
getstring.c:  if (y+height > display->visheight) y1 = display->visheight-height;
getstring.c:  Stringer->display = display;
getstring.c:  SendMessage( W, GETCOLOR, color); /* *DKY-27Jul90* */
getstring.c:  c = pick->character;
getstring.c:  EchoOff(W->display);
getstring.c:	  tab  = dif = pos[charnum] + W->x1+xoffset;
getstring.c:	  ytab = W->y1+3;
getstring.c:	  charnum--;
getstring.c:	  tab -= len[charnum];
getstring.c:/*	  fill_color(W->display->fildes, BRED/255.0, BGREEN/255.0, BBLUE/225.0); *DKY-27Jul90* */
getstring.c:	  fill_color(W->display->fildes, color[0]/255.0, color[1]/255.0, color[2]/225.0); /* *DKY-27Jul90* */
getstring.c:	  rectangle(W->display->fildes, (float)tab, (float)(W->y1+4),
getstring.c:		    (float)(tab+2+len[charnum]), (float)(W->y2-5));
getstring.c:	  fill_color(W->display->fildes, 0.0, 0.0, 0.0);
getstring.c:	  rectangle(W->display->fildes, (float)(W->x1+xoffset+dif), (float)(W->y1+4),
getstring.c:		    (float)(W->x1+xoffset+dif+2), (float)(W->y2-5));
getstring.c:	  make_picture_current(W->display->fildes);
getstring.c:      EchoOff(W->display, 1);
getstring.c:	CloseWindow(W->parent);
getstring.c:      else UnstallWin(W->parent);
getstring.c:	   /** I added the following four lines.  I'm not sure why they were not there - dave small 8/90 **/
getstring.c:	   set_monitor(W->display->bits, W->display->fildes);
getstring.c:	   set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);
getstring.c:	   interior_style(W->display->fildes, INT_SOLID, FALSE);
getstring.c:	   if ((charnum < alim)&&(pos[charnum]< W->width-xoffset*2-15))
getstring.c:	       tab  = dif = pos[charnum] + W->x1+xoffset;
getstring.c:	       ytab = W->y1+4;
getstring.c:	       /*  fill_color(W->display->fildes, BRED/255.0, BGREEN/255.0, BBLUE/225.0); *DKY-27Jul90* */
getstring.c:	       fill_color(W->display->fildes, color[0]/255.0, color[1]/255.0, color[2]/225.0); /* *DKY-27Jul90* */
getstring.c:	       rectangle(W->display->fildes, (float)tab, (float)(W->y1+4), (float)(tab+2), (float)(W->y2-5));
getstring.c:	       make_picture_current(W->display->fildes);
getstring.c:               C[0] = c;                   /* super-kluge way of getting character width */
getstring.c:	       dif = pos[charnum] = pos[charnum-1]+tab;
getstring.c:	       fill_color(W->display->fildes, 0.0, 0.0, 0.0);
getstring.c:	       rectangle(W->display->fildes, (float)(W->x1+xoffset+dif), (float)(W->y1+4),
getstring.c:			 (float)(W->x1+xoffset+dif+2), (float)(W->y2-5));
getstring.c:	       make_picture_current(W->display->fildes);
getstring.c:   EchoOn(pick->x, pick->y, W->display);
globals.c:   Echoes, query windows, two-screen operation...
globals.c:int e_value;			/* use this as a debugging flag... --Tim 3/29/91 */
grid.c:  params->step = step;
grid.c:  params->length = length;
grid.c:  params->num = num;
grid.c:  params->topmargin = topmargin;
grid.c:  params->leftmargin = leftmargin;
grid.c:  params->orient = orient;
grid.c:  params->thickness = thickness;
grid.c:  params->r = r;
grid.c:  params->g = g;
grid.c:  params->b = b;
grid.c:  screen = (W->display)->fildes;
grid.c:    cx1 = cstruct->x1;
grid.c:    cx2 = cstruct->x2;
grid.c:    cy1 = cstruct->y1;
grid.c:    cy2 = cstruct->y2;
grid.c:    length = parms->length;
grid.c:    step = parms->step;
grid.c:    topmargin = parms->topmargin + W->rely;
grid.c:    leftmargin = parms->leftmargin + W->relx;
grid.c:    num = parms->num;
grid.c:    thickness = parms->thickness;
grid.c:    orient = parms->orient;
grid.c:    red = (float) (parms->r) / 255.0;  
grid.c:    green = (float) (parms->g) / 255.0;
grid.c:    blue = (float) (parms->b) / 255.0;
grid.c:    clip_rectangle (screen, (float)0.0, (float)((W->display)->width-1), (float)0.0, (float)((W->display)->height-1));
hairy.c:/*  draw draws an anti-aliased line on the screen, if there are two points previously defined.
hairy.c:      && ((fabs (x - ax) > MINLEN) || (fabs (y - ay) > MINLEN))) /* make sure line is a minimum length */
hairy.c:	   ((fabs (x - bx) > MINLEN) || (fabs (y - by) > MINLEN))) /* make sure line is a minimum length */
hairy.c:    v1x = ax - bx;                        /* translate point b to the origin */
hairy.c:    v2x = cx - bx;
hairy.c:    v1y = ay - by;
hairy.c:    v2y = cy - by;
hairy.c:    a2 = (ang2 - ang1) / 2.0;
hairy.c:      a2 -= 90.0;
hairy.c:    b1 = 180.0 - a2;
hairy.c:  xstart = (int) (x - wd);
hairy.c:  ystart = (int) (y - wd);
hairy.c:  radius = (int) (wd - 1);
hairy.c:      near = (int) ((xx - xstart) * 16);
hairy.c:      far = (int) ((xend - xx) * 16);
hairy.c:      near2 = (int) ((yy - ystart) * 16);
hairy.c:      far2 = (int) ((yend - yy) * 16);
hairy.c:  dx_ab = bx - ax;
hairy.c:  dy_ab = by - ay;
hairy.c:    dx_ab = -dx_ab;
hairy.c:    dy_ab = -dy_ab;
hairy.c:  delyf = round (dx_ab / (len_ab * blur) * 65536);  /* get differential steps ( 0 - 65536) */
hairy.c:  dely1 = round (cos (radians ((180.0 - angle) - a1)) * 65536);
hairy.c:  delx1 = round (sin (radians ((180.0 - angle) - a1)) * 65536);
hairy.c:  dely2 = round (- cos (radians (angle + a2)) * 65536);
hairy.c:  { if (fabs ((angle + a1) - 90.0) < 0.0000001)
hairy.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
hairy.c:      ax_off = end1w * fabs (sin (radians ((a1 + angle) - 90.0)));
hairy.c:    if (fabs ((angle + a2) - 90.0) < .0000001)
hairy.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
hairy.c:      bx_off = end1w * fabs (sin (radians ((a2 + angle) - 90.0)));
hairy.c:  { if (fabs ((angle + a1) - 180.0) < 0.0000001)
hairy.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
hairy.c:      ay_off = end1w * fabs (sin (radians (180.0 - (a1 + angle))));
hairy.c:      ax_off = ay_off * fabs (tan (radians (90.0 - angle)));
hairy.c:    if (fabs ((angle + a2) - 180.0) < .0000001)
hairy.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
hairy.c:      by_off = end1w * fabs (sin (radians (180.0 - (a2 + angle))));
hairy.c:      bx_off = by_off * fabs (tan (radians (90.0 - angle)));
hairy.c:    dx_ab = -dx_ab;
hairy.c:    dy_ab = -dy_ab;
hairy.c:  xc = ax - ax_off;
hairy.c:    y = ay - ay_off;
hairy.c:  error = round (- delx * (ax - xc) + dely * (ay - y));        /* start at ax + a_off */
hairy.c:  error2_n = round ((ax - xc) * delx1 + (ay - y) * dely1) + 65536 - fudge; 
hairy.c:  error2_f = round ((bx - xc) * delx2 + (by - y) * dely2) + 65536 + fudge;
hairy.c:  offset = 16 - (width >>1); /* computes dist from edge of pixel to near edge of line */
hairy.c:  s1 = (dely >> 1) - delx;
hairy.c:    for (yc = y; (near < 32) && ((far2 > -1) || (dely2 > -1)) && ((near2 < 32) || (dely1 < 0)); --yc)
hairy.c:    err = error - dely;
hairy.c:    err2_n = error2_n - dely1;
hairy.c:    err2_f = error2_f - dely2;
hairy.c:    for (yc = y + 1; (far > -1) && ((near2 < 32) || (dely1 > -1)) && ((far2 > -1) || (dely2 < 0)); ++yc) 
hairy.c:      ink = get_ink(near, -dely, width, p, swapped, &r, &g, &b);
hairy.c:      err -= dely;
hairy.c:      err2_n -= dely1;
hairy.c:      err2_f -= dely2;
hairy.c:	    error -= dely;
hairy.c:	    error2_n -= dely1;
hairy.c:	    error2_f -= dely2;
hairy.c:	  { --y;
hairy.c:    error2_n -= delx1;
hairy.c:    error2_f -= delx2;
hairy.c:/* plots lines with slope -1 >= slope 
hairy.c:    x = ax - ax_off;
hairy.c:  yc = ay - ay_off;
hairy.c:  error = round (delx * (ax - x) - dely * (ay - yc));                          /* start at ax + ax_off */
hairy.c:  error2_n = round ((ax - x) * delx1 + (ay - yc) * dely1) + 65536 - fudge; 
hairy.c:  error2_f = round ((bx - x) * delx2 + (by - yc) * dely2) + 65536 + fudge;
hairy.c:  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */
hairy.c:    for (xc = x; (near < 32) && ((near2 < 32) || (delx1 < 0)) && ((far2 > -1) || (delx2 > -1)); --xc)
hairy.c:    err = error - delx;
hairy.c:    err2_n = error2_n - delx1;
hairy.c:    err2_f = error2_f - delx2;
hairy.c:    for (xc = x + 1; (far > -1) && ((near2 < 32) || (delx1 > -1)) && ((far2 > -1) || (delx2 < 0)); ++xc)
hairy.c:      ink = get_ink(near, -delx, width, p, !swapped, &r, &g, &b);
hairy.c:      err -= delx;
hairy.c:      err2_n -= delx1;
hairy.c:      err2_f -= delx2;
hairy.c:	  error -= delx;
hairy.c:	  error2_n -= delx1;
hairy.c:	  error2_f -= delx2;
hairy.c:	{ --x;
hairy.c:    error2_n -= dely1;
hairy.c:    error2_f -= dely2;
hairy2.c:  if ((!init) && (bristles != brush->bristles)) {
hairy2.c:    free (brush->ink);
hairy2.c:    free (brush->color);
hairy2.c:    free (brush->opacity);
hairy2.c:    brush->bristles = bristles;
hairy2.c:    if ((brush->ink = (int *)calloc(bristles, sizeof(int))) == 0)
hairy2.c:    if ((brush->opacity = (float *)calloc(bristles, sizeof(float))) == 0)
hairy2.c:    if ((brush->color = (struct ColorStruct *)calloc(bristles, sizeof(struct ColorStruct))) == 0)
hairy2.c:    new_ink = ink + (int) ((drand48() - 0.5) * variation * ink);
hairy2.c:    if (brush->ink[i] < 0) brush->ink[i] = 0;
hairy2.c:    total_ink = brush->ink[i] + new_ink;
hairy2.c:    (brush->color+i)->r = (int) ((r*per_ink) + 
hairy2.c:				 ((brush->color+i)->r * (1.0 - per_ink)));
hairy2.c:    (brush->color+i)->g = (int) ((g*per_ink) + 
hairy2.c:				 ((brush->color+i)->g * (1.0 - per_ink)));
hairy2.c:    (brush->color+i)->b = (int) ((b*per_ink) + 
hairy2.c:				 ((brush->color+i)->b * (1.0 - per_ink)));
hairy2.c:    if ((brush->color+i)->r > 255)
hairy2.c:      printf("r = %d\n", (brush->color+i)->r);
hairy2.c:    brush->ink[i] = total_ink;
hairy2.c:/*    brush->opacity[i] = 1.0 - (variation * 0.5 * drand48());*/
hairy2.c:    brush->opacity[i] = 1.0 - (0.4 * drand48());
hairy2.c:  for (x = 0; x < brush->bristles; x += 2) {
hairy2.c:    line_color(fildes, (brush->color+x)->r / 255.0, 
hairy2.c:	       (brush->color+x)->g / 255.0, 
hairy2.c:	       (brush->color+x)->b / 255.0);
hairy2.c:    draw2d(fildes, (float) (x/2 + x1), (float) y1 + (float) brush->ink[x] * 0.1);
hairy2.c:  near = -near;
hairy2.c:  bristle_wd = (float)width / (float)brush->bristles;
hairy2.c:      bristle1 = brush->bristles - bristle1;
hairy2.c:      bristle2 = brush->bristles - bristle2;
hairy2.c:    if (bristle1 >= brush->bristles) bristle1 = brush->bristles - 1;
hairy2.c:    if (bristle2 >= brush->bristles) bristle2 = brush->bristles - 1;
hairy2.c:	if (brush->ink[i] > 0) {
hairy2.c:	  ink += brush->opacity[i];
hairy2.c:	  /*	  brush->ink[i] -= 1;*/
hairy2.c:	  *r += (brush->color+i)->r;
hairy2.c:	  *g += (brush->color+i)->g;
hairy2.c:	  *b += (brush->color+i)->b;
hairy2.c:	if (brush->ink[i] > 0) {
hairy2.c:	  ink += brush->opacity[i];
hairy2.c:	  /*	  brush->ink[i] -= 1;*/
hairy2.c:	  *r += (brush->color+i)->r;
hairy2.c:	  *g += (brush->color+i)->g;
hairy2.c:	  *b += (brush->color+i)->b;
hairy2.c:  for (b = 0; b < brush->bristles; b++) 
hairy2.c:    brush->ink[b] -= amount;
hairy2.c:  near = -near;
hairy2.c:  bristle_wd = (float)width / (float)brush->bristles;
hairy2.c:  if (bristle1 >= brush->bristles) bristle1 = brush->bristles - 1;
hairy2.c:  if (bristle2 >= brush->bristles) bristle2 = brush->bristles - 1;
hairy2.c:    if (brush->ink[b] > 0) {
hairy2.c:      ink = brush->opacity[b];
hairy2.c:      brush->ink[b] -= 1;
hairy2.c:      if (brush->ink[b] > 0) {
hairy2.c:	ink += brush->opacity[b];
hairy2.c:	brush->ink[b] -= 1;
hairy2.c:      if (brush->ink[b] > 0) {
hairy2.c:	ink += brush->opacity[b];
hairy2.c:	brush->ink[b] -= 1;
icon.c:struct ticon_struct    /* triple icons  SL-10/5/90 */
icon.c:  c->icon = icon;
icon.c:  c->r1 = r1;
icon.c:  c->g1 = g1;
icon.c:  c->b1 = b1;
icon.c:  c->r2 = r2;
icon.c:  c->g2 = g2;
icon.c:  c->b2 = b2;
icon.c:  c->mask = mask;
icon.c:  switch (((struct pickstruct *)data)->button)
icon.c:    case (JUSTDOWN): flag = c->mask & 1;
icon.c:    case (JUSTUP):   flag = c->mask & 2;
icon.c:    case (BEENDOWN): flag = c->mask & 4;
icon.c:    case (BEENUP):   flag = c->mask & 8;
icon.c:  if (flag)  SwapColors(c->icon->source, c->icon->dx, c->icon->dy, c->r1, c->g1, c->b1, c->r2, c->g2, c->b2);
icon.c:    val = LoadBlurMap(path, &(icon->dx), &(icon->dy), &(icon->source));
icon.c:    val = LoadFullBitMap(path, &(icon->dx), &(icon->dy), &(icon->source));
icon.c:    val = LoadBitMap8to24(path, &(icon->dx), &(icon->dy), 
icon.c:			  &(icon->source), color, redclear);
icon.c:  icon->rule = redclear;
icon.c:  icon->hotdx = 0;
icon.c:  icon->hotdy = 0;
icon.c:  if (!(val = LoadSuguruBitMap(name, &(icon->dx), &(icon->dy), &(icon->source)))) {
icon.c:    icon->rule = redclear;
icon.c:    icon->hotdx = 0;
icon.c:    icon->hotdy = 0;
icon.c:  if (!(val = LoadDaveBitMap(name, &(icon->dx), 
icon.c:			     &(icon->dy), &(icon->source)))) 
icon.c:      icon->rule = redclear;
icon.c:      icon->hotdx = 0;
icon.c:      icon->hotdy = 0;
icon.c:  if (!(val = LoadSnakepitBitmap(name, w, h, &(icon->source)))) {
icon.c:    icon->rule = redclear;
icon.c:    icon->dx = w;
icon.c:    icon->dy = h;
icon.c:    icon->hotdx = 0;
icon.c:    icon->hotdy = 0;
icon.c:  matrix = (unsigned char *)malloc(source->dx*source->dy*3*sizeof(unsigned char));
icon.c:  for (x = 0; x < source->dx*source->dy*3; x++)
icon.c:    *(matrix+x) = *(source->source+x);
icon.c:  (*dest)->source = matrix;
icon.c:  (*dest)->dx = source->dx;
icon.c:  (*dest)->dy = source->dy;
icon.c:  (*dest)->rule = source->rule;
icon.c:  W->width = icon->dx;
icon.c:  W->height = icon->dy;
icon.c:  W->width = icon->dx;
icon.c:  W->height = icon->dy;
icon.c:  AttachCommand(W, ICON_NEWCOLOR, IconColorSwapDo, icon); /* *DKY-16Oct90* */
icon.c:  W->width = icon->dx;
icon.c:  W->height = icon->dy;
icon.c:  t->icon = icon;
icon.c:  t->transp = transparency;
icon.c:  AttachCommand(W, ICON_NEWCOLOR, IconColorSwapDo, icon); /* *DKY-16Oct90* */
icon.c:  W->width = icon->dx;
icon.c:  W->height = icon->dy;
icon.c:IconColorSwapDo( W, id, data, stuff) /* *DKY-16Oct90* */
icon.c:  SwapColors( icon->source, icon->dx, icon->dy, colors[0], colors[1], colors[2],   colors[3], colors[4], colors[5]);
icon.c:  C = W->commands;
icon.c:    while ((C->next)&&(C->id != DRAW)) C = C->next;
icon.c:    if (C->id != DRAW) return(0);
icon.c:    for (i = 0; i < C->numfuncs; i++)
icon.c:	if (*(C->functions+i) == DrawIcon)
icon.c:	    *(C->arguments+i) = data;
icon.c:  (W->display)->control[0x0003] = 0x04;
icon.c:  (W->display)->control[0x40bf] = 7;
icon.c:  if (W->display->bits == 24)
icon.c:    shape_write24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:		  W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:  else if (W->display->bits == 32)
icon.c:    shape_write32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:		  W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:  else if (W->display->bits == 4)
icon.c:  shape_write24to4(icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:		   W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:  icon = t->icon;
icon.c:  transp = t->transp;
icon.c:    (W->display)->control[0x0003] = 0x04;
icon.c:    (W->display)->control[0x40bf] = 7;
icon.c:    if (W->display->bits == 24)
icon.c:      shape_write_transp24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:			   W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2, transp);
icon.c:    else if (W->display->bits == 32)
icon.c:      shape_write_transp32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:			   W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2, transp);
icon.c:    t->transp = *((int *) (data));
icon.c:    t->icon = ((struct curstruct *) (data));
icon.c:    W->width = icon->dx;
icon.c:    W->height = icon->dy;
icon.c:    ShowWindow(W->parent, W->x1, W->y1, W->x2, W->y2);
icon.c:    if (W->parent->parent) ShowTops(W->parent, W->x1, W->y1, W->x2, W->y2);
icon.c:  d->icon1 = icon;
icon.c:  d->icon2 = icon2;
icon.c:  d->flag = 0;
icon.c:  W->width = icon->dx;
icon.c:  W->height = icon->dy;
icon.c:      if (d->flag) icon = d->icon2;
icon.c:      else icon = d->icon1;
icon.c:      (W->display)->control[0x0003] = 0x04;
icon.c:      (W->display)->control[0x40bf] = 7;
icon.c:      if (W->display->bits == 24)
icon.c:	shape_write24(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:		      W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:      else if (W->display->bits == 32)
icon.c:	shape_write32(W->display->control, icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:		      W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:      else if (W->display->bits == 4)
icon.c:	shape_write24to4(icon->source, icon->dx, icon->dy, W->display->buffer, W->display->width,
icon.c:			 W->display->height, W->x1, W->y1, icon->rule, cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:    d->flag = *((int *)data);
icon.c:    d->flag = *((int *)data);
icon.c:  xc = icon->dx;
icon.c:  yc = icon->dy;
icon.c:  matrix = icon->source;
icon.c:	    m2 = matrix2+3*(yc-y-1+x*yc);
icon.c:      icon->source = matrix2;
icon.c:      icon->dx = yc;
icon.c:      icon->dy = xc;
icon.c:	    m2 = matrix2+3*((yc-y-1)*xc+xc-x-1);
icon.c:      icon->source = matrix2;
icon.c:	    m2 = matrix2+3*(y+(xc-x-1)*yc);
icon.c:      icon->source = matrix2;
icon.c:      icon->dx = yc;
icon.c:      icon->dy = xc;
icon.c:	    m2 = matrix2+3*(y*xc+xc-x-1);
icon.c:      icon->source = matrix2;
icon.c:	    m2 = matrix2+3*((yc-y-1)*xc+x);
icon.c:      icon->source = matrix2;
icon.c:  if ((temp = (unsigned char *)malloc(sizeof(unsigned char)*icon->dx*icon->dy*3)) == NULL)
icon.c:  ptr = icon->source;
icon.c:  for (i = 0; i < (icon->dx*icon->dy); i++) {
icon.c:    *(temp+(i + (icon->dx*icon->dy))) = *ptr++;
icon.c:    *(temp+(i + (2*icon->dx*icon->dy))) = *ptr++;
icon.c:  free(icon->source);
icon.c:  icon->source = temp;
icon.c:  screen = W->display->fildes;
icon.c:    cx1 = cstruct->x1, cy1 = cstruct->y1;
icon.c:    cx2 = cstruct->x2, cy2 = cstruct->y2;
icon.c:    banks = ((int) (ceil((icon->dx / 256.0))));
icon.c:	{ wd = icon->dx % 256; if (wd == 0) wd = 256;}
icon.c:      rptr = icon->source+(bank*256);
icon.c:      gptr = icon->source+((bank*256)+(icon->dx * icon->dy));
icon.c:      bptr = icon->source+((bank*256)+(2*icon->dx * icon->dy));
icon.c:      for (y = 0; y < icon->dy; y++) {
icon.c:	rptr += icon->dx;
icon.c:	gptr += icon->dx;
icon.c:	bptr += icon->dx;
icon.c:      (W->display)->control[0x40bf] = 7;
icon.c:      for (y = 0; y < W->height; y++) {
icon.c:	y1 = ((int) ((y * icon->dy) / W->height));
icon.c:      for (x = 0; x < ((int) (wd*W->width/icon->dx)); x++) {
icon.c:	x1 = ((int) (x * icon->dx / W->width));
icon.c:	xpos = W->x1 + x + ((int) (bank*256.0*W->width/icon->dx));
icon.c:	  dcblock_move(screen, 1536+x1, cy1-W->y1, 
icon.c:		       1, cy2-cy1, 
icon.c:    (W->display)->control[0x40bf] = 7;
icon.c:AttachTripleIcon(W, icon, icon2, icon3 )     /* v 1.0b S.Librande - 10/05/90 */
icon.c:  t->icon1 = icon;
icon.c:  t->icon2 = icon2;
icon.c:  t->icon3 = icon3;
icon.c:  t->flag = 0;
icon.c:  W->width  = icon->dx;
icon.c:  W->height = icon->dy;
icon.c:TripleDrawIcon( W, id, data, stuff )      /* v 1.0b  S.Librande - 10/05/90 */
icon.c:      switch ( t->flag )
icon.c:	  icon = t->icon1;
icon.c:	  icon = t->icon2;
icon.c:	  icon = t->icon3;
icon.c:      (W->display)->control[0x0003] = 0x04;
icon.c:      (W->display)->control[0x40bf] = 7;
icon.c:      if (W->display->bits == 24)
icon.c:	shape_write24(W->display->control, icon->source,
icon.c:		                           icon->dx, icon->dy,
icon.c:		                           W->display->buffer, W->display->width,
icon.c:		       W->display->height, W->x1, W->y1, icon->rule,
icon.c:		       cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2 );
icon.c:      else if (W->display->bits == 32)
icon.c:	shape_write32(W->display->control, icon->source,
icon.c:		                           icon->dx, icon->dy,
icon.c:		                           W->display->buffer, W->display->width,
icon.c:		       W->display->height, W->x1, W->y1, icon->rule,
icon.c:		       cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:      else if (W->display->bits == 4)
icon.c:	shape_write24to4(icon->source, icon->dx, icon->dy,
icon.c:			 W->display->buffer, W->display->width,
icon.c:			 W->display->height, W->x1, W->y1, icon->rule,
icon.c:			 cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
icon.c:    t->flag = *((int *)data);
icon.c:  free(icon->source);
indicator.c:  params->stat = stat;
indicator.c:  params->r = r;
indicator.c:  params->g = g;
indicator.c:  params->b = b;
indicator.c:  params->thick = thick;
indicator.c:* This takes the standard do-function arguements *
indicator.c:* fildes (int)    The ever-present file descriptor                          *
indicator.c:  stat = params->stat;
indicator.c:  fildes = (W->display)->fildes;
indicator.c:    if (params->stat) {
indicator.c:      r = params->r;
indicator.c:      g = params->g;
indicator.c:      b = params->b;
indicator.c:      thick = params->thick;
indicator.c:      cx1 = cstruct->x1;  cy1 = cstruct->y1;
indicator.c:      cx2 = cstruct->x2;  cy2 = cstruct->y2;
indicator.c:	rectangle(fildes, (float)(W->x1 + bd), (float)(W->y1 + bd), (float)(W->x2 - bd), (float)(W->y2 - bd));
indicator.c:    button = pick->button;
indicator.c:/******************* --Tim, 3/27/91, so that the resulting turn-on/off message can be used by my window ********/
indicator.c:      params->stat = OFF; 
indicator.c:      params->stat = ON;
indicator.c:      params->stat = ON;
indicator.c:      params->stat = OFF;
indicator.c:	    or a -1 if the window is not an indicator
indicator.c:	    Tim Kukulski - July 18, 1990
indicator.c:      if (I->stat == ON)
indicator.c:      else if (I->stat == OFF) return (FALSE);
indicator.c:  else return (-1);
input.c:      locator->fildes = mouse;
input.c:      locator->width  = wide;
input.c:      locator->height = tall;
input.c:      locator->buttons = 2;
input.c:      locator->fildes = wacom;
input.c:      locator->width  = wide;
input.c:      locator->height = tall;
input.c:      locator->buttons = 0;
input.c:  locator->fildes = OpenLocator("/dev/knob1/", wide, tall);
input.c:  locator->width  = wide;
input.c:  locator->height = tall;
input.c:  locator->buttons = 0;
input.c:  locator->fildes = OpenLocator("/dev/knob2/", wide, tall);
input.c:  locator->width  = wide;
input.c:  locator->height = tall;
input.c:  locator->buttons = 0;
input.c:  locator->fildes = OpenLocator("/dev/knob3/", wide, tall);
input.c:  locator->width  = wide;
input.c:  locator->height = tall;
input.c:  locator->buttons = 0;
input.c:  locator->fildes = OpenLocator("/dev/tablet/", wide, tall);
input.c:  locator->width  = wide;
input.c:  locator->height = tall;
input.c:  locator->buttons = 1;
input.c:  locator = gopen(name, INDEV, "hp-hil", 0);
input.c:  vdc_extent(locator, (float)-20.0, (float)tall, (float)0, (float)wide-1, -20.0, (float)1);
iostuff.c:static float *ctable = NULL; /* contains paintbox 216 color table for loading old 8-bit icons */
iostuff.c:  for(blue = 1.0; blue >= 0.0; blue = blue - (1.0/5.0))
iostuff.c:    for(green = 1.0; green >= 0.0; green = green - (1.0/5.0))
iostuff.c:      for(red = 1.0; red >= 0.0; red = red - (1.0/5.0))
iostuff.c:  for (yy=yc-1; yy>=0; --yy)
iostuff.c:  for (yy=yc-1; yy>=0; --yy)
line.c:  dx_ab = bx - ax;
line.c:  dy_ab = by - ay;
line.c:    dx_ab = -dx_ab;
line.c:    dy_ab = -dy_ab;
line.c:  delyf = round (dx_ab / (len_ab * blur) * 65536);                   /* get differential steps ( 0 - 65536) */
line.c:  dely1 = round (cos (radians ((180.0 - angle) - a1)) * 65536);
line.c:  delx1 = round (sin (radians ((180.0 - angle) - a1)) * 65536);
line.c:  dely2 = round (- cos (radians (angle + a2)) * 65536);
line.c:  { if (fabs ((angle + a1) - 90.0) < 0.0000001)
line.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
line.c:      ax_off = end1w * fabs (sin (radians ((a1 + angle) - 90.0)));
line.c:    if (fabs ((angle + a2) - 90.0) < .0000001)
line.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
line.c:      bx_off = end1w * fabs (sin (radians ((a2 + angle) - 90.0)));
line.c:  { if (fabs ((angle + a1) - 180.0) < 0.0000001)
line.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
line.c:      ay_off = end1w * fabs (sin (radians (180.0 - (a1 + angle))));
line.c:      ax_off = ay_off * fabs (tan (radians (90.0 - angle)));
line.c:    if (fabs ((angle + a2) - 180.0) < .0000001)
line.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
line.c:      by_off = end1w * fabs (sin (radians (180.0 - (a2 + angle))));
line.c:      bx_off = by_off * fabs (tan (radians (90.0 - angle)));
line.c:    dx_ab = -dx_ab;
line.c:    dy_ab = -dy_ab;
line.c:      fudge = FUDGE + 2.2 * ff * (((intensity * trans) >>8) - 64);
line.c:      fudge = FUDGE + ff * (intensity - 64);
line.c:      fudge = FUDGE + 2.2 * ff * (((intensity * trans) >>8) - 64);
line.c:      fudge = FUDGE + ff * (intensity - 64);
line.c:/*  draw draws an anti-aliased line on the screen, if there are two points previously defined.
line.c:      && ((fabs (x - ax) > MINLEN) || (fabs (y - ay) > MINLEN))) /* make sure line is a minimum length */
line.c:	   ((fabs (x - bx) > MINLEN) || (fabs (y - by) > MINLEN))) /* make sure line is a minimum length */
line.c:    v1x = ax - bx;                        /* translate point b to the origin */
line.c:    v2x = cx - bx;
line.c:    v1y = ay - by;
line.c:    v2y = cy - by;
line.c:    a2 = (ang2 - ang1) / 2.0;
line.c:      a2 -= 90.0;
line.c:    b1 = 180.0 - a2;
line.c:  switch (x->type)
line.c:      printf ("ploss error, %s\n", x->name);
line.c:      printf ("tloss error, %s\n", x->name);
line.c: *    Cohen-Sutherland Clipping algorithm for line P1 = (x1, y1) to P2 = (x2, y2)
line.c:	 * y = y1 + slope * (x - x1), x = x1 + (1/slope) * (y - y1).
line.c:	  x1 = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
line.c:	  x1 = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
line.c:	  y1 = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
line.c:	  y1 = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
magnify.c:  return( factor);		/* *DKY-20Feb91* */
magnify.c:  screen = W->display->fildes;
magnify.c:    cx1 = cstruct->x1; 
magnify.c:    cy1 = cstruct->y1; 
magnify.c:    cx2 = cstruct->x2;
magnify.c:    cy2 = cstruct->y2;
magnify.c:    cx1 = W->x1;
magnify.c:    cy1 = W->y1;
magnify.c:    cx2 = W->x2;
magnify.c:    cy2 = W->y2;
magnify.c:    w = (W->width/pixel)+1;
magnify.c:    h = (W->height/pixel)+1;
magnify.c:/*    printf("FastMag %d %d  %d %d  factor %d\n",W->x1+*(factor+1),W->y1+*(factor+2),W->x1,W->y1,*factor); */
magnify.c:    FastMag(screen, W->x1 + *(factor+1), W->y1 + *(factor+2), w, h, W->x1,W->y1,pixel,0,0,0,0);
magnify.c:    clip_rectangle(screen,(float)0.0,(float)((W->display)->width-1),
magnify.c:		   0.0,(float)((W->display)->height-1));
magnify.c: *     -ability to resize window
magnify.c: *     -debug when mag factor is too small
magnify.c: *     -etc.
magnify.c:  mag = (struct Window *)MakeWindow(base->display,base->input,base,100,100,210,255,"Mag base (invisible)");
magnify.c:  magedArea = temp = (struct Window *)MakeWindow(base->display,base->input,mag,5,50,200,200,"magnifier");
magnify.c:  magStuff = (int *)MagnifierII(temp, 5, 0,-45);
magnify.c:  temp = (struct Window *)MakeWindow(base->display,base->input,mag,0,0,210,5,"top bar");
magnify.c:  temp = (struct Window *)MakeWindow( base->display, base->input, mag, 0,0,5,255, "left side");
magnify.c:  temp = (struct Window *)MakeWindow(base->display,base->input,mag,0,250,210,5,"bottom bar");
magnify.c:  temp = (struct Window *)MakeWindow(base->display,base->input,mag,205,0,5,255,"right side");
magnify.c:  temp = (struct Window *)MakeWindow(base->display,base->input,mag,0,45,210,5,"bar top of magnified area");
magnify.c:  temp = (struct Window *)MakeWindow(base->display,base->input,mag,45,0,185,45,"big black area (top right)");
magnify.c:  slider = (struct Window *)MakeWindow( base->display, base->input, temp, 0, 0, 10, 10,"mag factor slider");
magnify.c:  Maker( slider, 5, 25, -25, 45);
makefuncs.c:  params->x1 = x1;
makefuncs.c:  params->y1 = y1;
makefuncs.c:  params->x2 = x2;
makefuncs.c:  params->y2 = y2;
makefuncs.c:  params->x1 = x1;
makefuncs.c:  params->y1 = y1;
makefuncs.c:  params->x2 = x2;
makefuncs.c:  params->y2 = y2;
makefuncs.c:  params->dest = W2;
makefuncs.c:  params->id = id;
makefuncs.c:  params->data = data;
makefuncs.c:  x1 = param->x1;
makefuncs.c:  y1 = param->y1;
makefuncs.c:  if (x1<0) x1 += ((W->parent)->width-1);
makefuncs.c:  if (y1<0) y1 += ((W->parent)->height-1);
makefuncs.c:  x2 = param->x2;
makefuncs.c:  y2 = param->y2;
makefuncs.c:  if (x2<=0) x2 += ((W->parent)->width-1);
makefuncs.c:  if (y2<=0) y2 += ((W->parent)->height-1);
makefuncs.c:  x2 -= (x1-1);
makefuncs.c:  y2 -= (y1-1);
makefuncs.c:  params->x1 = x1;
makefuncs.c:  params->y1 = y1;
makefuncs.c:  params->x2 = x2;
makefuncs.c:  params->y2 = y2;
makefuncs.c:  fx1 = param->x1;
makefuncs.c:  fy1 = param->y1;
makefuncs.c:  x1 = fx1*(float)(W->parent->width-1);
makefuncs.c:  y1 = fy1*(float)(W->parent->height-1);
makefuncs.c:  if (x1<0) x1 += ((W->parent)->width-1);
makefuncs.c:  if (y1<0) y1 += ((W->parent)->height-1);
makefuncs.c:  fx2 = param->x2;
makefuncs.c:  fy2 = param->y2;
makefuncs.c:  x2 = fx2*(float)(W->parent->width-1);
makefuncs.c:  y2 = fy2*(float)(W->parent->height-1);
makefuncs.c:  if (x2<=0) x2 += (float)((W->parent)->width-1);
makefuncs.c:  if (y2<=0) y2 += (float)((W->parent)->height-1);
makefuncs.c:  x2 -= (x1-1);
makefuncs.c:  y2 -= (y1-1);
makefuncs.c:  if (W->parent->width > W->parent->height)   /* horizontal */
makefuncs.c:      if (x1<0) x1 += ((W->parent)->width-1);
makefuncs.c:      if (y1<0) y1 += ((W->parent)->height-1);
makefuncs.c:      if (x2<=0) x2 += ((W->parent)->width-1);
makefuncs.c:      if (y2<=0) y2 += ((W->parent)->height-1);
makefuncs.c:      x2 -= (x1-1);
makefuncs.c:      y2 -= (y1-1);
makefuncs.c:      if (x1<0) x1 += ((W->parent)->width-1);
makefuncs.c:      if (y1<0) y1 += ((W->parent)->height-1);
makefuncs.c:      if (x2<=0) x2 += ((W->parent)->width-1);
makefuncs.c:      if (y2<=0) y2 += ((W->parent)->height-1);
makefuncs.c:      x2 -= (x1-1);
makefuncs.c:      y2 -= (y1-1);
makefuncs.c:  x1 = param->x1;
makefuncs.c:  y1 = param->y1;
makefuncs.c:  if (x1<0) x1 += ((W->parent)->width-1);
makefuncs.c:  if (y1<0) y1 += ((W->parent)->height-1);
makefuncs.c:  x2 = param->x2;
makefuncs.c:  y2 = param->y2;
makefuncs.c:  if (x2<=0) x2 += ((W->parent)->width-1);
makefuncs.c:  if (y2<=0) y2 += ((W->parent)->height-1);
makefuncs.c:  x2 -= (x1-1);
makefuncs.c:  y2 -= (y1-1);
makefuncs.c:  SendMessage(param->dest, param->id, param->data);
matrix.c:   C[0][0] = (B[0][0]-A[0][0])*r + A[0][0]; C[0][1] = (B[0][1]-A[0][1])*r + A[0][1];
matrix.c:       C[0][2] = (B[0][2]-A[0][2])*r + A[0][2]; C[0][3] = (B[0][3]-A[0][3])*r + A[0][3];
matrix.c:   C[1][0] = (B[1][0]-A[1][0])*r + A[1][0]; C[1][1] = (B[1][1]-A[1][1])*r + A[1][1];
matrix.c:       C[1][2] = (B[1][2]-A[1][2])*r + A[1][2]; C[1][3] = (B[1][3]-A[1][3])*r + A[1][3];
matrix.c:   C[2][0] = (B[2][0]-A[2][0])*r + A[2][0]; C[2][1] = (B[2][1]-A[2][1])*r + A[2][1];
matrix.c:       C[2][2] = (B[2][2]-A[2][2])*r + A[2][2]; C[2][3] = (B[2][3]-A[2][3])*r + A[2][3];
matrix.c:   C[3][0] = (B[3][0]-A[3][0])*r + A[3][0]; C[3][1] = (B[3][1]-A[3][1])*r + A[3][1];
matrix.c:       C[3][2] = (B[3][2]-A[3][2])*r + A[3][2]; C[3][3] = (B[3][3]-A[3][3])*r + A[3][3];
matrix.c:        M[1][0] = -sinz;
matrix.c:        M[2][1] = -sinx;
matrix.c:        M[0][2] = -siny;
matrix.c:   c[0] = (a[1] * b[2] - (a[2] * b[1]));
matrix.c:   c[1] = (a[2] * b[0] - (a[0] * b[2]));
matrix.c:   c[2] = (a[0] * b[1] - (a[1] * b[0]));
matrix.c:a[0] = x1-x2; b[0] = x3 -x2;
matrix.c:a[1] = y1-y2; b[1] = y3 -y2;
matrix.c:a[2] = z1-z2; b[2] = z3 -z2;
matrix.c:   *cx = ay * bz - az * by;
matrix.c:   *cy = az * bx - ax * bz;
matrix.c:   *cz = ax * by - ay * bx;
midi.c:/*           -Dave "IO" Small 5/18/89          */
midi.c:/*--------------------------------------------------------------------*/
midi.c:/* indicator light -> it blinks red whenever there is a midi signal.  */
midi.c:/*--------------------------------------------------------------------*/
midi.c:  W = (struct Window *)MakeWindow(Parent->display, Parent->input, Parent, 
midi.c:/*--------------------------------------------------------------------*/
midi.c:/*  data (range: 0 - 127).  The note is also an int. Middle C is 60,  */
midi.c:/*--------------------------------------------------------------------*/
midi.c:  fd->note = note;
midi.c:  fd->channel = channel - 1;
midi.c:  fd->velocity = velocity;
midi.c:  fd->keystat = KEYUP;
midi.c:    button = pick->button;
midi.c:    params->keystat = KEYDOWN;
midi.c:    params->keystat = KEYUP;
midi.c:/*--------------------------------------------------------------------*/
midi.c:/*--------------------------------------------------------------------*/
midi.c:  fd->note = note;
midi.c:  fd->channel = channel;
midi.c:  fd->keystat = KEYUP;
midi.c:  keystat = params->keystat;
midi.c:    button = pick->button;
midi.c:    button = pick->button;
midi.c:    midi.note = params->note;
midi.c:    midi.channel = *(params->channel) - 1;
midi.c:    params->keystat = KEYDOWN;
midi.c:    midi.note = params->note;
midi.c:    midi.channel = *(params->channel) - 1;
midi.c:    params->keystat = KEYUP;
midi.c:  screen = W->display->fildes;
midi.c:    cx1 = cstruct->x1;
midi.c:    cy1 = cstruct->y1;
midi.c:    cx2 = cstruct->x2;
midi.c:    cy2 = cstruct->y2;
midi.c:    rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
midi.c:    rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
midi.c:    rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
midi.c:    button = pick->button;
midi.c:    byte = (unsigned char) (0xe0 + Note->channel);
midi.c:    byte = (unsigned char) Note->velocity;
midi.c:    byte = 0x90 + Note->channel;
midi.c:    byte = Note->note;
midi.c:    byte = Note->velocity;
midi.c:    byte = 0x80 + Note->channel;
midi.c:    byte = Note->note;
midi.c:    byte = Note->velocity;
midi.c:    if ((CurrentMidiWindow)&&(c != -1)) {
midi.c:/*--------------------------------------------------------------------*/
midi.c:/*--------------------------------------------------------------------*/
midi.c:   display = Root->display;
midi.c:   locator = Root->input;
midi.c:   label = (struct Window *)MakeWindow(Root->display,Root->input,Keyboard, 10,25,100,18,"label");
midi.c:   channel = (struct Window *)MakeWindow(Root->display,Root->input,Keyboard, 345,25,185,18,"channel");
midi.c:   Maker(DragBar, 5, 5, -25, 20);
midi.c:   StringWin(CloserWin, "X", 2, -2, "arch", 24, 8, 0, 0, 0, 0);
midi.c:   Maker(CloserWin, -20, 5, -5, 20);
midi.c:   Maker(SizerWin, -20, -20, -5, -5);
notes.c:  of putting this button into a popup menu, or making it a button on the surface -- each
notes.c:  of which require different opening routines.  The closing-code is built in to this routine.
notes.c:     struct Window *ToolkitParent; /* Parent of Toolkit - if set to NULL, assumes canvas as parent - DS 9/91 */
notes.c:  NoteCanvas = (struct Window *)MakeWindow(CanvasParent->display, CanvasParent->input, CanvasParent, x, y, wd, ht, "NoteCanvas");
notes.c:    NoteToolkit=(struct Window *)MakeWindow(NoteCanvas->display, NoteCanvas->input, NoteCanvas, 0, 0, 381, 230, "NoteWin");
notes.c:    NoteToolkit=(struct Window *)MakeWindow(ToolkitParent->display, ToolkitParent->input, ToolkitParent, 0, 0, 381, 230, "NoteWin");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 100, 3, 315, 15, "Drag Bar");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 273, 165, 45, 15, "Sketch2Win");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 273, 190, 45, 15, "Clear");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 273, 205, 45, 15, "Exit");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 333, 160, 39, 15, "Tools");
notes.c:  PenWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 333, 175, 45, 15, "Pencil");
notes.c:  MarkWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 333, 190, 45, 15, "Marker");
notes.c:   scheme was color-matched by hand from a set of paint chips by Suguru.  I
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 3, 22, 15*25, 15*9, "Color RandWin");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 3, 190, 100, 15, "Transparent Text");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 3, 205, 255, 15, "Transparent Slider");
notes.c:	   (char *)&(params->trans), (char *)&maxtrans, (char *)&mintrans);
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 3, 160, 100, 15, "Width Text");
notes.c:  RandWin=(struct Window *)MakeWindow(NoteToolkit->display, NoteToolkit->input, NoteToolkit, 3, 175, 255, 15, "Width Slider");
notes.c:	   (char *)&(params->thick), (char *)&maxthick, (char *)&minthick);
notes.c:  fd->selected = 24;
notes.c:  fd->size = size;
notes.c:  screen = (W->display)->fildes;
notes.c:  size = params->size;
notes.c:  selected = params->selected;
notes.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
notes.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
notes.c:	  rectangle(screen, (float) (W->x1 + i*size),
notes.c:		    (float) (W->y1 + j * size),
notes.c:		    (float) (W->x1 + i*size + size),
notes.c:		    (float) (W->y1 + j * size + size));
notes.c:    rectangle(screen, (float) (W->x1 + i*size),
notes.c:	      (float) (W->y1 + j * size),
notes.c:	      (float) (W->x1 + i*size + size),
notes.c:	      (float) (W->y1 + j * size + size));
notes.c:    button = pick->button;
notes.c:    x = pick->x - W->x1;
notes.c:    y = pick->y - W->y1;
notes.c:      params->selected = i + j*25;
notes.c:  aa_set_fb ((W->display)->bits, (W->display)->buffer, (W->display)->control);
notes.c:  pencil->hotdx = 0;
notes.c:  pencil->hotdy = 22;
notes.c:  marker->hotdx = 0;
notes.c:  marker->hotdy = 22;
notes.c:  spray->hotdy = 2;
notes.c:  brush->hotdx = 0;
notes.c:  brush->hotdy = 22;
notes.c:  eraser->hotdx = 0;
notes.c:  eraser->hotdy = 22;
notes.c:  fd->pallette = P; /* added by grace to open pallette */
notes.c:  fd->pencil = pencil;
notes.c:  fd->marker = marker;
notes.c:  fd->brush = brush;
notes.c:  fd->eraser = eraser;
notes.c:  fd->spray = spray;
notes.c:  fd->hand = hand;
notes.c:  fd->mini = mini;
notes.c:  fd->trans = 240;
notes.c:  fd->draw_mode = PENCIL;
notes.c:  fd->curs_type = MAXIMAL;
notes.c:  fd->thick = thick;
notes.c:  fd->dribble = dribble;
notes.c:  screen = (W->display)->fildes;
notes.c:  dribble = params->dribble;
notes.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
notes.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
notes.c:    aa_set_fb((W->display)->bits, (W->display)->buffer, (W->display)->control);
notes.c:    x = pick->x;
notes.c:    y = pick->y;
notes.c:    p = pick->p;
notes.c:    button = pick->button;
notes.c:    t = params->trans;
notes.c:    wd = params->thick * p;
notes.c:    W->display->control [3] = 4;
notes.c:    W->display->control [0x40bf] = 7;
notes.c:    W->display->control [0x40ef] = 0x33;
notes.c:    drawing_mode(W->display->fildes, 3);
notes.c:    make_picture_current(W->display->fildes);
notes.c:      aa_set_fb((W->display)->bits, (W->display)->buffer, (W->display)->control);
notes.c:      if (params->draw_mode == MARKER)
notes.c:      else if (params->draw_mode == PENCIL)
notes.c:      EchoOff(W->display,1);
notes.c:	(W->display)->control [3] = 4;
notes.c:	switch (params->draw_mode) {
notes.c:    if (params->curs_type == MAXIMAL)
notes.c:      switch (params->draw_mode) {
notes.c:	UpdateEcho(x,y,W->display,params->pencil);
notes.c:	UpdateEcho(x,y,W->display,params->marker);
notes.c:      UpdateEcho(x,y,W->display,params->mini);
notes.c:    params->draw_mode = PENCIL;
notes.c:    params->draw_mode = MARKER;
notes.c:    if (W->stat) CloseWindow(W);
notes.c:    if ((params->pallette)->stat) CloseWindow(params->pallette);
notes.c:    GetString(W->parent, 10, 60,"Name this object:", pathstr, 35);
notes.c:	MakeScribbleWindow(W, params->hand, pathstr);
notes.c:    if (!(W->stat)) OpenWindow(W);
notes.c:    if (!((params->pallette)->stat)) OpenWindow(params->pallette);
ofuncs.c:  if ((W->stat)&&(W->parent->stat)&&((id != DRAW)||(*(colors+3))))
ofuncs.c:      if (id != DRAW) EchoOff(W->display, 0);
ofuncs.c:      screen = W->display->fildes;
ofuncs.c:      rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
ofuncs.c:      if (id != DRAW) EchoOn(E_lastx, E_lasty, W->display);
ofuncs.c:  *(colors+3) = stuff->red;
ofuncs.c:  *(colors+4) = stuff->green;
ofuncs.c:  *(colors+5) = stuff->blue;
ofuncs.c:  if ((W->stat)&&(W->parent->stat)&&(id != DRAW))
ofuncs.c:      if (id != DRAW) EchoOff(W->display, 0);
ofuncs.c:      if (id != DRAW) EchoOn(E_lastx, E_lasty, W->display);
oldechoes.c:  orientation =  (x2-x1 > y2-y1);     /*** find out whether to divide up horizontally or vertically ***/
oldechoes.c:      E_maxwide[i] = x2-x1+1;
oldechoes.c:      E_maxtall[i] = (y2-y1+1)/4;
oldechoes.c:      E_maxwide[i] = (x2-x1+1)/4;
oldechoes.c:      E_maxtall[i] = y2-y1+1;
oldechoes.c:  int x, y, dx, dy, bits, i = -1, color;
oldechoes.c:  buffer = O->buffer;
oldechoes.c:  ibuf = (int *)O->buffer;
oldechoes.c:  control = O->control;
oldechoes.c:  bits = O->bits;
oldechoes.c:  if ((i>=0)&&(cursor->dx > E_maxwide[i])||(cursor->dy > E_maxtall[i]))
oldechoes.c:    printf("ERROR: InstallCursor() - Not enough space.\n                       - Your cursor is probably an illegal value\n");
oldechoes.c:      dx = cursor->dx;
oldechoes.c:      dy = cursor->dy;
oldechoes.c:      spos = cursor->source;
oldechoes.c:      E_wide[i] = cursor->dx;
oldechoes.c:      E_tall[i] = cursor->dy;
oldechoes.c:      E_hotdx[i] = cursor->hotdx;
oldechoes.c:      E_hotdy[i] = cursor->hotdy;
oldechoes.c:      fill_color(O->fildes, 0.0, 0.0, 0.0);
oldechoes.c:      drawing_mode(O->fildes, 3);
oldechoes.c:      interior_style(O->fildes, INT_SOLID, FALSE);
oldechoes.c:      rectangle(O->fildes, (float)E_sourcex[i], (float)E_sourcey[i],
oldechoes.c:		           (float)(E_sourcex[i]+dx-1), (float)(E_sourcey[i]+dy-1));
oldechoes.c:      make_picture_current(O->fildes);
oldechoes.c:	    if (*(spos+3*(x+y*dx)) == cursor->rule)
oldechoes.c:		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = *(cursor->source+3*(x+y*cursor->dx));
oldechoes.c:		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = *(cursor->source+3*(x+y*cursor->dx)+1);
oldechoes.c:		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*2048) = *(cursor->source+3*(x+y*cursor->dx)+2);
oldechoes.c:		    color = *(cursor->source+3*(x+y*cursor->dx))<<16 |
oldechoes.c:		      (*(cursor->source+3*(x+y*cursor->dx)+1))<<8 |
oldechoes.c:			(*(cursor->source+3*(x+y*cursor->dx)+2));
oldechoes.c:		    *(buffer+E_sourcex[i]+x+(E_sourcey[i]+y)*1024) = (*(cursor->source+3*(x+y*cursor->dx))) >>4;
oldechoes.c:  else printf("ERROR: UpdateEcho() - screen value not known\n");
oldechoes.c:  display = fildes->fildes;
oldechoes.c:      fildes->control [0x40c3] = 2;
oldechoes.c:      fildes->control[0x40bf] = 7;
oldechoes.c:      dcblock_move(display, E_backx[i], E_backy[i], E_wide[i], E_tall[i], E_oldx[i]-E_hotdx[i], E_oldy[i]-E_hotdy[i]);
oldechoes.c:      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_backx[i], E_backy[i]);
oldechoes.c:      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);
oldechoes.c:      dcblock_move(display, E_finalx[i], E_finaly[i], E_wide[i], E_tall[i], x-E_hotdx[i], y-E_hotdy[i]);
oldechoes.c:      fildes->control[0x40bf] = 7;
oldechoes.c:      fildes->control [0x40c3] = 2;         
oldechoes.c:      dcblock_move(fildes->fildes, E_backx[i], E_backy[i], E_wide[i], E_tall[i],
oldechoes.c:		                   E_oldx[i]-E_hotdx[i], E_oldy[i]-E_hotdy[i]);
oldechoes.c:      if (now) make_picture_current(fildes->fildes);
oldechoes.c:  else printf("ERROR: EchoOn() - screen value not known\n");
oldechoes.c:  if (x == 123456) {	/* *TIM-19Apr91* */
oldechoes.c:  display = fildes->fildes;
oldechoes.c:      fildes->control [0x40c3] = 2; 
oldechoes.c:      fildes->control[0x40bf] = 7;
oldechoes.c:      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_backx[i], E_backy[i]);
oldechoes.c:      dcblock_move(display, x-E_hotdx[i], y-E_hotdy[i], E_wide[i], E_tall[i], E_finalx[i], E_finaly[i]);
oldechoes.c:      dcblock_move(display, E_finalx[i], E_finaly[i], E_wide[i], E_tall[i], x-E_hotdx[i], y-E_hotdy[i]);
oldechoes.c:  else printf("ERROR: ChangeEcho() - screen value not known\n");
oldline.c:  dx_ab = bx - ax;
oldline.c:  dy_ab = by - ay;
oldline.c:    dx_ab = -dx_ab;
oldline.c:    dy_ab = -dy_ab;
oldline.c:  delyf = round (dx_ab / (len_ab * blur) * 65536);                   /* get differential steps ( 0 - 65536) */
oldline.c:  dely1 = round (cos (radians ((180.0 - angle) - a1)) * 65536);
oldline.c:  delx1 = round (sin (radians ((180.0 - angle) - a1)) * 65536);
oldline.c:  dely2 = round (- cos (radians (angle + a2)) * 65536);
oldline.c:  { if (fabs ((angle + a1) - 90.0) < 0.0000001)
oldline.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
oldline.c:      ax_off = end1w * fabs (sin (radians ((a1 + angle) - 90.0)));
oldline.c:    if (fabs ((angle + a2) - 90.0) < .0000001)
oldline.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
oldline.c:      bx_off = end1w * fabs (sin (radians ((a2 + angle) - 90.0)));
oldline.c:  { if (fabs ((angle + a1) - 180.0) < 0.0000001)
oldline.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a1 - 90.0)));
oldline.c:      ay_off = end1w * fabs (sin (radians (180.0 - (a1 + angle))));
oldline.c:      ax_off = ay_off * fabs (tan (radians (90.0 - angle)));
oldline.c:    if (fabs ((angle + a2) - 180.0) < .0000001)
oldline.c:    { end1w = (wd / 2.0) / cos (radians (fabs (a2 - 90.0)));
oldline.c:      by_off = end1w * fabs (sin (radians (180.0 - (a2 + angle))));
oldline.c:      bx_off = by_off * fabs (tan (radians (90.0 - angle)));
oldline.c:    dx_ab = -dx_ab;
oldline.c:    dy_ab = -dy_ab;
oldline.c:      fudge = FUDGE + 2.2 * ff * (((intensity * trans) >>8) - 64);
oldline.c:      fudge = FUDGE + ff * (intensity - 64);
oldline.c:      fudge = FUDGE + 2.2 * ff * (((intensity * trans) >>8) - 64);
oldline.c:      fudge = FUDGE + ff * (intensity - 64);
oldline.c:/*  draw draws an anti-aliased line on the screen, if there are two points previously defined.
oldline.c:      && ((fabs (x - ax) > MINLEN) || (fabs (y - ay) > MINLEN))) /* make sure line is a minimum length */
oldline.c:	   ((fabs (x - bx) > MINLEN) || (fabs (y - by) > MINLEN))) /* make sure line is a minimum length */
oldline.c:    v1x = ax - bx;                        /* translate point b to the origin */
oldline.c:    v2x = cx - bx;
oldline.c:    v1y = ay - by;
oldline.c:    v2y = cy - by;
oldline.c:    a2 = (ang2 - ang1) / 2.0;
oldline.c:      a2 -= 90.0;
oldline.c:    b1 = 180.0 - a2;
oldline.c:  switch (x->type)
oldline.c:      printf ("ploss error, %s\n", x->name);
oldline.c:      printf ("tloss error, %s\n", x->name);
onechar.c:/* ONECHAR.C -- By Chris Crowley (VLW)  (cajc@media-lab.media.mit.edu or @leo)              */
onechar.c:/*** these types were not included in the 300's -dave small 8/90 ****/
onechar.c:/*** they are in hp-ux 8.0 -- craig kanarick, Mon 27 Jan 93 1:54 am ***/
onechar.c:#ifdef HP-UX.300.7.0
onechar.c:     /***  mode:  1 = wait, 0 = no wait (non-blocking)  ***/
onechar.c:  termbuf.c_lflag &= ~(ICANON | (1-echo)*ECHO);
onechar.c:  if (c!=-1)
onechar.c:  if (c == -1) c = 0;
paragraph.c:/*  SUGGESTION:  What about adding the ability to center, fill, or right-justify paragraphs?
paragraph.c:/******* good idea... I'll do that next time I have time to dig in the code... --Tim */
paragraph.c:  params->font = font;
paragraph.c:  params->para = para;
paragraph.c:  params->size = size;
paragraph.c:  params->bits = bits;
paragraph.c:  params->offx = offx;
paragraph.c:  params->offy = offy;
paragraph.c:  params->red = red;
paragraph.c:  params->green = green;
paragraph.c:  params->blue = blue;
paragraph.c:  params->t = t;
paragraph.c:  params->top = 0;
paragraph.c:  params->leading = 0;
paragraph.c:      if ((fp=fopen(mstruct->para, "r"))==0) {
paragraph.c:	printf("ParagraphWin:  Error opening file '%s'.  Creating...\n", mstruct->para);
paragraph.c:	sprintf(line, "touch %s", mstruct->para);
paragraph.c:	if ((fp=fopen(mstruct->para, "r"))==0)
paragraph.c:	  printf("ParagraphWin:  Error creating file '%s'.  Creating...\n", mstruct->para);
paragraph.c:      set_font(mstruct->font, mstruct->size, mstruct->bits);
paragraph.c:      set_leading(mstruct->leading);
paragraph.c:      set_monitor(W->display->bits, W->display->fildes);
paragraph.c:      set_font_color(mstruct->red, mstruct->green, mstruct->blue, mstruct->t);
paragraph.c:      set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
paragraph.c:      make_picture_current(W->display->fildes);
paragraph.c:			     W->x1+mstruct->offx,
paragraph.c:			     W->y1+mstruct->offy
paragraph.c:			     -(int)((float)mstruct->size/4320.0*1020.0)
paragraph.c:			     -mstruct->top,
paragraph.c:			     W->x2, W->y2);
paragraph.c:     +-----------------------+
paragraph.c:     +-----------------------+
paragraph.c:     +-----------------------+
paragraph.c:	vertical_shift *= -(mstruct->size + mstruct->leading);	      /* scroll by lines */
paragraph.c:      if (vertical_shift > mstruct->top) vertical_shift = mstruct->top; /* don't go past top */
paragraph.c:      mstruct->top -= vertical_shift;				      /* shift */
paragraph.c:      set_font(mstruct->font, mstruct->size, mstruct->bits);
paragraph.c:      blocktop = W->y1 + mstruct->offy ;
paragraph.c:      blockheight = W->y2 - blocktop - vertical_shift ;
paragraph.c:      dcblock_move(W->display->fildes, W->x1, blocktop,
paragraph.c:		   W->x2-W->x1, blockheight,
paragraph.c:		   W->x1,  blocktop + vertical_shift);
paragraph.c:      AreaUpdateWin(W, W->x1, blocktop,
paragraph.c:		    W->x2, blocktop+vertical_shift);
paragraph.c:     +-----------------------+  W->y1+mstruct->offy
paragraph.c:     + - - - - - - - - - - - +  W->y1+mstruct->offy+vertical_shift   ---
paragraph.c:     |        ||             |      			          W->y2 - W->y1 -mstruct->offy - vertical shift
paragraph.c:     +-----------------------+  W->y2  . . . . . . . . ............__v
paragraph.c:     +-----------------------+  W->y1+mstruct->offy
paragraph.c:     + - - - - - - - - - - - +  W->y2-vertical shift
paragraph.c:     +-----------------------+  W->y2
paragraph.c:	vertical_shift *= -(mstruct->size + mstruct->leading);
paragraph.c:      mstruct->top += vertical_shift;
paragraph.c:      set_font(mstruct->font, mstruct->size, mstruct->bits);
paragraph.c:      blocktop = W->y1 + mstruct->offy + vertical_shift;
paragraph.c:      blockheight = W->y2 - blocktop;
paragraph.c:      dcblock_move(W->display->fildes, W->x1, blocktop,
paragraph.c:		   W->x2-W->x1, blockheight,
paragraph.c:		   W->x1,  blocktop - vertical_shift);
paragraph.c:      AreaUpdateWin(W, W->x1, W->y2-vertical_shift-mstruct->size,
paragraph.c:		    W->x2,  W->y2);
paragraph.c:      if ((fp=fopen(mstruct->para, "r"))==0) {
paragraph.c:	printf("ParagraphWin:  Error opening file '%s'.  Creating...\n", mstruct->para);
paragraph.c:	sprintf(line, "touch %s", mstruct->para);
paragraph.c:	if ((fp=fopen(mstruct->para, "r"))==0)
paragraph.c:	  printf("ParagraphWin:  Error creating file '%s'.  Creating...\n", mstruct->para);
paragraph.c:      set_font(mstruct->font, mstruct->size, mstruct->bits);
paragraph.c:      word_rect_from_wrapped_file(fp, W->x1+mstruct->offx, W->y1+mstruct->offy,
paragraph.c:				  W->x2, W->y2, wmstruct->test, wmstruct->number,
paragraph.c:				  &(wmstruct->wordx1), &(wmstruct->wordy1),
paragraph.c:				  &(wmstruct->wordx2), &(wmstruct->wordy2));
paragraph.c:      mstruct->para = data;
paragraph.c:      mstruct->para = data;
paragraph.c:      mstruct->top = 0;
paragraph.c:      if (W->stat) {CloseWindow(W); was_open = TRUE;}
paragraph.c:      mstruct->red = colors[0];
paragraph.c:      mstruct->green = colors[1];
paragraph.c:      mstruct->blue = colors[2];
paragraph.c:      mstruct->red = colors[0];
paragraph.c:      mstruct->green = colors[1];
paragraph.c:      mstruct->blue = colors[2];
paragraph.c:      mstruct->t = *trans;
paragraph.c:      mstruct->leading = *lead;
paragraph.c:      mstruct->font = newstruct->font;
paragraph.c:      mstruct->size = newstruct->size;
paragraph.c:      mstruct->bits = newstruct->bits;
paragraph.c:  params->x1 = x1;
paragraph.c:  params->y1 = y1;
paragraph.c:  params->x2 = x2;
paragraph.c:  params->y2 = y2;
paragraph.c:  params->test = temp;
paragraph.c:  params->number = number;
paragraph.c:  SendMessage(W->parent, GETWORDCOORDS, (char *)param);
paragraph.c:  relx = W->relx;
paragraph.c:  rely = W->rely;
paragraph.c:  width = W->width;
paragraph.c:  height = W->height;
paragraph.c:  if (param->x1 != NOMAKE)
paragraph.c:    relx = (param->wordx1 - W->parent->x1) + param->x1;
paragraph.c:  if (param->y1 != NOMAKE)
paragraph.c:    rely = (param->wordy1 - W->parent->y1) + param->y1;
paragraph.c:  if (param->x2 != NOMAKE)
paragraph.c:    width = (param->wordx2 - W->parent->x1 - relx) + param->x2;
paragraph.c:  if (param->y2 != NOMAKE)
paragraph.c:    height = (param->wordy2 - W->parent->y1 - rely) + param->y2;
pattern.c:* (mjbauer@media-lab.media.mit.edu  *
pattern.c:* a single-color background, it makes and maintains a patterned background.  *
pattern.c:* of the upper left corner send the PATTERN_RELATIVE message.  -SL  2/14/92  *
pattern.c:  params->pattern = pattern;
pattern.c:  params->isRelative = FALSE;
pattern.c:* This takes the standard do-function arguements *
pattern.c:* fildes (int)    The ever-present file descriptor                          *
pattern.c:* x1     (int)    The upper-left coordinates of where the master pattern is *
pattern.c:* y1     (int)      kept off-screen                                         *
pattern.c:* offx2  (int)      relative to its window.    -SL 2/14/92                  *
pattern.c:  pattern = params->pattern;
pattern.c:  fildes = (W->display)->fildes;
pattern.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
pattern.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
pattern.c:    (W->display)->control[0x0003] = 0x04;    /* these two lines set up the */
pattern.c:    (W->display)->control[0x40bf] = 7;       /* draw mode of frame buffer  */
pattern.c:    if (W->display->bits == 24)
pattern.c:      shape_write24(W->display->control,pattern->source,
pattern.c:		    pattern->dx,pattern->dy,
pattern.c:		    W->display->buffer,W->display->width,
pattern.c:		    W->display->height,x1,y1,pattern->rule,
pattern.c:    else if (W->display->bits == 32)
pattern.c:	/* Have to do a starbase command before frame buffer access will work.  Don't ask me why -BS 4/90 */
pattern.c:      interior_style(W->display->fildes,INT_SOLID,FALSE);
pattern.c:      rectangle(W->display->fildes,(float)(1280),(float)(0),(float)(1280+pattern->dx-1),(float)(pattern->dy-1));
pattern.c:      make_picture_current(W->display->fildes);
pattern.c:      shape_write32(W->display->control,pattern->source,
pattern.c:		    pattern->dx,pattern->dy,
pattern.c:		    W->display->buffer,W->display->width,
pattern.c:		    W->display->height,x1,y1,pattern->rule,
pattern.c:    else if (W->display->bits == 4)
pattern.c:      shape_write24to4(pattern->source,pattern->dx,pattern->dy,
pattern.c:		       W->display->buffer,W->display->width,
pattern.c:		       W->display->height,x1,y1,pattern->rule,
pattern.c:    pat_wd = pattern->dx;   /* width of one pattern unit */
pattern.c:    pat_ht = pattern->dy;   /* height of one pattern unit */
pattern.c:    if (params->isRelative==FALSE) {
pattern.c:      offx1 = (cx1 - W->x1)%pat_wd;  /* transform clipstruct into W's coord system */
pattern.c:      offx2 = (cx2 - W->x1)%pat_wd;
pattern.c:      offy1 = (cy1 - W->y1)%pat_ht;
pattern.c:      offy2 = (cy2 - W->y1)%pat_ht;
pattern.c:    else nextx1=pat_wd-offx1; /* the next pattern unit right of it */
pattern.c:    else nexty1=pat_ht-offy1; /* the next pattern unit below it */
pattern.c:    (W->display)->control[0x40bf] = 7;       /* draw mode of frame buffer  */
pattern.c:    if((cy2-offy2)==(cy1-offy1) &&
pattern.c:       (cx2-offx2)==(cx1-offx1))
pattern.c:		   cx2-cx1+1, cy2-cy1+1, cx1, cy1);
pattern.c:/* If the area is long and skinny -- top and bottom edges are in the same
pattern.c:    else if ((cy2-offy2)==(cy1-offy1))
pattern.c:	for(i=(cx1+nextx1); i<(cx2-offx2); i+=pat_wd)
pattern.c:	    dcblock_move(fildes, x1, y1+offy1, pat_wd, cy2-cy1+1, i, cy1);
pattern.c:		     nextx1, cy2-cy1+1, cx1, cy1);
pattern.c:		     offx2+1, cy2-cy1+1, cx2-offx2, cy1);
pattern.c:/* If the area is tall and skinny -- left and right edges are in the same
pattern.c:    else if ((cx2-offx2)==(cx1-offx1))
pattern.c:	for(j=(cy1+nexty1); j<(cy2-offy2); j+=pat_ht)
pattern.c:	    dcblock_move(fildes, x1+offx1, y1, cx2-cx1+1, pat_ht, cx1, j);
pattern.c:		     cx2-cx1+1, nexty1, cx1, cy1);
pattern.c:		     cx2-cx1+1, offy2+1, cx1, cy2-offy2);
pattern.c:	dcblock_move(fildes, x1+pat_wd-nextx1, y1+pat_ht-nexty1,
pattern.c:	dcblock_move(fildes, x1+pat_wd-nextx1, y1,
pattern.c:		     nextx1, offy2+1, cx1, cy2-offy2);
pattern.c:	dcblock_move(fildes, x1, y1+pat_ht-nexty1,
pattern.c:		     offx2+1, nexty1, cx2-offx2, cy1);
pattern.c:		     cx2-offx2, cy2-offy2);
pattern.c:	for (j=(cy1+nexty1); j<(cy2-offy2); j+=pat_ht)
pattern.c:	    dcblock_move(fildes, x1+pat_wd-nextx1, y1, nextx1, pat_ht, cx1, j);
pattern.c:			 offx2+1, pat_ht, cx2-offx2, j);
pattern.c:	for (i=(cx1+nextx1); i<(cx2-offx2); i+=pat_wd)
pattern.c:	    dcblock_move(fildes, x1, y1+pat_ht-nexty1, pat_wd, nexty1, i, cy1);
pattern.c:	    for (j=(cy1+nexty1); j<(cy2-offy2); j+=pat_ht)
pattern.c:	    dcblock_move(fildes, x1, y1, pat_wd, offy2+1, i, cy2-offy2);
pattern.c:    button = pick->button;
pattern.c:      params->isRelative = FALSE;
pattern.c:      params->isRelative = TRUE;
plotx.c:   Contains the two routines to plot lines with -1 <= slope <= 1.
plotx.c:  xc = ax - ax_off;
plotx.c:  y = ay - ay_off;
plotx.c:  error = round (- delx * (ax - xc) + dely * (ay - y));        /* start at ax + a_off */
plotx.c:  error2_n = round ((ax - xc) * delx1 + (ay - y) * dely1) + 65536 - fudge; 
plotx.c:  error2_f = round ((bx - xc) * delx2 + (by - y) * dely2) + 65536 + fudge;
plotx.c:  offset = 16 - (width >>1); /* computes dist from edge of pixel to near edge of line */
plotx.c:  s1 = (dely >> 1) - delx;
plotx.c:    for (yc = y; (near < 32) && ((far2 > -1) || (dely2 > -1)) && ((near2 < 32) || (dely1 < 0)); --yc)
plotx.c:    err = error - dely;
plotx.c:    err2_n = error2_n - dely1;
plotx.c:    err2_f = error2_f - dely2;
plotx.c:    for (yc = y + 1; (far > -1) && ((near2 < 32) || (dely1 > -1)) && ((far2 > -1) || (dely2 < 0)); ++yc) 
plotx.c:      err -= dely;
plotx.c:      err2_n -= dely1;
plotx.c:      err2_f -= dely2;
plotx.c:      error -= dely;
plotx.c:      error2_n -= dely1;
plotx.c:      error2_f -= dely2;
plotx.c:    error2_n -= delx1;
plotx.c:    error2_f -= delx2;
plotx.c:/* plots lines with -1 <= slope <= 0 
plotx.c:  xc = ax - ax_off;
plotx.c:  error = round (- delx * (ax - xc) + dely * (ay - y));                               /* start at ax + 1 */
plotx.c:  error2_n = round ((ax - xc) * delx1 + (ay - y) * dely1) + 65536 - fudge;            /* fudge ends for proper overlap */
plotx.c:  error2_f = round ((bx - xc) * delx2 + (by - y) * dely2) + 65536 + fudge;
plotx.c:  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */
plotx.c:  s1 = - (dely >> 1) - delx;
plotx.c:    for (yc = y; (near < 32) && ((far2 > -1) || (dely2 > -1)) && ((near2 < 32) || (dely1 < 0)) ; --yc)  
plotx.c:    err = error - dely;
plotx.c:    err2_n = error2_n - dely1;
plotx.c:    err2_f = error2_f - dely2;
plotx.c:    for (yc = y + 1; (far > -1) && ((near2 < 32) || (dely1 > -1)) && ((far2 > -1) || (dely2 < 0)); ++yc)
plotx.c:      err -= dely;
plotx.c:      err2_n -= dely1;
plotx.c:      err2_f -= dely2;
plotx.c:    { --y;
plotx.c:    error2_n -= delx1;
plotx.c:    error2_f -= delx2;
ploty.c:   Contains the two routines to plot lines with -1 <= slope <= 1.
ploty.c:  x = ax - ax_off;
ploty.c:  yc = ay - ay_off;
ploty.c:  error = round (delx * (ax - x) - dely * (ay - yc));                           /* start at ax + a_off */
ploty.c:  error2_n = round ((ax - x) * delx1 + (ay - yc) * dely1) + 65536 - fudge; 
ploty.c:  error2_f = round ((bx - x) * delx2 + (by - yc) * dely2) + 65536 + fudge;
ploty.c:  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */
ploty.c:  s1 = (delx >> 1) - dely;
ploty.c:    for (xc = x; (near < 32) && ((far2 > -1) || (delx2 > -1)) && ((near2 < 32) || (delx1 < 0)); --xc)
ploty.c:    err = error - delx;
ploty.c:    err2_n = error2_n - delx1;
ploty.c:    err2_f = error2_f - delx2;
ploty.c:    for (xc = x + 1; (far > -1) && ((near2 < 32) || (delx1 > -1)) && ((far2 > -1) || (delx2 < 0)); ++xc)
ploty.c:      err -= delx;
ploty.c:      err2_n -= delx1;
ploty.c:      err2_f -= delx2;
ploty.c:      error -= delx;
ploty.c:      error2_n -= delx1;
ploty.c:      error2_f -= delx2;
ploty.c:    error2_n -= dely1;
ploty.c:    error2_f -= dely2;
ploty.c:/* plots lines with slope -1 >= slope 
ploty.c:  yc = ay - ay_off;
ploty.c:  error = round (delx * (ax - x) - dely * (ay - yc));                          /* start at ax + ax_off */
ploty.c:  error2_n = round ((ax - x) * delx1 + (ay - yc) * dely1) + 65536 - fudge; 
ploty.c:  error2_f = round ((bx - x) * delx2 + (by - yc) * dely2) + 65536 + fudge;
ploty.c:  offset = 16 - (width >>1);                    /* computes dist from edge of pixel to near edge of line */
ploty.c:    for (xc = x; (near < 32) && ((near2 < 32) || (delx1 < 0)) && ((far2 > -1) || (delx2 > -1)); --xc)
ploty.c:    err = error - delx;
ploty.c:    err2_n = error2_n - delx1;
ploty.c:    err2_f = error2_f - delx2;
ploty.c:    for (xc = x + 1; (far > -1) && ((near2 < 32) || (delx1 > -1)) && ((far2 > -1) || (delx2 < 0)); ++xc)
ploty.c:      err -= delx;
ploty.c:      err2_n -= delx1;
ploty.c:      err2_f -= delx2;
ploty.c:    { --x;
ploty.c:    error2_n -= dely1;
ploty.c:    error2_f -= dely2;
ploty.c:  dely = - dely;
ploty.c:  delx = - delx;
point.c:  and in an optional 8-bit abuffer -- added 10/8/89
point.c:#define bufr(x,y) (r_bank+(x-xoff)+((y-yoff)*buf2wd))
point.c:#define bufg(x,y) (g_bank+(x-xoff)+((y-yoff)*buf2wd))
point.c:#define bufb(x,y) (b_bank+(x-xoff)+((y-yoff)*buf2wd))
point.c:	    aashort [31 - i][31 - j] = (unsigned char)(tab [i][j] * 255);
point.c:/*	    aashort [31 - i][31 - j] = (int)(tab [i][j] * 65536 + 0.55555555); */
point.c:  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
point.c:    *red = *pixel += ((r - *pixel) * filter) >>16;
point.c:    *green = *pixel += ((g - *pixel) * filter) >>16;
point.c:    *blue = *pixel += ((b - *pixel) * filter) >>16;
point.c:    *red += ((r - *red) * filter) >>16;
point.c:    *green += ((g - *green) * filter) >>16;
point.c:    *blue += ((b - *blue) * filter) >>16;
point.c:    *pixel += ((r - *pixel) * filter) >>16;
point.c:    *pixel += ((g - *pixel) * filter) >>16;
point.c:    *pixel += ((b - *pixel) * filter) >>16;
point.c:    *ab += ((255 - *ab) * filter) >>16;
point.c:  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
point.c:    *red = pixel[1] += ((r - pixel[1]) * filter) >>16;
point.c:    *green = pixel[2] += ((g - pixel[2]) * filter) >>16;
point.c:    *blue = pixel[3] += ((b - pixel[3]) * filter) >>16;
point.c:    *red += ((r - *red) * filter) >>16;
point.c:    *green += ((g - *green) * filter) >>16;
point.c:    *blue += ((b - *blue) * filter) >>16;
point.c:    pixel[1] += ((r - pixel[1]) * filter) >>16;
point.c:    pixel[2] += ((g - pixel[2]) * filter) >>16;
point.c:    pixel[3] += ((b - pixel[3]) * filter) >>16;
point.c:    *ab += ((255 - *ab) * filter) >>16;
point.c:  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
point.c:  *pixel -= (*pixel * r * filter) >>16;
point.c:  *pixel -= (*pixel * g * filter) >>16;
point.c:  *pixel -= (b * *pixel * filter) >>16;
point.c:  filter = aashort[near][near2] - aashort[far][near2] - aashort[near][far2] + aashort[far][far2] + 1;
point.c:  *pixel -= ((255 - *pixel) * r * filter) >>16;
point.c:  *pixel -= ((255 - *pixel) * g * filter) >>16;
point.c:  *pixel -= ((255 - *pixel) * b * filter) >>16;
popup.c:int PopUpCallFunction = 1;	/* *DKY-11Mar91* */
popup.c:int PopUpHighlightLine = 1;	/* *DKY-12Mar91* -- global to determine newly created pop-up lines are highlighted */
popup.c:/* POP-UP window routines
popup.c:   These routines allow you to construct a pop-up menu of choices.
popup.c:   These pop-ups assume that they are only active when the pen is down, and when you
popup.c:       B   ----------   B
popup.c:       I   |        |   I          setting a bit in the mask means that the pop-up
popup.c:       3   ----------   4
popup.c:     In this area the cursor is also 'safe'--i.e, it won't close the menu.
popup.c:     To make a pop-up, call MakePopUp with the mask you want. The window will be malloced
popup.c:     with no default control rectangle. Later you can change the pop-up's parameters with
popup.c:     There are two main ways of using these windows.  For the typical-mac menu-bar, you have
popup.c:     a window that triggers a pop-up when it gets pressed. To construct one of these, do
popup.c:                  it takes a pop-up as an argument.
popup.c:             1) assuming you have already made the pop-up, you add all the lines you want (see below).
popup.c:             2) use TransformCoords(popup, x1, y1, width, height) to set the pop-up's area on the screen.
popup.c:     Call ChangePopUpLineAttributes to change the parameters of a pop-up line.
popup.c:  pstruct->mask = mask;
popup.c:  pstruct->x1 = pstruct->y1 = pstruct->x2 = pstruct->y2 = -1; /* no rect */
popup.c:  pstruct->line_height = size;   /* I'm assuming the size is a good line_height */
popup.c:  pstruct->parms.string = NULL;
popup.c:  pstruct->parms.font   = font;
popup.c:  pstruct->parms.size   = size;
popup.c:  pstruct->parms.bits   = bits;
popup.c:  pstruct->parms.red    = fred;
popup.c:  pstruct->parms.green  = fgreen;
popup.c:  pstruct->parms.blue   = fblue;
popup.c:  pstruct->parms.t      = t;
popup.c:  pstruct->echo = echo;
popup.c:  menu = (struct Window *)MakeWindow(Root->display, Root->input, Root, 0, 0, 30, 4, "menu");
popup.c:  pt->menu = menu;
popup.c:  pt->x = x;
popup.c:  pt->y = y;
popup.c:  pt->callFunction = PopUpCallFunction;
popup.c:  menu = pt->menu;
popup.c:  if ((pick->button == BEENDOWN)||(pick->button == JUSTDOWN))
popup.c:      menu->display = W->display;
popup.c:      /* Make sure the menu is on the correct screen --> LHR 1/3/90  */
popup.c:      while(triggerroot->parent) triggerroot = triggerroot->parent;
popup.c:      menu->parent = triggerroot;
popup.c:      TransformCoords(menu, W->x1+pt->x, W->y2+pt->y, menu->width, menu->height);
popup.c:      x1 = MIN(W->x1, W->x1+pt->x);
popup.c:      x2 = MAX(W->x2, W->x1+pt->x);
popup.c:      y1 = MIN(W->y1, W->y2+pt->y);
popup.c:      y2 = MAX(W->y2, W->y2+pt->y);
popup.c:      EorSolidBox(W->display->fildes, W->x1, W->y1, W->x2, W->y2);
popup.c:      EorSolidBox(W->display->fildes, W->x1, W->y1, W->x2, W->y2);
popup.c:      if( pt->callFunction)	/* *DKY-11Mar91* */
popup.c:	if( (fs) && (fs->function))
popup.c:	    (*fs->function)(fs->arg);
popup.c: * TriggerPopUp() above.  The difference is that when the pop-up menu appears it
popup.c: * *DKY- 9Jan90*
popup.c:MakePopUpTriggerNoEor(W, echo, menu, x, y)     /* v 1.0b --- *DKY- 9Jan90**/
popup.c:  pt->menu = menu;
popup.c:  pt->x = x;
popup.c:  pt->y = y;
popup.c:  pt->callFunction = PopUpCallFunction;
popup.c:TriggerPopUpNoEor(W, id, data, stuff)     /* v 1.0b --- *DKY- 9Jan90**/
popup.c:  menu = pt->menu;
popup.c:  if ((pick->button == BEENDOWN)||(pick->button == JUSTDOWN))
popup.c:      menu->display = W->display;
popup.c:      /* Make sure the menu is on the correct screen --> LHR 1/3/90  */
popup.c:      while( triggerroot->parent) triggerroot = triggerroot->parent;
popup.c:      menu->parent = triggerroot;
popup.c:      TransformCoords(menu, W->x1+pt->x, W->y2+pt->y, menu->width, menu->height);
popup.c:      x1 = MIN(W->x1, W->x1+pt->x);
popup.c:      x2 = MAX(W->x2, W->x1+pt->x);
popup.c:      y1 = MIN(W->y1, W->y2+pt->y);
popup.c:      y2 = MAX(W->y2, W->y2+pt->y);
popup.c:      /* EorSolidBox(W->display->fildes, W->x1, W->y1, W->x2, W->y2); */
popup.c:      if( pt->callFunction)	/* *DKY-11Mar91* */
popup.c:	if( (fs) && (fs->function))
popup.c:	    (*fs->function)(fs->arg);
popup.c:      clip_rectangle(W->display->fildes,0.0,(float)W->display->width,0.0,(float)W->display->height);
popup.c:      dcblock_read(W->display->fildes,E_lastx,E_lasty,2,2,stupid,FALSE); /* STUPID STUPID STUPID fix to starbase bug */
popup.c:      fill_color(W->display->fildes,0.0,0.0,0.0);
popup.c:      interior_style(W->display->fildes,INT_SOLID,FALSE);
popup.c:      rectangle(W->display->fildes,0.0,0.0,1.0,1.0);
popup.c:      dcblock_write(W->display->fildes,E_lastx,E_lasty,2,2,stupid,FALSE); /* STUPID STUPID STUPID fix to starbase bug */
popup.c:      make_picture_current(W->display->fildes);
popup.c:/* Adds a line to a pop-up window  -- also see AddCascadingPopUpLine*/
popup.c:int CascadeTriggerWidth = 6;	/* *DKY-11Mar91* - for cascading menus */
popup.c:int CascadeUseIcon = 1;		/* *DKY-11Mar91* - do we put an icon on cascading menus? */
popup.c:/*  AddCascadePopUpLine() -- adds a line to a pop-up menu, which will display 'string' and if the pen is released
popup.c: *    right edge, a child (cascading or pull-right) menu will appear.  AddCascadePopUpLine() returns a pointer
popup.c: *    to that new child menu, which the user can then attach pop-up lines to.
popup.c: *    'cause of some bug that causes pstruct->line_height to be set improperly for large sized fonts.]
popup.c: *  *DKY-11Mar91*
popup.c:  /* only call the DO function of the first pop-up trigger -- otherwise we'll call the menu's function
popup.c:  menu2 = (struct Window *)MakePopUp( newLine, pstruct->echo, 11,
popup.c:				     pstruct->parms.font, pstruct->parms.size, 8,
popup.c:				     pstruct->parms.red, pstruct->parms.green, pstruct->parms.blue,
popup.c:				     pstruct->parms.t,
popup.c:				     rectstruct->red, rectstruct->green, rectstruct->blue);
popup.c:  /* make trigger area on right edge of menu line -- to trigger the cascade/pull-right menu */
popup.c:  newTrigger = (struct Window *)MakeWindow( newLine->display, newLine->input, newLine, 0, 0, 10, 10, "cascading menu trigger");
popup.c:  Rectify( newTrigger,  rectstruct->red, rectstruct->green, rectstruct->blue,  0, 0,0,0, 0);
popup.c:  Maker( newTrigger, -CascadeTriggerWidth, 0, 0, 0);
popup.c:  MakePopUpTriggerNoEor( newTrigger, pstruct->echo, menu2, CascadeTriggerWidth + 2, -pstruct->line_height);
popup.c:  EchoWrap( newTrigger, pstruct->echo, JUSTDOWN|BEENDOWN, 0, 0);
popup.c:    (struct Window *)MakeWindow( newLine->display, newLine->input, newLine, 0, 0, 1, 1, "cascading menu trigger");
popup.c:  Rectify( iconBase,  rectstruct->red, rectstruct->green, rectstruct->blue,  0, 0,0,0, 0);
popup.c:    TriRectify( iconBase, rectstruct->red, rectstruct->green, rectstruct->blue,
popup.c:	       pstruct->parms.red, pstruct->parms.green, pstruct->parms.blue, RIGHT);
popup.c:    Maker( iconBase, -(CascadeTriggerWidth + 6), 4, -(CascadeTriggerWidth + 1), -6);
popup.c:/*  EchoWrap( iconBase, pstruct->echo, JUSTDOWN|BEENDOWN, 0, 0); */
popup.c:/* construct a pop-up line and assign its functions */
popup.c: /* pick apart the menu-bar's function commands to get to the relevant data: menu, echo, font stuff */
popup.c: p = (struct popup_struct *) *(C->arguments);
popup.c: parms = &p->parms;
popup.c: echo = p->echo;
popup.c: line = (struct Window *)MakeWindow(menu->display, menu->input, menu, 0, 0, 100, 100, string); /* ignore size */
popup.c: Maker(line, 1, menu->height-3, -3, menu->height+16); /* these values will change in AttachPopUpLine */
popup.c:/* This function takes a pop-up line, which is not installed, and adds it to the end of a menu */
popup.c:  menu = line->parent;
popup.c:  rparms = (struct rstringstruct *) *(C->arguments);
popup.c:  sparms = rparms->parms;
popup.c:  set_font(sparms->font, sparms->size, sparms->bits);
popup.c:  wide = MAX(string_width(rparms->string)+24, menu->width);
popup.c:  mstruct = (struct makestruct *) *(C->arguments);
popup.c:  mstruct->y1 = menu->height-3;
popup.c:  mstruct->y2 = menu->height+16;
popup.c:  menu->height += 20;
popup.c:  menu->width = wide;
popup.c:  TransformCoords(menu, menu->relx, menu->rely, menu->width, menu->height);
popup.c:/* This function removes an installed pop-up line and adjusts the menu size
popup.c:   NOTE: pop-ups must be removed in the order that they were installed       */
popup.c:  menu = line->parent;
popup.c:  menu->height -= 20;
popup.c:  parms->function = function;
popup.c:  parms->arg = arg;
popup.c:  parms->highlightMenuLine = PopUpHighlightLine;
popup.c:      if( parms->highlightMenuLine) /* Only highlight if we're supposed to. *DKY-12Mar91* */
popup.c:	if (W->parent->stat == ALIVE) {
popup.c:	  EchoOff(W->display, 0);
popup.c:	  screen = W->display->fildes;
popup.c:	  rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
popup.c:	  EchoOn(E_lastx, E_lasty, W->display);
popup.c:      if ((pick->button == JUSTUP)||(pick->button == BEENUP))
popup.c:	    CloseWindow(W->parent);
popup.c:	  else UnstallWin(W->parent);
popup.c:	     query_return.  -ds 3/92
popup.c:	     if (parms->function)
popup.c:			 (*parms->function)(parms->arg); */
popup.c:    if ((!(pstruct->mask & 1)) &&(pick->y < W->y1)) outflag = 1;
popup.c:    else if ((!(pstruct->mask & 2)) &&(pick->y > W->y2)) outflag = 1;
popup.c:    else if ((!(pstruct->mask & 4)) &&(pick->x < W->x1)) outflag = 1;
popup.c:    else if ((!(pstruct->mask & 8)) &&(pick->x > W->x2)) outflag = 1;
popup.c:    if (pstruct->x1 != -1)  /* check rectangle */
popup.c:      if ((pstruct->x1 <= pick->x)&&(pstruct->y1 <= pick->y)&&(pstruct->x2 >= pick->x)&&(pstruct->y2 >= pick->y))
popup.c:    if ((pick->button == JUSTUP)||(pick->button == BEENUP)||(outflag))
popup.c:	EchoOff(W->display, 1);
popup.c:	EchoOn(pick->x, pick->y, W->display);
popup.c:      UpdateEcho(pick->x, pick->y, W->display, pstruct->echo);
popup.c:    pstruct->x1 = p2->x1;
popup.c:    pstruct->x2 = p2->x2;
popup.c:    pstruct->y1 = p2->y1;
popup.c:    pstruct->y2 = p2->y2;
popup.c:  rparms = (struct rstringstruct *) *(C->arguments);
popup.c:  rparms->string = string;
popup.c:  pstruct = (struct funcstruct *) *(C->arguments);
popup.c:  pstruct->function = function;
popup.c:  pstruct->arg = argument;
popup.c:   * DKY-27Jul90
popup.c:    menu = W->parent;
popup.c:    sparms = rparms->parms;
popup.c:    set_font( sparms->font, sparms->size, sparms->bits);
popup.c:    wide = MAX( string_width(rparms->string)+24, menu->width);
popup.c:    menu->width = wide;
popup.c:    TransformCoords( menu, menu->relx, menu->rely, menu->width, menu->height);
popup.c:SetPopUpCallFunctionMode( mode)	/* used when using cascading menus. *DKY-11Mar91* */
popup.c:SetCascadeTriggerWidth( width)	/* used to set cascading menu trigger width. *DKY-11Mar91* */
popup.c:SetCascadeUseIcon( i)	/* used to set if cascading menus have icons on them. *DKY-11Mar91* */
popup.c: * *DKY-12Mar91*
ppopen.c:*	pieper@media-lab.media.mit.edu
ppopen.c:	if ( (childpid = ppopen (fds, argc, argv)) == -1 )
ppopen.c:		return (-1);
ppopen.c:			return (-1);
ppopen.c:	if (pipe (ptoc) == -1)
ppopen.c:		return (-1);
ppopen.c:	if (pipe (ctop) == -1)
ppopen.c:		return (-1);
ppopen.c:			if (execv (*argv, argv+1) == -1)
ppopen.c:				exit (-1);
ppopen.c:		case (-1): /* error */
ppopen.c:			return (-1);
ppopen.c:	if ( (childpid = csh_ppopen (fds, command)) == -1 )
ppopen.c:		return (-1);
ppopen.c:			return (-1);
ppopen.c:	if (pipe (ptoc) == -1)
ppopen.c:		return (-1);
ppopen.c:	if (pipe (ctop) == -1)
ppopen.c:		return (-1);
ppopen.c:			if (execl ("/bin/csh", "csh", "-c", command, NULL) == -1)
ppopen.c:				exit (-1);
ppopen.c:		case (-1): /* error */
ppopen.c:			return (-1);
ppopen.c:The following code has many ways of accessing the same functionality -- which
ppopen.c:and otherwise act like their non-csh_ cousins.  These are a little less
query.c:  if (Win->relx+Win->width >= Win->display->viswidth)
query.c:    Win->relx = Win->display->viswidth-10-Win->width;
query.c:  if (Win->rely+Win->height >= Win->display->visheight)
query.c:    Win->rely = Win->display->visheight-10-Win->height;
query.c:  TransformCoords(Win, Win->relx, Win->rely, Win->width, Win->height);
query.c:  EchoOff(Win->display, 1);
query.c:    ReadLocII(Win->input->fildes, Win->display, &x, &y, &p);
query.c:    ReadLocII(Win->input->fildes, NULL, &x, &y, &p);
query.c:  while (Win->stat != DEAD)
query.c:      if ((CurrentTextWindow)&&(pick.character != -1)) SendMessage(CurrentTextWindow, NEWKEY, &pick);
query.c:      if (!screen_toggle) pick.button = ReadLocII(Win->input->fildes, Win->display, &(pick.x), &(pick.y), &(pick.p));
query.c:      else pick.button = ReadLocII(Win->input->fildes, NULL, &(pick.x), &(pick.y), &(pick.p));
query.c:  EchoOff(Win->display, 1);
register.c:  r->num = num;
register.c:  r->kind = kind;
register.c:  r->x = x;
register.c:  r->y = y;
register.c:  r->font = font;
register.c:  r->size = size;
register.c:  r->bits = bits;
register.c:  r->red = red;
register.c:  r->green = green;
register.c:  r->blue = blue;
register.c:  r->t = t;
register.c:  int oldRX;			/* *DKY-23Nov90* */
register.c:  if (r->kind == FLOAT) fnum = (float *)r->num;
register.c:  else inum = (int *)r->num;
register.c:      r->red = (colors[0]);
register.c:      r->green = (colors[1]);
register.c:      r->blue = (colors[2]);
register.c:    case(NEW_NUMBER): r->num = data;
register.c:      if (r->num) {
register.c:	if (r->kind) sprintf(string, "%5.2f", *fnum);
register.c:	set_font(r->font, r->size, r->bits);
register.c:	set_monitor(W->display->bits, W->display->fildes);
register.c:	set_font_color(r->red, r->green, r->blue, r->t);
register.c:	set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
register.c:	if( r->x >= 0)
register.c:	  display_string(string, W->x1+r->x, W->y1+r->y);
register.c:	else {			/* if X is a negative value, it'll be offset from right edge of window -- *DKY-23Nov90* */
register.c:	  display_string( string, W->x2 - width + r->x, W->y1 + r->y);
register.c:    if (pick->button == JUSTDOWN)
register.c:	if( r->x < 0) {
register.c:	  /* We move r->x so it's positive so we can type values in and have them appear in the right place.
register.c:	   * This should be a bit smarter about where to start the cursor so it doesn't overlap text that might be* in the window.   *DKY-23Nov90*
register.c:	  oldRX = r->x;
register.c:	  r->x = 2*(0 - r->x);
register.c:	set_font(r->font, r->size, r->bits);
register.c:	set_monitor(W->display->bits, W->display->fildes);
register.c:	set_font_color(r->red, r->green, r->blue, r->t);
register.c:	set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);
register.c:	tempnum = r->num;
register.c:	if (r->kind) f = *fnum;
register.c:	r->num = NULL;
register.c:	drawing_mode(W->display->fildes, 6);
register.c:	interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:	fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:	rectangle(W->display->fildes, (float)W->x1+r->x, (float)(W->y1+r->y), (float)(W->x1+r->x+2), (float)(W->y2-r->y));
register.c:	make_picture_current(W->display->fildes);
register.c:	drawing_mode(W->display->fildes, 3);
register.c:	    while ((c = getchar()) == -1);
register.c:	    while (( getchar()) != -1);
register.c:		    tab  = dif = pos[charnum] + W->x1+r->x;
register.c:		    ytab = W->y1+3;
register.c:		    string[charnum-1] = 0; /* *DKY- 8Jun91* This is to fix the backspace bug.  Before erase worked wrong. */
register.c:		    charnum--;
register.c:		    tab -= len[charnum];
register.c:		    ShowWindow(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);
register.c:		    ShowTops(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);
register.c:		    drawing_mode(W->display->fildes, 6);
register.c:		    interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:		    fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:		    rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
register.c:			      (float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
register.c:		    make_picture_current(W->display->fildes);
register.c:		    drawing_mode(W->display->fildes, 3);
register.c:		r->num = tempnum;
register.c:		if (r->kind) sscanf(string, "%f", r->num);
register.c:		else sscanf(string, "%d", r->num);
register.c:		if( oldRX)		/* *DKY-23Nov90* */
register.c:		  r->x = oldRX;
register.c:		    if ((charnum < 19)&&(pos[charnum]< W->width-r->x-15))
register.c:			tab  = dif = pos[charnum] + W->x1+r->x;
register.c:			ytab = W->y1+r->y;
register.c:			drawing_mode(W->display->fildes, 6);
register.c:			interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:			fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:			rectangle(W->display->fildes, (float)tab, (float)(W->y1+r->y), (float)(tab+2), (float)(W->y2-r->y));
register.c:			make_picture_current(W->display->fildes);
register.c:			drawing_mode(W->display->fildes, 3);
register.c:			make_picture_current(W->display->fildes);
register.c:			C[0] = c; /* super-kluge way of getting character width */
register.c:			dif = pos[charnum] = pos[charnum-1]+tab;
register.c:			drawing_mode(W->display->fildes, 6);
register.c:			interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:			fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:			rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
register.c:				  (float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
register.c:			make_picture_current(W->display->fildes);
register.c:			drawing_mode(W->display->fildes, 3);
register.c:			ShowTops(W, W->x1, W->y1, W->x2, W->y2);
register.c:  STRING REGISTER     *DKY-25Apr90*
register.c:  r->string = string;
register.c:  r->x = x;
register.c:  r->y = y;
register.c:  r->font = font;
register.c:  r->size = size;
register.c:  r->bits = bits;
register.c:  r->red = red;
register.c:  r->green = green;
register.c:  r->blue = blue;
register.c:  r->t = t;
register.c:      r->string = (char **)data;
register.c:      if (*(r->string)) {
register.c:	sprintf(string, "%s", *(r->string));
register.c:	set_font(r->font, r->size, r->bits);
register.c:	set_monitor(W->display->bits, W->display->fildes);
register.c:	set_font_color(r->red, r->green, r->blue, r->t);
register.c:	set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
register.c:	display_string(string, W->x1+r->x, W->y1+r->y);
register.c:      if (pick->button == JUSTDOWN)
register.c:	  set_font(r->font, r->size, r->bits);
register.c:	  set_monitor(W->display->bits, W->display->fildes);
register.c:	  set_font_color(r->red, r->green, r->blue, r->t);
register.c:	  set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);
register.c:	  *(r->string) = NULL;
register.c:	  drawing_mode(W->display->fildes, 6);
register.c:	  interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:	  fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:	  rectangle(W->display->fildes, (float)W->x1+r->x, (float)(W->y1+r->y), (float)(W->x1+r->x+2), (float)(W->y2-r->y));
register.c:	  make_picture_current(W->display->fildes);
register.c:	  drawing_mode(W->display->fildes, 3);
register.c:	      while ((c = getchar()) == -1);
register.c:	      while (( getchar()) != -1);
register.c:		      tab  = dif = pos[charnum] + W->x1+r->x;
register.c:		      ytab = W->y1+3;
register.c:		      charnum--;
register.c:		      tab -= len[charnum];
register.c:		      ShowWindow(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);
register.c:		      ShowTops(W, tab, W->y1+r->y, tab+2+len[charnum], W->y2-r->y);
register.c:		      drawing_mode(W->display->fildes, 6);
register.c:		      interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:		      fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:		      rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
register.c:				(float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
register.c:		      make_picture_current(W->display->fildes);
register.c:		      drawing_mode(W->display->fildes, 3);
register.c:		  /* we'd like to free what's previously stored in r->string, but if it's a ""-type string it'll crash */
register.c:		  *(r->string) = (char *)CopyString( string);
register.c:/*		      if ((charnum < 19)&&(pos[charnum]< W->width-r->x-15)) */
register.c:		      if ((pos[charnum]< W->width-r->x-15))
register.c:			  tab  = dif = pos[charnum] + W->x1+r->x;
register.c:			  ytab = W->y1+r->y;
register.c:			  drawing_mode(W->display->fildes, 6);
register.c:			  interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:			  fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:			  rectangle(W->display->fildes, (float)tab, (float)(W->y1+r->y), (float)(tab+2), (float)(W->y2-r->y));
register.c:			  make_picture_current(W->display->fildes);
register.c:			  drawing_mode(W->display->fildes, 3);
register.c:			  C[0] = c; /* super-kluge way of getting character width */
register.c:			  dif = pos[charnum] = pos[charnum-1]+tab;
register.c:			  drawing_mode(W->display->fildes, 6);
register.c:			  interior_style(W->display->fildes, INT_SOLID, FALSE);
register.c:			  fill_color(W->display->fildes, 1.0, 1.0, 1.0);
register.c:			  rectangle(W->display->fildes, (float)(W->x1+r->x+dif), (float)(W->y1+r->y), 
register.c:				    (float)(W->x1+r->x+dif+2), (float)(W->y2-r->y));
register.c:			  make_picture_current(W->display->fildes);
register.c:			  drawing_mode(W->display->fildes, 3);
register.c:			  ShowTops(W, W->x1, W->y1, W->x2, W->y2);
register.c: * *DKY- 5Aug90*
register.c:			  if (r->kind == 0)
register.c:			      c -= 33;
register.c:  parms->mask = mask;
register.c:  parms->num = num;
register.c:    switch (((struct pickstruct *)data)->button)
register.c:      case (JUSTDOWN): flag = parms->mask & 1;
register.c:      case (JUSTUP):   flag = parms->mask & 2;
register.c:      case (BEENDOWN): flag = parms->mask & 4;
register.c:      case (BEENUP):   flag = parms->mask & 8;
register.c:    if (*(parms->num) == TRUE)
register.c:      *(parms->num) = FALSE;
register.c:      *(parms->num) = TRUE;
sample.c:  screen = (W->display)->fildes;
sample.c:    cx1 = cstruct->x1;
sample.c:    cy1 = cstruct->y1;
sample.c:    cx2 = cstruct->x2;
sample.c:    cy2 = cstruct->y2;
sample.c:    clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1),
sample.c:		   0.0, (float)((W->display)->height-1));
sample.c:    make_picture_current((W->display)->fildes);
sample.c:      x = pick->x;
sample.c:      y = pick->y;
sample.c:      button = pick->button;
sample.c:	line_color(W->display->fildes, 1.0, 1.0, 1.0);
sample.c:	draw2d(W->display->fildes, (float)x, (float)y);
sample.c:	make_picture_current(W->display->fildes);
scribble.c:Note- the x and y passed to Scribblify are NOT the x and y 
scribble.c:  printf("YO!!! I have changed this code (MakeScribbleWindow)! It takes three (3) args!!!!!!! - dsmall 4/25/90\n");
scribble.c:  xoff = x1 - Parent->x1;
scribble.c:  yoff = y1 - Parent->y1;
scribble.c:  if (xoff > (Parent->width - (x2-x1))) xoff = Parent->width - (x2-x1);
scribble.c:  if (yoff > (Parent->height - (y2-y1))) yoff = Parent->height - (y2-y1);
scribble.c:  W=(struct Window *)MakeWindow(Parent->display, Parent->input, Parent,
scribble.c:				     xoff, yoff, x2 - x1, y2 - y1, path);
scribble.c:  xoff = x1 - Parent->x1;
scribble.c:  yoff = y1 - Parent->y1;
scribble.c:  if (xoff > (Parent->width - (x2-x1))) xoff = Parent->width - (x2-x1);
scribble.c:  if (yoff > (Parent->height - (y2-y1))) yoff = Parent->height - (y2-y1);
scribble.c:  W=(struct Window *)MakeWindow(Parent->display, Parent->input, Parent,
scribble.c:				     xoff, yoff, x2 - x1, y2 - y1, path);
scribble.c:  for(w = Parent, xoff = absx, yoff = absy; w->parent; w = w->parent) {
scribble.c:    xoff -= w->x1;
scribble.c:    yoff -= w->y1;
scribble.c:  *offsetx = absx - xoff;
scribble.c:  *offsety = absy - yoff;
scribble.c:  fd->path = path;
scribble.c:  fd->x = x;
scribble.c:  fd->y = y;
scribble.c:  screen = (W->display)->fildes;
scribble.c:  path = params->path;
scribble.c:  xoff = W->x1 - params->x;
scribble.c:  yoff = W->y1 - params->y;
scribble.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
scribble.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
scribble.c:    make_picture_current(W->display->fildes);
scribble.c:    W->display->control [3] = 4;
scribble.c:    W->display->control [0x40bf] = 7;
scribble.c:    W->display->control [0x40ef] = 0x33;
scribble.c:    drawing_mode(W->display->fildes, 3);
scribble.c:    aa_set_fb((W->display)->bits, (W->display)->buffer, (W->display)->control);
scribble.c:    W->display->control [3] = 4;
scribble.c:    W->display->control [0x40bf] = 7;
scribble.c:    W->display->control [0x40ef] = 0x33;
scribble.c:    drawing_mode(W->display->fildes, 3);
scribble.c:    make_picture_current(W->display->fildes);
scribble.c:	    if ((fx - wid) < minx) minx = fx - wid;
scribble.c:	    if ((fy - wid) < miny) miny = fy - wid;
scribble.c:	    if ((fx - wid) < minx) minx = fx - wid;
scribble.c:	    if ((fy - wid) < miny) miny = fy - wid;
scroller.c:  PopScroller = PopMat->parent->parent;
scroller.c:  if (PopScroller->stat)
scroller.c:  popstruct->text = text;
scroller.c:  popstruct->selection = commands;
scroller.c:  popstruct->mode = mode;
scroller.c:  strcpy(popstruct->title, s);
scroller.c:  viswidth = PopScroller->display->viswidth-20;
scroller.c:  visheight = PopScroller->display->height-20;
scroller.c:  set_font(popstruct->font, popstruct->size, 8);
scroller.c:  PopScroller->relx = x;
scroller.c:  PopScroller->rely = y;
scroller.c:****  rstruct = (struct resizestruct *)(PopScroller->port->Front->id->dostuff);
scroller.c:****  rstruct->x = width;
scroller.c:  if (PopScroller->relx+width > viswidth) PopScroller->relx = viswidth-width;
scroller.c:  if (PopScroller->rely+height > visheight) PopScroller->rely = visheight-height;
scroller.c:  TransformCoords(PopScroller, PopScroller->relx, PopScroller->rely, width, height);
scroller.c:/* non-global file scroller */
scroller.c:  Maker(resizer, -20, -25, -5, -10);
scroller.c:  pad = s->pad;  /* THIS is the inner window that will be returned to the caller */
scroller.c:  TextSelector(pad, echo, vfont, size, &s->line, &s->area, &s->min, &s->max, n1, n2, n3, h1, h2, h2, m1, m2, m3);
scroller.c:  Maker(ScrollMat, 5, 5+size+4+3, -7, -7-size-4-8);
scroller.c:  StringWin(headback, tstruct->title, 9, 1, vfont, size, 8, n1, n2, n3, 0);
scroller.c:  StringWin(headback, tstruct->title, 8, 0, vfont, size, 8, h1, h2, h3, 0);
scroller.c:  Maker(headback, 5, 5, -7, 5+size+4);
scroller.c:  Maker(Oback, 5, -7-size-4-5, p1+5, -7);
scroller.c:  Maker(Cback, -p2-36, -7-size-4-5, -36, -7);
scroller.c:  TransformCoords(Scroller, Scroller->relx, Scroller->rely, 400, 300);
scroller.c:  params->line = line;
scroller.c:  params->area = area;
scroller.c:  params->min = min;
scroller.c:  params->max = max;
scroller.c:  params->echo = echo;
scroller.c:  params->c1 = c1;
scroller.c:  params->c2 = c2;
scroller.c:  params->c3 = c3;
scroller.c:  params->s1 = s1;
scroller.c:  params->s2 = s2;
scroller.c:  params->s3 = s3;
scroller.c:  params->m1 = m1;
scroller.c:  params->m2 = m2;
scroller.c:  params->m3 = m3;
scroller.c:  params->text = NULL;
scroller.c:  params->font = vfont;
scroller.c:  params->size = size;
scroller.c:  params->selection = NULL;
scroller.c:  *(params->title) = NULL;
scroller.c:  screen = W->display->fildes;
scroller.c:      cx1 = cstruct->x1;  cy1 = cstruct->y1;
scroller.c:      cx2 = cstruct->x2;  cy2 = cstruct->y2;
scroller.c:      cx2 = W->display->viswidth;
scroller.c:      cy2 = W->display->visheight;
scroller.c:  text = parms->text;
scroller.c:  selection = parms->selection;
scroller.c:  startline = *parms->line;
scroller.c:  maxline = MIN(startline+*parms->area, *parms->max);
scroller.c:  offred = (float)parms->c1/255.0;
scroller.c:  offgreen = (float)parms->c2/255.0;
scroller.c:  offblue = (float)parms->c3/255.0;
scroller.c:  onred = (float)parms->s1/255.0;
scroller.c:  ongreen = (float)parms->s2/255.0;
scroller.c:  onblue = (float)parms->s3/255.0;
scroller.c:  ygap = parms->size;
scroller.c:  leftedge = W->x1+5;
scroller.c:  y = W->y1+5;
scroller.c:  set_font(parms->font, parms->size, 8);
scroller.c:  set_monitor(W->display->bits, W->display->fildes);
scroller.c:  fill_color(screen, (float)parms->m1/255.0, (float)parms->m2/255.0, (float)parms->m3/255.0);
scroller.c:  rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
scroller.c:      rectangle(screen, (float)leftedge, (float)y, (float)(leftedge+xgap-1), (float)(y+ygap-1));
scroller.c:  y = W->y1+3;
scroller.c:	  set_font_color(parms->s1, parms->s2, parms->s3, 0);
scroller.c:	  set_font_color(parms->c1, parms->c2, parms->c3, 0);
scroller.c:  clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
scroller.c:		 0.0, (float)((W->display)->height-1));
scroller.c:  echo = parms->echo;
scroller.c:  screen = W->display->fildes;
scroller.c:  text = parms->text;
scroller.c:  selection = parms->selection;
scroller.c:  startline = *parms->line;
scroller.c:  maxline = MIN(startline+*parms->area, *parms->max);
scroller.c:  offred = (float)parms->c1/255.0;
scroller.c:  offgreen = (float)parms->c2/255.0;
scroller.c:  offblue = (float)parms->c3/255.0;
scroller.c:  onred = (float)parms->s1/255.0;
scroller.c:  ongreen = (float)parms->s2/255.0;
scroller.c:  onblue = (float)parms->s3/255.0;
scroller.c:  set_font(parms->font, parms->size, 8);
scroller.c:  set_monitor(W->display->bits, W->display->fildes);
scroller.c:  set_text_clip_rectangle(W->x1, W->y1, W->x2, W->y2);
scroller.c:  ygap = parms->size;
scroller.c:  leftedge = W->x1+5;
scroller.c:    x = pick->x;
scroller.c:    y = pick->y;
scroller.c:    button = pick->button;
scroller.c:      EchoOff(W->display, 1);
scroller.c:	ys = W->y1+5;
scroller.c:	    if ((x>W->x1)&&(x<W->x2)&&(y>ys)&&(y<ys+ygap))
scroller.c:		if ((button == JUSTDOWN)&&(parms->mode)) mode = !selection[line];
scroller.c:		else if (!parms->mode) mode = TRUE;
scroller.c:		    fill_color(screen, (float)parms->m1/255.0, (float)parms->m2/255.0, (float)parms->m3/255.0);
scroller.c:		    if (!parms->mode) {
scroller.c:		      for (t = 0; (t < *parms->max)&&(notdone2); t++)
scroller.c:				ytop = W->y1+5+(t-startline)*(ygap+yspace);
scroller.c:					  (float)(W->x2-1), (float)(ybot+yspace));
scroller.c:					  (float)(leftedge+xgap-1), (float)ybot-1);
scroller.c:				set_font_color(parms->c1, parms->c2, parms->c3, 0);
scroller.c:				display_string(*(text+t), leftedge+xgap+xspace, ytop-2);
scroller.c:				ShowTops(W, W->x1, ytop, W->x2, ybot);
scroller.c:				fill_color(screen, (float)parms->m1/255.0, (float)parms->m2/255.0,
scroller.c:					   (float)parms->m3/255.0);
scroller.c:		    rectangle(screen, (float)leftedge+xgap+1, (float)ys, (float)(W->x2-1), (float)(ys+ygap));
scroller.c:		    rectangle(screen, (float)leftedge, (float)ys, (float)(leftedge+xgap-1), (float)(ys+ygap-1));
scroller.c:		      set_font_color(parms->s1, parms->s2, parms->s3, 0);
scroller.c:		      display_string(*(text+line), leftedge+xgap+xspace, ys-2);
scroller.c:		      set_font_color(parms->c1, parms->c2, parms->c3, 0);
scroller.c:		      display_string(*(text+line), leftedge+xgap+xspace, ys-2);
scroller.c:		    ShowTops(W, W->x1, ys, W->x2, ys+ygap);
scroller.c:      EchoOn(x, y, W->display);
scroller.c:    case (BEENUP):    UpdateEcho(x, y, W->display, echo);
scroller.c:      dy = (W->height-10)/(parms->size+3);
scroller.c:      GetArrayInfo(parms->text, &lines, &width, 0);
scroller.c:      *parms->area = MAX(dy, 1);
scroller.c:      *parms->max = MAX(lines, 1);
scroller.c:      *parms->line = 0;
scroller.c:      selection[*parms->max] = id;
scroller.c:      CloseWindow(W->parent->parent);
shadows.c:     ------------------------------------------------------------------
shadows.c:  if ( W->parent == NULL ) {
shadows.c:    fprintf( stderr, "TransShadowify: cannot put a shadow on %s. (no parent)\n", W->tag );
shadows.c:  parms->vertShadow   = NULL;
shadows.c:  parms->horizShadow  = NULL;
shadows.c:  parms->isShadowOn   = TRUE;
shadows.c:  parms->position     = CheckPosition( position );
shadows.c:  parms->offset       = CheckOffset( W, offset );
shadows.c:  parms->transparency = CheckTransparency( transparency );
shadows.c:  ShadowSizeAndPos( W, parms->offset, parms->position, vertSize,  vertPos,  V_SHADOW );
shadows.c:  ShadowSizeAndPos( W, parms->offset, parms->position, horizSize, horizPos, H_SHADOW );
shadows.c:  parms->vertShadow =  (struct Window *)MakeWindow( W->display, W->input, W->parent,
shadows.c:  TransRectify( parms->vertShadow, 0,0,0, 0, 0,0,0, 0, parms->transparency );
shadows.c:  Wimp( parms->vertShadow );
shadows.c:  EchoWrap( parms->vertShadow, echo, JUSTDOWN | JUSTUP | BEENDOWN, 0, 0 );
shadows.c:  InstallWin( parms->vertShadow );
shadows.c:  parms->horizShadow = (struct Window *)MakeWindow( W->display, W->input, W->parent,
shadows.c:  TransRectify( parms->horizShadow, 0,0,0, 0, 0,0,0, 0, parms->transparency );
shadows.c:  Wimp( parms->horizShadow );
shadows.c:  EchoWrap( parms->horizShadow, echo, JUSTDOWN | JUSTUP | BEENDOWN, 0, 0 );
shadows.c:  InstallWin( parms->horizShadow );
shadows.c:	parms->offset = CheckOffset( W, parms->offset );
shadows.c:	ShadowSizeAndPos( W, parms->offset, parms->position, vSize, vPos, V_SHADOW );
shadows.c:	ShadowSizeAndPos( W, parms->offset, parms->position, hSize, hPos, H_SHADOW );
shadows.c:	if ( parms->isShadowOn ) {
shadows.c:	  CloseWindow( parms->vertShadow );
shadows.c:	  CloseWindow( parms->horizShadow );
shadows.c:	if ( parms->vertShadow->parent != W->parent ) {
shadows.c:	  parms->horizShadow->parent  = W->parent;
shadows.c:	  parms->vertShadow->parent   = W->parent;
shadows.c:	  parms->horizShadow->display = W->display;
shadows.c:	  parms->vertShadow->display  = W->display;
shadows.c:	TransformCoords( parms->vertShadow, vPos[ X ],vPos[ Y ], vSize[ X ],vSize[ Y ] );
shadows.c:	TransformCoords( parms->horizShadow,hPos[ X ],hPos[ Y ], hSize[ X ],hSize[ Y ] );
shadows.c:	if ( parms->isShadowOn ) {
shadows.c:	  OpenWindow( parms->vertShadow );
shadows.c:	  OpenWindow( parms->horizShadow );
shadows.c:      parms->offset = CheckOffset( W, parms->offset );
shadows.c:      ShadowSizeAndPos( W, parms->offset, parms->position, vSize, vPos, V_SHADOW );
shadows.c:      ShadowSizeAndPos( W, parms->offset, parms->position, hSize, hPos, H_SHADOW );
shadows.c:      if ( parms->isShadowOn ) {
shadows.c:	CloseWindow( parms->vertShadow );
shadows.c:	CloseWindow( parms->horizShadow );
shadows.c:      if ( parms->vertShadow->parent != W->parent ) {
shadows.c:	parms->horizShadow->parent  = W->parent;
shadows.c:	parms->vertShadow->parent   = W->parent;
shadows.c:	parms->horizShadow->display = W->display;
shadows.c:	parms->vertShadow->display  = W->display;
shadows.c:      TransformCoords( parms->vertShadow, vPos[ X ], vPos[ Y ], vSize[ X ], vSize[ Y ] );
shadows.c:      TransformCoords( parms->horizShadow,hPos[ X ], hPos[ Y ], hSize[ X ], hSize[ Y ] );
shadows.c:      if ( parms->isShadowOn ) {
shadows.c:	OpenWindow( parms->vertShadow );
shadows.c:	OpenWindow( parms->horizShadow );
shadows.c:      parms->isShadowOn = FALSE;
shadows.c:      if ( parms->vertShadow->stat == OPENED ) {
shadows.c:	CloseWindow( parms->vertShadow );
shadows.c:	CloseWindow( parms->horizShadow );
shadows.c:      parms->isShadowOn = TRUE;
shadows.c:      if ( parms->vertShadow->stat == CLOSED ) {
shadows.c:	OpenWindow( parms->vertShadow );
shadows.c:	OpenWindow( parms->horizShadow );
shadows.c:      parms->offset = CheckOffset( W, newData );
shadows.c:      parms->position = CheckPosition( newData );
shadows.c:      parms->transparency = newData;
shadows.c:      SendMessage( parms->vertShadow,  TR_CHANGETRANS, (char *)&newData );
shadows.c:      SendMessage( parms->horizShadow, TR_CHANGETRANS, (char *)&newData );
shadows.c:      SendMessage( parms->vertShadow,  NEWCOLOR, data );
shadows.c:      SendMessage( parms->horizShadow, NEWCOLOR, data );
shadows.c:    size[ Y ] = W->height - offset;
shadows.c:      pos[ X ]  = W->relx + W->width;
shadows.c:      pos[ Y ]  = W->rely;
shadows.c:      pos[ X ]  = W->relx - offset;
shadows.c:      pos[ Y ]  = W->rely;
shadows.c:      pos[ X ]  = W->relx + W->width;
shadows.c:      pos[ Y ]  = W->rely + offset;
shadows.c:      pos[ X ]  = W->relx - offset;
shadows.c:      pos[ Y ]  = W->rely + offset;
shadows.c:    size[ X ] = W->width;
shadows.c:      pos[ X ] = W->relx + offset;
shadows.c:      pos[ Y ] = W->rely - offset;
shadows.c:      pos[ X ] = W->relx - offset;
shadows.c:      pos[ Y ] = W->rely - offset;
shadows.c:      pos[ X ] = W->relx + offset;
shadows.c:      pos[ Y ] = W->rely + W->height;
shadows.c:      pos[ X ] = W->relx - offset;
shadows.c:      pos[ Y ] = W->rely + W->height;
shadows.c:  int max_offset = MIN( W->width, W->height );
shadows.c:  return( ! (( W->relx == shadowStruct->lastX1 ) &&
shadows.c:	     ( W->rely == shadowStruct->lastY1 ) &&
shadows.c:	     ( W->relx + W->width  == shadowStruct->lastX2 ) &&
shadows.c:	     ( W->rely + W->height == shadowStruct->lastY2 )));
shadows.c:  shadowStruct->lastX1 = W->relx;
shadows.c:  shadowStruct->lastY1 = W->rely;
shadows.c:  shadowStruct->lastX2 = W->relx + W->width;
shadows.c:  shadowStruct->lastY2 = W->rely + W->height;
sibling.c:  parms->W = M;
sibling.c:  parms->id = id;
sibling.c:  parms->data = data;
sibling.c:  parms->mask = mask;
sibling.c:  parms->W = W;
sibling.c:  parms->id = id;
sibling.c:  parms->data = data;
sibling.c:  parms->mask = mask;
sibling.c:    switch (((struct pickstruct *)data)->button)
sibling.c:    case (JUSTDOWN): flag = parms->mask & 1;
sibling.c:    case (JUSTUP):   flag = parms->mask & 2;
sibling.c:    case (BEENDOWN): flag = parms->mask & 4;
sibling.c:    case (BEENUP):   flag = parms->mask & 8;
sibling.c:  if (flag) val = SendSiblingsMessage(parms->W, parms->id, parms->data);
sibling.c: P = W->parent;
sibling.c: L = P->port;
sibling.c: for (Current = L2->Front; Current != L2; Current = Current->Front)
sibling.c:     tempwin = Current->id;
sibling.c:  parms->W = M;
sibling.c:  parms->id = id;
sibling.c:  parms->data = data;
sibling.c:  parms->mask = mask;
sibling.c:  switch (((struct pickstruct *)data)->button)
sibling.c:    case (JUSTDOWN): flag = parms->mask & 1;
sibling.c:    case (JUSTUP):   flag = parms->mask & 2;
sibling.c:    case (BEENDOWN): flag = parms->mask & 4;
sibling.c:    case (BEENUP):   flag = parms->mask & 8;
sibling.c:  if (flag) val = SendChildrenMessage(parms->W, parms->id, parms->data);
sibling.c: L = W->port;
sibling.c:   return(-1);
sibling.c: for (Current = L2->Front; Current != L2; Current = Current->Front)
sibling.c:     tempwin = Current->id;
sibling.c: L = W->port;
sibling.c: for (Current = L2->Front; Current != L2; Current = Current->Front)
sibling.c:     tempwin = Current->id;
sibling.c:    while( W->parent)
sibling.c:      W = W->parent;
sibling.c:      if(W && W->tag)
sibling.c:	printf("%12s: W = \"%s\"\t ",name,W->tag);
sibling.c:      if(M && M->tag)
sibling.c:	printf("            : M = \"%s\"\t ",M->tag);
sibling.c:  if(W && W->tag)
sibling.c:    printf("W \"%s\" ",W->tag);
sibling.c:  M = parms->W;
sibling.c:  if(M && M->tag)
sibling.c:    printf("M \"%s\" ",M->tag);
sibling.c:  printf("id %5d ",parms->id);
sibling.c:  printf("data 0x%08x\n",parms->data);
slider.c:  params->orient = orient;
slider.c:  params->red = red;
slider.c:  params->green = green;
slider.c:  params->blue = blue;
slider.c:  params->shadow = shadow;
slider.c:  params->shadowred = shadowred;
slider.c:  params->shadowgreen = shadowgreen;
slider.c:  params->shadowblue = shadowblue;
slider.c:  params->barred = barred;
slider.c:  params->bargreen = bargreen;
slider.c:  params->barblue = barblue;
slider.c:  params->number = number;
slider.c:  params->max = max;
slider.c:  params->min = min;
slider.c:  params->kind = kind;
slider.c:  params->oldIntValue = 0;
slider.c:  params->oldFloatValue = 0.0;
slider.c:  screen = (W->display)->fildes;
slider.c:      cx1 = cstruct->x1;
slider.c:      cy1 = cstruct->y1;
slider.c:      cx2 = cstruct->x2;
slider.c:      cy2 = cstruct->y2;
slider.c:      cx1 = (float)W->x1;
slider.c:      cy1 = (float)W->y1;
slider.c:      cx2 = (float)W->x2;
slider.c:      cy2 = (float)W->y2;
slider.c:  shadow = params->shadow;
slider.c:  kind = params->kind;
slider.c:  if (kind) fnumber = (float *)params->number, fmax = (float *)params->max, fmin = (float *)params->min;
slider.c:  else number = (int *)params->number, max = (int *)params->max, min = (int *)params->min;
slider.c:  red = ((float)(params->red)/255.0);
slider.c:  green = ((float)(params->green)/255.0);
slider.c:  blue = ((float)(params->blue)/255.0);
slider.c:  red = ((float)(params->shadowred)/255.0);
slider.c:  green = ((float)(params->shadowgreen)/255.0);
slider.c:  blue = ((float)(params->shadowblue)/255.0);
slider.c:  x1 = W->x1; y1 = W->y1; x2 = W->x2; y2 = W->y2;
slider.c:  x2 -= (float)shadow; y2 -= (float)shadow;
slider.c:  red = ((float)(params->barred)/255.0);
slider.c:  green = ((float)(params->bargreen)/255.0);
slider.c:  blue = ((float)(params->barblue)/255.0);
slider.c:    ratio = (*fnumber-*fmin)/(*fmax-*fmin);
slider.c:  else ratio = ((float)*number - (float)*min)/((float)*max-(float)*min);
slider.c:  if (params->orient)
slider.c:      ratline = fy2-ratio*(fy2-fy1-3.0)-2.0;
slider.c:      ratline = fx1+ratio*(fx2-fx1-3.0)-2.0;
slider.c:  clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1), 
slider.c:		 0.0, (float)((W->display)->height-1));
slider.c:  make_picture_current((W->display)->fildes);
slider.c:  kind = params->kind;
slider.c:  if (kind) fnum = (float *)params->number, fmax = (float *)params->max, fmin = (float *)params->min;
slider.c:  else num = (int *)params->number, max = (int *)params->max, min = (int *)params->min;
slider.c:  x = pick->x;
slider.c:  y = pick->y;
slider.c:  dx = MAX(x, W->x1);
slider.c:  dy = MAX(y, W->y1);
slider.c:  dx = MIN(dx, W->x2);
slider.c:  dy = MIN(dy, W->y2);
slider.c:  button = pick->button;
slider.c:	      if (params->orient) /* for DYoung, so his sliders will work */
slider.c:		  ratio = (float)(W->y2-dy)/(float)(W->height-params->shadow-1);  
slider.c:		  ratio = (float)(dx-W->x1)/(float)(W->width-params->shadow-1);
slider.c:		  *fnum = *fmin+ratio*(*fmax-*fmin);
slider.c:		  *num = ((float)*min + ratio*((float)*max-(float)*min));
slider.c:	       * *DKY-24Jan91*
slider.c:		if( params->oldFloatValue != (float)(*fnum))
slider.c:		params->oldFloatValue = (float)(*fnum);
slider.c:		if( params->oldIntValue != (int)(*num))
slider.c:		params->oldIntValue = (int)(*num);
slider.c:      params->number = data;
slider.c:      params->red = *(colors);
slider.c:      params->green = *(colors+1);
slider.c:      params->blue = *(colors+2);
slider.c:  params->orient = orient;
slider.c:  params->shadow = shadow;
slider.c:  params->shadowred = shadowred;
slider.c:  params->shadowgreen = shadowgreen;
slider.c:  params->shadowblue = shadowblue;
slider.c:  params->barred = barred;
slider.c:  params->bargreen = bargreen;
slider.c:  params->barblue = barblue;
slider.c:  params->number = number;
slider.c:  params->max = max;
slider.c:  params->min = min;
slider.c:  params->kind = kind;
slider.c:  params->oldIntValue = 0;
slider.c:  params->oldFloatValue = 0.0;
slider.c:      UpdateWin( W->parent);
slider.c:	screen = (W->display)->fildes;
slider.c:	cx1 = cstruct->x1;
slider.c:	cy1 = cstruct->y1;
slider.c:	cx2 = cstruct->x2;
slider.c:	cy2 = cstruct->y2;
slider.c:	shadow = params->shadow;
slider.c:	kind = params->kind;
slider.c:	if (kind) fnumber = (float *)params->number, fmax = (float *)params->max, fmin = (float *)params->min;
slider.c:	else number = (int *)params->number, max = (int *)params->max, min = (int *)params->min;
slider.c:	red = ((float)(params->shadowred)/255.0);
slider.c:	green = ((float)(params->shadowgreen)/255.0);
slider.c:	blue = ((float)(params->shadowblue)/255.0);
slider.c:	x1 = W->x1; y1 = W->y1; x2 = W->x2; y2 = W->y2;
slider.c:	x2 -= (float)shadow; y2 -= (float)shadow;
slider.c:	red = ((float)(params->barred)/255.0);
slider.c:	green = ((float)(params->bargreen)/255.0);
slider.c:	blue = ((float)(params->barblue)/255.0);
slider.c:	  ratio = (*fnumber-*fmin)/(*fmax-*fmin);
slider.c:	else ratio = ((float)*number - (float)*min)/((float)*max-(float)*min);
slider.c:	if (params->orient)
slider.c:	    ratline = fy2-ratio*(fy2-fy1-3.0)-2.0;
slider.c:	    ratline = fx1+ratio*(fx2-fx1-3.0)-2.0;
slider.c:	clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1), 
slider.c:		       0.0, (float)((W->display)->height-1));
slider.c:	make_picture_current((W->display)->fildes);
slider.c:  kind = params->kind;
slider.c:  if (kind) fnum = (float *)params->number, fmax = (float *)params->max, fmin = (float *)params->min;
slider.c:  else num = (int *)params->number, max = (int *)params->max, min = (int *)params->min;
slider.c:      x = pick->x;
slider.c:      y = pick->y;
slider.c:      dx = MAX(x, W->x1);
slider.c:      dy = MAX(y, W->y1);
slider.c:      dx = MIN(dx, W->x2);
slider.c:      dy = MIN(dy, W->y2);
slider.c:      button = pick->button;
slider.c:	      if (params->orient)
slider.c:		  ratio = (float)(W->y2-dy)/(float)(W->height-params->shadow -1);
slider.c:		  ratio = (float)(dx-W->x1)/(float)(W->width-params->shadow -1);
slider.c:		  *fnum = *fmin+ratio*(*fmax-*fmin);
slider.c:		  *num = ((float)*min + ratio*((float)*max-(float)*min));
slider.c:	       * *DKY-24Jan91*
slider.c:		if( params->oldFloatValue != (float)(*fnum))
slider.c:		  UpdateWin( W->parent);
slider.c:		params->oldFloatValue = (float)(*fnum);
slider.c:		if( params->oldIntValue != (int)(*num))
slider.c:		  UpdateWin( W->parent);
slider.c:		params->oldIntValue = (int)(*num);
slider.c:    case (NEW_NUMBER):		/* *DKY-23Jan91* */
slider.c:      params->number = data;
slider.c:  params->orient = orient;
slider.c:  params->red = red;
slider.c:  params->green = green;
slider.c:  params->blue = blue;
slider.c:  params->shadow = shadow;
slider.c:  params->shadowred = shadowred;
slider.c:  params->shadowgreen = shadowgreen;
slider.c:  params->shadowblue = shadowblue;
slider.c:  params->barred = barred;
slider.c:  params->bargreen = bargreen;
slider.c:  params->barblue = barblue;
slider.c:  params->number = number;
slider.c:  params->max = max;
slider.c:  params->min = min;
slider.c:  params->kind = kind;
slider.c:  params->area = area;
slider.c:  screen = (W->display)->fildes;
slider.c:  cx1 = cstruct->x1;  cy1 = cstruct->y1;
slider.c:  cx2 = cstruct->x2;  cy2 = cstruct->y2;
slider.c:  shadow = params->shadow;
slider.c:  kind = params->kind;
slider.c:      fnumber = (float *)params->number;
slider.c:      fmax = (float *)params->max;
slider.c:      fmin = (float *)params->min;
slider.c:      farea = (float *)params->area;
slider.c:      number = (int *)params->number;
slider.c:      max = (int *)params->max;
slider.c:      min = (int *)params->min;
slider.c:      area = (int *)params->area;
slider.c:  red = ((float)(params->red)/255.0);
slider.c:  green = ((float)(params->green)/255.0);
slider.c:  blue = ((float)(params->blue)/255.0);
slider.c:  red = ((float)(params->shadowred)/255.0);
slider.c:  green = ((float)(params->shadowgreen)/255.0);
slider.c:  blue = ((float)(params->shadowblue)/255.0);
slider.c:  x2 -= (float)shadow; y2 -= (float)shadow;
slider.c:  red = ((float)(params->barred)/255.0);
slider.c:  green = ((float)(params->bargreen)/255.0);
slider.c:  blue = ((float)(params->barblue)/255.0);
slider.c:      if (!(*fmax-*fmin)) div = 1.0;
slider.c:      else div = *fmax-*fmin;
slider.c:      ratio = (*fnumber-*fmin)/div;
slider.c:      if (!(*max-*min)) div = 1.0;
slider.c:      else div = (float)(*max-*min);
slider.c:      ratio = ((float)*number - (float)*min)/div;
slider.c:  if (params->orient)
slider.c:      ratline = fy1+ratio*(fy2-fy1+1);
slider.c:      aratline = ratline+aratio*(fy2-fy1+1.0);
slider.c:      aratline = MIN(aratline, fy2-1.0);
slider.c:      aratline -= ratline;
slider.c:      ratline = fx1+ratio*(fx2-fx1+1.0);
slider.c:      aratline = ratline+aratio*(fx2-fx1+1.0);
slider.c:      aratline = MIN(aratline, fx2-1.0);
slider.c:      aratline -= ratline;
slider.c:  clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1), 
slider.c:		 0.0, (float)((W->display)->height-1));
slider.c:  make_picture_current((W->display)->fildes);
slider.c:  kind = params->kind;
slider.c:      fnum = (float *)params->number;
slider.c:      fmax = (float *)params->max;
slider.c:      fmin = (float *)params->min;
slider.c:      farea = (float *)params->area;
slider.c:      if (!(*fmax-*fmin)) div = 1.0;
slider.c:      else div = *fmax-*fmin;
slider.c:      ratio = (*fnum-*fmin)/div;
slider.c:      num = (int *)params->number;
slider.c:      max = (int *)params->max;
slider.c:      min = (int *)params->min;
slider.c:      area = (int *)params->area;
slider.c:      if (!(*max-*min)) div = 1.0;
slider.c:      else div = (float)(*max-*min);
slider.c:      ratio = (float)(*num - *min)/div;
slider.c:	x = pick->x;
slider.c:	y = pick->y;
slider.c:	dx = MAX(x, W->x1);
slider.c:	dy = MAX(y, W->y1);
slider.c:	dx = MIN(dx, W->x2);
slider.c:	dy = MIN(dy, W->y2);
slider.c:	button = pick->button;
slider.c:	      if (params->orient)
slider.c:		rat = (float)(dy-W->y1)/(float)(W->height-params->shadow);
slider.c:		rat = (float)(dx-W->x1)/(float)(W->width-params->shadow);
slider.c:		      newpos = 1.0-aratio;
slider.c:		      difx = (float)dx-(float)W->x1-newpos*(float)(W->width-params->shadow);
slider.c:		      dify = (float)dy-(float)W->y1-newpos*(float)(W->height-params->shadow);
slider.c:		difx = (float)dx-(float)W->x1-newpos*(float)(W->width-params->shadow);
slider.c:		dify = (float)dy-(float)W->y1-newpos*(float)(W->height-params->shadow);
slider.c:		  *fnum = *fmin+newpos*(*fmax-*fmin);
slider.c:		  *num = (int)(((float)*min + newpos*((float)*max-(float)*min))+.5);
slider.c:	      dx -= difx;
slider.c:	      dy -= dify;
slider.c:	      if (params->orient)
slider.c:		rat = (float)(dy-W->y1)/(float)(W->height-params->shadow);
slider.c:		rat = (float)(dx-W->x1)/(float)(W->width-params->shadow);
slider.c:		      newpos = 1.0-aratio;
slider.c:		  *fnum = *fmin+newpos*(*fmax-*fmin);
slider.c:		  *num = (int)(((float)*min + newpos*((float)*max-(float)*min))+.5);
slider.c:	       * *DKY-24Jan91*
slider.c:		if( params->oldFloatValue != (float)(*fnum))
slider.c:		params->oldFloatValue = (float)(*fnum);
slider.c:		if( params->oldIntValue != (int)(*num))
slider.c:		params->oldIntValue = (int)(*num);
slider.c:    case NEWCOLOR:		/* *DKY- 2Nov90* */
slider.c:	params->red = *(colors);
slider.c:	params->green = *(colors+1);
slider.c:	params->blue = *(colors+2);
slider.c:    case NEWBARCOLOR:		/* *DKY- 2Nov90* */
slider.c:	params->barred = *(colors);
slider.c:	params->bargreen = *(colors+1);
slider.c:	params->barblue = *(colors+2);
slider.c:    case SET_SHADOW:		/* *DKY- 2Nov90* */
slider.c:      params->shadow = (int)data;
slider.c:    case NEW_NUMBER:		/* BS - 1/23/91 */
slider.c:      params->number = data;
slider.c: *           indent -- which is the number of pixels to indent the bar.
slider.c: *           barborder(red,green,blue) -- the color of the bar's border.
slider.c: * *DKY-24Jul90*
slider.c:  params->orient = orient;
slider.c:  params->red = red;
slider.c:  params->green = green;
slider.c:  params->blue = blue;
slider.c:  params->shadow = shadow;
slider.c:  params->shadowred = shadowred;
slider.c:  params->shadowgreen = shadowgreen;
slider.c:  params->shadowblue = shadowblue;
slider.c:  params->barred = barred;
slider.c:  params->bargreen = bargreen;
slider.c:  params->barblue = barblue;
slider.c:  params->barborderred = barborderred;
slider.c:  params->barbordergreen = barbordergreen;
slider.c:  params->barborderblue = barborderblue;
slider.c:  params->number = number;
slider.c:  params->max = max;
slider.c:  params->min = min;
slider.c:  params->kind = kind;
slider.c:  params->area = area;
slider.c:  params->indent = indent;
slider.c:  params->oldIntValue = 0;
slider.c:  params->oldFloatValue = 0.0;
slider.c:  screen = (W->display)->fildes;
slider.c:	params->barred = (colors[0]);
slider.c:	params->bargreen = (colors[1]);
slider.c:	params->barblue = (colors[2]);
slider.c:	params->barborderred = (colors[0]);
slider.c:	params->barbordergreen = (colors[1]);
slider.c:	params->barborderblue = (colors[2]);
slider.c:	params->barborderred = (colors[0]);
slider.c:	params->barbordergreen = (colors[1]);
slider.c:	params->barborderblue = (colors[2]);
slider.c:	params->barred = (colors[0]);
slider.c:	params->bargreen = (colors[1]);
slider.c:	params->barblue = (colors[2]);
slider.c:	cx1 = cstruct->x1;  cy1 = cstruct->y1;
slider.c:	cx2 = cstruct->x2;  cy2 = cstruct->y2;
slider.c:	shadow = params->shadow;
slider.c:	kind = params->kind;
slider.c:	indent = params->indent;
slider.c:	    fnumber = (float *)params->number;
slider.c:	    fmax = (float *)params->max;
slider.c:	    fmin = (float *)params->min;
slider.c:	    farea = (float *)params->area;
slider.c:	    number = (int *)params->number;
slider.c:	    max = (int *)params->max;
slider.c:	    min = (int *)params->min;
slider.c:	    area = (int *)params->area;
slider.c:	red = ((float)(params->red)/255.0);
slider.c:	green = ((float)(params->green)/255.0);
slider.c:	blue = ((float)(params->blue)/255.0);
slider.c:	red = ((float)(params->shadowred)/255.0);
slider.c:	green = ((float)(params->shadowgreen)/255.0);
slider.c:	blue = ((float)(params->shadowblue)/255.0);
slider.c:	x2 -= (float)shadow; y2 -= (float)shadow;
slider.c:	red = ((float)(params->barred)/255.0);
slider.c:	green = ((float)(params->bargreen)/255.0);
slider.c:	blue = ((float)(params->barblue)/255.0);
slider.c:	/* *DKY-24Jul90-01:33* */
slider.c:	red = ((float)(params->barborderred)/255.0);
slider.c:	green = ((float)(params->barbordergreen)/255.0);
slider.c:	blue = ((float)(params->barborderblue)/255.0);
slider.c:	    if (!(*fmax-*fmin)) div = 1.0;
slider.c:	    else div = *fmax-*fmin;
slider.c:	    ratio = (*fnumber-*fmin)/div;
slider.c:	    if (!(*max-*min)) div = 1.0;
slider.c:	    else div = (float)(*max-*min);
slider.c:	    ratio = ((float)*number - (float)*min)/div;
slider.c:	if (params->orient)
slider.c:	    ratline = fy1+ratio*(fy2-fy1+1);
slider.c:	    aratline = ratline+aratio*(fy2-fy1+1.0);
slider.c:	    aratline = MIN(aratline, fy2-1.0);
slider.c:	    aratline -= ratline;
slider.c:	    rectangle(screen, fx1 + indent, ratline + 1, fx2 - indent, ratline+aratline);
slider.c:	    ratline = fx1+ratio*(fx2-fx1+1.0);
slider.c:	    aratline = ratline+aratio*(fx2-fx1+1.0);
slider.c:	    aratline = MIN(aratline, fx2-1.0);
slider.c:	    aratline -= ratline;
slider.c:	    rectangle(screen, ratline + 1, fy1 + indent, ratline+aratline, fy2 - indent);
slider.c:	clip_rectangle((W->display)->fildes, (float)0.0, (float)((W->display)->width-1), 
slider.c:		       0.0, (float)((W->display)->height-1));
slider.c:	make_picture_current((W->display)->fildes);
slider.c:  kind = params->kind;
slider.c:      fnum = (float *)params->number;
slider.c:      fmax = (float *)params->max;
slider.c:      fmin = (float *)params->min;
slider.c:      farea = (float *)params->area;
slider.c:      if (!(*fmax-*fmin)) div = 1.0;
slider.c:      else div = *fmax-*fmin;
slider.c:      ratio = (*fnum-*fmin)/div;
slider.c:      num = (int *)params->number;
slider.c:      max = (int *)params->max;
slider.c:      min = (int *)params->min;
slider.c:      area = (int *)params->area;
slider.c:      if (!(*max-*min)) div = 1.0;
slider.c:      else div = (float)(*max-*min);
slider.c:      ratio = (float)(*num - *min)/div;
slider.c:      x = pick->x;
slider.c:      y = pick->y;
slider.c:      dx = MAX(x, W->x1);
slider.c:      dy = MAX(y, W->y1);
slider.c:      dx = MIN(dx, W->x2);
slider.c:      dy = MIN(dy, W->y2);
slider.c:      button = pick->button;
slider.c:	    if (params->orient)
slider.c:	      rat = (float)(dy-W->y1)/(float)(W->height-params->shadow);
slider.c:	      rat = (float)(dx-W->x1)/(float)(W->width-params->shadow);
slider.c:		    newpos = 1.0-aratio;
slider.c:		    difx = (float)dx-(float)W->x1-newpos*(float)(W->width-params->shadow);
slider.c:		    dify = (float)dy-(float)W->y1-newpos*(float)(W->height-params->shadow);
slider.c:	      difx = (float)dx-(float)W->x1-newpos*(float)(W->width-params->shadow);
slider.c:	      dify = (float)dy-(float)W->y1-newpos*(float)(W->height-params->shadow);
slider.c:		*fnum = *fmin+newpos*(*fmax-*fmin);
slider.c:		*num = (int)(((float)*min + newpos*((float)*max-(float)*min))+.5);
slider.c:	       dx -= difx;
slider.c:	       dy -= dify;
slider.c:	       if (params->orient)
slider.c:		 rat = (float)(dy-W->y1)/(float)(W->height-params->shadow);
slider.c:		 rat = (float)(dx-W->x1)/(float)(W->width-params->shadow);
slider.c:		       newpos = 1.0-aratio;
slider.c:		   *fnum = *fmin+newpos*(*fmax-*fmin);
slider.c:		   *num = (int)(((float)*min + newpos*((float)*max-(float)*min))+.5);
slider.c:		* *DKY-24Jan91*
slider.c:		 if( params->oldFloatValue != (float)(*fnum))
slider.c:		 params->oldFloatValue = (float)(*fnum);
slider.c:		 if( params->oldIntValue != (int)(*num))
slider.c:		 params->oldIntValue = (int)(*num);
soundify.c:/*           -Dave "IO" Small 5/18/89          */
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:/*  data (range: 0 - 127).  The note is also an int. Middle C is 60,  */
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:  fd->track = track;
soundify.c:  track  = params->track;
soundify.c:    maxx = Root1->width;
soundify.c:    winx = W->x1;
soundify.c:  fd->track = track;
soundify.c:  track  = params->track;
soundify.c:    button = pick->button;
soundify.c:	if ((((W->mask)->Behind)->id) == W)
soundify.c:	for( Temp = (W->mask)->Front;
soundify.c:	    ( (Temp->id != W) && (Temp != W->mask) ); Temp = Temp->Front, above++);
soundify.c:    while (W->parent != NULL);
soundify.c:  fd->note = note;
soundify.c:  fd->channel = channel - 1;
soundify.c:  fd->velocity = velocity;
soundify.c:  fd->keystat = KEYUP;
soundify.c:    button = pick->button;
soundify.c:      AkaiNoteOn(params->channel, params->note, params->velocity);
soundify.c:      AkaiNoteOff(params->channel, params->note, params->velocity);
soundify.c:    AkaiPitchbend(params->channel, params->note, params->velocity);
soundify.c:    AkaiNoteOn(params->channel, params->note, params->velocity);
soundify.c:    params->keystat = KEYDOWN;
soundify.c:    AkaiNoteOff(params->channel, params->note, params->velocity);
soundify.c:    params->keystat = KEYUP;
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:/* indicator light -> it blinks red whenever there is a midi signal.  */
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:  W = (struct Window *)MakeWindow(Parent->display, Parent->input, Parent, 
soundify.c:  fd->note = note;
soundify.c:  fd->channel = channel - 1;
soundify.c:  fd->velocity = velocity;
soundify.c:  fd->keystat = KEYUP;
soundify.c:    button = pick->button;
soundify.c:    params->keystat = KEYDOWN;
soundify.c:    params->keystat = KEYUP;
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:  fd->note = note;
soundify.c:  fd->channel = channel;
soundify.c:  fd->keystat = KEYUP;
soundify.c:  keystat = params->keystat;
soundify.c:    button = pick->button;
soundify.c:    button = pick->button;
soundify.c:    midi.note = params->note;
soundify.c:    midi.channel = *(params->channel) - 1;
soundify.c:    params->keystat = KEYDOWN;
soundify.c:    midi.note = params->note;
soundify.c:    midi.channel = *(params->channel) - 1;
soundify.c:    params->keystat = KEYUP;
soundify.c:  screen = W->display->fildes;
soundify.c:    cx1 = cstruct->x1;
soundify.c:    cy1 = cstruct->y1;
soundify.c:    cx2 = cstruct->x2;
soundify.c:    cy2 = cstruct->y2;
soundify.c:    rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
soundify.c:    rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
soundify.c:    rectangle(screen, (float)W->x1, (float)W->y1, (float)W->x2, (float)W->y2);
soundify.c:    button = pick->button;
soundify.c:    byte = (unsigned char) (0xe0 + Note->channel);
soundify.c:    byte = (unsigned char) Note->velocity;
soundify.c:    byte = 0x90 + Note->channel;
soundify.c:    byte = Note->note;
soundify.c:    byte = Note->velocity;
soundify.c:    byte = 0x80 + Note->channel;
soundify.c:    byte = Note->note;
soundify.c:    byte = Note->velocity;
soundify.c:    if ((CurrentMidiWindow)&&(c != -1)) {
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:/*--------------------------------------------------------------------*/
soundify.c:   display = Root->display;
soundify.c:   locator = Root->input;
soundify.c:   label = (struct Window *)MakeWindow(Root->display,Root->input,Keyboard, 10,25,100,18,"label");
soundify.c:   channel = (struct Window *)MakeWindow(Root->display,Root->input,Keyboard, 345,25,185,18,"channel");
soundify.c:   Maker(DragBar, 5, 5, -25, 20);
soundify.c:   StringWin(CloserWin, "X", 2, -2, "arch", 24, 8, 0, 0, 0, 0);
soundify.c:   Maker(CloserWin, -20, 5, -5, 20);
soundify.c:   Maker(SizerWin, -20, -20, -5, -5);
stepper.c:/*** standard parameters.  Does NOT set the functions for stepper->pad, just the size ***/
stepper.c:  upstep_icon->rule = redclear;
stepper.c:  LoadBitMap8to24("icons/upstep_icon", &upstep_icon->dx, &upstep_icon->dy, &upstep_icon->source, 125, redclear);
stepper.c:  downstep_icon->rule = redclear;
stepper.c:  LoadBitMap8to24("icons/downstep_icon", &downstep_icon->dx, &downstep_icon->dy, &downstep_icon->source, 125, redclear);
stepper.c:      pad = MakeWindow(display, locator, Stepper, 0, 0, width-20, padheight, "pad");
stepper.c:      Maker(pad, 0, 0, -24, 0);
stepper.c:      s->pad = pad;
stepper.c:      pad = MakeWindow(display, locator, Stepper, 0, 0, width, padheight-20, "pad");
stepper.c:      Maker(pad, 0, 0, 0, -24);
stepper.c:      s->pad = pad;
stepper.c:  SwapColors(upstep_icon->source, upstep_icon->dx, upstep_icon->dy, VLIGHT, VLIGHT, VLIGHT, s1, s2, s3);
stepper.c:  SwapColors(upstep_icon->source, upstep_icon->dx, upstep_icon->dy, FULL, FULL, FULL, h1, h2, h3);
stepper.c:  SwapColors(downstep_icon->source, downstep_icon->dx, downstep_icon->dy, VLIGHT, VLIGHT, VLIGHT, s1, s2, s3);
stepper.c:  SwapColors(downstep_icon->source, downstep_icon->dx, downstep_icon->dy, FULL, FULL, FULL, h1, h2, h3);
stepper.c:      Up = MakeWindow(display, locator, Stepper, width-20, 0, 20, 20, "slider");
stepper.c:      Maker(Up, -19, 0, 0, 19);
stepper.c:      Up = MakeWindow(display, locator, Stepper, 0, height-20, 20, 20, "slider");
stepper.c:      Maker(Up, 0, -19, 19, 0);
stepper.c:  Down = MakeWindow(display, locator, Stepper, width-20, height-20, 20, 20, "slider");
stepper.c:  Maker(Down, -19, -19, 0, 0);
stepper.c:      slider = MakeWindow(display, locator, Stepper, 20, height-20, 20, height-40, "slider");
stepper.c:      Maker(slider, -19, 20, 0, -20);
stepper.c:      AreaSlider(slider, 1, b1, b2, b3, 0, 0, 0, 0, s1, s2, s3, 0, &s->line, &s->max, &s->min, &s->area);
stepper.c:      slider = MakeWindow(display, locator, Stepper, width-20, 20, width-40, 20, "slider");
stepper.c:      Maker(slider, 20, -19, -20, 0);
stepper.c:      AreaSlider(slider, 0, b1, b2, b3, 0, 0, 0, 0, s1, s2, s3, 0, &s->line, &s->max, &s->min, &s->area);
stepper.c:  s->slider = slider;
stepper.c:  params->line = 0;
stepper.c:  params->area =0;
stepper.c:  params->min = 0;
stepper.c:  params->max = 0;
stepper.c:  params->slider = NULL;
stepper.c:  params->pad = NULL;
stepper.c:      if (step->line)
stepper.c:	  step->line -= step->area;
stepper.c:	  step->line = MAX(step->min, step->line);
stepper.c:	  UpdateWin(step->slider);
stepper.c:	  UpdateWin(step->pad);
stepper.c:      if ((step->line + step->area) <= (step->max - step->min))
stepper.c:	  step->line += step->area;
stepper.c:	  step->line = MIN(step->max, step->line);
stepper.c:	  UpdateWin(step->slider);
stepper.c:	  UpdateWin(step->pad);
subext.c:/*** subext.c - dead@media-lab.media.mit.edu - 04/03/85 ***/
subext.c:       --el > -1 && --fl > -1 && fname[fl] == ext[el]; )
subext.c:  if (el == -1)
ttyutil.c:*	int	cc;         * 0, we hope; -1 on error
ttyutil.c:* 	int	cc;         * actual read count, -1 for error 
ttyutil.c:*	int	timeout;    * secs to wait before quiting, -1 for indefinite, 0 polls
ttyutil.c:* 	int	cc;         * actual read count, -1 for error 
ttyutil.c:* 	int	cc;         * actual write count, -1 for error 
ttyutil.c:* 	int	cc;     * 0 for successful operation, -1 for error 
ttyutil.c:* 	int	cc;     * number of chars discarded, -1 for error 
ttyutil.c:	*	Open for non-blocking read
ttyutil.c:		return(-1);
ttyutil.c:	if (ioctl(fd, TCGETA, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:	if (ioctl(fd, TCSETA, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:		return(-1);
ttyutil.c:ttyutil_break()	-- send break.  NB: HPUX ignores "duration"
ttyutil.c:	if (ioctl(fd, TCSBRK, 0) == -1)	
ttyutil.c:		return(-1);
ttyutil.c:	if (ioctl(fd, TCGETA, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:	if (ioctl(fd, TCGETA, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:		if (ioctl(fd, TCSETA, &tio) == -1)
ttyutil.c:			return(-1);
ttyutil.c:    if (ioctl (fd,FIONREAD,&i)==-1)
ttyutil.c:	else if (num != -1)
ttyutil.c:  if (Timeout == 1) return (-2);
ttyutil.c:  if (num == -1)
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:		return(-1);
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:	if (ttyutil_set_min_and_time(fd, 0, 0) == -1)
ttyutil.c:		return(-1);
ttyutil.c:		return(-1);
ttyutil.c:		{	for (i=0; i<num-1; i++)
ttyutil.c:			printf("[0x%x].\n", (byte)buf[num-1]);
ttyutil.c:int timeoutval;			/* In millisecs, 0 for poll, -1 for indefinite */
ttyutil.c:	if (ttyutil_set_min_and_time(fd, 0, 0) == -1)
ttyutil.c:		return(-1);
ttyutil.c:	if (timeoutval == -1) toptr = NULL;
ttyutil.c:		return(-1);
ttyutil.c:			return(-1);
ttyutil.c:	if (num == 0) num = -2;
ttyutil.c:		if (num == -2) printf ("ttyutil_nread: TIMEOUT\n");
ttyutil.c:		{	for (i=0, buf = buf_save; i<num-1; i++, buf++)
ttyutil.c:ttyutil_write() -- Write buf to tty
ttyutil.c:		for (i=0; i<writenum-1; i++)
ttyutil.c:			printf("[0x%x].\n", (byte)buf[writenum-1]);
ttyutil.c:			return (-1);
ttyutil.c:				return (-1);
ttyutil.c:ttyutil_drain() -- Drain output buffer
ttyutil.c:	if (ioctl(fd, TCGETA, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:	if (ioctl(fd, TCSETAW, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:ttyutil_clear() -- Clear input and output buffers
ttyutil.c:ttyutil_set_min_and_time() -- Set timeout for read.
ttyutil.c:	if (ioctl(fd, TCGETA, &tio) == -1)
ttyutil.c:		return(-1);
ttyutil.c:		if (ioctl(fd, TCSETA, &tio) == -1)
ttyutil.c:			return(-1);
twoscreen.c:	  printf("Cannot find second renaissance screen. Looking for a 4-plane wimp screen.\n");
twoscreen.c:  L = R->port;
twoscreen.c:  for (Cur = L2->Front; Cur != L2; Cur = Cur->Front)
twoscreen.c:      C = Cur->id;
twoscreen.c:      C->display = R2->display;
twoscreen.c:      C->parent = R2;
twoscreen.c:    if (Output2->bits == 4)
twoscreen.c:	gclose(Output2->fildes);
twoscreen.c:	Output2->fildes = gopen("/dev/crt", OUTDEV, NULL, INIT);
twoscreen.c:	gclose(Output2->fildes);
twoscreen.c:      if (Output2->bits == 4)
twoscreen.c:	  gclose(Output2->fildes);
twoscreen.c:	  Output2->fildes = gopen("/dev/crt", OUTDEV, NULL, INIT);
twoscreen.c:	  gclose(Output2->fildes);
twoscreen.c:      else if (Output2->bits == 24)
twoscreen.c:	  gclose(Output2->fildes);
twoscreen.c:	  Output2->fildes = gopen("/dev/crtren2", OUTDEV, NULL, INIT);
twoscreen.c:	  gclose(Output2->fildes);
twoscreen.c:  if (Output1->bits == 24)
twoscreen.c:      gclose(Output1->fildes);
twoscreen.c:      Output1->fildes = gopen("/dev/crtren", OUTDEV, NULL, INIT);
twoscreen.c:      gclose(Output1->fildes);
twoscreen.c:  if ((!O)||(O->bits != 4)) return;
twoscreen.c:  define_color_table(O->fildes, 8, 8, clist);
twoscreen.c:  if (O1->bits >= 24)
twoscreen.c:      if (O2->bits >= 24)
twoscreen.c:      else if (O2->bits == 4)
twoscreen.c:  if (p->character == ' ')
twoscreen.c:      if(Root1->display == Root2->display) {  /* <---------------------------this should let you do spacebar switching */
twoscreen.c:	                                                                  /* (4/16/91) --Tim */
twoscreen.c:	EchoOff(screen_toggle->display,FALSE);
twoscreen.c:	EchoOn(123456,0, screen_toggle->display);
twoscreen.c:      if (*a > Output2->viswidth)
twoscreen.c:	  *a -= Output2->viswidth;
twoscreen.c:      else if ((screen == Output2) && (!side)) *a = screen->viswidth;
twoscreen.c:   if ((Root2)&&((!bits)||(Output2->bits >= 24))&&(!screen_toggle))
twoscreen.c:  x = pick->x;
twoscreen.c:  y = pick->y;
twoscreen.c:  dx = x-W->x1;
twoscreen.c:  dy = y-W->y1;
twoscreen.c:  if (pick->button == JUSTDOWN)
twoscreen.c:      pick->x = W->x1+dx;
twoscreen.c:      pick->y = W->y1+dy;
twoscreen.c:  dx = *x - W->x1;
twoscreen.c:  dy = *y - W->y1;
twoscreen.c:  width = W->width;
twoscreen.c:  height = W->height;
twoscreen.c:  display1 = (Root1->display)->fildes;
twoscreen.c:  display2 = (Root2->display)->fildes;
twoscreen.c:  locator = (W->input)->fildes;
twoscreen.c:  if ((Root1->display) == W->display) *x = *x +Root2->width;
twoscreen.c:  clip_rectangle(display1, 0.0, (float)Root1->width, 0.0, (float)Root1->height);
twoscreen.c:  clip_rectangle(display2, 0.0, (float)Root2->width, 0.0, (float)Root2->height);
twoscreen.c:  xs = *x-dx; ys = *y-dy; xe = *x-dx+width-1; ye = *y-dy+height-1;
twoscreen.c:  if (xs < Root2->width) {
twoscreen.c:    make_picture_current(display1); /* *DKY-23Sep90* */
twoscreen.c:    make_picture_current(display2); /* *DKY-23Sep90* */
twoscreen.c:  if (xe >= Root2->width) {
twoscreen.c:    rectangle(display1, (float)(xs-Root2->width), (float)ys, (float)(xe-Root2->width), (float)ye);
twoscreen.c:    make_picture_current(display1); /* *DKY-23Sep90* */
twoscreen.c:    make_picture_current(display2); /* *DKY-23Sep90* */
twoscreen.c:      *x -= dx;
twoscreen.c:      *y -= dy;
twoscreen.c:      if (*x+width-1> Root2->width+Root1->width-1) *x = (Root2->width+Root1->width-1)-width;
twoscreen.c:      if (*y+height-1> Root1->height-1) *y = (Root1->height-1)-height;
twoscreen.c:      if ((*x != xs)||(*y != ys)||(*x+width-1 != xe)||(*y+height-1 != ye))
twoscreen.c:	  if (xs < Root2->width) {
twoscreen.c:	    make_picture_current(display1); /* *DKY-23Sep90* */
twoscreen.c:	    make_picture_current(display2); /* *DKY-23Sep90* */
twoscreen.c:	  if (xe >= Root2->width) {
twoscreen.c:	    rectangle(display1, (float)(xs-Root2->width), (float)ys, (float)(xe-Root2->width), (float)ye);
twoscreen.c:	    make_picture_current(display1); /* *DKY-23Sep90* */
twoscreen.c:	    make_picture_current(display2); /* *DKY-23Sep90* */
twoscreen.c:	  xs = *x; ys = *y; xe = *x+width-1; ye = *y+height-1;
twoscreen.c:	  if (xs < Root2->width) {
twoscreen.c:	    make_picture_current(display1); /* *DKY-23Sep90* */
twoscreen.c:	    make_picture_current(display2); /* *DKY-23Sep90* */
twoscreen.c:	  if (xe >= Root2->width) 
twoscreen.c:	    rectangle(display1, (float)(xs-Root2->width), (float)ys, (float)(xe-Root2->width), (float)ye);
twoscreen.c:  if ((*x <Root2->width) && (xe > Root2->width))
twoscreen.c:      if (Root2->width - *x > xe-Root2->width) ddx = -10;
twoscreen.c:      while ((*x <Root2->width) && (xe >= Root2->width))
twoscreen.c:	  rectangle(display1, (float)(*x-Root2->width), (float)*y, (float)(xe-Root2->width), (float)ye);
twoscreen.c:	  xe = *x+width-1; ye = *y+height-1;
twoscreen.c:	  rectangle(display1, (float)(*x-Root2->width), (float)*y, (float)(xe-Root2->width), (float)ye);
twoscreen.c:  rectangle(display1, (float)(*x-Root2->width), (float)*y, (float)(xe-Root2->width), (float)ye);
twoscreen.c:  if ((*x < Root2->width)&&(*y+height > Root2->height)) *y = Root2->height-height;
twoscreen.c:  if (*x < Root2->width) W->parent = Root2, W->display = Root2->display;
twoscreen.c:  else W->parent = Root1, *x -= Root2->width, W->display = Root1->display;
twoscreen.c:  clip_rectangle(display1, 0.0, (float)Root1->display->width, 0.0, (float)Root1->display->height);
twoscreen.c:  clip_rectangle(display2, 0.0, (float)Root2->display->width, 0.0, (float)Root2->display->height);
twoscreen.c:  L = W->port;
twoscreen.c:  for (C = L->Front; C != L; C = C->Front)
twoscreen.c:      C->id->display = W->display;
twoscreen.c:      ChangeDisplay(C->id);
upc.c:  UPC = (struct Window *)MakeWindow(parent->display, parent->input, parent,
upc.c:  SizerWin = (struct Window *)MakeWindow(parent->display,parent->input,
upc.c:  Maker(SizerWin, -20, -20, -1, -1);
upc.c:  fd->firstfive = firstfive;
upc.c:  fd->secondfive = secondfive;
upc.c:  fd->r = r;
upc.c:  fd->g = g;
upc.c:  fd->b = b;
upc.c:  screen = (W->display)->fildes;
upc.c:    cx1 = cstruct->x1;  cy1 = cstruct->y1;
upc.c:    cx2 = cstruct->x2;  cy2 = cstruct->y2;
upc.c:    make_picture_current(W->display->fildes);
upc.c:    W->display->control [3] = 4;
upc.c:    W->display->control [0x40bf] = 7;
upc.c:    W->display->control [0x40ef] = 0x33;
upc.c:    drawing_mode(W->display->fildes, 3);
upc.c:    aa_set_clip (cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
upc.c:    aa_set_fb((W->display)->bits, (W->display)->buffer, (W->display)->control);
upc.c:    aa_set_color(params->r, params->g, params->b);
upc.c:    set_monitor(W->display->bits, W->display->fildes);
upc.c:    set_font_color(params->r, params->g, params->b, 0);
upc.c:    set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
upc.c:    sprintf(string, "%d%d", params->firstfive, params->secondfive);
upc.c:    space = W->width / 18;
upc.c:		       (int) (W->x1 + space*i), W->y2 - small_size);
upc.c:		       (int) (W->x1 + space*i), W->y2 - small_size);
upc.c:	draw_num(W->x1 + space*i, (float)W->y1 + space*0.5, 
upc.c:		 W->x1 + space*i + space*0.8, 
upc.c:		 (float)W->y2 - font_size*0.5, number);
upc.c:	draw_num(W->x1 + space*i, (float)W->y1 + space*0.5,
upc.c:		 W->x1 + space*i + space*0.8, 
upc.c:		 (float)W->y2 - font_size, number);
upc.c:		       (int) (W->x1 + space*i), W->y2 - font_size);
upc.c:    aa_move(x1 + 0.5*(x2-x1), y1, (x2-x1));
upc.c:    aa_draw(x1 + 0.5*(x2-x1), y2, (x2-x1));
upc.c:  wd = x2 - x1;
video.c:  if (!(val = LoadSuguruFrameBitMap(fname, &(icon->dx), &(icon->dy), &(icon->source)))) {
video.c:    icon->rule = redclear;
video.c:    icon->hotdx = 0;
video.c:    icon->hotdy = 0;
video.c:  /* Load in a video file of the format "width height numframesCR" --> banks */
video.c:  fscanf(fp, "%d %d %d\n", &(vid->width), &(vid->height), &(vid->numframes));
video.c:  printf("\nLoading %s, size %d x %d, numframes %d.",filename,vid->width,vid->height,vid->numframes);
video.c:  if ((vid->frames = (unsigned char **)malloc((vid->numframes)*(sizeof(unsigned char *)))) == NULL)
video.c:  size = vid->width*vid->height*3;
video.c:  for (i = 0; i < vid->numframes; i++) {
video.c:    if ((*((vid->frames)+i) = (unsigned char *)malloc(size * (sizeof(unsigned char)))) == NULL)
video.c:    fread(*(vid->frames+i), sizeof(unsigned char), size, fp);
video.c:  vid->current_frame = 0;
video.c:     int display, x, y, playframes;  /* <-- number of frames to play */
video.c:  width = vid->width;  height = vid->height;
video.c:    data = *(vid->frames+vid->current_frame);
video.c:    if (vid->current_frame < ((vid->numframes)-1)) vid->current_frame++;
video.c:    else vid->current_frame = 0;
wacom.c:/*      Wacom super digitizer SD-210.          */
wacom.c:/*           -Dave "IO" Small 10/30/88         */
wacom.c:  if ((Tablet = ttyutil_open(dev)) == -1)
wacom.c:    return (-1);
wacom.c:    numread += read(fildes, &data[numread], 7 - numread), count++;
wacom.c:      if (sign) A -= 127;
wacom.c:    /*** Check to see if the location jumped - I think that this is
wacom.c:    else if (((last_x - *x) > 50.0) ||
wacom.c:	     ((last_y - *y) > 50.0) ||
wacom.c:	     ((last_x - *x) < -50.0) ||
wacom.c:	     ((last_y - *y) < -50.0)) {
wacom.c:  /*** Timed out read on RS-232, return last good point ***/
windowtools.c:struct Window *Inhibitdraw = NULL;     /* Tim, 4-16-91, so that I can do two roots on the same display */
windowtools.c:DrawOnly(root)			/* Tim, 4-16-91, so that I can do two roots on the same display */
windowtools.c:  if( Inhibitdraw && ((id == DRAW) || (id == UPDATE)) && (FindRoot(W)==Inhibitdraw)) /* Tim,  4-16-91, see above*/
windowtools.c:  C = W->commands;
windowtools.c:  while ((C)&&(C->id != id) && (C->id != DEFAULT)) C = C->next;
windowtools.c:  if (C) for (count = 0; (count < C->numfuncs)&&(val != STOP); count++)
windowtools.c:    val |= (**(C->functions+count))(W, id, data, *(C->arguments+count));
windowtools.c:  C = W->commands;
windowtools.c:    while ((C->next)&&(C->id != id)) C = C->next;
windowtools.c:    if (C->id != id) {
windowtools.c:      C->next = (struct Command *)malloc(sizeof(struct Command));
windowtools.c:      C = C->next;
windowtools.c:      C->numfuncs = 0;
windowtools.c:      C->next = NULL;
windowtools.c:    C = W->commands = (struct Command *)malloc(sizeof(struct Command));
windowtools.c:    C->numfuncs = 0;
windowtools.c:    C->next = NULL;
windowtools.c:  C->id = id;
windowtools.c:  C->numfuncs++;
windowtools.c:  functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
windowtools.c:  args = (char **)malloc(C->numfuncs*sizeof(char *));
windowtools.c:  for (i = 0; i < C->numfuncs-1; i++)
windowtools.c:      *(functions+i) = *(C->functions+i);
windowtools.c:      *(args+i) = *(C->arguments+i);
windowtools.c:  *(functions+C->numfuncs-1) = function;
windowtools.c:  *(args+C->numfuncs-1) = argument;
windowtools.c:  if (C->numfuncs >1) { free(C->functions);   free(C->arguments);}
windowtools.c:  C->functions = functions;
windowtools.c:  C->arguments = args;
windowtools.c:  C = W->commands;
windowtools.c:    while ((C->next)&&(C->id != id)) prev = C, C = C->next;
windowtools.c:    if (C->id == id)
windowtools.c:	while ((t < C->numfuncs)&&(!done))
windowtools.c:	    if (*(C->functions+t) == function) done = 1;
windowtools.c:	    C->numfuncs--;
windowtools.c:	    if (C->numfuncs) {
windowtools.c:	      functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
windowtools.c:	      args = (char **)malloc(C->numfuncs*sizeof(char *));
windowtools.c:	      for (i = 0; i < C->numfuncs+1; i++)
windowtools.c:		    *(functions+n) = *(C->functions+i);
windowtools.c:		    *(args+n) = *(C->arguments+i);
windowtools.c:	      free(C->functions);
windowtools.c:	      free(C->arguments);
windowtools.c:	      C->functions = functions;
windowtools.c:	      C->arguments = args;
windowtools.c:	      if (!prev) W->commands = C->next;
windowtools.c:	      else prev->next = C->next;
windowtools.c:	      free(C->functions);
windowtools.c:	      free(C->arguments);
windowtools.c:  return (-1);
windowtools.c:  C = W->commands;
windowtools.c:    while ((C->next)&&(C->id != id)) C = C->next;
windowtools.c:    if (C->id != id) return(0);
windowtools.c:    C->numfuncs++;
windowtools.c:    functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
windowtools.c:    args = (char **)malloc(C->numfuncs*sizeof(char *));
windowtools.c:    for (i = 0; i < C->numfuncs; i++)
windowtools.c:	if ((*(C->functions+i) == function)&&(*(C->arguments+i) == argument))
windowtools.c:  C = W->commands;
windowtools.c:    while ((C->next)&&(C->id != id)) C = C->next;
windowtools.c:    if (C->id != id) return(0);
windowtools.c:    C->numfuncs++;
windowtools.c:    functions = (int (**)())malloc(C->numfuncs*sizeof(int (*)()));
windowtools.c:    for (i = 0; i < C->numfuncs; i++)
windowtools.c:	if (*(C->functions+i) == function)
windowtools.c:  C = W->commands;
windowtools.c:  while ((C)&&(C->id != id)) C = C->next;
windowtools.c:  if (C)  return(*C->arguments);
windowtools.c:  for (t = 0; t < C->numfuncs; t++)
windowtools.c:    if (*(C->functions+t) == function)
windowtools.c:      return(*(C->arguments+t));
windowtools.c:  NewMem->display   = fildes;
windowtools.c:  NewMem->input     = ifildes;
windowtools.c:  NewMem->parent    = owner;
windowtools.c:  NewMem->relx      = subx;
windowtools.c:  NewMem->rely      = suby;
windowtools.c:  NewMem->width     = winwide;
windowtools.c:  NewMem->height    = wintall;
windowtools.c:  NewMem->stat      = 0;
windowtools.c:  NewMem->commands  = NULL;
windowtools.c:  NewMem->port      = MakeList();
windowtools.c:  NewMem->mask      = MakeList();
windowtools.c:      if ((NewMem->tag = (char *)malloc((strlen(tag)+1)*sizeof(char)))==NULL) {
windowtools.c:	fprintf(stderr,"MakeWindow malloc NewMem->tage error errno=%d\n",errno);
windowtools.c:      strcpy(NewMem->tag, tag);
windowtools.c:  else NewMem->tag = NULL;
windowtools.c:    ShowWindow(W, W->x1, W->y1, W->x2, W->y2);
windowtools.c:    if (W->parent) ShowTops(W, W->x1, W->y1, W->x2, W->y2);
windowtools.c:  if (W->parent) ShowTops(W, x1, y1, x2, y2);
windowtools.c:  if (W->stat != 1)
windowtools.c:      if (W->parent)
windowtools.c:	  AddToList((W->parent)->port, W);
windowtools.c:      GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
windowtools.c:      TransformCoords(W,W->relx,W->rely,W->width,W->height); /* BS 2/22/91 */
windowtools.c:      W->stat = 1;
windowtools.c:/* Two screen version of install  -- LHR  1/11/90 */
windowtools.c:  if (W->stat != 1)
windowtools.c:      if (W->parent)
windowtools.c:	  if (W->display != W->parent->display) W->display = W->parent->display;
windowtools.c:	  AddToList((W->parent)->port, W);
windowtools.c:      GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
windowtools.c:      W->stat = 1;
windowtools.c:    DrawMask(W, W->x1, W->y1, W->x2, W->y2);
windowtools.c:    ShowTops(W->parent, W->x1, W->y1, W->x2+1, W->y2+1);
windowtools.c:CloseAllChildren( window)	/* closes all children of a window -- *DKY- 8Jul90* */
windowtools.c:  if( window->port) {
windowtools.c:    list = window->port;
windowtools.c:      list = list->Front;
windowtools.c:    while( list->id != NULL) {
windowtools.c:      CloseAllChildren( list->id);
windowtools.c:      CloseWindow( list->id);
windowtools.c:      list = list->Front;
windowtools.c:  if (W->stat) {
windowtools.c:    if (GetFromList((W->parent)->port, W))
windowtools.c:	W->stat = 0;
windowtools.c:      printf("UnstallWin() -- failed on window '%s'\n", W->tag);
windowtools.c: * DKY-19Feb91
windowtools.c:  L = (W->parent)->port;
windowtools.c:  for (Current = L2->Front; Current != L2; Current = Current->Front)
windowtools.c:      temp = Current->id;
windowtools.c:  Temp = (W->mask)->Front;
windowtools.c:  while (Temp != W->mask)
windowtools.c:      if (Temp->id != W)
windowtools.c:	GetFromList((Temp->id)->mask, W);
windowtools.c:      Temp = Temp->Front;
windowtools.c:  (W->mask)->Front = W->mask;
windowtools.c:  (W->mask)->Behind = W->mask;
windowtools.c:  L = (W->parent)->port;
windowtools.c:  Pad = W->mask;
windowtools.c:  for (Current = L->Front; Current != L; Current = Current->Front)
windowtools.c:      if (Current->id != W) {
windowtools.c:	if (Project(W, Current->id)) AddToList(Pad, Current->id);
windowtools.c:  L = (W->parent)->port;
windowtools.c:  for (Current= L->Front; Current != L; Current = Current->Front)
windowtools.c:    if (Current->id != W)
windowtools.c:      if (Project(W, Current->id)) AddToList((Current->id)->mask, W);
windowtools.c:  L = (W->parent)->port;
windowtools.c:  for (Current = L->Front; Current != L; Current = Current->Front)
windowtools.c:    if (Current->id != W)
windowtools.c:      GetFromList((Current->id)->mask, W);
windowtools.c:  L = W->port;
windowtools.c:  Current = L->Behind;
windowtools.c:      W = PastWin->parent;
windowtools.c:      L = W->port;
windowtools.c:      Current = L->Behind;
windowtools.c:      for(Current; ((Current->id != PastWin)&&(Current != L)); Current= Current->Behind);
windowtools.c:      if (Current->id == PastWin) Current = Current->Behind;
windowtools.c:  x1 = W->x1; y1 = W->y1;
windowtools.c:      Win = Current->id;
windowtools.c:      if ((Win->relx+x1 <= x) && (Win->relx+x1+Win->width-1 >= x) &&
windowtools.c:          (Win->rely+y1 <= y) && (Win->rely+y1+Win->height-1 >= y))
windowtools.c:      Current = Current->Behind;
windowtools.c:  wx1 = W1->relx;  wx2 = wx1 + W1->width-1;
windowtools.c:  wy1 = W1->rely;  wy2 = wy1 + W1->height-1;
windowtools.c:  px1 = W2->relx;  px2 = px1 + W2->width-1;
windowtools.c:  py1 = W2->rely;  py2 = py1 + W2->height-1;
windowtools.c:  cstruct.x1 = MAX(a1, W->x1);
windowtools.c:  cstruct.y1 = MAX(b1, W->y1);
windowtools.c:  cstruct.x2 = MIN(a2, W->x2);
windowtools.c:  cstruct.y2 = MIN(b2, W->y2);
windowtools.c:  if (W->parent == NULL)
windowtools.c:      ShowBottoms(W->parent, x1, y1, x2, y2);
windowtools.c:   if ((W->parent)->parent) 
windowtools.c:     GetMostClipped((W->parent)->parent, &x1, &y1, &x2, &y2);
windowtools.c:  DrawWindow(W->parent, x1, y1, x2, y2);
windowtools.c:  for (Temp = (W->mask)->Front ; (Temp != W->mask) ; Temp = Temp->Front)
windowtools.c:    if (Temp->id != W) ShowWindow(Temp->id, x1, y1, x2, y2);
windowtools.c:  for (win = parent; win != NULL; win = win->parent) {
windowtools.c:    if (win->x1 > *x1) *x1 = win->x1;
windowtools.c:    if (win->y1 > *y1) *y1 = win->y1;
windowtools.c:    if (win->x2 < *x2) *x2 = win->x2;
windowtools.c:    if (win->y2 < *y2) *y2 = win->y2;
windowtools.c:  if (W->parent)
windowtools.c:    GetMostClipped(W->parent, &x1, &y1, &x2, &y2);
windowtools.c:  L = W->port;
windowtools.c:    for (Current  = L->Front; Current !=L; Current = Current->Front)
windowtools.c:	Win = Current->id;
windowtools.c:	fx1 = MAX(Win->x1, x1);
windowtools.c:	fx2 = MIN(Win->x2, x2);
windowtools.c:	fy1 = MAX(Win->y1, y1);
windowtools.c:	fy2 = MIN(Win->y2, y2);
windowtools.c:  if (W->parent == NULL) {
windowtools.c:  if ((((W->mask)->Behind)->id) == W) {
windowtools.c:    ShowTops(W->parent, x1, y1, x2, y2);
windowtools.c:  for(Temp = (W->mask)->Front; ((Temp->id != W)&&(Temp!=W->mask));Temp = Temp->Front);
windowtools.c:  if (Temp == W->mask) printf("ShowTops() - oops there's nothing on top of window '%s'!\n", W->tag);
windowtools.c:  if (Temp != W->mask) {
windowtools.c:    for (Temp = Temp->Front; (Temp != W->mask) ; Temp = Temp->Front)
windowtools.c:	if ((x2 >= (Temp->id)->x1) && (x1 <= (Temp->id)->x2) && (y2 >= (Temp->id)->y1) && (y1 <= (Temp->id)->y2))
windowtools.c:	  ShowWindow(Temp->id, x1, y1, x2, y2);
windowtools.c:  ShowTops(W->parent, x1, y1, x2, y2);
windowtools.c:      *x1 += Trace->relx;
windowtools.c:      *y1 += Trace->rely;
windowtools.c:      Trace = Trace->parent;
windowtools.c:  *x2 = *x1+W->width-1;
windowtools.c:  *y2 = *y1+W->height-1;
windowtools.c:  TransformCoords(W,W->relx,W->rely,W->width,W->height);
windowtools.c:  GetPoints(W->parent, &ox, &oy, &ow, &ol);
windowtools.c:  if (nx+W->width-1<=ow)  W->relx=nx-ox;
windowtools.c:  if (ny+W->height-1<=ol) W->rely=ny-oy;
windowtools.c:  GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
windowtools.c:  L = W->port;
windowtools.c:  for (Current = L->Front; Current != L; Current = Current->Front)
windowtools.c:    AdjustCoords(Current->id);
windowtools.c:  TransformCoords(W, W->relx, W->rely, wide, tall);
windowtools.c:  L = W->port;
windowtools.c:  oldwide = W->width;
windowtools.c:  oldtall = W->height;
windowtools.c:  oldx = W->relx;
windowtools.c:  oldy = W->rely;
windowtools.c:  W->relx = x;
windowtools.c:  W->rely = y;
windowtools.c:  W->width = wide;
windowtools.c:  W->height = tall;
windowtools.c:  GetPoints(W, &(W->x1), &(W->y1), &(W->x2), &(W->y2));
windowtools.c:  W->x1 += (x-oldx);
windowtools.c:  W->y1 += (y-oldy);
windowtools.c:  W->x2 += (x-oldx)+(wide-oldwide);
windowtools.c:  W->y2 += (y-oldy)+(tall-oldtall);
windowtools.c:  for (Current = L2->Front; Current != L2; Current = Current->Front)
windowtools.c:      tempwin = Current->id;
windowtools.c:struct Window *			/* returns root of window w.  *DKY-23Sep90* */
windowtools.c:    while( w->parent != NULL)
windowtools.c:      w = w->parent;
windowtools.c:  Wx1=W->x1;
windowtools.c:  Wx2=W->x2;
windowtools.c:  Wy1=W->y1;
windowtools.c:  Wy2=W->y2;
windowtools.c:  Wx1 = MIN( Wx1, M->x1);
windowtools.c:  Wy1 = MIN( Wy1, M->y1);
windowtools.c:  Wx2 = MAX( Wx2, M->x2);
windowtools.c:  Wy2 = MAX( Wy2, M->y2);
windowtools.c:  Wwd = Wx2-Wx1;
windowtools.c:  Wht = Wy2-Wy1;
windowtools.c:      button = p->button;
windowtools.c:      if( loop->button >0) {
windowtools.c:      loop->button = button;
windowtools.c:      p->button = buttonstat;
windowtools.c:      p->bnum = button;
windowtools.c:	NewWin = Windowfind( W, p->x, p->y, NULL);
windowtools.c:	  NewWin = Windowfind( W, p->x, p->y, NewWin);
windowtools.c:	if( loop->Last != NewWin) {
windowtools.c:	  SendMessage( loop->Last, NOECHO, NewWin); /* SendMessage(loop->Last, NOECHO, data); */
windowtools.c:	  loop->Last = NewWin;
windowtools.c:	  SendMessage( loop->Last, ECHO, NewWin); /* SendMessage(loop->Last, ECHO, data); */
windowtools.c:      loop->trap = trap;
windowtools.c:      trap = t->window;
windowtools.c:      trapstat = t->until;
windowtools.c:  L->Front = L->Behind = L;
windowtools.c:  L->id = NULL;
windowtools.c:    for (Current = L->Front; (Current != L); Current = Current->Front)
windowtools.c:    if (Current->id == id)
windowtools.c:  Temp->Front = L;
windowtools.c:  Temp->Behind = L->Behind;
windowtools.c:  (L->Behind)->Front = Temp;
windowtools.c:  L->Behind = Temp;
windowtools.c:  Temp->id = id;
windowtools.c:  while (Current->id != id)
windowtools.c:      Current = Current ->Front;
windowtools.c:  (Current->Behind)->Front = Current->Front;
windowtools.c:  (Current->Front)->Behind = Current->Behind;
windowtools.c:  for(Current = L1->Front; Current != L1; Current = Current->Front)
windowtools.c:    AddToList(*L2, Current->id);
windowtools.c:  Temp = L->Front;
windowtools.c:      Temp = Temp->Front;
windowtools.c:  for (Current = L->Front; (Current->id !=id)&&(Current != L); Current = Current->Front);
windowtools.c:  for (Current = L->Front; (Current != L) && (strcmp(Current->id->tag, name)); Current = Current->Front);
windowtools.c:RemoveWindowFromList( L, W)	/* remove element from list whose id == W *DKY-30Apr91* */
windowtools.c:    printf( "ERROR: RemoveFromList() -- null list.\n");
windowtools.c:    return( -1);
windowtools.c:  while( L->id != W) {
windowtools.c:    L = L->Front;
windowtools.c:  if( L->id == W) {
windowtools.c:    L->Front->Behind = L->Behind;
windowtools.c:    L->Behind->Front = L->Front;
windowtools.c:CloseWindowsInList( L)		/* close all windows in list *DKY-30Apr91* */
windowtools.c:  L = L->Front;
windowtools.c:  while( L->id) {
windowtools.c:    CloseWindow( L->id);
windowtools.c:    L = L->Front;
windowtools.c:UnstallWindowsInList( L)		/* unstall all windows in list *DKY-11May91* */
windowtools.c:  L = L->Front;
windowtools.c:  while( L->id) {
windowtools.c:    UnstallWin( L->id);
windowtools.c:    L = L->Front;
windowtools.c:OpenWindowsInList( L)		/* open all windows in list *DKY-30Apr91* */
windowtools.c:  L = L->Front;
windowtools.c:  while( L->id) {
windowtools.c:    OpenWindow( L->id);
windowtools.c:    L = L->Front;
windowtools.c:FindChildByName( W, childName)	/* *DKY- 2Nov90* */
windowtools.c:  list = (struct List *)AskListByName( W->port, childName);
windowtools.c:    return( list->id);
windowtools.c:  t->window = W;
windowtools.c:  t->until = id;
windowtools.c:  L->Front = L->Behind = L;
windowtools.c:  L->id = id;
windowtools.c:  for (Current = L->Front; (Current != L); Current = Current->Front);
windowtools.c:  Temp->Front = L;
windowtools.c:  Temp->Behind = L->Behind;
windowtools.c:  (L->Behind)->Front = Temp;
windowtools.c:  L->Behind = Temp;
windowtools.c:  Temp->id = T;
windowtools.c:  while (Current->id != T)
windowtools.c:      Current = Current ->Front;
windowtools.c:  (Current->Behind)->Front = Current->Front;
windowtools.c:  (Current->Front)->Behind = Current->Behind;
windowtools.c:  for (Current = L->Front; (Current->id != T)&&(Current != L); Current = Current->Front);
windowtools.c:  Cur = L->Front;
windowtools.c:      Cur = Cur->Front;
windowtools.c:  for(Current = L1->Front; Current != L1; Current = Current->Front)
windowtools.c:    AddThing(*L2, Current->id);
yesno.c:  if( YesNo)			/* *DKY-21Feb91* */
yesno.c:  YesNo = MakeWindow(W->display,W->input,W,0,0,100,100,"yesno");
yesno.c:  Headline = MakeWindow(W->display,W->input,YesNo,0,0,100,100,"Headline");
yesno.c:  Maker(Headline,7,2,-5,2+16);
yesno.c:  Yback = MakeWindow(W->display,W->input,YesNo,0,0,100,100,"Yback");
yesno.c:  Nback = MakeWindow(W->display,W->input,YesNo,0,0,100,100,"Nback");
yesno.c:  display = Root->display;
yesno.c:  YesNo->parent = Root;
yesno.c:  set_font(parms->font,parms->size,parms->bits);
yesno.c:  parms->string = string;
yesno.c:  if (x+width > display->viswidth) x1 = display->viswidth-width;
yesno.c:  if (y+height > display->visheight) y1 = display->visheight-height;
yesno.c:  YesNo->display = display;
yesno.c:  ThreeChoice = MakeWindow(W->display,W->input,W,0,0,100,100,"ThreeChoice");
yesno.c:  THeadline = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"Headline");
yesno.c:  Maker(THeadline,7,2,-5,18);
yesno.c:  B1 = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"B1");
yesno.c:  Maker(B1,0,18,10,-6);
yesno.c:  B2 = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"B2");
yesno.c:  Maker(B2,0,18,10,-6);
yesno.c:  B3 = MakeWindow(W->display,W->input,ThreeChoice,0,0,100,100,"B3");
yesno.c:  Maker(B3,0,18,10,-6);
yesno.c:  display = Root->display;
yesno.c:  ThreeChoice->parent = Root;
yesno.c:  set_font(parms->font,parms->size,parms->bits);
yesno.c:  parms->string = string;
yesno.c:  parms = (struct stringstruct *)(*(C->arguments+1));
yesno.c:  parms->string = string1;
yesno.c:  parms = (struct stringstruct *)*(C->arguments+1);
yesno.c:  parms->string = string2;
yesno.c:  parms = (struct stringstruct *)*(C->arguments+1);
yesno.c:  parms->string = string3;
yesno.c:  if (width > twidth) p1 += (width-twidth)/2;
yesno.c:  if (width > twidth) p2 += (width-twidth)/2;
yesno.c:  m->x1 = 8;
yesno.c:  m->x2 = p1-5;
yesno.c:  m->y1 = height/2;
yesno.c:  m->x1 = p1;
yesno.c:  m->x2 = p2-5;
yesno.c:  m->y1 = height/2;
yesno.c:  m->x1 = p2;
yesno.c:  m->x2 = p2+w3;
yesno.c:  m->y1 = height/2;
yesno.c:  if (x+width > display->viswidth) x1 = display->viswidth-width;
yesno.c:  if (y+height > display->visheight) y1 = display->visheight-height;
yesno.c:  ThreeChoice->display = display;
