#include "ScanalyzeUtils.h"
#include <stdio.h>

void prepareVrip(){
    extern Tcl_Interp* interp;

    int nArgs = 3;
    // resolution, save directory
    char* vArgs[] = {"" , "0", "/tmp/vrip-prep"};
    // Write translation and xf files
    PlvWritePlyForVripCmd(NULL, interp, nArgs, vArgs);

}

