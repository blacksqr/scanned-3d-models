#include <stdio.h>

#include "CommonUtils.h"
#include "plvPlyCmds.h"
#include "volfill.h"
#include "plvMeshCmds.h"

/*

NOTES: order of execution

Save all visable to directory
- vrip.conf needs to have fully qualifed path of ply files (changed manually)
vripnew /local/scanned-3d-models/samples/range-scan/bunny/data/test/vrip.vri /local/scanned-3d-models/samples/range-scan/bunny/data/test/vrip.conf  /local/scanned-3d-models/samples/range-scan/bunny/data/test/vrip.conf .001 -show_render

need to fill holes here:
volfill /local/scanned-3d-models/samples/range-scan/bunny/data/test/vrip.vri /local/scanned-3d-models/samples/range-scan/bunny/data/test/filled.vri

vripsurf /local/scanned-3d-models/samples/range-scan/bunny/data/test/vrip.vri /local/scanned-3d-models/samples/range-scan/bunny/data/test/vrip.ply
vripsurf /local/scanned-3d-models/samples/range-scan/bunny/data/test/filled.vri /local/scanned-3d-models/samples/range-scan/bunny/data/test/filled.ply

GenericScan.cc PlvWritePlyForVripCmd

*/


char* dir = "/tmp/vrip-prep";
char* rootDir = "../";

void prepareVrip(){
    extern Tcl_Interp* interp;

    int nArgs = 3;
    // resolution, save directory
    char* vArgs[] = {"" , "0", dir};
    // Write translation and xf files
    PlvWritePlyForVripCmd(NULL, interp, nArgs, vArgs);

}

void createNewVripVri(){
    char cmd[1000];
    sprintf(cmd, " cd %s/vrip; ./vrip.sh src/vrip/vripnew.tcl %s/bun.vri %s/vrip.conf %s/vrip.conf .001 -show_render", rootDir, dir, dir, dir );
    system(cmd);
}

void runVolfill(){
    int nArgs = 3;
    char source[200];
    char dest[200];
    sprintf(source, "%s/bun.vri", dir);
    sprintf(dest, "%s/filled-bun.vri", dir);
    // source.vri, dest.vri
    char* vArgs[] = {"" , source, dest};
    // fill the holes
    volfill(nArgs, vArgs);
}

void createVripSurf(){
    char cmd[1000];
    sprintf(cmd, " cd %s/vrip; ./vrip.sh src/vrip/vripsurf.tcl %s/filled-bun.vri %s/filled-bun.ply", rootDir, dir, dir );
    system(cmd);
}

void launchScanalyze(void){
    char cmd[1000];
    sprintf(cmd, " cd %s/scanalyze; ./scanalyze.debug %s/filled-bun.ply", rootDir, dir );
    system(cmd);
}


void runICP(void){
    extern Tcl_Interp* interp;

    int nArgs = 6;
    // resolution, save directory
    char* vArgs[] = {"" , "create", "group1.gp", "bun_0.ply", "bun_1.ply"};
    // Write translation and xf files
    //plv_groupscans create [append name ".gp"] $members $dirty
    PlvGroupScansCmd(NULL, interp, nArgs, vArgs);

}

