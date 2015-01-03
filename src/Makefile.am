bin_PROGRAMS = parewi

AM_CFLAGS=-Wall -g -DDATA_PREFIX=\"${DATA_PREFIX}\" -DDEBUG \
		  -D$(SOUND)SOUND

DATA_PREFIX=${pkgdatadir}

parewi_SOURCES = 	main.c \
					parewi.c

EXTRA_DIST = 		parewi.h \
					uthash.h \
					utarray.h \
					utlist.h \
					utstring.h \
					filesys.h

