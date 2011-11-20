#include <qapplication.h>
#include <stdlib.h>
#include <limits.h>
#include "form1.h"

#include "plvScene.h"
Tcl_Interp* interp = Tcl_CreateInterp();

int main( int argc, char ** argv )
{

    cout << "Creating scene..." << endl;
    theScene = new Scene (interp);

    QApplication a( argc, argv );
    Form1 w;
    w.show();

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
	return a.exec();

    return 0;
}

