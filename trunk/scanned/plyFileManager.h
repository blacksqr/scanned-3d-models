#ifndef PLY_FILE_MANAGER_H
#define PLY_FILE_MANAGER_H

#include <string.h>
#include <vector.h>
#include "plyObjectManager.h"
#include "Trackball.h"

#ifndef PI
#define PI 3.14159265358979323846264
#endif

using std::string;

class PlyFileManager
{
public:
	PlyFileManager();

        void initFileManager();
	void scanGroupDirectoryChanged(char *newDirectory);
	void setObjectManager( PlyObjectManager *objectManager);
	string *getScanNames(void){return inOrderScanNames;}
	int getNumberFiles(void){return numberOfFiles;}
	void resetFileManager( void );

private:
	string *inOrderFilenames;
	string *inOrderScanNames;
	int numberOfFiles;
	char *directory;
        bool filesAreValid;
        void getFiles(string dir, vector<string> &files);
        void reinitializeFileManager( void );
        PlyObjectManager *objectManager;
        char *scanGroupDirectory;
};

#endif
