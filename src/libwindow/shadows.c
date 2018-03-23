/*
     shadows.c
     Steve Librande       11/6/91

     Attach this command onto a window to make a transparent shadow that
     follows a window around.  The shadow is actually two transparent windows,
     made by combining a horizontal and vertical window.
     The shadow's parent is always the same as the window's parent.

     
     Shadow messages:        Description:
     ------------------------------------------------------------------
     SHADOW_UPDATE           Updates the shadow.  This should be called
                                after a color or transparency change.
     SHADOW_OFF              Turns the shadow off by closing the transparent windows.
     SHADOW_ON               Turns the shadow on by opening the transparent windows.
     CHANGE_SHADOW_TRANS     Changes transparency of the shadow, but doesn't update.
     CHANGE_SHADOW_COLOR     Changes the color of the shadow.  Default is BLACK.
     CHANGE_SHADOW_OFFSET    Determines how far away the shadow lies from the window.
     CHANGE_SHADOW_POS       Changes the direction the shadow falls.  The options are
                              UP_AND_LEFT, UP_AND_RIGHT, DOWN_AND_RIGHT or DOWN_AND_LEFT.
			       
     Note: When changing the shadow's color or transparency value you must send a
           SHADOW_UPDATE message to see the effects.  However, if you change the
	   offset or the position then the change happens immediately, no update
	   message needs to be sent.

	   If a shadow is turned off, messages can still be sent to it, the changes
	   won't show up until the shadow is turned on again.  The SHADOW_UPDATE
	   message is ignored when the shadow is off.

     Bugs: Problems in TransRectify make the shadows draw and update with missing
           pixels.  Look close and you'll see 'em.  Don't blame me, fix TransRectify.

	   Windows with rounded corners will have square edged shadows.  Fix this by
	   writing a TransRoundRectify.

	   If a window is moved or resized from one location to the exact same location
	   its shadow won't update.
*/

#include <stdio.h>
#include <starbase.c.h>
#include <string.h>
#include <windows.c.h>
#include <structures.h>

#define X         0
#define Y         1
#define V_SHADOW  0
#define H_SHADOW  1
#define MIN_OFFSET        2
#define MAX_TRANSPARENCY  255

static int CheckPosition();
static int CheckTransparency();
static int CheckOffset();
static void ShadowSizeAndPos();
static int CheckForMove();
static void SetLastPosition();


/*
     TRANS SHADOWIFY
     Attaches a transparent drop shadow to a window.

     W is the window you want to attach the shadow to.

     The echo is the cursor you want over the shadows.
     
     The position of the drop shadow can be either UP_AND_LEFT (0),
        UP_AND_RIGHT (1), DOWN_AND_RIGHT (2) or DOWN_AND_LEFT (3).
			    
     The offset is between 2 and the smallest dimension of the window.
        (i.e., a window with dimensions 10 x 20 would have a maximum offset of 10)
        To make a window with a zero offset, (no shadow) send the SHADOW_OFF message.
	A bug in TransRectWin prevents an offset of 1.
	
     The transparency is between 0 (opaque) to 255 (invisible).
*/
struct transhadowStruct *
TransShadowify( W, echo, position, offset, transparency )
     struct Window *W;
     struct curstruct *echo;
     int position, offset, transparency;
{
  int TransShadowWin();
  
  struct transhadowStruct *parms;
  int max_offset,
      vertPos[ 2 ], vertSize[ 2 ],
      horizPos[ 2 ], horizSize[ 2 ];

  if ( W->parent == NULL ) {
    fprintf( stderr, "TransShadowify: cannot put a shadow on %s. (no parent)\n", W->tag );
    return( NULL );
  }
  else if ( W == NULL ) {
    fprintf( stderr, "TransShadowify: cannot put a shadow on a NULL window.\n" );
    return( NULL );
  }
  
  parms = (struct transhadowStruct *)malloc( sizeof( struct transhadowStruct ));

  parms->vertShadow   = NULL;
  parms->horizShadow  = NULL;
  parms->isShadowOn   = TRUE;
  parms->position     = CheckPosition( position );
  parms->offset       = CheckOffset( W, offset );
  parms->transparency = CheckTransparency( transparency );

  SetLastPosition( W, parms );

  ShadowSizeAndPos( W, parms->offset, parms->position, vertSize,  vertPos,  V_SHADOW );
  ShadowSizeAndPos( W, parms->offset, parms->position, horizSize, horizPos, H_SHADOW );

  parms->vertShadow =  (struct Window *)MakeWindow( W->display, W->input, W->parent,
		vertPos[ X ], vertPos[ Y ], vertSize[ X ], vertSize[ Y ], "vertShadow" );
  TransRectify( parms->vertShadow, 0,0,0, 0, 0,0,0, 0, parms->transparency );
  Wimp( parms->vertShadow );
  EchoWrap( parms->vertShadow, echo, JUSTDOWN | JUSTUP | BEENDOWN, 0, 0 );
  InstallWin( parms->vertShadow );

  
  parms->horizShadow = (struct Window *)MakeWindow( W->display, W->input, W->parent,
	horizPos[ X ], horizPos[ Y ], horizSize[ X ], horizSize[ Y ], "horizShadow" );
  TransRectify( parms->horizShadow, 0,0,0, 0, 0,0,0, 0, parms->transparency );
  Wimp( parms->horizShadow );
  EchoWrap( parms->horizShadow, echo, JUSTDOWN | JUSTUP | BEENDOWN, 0, 0 );
  InstallWin( parms->horizShadow );
  

  AttachCommand( W, DRAW,                 TransShadowWin, parms );
  AttachCommand( W, SHADOW_UPDATE,        TransShadowWin, parms );
  AttachCommand( W, SHADOW_OFF,           TransShadowWin, parms );
  AttachCommand( W, SHADOW_ON,            TransShadowWin, parms );
  AttachCommand( W, CHANGE_SHADOW_TRANS,  TransShadowWin, parms );
  AttachCommand( W, CHANGE_SHADOW_COLOR,  TransShadowWin, parms );
  AttachCommand( W, CHANGE_SHADOW_OFFSET, TransShadowWin, parms );
  AttachCommand( W, CHANGE_SHADOW_POS,    TransShadowWin, parms );
  return( parms );
}


TransShadowWin( W, id, data, stuff )
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct transhadowStruct *parms;
  static int newData;
  int vSize[ 2 ], vPos[ 2 ],
      hSize[ 2 ], hPos[ 2 ];

  parms = (struct transhadowStruct *)stuff;
  
  switch (id)
    {
    case DRAW:
      if ( CheckForMove( W, parms )) {
	SetLastPosition( W, parms );
	parms->offset = CheckOffset( W, parms->offset );
	ShadowSizeAndPos( W, parms->offset, parms->position, vSize, vPos, V_SHADOW );
	ShadowSizeAndPos( W, parms->offset, parms->position, hSize, hPos, H_SHADOW );
	if ( parms->isShadowOn ) {
	  CloseWindow( parms->vertShadow );
	  CloseWindow( parms->horizShadow );
	}
	
	/* Changes the shadow's parent if the shadowed window changes parents */
	if ( parms->vertShadow->parent != W->parent ) {
	  parms->horizShadow->parent  = W->parent;
	  parms->vertShadow->parent   = W->parent;
	  parms->horizShadow->display = W->display;
	  parms->vertShadow->display  = W->display;
	}

	TransformCoords( parms->vertShadow, vPos[ X ],vPos[ Y ], vSize[ X ],vSize[ Y ] );
	TransformCoords( parms->horizShadow,hPos[ X ],hPos[ Y ], hSize[ X ],hSize[ Y ] );
	if ( parms->isShadowOn ) {
	  OpenWindow( parms->vertShadow );
	  OpenWindow( parms->horizShadow );
	}
      }
      break;
	
    case SHADOW_UPDATE:
      parms->offset = CheckOffset( W, parms->offset );
      ShadowSizeAndPos( W, parms->offset, parms->position, vSize, vPos, V_SHADOW );
      ShadowSizeAndPos( W, parms->offset, parms->position, hSize, hPos, H_SHADOW );
      if ( parms->isShadowOn ) {
	CloseWindow( parms->vertShadow );
	CloseWindow( parms->horizShadow );
      }

      /* Changes the shadow's parent if the shadowed window changes parents */
      if ( parms->vertShadow->parent != W->parent ) {
	parms->horizShadow->parent  = W->parent;
	parms->vertShadow->parent   = W->parent;
	parms->horizShadow->display = W->display;
	parms->vertShadow->display  = W->display;
      }
      
      TransformCoords( parms->vertShadow, vPos[ X ], vPos[ Y ], vSize[ X ], vSize[ Y ] );
      TransformCoords( parms->horizShadow,hPos[ X ], hPos[ Y ], hSize[ X ], hSize[ Y ] );
      if ( parms->isShadowOn ) {
	OpenWindow( parms->vertShadow );
	OpenWindow( parms->horizShadow );
      }
      break;

    case SHADOW_OFF:
      parms->isShadowOn = FALSE;
      if ( parms->vertShadow->stat == OPENED ) {
	CloseWindow( parms->vertShadow );
	CloseWindow( parms->horizShadow );
      }
      break;

    case SHADOW_ON:
      parms->isShadowOn = TRUE;
      if ( parms->vertShadow->stat == CLOSED ) {
	OpenWindow( parms->vertShadow );
	OpenWindow( parms->horizShadow );
      }
      break;

    case CHANGE_SHADOW_OFFSET:
      newData = *(int *)data;
      parms->offset = CheckOffset( W, newData );
      SendMessage( W, SHADOW_UPDATE, NULL );
      break;

    case CHANGE_SHADOW_POS:
      newData = *(int *)data;
      parms->position = CheckPosition( newData );
      SendMessage( W, SHADOW_UPDATE, NULL );
      break;

    case CHANGE_SHADOW_TRANS:
      newData = CheckTransparency( *(int *)data );
      parms->transparency = newData;
      SendMessage( parms->vertShadow,  TR_CHANGETRANS, (char *)&newData );
      SendMessage( parms->horizShadow, TR_CHANGETRANS, (char *)&newData );
      break;

    case CHANGE_SHADOW_COLOR:
      SendMessage( parms->vertShadow,  NEWCOLOR, data );
      SendMessage( parms->horizShadow, NEWCOLOR, data );
      break;

    default:
      fprintf( stderr, "TransShadowWin: cannot process command id = %d\n", id );
    }
}




/*
     SHADOW SIZE AND POS
     Calculates the appropriate size and position for a shadow on a given window W.
     Offset is how far the shadow is from the window.
     Position is UP_AND_LEFT, UP_AND_RIGHT, DOWN_AND_LEFT, or DOWN_AND_RIGHT.
     Size and pos are arrays of 2 integer x,y pairs.
     Direction is either H_SHADOW or V_SHADOW to determine which part of the
       shadow to calculate.
*/
static void ShadowSizeAndPos( W, offset, position, size, pos, direction )
     struct Window *W;
     int offset, position, direction;
     int *size, *pos;
{
  switch ( direction ) {
  case ( VERTICAL ):
    size[ X ] = offset;
    size[ Y ] = W->height - offset;
    switch ( position ) {
    case ( UP_AND_RIGHT ):
      pos[ X ]  = W->relx + W->width;
      pos[ Y ]  = W->rely;
      break;
    case ( UP_AND_LEFT ):
      pos[ X ]  = W->relx - offset;
      pos[ Y ]  = W->rely;
      break;
    case ( DOWN_AND_RIGHT ):
      pos[ X ]  = W->relx + W->width;
      pos[ Y ]  = W->rely + offset;
      break;
    case ( DOWN_AND_LEFT ):
      pos[ X ]  = W->relx - offset;
      pos[ Y ]  = W->rely + offset;
      break;
    }
    break;

  case ( HORIZONTAL ):
    size[ X ] = W->width;
    size[ Y ] = offset;
    switch ( position ) {
    case ( UP_AND_RIGHT ):
      pos[ X ] = W->relx + offset;
      pos[ Y ] = W->rely - offset;
      break;
    case ( UP_AND_LEFT ):
      pos[ X ] = W->relx - offset;
      pos[ Y ] = W->rely - offset;
      break;
    case ( DOWN_AND_RIGHT ):
      pos[ X ] = W->relx + offset;
      pos[ Y ] = W->rely + W->height;
      break;
    case ( DOWN_AND_LEFT ):
      pos[ X ] = W->relx - offset;
      pos[ Y ] = W->rely + W->height;
      break;
    }
    break;
  }
}


static int CheckPosition( pos )
     int pos;
{
  if (( pos == UP_AND_RIGHT ) || ( pos == UP_AND_LEFT )
       || ( pos == DOWN_AND_RIGHT ) || ( pos == DOWN_AND_LEFT ))
    return( pos );
  else
    return( DOWN_AND_RIGHT );
}


static int CheckTransparency( trans )
     int trans;
{
  if ( trans < 0 )
    return( 0 );
  else if ( trans > MAX_TRANSPARENCY )
    return( MAX_TRANSPARENCY );
  else
    return( trans );
}


/*
    The offset of the shadow cannot be > the minimum dimension of the window.
    Also, because of a bug in transparent rectify, a window cannot have an
    offset of 1, so 2 is the minimum.
*/    
static int CheckOffset( W, offset )
     struct Window *W;
     int offset;
{
  int max_offset = MIN( W->width, W->height );

  if ( offset < MIN_OFFSET )
    return( MIN_OFFSET );
  else if ( offset > max_offset )
    return( max_offset );
  else 
    return( offset );
}


/*
     Returns 1 if the window moved, 0 if it hasn't.
*/     
static int CheckForMove( W, shadowStruct )
     struct Window *W;
     struct transhadowStruct *shadowStruct;
{
  return( ! (( W->relx == shadowStruct->lastX1 ) &&
	     ( W->rely == shadowStruct->lastY1 ) &&
	     ( W->relx + W->width  == shadowStruct->lastX2 ) &&
	     ( W->rely + W->height == shadowStruct->lastY2 )));
}

static void SetLastPosition( W, shadowStruct )
     struct Window *W;
     struct transhadowStruct *shadowStruct;
{
  shadowStruct->lastX1 = W->relx;
  shadowStruct->lastY1 = W->rely;
  shadowStruct->lastX2 = W->relx + W->width;
  shadowStruct->lastY2 = W->rely + W->height;
}


#undef X         
#undef Y         
#undef V_SHADOW  
#undef H_SHADOW  
#undef MIN_OFFSET
#undef MAX_TRANSPARENCY
