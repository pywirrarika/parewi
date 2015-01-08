/*
 * filesys.h
 *
 * Description: Function to work with files. 
 *
 * Authors: Manuel Mager <pywirrarika@gmail.com> (c) 2015
 * Copyright: GPL v3 or later
 *
 */

#ifndef FILESYS_H
#define FILESYS_H

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    /* UNIX-style OS. ------------------------------------------- */

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define HOME "HOME"

#elif defined(__WIN32)
#define HOME "USERPROFILE"

#else
#error This platform is not supported
#endif

#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "parewi.h"

gchar *get_home_dir(void);
int mk_confdir(parewiS *);
int mkdir_if_not_exists(gchar *);
int dir_exists(gchar *);
int parewi_get_games(parewiS *);
GDir *dir_open(gchar *path);

#endif
