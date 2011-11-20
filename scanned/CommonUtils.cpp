#include <stdio.h>

#include "CommonUtils.h"
#include "plvPlyCmds.h"

char* dir = "/tmp/vrip-prep";
void prepareVrip(){
    extern Tcl_Interp* interp;

    int nArgs = 3;
    // resolution, save directory
    char* vArgs[] = {"" , "0", dir};
    // Write translation and xf files
    PlvWritePlyForVripCmd(NULL, interp, nArgs, vArgs);

}

void createNewVripVri(){

}

