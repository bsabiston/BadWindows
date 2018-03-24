#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>

#define LEFTEND   33
#define BACKCHAR  34
#define RIGHTEND  35

#define DEBUG 0

float fgrd_hue, fgrd_light, fgrd_sat;
float bgrd_hue, bgrd_light, bgrd_sat;

float fgrd_H, fgrd_V, fgrd_C;
float bgrd_H, bgrd_V, bgrd_C;







Adaptive3StringWin(W, contrast, string, x, y, font, size, bits, red, green, blue, t, munsellflag)     /*DB 26june90 */
     struct Window *W;
     float contrast;
     char *string, *font;
     int size, bits, red, green, blue, t, x, y, munsellflag;
{
  struct adaptive_stringstruct *params;
  int Adaptive_DrawAString();

  /*printf("\nW %s   backgrdwin %s  string %s  x %d  y %d   font %s   size %d   bits %d   red %d   green %d   blue %d   t %d",
            W->tag, backgrdwin->tag, string, x, y, font, size, bits, red, green, blue, t); */

  params = (struct adaptive_stringstruct *) malloc(sizeof(struct adaptive_stringstruct));
  params->parms = (struct stringstruct *) malloc (sizeof (struct stringstruct));

  params->parms->font = font;

  params->parms->string = string;

  params->parms->size = size;
  params->parms->bits = bits;
  params->parms->x = x;
  params->parms->y = y;
  params->parms->red = red;
  params->parms->green = green;
  params->parms->blue = blue;
  params->parms->t = t;
  params->parms->char_space = 0;
  params->parms->word_space = 0;

  params->contrast = contrast;
  params->munsellflag = munsellflag;

  AttachCommand(W, DRAW, Adaptive3_DrawAString, (char *) params);

}




Adaptive3_DrawAString(W, id, data, stuff)  
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct adaptive_stringstruct *mstruct, *newstruct;
  struct clipstruct *cstruct;
  int screen, cx1, cx2, cy1, cy2;
  int *colors, *trans;
  int *temp;

  if (id==DRAW)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      cstruct = (struct clipstruct *)data;

      /*printf ("\nIn Adaptive3_DrawAString, clip coords: x1 %d, y1 %d, x2 %d, y2 %d", cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);*/

      set_font(mstruct->parms->font, mstruct->parms->size, mstruct->parms->bits);
      set_monitor(W->display->bits, W->display->fildes);
      set_text_clip_rectangle(cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);
      set_char_space(mstruct->parms->char_space);
      set_word_space(mstruct->parms->word_space);
      if (mstruct->parms->string)
	{
	  if (mstruct->parms->x == CENTERED)
	    {
	      int xx;
	      xx = W->x1+W->width/2 - string_width(mstruct->parms->string)/2;
	      display3_adaptive_string(W,mstruct, xx, W->y1+mstruct->parms->y);
	    }
	  else if (mstruct->parms->x < 0)
	    {
	      int xx;
	      xx = string_width(mstruct->parms->string);
	      display3_adaptive_string(W, mstruct, W->x2 - xx + mstruct->parms->x, W->y1+mstruct->parms->y);
	    }
	  else display3_adaptive_string(W, mstruct, W->x1+mstruct->parms->x, W->y1+mstruct->parms->y);
	}
      set_char_space( 0);	/* *DKY-18Mar90-17:29* */
      set_word_space( 0);	/* *DKY-18Mar90-17:29* */
    }

  else if (id == ATTRIBUTES)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      mstruct->parms->string = data;
    }

  else if (id == CHANGESTRING)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      mstruct->parms->string = data;
    }

  else if (id == CHANGECOLOR)
    {
      CloseWindow(W);
      mstruct = (struct adaptive_stringstruct *)stuff;
      colors = (int *)data;	/* I changed this to take an *int, 12/5/89, dsmall */
      mstruct->parms->red = (colors[0]);
      mstruct->parms->green = (colors[1]);
      mstruct->parms->blue = (colors[2]);
      OpenWindow(W);
    }

  else if (id == CHANGETRANS)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      trans = (int *)data;
      mstruct->parms->t = *trans;
    }

  else if (id == SETCHARSPACE)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      temp = (int *)data;
      mstruct->parms->char_space = *temp;
    }

  else if (id == SETWORDSPACE)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      temp = (int *)data;
      mstruct->parms->word_space = *temp;
    }

  else if (id == CHANGEFONT)
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      newstruct = (struct adaptive_stringstruct *)data;
      mstruct->parms->font = newstruct->parms->font;
      mstruct->parms->size = newstruct->parms->size;
      mstruct->parms->bits = newstruct->parms->bits;
    }

  else if (id == CHANGE_X_POS)	/* *DKY-13May90* */
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      temp = (int *)data;
      mstruct->parms->x = *temp;
    }

  else if (id == CHANGE_Y_POS)	/* *DKY-13May90* */
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      temp = (int *)data;
      mstruct->parms->y = *temp;
    }

  else if (id == SET_SIZE)	/* *DKY-13May90* */
    {
      mstruct = (struct adaptive_stringstruct *)stuff;
      temp = (int *)data;
      mstruct->parms->size = *temp;
    }

  else if (id == GET_STRINGWIN_COLOR) {  	/* *DKY-15May90* */
    int **colors;
    /* data is a pointer to an array of 3 integers */
    colors = (int **)data;
    mstruct = (struct adaptive_stringstruct *)stuff;

    *colors = (int *)&(mstruct->parms->red);
    *(colors+1) = (int *)&(mstruct->parms->green);
    *(colors+2) = (int *)&(mstruct->parms->blue);
  }

}



display3_adaptive_string (W, stringstuff, x, y)
struct Window *W;
struct adaptive_stringstruct *stringstuff;
int x, y;
{
  int stwidth, stheight, string_width(), *draw_adapt_box(), *control3_forground_contrast(), *b_rgb, *new_f_rgb, *old_f_rgb;
  int *munsell_control_foreground_contrast();
  old_f_rgb = (int *) malloc (sizeof (int) * 3);
  *old_f_rgb = stringstuff->parms->red;  *(old_f_rgb+1) = stringstuff->parms->green;  *(old_f_rgb+2) = stringstuff->parms->blue;

  if ((set_font (stringstuff->parms->font, stringstuff->parms->size, stringstuff->parms->bits)) == 0) printf("\n ERROR set_font");
  stwidth = (int) string_width (stringstuff->parms->string);
  stheight = stringstuff->parms->size;
  
  b_rgb = (int *) draw_adapt_box (W, stringstuff, stwidth, stheight, W->x1 + stringstuff->parms->x, W->y1 + stringstuff->parms->y);


  if (stringstuff->munsellflag) 
    new_f_rgb = (int *) munsell_control_foreground_contrast (b_rgb, old_f_rgb, stringstuff->contrast);
  else 
    new_f_rgb = (int *) control3_forground_contrast (b_rgb, old_f_rgb, stringstuff->contrast);
  
  free (b_rgb);

  set_font_color (*new_f_rgb, *(new_f_rgb+1), *(new_f_rgb+2), stringstuff->parms->t);
  /*printf("\nForeground R %d  G %d  B %d", *new_f_rgb, *(new_f_rgb+1), *(new_f_rgb+2));*/

  free (new_f_rgb);

  if ((set_font (stringstuff->parms->font, stringstuff->parms->size, stringstuff->parms->bits)) == 0) printf("\n ERROR set_font");
  
  display_string (stringstuff->parms->string, x+4, y);

  clip_rectangle (W->display->fildes, (float) 0.0, (float)((W->display)->width-1), (float) 0.0, (float)((W->display)->height-1));
}




  
int *control3_forground_contrast (rgb_back, rgb_front, contrast)
int *rgb_back, *rgb_front;
float contrast;
{
  float *hls_back, *hls_front, old_contrast, upper, lower, maxsat(), *rgb_to_hls();
  int *hls_to_rgb();

  hls_back = (float *) rgb_to_hls (rgb_back);
  hls_front = (float *) rgb_to_hls (rgb_front);

  bgrd_hue = *hls_back;   bgrd_light = *(hls_back+1);   bgrd_sat = *(hls_back+2);



  upper = *(hls_back+1) + contrast;  /* Compute light and dark values of foreground lightness */
  if (upper > 1.0)  upper = 1.0; 

  lower = *(hls_back+1) - contrast;
  if (lower < 0.0)  lower = 0.0; 

  old_contrast = *(hls_back+1) - *(hls_front+1);
  /*printf("old_contrast: %f\n", old_contrast);*/

  if (old_contrast < 0)     /* Light on Dark */ 

    if (upper > 1.0)
      if (maxsat(lower) >= *(hls_front+2)) {
	/*printf ("\nL on D, lower, no adjustment");*/
	*(hls_front+1) = lower;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb(hls_front));
      }
      else {
	/*printf("\nL on D, lower, adjustment");*/
	*(hls_front+1) = lower;
	*(hls_front+2) = maxsat(lower);
	if (*(hls_front+2) == 0) *hls_front = -1.0;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb(hls_front));
      }
    
    else 
      
      if (maxsat(upper) > *(hls_front+2)) {
	/*printf("\nL on D, upper, no adjustment");*/
	*(hls_front+1) = upper;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb (hls_front));
      }
      else {
	/*printf("\nL on D, upper, adjustment");*/
	*(hls_front+1) = upper;
	*(hls_front+2) = maxsat(upper);
	if (*(hls_front+2) == 0) *hls_front = -1.0;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb (hls_front));
      }
  

  else    /* Dark on Light */
    
    if (lower < 0.0)
      if (maxsat(upper) > *(hls_front+2)) {
	/*printf ("\nD on L, upper, no adjustment");*/
	*(hls_front+1) = upper;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb (hls_front));
      }
      else {
	/*printf ("\nD on L, upper, adjustment");*/
	*(hls_front+1) = upper;
	*(hls_front+2) = maxsat(upper);
	if (*(hls_front+2) == 0) *hls_front = -1.0;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb (hls_front));
      }
    else 
      if (maxsat(lower) > *(hls_front+2)) {
	/*printf ("\nD on L, lower, no adjustment");*/
	*(hls_front+1) = lower;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb (hls_front));
      }
      else {
      /*printf ("\nD on L, lower, adjustment");*/
	*(hls_front+1) = lower;
	*(hls_front+2) = maxsat(lower);
	if (*(hls_front+2) == 0) *hls_front = -1.0;
	fgrd_hue = *hls_front;   fgrd_light = *(hls_front+1);   fgrd_sat = *(hls_front+2);
	return ((int *) hls_to_rgb (hls_front));
      }
}


