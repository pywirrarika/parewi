AC_INIT([Parewi Educational Platform], [0.0.1], [libresoft.cuautitlan@gmail.com], [parewi])

AC_PREREQ([2.62])
AC_CANONICAL_HOST
AC_CANONICAL_BUILD
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE(foreign)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

NAME_VERSION=$PACKAGE-$VERSION

AC_DEFINE_UNQUOTED([PROGRAM_NAME], "$PACKAGE", [Parewi Educational Platform])

AC_SUBST(NAME_VERSION)

AC_GNU_SOURCE

LT_INIT

# ------------------------------------------------
# Check por programs.
# ------------------------------------------------

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

# ------------------------------------------------
# Check for libraries
# ------------------------------------------------

dnl Check for SDL
SDL_VERSION=2.0.0
AM_PATH_SDL2($SDL_VERSION,
        :,
        AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

dnl ---------------------------------------------------------------------------
dnl In the following checks we attempt to use pkg-config if available, falling
dnl back to #AC_CHECK_LIB if #PKG_CHECK_MODULES fails.
dnl ---------------------------------------------------------------------------

dnl Check for SDL_image: ------------------------------------------------------

PKG_CHECK_MODULES([SDL_IMAGE],
    [SDL_image],
    ,
    [  
      [echo "SDL_IMAGE not found via pkg_config, checking with AC_CHECK_LIB:"]
      AC_CHECK_LIB([SDL_image],
	[IMG_Load],
        ,
        [AC_MSG_ERROR([SDL_image not found! http://www.libsdl.org/projects/SDL_image])]
      )
      [echo "SDL_IMAGE successfully located"]
    ]
)

AC_DEFINE([HAVE_LIBSDL_IMAGE],[1],[Define to 1 if you have the `SDL_image` library])
CFLAGS="$CFLAGS $SDL_IMAGE_CFLAGS"
LIBS="$LIBS $SDL_IMAGE_LIBS"


CFLAGS="$CFLAGS -Wall"

AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
])

AC_OUTPUT

