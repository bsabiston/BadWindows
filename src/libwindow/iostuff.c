#include <stdio.h>
#include <windows.c.h>
#include <structures.h>

static float *ctable = NULL; /* contains paintbox 216 color table for loading old 8-bit icons */

char *bw_file(name)
char *name;
{
  static char badwdirectory[200];
  sprintf(badwdirectory,"%s%s",BADWINDOWS_DIRECTORY,name);
  return(badwdirectory);
}

SetBadWindowsDirectory(name)
char *name;
{
  if (BADWINDOWS_DIRECTORY) free(BADWINDOWS_DIRECTORY);
  BADWINDOWS_DIRECTORY = (char *)CopyString(name);
}


InitSoftColorTable()     /* v 1.0b */
{
  int color;
  float red, green, blue;

  if (!ctable) ctable = (float *)malloc(256*3*sizeof(float));

  for(color=0;color<39;++color)
    ctable[color*3] = ctable[color*3+1] = ctable[color*3+2] = 0;

  color = 39;
  for(blue = 1.0; blue >= 0.0; blue = blue - (1.0/5.0))
    for(green = 1.0; green >= 0.0; green = green - (1.0/5.0))
      for(red = 1.0; red >= 0.0; red = red - (1.0/5.0))
	{
	  ctable[color*3] = (int)(red*255.0);
	  ctable[color*3+1] = (int)(green*255.0);
	  ctable[color*3+2] = (int)(blue*255.0);
	  ++color;
	};

  ctable[5*3] = LIGHT;
  ctable[5*3+1] = LIGHT;
  ctable[5*3+2] = LIGHT;

  ctable[255*3] = FULL;
  ctable[255*3+1] = FULL;
  ctable[255*3+2] = FULL;

  ctable[0] = NONE;
  ctable[1] = NONE;
  ctable[2] = NONE;

  return;
}



LoadFullBitMap(name, xt, yt, buffer)     /* v 1.0b */
     char *name;
     int *xt, *yt;
     unsigned char **buffer;
{
  FILE *fopen(), *fp;
  int xx, yy, xc, yc;
  unsigned char *pic, value;

  fp = fopen(name, "r");

  if (fp == NULL) return (0);

  fscanf(fp, "%d %d", &xc, &yc);

  pic=(unsigned char *)malloc(xc*yc*3*sizeof(unsigned char));
  if (!pic) return(NULL);
  for (yy=yc-1; yy>=0; --yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)] = value;
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+1] = value;
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+2] = value;
      }
  *xt = xc;
  *yt = yc;
  *buffer = pic;

  fclose(fp);

  return(1);
}


LoadSuguruBitMap(name, xt, yt, buffer)     /* v 1.0b */
     char *name;
     int *xt, *yt;
     unsigned char **buffer;
{
  FILE *fopen(), *fp;
  int xx, yy, xc, yc;
  unsigned char *pic, value;

  fp = fopen(name, "r");

  if (fp == NULL) return (0);

  fscanf(fp, "%d %d\n", &xc, &yc);
  printf("Loading %s, size %d x %d\n",name,xc,yc);
  pic=(unsigned char *)malloc(xc*yc*3*sizeof(unsigned char));
  if (!pic) return(NULL);

  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)] = value;
      }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+1] = value;
      }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+2] = value;
      }

  *xt = xc;
  *yt = yc;
  *buffer = pic;

  fclose(fp);

  return(1);
}


/* Loads the first frame of a video file as a bitmap */
LoadSuguruFrameBitMap(name, xt, yt, buffer)     /* v 1.0b */
     char *name;
     int *xt, *yt;
     unsigned char **buffer;
{
  FILE *fopen(), *fp;
  int xx, yy, xc, yc, numfr;
  unsigned char *pic, value;

  fp = fopen(name, "r");

  if (fp == NULL) return (0);

  fscanf(fp, "%d %d %d\n", &xc, &yc, &numfr);
  printf("Loading %s, size %d x %d\n",name,xc,yc);
  pic=(unsigned char *)malloc(xc*yc*3*sizeof(unsigned char));
  if (!pic) return(NULL);

  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)] = value;
      }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+1] = value;
      }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+2] = value;
      }

  *xt = xc;
  *yt = yc;
  *buffer = pic;

  fclose(fp);

  return(1);
}



LoadDaveBitMap(name, xt, yt, buffer)     /* v 1.0b */
     char *name;
     int *xt, *yt;
     unsigned char **buffer;
{
  FILE *fopen(), *fp;
  int xx, yy, xc, yc;
  unsigned char *pic, value;

  fp = fopen(name, "r");

  if (fp == NULL) return (0);

  fread (&xc, sizeof(int), 1, fp);
  fread (&yc, sizeof(int), 1, fp);
	
  /** This is a terrible kludge to load things that start with ascii **/
  if (xc >1280) {
    printf("wd was %d\n", xc);
    rewind(fp);
    fscanf(fp, "%d %d\n", &xc, &yc);
  }

  printf("Loading %s, size %d x %d\n",name,xc,yc);
  pic=(unsigned char *)malloc(xc*yc*3*sizeof(unsigned char));
  if (!pic) {
    printf("Error allocating memory for %s\n", name);
    return(NULL);
  }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)] = value;
      }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+1] = value;
      }
  for (yy=0; yy<yc; ++yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	pic[yy*(xc*3)+(xx*3)+2] = value;
      }

  *xt = xc;
  *yt = yc;
  *buffer = pic;

  fclose(fp);

  return(1);
}



LoadBitMap8to24(name, xt, yt, buffer, color, ccolor)     /* v 1.0b */
     char *name;
     int *xt, *yt, color, ccolor;
     unsigned char **buffer;
{
  FILE *fopen(), *fp;
  int xx, yy, xc, yc;
  unsigned char *pic, value;

  fp = fopen(name, "r");

  if ((fp == NULL)||(ctable == NULL)) return (0);

  fscanf(fp, "%d %d", &xc, &yc);

  pic=(unsigned char *)malloc(xc*yc*3*sizeof(unsigned char));
  for (yy=yc-1; yy>=0; --yy)
    for(xx=0; xx<xc; ++xx)
      {
	value = getc(fp);
	if (value != color)
	  {
	    pic[yy*(xc*3)+(xx*3)] = ctable[value*3];
	    pic[yy*(xc*3)+(xx*3)+1] = ctable[value*3+1];
	    pic[yy*(xc*3)+(xx*3)+2] = ctable[value*3+2];
	  }
	else {
	  pic[yy*(xc*3)+(xx*3)] = ccolor;
	  pic[yy*(xc*3)+(xx*3)+1] = 0;
	  pic[yy*(xc*3)+(xx*3)+2] = 0;
	}
      }
  *xt = xc;
  *yt = yc;
  *buffer = pic;

  fclose(fp);

  return(1);
}


