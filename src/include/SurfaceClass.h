//UVi Soft (2008)
//Long Fei (lf426), E-mail: zbln426@163.com

//FileName: SurfaceClass.h

#ifndef SURFACE_CLASS_H
#define SURFACE_CLASS_H

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

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
    void flip() const;
    void fillColor(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0) const;
};

class DisplaySurface
{
private:
    std::string fileName;
    SDL_Surface* pSurface;
    SDL_Surface* pScreen;
public:
    DisplaySurface(const std::string& file_name, const ScreenSurface& screen);
    ~DisplaySurface();
    SDL_Surface* point() const;
    void blit() const;
    void blit(int at_x, int at_y) const;
    void blit(int at_x, int at_y,
                int from_x, int from_y, int w, int h,
                int delta_x = 0, int delta_y = 0) const;
    void colorKey(Uint8 r = 0, Uint8 g = 0xFF, Uint8 b = 0xFF, Uint32 flag = SDL_SRCCOLORKEY);
};

class ErrorInfo
{
private:
    std::string info;
public:
    ErrorInfo():info("Unknown ERROR!")
    {}
    ErrorInfo(const char* c_str)
    {
        info = std::string(c_str);
    }
    ErrorInfo(const std::string& str):info(str)
    {}
    void show() const
    {
        std::cerr << info << std::endl;
    }
};

#endif