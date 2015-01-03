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

typedef struct parewiS{
    int exp;
    lua_State* L;
}parewiS;

parewiS *parewi_create_obj(void);
void    parewi_free_obj(parewiS *);

#endif

