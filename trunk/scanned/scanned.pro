TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

LIBS	+= -lGLU -lGL -ltk8.4 -ltcl8.4 -lXext -lXmu -lz -lm

INCLUDEPATH	+= ..

HEADERS	+= myglwidget.h \
	Model_PLY.h \
	PolygonUtils.h \
	VectorUtils.h

SOURCES	+= mainApplication.cpp \
	myglwidget.cpp \
	Model_PLY.cpp \
	PolygonUtils.cpp \
	VectorUtils.cpp

FORMS	= form1.ui

IMAGES	= images/filenew \
	images/fileopen \
	images/filesave \
	images/print \
	images/undo \
	images/redo \
	images/editcut \
	images/editcopy \
	images/editpaste \
	images/searchfind

INCLUDEPATH	+= .
INCLUDEPATH	+= /usr/include
INCLUDEPATH	+= ../scanalyze/

QT += openGL

QMAKE_CXXFLAGS=-fno-for-scope -fpermissive -w

OBJECTS += ../scanalyze/OBJS/debug/*.o

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

