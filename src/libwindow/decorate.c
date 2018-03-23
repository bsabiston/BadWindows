/*
     decorate.c
     S. Librande      February 14, 1992

     DecorateWindow takes in a window and "decorates" it with bitmap images.
     The window is divided up into 9 sections, and each section can becomed
     patternified with a different bitmap.  The sections are labelled:

               +----+----------------------+----+
	       |    |                      |    |
	       | ul |        top           | ur |
	       |    |                      |    |
	       +----+----------------------+----+
	       |    |                      |    |
	       |    |                      | r  |
	       | l  |                      | i  |
	       | e  |       center         | g  |
	       | f  |                      | h  |
	       | t  |                      | t  |
	       |    |                      |    |
	       |    |                      |    |
	       +----+----------------------+----+
	       |    |                      |    |
	       | ll |       bottom         | lr |
	       |    |                      |    |
	       +----+----------------------+----+
	  
     To decorate a window, you must first create the bitmap images you wish
     to load using the Dave format (RGB in banks with height and width header
     of 8 bytes).  Then make a decor file which describes how the window is to
     be cut up and which bitmaps go where.  The file format is as follows:

               # optional comments
               x-border-size, y-border-size
	       
	       ul-bitmap-file      optional comments
	       ur-bitmap-file
	       lr-bitmap-file
	       ll-bitmap-file
	       
	       top-bitmap-file
	       right-bitmap-file
	       bottom-bitmap-file
	       left-bitmap-file
	       center-bitmap-file

     This file is read in, parsed and the appropriate bitmaps are Patternify-ed
     onto child windows.  The children are automatically Maker-ed, so if the window
     changes size the border size will remain constant.  Any line starting with a
     # character is considered to be a comment and is ignored.  Also, only the
     first string in each file name line is read in, any other strings after the
     first are treated as comments and discarded.

     If the x-border-size is less than 1, then only 3 windows will be made: the
     top, center and bottom.  If the y-border-size is less than 1, only 3 windows
     will be made: the left, center and right.  In either of these cases, only the
     first three bitmap file names will be read in from the decor file, the rest
     will be ignored.

     If the x-border-size or y-border-size are greater than the window size then
     the results are undefined.
*/


#include <stdio.h>
#include <starbase.c.h>
#include <string.h>
#include <windows.c.h>
#include <structures.h>

#define MAX_DECOR_SEGS   9
#define MAX_STRING_SIZE 64
#define DECOR_UL     1
#define DECOR_UR     2
#define DECOR_LR     3
#define DECOR_LL     4
#define DECOR_TOP    5
#define DECOR_RIGHT  6
#define DECOR_BOTTOM 7
#define DECOR_LEFT   8
#define DECOR_CENTER 9

#define DECOR_COMMENT_CHAR '#'

#define DECORNAME_UL     "decor ul corner"
#define DECORNAME_UR     "decor ur corner"
#define DECORNAME_LR     "decor lr corner"
#define DECORNAME_LL     "decor ll corner"
#define DECORNAME_TOP    "decor top edge"
#define DECORNAME_RIGHT  "decor right edge"
#define DECORNAME_BOTTOM "decor bottom edge"
#define DECORNAME_LEFT   "decor left edge"
#define DECORNAME_CENTER "decor center"


static int ParseDecorFile();
static int LoadBitmapPatterns();

static struct curstruct
  *curpattern[ MAX_DECOR_SEGS + 1 ];   /* index 0 is left open */

static int
  x_border,
  y_border,
  num_of_segs;


/*
     DECORATE WINDOW
     See the header of this file for a full description.
*/     
int DecorateWindow( W, echo, decorfileName )
     struct Window *W;
     struct curstruct *echo;
     char *decorfileName;
{
  struct Window *ul,
                *ur,
                *lr,
                *ll,
                *top,
                *right,
                *bottom,
                *left,
                *center;
  int x_edgesize,
      y_edgesize,
      result;
  


  if (( result = ParseDecorFile( decorfileName )) != 0 ) {
    if ( result == -1 )
      fprintf( stderr, "DecorateWindow: Can not open decor file '%s'\n", decorfileName );
    else
      fprintf( stderr, "DecorateWindow: Error on line %d of your decor file '%s'\n",
	                result, decorfileName );
    return( 0 );
  }
  x_edgesize = W->width - ( 2 * x_border );
  y_edgesize = W->height - ( 2 * y_border );

  
/*   CORNERS    */
  
  if (( x_border > 0 ) && ( y_border > 0 )) {
    ul = (struct Window *)MakeWindow( W->display, W->input, W,
				    0,0, x_border, y_border, DECORNAME_UL );
    Patternify( ul, curpattern[ DECOR_UL ] );
    SendMessage( ul, PATTERN_RELATIVE, TRUE );
    /* Maker( ul, 0,0, x_border - 1, y_border - 1); */ /* No need to Maker this corner*/
    Wimp( ul );
    EchoWrap( ul, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( ul );

    ur = (struct Window *)MakeWindow( W->display, W->input, W,
				    W->width - x_border, 0,
				    x_border, y_border, DECORNAME_UR );
    Patternify( ur, curpattern[ DECOR_UR ] );
    SendMessage( ur, PATTERN_RELATIVE, TRUE );
    Maker( ur, -x_border + 1, 0, 0, y_border - 1 );
    Wimp( ur );
    EchoWrap( ur, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( ur );
    
    lr = (struct Window *)MakeWindow( W->display, W->input, W,
				    W->width - x_border, W->height - y_border,
				    x_border, y_border, DECORNAME_LR );
    Patternify( lr, curpattern[ DECOR_LR ] );
    SendMessage( lr, PATTERN_RELATIVE, TRUE );
    Maker( lr, -x_border + 1, -y_border + 1, 0, 0 );
    Wimp( lr );
    EchoWrap( lr, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( lr );


    ll = (struct Window *)MakeWindow( W->display, W->input, W,
				    0, W->height - y_border,
				    x_border, y_border, DECORNAME_LL );
    Patternify( ll, curpattern[ DECOR_LL ] );
    SendMessage( ll, PATTERN_RELATIVE, TRUE );
    Maker( ll, 0, -y_border + 1, x_border - 1, 0 );
    Wimp( ll );
    EchoWrap( ll, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( ll );
  }

  
  
/*   EDGES   */
  
  if ( y_border > 0 ) {
    top = (struct Window *)MakeWindow( W->display, W->input, W,
				     x_border, 0,
				     x_edgesize, y_border, DECORNAME_TOP );
    if ( x_border > 0 )
      Patternify( top, curpattern[ DECOR_TOP ] );
    else
      Patternify( top, curpattern[ 1 ] );
    SendMessage( top, PATTERN_RELATIVE, TRUE );
    Maker( top, x_border, 0, -x_border, y_border - 1 );
    Wimp( top );
    EchoWrap( top, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( top );

    bottom = (struct Window *)MakeWindow( W->display, W->input, W,
				        x_border, W->height - y_border,
				        x_edgesize, y_border, DECORNAME_BOTTOM );
    if ( x_border > 0 )
      Patternify( bottom, curpattern[ DECOR_BOTTOM ] );
    else
      Patternify( bottom, curpattern[ 3 ] );
    SendMessage( bottom, PATTERN_RELATIVE, TRUE );
    Maker( bottom, x_border, -y_border + 1, -x_border, 0 );
    Wimp( bottom );
    EchoWrap( bottom, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( bottom );
  }

  if ( x_border > 0 ) {
    right = (struct Window *)MakeWindow( W->display, W->input, W,
				       W->width - x_border, y_border,
				       x_border, y_edgesize, DECORNAME_RIGHT );
    if ( y_border > 0 )
      Patternify( right, curpattern[ DECOR_RIGHT ] );
    else
      Patternify( right, curpattern[ 3 ] );
    SendMessage( right, PATTERN_RELATIVE, TRUE );
    Maker( right, -x_border + 1, y_border, 0, -y_border );
    Wimp( right );
    EchoWrap( right, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( right );

    left = (struct Window *)MakeWindow( W->display, W->input, W,
				      0, y_border,
				      x_border, y_edgesize, DECORNAME_LEFT );
    if ( y_border > 0 )
      Patternify( left, curpattern[ DECOR_LEFT ] );
    else
      Patternify( left, curpattern[ 1 ] );
    SendMessage( left, PATTERN_RELATIVE, TRUE );
    Maker( left, 0, y_border, x_border - 1, -y_border );
    Wimp( left );
    EchoWrap( left, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
    InstallWin( left );
  }


/*   CENTER  */
  
  center = (struct Window *)MakeWindow( W->display, W->input, W,
				        x_border, y_border, x_edgesize, y_edgesize,
				        DECORNAME_CENTER );
  if (( x_border > 0 ) && ( y_border > 0 ))
    Patternify( center, curpattern[ DECOR_CENTER ] );
  else
    Patternify( center, curpattern[ 2 ] );
  SendMessage( center, PATTERN_RELATIVE, TRUE );
  Maker( center, x_border, y_border, -x_border, -y_border );
  Wimp( center );
  EchoWrap( center, echo, JUSTUP | JUSTDOWN | BEENDOWN, 0, 0 );
  InstallWin( center );

  return( 0 );
}





/*
     PARSE DECOR FILE
     Reads in a decor file and assigns bitmaps to the different portions of
     the window by setting the global curstruct definitions.  See the header of
     this file for a complete description of the file format.
     Returns 0 if successful, -1 if the file cannot be opened, or the line
     number of the failure if there is a bad line in the file.
*/
static int ParseDecorFile( filename )
     char *filename;
{
  FILE *inF;
  char stringlist[ MAX_DECOR_SEGS + 1 ][ MAX_STRING_SIZE ];
  char line[ MAX_STRING_SIZE ];
  int line_number = 0;
  register index;
  
  if (( inF = fopen( filename, "r" )) == NULL ) {
    return( -1 );
  }

  for ( index = 0; index < MAX_DECOR_SEGS + 1; index++ )        /* initialize array */
    strcpy( stringlist[ index ], "" );

  do {
    fgets( line, MAX_STRING_SIZE, inF );
    sscanf( line, "%s", stringlist[ 0 ] );
    line_number++;
  } while ( !( strcmp( stringlist[ 0 ], "" )) ||
	     ( stringlist[ 0 ][ 0 ] == DECOR_COMMENT_CHAR ));
  
  sscanf( line, "%d %d\n", &x_border, &y_border );               /* read x, y sizes  */
  /*  printf( "the size is %d, %d\n", x_border, y_border ); */
  
  if (( x_border > 0 ) && ( y_border > 0 ))                 /* check for valid sizes */
    num_of_segs = MAX_DECOR_SEGS;
  else if (( x_border <= 0 ) && ( y_border <= 0 ))
    return( line_number );
  else {
    x_border = MAX( 0, x_border );
    y_border = MAX( 0, y_border );
    num_of_segs = 3;
  }

	   
/*
    The first string starts at index 1, not 0.
    0 is reserved as a sentinel position when doing the matching search.
*/    
  for ( index = 1; index < num_of_segs + 1; index++ ) {
    do {
      fgets( line, MAX_STRING_SIZE, inF );
      sscanf( line, "%s", stringlist[ index ] );
      line_number++;
    } while ( !( strcmp( stringlist[ index ], "" )) ||
	       ( stringlist[ index ][ 0 ] == DECOR_COMMENT_CHAR ));
    
  }
  fclose( inF );

  if ( LoadBitmapPatterns( stringlist ))
    return( 0 );
  else
    return( -1 );
}



/*
     LOAD BITMAP PATTERNS
     Sets the global curstruct pointer of each segment to a bitmap.  If
     the bitmap had already been loaded by another segment, then it is not
     reloaded again.  It is therefore possible to have several segments with
     pointers to the same bitmap.
*/     
static int LoadBitmapPatterns( patterns )
     char patterns[][ MAX_STRING_SIZE ];
{
  static int FindMatch();
  int match,
      index;

  curpattern[ DECOR_UL ] =                  /* 1st one, no need to check for match */
    (struct curstruct *)LoadDaveIcon( patterns[ DECOR_UL ] );

  for ( index = DECOR_UR; index <= num_of_segs; index++ ) {
    if ( match = FindMatch( patterns, index )) {
      /* printf( "index %d is matched at %d\n", index, match ); */
      curpattern[ index ] = curpattern[ match ];
    }
    else
      curpattern[ index ] = (struct curstruct *)LoadDaveIcon( patterns[ index ] );
  }
  
  return( 1 );
}




/*
     FIND MATCH
     Looks through a list of strings and determines if string n in the list
     is located anywhere else in the list.  This function uses a "sentinel" search
     and works by putting the nth string in position 0 of the list, then searching
     backwards through the list until it is found.
     Returns the index of the match, or 0 if there is no match.
*/
static int FindMatch( strings, n )
     char strings[][ MAX_STRING_SIZE ];
     int n;
{
  register index;

  strcpy( strings[ 0 ], strings[ n ] );
  for ( index = n - 1; index >= 0; index-- ) {
    if ( ! strcmp( strings[ n ], strings[ index ] ))
      return( index );
  }
}




#undef MAX_STRING_SIZE
