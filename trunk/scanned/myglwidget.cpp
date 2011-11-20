//#include <gl/gl.h>
#include <stdio.h>
#include <rope.h>
#include <vector.h>

#include "ScanFactory.h"
#include "MeshTransport.h"
#include "DisplayMesh.h"
#include "plvDraw.h"
#include "plvGlobals.h"
#include "plvScene.h"
//#include "PolygonUtils.h"
//#include "VectorUtils.h"
//#include "Model_PLY.h"
#include "myglwidget.h"

//object obj;
//char objectFile[150];
int zooming;
float zoomfactor;
int beginx, beginy, lastX, lastY;
static const int RADIUS = 1;
float elevation;
float swing;
bool buttonPressed;

RigidScan *scan;

static void initRenderParams ( void );

void MyGLWidget::timeOut()
{
	updateGL();
}

void MyGLWidget::initializeGL()
{
	printf("MyGLWidget::initializeGL() called");
	init();
}

void MyGLWidget::resizeGL( int width, int height )
{
}

void MyGLWidget::paintGL()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glScalef(float(zoomfactor),float(zoomfactor),float(zoomfactor));
	glTranslatef(0.0, 0.0, -RADIUS);
	recalcModelView();
	
	if(scan)
	{
        for(int i = 0; i < displayableMeshes.size(); i++)
		{
			drawMesh(displayableMeshes[i]->getMeshData()->mesh());
		}
	}

	glPopMatrix();

	glFlush();
}

void MyGLWidget::drawMesh(MeshTransport *mesh)
{
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
}
  
void MyGLWidget::keyPressEvent( QKeyEvent *e )
{
	printf("Key Pressed");
	// do nothing...yet
}


void MyGLWidget::mousePressEvent( QMouseEvent *event )
{
	printf("Mouse PRessed");
	buttonPressed = true;
	if(event->button() == Qt::MidButton)
		zooming = true;		

	lastX = event->x();
	lastY = event->y();
	beginx = event->x();
	beginy = event->y();

	updateGL();
}

void QWidget::mouseReleaseEvent( QMouseEvent *event )
{
	printf("BaseClass::Mouse Released");

}
void MyGLWidget::mouseReleaseEvent( QMouseEvent *event )
{
	printf("Mouse Released");
	buttonPressed = false;
	zooming = false;

	lastX = event->x();
	lastY = event->y();
	beginx = event->x();
	beginy = event->y();

	updateGL();
}

void MyGLWidget::mouseMoveEvent( QMouseEvent *event )
{
	if(buttonPressed)
	{
		if(!zooming)
		{
			// The current elevation and swing of the camera.  We simply
			// append the amount of mouse movement in the x and y direction to
			// the currently running elevation and swing.
			elevation += (event->y() - lastY);
			swing += (event->x() - lastX);
	
	
			// tell openGL to redraw the screen.  The whole screen has to redraw so
			// we might as well do it this way.
			//glutPostRedisplay();
	
			// keep track of the current mouse movement so that we can use it
			// for the next mouse movement.
			lastX = event->x();
			lastY = event->y();
			updateGL();
	
			return;
		}
		else
		{
			zoomfactor = zoomfactor * (1.0 + (((float) (beginy - event->pos().y())) / 640));
			beginx = event->x();
			beginy = event->y();
			//glutPostRedisplay();
	
			updateGL();
			return;
		}
	}

}
  

/**
* Draws the 3DS object into the scene
**/
void MyGLWidget::display3DSObject(void)
{
/*
	int l_index;
	
    glBegin(GL_TRIANGLES);

	for (l_index=0;l_index<obj.polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Coordinates of the first vertex
		glNormal3f( obj.vertex[ obj.polygon[l_index].a ].normal.x,
                    obj.vertex[ obj.polygon[l_index].a ].normal.y,
                    obj.vertex[ obj.polygon[l_index].a ].normal.z);
		glTexCoord2f( obj.mapcoord[ obj.polygon[l_index].a ].u,
                      obj.mapcoord[ obj.polygon[l_index].a ].v);
		glVertex3f( obj.vertex[ obj.polygon[l_index].a ].x,
                    obj.vertex[ obj.polygon[l_index].a ].y,
                    obj.vertex[ obj.polygon[l_index].a ].z); //Vertex definition
			

        //----------------- SECOND VERTEX -----------------
        // Coordinates of the second vertex
		glNormal3f( obj.vertex[ obj.polygon[l_index].b ].normal.x,
                    obj.vertex[ obj.polygon[l_index].b ].normal.y,
                    obj.vertex[ obj.polygon[l_index].b ].normal.z);
		glTexCoord2f( obj.mapcoord[ obj.polygon[l_index].b ].u,
                      obj.mapcoord[ obj.polygon[l_index].b ].v);
        glVertex3f( obj.vertex[ obj.polygon[l_index].b ].x,
                    obj.vertex[ obj.polygon[l_index].b ].y,
                    obj.vertex[ obj.polygon[l_index].b ].z);

		 //----------------- THIRD VERTEX -----------------
        // Coordinates of the Third vertex
		glNormal3f( obj.vertex[ obj.polygon[l_index].c ].normal.x,
                    obj.vertex[ obj.polygon[l_index].c ].normal.y,
                    obj.vertex[ obj.polygon[l_index].c ].normal.z);
		glTexCoord2f( obj.mapcoord[ obj.polygon[l_index].c ].u,
                      obj.mapcoord[ obj.polygon[l_index].c ].v);
		glVertex3f( obj.vertex[ obj.polygon[l_index].c ].x,
                    obj.vertex[ obj.polygon[l_index].c ].y,
                    obj.vertex[ obj.polygon[l_index].c ].z);			
    }
	
    glEnd();
*/
}

/**
 *  Handles the rotation of the scene due to mouse dragging
 **/
void MyGLWidget::recalcModelView(void)
{
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(0, 0, -RADIUS);
	glRotatef(elevation, 1, 0, 0);
	glRotatef(swing, 0, 1, 0);
}

void MyGLWidget::setupLighting(void)
{
	// set up light 0
	//GLfloat lightZeroPosition[] = {1.0, 1.0, -1.0, 0.0};
	GLfloat lightZeroPosition[] = {0.1, 0.1, -0.1, 0.0};
	GLfloat lightZeroColor[] = {0.0, 0.4, 1.0, 1.0}; //0x0066FF -- blue-ish
  
	glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);



	// set up light 1
	GLfloat lightOnePosition[] = {-1.0, 0.0, 1.0, 0.0};
	GLfloat lightOneColor[] = {0.65, 1.0, 0.52, 1.0}; //0x00FF33 -- green-ish  A6D785
  
	glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightOneColor);



	GLfloat local_view[] = {0.0};
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);


	// to start...turn on both lights
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void MyGLWidget::init(void)
{
	printf("MyGLWidget::init() called");
	setMouseTracking( true );
	glViewport(0, 0, 680, 610);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// setup the projection type = perspective
	glMatrixMode(GL_PROJECTION);

	glOrtho(-10,10,-10,10,-900,10000);
	//glOrtho(-10,680,-10,610,-900,10000);

	// setup the camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set up all scene lighting starting conditions
	GLfloat local_view[] = {0.0};
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);

  	// set up all scene lighting starting conditions
  	setupLighting();

		  
  	//zoomfactor = 1.0;
  	zoomfactor = 51.0;
	zooming = false;
	lastX = -1;
	lastY = -1;
	buttonPressed = false;
	elevation = 0;
	swing = 0;

    initRenderParams();

//	loadPlyFile("plyfiles/pickup_big.ply");
}

void MyGLWidget::loadPlyFile(char *filename)
{
	//filename = "/home/swilber/school/scanned-3d-models/scanned-3d-models/samples/range-scan/bunny/data/bun000.ply";
	printf("\n\nLoading PLY File:  %s\n\n\n", filename);
	crope cropeString (filename);
	printf("\nNewString[%s]", cropeString.c_str());
	scan = CreateScanFromFile (cropeString);
	initRenderParams();
	DisplayableRealMesh *displayableMesh = new DisplayableRealMesh(scan, "SCAN");

	displayableMeshes.push_back(displayableMesh);

	theScene->meshSets.push_back(displayableMesh);

	updateGL();
	

	printf("\n\nLoaded PLY File:  %s\n\n\n", filename);
}

static void
initRenderParams()
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
