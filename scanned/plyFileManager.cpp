#include <dirent.h>
#include <iostream.h>
#include <errno.h>
#include "plyFileManager.h"


PlyFileManager::PlyFileManager()
{ 
}

void PlyFileManager::initFileManager()
{
	assert(this->directory != NULL && this->objectManager != NULL);

	this->filesAreValid = false;

	string dirString(directory);

	vector<string> files;
	string dir = directory;
	getFiles(dir, files);

	bool fileNumbersExist[files.size()];
	for(int j = 0; j < files.size(); j++)
	{
		fileNumbersExist[j] = false;
	}
	string orderedFileNames[files.size()]; // include full path of file
	inOrderScanNames = new string[files.size()]; // just the file name no directory

        string filePrefixCheck;

	// fileformat is scan_<i>.ply
    for(int i = 0; i < files.size(); i++)
	{
		string file = files[i];
		size_t underscoreLoc = file.find('_');
		size_t periodLoc = file.find('.');
		if (underscoreLoc <= 0 && periodLoc <= 0)
			printf("\nFile not formatted correctly....should be 'prefix_<index>.ply'");

		string prefix = file.substr(0, underscoreLoc);
		if(filePrefixCheck.size() == 0)
		{
			filePrefixCheck = prefix;
		}
		else
		{
			if(filePrefixCheck != prefix)
				printf("\nFiles in directory don't have a common prefix");
		}

		string numberString = file.substr(underscoreLoc+1, periodLoc);
		int number = atoi(numberString.c_str());
		if(fileNumbersExist[number])
			printf("\nTwo files have the same index [%d]", number);

		fileNumbersExist[number] = true;
		orderedFileNames[number] = dirString + "/" + file;
		inOrderScanNames[number] = file;

	}

	for(int k = 0; k < files.size();k++)
	{
		if(!fileNumbersExist[k])
			printf("\nMissing scan number [%d]", k);
	}

        inOrderFilenames = orderedFileNames;
	numberOfFiles = files.size();

	for(int m = 0; m < numberOfFiles; m++)
	{
		string filenameString = inOrderFilenames[m];
		RigidScan *scan = objectManager->addObject(filenameString.c_str());
	}
	objectManager->rotateAllObjectsAroundYAxis();
	objectManager->translateAllObjectsAlongZAxis();

	this->filesAreValid = true;
}

void PlyFileManager::getFiles(string dir, vector<string> &finalFiles)
{
	printf("Founding files in %s", dir.c_str());
	vector<string> files;

	DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);


	for(int i = 0; i < files.size(); i++)
	{
		if(files[i] != "." && files[i] != ".." && files[i] != ".svn")
			finalFiles.push_back(files[i]);
	}
    return 0;
}

void PlyFileManager::setObjectManager( PlyObjectManager *objectManager)
{
	this->objectManager = objectManager;
}

void PlyFileManager::scanGroupDirectoryChanged(char *newDirectory)
{
	this->directory = newDirectory;
	reinitializeFileManager();
}

void PlyFileManager::reinitializeFileManager(void)
{
	objectManager->removeAllObjects();
	initFileManager();
}
