#study SDL
#@author Ray Yee
OUT = ../bin/sdl_study
CXX = g++
MINGW = -lmingw32
#SDL = -lSDLmain -lSDL -lSDL_image -lSDL_ttf
SDL = -lSDLmain -lSDL -lSDL_image

OBJECTS = main.o SurfaceClass.o

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CXX) -o $@ $^ $(MINGW) ${SDL}

$(OBJECTS): main.cpp SurfaceClass.cpp include/SurfaceClass.h
	$(CXX) -c main.cpp SurfaceClass.cpp

clean:
	rm -rf *.o $(OUT).exe