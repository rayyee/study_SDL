//UVi Soft (2008)
//Long Fei (lf426), E-mail: zbln426@163.com

#include "include/SurfaceClass.h"

int game(int argc, char* argv[]);
int main(int argc ,char* argv[])
{
    int mainRtn = 0;
    try {
        mainRtn = game(argc, argv);
    }
    catch ( const ErrorInfo& info ) {
        info.show();
        return -1;
    }
    
    return mainRtn;
}

int game(int argc ,char* argv[])
{
    //Create a SDL screen.
    const int SCREEN_WIDTH = 1450;
    const int SCREEN_HEIGHT = 900;
    ScreenSurface screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    //Fill background with white.(default is black)
    screen.fillColor(0x00, 0x00, 0x00);

    //Load a sprite pic, and colorkey.(default color: R=0,G=0xFF,B=0xFF)
    DisplaySurface sprite("adventurer.png", screen);
    sprite.colorKey();

    //the 4 dots's coordinate.
    //int atX[4] = {0, 540, 0, 540};
    //int atY[4] = {0, 0, 380, 380};
    //the 4 dots's clip coordinate.
    //int fromX[4] = {0, 100, 0 ,100};
    //int fromY[4] = {0, 0, 100, 100};
    //dots's size.
    const int IMG_WIDTH = 128;
    const int IMG_HEIGHT = 128;
    //clip dots.
    //for ( int i = 0; i < 4; i++ )
        //sprite.blit(atX[i], atY[i], fromX[i], fromY[i], IMG_WIDTH, IMG_HEIGHT);
    //Draw dots and screen.
    //screen.flip();
    
    //press ESC or click X to quit.
    bool gameOver = false;
	short index = 0;
    SDL_Event gameEvent;
    while( gameOver == false ){
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
		
		index ++;
		if (index > 38) index = 0;
		
		screen.flip();
		sprite.blit(0, 0, index * IMG_HEIGHT, 0, IMG_WIDTH, IMG_HEIGHT);
    }

    return 0;
}