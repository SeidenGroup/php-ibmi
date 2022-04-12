PHP_ARG_ENABLE([ibmi],
  [whether to enable additional IBM i support],
  [AS_HELP_STRING([--enable-ibmi],
    [Enable ibmi support])],
  [no])

if test "$PHP_IBMI" != "no"; then
  dnl While we can check for features, libraries, and headers, it's not of much
  dnl use since all the versions of IBM i we support expose the same extended
  dnl functionality. So just reduce this to an OS type check.
  dnl Cross-compiling is blocked by this but I don't think PASE cross-compiles
  dnl are supported by anything but AIX (which is not really crossing).
  AC_MSG_CHECKING(if compiling on IBM i)
  if test "x$(uname)" = "xOS400" ; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([This extension only supports IBM i])
  fi

  AC_DEFINE(HAVE_IBMI, 1, [ Have ibmi support ])

  PHP_NEW_EXTENSION(ibmi, ccsid.c systemcl.c files.c ibmi.c xmlservice.c, $ext_shared)
fi
