#include <qapplication.h>
#include <stdlib.h>
#include <limits.h>
#include "form1.h"

/*
#include "togl.h"
#include "plvInit.h"
#include "plvGlobals.h"
#include "plvCmds.h"
#include "plvPlyCmds.h"
#include "plvViewerCmds.h"
#include "plvDrawCmds.h"
#include "plvCybCmds.h"
#include "plvImageCmds.h"
#include "plvClipBoxCmds.h"
#include "plvMeshCmds.h"
#include "plvScene.h"
#include "plvDraw.h"
#include "sczRegCmds.h"
#include "plvAnalyze.h"
#include "plvMMCmds.h"
#include "CyberCmds.h"
#include "Trackball.h"
#include "BailDetector.h"
#include "Progress.h"
*/

// Prototypes
//float getGLVersionA (void);
//int appInit(Tcl_Interp *interp);

int main( int argc, char ** argv )
{
//   Tcl_Interp* interp = Tcl_CreateInterp();

/*
  Tk_Window main;
  main = Tk_MainWindow(interp);

  g_tclInterp = interp;
*/
 //  tbView  = new Trackball;
  // theScene = new Scene (interp);
 

    // initialize interactors
    //Togl_DisplayFunc (drawInTogl);
    //Togl_CreateFunc (catchToglCreate);
    //Togl_OverlayDisplayFunc (drawOverlay);
 
    printf("initDr\n");

    //initDrawing();
    printf("initDrDone\n");

//   char *plvDir = getenv("SCANALYZE_DIR");
 //  if (plvDir == NULL) {
  //   printf("Need to set SCANALYZE_DIR environment variable.");
   //  return 1;
  // }

  // and, once togl widget exists (after scanalyze.tcl is sourced):
  // since these things need a GL context
//    initDrawingPostCreation();
    //getGLVersionA();
 //   Tk_CreateTimerHandler (30, SpinTrackballs, (ClientData)main);
 
  // finally, source the user customizations -- ~/.scanalyzerc
//  char* homeDir = getenv("HOME");
 // if (homeDir == NULL) {
 //   fprintf(stderr, "Environment variable HOME not set - "
//	    "will not execute $HOME/.scanalyzerc\n");
 // } else {
  //  char rcPath[PATH_MAX];
   // strcpy(rcPath, homeDir);
 //   strcat(rcPath, "/.scanalyzerc");
 // }

    //appInit(interp);
    
    QApplication a( argc, argv );
    Form1 w;
    w.show();

    //a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
	//return a.exec();
    return 1;
}


/*
int
PlvDeinitCmd(ClientData clientData, Tcl_Interp *interp, 
	     int argc, char *argv[])
{
#if 0
  delete theScene;
  theScene = NULL;

  //if this returns, Tk keeps processing events, and may call event
  //handlers -- in particular, it will try to redraw, which will crash
  //because there's no scene -- could also have drawMeshes() check for this.
  exit (0);
#else
  theScene->freeMeshes();
#endif

  return TCL_OK;
}
*/

/*
float
getGLVersionA (void)
{
  const GLubyte* verStr = glGetString (GL_VERSION);
  const GLubyte* verRenderer = glGetString (GL_RENDERER);
  
  float ver = atof ((const char*)verStr);
   
  printf ("OpenGL version is %g is rendered by %s\n", ver, verRenderer);

  return ver;
}
*/

/*
int PlvGetRendererStringCmd(ClientData clientData, Tcl_Interp *interp, 
			    int argc, char *argv[])
{
  const GLubyte* renderer = glGetString (GL_RENDERER);
  Tcl_SetResult (interp, (char*)renderer, TCL_VOLATILE);
  return TCL_OK;
}


int PlvGetWordSizeCmd(ClientData clientData, Tcl_Interp *interp, 
		      int argc, char *argv[])
{
  char buf[8];
  sprintf (buf, "%ld", sizeof (long));
  Tcl_SetResult (interp, buf, TCL_VOLATILE);
  return TCL_OK;
}

*/

/*
int
appInit(Tcl_Interp *interp)
{


 if (Togl_Init(interp) != TCL_OK) {
        fprintf(stderr, "Togl initialization failed: %s\n",
                interp->result);
        return TCL_ERROR;
      }
puts ("Togl...");


puts ("about to plvinit");
    if (Plv_Init(interp) != TCL_OK) {
        fprintf(stderr, "Scanalyze initialization failed:\n\n%s\n",
                interp->result);
        fprintf(stderr, "\nThings will probably not work as expected.\n");
    } 

  //  storeMinMaxZBufferValues();

   theScene->centerCamera();
    theScene->setHome();
    TbObj::clear_undo();
 return 0;
}
*/

