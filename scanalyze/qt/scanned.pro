TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

LIBS	+= -lGLU -lGL -ltk8.4 -ltcl8.4 -lXext -lXmu -lz -lm

INCLUDEPATH	+= ../

SOURCES	+= mainApplication.cpp

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

QMAKE_CXXFLAGS=-fno-for-scope -fpermissive -w



OBJECTS += ../OBJS/debug/*.o



unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

