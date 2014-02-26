#include "include/SurfaceClass.h"

//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
//class ScreenSurface

int ScreenSurface::screenNum = 0;

ScreenSurface::ScreenSurface():
width(640), height(480), bpp(32), flags(0)
{
    if ( screenNum > 0 )
        throw "DONOT create more than ONE screen!";
    if ( SDL_Init(SDL_INIT_VIDEO ) < 0  )
        throw SDL_GetError();
    pScreen = SDL_SetVideoMode(width, height, bpp, flags);
    screenNum++;
}

ScreenSurface::ScreenSurface(int w, int h, int b, Uint32 f):
width(w), height(h), bpp(b), flags(f)
{
    if ( screenNum > 0 )
        throw "DONOT create more than ONE screen!";
    if ( SDL_Init(SDL_INIT_VIDEO < 0 ) )
        throw SDL_GetError();
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

bool ScreenSurface::flip() const
{
    if ( SDL_Flip(pScreen) < 0 )
        return false;
    else return true;
}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
//class DisplaySurface

DisplaySurface::DisplaySurface(std::string file_name, const ScreenSurface& screen):
fileName(file_name)
{
    pSurface = SDL_LoadBMP(file_name.c_str());
    if ( pSurface == 0 )
        throw SDL_GetError();
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

bool DisplaySurface::blit() const
{
    if ( SDL_BlitSurface(pSurface, 0, pScreen, 0) < 0 )
        return false;
    else return true;
}


bool DisplaySurface::blit(int at_x, int at_y) const
{
    SDL_Rect offset;
    offset.x = at_x;
    offset.y = at_y;

    if ( SDL_BlitSurface(pSurface, 0, pScreen, &offset) < 0 )
        return false;
    else return true;
}

bool DisplaySurface::blit(int at_x, int at_y,
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
        return false;
    else return true;
}

bool DisplaySurface::blitToSurface(const DisplaySurface& dst_surface, int at_x, int at_y) const
{
    SDL_Rect offset;
    offset.x = at_x;
    offset.y = at_y;

    if ( &dst_surface == this )
        throw "Cannot blit surface to itself!";

    if ( SDL_BlitSurface(pSurface, 0, dst_surface.point(), &offset) < 0 )
        return false;
    else return true;
}

bool DisplaySurface::blitToSurface(const DisplaySurface& dst_surface,
                                    int at_x, int at_y,
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

    if ( &dst_surface == this )
        throw "Cannot blit surface to itself!";

    if ( SDL_BlitSurface(pSurface, &dest, dst_surface.point(), &offset) < 0 )
        return false;
    else return true;
}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA