#ifndef GAME_H
#define GAME_H

#include "parewi.h"

pGame *parewi_create_game(gchar *, gchar *, gchar *, gchar *);
void parewi_free_pgame(pGame *);

#endif
