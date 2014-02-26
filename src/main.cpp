#include "include/SurfaceClass.h"

void game();
int main(int argc ,char* argv[])
{
    try {
        game();
    }
    catch ( const char* s ) {
        std::cerr << s << std::endl;
        return -1;
    }
    
    return 0;
}

void game()
{
    //Create a SDL screen.
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    ScreenSurface screen(SCREEN_WIDTH, SCREEN_HEIGHT);

    //Create 2 SDL surface for the screen that just created.
    DisplaySurface backGround("background.bmp", screen);
    DisplaySurface frontImage("role.bmp", screen);
    //VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    //way2: If use blitToSurface, must get a copy of backGround.
/*
    DisplaySurface backGroundCopy("bg.bmp", screen);
*/
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    //Blit backGround surface to screen and flip the screen.
    if ( backGround.blit() == false )
        throw SDL_GetError();
    if ( screen.flip() == false )
        throw SDL_GetError();

    //variable for main loop.
    //key event for up, down, left and right.
    Uint8* keys;
    //moving image's coordinate.
    int xpos = 0;
    int ypos = 0;
    //moving image's size.
    const int IMG_WIDTH = 128;
    const int IMG_HEIGHT = 128;
    //main loop.
    bool gameOver = false;
    while( gameOver == false ){
        //press ESC or click X to quit.
        SDL_Event gameEvent;
        while ( SDL_PollEvent(&gameEvent) != 0 ){
            if ( gameEvent.type == SDL_QUIT ){
                gameOver = true;
            }
            if ( gameEvent.type == SDL_KEYUP ){
                if ( gameEvent.key.keysym.sym == SDLK_ESCAPE ){
                    gameOver = true;
                }
            }
        }
        //key event to move image.
        keys = SDL_GetKeyState(0);
        if ( keys[SDLK_UP] || keys[SDLK_w] ){
            ypos -= 1;
        }
        if ( keys[SDLK_DOWN]|| keys[SDLK_s] ){
            ypos += 1;
        }
        if ( keys[SDLK_LEFT]|| keys[SDLK_a] ){
            xpos -= 1;
        }
        if ( keys[SDLK_RIGHT]|| keys[SDLK_d] ){
            xpos += 1;
        }

        //Hold moving image on the backGround area.
        if ( xpos <= 0 )
            xpos = 0;
        if ( xpos >= SCREEN_WIDTH - IMG_WIDTH )
            xpos = SCREEN_WIDTH - IMG_WIDTH;
        if ( ypos <= 0 )
            ypos = 0;
        if ( ypos >= SCREEN_HEIGHT - IMG_HEIGHT )
            ypos = SCREEN_HEIGHT - IMG_HEIGHT;

        //VVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
        //way1: blit surface to screen
        //Blit a part of backGround ( a rectangular area ) to screen,
        //then the original blitted backGround can be "cleaned".
        if ( backGround.blit(xpos, ypos, xpos, ypos, IMG_WIDTH, IMG_HEIGHT) == false )
            throw SDL_GetError();
        //Blit the image to screen.
        if ( frontImage.blit(xpos, ypos) == false )
            throw SDL_GetError();
        //Flip the screen
        if ( screen.flip() == false )
            throw SDL_GetError();
        //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

        //VVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
        //way2: blit surface to surface, then blit the last surface to screen
/*
        if ( backGroundCopy.blitToSurface(backGround, xpos, ypos, xpos, ypos, IMG_WIDTH, IMG_HEIGHT) == false )
            throw SDL_GetError();
        if ( frontImage.blitToSurface(backGround, xpos, ypos) == false )
            throw SDL_GetError();
        if ( backGround.blit() == false )
            throw SDL_GetError();
        if ( screen.flip() == false )
            throw SDL_GetError();
*/
        //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    }

    return;
}