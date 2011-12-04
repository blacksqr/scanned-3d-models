#include "plyObjectManager.h"
#include "plvScene.h"
#include "Mesh.h"

static void initRenderParams(void);
static void drawMesh(RigidScan *);


PlyObjectManager::PlyObjectManager()
{
	initRenderParams();
	Mesh::progress_update = 0xffffffff;
	scanGroupTotalAngle = 360;
	scanGroupTranslation = 0;
}

RigidScan* PlyObjectManager::addObject(char * filename)
{

	printf("\n\nLoading PLY File:  %s\n\n\n", filename);
	crope cropeString (filename);
	printf("\nNewString[%s]", cropeString.c_str());
  
	RigidScan *scan = CreateScanFromFile (cropeString);
	DisplayableRealMesh *displayableMesh = new DisplayableRealMesh(scan, "SCAN");
	displayableMesh->invalidateCachedData();
    scan->select_coarsest();
	handleFlippingNormals(scan);

	displayableMeshes.push_back(displayableMesh);
    theScene->addMeshSet(scan, false, scan->get_name().c_str());

	printf("\n\nLoaded PLY File:  %s\n\n\n", filename);

	return scan;
}

void PlyObjectManager::handleFlippingNormals(RigidScan *scan)
{
	scan->flipNormals();
}

void PlyObjectManager::setHighestScanResolution(void)
{
    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		displayableMeshes[i]->getMeshData()->select_finest();
	}
}

void PlyObjectManager::setLowestScanResolution(void)
{
    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		displayableMeshes[i]->getMeshData()->select_coarsest();
	}
}

void PlyObjectManager::removeAllObjects( void )
{
	displayableMeshes.clear();
	theScene->meshSets.clear();
}

void PlyObjectManager::drawAllObjects( void )
{
	glColor3f(1.0, 1.0, 1.0);
    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		drawMesh(displayableMeshes[i]->getMeshData());
	}
}

void PlyObjectManager::rotateAllObjectsAroundYAxis()
{
	// load each ply file
	float degreesBetweenScan = (float)scanGroupTotalAngle/(float)displayableMeshes.size();
    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		RigidScan *scan = displayableMeshes[i]->getMeshData();
		rotateObjectAroundYAxis(scan, (float)i*degreesBetweenScan);
	}
}

void PlyObjectManager::rotateObjectAroundYAxis(RigidScan* scan, float degrees)
{
  	Pnt3 axis;
  	axis[0] = 0; axis[1] = 1; axis[2] = 0;
	float angle_rads = (degrees/360.0) * (2.0*PI);

	float q[4];
 	Pnt3 a = axis;   // mungeable copy
	// convert axis to quaternion
	a.normalize();
	a *= sin(angle_rads/2.0);
	q[1]=a[0]; q[2]=a[1]; q[3]=a[2];
	q[0] = cos(angle_rads/2.0);


	// rotate the scan by calculated quaternion
	scan->rotateWithoutTranslation(q[0], q[1], q[2], q[3], true);
}

void PlyObjectManager::translateAllObjectsAlongZAxis( void )
{
    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		RigidScan *scan = displayableMeshes[i]->getMeshData();
		translateObjectAlongZAxis(scan);
	}
}

void PlyObjectManager::translateObjectAlongZAxis( RigidScan *scan )
{
	float zTrans = (float) scanGroupTranslation / 600.0;
	scan->translateCorrectly(0.0, 0.0, zTrans, true);
}

void PlyObjectManager::printAllObjectXForms(void)
{

    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		RigidScan *scan = displayableMeshes[i]->getMeshData();
		Xform<float> xf = scan->getXform();
		printf("\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n\n\n\n",
			xf(0,0), xf(0,1), xf(0,2), xf(0,3),
			xf(1,0), xf(1,1), xf(1,2), xf(1,3),
			xf(2,0), xf(2,1), xf(2,2), xf(2,3),
			xf(3,0), xf(3,1), xf(3,2), xf(3,3));
	}
}

void PlyObjectManager::scanGroupAngleChanged(int newValue)
{
	assert( newValue >= 0 && newValue <= 360);
	this->scanGroupTotalAngle = newValue;
	resetAllObjectXForm();
	rotateAllObjectsAroundYAxis();
	translateAllObjectsAlongZAxis();
}

void PlyObjectManager::scanGroupTranslationChanged(int newValue)
{
	this->scanGroupTranslation = newValue;
	resetAllObjectXForm();
	rotateAllObjectsAroundYAxis();
	translateAllObjectsAlongZAxis();
}

void PlyObjectManager::resetAllObjectXForm( void )
{
    for(int i = 0; i < displayableMeshes.size(); i++)
	{
		displayableMeshes[i]->getMeshData()->resetXform();
	}
}


static void drawMesh(RigidScan *scan)
{
  glMatrixMode (GL_MODELVIEW);
  glPushMatrix();
  scan->gl_xform();
  glMatrixMode (GL_TEXTURE);
  glPushMatrix();
  scan->gl_xform();

  bool bPointsOnly = (theRenderParams->polyMode == GL_POINT);
  bPointsOnly = false;
  MeshTransport *mesh = scan->mesh(true, (bPointsOnly)?true:false, RigidScan::colorTrue, 3);
  bool bGeometryOnly = false;
  //bool bLores = bManipulating && theRenderParams->bRenderManipsLores;
  //DrawData& cache = bLores ? this->cache[1] : this->cache[0];

/*    FOR DRAWING POINTS WHEN THE OBJECT IS BEING MOVED
    // don't stick the points-only view in a dlist!
	bool bManipulating = false;
    if (bManipulating) 
	{
      	if (theRenderParams->bRenderManipsPoints) {
		// draw points-only view for speed
			bPointsOnly = true;

			if (theRenderParams->bRenderManipsTinyPoints) {
	  			glPointSize (1.0);
			} else {
	  			glPointSize (2.0);
			}
      	}
      
      	if (theRenderParams->bRenderManipsUnlit) {
			glDisable (GL_LIGHTING);
			bGeometryOnly = true;
      	}
    }
*/

  // hidden-line back pass doesn't need anything but geometry
  if (theRenderParams->hiddenLine &&
      (theRenderParams->polyMode == GL_FILL))
    bGeometryOnly = true;

  //bool bWantNormals = theRenderParams->light && !bGeometryOnly;
  bool bWantNormals = true;
  bool bWantColor = (mesh->color.size() == mesh->vtx.size()
		     && !bGeometryOnly);

  if (bWantColor)
    glEnable (GL_COLOR_MATERIAL);

  // set up client vertex-pointer state with relevant pointers
  //if (g_glVersion >= 1.1) {
    // vertex arrays -- only supported under OpenGL 1.1 (Irix 6.5)
    glEnableClientState (GL_VERTEX_ARRAY);
    if (bWantNormals)
	{
      glEnableClientState (GL_NORMAL_ARRAY);
	}

    for (int imesh = 0; imesh < mesh->vtx.size(); imesh++) {

// STL Update        
      glVertexPointer (3, GL_FLOAT, 0, &*(mesh->vtx[imesh]->begin()));
      
      glMatrixMode (GL_MODELVIEW);
      glPushMatrix();
      glMultMatrixf (mesh->xf[imesh]);
      // we should do this but it overflows the texture matrix stack...
      // TODO: make our own internalPushMatrix function
      //glMatrixMode (GL_TEXTURE);
      //glPushMatrix();
      //glMultMatrixf (cache.mesh->xf[imesh]);
      
      if (bWantNormals)
		{
		// STL Update        
		glNormalPointer (MeshTransport::normal_type, 0, &*(mesh->nrm[imesh]->begin()));
		}

      // the second test below avoids using color arrays of size 1, even
      // if there is only 1 vertex -- this tends to hang GL on maglio.
      // The "color the whole fragment that color without using
      // glColorPointer" case takes care of it anyway, without hanging.
      bool bThisWantColor = bWantColor
	&& (mesh->color[imesh]->size() > 4)
	&& (mesh->color[imesh]->size()
	    == 4 * mesh->vtx[imesh]->size());

      if (bThisWantColor) {
	// only enable vertex-array color if array is expected size.
	glEnableClientState (GL_COLOR_ARRAY);
// STL Update        
	glColorPointer (4, GL_UNSIGNED_BYTE, 0,
			&*(mesh->color[imesh]->begin()));
      } else {
	// don't have a full color array...
	glDisableClientState (GL_COLOR_ARRAY);
	// but we might have a per-fragment color for all these vertices.
	if (bWantColor && mesh->color[imesh]->size() == 4) {
// STL Update        
	  glColor4ubv (&*(mesh->color[imesh]->begin()));
	}
      }
	
	float colorWhite[4] = { 1.0, 1.0, 1.0};
	float colorGray[4] = { 0.4, 0.4, 0.4};
	float diffuseColor[4] = { 0.7, 0.7, 0.7, 1.0 };
	float ambientColor[4] = { 0.2, 0.2, 0.2, 1.0 };
	float backSpecular[4] = {1.0, 1.0, 1.0, 1.0};
	float backShininess = 25.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, backSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, backShininess);
	glColor4fv(colorWhite);
      
      if (bPointsOnly) {
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
#if 1
	// this is obviously slower than hell for small count.  But maglio
	// appears to have a bug such that the second form times out and
	// hangs for a huge vtx list, if lighting is enabled.  Turn off
	// lighting or glDisableClientState (GL_NORMAL_ARRAY) and it's ok.
	// And if we render the same data 1 at a time, no prob.
	// In fact, it works for count = 1M, but not 1.5M. ???

	// one more note on this: a dejanews search for "GL:Wait Rdata"
	// turns up exactly one pair of hits, in which someone else
	// complains of a similar situation on an Onyx2 IR irix 6.5.1, and
	// an sgi rep acknowledges it sounds like an sgi bug.

	// with any significant value for count, this shouldn't be any
	// slower anyway so I'll leave it enabled.

	// 1M vertices per pass works fine for non-colored renderings
	// but crashes for color sometimes, so
	// we'll use 400K.

	// While we're documenting the follies of the IR, when color is
	// enabled, maglio consistently hits the same GL:Wait Rdata timeout
	// for vertex arrays of size 1.


	int total = mesh->vtx[imesh]->size();
	int count = 400000;
	if (bThisWantColor ) {
	  while ((total % count) == 1)  // to avoid yet another hang
	    --count;
	}
	glDrawArrays (GL_POINTS, 0, total % count);
	for (int i = total%count; i < total; i += count) {
	  glDrawArrays (GL_POINTS, i, count);
	}
#else
	glDrawArrays (GL_POINTS, 0, mesh->vtx[imesh]->size());
#endif
      //} else if (bStrips) {
      } else if (false) {
// STL Update
	//vector<int>::const_iterator lenEnd = StripInds[imesh].end();
	vector<int>::const_iterator start = mesh->tri_inds[imesh]->begin();

	//for (vector<int>::const_iterator len = StripInds[imesh].begin();
	     //len < lenEnd; len++) {             
	  //glDrawElements (GL_TRIANGLE_STRIP, *len,
			  //GL_UNSIGNED_INT, &*start);
        //start += *len + 1;
	//}
      } else {

	int total = mesh->tri_inds[imesh]->size();
	//int count = 600000; // must be divisible by 3
	int count = 3000; // must be divisible by 3
	//total[235146]   count[600000]  i[235146]
	glDrawElements (GL_TRIANGLES, total%count,
			GL_UNSIGNED_INT, &*(mesh->tri_inds[imesh]->begin()));
	for (int i = total%count; i < total; i += count)
// STL Update        
	  glDrawElements (GL_TRIANGLES, count,
			  GL_UNSIGNED_INT,
			  &*(mesh->tri_inds[imesh]->begin() + i));
      }

      //glMatrixMode (GL_TEXTURE);
      //glPopMatrix();
      glMatrixMode (GL_MODELVIEW);
      glPopMatrix();

    }

    glDisableClientState (GL_VERTEX_ARRAY);
    glDisableClientState (GL_NORMAL_ARRAY);
    glDisableClientState (GL_COLOR_ARRAY);

  //} else {
    // OpenGL 1.0 -- no standard vertex arrays
    // but can use gldrawarraysext, glvertexpointerext, etc. on older IRIX
    // if anyone needs this, they need to rewrite it
    //cerr << "OpenGL 1.0 not currently supported.  "
	 //<< "Have fun doing anything but rendering." << endl;
  //}

  glDisable (GL_COLOR_MATERIAL);
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
}

static void initRenderParams()
{
    theRenderParams = new RenderParams;
    theRenderParams->polyMode = GL_FILL;
    theRenderParams->hiddenLine = false;
    theRenderParams->shadeModel = perVertex;
    theRenderParams->cull = false;
    theRenderParams->useTstrips = false;
    theRenderParams->boundSelection = true;

    theRenderParams->light = true;
    theRenderParams->colorMode = grayColor;
    theRenderParams->useEmissive = false;
    theRenderParams->twoSidedLighting = false;
    
    // taken care of by two sided lighting
    // kberg - 6/5/01
    //theRenderParams->backFaceEmissive = false;

    theRenderParams->backfaceMode = lit;

    theRenderParams->confScale = 1;

    theRenderParams->pointSize = 1.0;
    theRenderParams->lineWidth = 1.0;

    theRenderParams->blend = 0;
    
    theRenderParams->shininess = 20;

    theRenderParams->specular[0] = 128;
    theRenderParams->specular[1] = 128;
    theRenderParams->specular[2] = 128;
    theRenderParams->specular[3] = 255;

    theRenderParams->diffuse[0] = 178; // .7 * 255
    theRenderParams->diffuse[1] = 178;
    theRenderParams->diffuse[2] = 178;
    theRenderParams->diffuse[3] = 255;

    /* added by kberg 6/5/01
       paramters used when two sided lighting is turne don
    */
    theRenderParams->backDiffuse[0] = 25;
    theRenderParams->backDiffuse[1] = 25;
    theRenderParams->backDiffuse[2] = 25;
    theRenderParams->backDiffuse[3] = 255;
    
    theRenderParams->backSpecular[0] = 18;
    theRenderParams->backSpecular[1] = 18;
    theRenderParams->backSpecular[2] = 18;
    theRenderParams->backSpecular[3] = 255;
    
    theRenderParams->backShininess = 20;

    theRenderParams->background[0] = 0;
    theRenderParams->background[1] = 0;
    theRenderParams->background[2] = 0;
    theRenderParams->background[3] = 255;

    theRenderParams->lightPosition[0] = 0.0;
    theRenderParams->lightPosition[1] = 0.0;
    theRenderParams->lightPosition[2] = 1.0;

    theRenderParams->lightAmbient[0] = 0.0;
    theRenderParams->lightAmbient[1] = 0.0;
    theRenderParams->lightAmbient[2] = 0.0;
    theRenderParams->lightAmbient[3] = 1.0;

    theRenderParams->lightDiffuse[0] = 1.0;
    theRenderParams->lightDiffuse[1] = 1.0;
    theRenderParams->lightDiffuse[2] = 1.0;
    theRenderParams->lightDiffuse[3] = 1.0;

    theRenderParams->lightSpecular[0] = 1.0;
    theRenderParams->lightSpecular[1] = 1.0;
    theRenderParams->lightSpecular[2] = 1.0;
    theRenderParams->lightSpecular[3] = 1.0;

    theRenderParams->shadows = false;
    theRenderParams->antiAlias = false;
    theRenderParams->numAntiAliasSamps = 8;
    theRenderParams->jitterX = 0;
    theRenderParams->jitterY = 0;
    theRenderParams->jitterArray = (jitter_point *)j8;
    theRenderParams->dofJitterX = 0;
    theRenderParams->dofJitterY = 0;
    theRenderParams->dofCenter = 0.5; // ratio between near and far
    theRenderParams->shadowLength = 0.05;
    theRenderParams->fromLightPOV = false;

    theRenderParams->flipnorm = false;
    theRenderParams->clearBeforeRender = true;
    theRenderParams->accelerateWithBbox = true;

    theRenderParams->bRenderManipsPoints = true;
    theRenderParams->bRenderManipsTinyPoints = false;
    theRenderParams->bRenderManipsUnlit = false;
    theRenderParams->bRenderManipsLores = false;
    theRenderParams->bRenderManipsSkipDlist = true;
    theRenderParams->iFastManipsThreshold = 0;
    
#ifdef no_overlay_support
    // RGBA being read back in
    theRenderParams->savedImage = new char[4 * theWidth * theHeight];
    
    theRenderParams->savedImageWidth = theWidth;
    theRenderParams->savedImageHeight = theHeight;
#endif
}

