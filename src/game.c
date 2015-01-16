#include <stdio.h>
#include <stdlib.h>

#include "parewi.h"

pGame *
parewi_create_game(gchar *name, gchar *dir, gchar *comment, gchar *script)
{
    pGame *pgame = NULL;

    if(!name || !dir || !comment || !script)
    {
        fprintf(stderr, "No name, directory or comment to create \
                pGame object.\n");
        return NULL;
    }

    pgame = malloc(sizeof(pGame));
    if(!pgame)
    {
        fprintf(stderr, "Couldn't alloc memory for pgame obj.\n");
        return NULL;
    }

    pgame->name = name;
    pgame->dir = dir;
    pgame->comment = comment;
    pgame->script = script; 

    return pgame;
}

void
parewi_free_pgame(pGame *pgame)
{
    free(pgame->dir);
    pgame->dir = NULL;

    free(pgame);
    pgame = NULL;
    return;
}


