bin_PROGRAMS = parewi

AM_CFLAGS=-Wall -g -DDATA_PREFIX=\"${DATA_PREFIX}\" -DDEBUG \
		  -D$(SOUND)SOUND

DATA_PREFIX=${pkgdatadir}

parewi_SOURCES = 	main.c \
					filesys.c \
					game.c \
					parewi.c

EXTRA_DIST = 		parewi.h \
					game.h \
					filesys.h

