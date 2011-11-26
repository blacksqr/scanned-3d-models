#include <stdio.h>
#include <stdlib.h>
#include <rope.h>
#include <vector.h>

#include "myglwidget.h"

int zooming;
float zoomfactor;
int beginx, beginy, lastX, lastY;
static const int RADIUS = 1;
float elevation;
float swing;
bool buttonPressed;


static void initRenderParams ( void );

void MyGLWidget::timeOut()
{
	updateGL();
}

void MyGLWidget::initializeGL()
{
	init();
	fileManager.setObjectManager(&objectManager);
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
	
	objectManager.drawAllObjects();

	glPopMatrix();

	glFlush();
}

void MyGLWidget::keyPressEvent( QKeyEvent *e )
{
	// do nothing...yet
}


void MyGLWidget::mousePressEvent( QMouseEvent *event )
{
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

}
void MyGLWidget::mouseReleaseEvent( QMouseEvent *event )
{
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
	GLfloat lightZeroColor[] = {1.0, 1.0, 1.0, 1.0}; //0x0066FF -- blue-ish
  
	glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);



	// set up light 1
	GLfloat lightOnePosition[] = {-1.0, 0.0, 1.0, 0.0};
	GLfloat lightOneColor[] = {1.0, 1.0, 1.0, 1.0}; //0x00FF33 -- green-ish  A6D785
  
	glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightZeroColor);
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


}

void MyGLWidget::loadPlyDirectory(char *directory)
{
	fileManager.scanGroupDirectoryChanged(directory);
	updateGL();
}

void MyGLWidget::scanGroupAngleChanged(int value)
{
	objectManager.scanGroupAngleChanged(value);
	updateGL();
}
