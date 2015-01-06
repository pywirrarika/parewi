/*
 * main.c
 *
 * Description: This is the starting point for the Parewi 
 *              platform. 
 *
 * Authors: Manuel Mager <pywirrarika@gmail.com> (c) 2015
 * Copyright: GPL v3 or later
 *
 */


#include<config.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
#include "SDL_image.h"

#include "parewi.h"

lua_State* l;

int
main(int argc, char **argv)
{
    // Local variables
    int flags;  
    int initted;
    int start = 0;
    int result;
    char alo[60] = "";
    int quit = 0;

    SDL_Window *win = NULL;
    SDL_Event event;
    SDL_Renderer *render = NULL;
    SDL_Surface *image = NULL;
    SDL_Surface *screen = NULL;

    parewiS *P;

    P = parewi_create_obj();

    // Starting SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s", SDL_GetError()); 
        return 1;
    }
    //Crating the main window handler for SDL
    win = SDL_CreateWindow("Hello FES Cuautitlan!", 100, 100, 640, 480,\
            SDL_WINDOW_SHOWN);
    if(!win)
    {
        printf("Error creating SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // load support for the JPG and PNG image formats
    flags=IMG_INIT_JPG|IMG_INIT_PNG;
    initted=IMG_Init(flags);
    // handle error
    if(initted&flags != flags) 
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
    screen = SDL_GetWindowSurface(win);
    SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );

    sprintf(alo, "%s/images/linux.bmp", DATA_PREFIX);
    printf("%s\n", alo);
    image = SDL_LoadBMP(alo);
    if(!image)
    {
        fprintf(stderr, "Error: couldn't load %s, %s\n", alo, IMG_GetError());
    }   
    else
    {
        SDL_BlitSurface(image, NULL, screen, NULL);
    }

    result = (luaL_loadfile(P->L, "lua_exp.lua") || lua_pcall(P->L,0,0,0));
    if(result)
        fprintf(stderr, "Error: couldn't load LUA Script\n");

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
        start = SDL_GetTicks( );
        SDL_UpdateWindowSurface( win );
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    parewi_free_obj(P); 
    printf("Hola Grupo de software libre de la FES Cuautitlán %s!\n", DATA_PREFIX);
    return 0;
}
