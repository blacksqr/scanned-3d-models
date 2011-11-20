#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "qgl.h"
#include "qframe.h"
#include "plyObjectManager.h"
#include "plyFileManager.h"

class MyGLWidget : public QGLWidget
{
	Q_OBJECT

	public:
		MyGLWidget( QWidget* parent, const char title[20]) : QGLWidget( parent, title) 
		//MyGLWidget( QFrame* frame, const char title[20]) : QGLWidget( 30, NULL, title) 
		{
			printf("In MyGLWidget ctor()");
		//	initializeGL();
		}
		//MyGLWidget( QFrame*&, char const* );
		void initializeGL();
		//void setGeometry(const QRect&);
		void resizeGL( int width, int height );
		void paintGL();
		void keyPressEvent( QKeyEvent *e );
		void mousePressEvent( QMouseEvent *event );
		void mouseReleaseEvent( QMouseEvent *event );
		void mouseMoveEvent( QMouseEvent *event );
		void timeOut( void );

		void recalcModelView(void);
		void display3DSObject(void);
		void setupLighting(void);
		void setupCallbacks(void);
		void init(void);
		void loadPlyFile(char *filename);

	private:
		PlyObjectManager objectManager;
		PlyFileManager fileManager;

};

#endif
