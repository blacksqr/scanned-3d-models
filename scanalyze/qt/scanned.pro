TEMPLATE	= app
LANGUAGE	= C++

INCLUDEPATH += ../

LIBS += -lGLU -lGL -ltk8.4 -ltcl8.4 -lXext -lXmu -lz -lm

QMAKE_CXXFLAGS=-fno-for-scope -fpermissive -w

CONFIG	+= qt warn_on release

SOURCES	+= mainApplication.cpp

OBJECTS += ../OBJS/debug/*.o

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

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

