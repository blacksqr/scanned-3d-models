TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

LIBS	+= -lglut -lGLU -lGL -ltk8.4 -ltcl8.4 -lXext -lXmu -lz -lm

INCLUDEPATH	+= ..

HEADERS	+= myglwidget.h \
	plyObjectManager.h \
	plyFileManager.h \
	PolygonUtils.h \
	VectorUtils.h \
	CommonUtils.h

SOURCES	+= mainApplication.cpp \
	myglwidget.cpp \
	plyObjectManager.cpp \
	plyFileManager.cpp \
	PolygonUtils.cpp \
	VectorUtils.cpp \
	CommonUtils.cpp

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
INCLUDEPATH	+= ../volfill/

QT += openGL

QMAKE_CXXFLAGS=-fno-for-scope -fpermissive -w

OBJECTS += ../scanalyze/OBJS/debug/*.o
OBJECTS += ../volfill/*.o

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

