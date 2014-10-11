#include<config.h>
#include<stdio.h>
#include<SDL2/SDL.h>

int
main(int argc, char **argv)
{

    SDL_Window *win = NULL;
    SDL_Event event;
    SDL_Render *render;
    SDL_Surface *image;

    int quit = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s", SDL_GetError()); 
        return 1;
    }
    win = SDL_CreateWindow("Hello FES Cuautitlan!", 100, 100, 640, 480,\
            SDL_WINDOW_SHOWN);
    if(!win)
    {
        printf("Error creating SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("Hola Grupo de software libre de la FES Cuautitlán\n");
    return 0;
}
