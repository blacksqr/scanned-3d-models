#include <stdio.h>

#include "CommonUtils.h"
#include "plvPlyCmds.h"
#include "volfill.h"
#include "plvMeshCmds.h"
#include "sczRegCmds.h"
#include "fileutils.h"
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
char* newVri = "vrip.vri";
char* filledVri = "filled-vrip.vri";
char* finalPly = "final.ply";

void removeVripPrepDir()
{
	removeDirectoryRecursively(dir);
}

void prepareVrip(){
    extern Tcl_Interp* interp;

    // We should always clear out the temp dir before running this.
    removeVripPrepDir();

    int nArgs = 3;
    // resolution, save directory
    char* vArgs[] = {"" , "0", dir};
    // Write translation and xf files
    PlvWritePlyForVripCmd(NULL, interp, nArgs, vArgs);

}

void createNewVripVri(){
    char cmd[1000];
    sprintf(cmd, " cd %s/vrip; ./vrip.sh src/vrip/vripnew.tcl %s/%s %s/vrip.conf %s/vrip.conf .001 -show_render", 
			rootDir, dir, newVri, dir, dir );
    system(cmd);
}

void runVolfill(){
    int nArgs = 3;
    char source[200];
    char dest[200];
    sprintf(source, "%s/%s", dir, newVri);
    sprintf(dest, "%s/%s", dir, filledVri);
    // source.vri, dest.vri
    char* vArgs[] = {"" , source, dest};
    // fill the holes
    volfill(nArgs, vArgs);
}

void createVripSurf(){
    char cmd[1000];
    // Need to check if we ran Vri so we have the right file to input to vrip march
    char* vriFile = filledVri;
    if(skipVolfill){
	vriFile = newVri;
    } 
    sprintf(cmd, " cd %s/vrip; ./vrip.sh src/vrip/vripsurf.tcl %s/%s %s/%s", rootDir, dir, vriFile, dir, finalPly );
    system(cmd);
}

void launchScanalyze(void){
    char cmd[1000];
    sprintf(cmd, " cd %s/scanalyze; ./scanalyze.debug %s/%s", rootDir, dir, finalPly );
    system(cmd);
}


void runICP(string* scans, int nScans){
    extern Tcl_Interp* interp;
    
    if(nScans < 2)
    {
        printf("Must have more than 1 file to run ICP");
	return;
    } 

    int nConverge = 20;
    float converge[nConverge];
    float error = 0; 

    int nArgs = 0;
    char buffer[150];
    char baseScan[150];
    char nextScan[150];
    sprintf(baseScan, "%s", scans[0].c_str());

    for(int r = 0; r < 2 ; r++){
    for(int i = 1; i < nScans; i++)
    {
	sprintf(nextScan, "%s", scans[i].c_str());
        printf("\n\nProcessing[%i]=%s\r\n", i, nextScan);

        // Sampling rate, ??, iterations, Cull percentage, ??, 
        // plane?, scan1, scan2, threshold (relative absolute), threshold value, ??, globalreg value, ??
	nArgs=14;
        char* vArgs[] = {"" , "0.10", "0", "20", "3", "1", "plane", 
                    baseScan , nextScan, "abs", "5.0", "1", "200", "0"};

	for(int j =0; j < nConverge; j++)
	{
		printf("**Running ICP Command\n");
        	PlvRegIcpCmdGetError(NULL, interp, nArgs, vArgs, error);
		printf("Error[%i] is %f\n", j, error);
		converge[j] = error;
		if(j>=1){
			if(converge[j]<converge[j-1]){
				//do nothing
			} else {
				// might be converging
				if(converge[j] <= converge[j-2]){
				// Found convergence.
        				printf("Converging on iteration %i\n", j);
					break;
				}	
			}
		}

	}

	// set baseScan for next itreration
	strcpy(baseScan, nextScan); 
    }
    }

		// Now group results
		//sprintf(buffer, "auto-group%i", i);
		//nArgs = 6;
        	//char* grpArgs[] = {"" , "create", buffer, baseScan, nextScan, "0"};
	        //plv_groupscans create [append name ".gp"] $members $dirty
       		// PlvGroupScansCmd(NULL, interp, nArgs, grpArgs);
		//strcpy(baseScan, buffer); 
    //int nArgs = 5;
    // resolution, save directory
    //char* vArgs[] = {"" , "create", "group1.gp", "bun_0.ply", "bun_1.ply"};
    // Write translation and xf files
    //PlvGroupScansCmd(NULL, interp, nArgs, vArgs);
  
    //char* vArgs[] = {"" , "0.10", "0", "20", "3", "1", "plane", 
    //                 "bun_0.ply", "bun_1.ply", "abs", "5.0", "1", "200", "0"};
    //PlvRegIcpCmd(NULL, interp, nArgs, vArgs);
}

