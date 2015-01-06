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

// Tree structure of the configuration
// directory. 
#define CONF_SIZE 4
gchar *conf_dir_tree[] = {   
      "games", 
      "players", 
      "teachers", 
      "others" 
};

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
    gint    i;
    gchar   path[255];

#ifdef __WIN32
    gchar *conf = "parewi";
#else
    gchar *conf = ".parewi";
#endif


    g_sprintf(parewi->confdir, "%s/%s",parewi->homedir, conf);
    printf("New dir: %s\n", parewi->confdir);

    if(mkdir_if_not_exists(parewi->confdir) == -1)
        return -1;

    for(i=0; i<CONF_SIZE; i++)
    {
        printf("%s\n", conf_dir_tree[i]);
        sprintf(path, "%s/%s\n", parewi->confdir, conf_dir_tree[i]);
        printf("creating %s", path);
        mkdir_if_not_exists(path);
    }
patpathh    return 1;
}

int mkdir_if_not_exists(gchar *path)
{
    if(path == NULL)
        return -1;

    if(!dir_exists(path))
    {
        if(g_mkdir(&(path), 0777)!=0)
        {
            fprintf(stderr,"Error creating %s\n", path);
            return -1;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int dir_exists(gchar *confdir)
{
    GDir *dir = NULL;
    GError *error = NULL;

    dir=g_dir_open(confdir, 0, &error);
    if(error!=NULL)
    {
        if( error->code == G_FILE_ERROR_NOENT)
        {
            printf("Directory doesn't exist. Creating a new one...\n");
            g_error_free(error);
            if(dir != NULL)
                g_dir_close(dir);
        }
    }
    else if(dir != NULL)
    {
        g_dir_close(dir);
        return 1;
    }
    return 0;
}


