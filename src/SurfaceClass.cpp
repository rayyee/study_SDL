//UVi Soft (2008)
//Long Fei (lf426), E-mail: zbln426@163.com

#include "include/SurfaceClass.h"

//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
//class ScreenSurface

int ScreenSurface::screenNum = 0;

ScreenSurface::ScreenSurface():
width(640), height(480), bpp(32), flags(0)
{
    if ( screenNum > 0 )
        throw ErrorInfo("DONOT create more than ONE screen!");
    if ( SDL_Init(SDL_INIT_VIDEO < 0 ) )
        throw ErrorInfo(SDL_GetError());
    pScreen = SDL_SetVideoMode(width, height, bpp, flags);
    screenNum++;
}

ScreenSurface::ScreenSurface(int w, int h, int b, Uint32 f):
width(w), height(h), bpp(b), flags(f)
{
    if ( screenNum > 0 )
        throw ErrorInfo("DONOT create more than ONE screen!");
    if ( SDL_Init(SDL_INIT_VIDEO < 0 ) )
        throw ErrorInfo(SDL_GetError());
    pScreen = SDL_SetVideoMode(width, height, bpp, flags);
    screenNum++;
}

ScreenSurface::~ScreenSurface()
{
    SDL_Quit();
}

SDL_Surface* ScreenSurface::point() const
{
    return pScreen;
}

void ScreenSurface::flip() const
{
    if ( SDL_Flip(pScreen) < 0 )
        throw ErrorInfo(SDL_GetError());
}


void ScreenSurface::fillColor(Uint8 r, Uint8 g, Uint8 b) const
{
     if ( SDL_FillRect(pScreen, 0, SDL_MapRGB(pScreen->format, r, g, b)) < 0 )
         throw ErrorInfo(SDL_GetError());
}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
//class DisplaySurface

DisplaySurface::DisplaySurface(const std::string& file_name, const ScreenSurface& screen):
fileName(file_name)
{
    SDL_Surface* pSurfaceTemp = IMG_Load(file_name.c_str());
    if ( pSurfaceTemp == 0 )
        throw ErrorInfo(SDL_GetError());
    pSurface = SDL_DisplayFormat(pSurfaceTemp);
    if ( pSurface == 0 )
        throw ErrorInfo(SDL_GetError());
    SDL_FreeSurface(pSurfaceTemp);
    pScreen = screen.point();
}

DisplaySurface::~DisplaySurface()
{
    SDL_FreeSurface(pSurface);
}

SDL_Surface* DisplaySurface::point() const
{
    return pSurface;
}

void DisplaySurface::blit() const
{
    if ( SDL_BlitSurface(pSurface, 0, pScreen, 0) < 0 )
        throw ErrorInfo(SDL_GetError());
}


void DisplaySurface::blit(int at_x, int at_y) const
{
    SDL_Rect offset;
    offset.x = at_x;
    offset.y = at_y;

    if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset) < 0 )
        throw ErrorInfo(SDL_GetError());
}

void DisplaySurface::blit(int at_x, int at_y,
                          int from_x, int from_y, int w, int h,
                          int delta_x, int delta_y) const
{
    SDL_Rect offset;
    offset.x = at_x - delta_x;
    offset.y = at_y - delta_y;

    SDL_Rect dest;
    dest.x = from_x - delta_x;
    dest.y = from_y - delta_y;
    dest.w = w + delta_x*2;
    dest.h = h + delta_y*2;

    if ( SDL_BlitSurface(pSurface, &dest, pScreen, &offset) < 0 )
        throw ErrorInfo(SDL_GetError());
}

void DisplaySurface::colorKey(Uint8 r, Uint8 g, Uint8 b, Uint32 flag)
{
    Uint32 colorkey = SDL_MapRGB(pSurface->format, r, g, b);
    if ( SDL_SetColorKey(pSurface, flag, colorkey ) < 0 )
        throw ErrorInfo(SDL_GetError());
}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA