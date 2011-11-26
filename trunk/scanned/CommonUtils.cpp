#include <stdio.h>

#include "CommonUtils.h"
#include "plvPlyCmds.h"
#include "volfill.h"
#include "plvMeshCmds.h"
#include "sczRegCmds.h"
using std::string;


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


void runICP(string* scans, int nScans){
    extern Tcl_Interp* interp;
    
    if(nScans < 2)
    {
        printf("Must have more than 1 file to run ICP");
	return;
    } 

    int nArgs = 0;
    char buffer[150];
    char baseScan[150];
    char nextScan[150];
    sprintf(baseScan, "%s", scans[0].c_str());
    printf("Processing[0]=%s\r\n", baseScan);
    for(int i = 1; i < nScans; i++)
    {
	sprintf(nextScan, "%s", scans[i].c_str());
        printf("Processing[%i]=%s\r\n", i, nextScan);

	// First run ICP
        // Sampling rate, ??, iterations, Cull percentage, ??, 
        // plane?, scan1, scan2, threshold (relative absolute), threshold value, ??, globalreg value, ??
	nArgs=14;
        char* vArgs[] = {"" , "0.10", "0", "20", "3", "1", "plane", 
                    baseScan , nextScan, "abs", "5.0", "1", "200", "0"};
        PlvRegIcpCmd(NULL, interp, nArgs, vArgs);

	// Now group results
	sprintf(buffer, "auto-group%i", i);
	nArgs = 6;
        char* grpArgs[] = {"" , "create", buffer, baseScan, nextScan, "0"};
        //plv_groupscans create [append name ".gp"] $members $dirty
       // PlvGroupScansCmd(NULL, interp, nArgs, grpArgs);

	// set baseScan for next itreration
	strcpy(baseScan, nextScan); 
	//strcpy(baseScan, buffer); 
    }

    //int nArgs = 5;
    // resolution, save directory
    //char* vArgs[] = {"" , "create", "group1.gp", "bun_0.ply", "bun_1.ply"};
    // Write translation and xf files
    //PlvGroupScansCmd(NULL, interp, nArgs, vArgs);
  
    //char* vArgs[] = {"" , "0.10", "0", "20", "3", "1", "plane", 
    //                 "bun_0.ply", "bun_1.ply", "abs", "5.0", "1", "200", "0"};
    //PlvRegIcpCmd(NULL, interp, nArgs, vArgs);
}

