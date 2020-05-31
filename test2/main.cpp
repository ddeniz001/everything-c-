/*Created by Denizhan Deniz
Copyright @ 2020 Denizhan Deniz. All rights reserved.*/

#include "SDL2.h"
#include <stdio.h>

const int WIDTH = 640;
const int HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window *gwindow = NULL;
SDL_Surface *gscreenSurface = NULL;
SDL_Surface *ghelloWorld = NULL;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("cannot initialize.");
        success = false;
    }
    else
    {
        gwindow = SDL_CreateWindow("TITLE",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (gwindow == NULL)
        {
            printf("could not create window. %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gscreenSurface = SDL_GetWindowSurface(gwindow);
        }
    }
    return success;


}

// load image
bool loadMedia()
{
    bool success = true;

    ghelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    if (ghelloWorld == NULL)
    {
        printf("Could not find media.\n");
        success = false;
    }
    return success;

}

// cleanup
void close()
{
    // get rid of image
    SDL_FreeSurface(ghelloWorld);
    ghelloWorld = NULL;

    // get rid of window
    SDL_DestroyWindow(gwindow);
    gwindow = NULL;

    SDL_Quit();

}



int main(int argc, char* args[])
{
    // startup
    if (!init())
    {
        printf("Could not initialize.\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Could not load media.\n");
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                // 1st argument is source image, 3rd argument is destination
                SDL_BlitSurface(ghelloWorld, NULL, gscreenSurface, NULL);

                SDL_UpdateWindowSurface(gwindow);

            }
        }
    }

    close();
    return 0;
}







