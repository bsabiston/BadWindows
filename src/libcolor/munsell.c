#define NUMH 40 /* 0 to 100 by 2.5 */
#define NUMV 12  /* 1 to 12 */  /* values 10 - 12 are extrapolated */
#define NUMC 15 /* 0 to 26 by 2 */

float   munciedata[NUMV][NUMH][NUMC][2];
char    mundata[] = "/u/walter/ncolor/munsell2cie.data";
int     munsellinit = 0;
