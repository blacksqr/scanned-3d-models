#ifndef PLY_OBJECT_MANAGER_H
#define PLY_OBJECT_MANAGER_H

#include "MeshTransport.h"
#include "DisplayMesh.h"
#include "plvDraw.h"
#include "plvGlobals.h"
#include "ScanFactory.h"

class PlyObjectManager
{

public:
	PlyObjectManager();
	RigidScan* addObject(char * filename);
	void removeAllObjects( void );
	void drawAllObjects( void );

private:
		vector<DisplayableMesh*> displayableMeshes;
};

#endif
