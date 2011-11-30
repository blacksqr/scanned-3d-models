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
	void scanGroupAngleChanged(int newValue);
	void scanGroupTranslationChanged(int newValue);
	void rotateAllObjectsAroundYAxis( void );
	void translateAllObjectsAlongZAxis( void );
	void printAllObjectXForms(void);
	void setHighestScanResolution(void);
	void setLowestScanResolution(void);

private:
	vector<DisplayableMesh*> displayableMeshes;
    int scanGroupTotalAngle;
    int scanGroupTranslation;
	void rotateObjectAroundYAxis(RigidScan* scan, float degrees);
	void translateObjectAlongZAxis(RigidScan* scan);
	void resetAllObjectXForm( void );
	void handleFlippingNormals(RigidScan *);
};

#endif
