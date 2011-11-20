#include "plyObjectManager.h"
#include "plvScene.h"

static void initRenderParams(void);
static void drawMesh(RigidScan *);

PlyObjectManager::PlyObjectManager()
{
	initRenderParams();
}

RigidScan* PlyObjectManager::addObject(char * filename)
{
	printf("\n\nLoading PLY File:  %s\n\n\n", filename);
	crope cropeString (filename);
	printf("\nNewString[%s]", cropeString.c_str());
	RigidScan *scan = CreateScanFromFile (cropeString);
	initRenderParams();
	DisplayableRealMesh *displayableMesh = new DisplayableRealMesh(scan, "SCAN");

	displayableMeshes.push_back(displayableMesh);

	theScene->meshSets.push_back(displayableMesh);

	

	printf("\n\nLoaded PLY File:  %s\n\n\n", filename);

	return scan;
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

static void drawMesh(RigidScan *scan)
{
  MeshTransport *mesh = scan->mesh();

  glMatrixMode (GL_MODELVIEW);
  glPushMatrix();
  scan->gl_xform();
  glMatrixMode (GL_TEXTURE);
  glPushMatrix();
  scan->gl_xform();

  bool bPointsOnly = (theRenderParams->polyMode == GL_POINT);
  bPointsOnly = true;
  if (theRenderParams->bRenderManipsTinyPoints) 
  {
    glPointSize (1.0);
  } 
  else 
  {
    glPointSize (2.0);
  }

  glPointSize (5.0);
  int frags = mesh->vtx.size();
  const vector<Pnt3>* vtx = NULL;
  const vector<int>* tri = NULL;
  const vector<short>* nrm = NULL;
  const vector<uchar>* color = NULL;


  for (int ifrag = 0; ifrag < frags; ifrag++) {
    vtx = mesh->vtx[ifrag];
    tri = mesh->tri_inds[ifrag];
    int nTris = tri->size() / 3;
#ifndef SCZ_NORMAL_FORCEFLOAT
    if (ifrag < mesh->nrm.size())
      nrm = mesh->nrm[ifrag];
    else
#else
	cerr << "Flat normals not supported in hack-normals-back-to-floats mode" << endl;
#endif
      nrm = NULL;
    if (nrm && nrm->size() != nTris * 3)
      nrm = NULL;
    if (ifrag < mesh->color.size())
      color = mesh->color[ifrag];
    else
      color = NULL;
    if (color && color->size() != nTris * 4)
      color = NULL;

    if (color)
      glEnable (GL_COLOR_MATERIAL);

    if (bPointsOnly) 
      glBegin (GL_POINTS);
    else 
      glBegin(GL_TRIANGLES);
    
    for (int it = 0; it < nTris; it++) {
      int it3 = 3*it;
      if (color)
		glColor4ubv (&(*color)[4*it]);
      if (nrm)
		glNormal3sv (&(*nrm)[it3]);

      glVertex3fv (&((*vtx)[(*tri)[it3]])[0]);
      glVertex3fv (&((*vtx)[(*tri)[it3+1]])[0]);
      glVertex3fv (&((*vtx)[(*tri)[it3+2]])[0]);
    }
    glEnd();
    glDisable (GL_COLOR_MATERIAL);
  }
  glMatrixMode (GL_TEXTURE);
  glPopMatrix();
  glMatrixMode (GL_MODELVIEW);
  glPopMatrix();

}

