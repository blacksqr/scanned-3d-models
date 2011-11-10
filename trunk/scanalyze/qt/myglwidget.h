#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "qgl.h"
#include "qframe.h"

class MyGLWidget : QGLWidget
{
	Q_OBJECT

	public:
		MyGLWidget( QFrame* , const char[20] ) : QGLWidget( ) {}
		//MyGLWidget( QFrame*&, char const* );
		void initializeGL();
		void setGeometry(const QRect&);
		void resizeGL( int width, int height );
		void paintGL();
		void keyPressEvent( QKeyEvent *e );
		void mousePressEvent( QMouseEvent *event );
		void mouseReleaseEvent( QMouseEvent *event );
		void moveEvent( QMoveEvent *event );

		void recalcModelView(void);
		void display3DSObject(void);
		void setupLighting(void);
		void setupCallbacks(void);
		void init(void);
};

#endif
