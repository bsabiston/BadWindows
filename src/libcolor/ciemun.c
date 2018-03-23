/* ----- harryp                 Jan 30 1990
 *
 *     this program takes a triplet of cie coodrinates(x,y,Y) 
 *     and finds its equivalent munsell triplet(H,V,C).
 */

#include <stdio.h>
#include <sys/file.h>
#include <math.h>
#include <munsell.h>
#include <cie.h>

float ciecoef[7] = { 0.0, 0.0, C1, -C2, C3, -C4, C5 };
float cieN[2] = { Nx, Ny };


static float   munciedata [NUMV] [NUMH] [NUMC] [2];
static char    mundata[] = "data/muncie.data";
static int     munsellinit = 0;


ciemun( x, y, Y, H, V, C )
float *H, *V, *C, Y, x, y;
{    
     register int i, j, k;
     int	h[2], v[2], c[2], u;
     float	ph[8][2];
     float	p[8][2], ih[4], ic[4];     
     int num = 0;
     double dv;


     /* calculate V from Y */

     Y2v( Y, V );


     v[0] = v[1] = floor((double) *V );
     v[0]--;


     dv = *V - v[1]; 


     if( v[0] < 0 ) {printf ("\nBad CIE v[0]= %d", v[0]); return( BADCIE );}

     if( v[0] >= NUMV ) {printf ("\nBad CIE v[0]>=NUMV: %d", v[0]); return( BADCIE );}

     if( v[1] >= NUMV ) {printf ("\nv[1]>=NUMV: %d", v[1]); v[1] = NUMV-1;}


     /*printf ("\nInput cieaccess() x %.3f  y %.3f  v[0] %d", x, y, v[0]);*/
     /* get corners of cube surrounding point in HVC space */
     u = cieaccess( x, y, &h[0], v[0], &c[0] ) ;
     /*printf ("\ncieaccess() u = %d", u);*/

     if(u < 0) {
       printf ("\nciemun() returned BADCIE");
       return( BADCIE );
     }
      
     h[1] = h[0]+1;

     if( h[1] == NUMH ) h[1] = 0;

     c[1] = c[0]+1;

     if( c[1] > NUMC ) c[1] = NUMC;


#ifdef (0)
     fprintf( stderr, "CIE (%f %f %f) %d-%d %d-%d %d-%d\n",
	     x,y,Y,h[0],h[1],v[0],v[1],c[0],c[1] );
#endif

     /* get corners of cube surrounding point in HVC space */
     for( j = 0 ; j < 2 ; j++ ) {

	  p [(j<<2)] [littlex] =  munciedata [v[j]] [h[0]] [c[0]] [littlex];
	  p [(j<<2)] [littley] =  munciedata [v[j]] [h[0]] [c[0]] [littley];

	  p [(j<<2)+1] [littlex] = munciedata [v[j]] [h[1]] [c[0]] [littlex];
	  p [(j<<2)+1] [littley] = munciedata [v[j]] [h[1]] [c[0]] [littley];

	  p [(j<<2)+2] [littlex] = munciedata [v[j]] [h[1]] [c[1]] [littlex];
	  p [(j<<2)+2] [littley] = munciedata [v[j]] [h[1]] [c[1]] [littley];

	  p [(j<<2)+3] [littlex] = munciedata [v[j]] [h[0]] [c[1]] [littlex];
	  p [(j<<2)+3] [littley] = munciedata [v[j]] [h[0]] [c[1]] [littley];
     }

     lerp( dv, p[0], p[4], ph[0] );
     lerp( dv, p[1], p[5], ph[1] );
     lerp( dv, p[2], p[6], ph[2] );
     lerp( dv, p[3], p[7], ph[3] );

     cieinterpolation( x, y, ph, ih, ic );
     
#ifdef (0)
     fprintf( stderr, "(%f %f) (%f %f) %f\n",ih[0],ic[0],ih[1],ic[1],dv);
#endif

     /* interpolate between values */
     *C = c[0] + ic[1] ;
     *H = h[0] + ih[1] ;
     *C *= 2.0;      /* go from 0-15 to 0-30 */
     *H *= 2.5;	/* go from 0-40 to 0-100 */    

}




cieaccess( x, y, h, v, c )
int	*h, v, *c;
float	x, y;
{
  /*register int i,j, munfd, code;*/
  int i, j, code;
  FILE *munfp;
  
  
  if( munsellinit == 0 ) {
    
    /*if( (munfd = open( bw_file(mundata), O_RDONLY ,0 )) < 0 ) {
      printf("muncie: I couldn't open %s\n", bw_file(mundata));
      return( -1 );
      }*/
    
    if ( (munfp = fopen (bw_file(mundata), "r")) == NULL) {
      printf("muncie: I couldn't open %s\n", bw_file(mundata));
      return(-1);
    }

    /*read( munfd, munciedata, NUMMUN );*/
    fread (munciedata, sizeof(float), NUMMUN, munfp);
    printf("\nREAD MUNCIEDATA");
    fclose (munfp);
    /*close( munfd );*/
    munsellinit = 1;
  }
  
  for( *h = 0 , i = 0 ; i < NUMH-1 ; (*h)++, i++ ) {
    for( *c=0, j=0, code=0 ; (j < NUMC-1) && (code!=-1) ; (*c)++, j++ ) {
      code = cieinside( munciedata[v][i][j], munciedata[v][i+1][j], munciedata[v][i+1][j+1], munciedata[v][i][j+1], x, y );
      
      if( code > 0 ) return( 0 );
    }
  }
  
  /* take care of hue wrap around */
  for( *c=0, j=0, code = 0 ; (j < NUMC-1) && (code!=-1) ; (*c)++, j++ ) {
    code = cieinside( munciedata[v][i][j], munciedata[v][i][j+1], munciedata[v][0][j+1], munciedata[v][0][j], x, y );
    

#ifdef DESPAIR
    fprintf( stderr, "%d %d %d\n",i,j,code);
#endif
    if( code > 0 ) return( 0 );
  }
  printf("\nAHA");  
  return( BADHVC );
} 



  
Y2v( y, v )
     float y, *v;
{
  /*     this subroutine solves the equation
   *     Y = 1.2219v -0.23111v**2 +0.23951v**3 -0.021009v**4 +0.0008404v**5
   *     for v in terms of a given Y.
   */

  int iter=15, i, j;
  float va, deriv, diff, funct, test, ttt, tol = 0.00001;
  
  *v = pow( (double)y, 0.5 );

  ciecoef[1]= -y;

  for( i=1 ; i <= iter ; i++ ) {
    funct=ciecoef[1];
    deriv=ciecoef[2];
    for( j=2 ; j<6 ; j++ ) {
      va = pow( *v, (double)(j-1) );
      funct = funct + (ciecoef[j] * va);
      ttt=j;   /* make sure next line is all float */
      deriv = deriv + (ttt * ciecoef[j+1] * va);
    }
    funct = funct + (ciecoef[6] * va * (*v));
    ttt = diff = funct/deriv;
    if (ttt < 0.0) ttt = -ttt;
    test = tol - ttt;
    *v -= diff;
    if (test > 0.0) break;
  }

  return( 0 );
}




/* quick & dirty */
int cieinside( a, b, c, d, x, y )
float a[2],b[2],c[2],d[2],x,y;
{
  float ciemin(), ciemax(), xc[4], yc[4];



  if(( a[littlex] == x) && ( a[littley] == y)) return(1);
  if(( b[littlex] == x) && ( b[littley] == y)) return(1);
  if(( c[littlex] == x) && ( c[littley] == y)) return(1);
  if(( d[littlex] == x) && ( d[littley] == y)) return(1);
  
  /* fail on 0.0 test */
  if( a[littlex] == 0.0 ) return( -1 );
  if( b[littlex] == 0.0 ) return( -1 );
  if( c[littlex] == 0.0 ) return( -1 );
  if( d[littlex] == 0.0 ) return( -1 );
  if( a[littley] == 0.0 ) return( -1 );
  if( b[littley] == 0.0 ) return( -1 );
  if( c[littley] == 0.0 ) return( -1 );
  if( d[littley] == 0.0 ) return( -1 );

  if( x < ciemin( a[littlex],b[littlex],c[littlex],d[littlex] ) ) return( 0 );
  if( x > ciemax( a[littlex],b[littlex],c[littlex],d[littlex] ) ) return( 0 );
  if( y < ciemin( a[littley],b[littley],c[littley],d[littley] ) ) return( 0 );
  if( y > ciemax( a[littley],b[littley],c[littley],d[littley] ) ) return( 0 );

/* do further (quadralateral) check here */
  xc[0] =  a[0]; yc[0] = a[1];
  xc[1] =  b[0]; yc[1] = b[1];
  xc[2] =  c[0]; yc[2] = c[1];
  xc[3] =  d[0]; yc[3] = d[1];


  return( cieinout( x, y, xc, yc ) );
}




float ciemin( a, b, c, d )
float a, b, c, d;
{
  float e, f;

  e = (a<b)?a:b;
  f = (c<d)?c:d;
  return( (e<f)?e:f );
}





float ciemax( a, b, c, d )
float a, b, c, d;
{
  float e, f;

  e = (a>b)?a:b;
  f = (c>d)?c:d;
  return( (e>f)?e:f );
}




int cieinout (x, y, xcoord, ycoord)
float x, y, xcoord[], ycoord[];
{
/*    this subroutine is used to determine whether or not the point
      with coordinates (x,y) lies inside the quadrilateral, the
      corners of which are given by the points (xcoord(i),ycoord(i)).
      It does that by the parity method.
*/

  float  diffx,diffy,prod,v1,v2,maxy,miny;
  float minx,maxx;
  int j,k[4],n,p,i,status,parity=0;
  
  for(j=0,i=0; j<4;j++){
       if(y == ycoord[j]) {	    
	    k[i]=j;
	    i++;
       }
  }
  parity = 0;
  if (i == 0){
       /***** staff: usual case ******/
       parity+= reg_cieinout(x, y, xcoord, ycoord,parity);
  }
  if (i == 1){ 
       
       j= k[0];
       if(xcoord[j] > x) parity+=reg_cieinout(x, y, xcoord, ycoord, parity); 
       else { 
	    p = (j == 3)?0:(j+1);
	    n = (j == 0)?3:(j-1);
	    maxy = (ycoord[p] > ycoord[n]) ? ycoord[p] : ycoord[n];
	    miny = (ycoord[p] < ycoord[n]) ? ycoord[p] : ycoord[n];
	    if( (y < miny) ||  (y > maxy)) 
	      parity ++ ;
	    parity+=reg_cieinout(x, y, xcoord, ycoord, parity);
       } 
  } 
  if (i == 2) {
       
       p = k[0];
       n = k[1];
       minx = (xcoord[p] < xcoord[n]) ? xcoord[p] : xcoord[n];
       maxx = (xcoord[p] > xcoord[n]) ? xcoord[p] : xcoord[n];
       if( (x >= minx) && (maxx >= x)) parity = 1;
  }
  
  while(parity>(-1)){
       if (parity==0) /* point outside */
	 return(0);
       parity-=2;
  }
  return(1);  /* point outside */
}



  

reg_cieinout(x, y, xcoord, ycoord,parity)
float x,y,xcoord[4],ycoord[4];
int parity;
{
  int i,j,k;
  float ratio,xcheck,maxy,miny;
  for (j = 0; j<4; j++) {
    k = (j == 3)?0:(j+1);
    maxy = (ycoord[j] > ycoord[k]) ? ycoord[j] : ycoord[k];
    miny = (ycoord[j] < ycoord[k]) ? ycoord[j] : ycoord[k];
    
    if ( y > maxy) continue;
    if ( y < miny) continue;
    
    ratio = (xcoord[j] - xcoord[k])/(ycoord[j]-ycoord[k]);
    xcheck = ratio * (y - ycoord[k]) + xcoord[k];
    if (x >= xcheck) 
      parity++;	
  }
  
  
  return(parity);
}





cieinterpolation( x, y, p, h, c)
float x, y, p[4][2], h[4], c[4];
{
/* this subroutine interpolates the values of deltahue & deltachroma
 * by doing the inverse interpolation of the one used in case in
 * muncie.c:
 *                                 |x00 y00|
 *              | 1-dc dc 0   0  | |x01 y01|                             
 *   |1-dh dh|  | 0     0 dc 1-dc| |x11 y11|  = |x[dh][dc] y[dh][dc]| =|x y|
 *                                 |x10 y10|
 */

  float  xy00[2],xy01[2],xy11[2],xy10[2],delta;
  float Det,e,z;
  float a1,a2,b1,b2,b3,b4,c1,c2;
  float D,F;
  int i,j,k;
  
  for( j = 0 ; j < 1 ; j++ ) {
    for( k = 0 ; k < 2 ; k++ ) {
      xy00[k] = p[0][k];   /* h,c */
      xy10[k] = p[1][k]; /* h+1,c */
      xy11[k] = p[2][k]; /* h+1,c+1 */
      xy01[k] = p[3][k]; /* h,c+1 */
    }
    /*if( cieinside( xy00,xy10,xy11,xy01, x, y ) == 0 ) {
      printf("OUTSIDE\n");
      }
      else printf("INSIDE\n");
      */
       	    
    a1 = (xy00[littlex] - xy10[littlex]) * (xy11[littley] - xy10[littley] + xy00[littley] - xy01[littley]);
    a2 = (xy10[littley] - xy00[littley]) * (xy11[littlex] - xy10[littlex] + xy00[littlex] - xy01[littlex]);
    
    b1 = (xy00[littlex] - xy10[littlex]) * (xy01[littley] - xy00[littley]);
    b2 = (x - xy00[littlex]) * (xy11[littley] - xy10[littley] + xy00[littley] - xy01[littley]);
    b3 = (xy01[littlex] - xy00[littlex]) * (xy10[littley] - xy00[littley]);
    b4 = (y - xy00[littley]) * (xy11[littlex] - xy10[littlex] + xy00[littlex] - xy01[littlex]);
    
    c1 = (x - xy00[littlex]) * (xy01[littley] - xy00[littley]);
    c2 = (y - xy00[littley]) * (xy01[littlex] - xy00[littlex]);
    
    a1 = a1 + a2;
    b1 = b1 + b2 + b3 - b4;
    c1 = c1 - c2;
    if( a1 ==0){
      h[1] = h[2]= - c1/b1;	   
    }
    else{
      delta = (b1 * b1) - 4 * a1 * c1;
      if (delta < 0) 
	if ((delta += .0000001) < 0) {		  
	  exit(-1);
	}
      D = sqrt((double)delta);
      
      h[1] = (D - b1)/ (2 * a1);
      h[2] = (- D - b1)/ (2 * a1);
    }
    for( i = 1; i < 3; i++){
      c[i] = ((x - xy00[littlex]) + h[i] * (xy00[littlex] - xy10[littlex])) / ((xy01[littlex] - xy00[littlex]) + h[i] *  (xy11[littlex]-xy10[littlex]+xy00[littlex]-xy01[littlex]));
    }
    /*
      printf("-b/a = %f\t : h[1]+h[2]=%f\t:\n",(-b1/a1),(h[1]+h[2]));       
      printf(" c/a = %f\t : h[1]*h[2]=%f\t:\n",(c1/a1),(h[1]*h[2]));
      for(i=1; i<3; i++){
      printf(" c[%d] = %f\t : h[%d] = %f\t :\n",i,c[i],i,h[i]);
      } 
      */
    D = c[1] * c[1] + h[1] * h[1];
    F = c[2] * c[2] + h[2] * h[2];
    if ( F < D) {
      c[1] = c[2];
      h[1] = h[2];
    }       
  }
  return( 0 );
}





lerp( a, p0, p1, p )
     float a, p0[2], p1[2], p[];
{
  register int	i;
  
  for( i = 0 ; i < 2 ; i++ )
    p[i] = p0[i] + (p1[i]-p0[i])*a;
  return( 0 );
}




