ifeq ($(shell uname),Linux)
CC = g++ -fno-for-scope -fpermissive -w -O2 -g
else
CC = CC -O
endif

CXXSRCS = ActiveGrid.cc ChunkLink.cc main.cc Matrix2f.cc \
	Matrix4f.cc OccGridRLE.cc util.cc ChunkAllocator.cc \
	fb.cc MainWrapper.cc Matrix3f.cc OccGrid.cc Quaternion.cc \
	Vec3f.cc

LIBS = -lGLU -lGL -lglut
OBJS = $(CXXSRCS:.cc=.o) 

all: volfill

volfill: ${OBJS}
	${CC} -o $@ $^ $(LIBS) ${CFLAGS} 

%.o: %.cc $(DEPS)
	$(CC) -o $@ -c $<

clean:
	rm -f volfill ${OBJS}
	@echo "all cleaned up!"
