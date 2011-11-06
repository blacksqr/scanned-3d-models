ifeq ($(shell uname),Linux)
CC = g++ -fno-for-scope -fpermissive -w -O2 -g
else
CC = CC -O
endif

LIBS = -lGLU -lGL -lglut

all: volfill

volfill : $(wildcard *.cc) $(wildcard *.cpp)
	$(CC) -o $@ $^ $(LIBS)

clean :
	rm -f volfill
