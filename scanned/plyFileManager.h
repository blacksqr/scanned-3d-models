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

    void initFileManager(PlyObjectManager *objectManager, char *dir);

private:
	string *inOrderFilenames;
	int numberOfFiles;
	char *directory;
	bool filesAreValid;
	void getFiles(string dir, vector<string> &files);
	void rotateObjectAroundYAxis(RigidScan* scan, float degrees);

	PlyObjectManager *objectManager;

};

#endif
