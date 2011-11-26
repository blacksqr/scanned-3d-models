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

static int patchdata[][16] =
{
    /* rim */
  {102, 103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15},
    /* body */
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27},
  {24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40},
    /* lid */
  {96, 96, 96, 96, 97, 98, 99, 100, 101, 101, 101,
    101, 0, 1, 2, 3,},
  {0, 1, 2, 3, 106, 107, 108, 109, 110, 111, 112,
    113, 114, 115, 116, 117},
    /* bottom */
  {118, 118, 118, 118, 124, 122, 119, 121, 123, 126,
    125, 120, 40, 39, 38, 37},
    /* handle */
  {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56},
  {53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
    28, 65, 66, 67},
    /* spout */
  {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83},
  {80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
    92, 93, 94, 95}
};
/* *INDENT-OFF* */

static float cpdata[][3] =
{
    {0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
    -0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
    {0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
    0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
    2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
    2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
    {1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
    1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
    {0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
    0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
    0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
    {1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
    {1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
    -1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
    -0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
    2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
    2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
    2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
    {-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
    -0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
    1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
    -0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
    1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
    0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
    0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
    {2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
    -0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
    2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
    {3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
    {3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
    {2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
    3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
    3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
    -0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
    2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
    2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
    2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
    {0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
    -0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
    0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
    {0.84, -1.5, 0.075}
};

/* *INDENT-ON* */

/* This "fastTeapot" routine is faster than glutSolidTeapot. */
static void
fastSolidTeapot(GLint grid, GLdouble scale)
{
  float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
  long i, j, k, l;

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_MAP2_VERTEX_3);
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);
  glTranslatef(0.0, 0.0, -1.5);
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 4; k++) {
        for (l = 0; l < 3; l++) {
          p[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
          q[j][k][l] = cpdata[patchdata[i][j * 4 + (3 - k)]][l];
          if (l == 1)
            q[j][k][l] *= -1.0;
          if (i < 6) {
            r[j][k][l] =
              cpdata[patchdata[i][j * 4 + (3 - k)]][l];
            if (l == 0)
              r[j][k][l] *= -1.0;
            s[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
            if (l == 0)
              s[j][k][l] *= -1.0;
            if (l == 1)
              s[j][k][l] *= -1.0;
          }
        }
      }
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &p[0][0][0]);
    glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &q[0][0][0]);
    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    if (i < 6) {
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &r[0][0][0]);
      glEvalMesh2(GL_FILL, 0, grid, 0, grid);
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &s[0][0][0]);
      glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    }
  }
}


void MyGLWidget::paintGL()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, -40);
	glScalef(float(zoomfactor),float(zoomfactor),float(zoomfactor));
	glTranslatef(0.0, 0.0, -RADIUS);
	recalcModelView();
	
	//QPainter painter(this);
	//painter.begin(this);
	objectManager.drawAllObjects();
	//painter.end();
	//fastSolidTeapot(10, 0.1);

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
	GLfloat lightZeroPosition[] = {-100.7, 100.0, -100.2, 0.0};
	GLfloat lightZeroColor[] = {1.0, 1.0, 1.0, 1.0}; //0x0066FF -- blue-ish
  
	glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_SHININESS, 100);



	// set up light 1
	GLfloat lightOnePosition[] = {0.2, 0.0, 0.5, 0.0};
	GLfloat lightOneColor[] = {1.0, 1.0, 1.0, 1.0}; //0x00FF33 -- green-ish  A6D785
  
	glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightZeroColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightOneColor);



	//GLfloat local_view[] = {0.0};
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);


	// to start...turn on both lights
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
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
	glLoadIdentity();
//	glOrtho(-10,10,-10,10,-10,10);
	glOrtho(-10,10,-10,10,-900,10000);
	//glOrtho(-10,680,610,0.0f, 0.0f, 1.0f);

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
