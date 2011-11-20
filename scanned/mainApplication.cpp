#include <qapplication.h>
#include <stdlib.h>
#include <limits.h>
#include "form1.h"

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

// Prototypes
//float getGLVersionA (void);
//int appInit(Tcl_Interp *interp);
void prepareVrip(void);
Tcl_Interp* interp = Tcl_CreateInterp();


int main( int argc, char ** argv )
{
   cout << "Creating scene..." << endl;
   theScene = new Scene (interp);
//   cout << "Running prepare vrip..." << endl;
 //  prepareVrip();

    QApplication a( argc, argv );
    Form1 w;
    w.show();

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
	return a.exec();

    return 0;
}


void prepareVrip(){

    int nArgs = 3;
    // resolution, save directory
    char* vArgs[] = {"0", "/tmp/tony", ""};
    // Write translation and xf files
    PlvWritePlyForVripCmd(NULL, interp, nArgs, vArgs);

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

