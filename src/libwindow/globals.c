/* globals for the window system */
/* you don't REALLY need these to run windows. ie windowtools.c does not use them
   these variables are required for much of the standard window code.
   Echoes, query windows, two-screen operation...
*/

#include <stdio.h>
#include <windows.c.h>

struct Window *Root1 = NULL,*Root2 = NULL;
struct OutDev *Output1 = NULL, *Output2 = NULL;
struct InDev *Input1 = NULL, *Input2 = NULL;
struct Window *CurrentTextWindow = NULL;       /* current window to receive keyboard input                        */
/* struct Window *CurrentMidiWindow = NULL;*/  /* current window to receive midi input                            */
struct Window *screen_toggle = NULL;           /* switch between screens                                          */
int E_lastx,E_lasty;                           /* last x and y mouse positions                                    */
char *query_return;                            /* return value from query                                         */
int e_value;			               /* use this as a debugging flag... --Tim 3/29/91 */

int CurrentRed = 0,CurrentGreen = 0,CurrentBlue = 0, CurrentIndex = -1, CurrentSubIndex = -1, CurrentPaletteIndex = -1;
float CurrentHue = 29.0, CurrentSat = 4.0, CurrentVal = 5.70;        /* brownish */

int (*set_new_color)() = NULL;                 /* this functon is called when a new color is set                  */
struct Window *E_lastRoot;
char *BADWINDOWS_DIRECTORY = "/vlw/";                    /* badwindows directory -- Use SetBadWindowsDirectory() to change  */
unsigned char ColorTable[256][3] = NULL; /* contains current 8bit color table */
char wdefstring[500];
