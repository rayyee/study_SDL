//FileName: SurfaceClass.h

#ifndef SURFACE_CLASS_H
#define SURFACE_CLASS_H

#include <iostream>
#include <string>
#include "SDL/SDL.h"

using std::string;

class ScreenSurface
{
private:
    static int screenNum;
    int width;
    int height;
    int bpp;
    Uint32 flags;
    SDL_Surface* pScreen;
public:
    ScreenSurface();
    ScreenSurface(int w, int h, int b = 0, Uint32 f = 0);
    ~ScreenSurface();
    SDL_Surface* point() const;
    bool flip() const;
};

class DisplaySurface
{
private:
    string fileName;
    SDL_Surface* pSurface;
    SDL_Surface* pScreen;
public:
    DisplaySurface(string file_name, const ScreenSurface& screen);
    ~DisplaySurface();
    SDL_Surface* point() const;
    bool blit() const;
    bool blit(int at_x, int at_y) const;
    bool blit(int at_x, int at_y,
                int from_x, int from_y, int w, int h,
                int delta_x = 2, int delta_y = 2) const;
    bool blitToSurface(const DisplaySurface& dst_surface,
                        int at_x = 0, int at_y = 0) const;
    bool blitToSurface(const DisplaySurface& dst_surface,
                        int at_x, int at_y,
                        int from_x, int from_y, int w, int h,
                        int delta_x = 2, int delta_y = 2) const;
};

#endif