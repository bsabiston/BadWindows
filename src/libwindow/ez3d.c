/* **************************** */ 
/* EZ 3D                        */
/* simple 3d viewport display   */
/* **************************** */   

#include <stdio.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>
#include <math.h>
#include "ez3d.h"
#define Gray(Level) Level, Level, Level 


/* Attach the first of two DRAW functions to a window.  Use the starbase camera
   structure as the stuff. */

Camera3D_On(W,scam)
struct Window *W;
camera_arg *scam;
{
  int Cam3D_On(), Cam3D_Commands();
  AttachCommand(W,DRAW,Cam3D_On,scam);
  AttachCommand(W,VP_GET_CAMERA,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_X,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_Y,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_Z,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_FRONT,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_BACK,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_FOV,Cam3D_Commands,scam);
  AttachCommand(W,VP_SET_PROJ,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_X,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_Y,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_Z,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_FRONT,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_BACK,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_FOV,Cam3D_Commands,scam);
  AttachCommand(W,VP_ADD_PROJ,Cam3D_Commands,scam);
}


Camera3D_Off(W)
struct Window *W;
{
  int Cam3D_Off();
  AttachCommand(W,DRAW,Cam3D_Off,NULL);
  return(0);
}



Cam3D_On(W,id,data,stuff)
struct Window *W;
char *data,*stuff;
int id;
{
  struct clipstruct *cstruct;
  camera_arg *scam;
  int screen, cx1, cx2, cy1, cy2, times;
  static float smatrix[4][4] = {1.0, 0.0, 0.0, 0.0, 
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, -1.0,0.0,
				0.0, 0.0, 0.0, 1.0};

  screen = (W->display)->fildes;
  switch (id)    {
    case(DRAW):
    cstruct = (struct clipstruct *)data;

    cx1 = cstruct->x1;
    cy1 = cstruct->y1;
    cx2 = cstruct->x2;
    cy2 = cstruct->y2;

    clip_rectangle(screen, (float)cx1, (float)cx2, (float)cy1, (float)cy2);

  default:
    cx1 = W->x1;
    cy1 = W->y1;
    cx2 = W->x2;
    cy2 = W->y2;

    scam = (camera_arg *)stuff;

    /* Set Up camera */

    flush_matrices(screen);
    view_camera(screen,scam);
    view_port(screen,(float)W->x1,(float)W->y2,(float)W->x2,(float)W->y1); 
/*     view_matrix3d (screen, smatrix, PRE_CONCAT_VW);  for right/left coordinate switch */ 
    times = hidden_surface(screen,TRUE,TRUE);
    if (times >1) printf("OH NO! This scene needs to render more than once!!!\n");
    zbuffer_switch(screen,1);

    break;
  }
}




Cam3D_Off(W,id,data,stuff)
struct Window *W;
char *data,*stuff;
int id;
{
  int screen;

  screen = (W->display)->fildes;
  switch (id)    {
    case(DRAW):
    default:
      /* Undo camera */

	   surface_model(screen,FALSE,1,1.0,1.0,1.0);
	   vertex_format(screen,0,0,0,FALSE,CLOCKWISE);
	   move3d(screen,0.0,0.0,0.0);
	   hidden_surface(screen,FALSE,FALSE);
	   light_switch(screen,1);
	   light_ambient(screen,1.0,1.0,1.0);

      flush_matrices(screen);

      clip_rectangle(screen, (float)0.0, (float)((W->display)->width-1),
		     0.0, (float)((W->display)->height-1));
      make_picture_current(screen);

    break;
  }
}


Cam3D_Commands(W,id,data,stuff)
struct Window *W;
int id;
char *data, *stuff;
{
  camera_arg *scam;
  scam = (camera_arg *)stuff;

  switch (id)
    {
    case (VP_GET_CAMERA):
      return(scam);
      break;
    default:
      break;
    }

  return(0);
}


camera_arg *GetCamera(refx,refy,refz,camx,camy,camz,upx,upy,upz,field_of_view,front,back,projection)
float refx,refy,refz,camx,camy,camz,upx,upy,upz,field_of_view,front,back;
int projection;
{
  camera_arg *cam;

  cam = (camera_arg *)malloc(sizeof(camera_arg));
  cam->refx = refx;
  cam->refy = refy;
  cam->refz = refz;
  cam->camx = camx;
  cam->camy = camy;
  cam->camz = camz;
  cam->upx = upx;
  cam->upy = upy;
  cam->upz = upz;
  cam->field_of_view = field_of_view;
  cam->front = front;
  cam->back = back;
  cam->projection = projection;

  return(cam);
}


camera_arg *DefaultCamera()
{
  camera_arg *cam;

  cam = (camera_arg *)malloc(sizeof(camera_arg));
  cam->refx = 0.0;
  cam->refy = 0.0;
  cam->refz = 0.0;
  cam->camx = 0.0;
  cam->camy = 0.0;
  cam->camz = 10.0; 
  cam->upx = 0.0;
  cam->upy = 1.0;
  cam->upz = 0.0;
  cam->field_of_view = 45.0;
  cam->front = -20.0;
  cam->back = 200.0;
  cam->projection = CAM_PERSPECTIVE;

  return(cam);
}


/* ********************* */
/* PIVOTING CAMERA MODEL */
/* ********************* */

/* Attach front-end to camera model, for doing circular pivots around reference point */
Pivotify(W,scam) 
struct Window *W;
camera_arg *scam;
{
  int Pivot_Commands();
  struct pivot_struct *p;

  p = (struct pivot_struct *)malloc(sizeof(struct pivot_struct));
  p->scam = scam;
  p->tilt = 0.0;

  AttachCommand(W,PV_SET_SCAM, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_READ_SCAM, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_ADD_THETA, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_ADD_PHI, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_ADD_TILT, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_ADD_DISTANCE, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_SET_THETA, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_SET_PHI, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_SET_TILT, Pivot_Commands,(char *)p);
  AttachCommand(W,PV_SET_DISTANCE, Pivot_Commands,(char *)p);

  SendMessage(W,PV_READ_SCAM,NULL);
  return (0);
}


Pivot_Commands(W,id,data,stuff)
struct Window *W;
char *data,*stuff;
int id;
{
  struct pivot_struct *p;
  camera_arg *scam;
  float f;
  
  p = (struct pivot_struct *)stuff;
  scam = p->scam;

  switch (id)
    {
    case (PV_READ_SCAM):
      Reverse_Compute_Cam(p);
      break;

    case (PV_SET_SCAM):
      Compute_Cam(p);
      break;
 
    case (PV_ADD_THETA):
      f = *((float *)data);
      p->theta += f;
      break;

    case (PV_ADD_PHI):
      f = *((float *)data);
      p->phi += f;
      break;

    case (PV_ADD_TILT):
      f = *((float *)data);
      p->tilt += f;
      break;

    case (PV_ADD_DISTANCE):
      f = *((float *)data);
      if (p->distance + f)
	p->distance += f;
      break;

    case (PV_SET_THETA):
      f = *((float *)data);
      p->theta = f;
      break;

    case (PV_SET_PHI):
      f = *((float *)data);
      p->phi = f;
      break;

    case (PV_SET_TILT):
      f = *((float *)data);
      p->tilt = f;
      break;

    case (PV_SET_DISTANCE):
      f = *((float *)data);
      if (p->distance)
	p->distance = f;
      break;

   default:
      break;
    }

  return(0);
}


/* set the values in scam according to angles in pivot_struct */

Compute_Cam(parms)
struct pivot_struct *parms;
{
  camera_arg *cam;
  float cx,cy,cz,cval,sval,l;

  cam = parms->scam;

      cam->camx = parms->distance*cos(parms->phi*M_PI/180.0)*sin(parms->theta*M_PI/180.0);
      cam->camy = parms->distance*sin(parms->phi*M_PI/180.0);
      cam->camz = parms->distance*cos(parms->phi*M_PI/180.0)*cos(parms->theta*M_PI/180.0);
      cam->upx = parms->distance*cos(parms->phi*M_PI/180.0+M_PI/2.0)*sin(parms->theta*M_PI/180.0);
      cam->upy = parms->distance*sin(parms->phi*M_PI/180.0+M_PI/2.0);
      cam->upz = parms->distance*cos(parms->phi*M_PI/180.0+M_PI/2.0)*cos(parms->theta*M_PI/180.0);
      NoVectorCross(cam->camx,cam->camy,cam->camz,cam->upx,cam->upy,cam->upz,&cx,&cy,&cz);

      Normalize(&cx,&cy,&cz);
      Normalize(&cam->upx,&cam->upy,&cam->upz);
      cval = cos(parms->tilt*M_PI/180.0);
      sval = sin(parms->tilt*M_PI/180.0);

      cam->upx = (cval*cam->upx+sval*cx);
      cam->upy = (cval*cam->upy+sval*cy);
      cam->upz = (cval*cam->upz+sval*cz);

      cam->camx += cam->refx;
      cam->camy += cam->refy;
      cam->camz += cam->refz;
}


Reverse_Compute_Cam(parms)
struct pivot_struct *parms;
{
  /* change coordinates from old camera mode */
  double newx,newy,newz,length;
  camera_arg *cam;

  cam = parms->scam;
  newx = (double)(cam->camx-cam->refx);
  newy = (double)(cam->camy-cam->refy);
  newz = (double)(cam->camz-cam->refz);
  length = sqrt(newx*newx + newy*newy +newz*newz);
  parms->theta = (atan2(newx,newz))*180/M_PI;
  parms->phi = (asin(newy/length))*180/M_PI;
  parms->distance = length;

}


set_lights(display)
int display;
{

  light_ambient(display, Gray(.15));
  light_source(display, 1, DIRECTIONAL, Gray(1.0), -10.0, 10.0, 10.0);  
/*  light_source(display, 2, DIRECTIONAL, Gray(0.8), -5.0, -12.0, -10.0);  
  light_source(display, 3, DIRECTIONAL, Gray(0.6), 10.0, 0.0, 0.0);  
  light_source(display, 4, DIRECTIONAL, Gray(0.8), -20.0, -20.0, 20.0);
*/
  light_switch(display, 3);
}

DrawTarget(screen)
int screen;
{
  float fr,fg,fb,tx,ty,tz;
  
  tx = 0.0;
  ty = 0.0;
  tz = 0.0;
  line_color(screen,0.1,0.1,0.6);
  curve_resolution(screen,1,8.0,8.0,6.0,6.0);
  interior_style(screen,INT_HOLLOW,TRUE);
  perimeter_color(screen,0.6,0.6,0.6);
  move3d(screen,tx-300.0,ty,tz);
  draw3d(screen,tx+300.0,ty,tz);
  
  move3d(screen,tx,ty-300.0,tz);
  draw3d(screen,tx,ty+300.0,tz);
  
  move3d(screen,tx,ty,tz-300.0);
  draw3d(screen,tx,ty,tz+300.0);

  move3d(screen,tx,ty,tz);
  line_color(screen,0.2,0.2,0.8);
  arc(screen,4.0,4.0,tx,ty,0.0,2.0*3.14159,0.0,2);
  make_picture_current(screen);
}



/* ******************* */
/* TRANSFORMATION      */
/* MATRIX              */
/* WINDOW FUNCTIONS    */
/* ******************* */

PushMatrix(W)
struct Window *W;
{
  int Matrix_Commands(), AttachMatrix();
  struct transform_struct *t;

  t = (struct transform_struct *)malloc(sizeof(struct transform_struct));

  AttachCommand(W,DRAW,AttachMatrix,(char *)t);

  AttachCommand(W,TRANS_ADD_X, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_Y, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_Z, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_RX, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_RY, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_RZ, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_SX, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_SY, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_ADD_SZ, Matrix_Commands,(char *)t);

  AttachCommand(W,TRANS_SET_X, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_Y, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_Z, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_RX, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_RY, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_RZ, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_SX, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_SY, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_SZ, Matrix_Commands,(char *)t);

  AttachCommand(W,TRANS_INIT, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_COMPUTE_MAT, Matrix_Commands,(char *)t);
  AttachCommand(W,TRANS_SET_MAT, Matrix_Commands,(char *)t);

  SendMessage(W,TRANS_INIT,NULL);
  return (0);
}


PopMatrix(W)
struct Window *W;
{
  int DetachMatrix();
  AttachCommand(W,DRAW,DetachMatrix,NULL);
  return(0);
}



AttachMatrix(W,id,data,stuff)
struct Window *W;
int id;
unsigned char *data, *stuff;
{
  struct transform_struct *t;
  t = (struct transform_struct *)stuff;
  if (t->new)
    {
      Scale(t->mat,t->sx,t->sy,t->sz,0);
      Rotate(t->mat,t->rx,t->ry,t->rz,1);
      Translate(t->mat,t->x,t->y,t->z,1);
      t->new = 0;
    }
  concat_transformation3d(W->display->fildes,t->mat,PRE,PUSH);
  return(0);
}

DetachMatrix(W,id,data,stuff)
struct Window *W;
int id;
unsigned char *data, *stuff;
{
  pop_matrix(W->display->fildes);
  return(0);
}

Matrix_Commands(W,id,data,stuff)
struct Window *W;
int id;
unsigned char *data, *stuff;
{
  struct transform_struct *t;
  float *M, f;

  t = (struct transform_struct *)stuff;

  switch (id)
    {
    case (TRANS_INIT):
      t->x = t->y = t->z = 0.0;
      t->rx = t->ry = t->rz = 0.0;
      t->sx = t->sy = t->sz = 1.0;
      MakeIdentity(t->mat);
      t->new = 0;
      break;

    case (TRANS_SET_MAT):
      M = (float *) data;
      CopyMatrix(M, t->mat);
      break;

    case (TRANS_COMPUTE_MAT):
       Scale(t->mat,t->sx,t->sy,t->sz,0);
       Rotate(t->mat,t->rx,t->ry,t->rz,1);
       Translate(t->mat,t->x,t->y,t->z,1);
       t->new = 0;
      break;

    case (TRANS_ADD_X):
      f = *((float *)data);
      t->x += f;
      t->new = 1;
      break;
    case (TRANS_ADD_Y):
      f = *((float *)data);
      t->y += f;
      t->new = 1;
      break;
    case (TRANS_ADD_Z):
      f = *((float *)data);
      t->z += f;
      t->new = 1;
      break;
    case (TRANS_ADD_RX):
      f = *((float *)data);
      t->rx += f;
      t->new = 1;
      break;
    case (TRANS_ADD_RY):
      f = *((float *)data);
      t->ry += f;
      t->new = 1;
      break;
    case (TRANS_ADD_RZ):
      f = *((float *)data);
      t->rz += f;
      t->new = 1;
      break;
    case (TRANS_ADD_SX):
      f = *((float *)data);
      t->sx += f;
      t->new = 1;
      break;
    case (TRANS_ADD_SY):
      f = *((float *)data);
      t->sy += f;
      t->new = 1;
      break;
    case (TRANS_ADD_SZ):
      f = *((float *)data);
      t->sz += f;
      t->new = 1;
      break;

    case (TRANS_SET_X):
      f = *((float *)data);
      t->x = f;
      t->new = 1;
      break;
    case (TRANS_SET_Y):
      f = *((float *)data);
      t->y = f;
      t->new = 1;
      break;
    case (TRANS_SET_Z):
      f = *((float *)data);
      t->z = f;
      t->new = 1;
      break;
    case (TRANS_SET_RX):
      f = *((float *)data);
      t->rx = f;
      t->new = 1;
      break;
    case (TRANS_SET_RY):
      f = *((float *)data);
      t->ry = f;
      t->new = 1;
      break;
    case (TRANS_SET_RZ):
      f = *((float *)data);
      t->rz = f;
      t->new = 1;
      break;
    case (TRANS_SET_SX):
      f = *((float *)data);
      t->sx = f;
      t->new = 1;
      break;
    case (TRANS_SET_SY):
      f = *((float *)data);
      t->sy = f;
      t->new = 1;
      break;
    case (TRANS_SET_SZ):
      f = *((float *)data);
      t->sz = f;
      t->new = 1;
      break;

   default:
      break;
    }

  return(0);
}



TrackLights(W,id,data,stuff)
struct Window *W;
int id;
char *data, *stuff;
{
  int display;
  float x,y,z, nx,ny,nz,cx,cy,cz;
  camera_arg *scam;

  display = W->display->fildes;
  scam = (camera_arg *)stuff;
  CullVector(scam->camx,scam->camy,scam->camz,0.0,0.0,0.0,scam->upx,scam->upy,scam->upz,&x,&y,&z);

  cx = scam->camx;
  cy = scam->camy;
  cz = scam->camz;
  Normalize(&x,&y,&z);
  Normalize(&cx,&cy,&cz);
  nx = (cx*3+scam->upx*4+x*2)/9.0;
  ny = (cy*3+scam->upy*4+y*2)/9.0;
  nz = (cz*3+scam->upz*4+z*2)/9.0;

  light_ambient(display, Gray(.3));
  light_source(display, 1, DIRECTIONAL, Gray(1.0), nx, ny,nz);
  light_source(display, 2, DIRECTIONAL, Gray(.5), -nx, -ny,-nz);
  light_source(display, 3, DIRECTIONAL, Gray(.3), -nx, -ny,nz);
  light_switch(display, 15);

  return(0);
}
