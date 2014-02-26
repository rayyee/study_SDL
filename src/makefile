#study SDL
#@author Ray Yee
OUT = sdl_study
CXX = g++
MINGW = -lmingw32
#SDL = -lSDLmain -lSDL -lSDL_image -lSDL_ttf
SDL = -lSDLmain -lSDL

OBJECTS = SurfaceClass.o

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CXX) -o $@ $^ $(MINGW) ${SDL}

$(OBJECTS): SurfaceClass.cpp include/SurfaceClass.h
	$(CXX) -c SurfaceClass.cpp

clean:
	rm -rf *.o $(OUT)