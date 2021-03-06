#include "stdio.h"

#define NUMH 40 
#define NUMV 12 
#define NUMC 15 
#define	NUMMUN NUMH*NUMV*NUMC*2

static float   munciedata[NUMV][NUMH][NUMC][2];
static char    mundata[] = "/vlw/data/BadW/muncie.data";


main()
{
  FILE *munfp, *fp;
  int v, h, c;

  munfp = fopen( mundata, "r" );
  
  fread( munciedata, sizeof(float), NUMMUN, munfp );
  fclose( munfp );

  fp = fopen("muncie.ascii", "w");
  
  for (v = 0; v < NUMV; v++) {
    for (h = 0; h < NUMH; h++) {
      for (c = 0; c < NUMC; c++) {
	fprintf(fp, "%f %f\n", munciedata[v][h][c][0], munciedata[v][h][c][1]);
      }
    }
  }
  fclose (fp);
}

