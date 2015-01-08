/*
 * parewi.h
 *
 * Description: This header contains the definition of
 *              the basic structures for all the platform.
 *
 * Authors: Manuel Mager <pywirrarika@gmail.com> (c) 2015
 * Copyright: GPL v3 or later
 *
 */

#ifndef PAREWI_H
#define PAREWI_H

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
#include<SDL2/SDL.h>
#include<glib.h>

typedef struct parewiS{
    int             id;
    int             exp;
    lua_State       *L;
    char            *homedir;
    char            confdir[255];
    GHashTable      *games;
    struct pGame    *currentg; 
}parewiS;

typedef struct pGame{
    gchar           *dir;
    GHashTable      *models; 
    GHashTable      *objects;
    gchar           *name;
    gchar           *script; 
    gchar           *comment;
}pGame;

typedef struct pElement{
    int             id;
    gchar           *image_name;
    gchar           *name;
}pElement;

typedef struct pObject{
    int             id;
    SDL_Surface     *image;
    SDL_Rect        coords;
    SDL_Rect        blit;
}pObject;

parewiS *parewi_create_obj(void);
void    parewi_free_obj(parewiS *);

#endif

