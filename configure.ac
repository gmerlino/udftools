dnl Process this file with autoconf to produce a configure script.
AC_INIT(udftools, 1.3, , , [https://github.com/pali/udftools/])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(include/config.h:include/config.in)
AM_INIT_AUTOMAKE([subdir-objects])

dnl Checks for programs.
AC_PROG_CC([clang gcc])
AC_DISABLE_SHARED
AM_PROG_LIBTOOL

dnl Checks for libraries.
AC_CHECK_LIB(readline, readline, , AC_MSG_ERROR([cannot find -lreadline.]))

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(fcntl.h malloc.h sys/time.h unistd.h endian.h getopt.h sys/isa_defs.h string.h strings.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_HEADER_TIME
AC_STRUCT_TM
AC_SYS_LARGEFILE

dnl Checks for library functions.
AC_SUBST(LTLIBOBJS)

dnl Enable Darwin extensions (AC_USE_SYSTEM_EXTENSIONS does not enable
dnl them in 2.63)
AC_CANONICAL_HOST
AS_CASE([$host_os],
       [darwin*], [CPPFLAGS="${CPPFLAGS} -D_DARWIN_C_SOURCE"])

AC_CONFIG_FILES(Makefile libudffs/Makefile mkudffs/Makefile cdrwtool/Makefile pktsetup/Makefile udffsck/Makefile wrudf/Makefile doc/Makefile)

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
[enable debugging, default: no]),
[case "${enableval}" in
    yes) debug=true ;;
    no)  debug=false ;;
    *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_CONDITIONAL(HAVE_DARWIN, test "${SYS}" = "darwin")

AC_ARG_ENABLE(tests,
AS_HELP_STRING([--enable-tests],
[enable tests building, default: no]),
[case "${enableval}" in
    yes) tests=true ;;
    no)  tests=false ;;
    *)   AC_MSG_ERROR([bad value ${enableval} for --enable-tests]) ;;
esac],
[tests=false])

AM_CONDITIONAL(TESTS, test x"$tests" = x"true")

AC_C_BIGENDIAN
AM_CONDITIONAL(WORDS_LITTLEENDIAN, test "x$ac_cv_c_bigendian" = "xno")
AM_CONDITIONAL(WORDS_BIGENDIAN, test "x$ac_cv_c_bigendian" = "xyes")

AC_PROG_CC_C99

AC_OUTPUT
