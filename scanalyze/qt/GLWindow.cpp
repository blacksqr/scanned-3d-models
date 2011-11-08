#include <windows.h>
#include <gl/gl.h>
#include <GL/glut.h>
#include <stdio.h>


#include "PolygonUtils.h"
#include "VectorUtils.h"
#include "3dsloader.h"
#include "Model_PLY.h"

object obj;
char objectFile[150];
int zooming;
float zoomfactor;
int beginx, beginy, lastX, lastY;
static const int RADIUS = 1;
float elevation;
float swing;
bool buttonPressed;

Model_PLY plyLoader;

void recalcModelView(void);


/**
* Draws the 3DS object into the scene
**/
void display3DSObject(void)
{
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
}


/**
 *  Repaints the entire openGL window.  The first time this function is called
 *  the initialization code will be called
 **/
void draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glScalef(float(zoomfactor),float(zoomfactor),float(zoomfactor));
	glTranslatef(0.0, 0.0, -RADIUS);
	recalcModelView();
	
	//display3DSObject();
	plyLoader.Draw();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

/**
 *  Handles the rotation of the scene due to mouse dragging
 **/
void recalcModelView(void)
{
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(0, 0, -RADIUS);
	glRotatef(elevation, 1, 0, 0);
	glRotatef(swing, 0, 1, 0);
}

/**
 *  This function handles all events sent to the openGL window.  This includes
 * mouse movements, key presses and even redraw events
 **/
void mouseButtonPressedCallback(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		buttonPressed = true;
		if(button == GLUT_MIDDLE_BUTTON)
			zooming = true;		
	}
	else
	{
		buttonPressed = false;
		zooming = false;
	}

	lastX = x;
	lastY = y;
	beginx = x;
	beginy = y;
}

void mouseMotionCallback(int x, int y)
{
	if(!zooming)
	{
		// The current elevation and swing of the camera.  We simply
		// append the amount of mouse movement in the x and y direction to
		// the currently running elevation and swing.
		elevation += (y - lastY);
		swing += (x - lastX);


		// tell openGL to redraw the screen.  The whole screen has to redraw so
		// we might as well do it this way.
		glutPostRedisplay();

		// keep track of the current mouse movement so that we can use it
		// for the next mouse movement.
		lastX = x;
		lastY = y;

		return;
	}
	else
	{
		zoomfactor = zoomfactor * (1.0 + (((float) (beginy - y)) / 640));
		beginx = x;
		beginy = y;
		glutPostRedisplay();

		return;
	}

}


void setupLighting(void)
{
  // set up light 0
  GLfloat lightZeroPosition[] = {10.0, 4.0, -2.0, 0.0};
  GLfloat lightZeroColor[] = {0.0, 0.4, 1.0, 1.0}; //0x0066FF -- blue-ish
  GLfloat debug_lightZeroColor[] = {1.0, 1.0, 1.0, 1.0}; //0x00FF33 -- white-ish
  
  glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);



  // set up light 1
  GLfloat lightOnePosition[] = {-5.0, 0.0, 2.0, 0.0};
  GLfloat lightOneColor[] = {0.65, 1.0, 0.52, 1.0}; //0x00FF33 -- green-ish  A6D785
  GLfloat debug_lightOneColor[] = {1.0, 1.0, 1.0, 1.0}; //0x00FF33 -- white-ish
  GLfloat lightOneSpecular[] = {1.0, 1.0, 1.0, 1.0};
  
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

/**
 * Setups up all of the various callbacks needed by this application
 **/
void setupCallbacks(void)
{
  glutDisplayFunc(draw);
  glutMouseFunc(mouseButtonPressedCallback);
  glutMotionFunc(mouseMotionCallback);

}

void init(void)
{
	glViewport(0, 0, 890, 890);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
		

	// setup the projection type = perspective
	glMatrixMode(GL_PROJECTION);

	glOrtho(-10,10,-10,10,-900,10000);

	// setup the camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set up all scene lighting starting conditions
	GLfloat local_view[] = {0.0};
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);

		  
  	zoomfactor = 1.0;
	zooming = false;
	lastX = -1;
	lastY = -1;
	buttonPressed = false;
	elevation = 0;
	swing = 0;

	printf("\n\nLoading PLY File\n\n\n");
	plyLoader.Load("plyfiles/pickup_big.ply");
	printf("\n\nLoaded PLY File\n\n\n");

}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 640);
  
  glutCreateWindow("PLY Viewer");
 
  // all mouse and keyboard callback should get setup here
  setupCallbacks();

  init();
  
  glEnable(GL_DEPTH_TEST);


  // setup the projection type = perspective
  glMatrixMode(GL_PROJECTION);

  // setup the camera position
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); 

  // set up all scene lighting starting conditions
  setupLighting();


  // start the program loop
  glutMainLoop();
  return 0; 
}