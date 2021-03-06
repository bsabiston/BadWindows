#include <starbase.c.h>
#include <stdio.h>
#include <structures.h>
#include <windows.c.h>
#include "/u/didier/TYPO2/adapstructs.h"

#define LEFTEND   33
#define BACKCHAR  34
#define RIGHTEND  35

#define DEBUG 0

struct colorcodestruct *Current_a_table;
char *Current_a_color;

float fgrd_hue, fgrd_light, fgrd_sat;
float bgrd_hue, bgrd_light, bgrd_sat;

float fgrd_H, fgrd_V, fgrd_C;
float bgrd_H, bgrd_V, bgrd_C;







Adaptive2StringWin(W, string, x, y, font, size, bits, color_name, t)     /*DB 21 oct 90 */
     struct Window *W;
     char *string, *font, *color_name;
     int size, bits, t, x, y;
{
  struct adaptive2_stringstruct *params;
  int Adaptive2_DrawAString();

  /*printf("\nW %s   backgrdwin %s  string %s  x %d  y %d   font %s   size %d   bits %d   
    red %d   green %d   blue %d   t %d",
    W->tag, backgrdwin->tag, string, x, y, font, size, bits, red, green, blue, t); */

  params = (struct adaptive2_stringstruct *) malloc(sizeof(struct adaptive2_stringstruct));
  params->parms = (struct stringstruct *) malloc (sizeof (struct stringstruct));

  params->parms->font = font;

  params->parms->string = string;

  params->parms->size = size;
  params->parms->bits = bits;
  params->parms->x = x;
  params->parms->y = y;
  params->parms->red = 0;
  params->parms->green = 0;
  params->parms->blue = 0;
  params->parms->t = t;
  params->parms->char_space = 0;
  params->parms->word_space = 0;

  params->color_name = color_name;

  AttachCommand(W, DRAW, Adaptive2_DrawAString, (char *) params);

}




Adaptive2_DrawAString(W, id, data, stuff)  
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct adaptive2_stringstruct *mstruct, *newstruct;
  struct clipstruct *cstruct;
  int screen, cx1, cx2, cy1, cy2;
  int *colors, *trans;
  int *temp;

  if (id==DRAW)
    {
      mstruct = (struct adaptive2_stringstruct *)stuff;
      cstruct = (struct clipstruct *)data;

      /*printf ("\nIn Adaptive2_DrawAstring, clip coords: x1 %d, y1 %d, x2 %d, y2 %d", 
	cstruct->x1, cstruct->y1, cstruct->x2, cstruct->y2);*/

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
	      display2_adaptive_string(W,mstruct, xx, W->y1+mstruct->parms->y);
	    }
	  else if (mstruct->parms->x < 0)
	    {
	      int xx;
	      xx = string_width(mstruct->parms->string);
	      display2_adaptive_string(W, mstruct, W->x2 - xx + mstruct->parms->x, W->y1+mstruct->parms->y);
	    }
	  else display2_adaptive_string(W, mstruct, W->x1+mstruct->parms->x, W->y1+mstruct->parms->y);
	}
      set_char_space( 0);	/* *DKY-18Mar90-17:29* */
      set_word_space( 0);	/* *DKY-18Mar90-17:29* */
    }
}



display2_adaptive_string (W, stringstuff, x, y)
struct Window *W;
struct adaptive2_stringstruct *stringstuff;
int x, y;
{
  int stwidth, stheight, string_width(), *draw_adapt_box(), *control2_foreground_contrast(), *b_rgb, *new_f_rgb, *old_f_rgb;
  int *munsell_control_foreground_contrast();


  if ((set_font (stringstuff->parms->font, stringstuff->parms->size, stringstuff->parms->bits)) == 0) 
    printf("\n ERROR set_font");
  stwidth = (int) string_width (stringstuff->parms->string);
  stheight = stringstuff->parms->size;
  
  b_rgb = (int *) draw_adapt_box (W, stringstuff, stwidth, stheight, W->x1 + stringstuff->parms->x, 
				  W->y1 + stringstuff->parms->y);

  new_f_rgb = (int *) control2_foreground_contrast (b_rgb, stringstuff->color_name);
  
  free (b_rgb);

  set_font_color (*new_f_rgb, *(new_f_rgb+1), *(new_f_rgb+2), stringstuff->parms->t);

  /*printf("\nForeground R %d  G %d  B %d", *new_f_rgb, *(new_f_rgb+1), *(new_f_rgb+2));*/

  free (new_f_rgb);

  if ((set_font (stringstuff->parms->font, stringstuff->parms->size, stringstuff->parms->bits)) == 0) 
    printf("\n ERROR set_font");
  
  display_string (stringstuff->parms->string, W->relx, W->rely);
/*  display_string (stringstuff->parms->string, x+4, y);*/

  clip_rectangle (W->display->fildes, (float) 0.0, (float)((W->display)->width-1), (float) 0.0, 
		  (float)((W->display)->height-1));
}



int *control2_foreground_contrast (rgb_back, front_color_name)
int *rgb_back;
char *front_color_name;
{
  float *hls_back, *hls_front, old_contrast, upper, lower, maxsat(), *rgb_to_hls(), contrast, find_contrast();
  int *hls_to_rgb(), *rgb_front, front_color_index, *colorname2rgb();


  front_color_index = (int) color_index (front_color_name);

  rgb_front = (int *) colorname2rgb (front_color_index);

  hls_back = (float *) rgb_to_hls (rgb_back);
  hls_front = (float *) rgb_to_hls (rgb_front);

  bgrd_hue = *hls_back;   bgrd_light = *(hls_back+1);   bgrd_sat = *(hls_back+2);

  contrast = (float) find_contrast (bgrd_light, front_color_index);

#if DEBUG
  printf("\nColor_index %d    fr %d  fg %d  fb %d", front_color_index, *rgb_front, *(rgb_front+1), *(rgb_front+2));
  printf("\nHLS_BACK %.3f %.3f %.3f", *hls_back, *(hls_back+1), *(hls_back+2));
  printf("\nHLS_FRONT %.3f %.3f %.3f", *hls_front, *(hls_front+1), *(hls_front+2));
  printf("\ncontrast %.3f", contrast);
#endif

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



float find_contrast (back_lite, color_index)
float back_lite;
int color_index;
{ 
  int contrast_index;

  contrast_index = (int) find_contrast_index (back_lite);
  
  if (Current_a_table) 
    return ((float) *(*(Current_a_table->table + color_index) + contrast_index));
  else
    printf("\nERROR: adaptive.c  find_contrast()");
}


int color_index (color_name)
char *color_name;
{
  int i, color_num;
  char **color_names;

  if (Current_a_table) {
    color_num = (int) Current_a_table->num_colors;
    
    color_names = (char **) Current_a_table->color_names;
    
    for ( i = 0 ; i < color_num ; i++)
      if (strcmp(*(color_names + i), color_name) == 0)
	return(i);
    
    printf("\nERROR: adaptive.c  color_index() color %s not in this table", color_name);
    exit(1);
  }
  else {
    printf("\nERROR: adaptive.c color_index() adaptive color table not set, use set_adaptive_color_table()");
    exit(1);
  }
}


int *colorname2rgb (color_index)
int color_index;
{
  int *rgb, *colors, index;

  colors = (int *) Current_a_table->colors;
  index = color_index * 3;

  rgb = (int *) malloc (sizeof (int) * 3);

  *rgb = *(colors + index);
  *(rgb+1) = *(colors + index + 1);
  *(rgb+2) = *(colors + index + 2);

  return ((int *) rgb);
}

  
/*-------------------------Maps background lightness values (HLS) to contrast indices from 0 to 14 */
int find_contrast_index (back_lite)
float back_lite;
{
  int count = 0, i;
  float lite = 0.0, step = 0.066;

  if ((back_lite < 0.0) || (back_lite > 1.0)) {
    printf ("\nget_contrast_index() utils.c  ERROR: background lightness value out of bound");
    exit (1);
  }

  for (i = 0 ; i < 15 ; i++)
    if ((back_lite > lite) && (back_lite < lite + step))
      return (count);
  else {
    count++;
    lite += step;
  }
  return (0);
}



  






