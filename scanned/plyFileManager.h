#ifndef PLY_FILE_MANAGER_H
#define PLY_FILE_MANAGER_H

#include <string.h>
#include <vector.h>
#include "plyObjectManager.h"

using std::string;

class PlyFileManager
{
public:
	PlyFileManager();

    void initFileManager(PlyObjectManager *objectManager, char *dir);
	void loadFiles(void);

private:
	string *inOrderFilenames;
	int numberOfFiles;
	char *directory;
	bool filesAreValid;
	void getFiles(string dir, vector<string> &files);

	PlyObjectManager *objectManager;

};

#endif
