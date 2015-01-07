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
#include "game.h"
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

gchar *
get_home_dir(void)
{
    gchar *homedir;

    if ((homedir = getenv(HOME)) == NULL) 
    {
            homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
}

int 
mk_confdir(parewiS *parewi)
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
        sprintf(path, "%s/%s", parewi->confdir, conf_dir_tree[i]);
        mkdir_if_not_exists(path);
    }
    return 1;
}

int 
mkdir_if_not_exists(gchar *path)
{
    if(path == NULL)
        return -1;


    printf("creating %s\n", path);

    if(!dir_exists(path))
    {
        if(g_mkdir(path, 0777)!=0)
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

int 
dir_exists(gchar *confdir)
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

GDir *
dir_open(gchar *path)
{
    GDir *dir = NULL;
    GError *error = NULL;

    dir=g_dir_open(path, 0, &error);
    if(error!=NULL)
    {
        if( error->code == G_FILE_ERROR_NOENT)
        {
            printf("Directory doesn't exist.  Creating a new one...\n");
            g_error_free(error);
            if(dir != NULL)
                g_dir_close(dir);
            return NULL;
        }
    }
    return dir;
}



GDir *
parewi_get_games(parewiS *parewi)
{
    gchar   *game_path;
    gchar   *subdir_path;
    gchar   *subdir_name;
    GDir    *dir = NULL;
    pGame   *game;

    game_path = g_strjoin("/", parewi->confdir, "games", NULL);

    dir = dir_open(game_path);
    if(dir == NULL)
    {
        fprintf(stderr, "Couldn't open games configuration directory!\n");
        return NULL;
    }

    // Read the subdirectories of $HOME/.parewi/games to find
    // Parewi Games and registrate to the parewi object. 

    while((subdir_name = g_dir_read_name(dir)) != NULL)
    {
        subdir_path = g_strjoin("/", game_path, subdir_name, NULL);
        
        game = parewi_create_game(subdir_name, subdir_path, "Comment");
        if(game == NULL)
        {
            fprintf(stderr, "Error creating a new game\n");
            return NULL;
        }
        printf("Game name: %s\n", game->name);

        // Registrating the game
        // TODO: check the existence of Lua main script
        g_hash_table_insert(parewi->games, game->name, game);
    }

    return 0;
}
