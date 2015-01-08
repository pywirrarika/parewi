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

#include <stdio.h>
#include <stdlib.h>

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include "parewi.h"
#include "filesys.h"

parewiS *
parewi_create_obj(void)
{
    parewiS* parewi_object = NULL;

    parewi_object = malloc(sizeof(parewiS));
    if(!parewi_object)
    {
        fprintf(stderr, "Error: allocate memory problem.\n");
    }

    // Starting LUA
    parewi_object->L = luaL_newstate();
    luaL_openlibs(parewi_object->L);

    parewi_object->homedir = get_home_dir();

    parewi_object->games = g_hash_table_new(g_str_hash, g_str_equal);

    printf("Home dir: %s\n", parewi_object->homedir);
    mk_confdir(parewi_object);

    if(!parewi_get_games(parewi_object))
    {
        return NULL;
    }

    printf("There are %d keys in the hash table\n",
            g_hash_table_size(parewi_object->games));
    // TODO: This is only tempraly code

    pGame *game = g_hash_table_lookup(parewi_object->games ,"colors");
    parewi_object->currentg=game;

    printf("colors: %s\n", game->dir);
    // TODO: End tmp code

    return parewi_object;
}

void    
parewi_free_obj(parewiS *parewi_object)
{
    lua_close(parewi_object->L);
    parewi_object->homedir = NULL;
    free(parewi_object);
    parewi_object = NULL;
    return;
}



