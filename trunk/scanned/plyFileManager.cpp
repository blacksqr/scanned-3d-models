#include <dirent.h>
#include <iostream.h>
#include <errno.h>
#include "plyFileManager.h"


PlyFileManager::PlyFileManager()
{

}

void PlyFileManager::initFileManager(PlyObjectManager *objectManager, char *directory)
{
	this->filesAreValid = false;
	this->directory = directory;
	this->objectManager = objectManager;

	string dirString(directory);

	vector<string> files;
	string dir = directory;
	getFiles(dir, files);

	bool fileNumbersExist[files.size()];
	for(int j = 0; j < files.size(); j++)
	{
		fileNumbersExist[j] = false;
	}
	string orderedFileNames[files.size()];

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

	}

	for(int k = 0; k < files.size();k++)
	{
		if(!fileNumbersExist[k])
			printf("\nMissing scan number [%d]", k);
	}

	inOrderFilenames = orderedFileNames;
	numberOfFiles = files.size();

	// load each ply file
	float degreesBetweenScan = 360.0/(float)files.size();
	for(int m = 0; m < numberOfFiles; m++)
	{
		string filenameString = inOrderFilenames[m];
		RigidScan *scan = objectManager->addObject(filenameString.c_str());

		rotateObjectAroundYAxis(scan, (float)m*degreesBetweenScan);
	}

	this->filesAreValid = true;
}

void PlyFileManager::rotateObjectAroundYAxis(RigidScan* scan, float degrees)
{
	printf("Rotating this object %f degrees", degrees);
  	Pnt3 axis;
  	axis[0] = 0; axis[1] = 1; axis[2] = 0;
	float angle_rads = (degrees/360.0) * (2.0*PI);
	printf("Rotating this object %f radians", angle_rads);

	float q[4];
 	Pnt3 a = axis;   // mungeable copy
	// convert axis to quaternion
	a.normalize();
	a *= sin(angle_rads/2.0);
	q[1]=a[0]; q[2]=a[1]; q[3]=a[2];
	q[0] = cos(angle_rads/2.0);

	// rotate the scan by calculated quaternion
	scan->rotate(q[0], q[1], q[2], q[3], false);

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

