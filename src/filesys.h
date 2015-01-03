#ifndef FILESYS_H
#define FILESYS_H

#include <stdlib.h>

// If the operating system is POSIX
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

char *homedir(void)
{
    char *homedir;

    if ((homedir = getenv(HOME)) == NULL) 
    {
            homedir = getpwuid(getuid())->pw_dir;
    }

    return homedir;
};
#endif
