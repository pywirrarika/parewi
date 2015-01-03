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

    homedir();
    return parewi_object;
}

void    
parewi_free_obj(parewiS *parewi_object)
{
    free(parewi_object);
    parewi_object = NULL;
    return;
}



