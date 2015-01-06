/*
 * filesys.h
 *
 * Description: Function to work with files. 
 *
 * Authors: Manuel Mager <pywirrarika@gmail.com> (c) 2015
 * Copyright: GPL v3 or later
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "parewi.h"
#include "filesys.h"


gchar *get_home_dir(void)
{
    gchar *homedir;

    if ((homedir = getenv(HOME)) == NULL) 
    {
            homedir = getpwuid(getuid())->pw_dir;
    }

    return homedir;
}

int mk_confdir(parewiS *parewi)
{

#ifdef __WIN32
    gchar *conf = "parewi";
#else
    gchar *conf = ".parewi";
#endif

    g_sprintf(parewi->confdir, "%s/%s",parewi->homedir, conf);
    printf("New dir: %s\n", parewi->confdir);
    if(g_mkdir("config", 0777)!=0)
    {
        fprintf(stderr,"Error creating configuration directory\n");
        return -1;
    }
    return 0;
}
