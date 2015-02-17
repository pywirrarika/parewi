AC_INIT([Parewi Educational Platform], [0.0.1], [libresoft.cuautitlan@gmail.com], [parewi])


AC_PREREQ([2.62])
AC_CANONICAL_HOST
AC_CANONICAL_BUILD
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE(foreign)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

NAME_VERSION=$PACKAGE-$VERSION

AC_DEFINE_UNQUOTED([PROGRAM_NAME], "$PACKAGE", [Parewi Educational Platform])

AC_SUBST(NAME_VERSION)

AC_GNU_SOURCE
AM_GNU_GETTEXT_VERSION([0.18.1])
AM_GNU_GETTEXT([external])

#LT_INIT

# ------------------------------------------------
# Check por programs.
# ------------------------------------------------

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_LIBTOOL

# ------------------------------------------------
# Check for libraries
# ------------------------------------------------
dnl Check glib
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.24.1])
CFLAGS="$CFLAGS $GLIB_CFLAGS"
LIBS="$LIBS $GLIB_LIBS"

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

dnl Check for SDL_mixer: --------------------------------------------------------

PKG_CHECK_MODULES([SDL_MIXER],
    [SDL_mixer],
    [],
    [AC_MSG_NOTICE([SDL_mixer not located by pkg-config, checking with AC CHECK LIB:])
    AC_CHECK_LIB([SDL_mixer],
        [Mix_OpenAudio],
        [],
        [AC_MSG_ERROR([SDL_mixer not found! http://www.libsdl.org/projects/SDL_mixer])])])

AC_DEFINE([HAVE_LIBSDL_MIXER],[1],[Define to 1 if you have the 'SDL_mixer' library])
CFLAGS="$CFLAGS $SDL_MIXER_CFLAGS"
LIBS="$LIBS $SDL_MIXER_LIBS"


dnl Check for LUA Support: ------------------------------------------------------

AX_PROG_LUA([])
AX_LUA_HEADERS([],[AC_MSG_ERROR([No lua headers found. ])])
CFLAGS="$CFLAGS $LUA_INCLUDE"
echo "Lua headers:$LUA_INCLUDE"
AX_LUA_LIBS
LIBS="$LIBS $LUA_LIB"


dnl Check for SDL_Pango: --------------------------------------------------------

dnl SDL_Pango is enabled by default.
dnl If SDL_Pango disabled at configure time, or if we can't find it,
dnl we look for SDL_ttf:

AC_ARG_WITH([sdlpango],
	[AS_HELP_STRING([--without-sdlpango],
	[Do not use SDL_Pango even if available])],
	[],
	[with_sdlpango=yes])


if test "x$with_sdlpango" != xno; then

PKG_CHECK_MODULES([SDL_PANGO],
	[SDL_Pango],
	[],
	[AC_MSG_NOTICE([SDL_Pango not located by pkg-config, checking with AC CHECK LIB:])
	 AC_CHECK_LIB([SDL_Pango],
		[SDLPango_Init],
		[],
		[AC_MSG_FAILURE([SDL_Pango test failed (--without-sdlpango to disable)])])])

AC_DEFINE([HAVE_LIBSDL_PANGO],[1],[Define to 1 if you have the `SDL_Pango` library])
CFLAGS="$CFLAGS $SDL_PANGO_CFLAGS"
LIBS="$LIBS $SDL_PANGO_LIBS"
DEP_PKGS="$DEP_PKGS SDL_Pango"

fi



dnl We only use SDL_ttf if SDL_Pango disabled: --------------------------------------

if [test "x$with_sdlpango" = xno]; then
dnl Add freetype link "by hand" until mingw-cross-env takes care
dnl of this automatically
LIBS="-lfreetype $LIBS"

PKG_CHECK_MODULES([SDL_ttf],
	[SDL_ttf],
	[],
	[AC_MSG_NOTICE([SDL_ttf not located by pkg-config, checking with AC CHECK LIB:])
	 AC_CHECK_LIB([SDL_ttf],
		[TTF_Init],
		[],
		[AC_MSG_ERROR([SDL_ttf not found! http://www.libsdl.org/projects/SDL_ttf])])])

AC_DEFINE([HAVE_LIBSDL_TTF],[1],[Define to 1 if you have the `SDL_ttf` library])
CFLAGS="$CFLAGS $SDL_TTF_CFLAGS"
LIBS="$LIBS $SDL_TTF_LIBS"
DEP_LIBS="$DEP_LIBS -lSDL_ttf"
fi



dnl Check for SDL_net: --------------------------------------------------------

dnl SDL_net is enabled by default.

AC_ARG_WITH([sdlnet],
	[AS_HELP_STRING([--without-sdlnet],
	[Do not use SDL_net even if available])],
	[],
	[with_sdlnet=yes]
)

if test "x$with_sdlnet" != xno; then
dnl We will need this for socket programming on Win32
AC_CHECK_LIB([ws2_32],
             [WSAStartup],
	     []  ,
	     [AC_MSG_NOTICE([Windows socket library ws2_32 not found - (only needed on win32)])])


PKG_CHECK_MODULES([SDL_NET],
	[SDL_net],
	[],
	[AC_MSG_NOTICE([SDL_net not located by pkg-config, checking with AC CHECK LIB:])
	 AC_CHECK_LIB([SDL_net],
		[SDLNet_Init],
		[],
		[AC_MSG_FAILURE([SDL_net test failed (--without-sdlnet to disable)])])])

AC_DEFINE([HAVE_LIBSDL_NET],[1],[Define to 1 if you have the 'SDL_net' library])
CFLAGS="$CFLAGS $SDL_NET_CFLAGS"
LIBS="$LIBS $SDL_NET_LIBS"
DEP_LIBS="$DEP_LIBS -lSDL_net"
fi



dnl Check for libRSVG and cairo. SVG support is enabled by default ----------------------

AC_ARG_WITH([rsvg],
	[AS_HELP_STRING([--without-rsvg],[do not use libRSVG even if available])],
	[with_rsvg=no],
	[with_rsvg=yes])

if test "x$with_rsvg" = xyes; then
PKG_CHECK_MODULES([RSVG],
	[librsvg-2.0 >= 2.18],
	[],
	[AC_MSG_FAILURE([libRSVG test failed (--without-rsvg to disable svg support)])])

CFLAGS="$CFLAGS $RSVG_CFLAGS"
LIBS="$LIBS $RSVG_LIBS"
DEP_PKGS="$DEP_PKGS librsvg-2.0"
fi

if test "x$with_rsvg" = xyes; then
PKG_CHECK_MODULES([CAIRO],
	[cairo >= 1.4.10],
	[],
	[AC_MSG_FAILURE([cairo test failed (--without-rsvg to disable svg support)])])

CFLAGS="$CFLAGS $CAIRO_CFLAGS"
LIBS="$LIBS $CAIRO_LIBS"
AC_DEFINE([HAVE_RSVG],[1],[Define to 1 if you have the `libRSVG` library])
fi



if test "x$with_rsvg" = xyes; then
PKG_CHECK_MODULES([LIBPNG],
	[libpng >= 1.2.37],
	[],
	[AC_MSG_FAILURE([libpng test failed (--without-rsvg to disable svg support)])])
CFLAGS="$CFLAGS $LIBPNG_CFLAGS"
LIBS="$LIBS $LIBPNG_LIBS"
AC_DEFINE([HAVE_LIBPNG],[1],[Define to 1 if you have the `libpng` library])
fi



dnl Check for libxml2: --------------------------------------------------------

PKG_CHECK_MODULES([XML2],
	[libxml-2.0],
	[],
	[AC_MSG_NOTICE([libxml2 not located by pkg-config, checking with AC CHECK LIB:])
	 AC_CHECK_LIB([xml2],
		[xmlParseFile],
		[],
		[AC_MSG_ERROR([libxml-2.0 not found: http://www.xmlsoft.org])])])

AC_DEFINE([HAVE_LIBXML2],[1],[Define to 1 if you have the `libxml-2.0` library])
CFLAGS="$CFLAGS $XML2_CFLAGS"
LIBS="$LIBS $XML2_LIBS"
DEP_PKGS="$DEP_PKGS libxml-2.0"



dnl Check for math functions - needed for SDL_extras: --------------------------------------------

AC_CHECK_LIB([m],
	[csin],
	[],
	[AC_MSG_ERROR([Math library not found - functions in <math.h> may not be available.])])



dnl Output substitutions needed for t4k_common.pc.in:
dnl (these are used by the subsequent build process of a program using t4k_common,
dnl not by the build process of t4k_common itself).

AC_SUBST(DEP_PKGS)
AC_SUBST(DEP_LIBS)
AC_SUBST(DEP_LIBS_PRIVATE)


# --------------------------------------------------------------------------------------
# Checks for header files.
# --------------------------------------------------------------------------------------

AC_FUNC_ALLOCA
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([argz.h error.h errno.h fcntl.h float.h iconv.h inttypes.h langinfo.h libgen.h libintl.h limits.h locale.h malloc.h math.h stddef.h stdint.h stdio_ext.h stdlib.h string.h strings.h sys/param.h unistd.h wchar.h])


# --------------------------------------------------------------------------------------------
# Checks for typedefs, structures, and compiler characteristics.
# --------------------------------------------------------------------------------------------

AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_C_RESTRICT
AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_C_VOLATILE
AC_CHECK_TYPES([ptrdiff_t])




echo "$CFLAGS"
AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 data/Makefile
                 data/images/Makefile
                 data/sounds/Makefile
                 po/Makefile.in
])

AC_OUTPUT

