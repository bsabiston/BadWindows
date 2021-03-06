/**********************************************************************


  Sibling.c

  Tim Kukulski


  Visible Language Workshop
  
  Summer 1990

  

  "Like Messenger, only more so."

  Sends a messge to all the siblings of a window.
  
  SiblingMessenger();
       PassSiblingsMessage();
    SendSiblingsMessage();       

  ChildrenMessanger();
       PassChildrenMessage();
    SendChildrenMessage();

**********************************************************************/

#include <stdio.h>
#include <math.h>
#include <starbase.c.h>
#include <windows.c.h>
#include <structures.h>

/**********************************************************************

           SiblingMessenger(W,id1,M,id,data,mask)

  
                      W       Activation Window
		      
		      id1     Activation message
		      
		      M       The Window who's siblings we want
		              to talk to.

		      id      The message we want to send.

		      data    The data accompanying the message.

		      mask    The echo mask.
  
**********************************************************************/


SiblingMessenger(W, id1, M, id, data, mask)     /* v 1.0 */
     struct Window *W, *M;
     int id, mask, id1;
     char *data;
{
  int PassSiblingsMessage();
  struct messagestruct *parms;

  parms = (struct messagestruct *)malloc(sizeof(struct messagestruct));


  parms->W = M;
  parms->id = id;
  parms->data = data;
  parms->mask = mask;
  AttachCommand(W, id1, PassSiblingsMessage, parms);
  if(e_value)
    MessengerDebug(W, id1, M, id, data, mask,parms,"SiblingMessenger");
}

SiblingMessengerB(W, id1, id, data, mask)     /* v 1.0 */
     struct Window *W;
     int id, mask, id1;
     char *data;
{
  int PassSiblingsMessage();
  struct messagestruct *parms;

  parms = (struct messagestruct *)malloc(sizeof(struct messagestruct));

  parms->W = W;
  
  parms->id = id;
  parms->data = data;
  parms->mask = mask;
  AttachCommand(W, id1, PassSiblingsMessage, parms);

}



PassSiblingsMessage(W, id, data, stuff)     /* v 1.0 */
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct messagestruct *parms;
  int flag = 1, val = 0;

  parms = (struct messagestruct *)stuff;

  if(id == DO)
    switch (((struct pickstruct *)data)->button)
    {
    case (JUSTDOWN): flag = parms->mask & 1;
      break;
    case (JUSTUP):   flag = parms->mask & 2;
      break;
    case (BEENDOWN): flag = parms->mask & 4;
      break;
    case (BEENUP):   flag = parms->mask & 8;
      break;
    }
  if (flag) val = SendSiblingsMessage(parms->W, parms->id, parms->data);

  return(val);
}

int SendSiblingsMessage(W,id,data)
     struct Window *W;
     int id;
     char *data;
{
 struct List *Current, *L, *L2;
 struct Window *P, *tempwin;
 int count = 0;

 P = W->parent;
 L = P->port;

 CopyList(L,&L2);

 for (Current = L2->Front; Current != L2; Current = Current->Front)
   {
     tempwin = Current->id;
     if(tempwin != W)
       {
	 SendMessage(tempwin,id,data);
	 count++;
       }
   }
 
 FreeList(L2);
/* return(count); */
 return (0);
}


/**********************************************************************

           ChildrenMessenger(W,id1,M,id,data,mask)

  
                      W       Activation Window
		      
		      id1     Activation message
		      
		      M       The Window who's children we want
		              to talk to.

		      id      The message we want to send.

		      data    The data accompanying the message.

		      mask    The echo mask.
  
**********************************************************************/


ChildrenMessenger(W, id1, M, id, data, mask)     /* v 1.0 */
     struct Window *W, *M;
     int id, mask, id1;
     char *data;
{
  int PassChildrenMessage();
  struct messagestruct *parms;

  parms = (struct messagestruct *)malloc(sizeof(struct messagestruct));
  parms->W = M;
  parms->id = id;
  parms->data = data;
  parms->mask = mask;
  AttachCommand(W, id1, PassChildrenMessage, parms);
  if(e_value)
    MessengerDebug(W, id1, M, id, data, mask,parms,"ChildrenMessenger");

}



PassChildrenMessage(W, id, data, stuff) 
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct messagestruct *parms;
  int flag = 1 , val = 0;

  parms = (struct messagestruct *)stuff;

  if(id == DO)
  switch (((struct pickstruct *)data)->button)
    {
    case (JUSTDOWN): flag = parms->mask & 1;
      break;
    case (JUSTUP):   flag = parms->mask & 2;
      break;
    case (BEENDOWN): flag = parms->mask & 4;
      break;
    case (BEENUP):   flag = parms->mask & 8;
      break;
    }
  if (flag) val = SendChildrenMessage(parms->W, parms->id, parms->data);

  return(val);
}

int SendChildrenMessage(W,id,data)
     struct Window *W;
     int id;
     char *data;
{
 struct List *Current, *L, *L2;
 struct Window *tempwin;
 int count = 0;

 L = W->port;

 if(L == NULL)
   return(-1);
 
 CopyList(L,&L2);

 for (Current = L2->Front; Current != L2; Current = Current->Front)
   {
     tempwin = Current->id;
     SendMessage(tempwin,id,data);
     count++;
   }
 
 FreeList(L2);
 return(count);
}


/**********************************************************************

              CloseAllChildren(W)


	         W    Parent Window of said children.

		 DB 
**********************************************************************/



int CloseAllChildrenB(W)
     struct Window *W;
{
 struct List *Current, *L, *L2;
 struct Window *tempwin;
 int count = 0;

 L = W->port;

 CopyList(L,&L2);

 for (Current = L2->Front; Current != L2; Current = Current->Front)
   {
     tempwin = Current->id;
     CloseWindow (tempwin);
     count++;
   }
 
 FreeList(L2);
 return(count);
}


struct Window *FindRoot(W)
     struct Window *W;
{
  if( W) {
    while( W->parent)
      W = W->parent;
    return( W);
  }
  else
    printf( "FindRoot: NULL window!\n");
}

/*************************** things to debug your messenger use ************/
MessengerDebug(W, id1, M, id, data, mask, parms,name)
     struct Window *W, *M;
     int id, mask, id1;
     char *data, *parms, *name;
    {
      int MessageDebug();
      
      if(W && W->tag)
	printf("%12s: W = \"%s\"\t ",name,W->tag);
      printf("id1 %5d\n",id1);
      if(M && M->tag)
	printf("            : M = \"%s\"\t ",M->tag);
      printf("id %5d ",id);
      printf("data 0x%08x ",data);
      printf("mask 0x%02x\n",mask);

      AttachCommand(W, id1, MessageDebug, parms);
}
  
int 
MessageDebug(W, id, data, stuff)
     struct Window *W;
     int id;
     char *data, *stuff;
{
  struct messagestruct *parms;
  struct Window *M;
  if(!e_value)
    return(0);

  parms = (struct messagestruct *)stuff;
  printf("MessageDebug: ");
  if(W && W->tag)
    printf("W \"%s\" ",W->tag);
  else
    printf("W is NULL ");
  printf("id %5d ",id);
  printf("data 0x%08x\n",data);
  printf("            : ");
  M = parms->W;
  if(M && M->tag)
    printf("M \"%s\" ",M->tag);
  else
    printf("M is NULL ");
  printf("id %5d ",parms->id);
  printf("data 0x%08x\n",parms->data);
  return(0);
}
