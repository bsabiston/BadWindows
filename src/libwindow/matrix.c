

/******************************************************************************
Copyright 1990 by the Massachusetts Institute of Technology.  All 
rights reserved.

Developed by the Visible Language Workshop at the Media Laboratory, MIT, 
Cambridge, Massachusetts, with support from Hewlett Packard, DARPA, and Nynex.

For use by Suguru Ishizaki.  
This distribution is approved by Nicholas Negroponte, Director of 
the Media Laboratory, MIT.

Permission to use, copy, or modify these programs and their 
documentation for educational and research purposes only and 
without fee is hereby granted, provided that this copyright notice 
appears on all copies and supporting documentation.  For any other 
uses of this software, in original or modified form, including but not 
limited to distribution in whole or in part, specific prior permission 
must be obtained from MIT.  These programs shall not be used, 
rewritten, or adapted as the basis of a commercial software or 
hardware product without first obtaining appropriate licenses from 
MIT.  MIT makes no representations about the suitability of this 
software for any purpose.  It is provided "as is" without express or 
implied warranty."
******************************************************************************/





#include <stdio.h>
#include <math.h>

#define PI (float)3.141592


/********************* matrix manipulation functions ***********************/

MatPrint(M)
float M[4][4];
   {
   printf(" %4f  %4f  %4f  %4f\n",M[0][0],M[0][1],M[0][2],M[0][3]);
   printf(" %4f  %4f  %4f  %4f\n",M[1][0],M[1][1],M[1][2],M[1][3]);
   printf(" %4f  %4f  %4f  %4f\n",M[2][0],M[2][1],M[2][2],M[2][3]);
   printf(" %4f  %4f  %4f  %4f\n",M[3][0],M[3][1],M[3][2],M[3][3]);
   }


MakeIdentity(M)
float M[4][4];
   {
   M[0][0] = M[1][1] = M[2][2] = M[3][3] = 1.0;
   M[0][1] = M[0][2] = M[0][3] = 0.0;
   M[1][0] = M[1][2] = M[1][3] = 0.0;
   M[2][0] = M[2][1] = M[2][3] = 0.0;
   M[3][0] = M[3][1] = M[3][2] = 0.0;
   }

CopyMatrix(A,B)
float A[4][4],B[4][4];
   {
   B[0][0] = A[0][0]; B[0][1] = A[0][1]; B[0][2] = A[0][2]; B[0][3] = A[0][3];
   B[1][0] = A[1][0]; B[1][1] = A[1][1]; B[1][2] = A[1][2]; B[1][3] = A[1][3];
   B[2][0] = A[2][0]; B[2][1] = A[2][1]; B[2][2] = A[2][2]; B[2][3] = A[2][3];
   B[3][0] = A[3][0]; B[3][1] = A[3][1]; B[3][2] = A[3][2]; B[3][3] = A[3][3];
   }

InterpolateMatrix(A,B,C,r)
float A[4][4],B[4][4],C[4][4],r;
   {
   C[0][0] = (B[0][0]-A[0][0])*r + A[0][0]; C[0][1] = (B[0][1]-A[0][1])*r + A[0][1];
       C[0][2] = (B[0][2]-A[0][2])*r + A[0][2]; C[0][3] = (B[0][3]-A[0][3])*r + A[0][3];
   C[1][0] = (B[1][0]-A[1][0])*r + A[1][0]; C[1][1] = (B[1][1]-A[1][1])*r + A[1][1];
       C[1][2] = (B[1][2]-A[1][2])*r + A[1][2]; C[1][3] = (B[1][3]-A[1][3])*r + A[1][3];
   C[2][0] = (B[2][0]-A[2][0])*r + A[2][0]; C[2][1] = (B[2][1]-A[2][1])*r + A[2][1];
       C[2][2] = (B[2][2]-A[2][2])*r + A[2][2]; C[2][3] = (B[2][3]-A[2][3])*r + A[2][3];
   C[3][0] = (B[3][0]-A[3][0])*r + A[3][0]; C[3][1] = (B[3][1]-A[3][1])*r + A[3][1];
       C[3][2] = (B[3][2]-A[3][2])*r + A[3][2]; C[3][3] = (B[3][3]-A[3][3])*r + A[3][3];
   }

Translate(M,x,y,z,c)
float M[4][4],x,y,z;
int c;
   {
   float temp[4][4];
   if (c)
      {
      MakeIdentity(temp);
      temp[3][0] = x;
      temp[3][1] = y;
      temp[3][2] = z;
      Concat(M,temp,M);
      }

   else {
        MakeIdentity(M);
        M[3][0] = x;
        M[3][1] = y;
        M[3][2] = z;
        }
   }



Scale(M,x,y,z,c)

float M[4][4],x,y,z;
int c;
   {
   float temp[4][4];
   if (c)
      {
      MakeIdentity(temp);
      temp[0][0] = x;
      temp[1][1] = y;
      temp[2][2] = z;
      Concat(M,temp,M);
      }
   else {
        MakeIdentity(M);
        M[0][0] = x;
        M[1][1] = y;
        M[2][2] = z;
        }
   }


Rotate(M,x,y,z,c)

float M[4][4],x,y,z;
int c;
   {
   float temp[4][4];
   if (c)
      {
      Rotate(temp,x,y,z,0);
      Concat(M,temp,M);
      }
   else {
        Rotx(M,x,0);
        Roty(M,y,1);
        Rotz(M,z,1);
        } 
   }


Rotz(M,z,c)

float M[4][4],z;
int c;
   {
   float temp[4][4];
   float cosz,sinz,za;

   za = z*PI/180.0;

   cosz = (float)(cos((float)za));
   sinz = (float)(sin((float)za));
   if (c)
      {
      Rotz(temp,z,0);
      Concat(M,temp,M);
      }
   else {
        MakeIdentity(M);
        M[0][0] = cosz;
        M[0][1] = sinz;
        M[1][0] = -sinz;
        M[1][1] = cosz;    
        }
   }


Rotx(M,x,c)

float M[4][4],x;
int c;
   {
   float temp[4][4];
   float cosx,sinx,xa;

   xa = x*PI/180.0;

   cosx = (float)(cos((float)xa));
   sinx = (float)(sin((float)xa));
   if (c)
      {
      Rotx(temp,x,0);
      Concat(M,temp,M);
      }
   else {
        MakeIdentity(M);
        M[1][1] = cosx;
        M[1][2] = sinx;
        M[2][1] = -sinx;
        M[2][2] = cosx;    
        }
   }



Roty(M,y,c)

float M[4][4],y;
int c;
   {
   float temp[4][4];
   float cosy,siny,ya;

   ya = y*PI/180.0;

   cosy = (float)(cos((float)ya));
   siny = (float)(sin((float)ya));
   if (c)
      {
      Roty(temp,y,0);
      Concat(M,temp,M);
      }
   else {
        MakeIdentity(M);
        M[2][2] = cosy;
        M[2][0] = siny;
        M[0][2] = -siny;
        M[0][0] = cosy;    
        }
   }


ConcatVector(ax,ay,az,ah,N,bx,by,bz,bh)
float ax,ay,az,ah,N[4][4],*bx,*by,*bz,*bh;
{
   float rn0,rn1,rn2,rn3;

       rn0 = ax*N[0][0]+ay*N[1][0]+az*N[2][0]+ah*N[3][0];
       rn1 = ax*N[0][1]+ay*N[1][1]+az*N[2][1]+ah*N[3][1];
       rn2 = ax*N[0][2]+ay*N[1][2]+az*N[2][2]+ah*N[3][2];
       rn3 = ax*N[0][3]+ay*N[1][3]+az*N[2][3]+ah*N[3][3];
       *bx = rn0;
       *by = rn1;
       *bz = rn2;
       *bh = rn3;

}


PConcat(M,N,R,n)
float *M,N[4][4],*R;
int n;
   {
   float rn0,rn1,rn2,rn3;
   int c;
   
   for (c=0; c<n;c++)
       {
       rn0 = M[c*4]*N[0][0]+M[c*4+1]*N[1][0]+M[c*4+2]*N[2][0]+M[c*4+3]*N[3][0];
       rn1 = M[c*4]*N[0][1]+M[c*4+1]*N[1][1]+M[c*4+2]*N[2][1]+M[c*4+3]*N[3][1];
       rn2 = M[c*4]*N[0][2]+M[c*4+1]*N[1][2]+M[c*4+2]*N[2][2]+M[c*4+3]*N[3][2];
       rn3 = M[c*4]*N[0][3]+M[c*4+1]*N[1][3]+M[c*4+2]*N[2][3]+M[c*4+3]*N[3][3];
       R[c*4] = rn0;
       R[c*4+1] = rn1;
       R[c*4+2] = rn2;
       R[c*4+3] = rn3;
       }

   }

Concat(M,N,R)
float M[4][4],N[4][4],R[4][4];
   {
   PConcat(M,N,R,4);  
   } 


Cross (a, b, c)

float a[3],b[3],c[3];
{
   c[0] = (a[1] * b[2] - (a[2] * b[1]));
   c[1] = (a[2] * b[0] - (a[0] * b[2]));
   c[2] = (a[0] * b[1] - (a[1] * b[0]));
} 

CullVector(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4)
float x1,y1,z1,x2,y2,z2,x3,y3,z3,*x4,*y4,*z4;
{
float a[3],b[3],c[3];

a[0] = x1-x2; b[0] = x3 -x2;
a[1] = y1-y2; b[1] = y3 -y2;
a[2] = z1-z2; b[2] = z3 -z2;
Cross(a,b,c);
*x4 = c[0];
*y4 = c[1];
*z4 = c[2];

if ((*x4)||(*y4)||(*z4)) return(1);
else return(0);

}


float NoVectorDot(ax,ay,az,bx,by,bz)
float ax,ay,az,bx,by,bz;
{
  float c;
  
  c = ax*bx + ay*by +az*bz;
  return(c);
}


float Dot (a, b)

float a[3],b[3];
{
   int i;
   float c;
   
   c = 0;

   for (i=0; i<3; ++i)
       c += a[i] * b[i];

   return (c);
 }


NoVectorCross (ax,ay,az, bx,by,bz, cx,cy,cz)
float ax,ay,az,bx,by,bz,*cx,*cy,*cz;
{
   *cx = ay * bz - az * by;
   *cy = az * bx - ax * bz;
   *cz = ax * by - ay * bx;
} 


Normalize(x,y,z)
float *x,*y,*z;
{
float l;
l = sqrt(*x * *x + *y * *y + *z * *z);
*x /= l;
*y /= l;
*z /= l;
}
