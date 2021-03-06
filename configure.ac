dnl Process this file with autoconf to produce a configure script.

dnl NOTE: As the version number changes, it must be changed in both of the
dnl _INIT statements below (AC and AM).	 
dnl Change the version number here when required.
VERSION=0.00.00

dnl Change the version number here when required.
AC_INIT(manygames, 0.00.00, manygames-bugs@lists.sourceforge.net)
dnl ---------------------------------------------------------------------------
dnl Gets the host type
dnl ---------------------------------------------------------------------------
AC_CANONICAL_TARGET
dnl Change the version number here when required.
AM_INIT_AUTOMAKE(manygames, 0.00.00)
AC_PREFIX_DEFAULT(/usr/local/games)

AM_CONFIG_HEADER(include/manygames/manygames_config.hpp)


dnl ---------------------------------------------------------------------------
dnl Checks for programs.
dnl ---------------------------------------------------------------------------
AM_PROG_LEX
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)
AC_PROG_CXX
AC_LANG(C++)
AC_PROG_YACC
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AM_GNU_GETTEXT

dnl ---------------------------------------------------------------------------
dnl Checks for header files.
dnl ---------------------------------------------------------------------------
AC_HEADER_STDC

dnl ---------------------------------------------------------------------------
dnl Check for C++ features
dnl ---------------------------------------------------------------------------
AC_CACHE_CHECK([for working member templates (C++)],
  ac_cv_member_templates_ok,
[AC_TRY_COMPILE([
  class foo
  { 
  public:
    template <class T>
    bool callme(T t) { return true; }
  };
  ],
  [
    foo f;
    f.callme(int(1));
    f.callme(bool(true));
    f.callme(double(1.0));
  ], 
  ac_cv_member_templates_ok=yes,
  ac_cv_member_templates_ok=no)
])
if test $ac_cv_member_templates_ok = yes; then
  AC_DEFINE(MEMBER_TEMPLATES_WORK, 1, Member templates work or not (C++))
fi

AC_CACHE_CHECK([for working subtype ptr returns for virtual functions (C++)],
  ac_cv_virtual_return_type_ok,
[AC_TRY_COMPILE([
  class foo
  {
  public:
    virtual foo* This();
  };

  class bar : public foo
  {
  public:
    virtual bar* This();
  };

  foo* foo::This() { return this; }
  bar* bar::This() { return this; }
  ],
  [
    foo f, *bp1, *bp2, *p3, *p4;
    bar b;

    bp1 = &f;
    bp2 = &b;

    p3 = bp1->This();
    p4 = bp2->This();
  ],
  ac_cv_virtual_return_type_ok=yes,
  ac_cv_virtual_return_type_ok=no)
])
if test $ac_cv_virtual_return_type_ok = no; then
  AC_DEFINE(BROKEN_RETURN_SUBTYPES_ON_VIRTUAL, 1, If virtual functions cannot have return types of a subclass (C++))
fi  

dnl ---------------------------------------------------------------------------
dnl Check for special libraries
dnl ---------------------------------------------------------------------------

dnl ---------------
dnl gtkmm-2.0
dnl ---------------
PKG_CHECK_MODULES(GTKMM, gtkmm-2.4)
AC_SUBST(GTKMM_CFLAGS)
AC_SUBST(GTKMM_LIBS)


dnl dnl ---------------
dnl dnl SigC++
dnl dnl ---------------
PKG_CHECK_MODULES(SIGC, sigc++-2.0)
AC_SUBST(SIGC_CFLAGS)
AC_SUBST(SIGC_LIBS)


AC_PATH_XTRA
if test -n "$no_x"; then
dnl AC_MSG_ERROR([Can't find X, you need X!])
  USE_X=false
else
  USE_X=true
fi
AC_SUBST(X_INCLUDE_DIRS)
AC_SUBST(X_LIB_DIRS)

dnl echo -e "checking for SigC++... \c"
dnl dnl AC_CHECK_PROG(sigcxx_val,"sigc-config --cflags","yes","no")
dnl if [ `sigc-config --cflags >/dev/null 2>/dev/null` ]
dnl then
dnl   echo "yes"
dnl   AC_DEFINE(USE_SIGCXX, 1, Using sigc++ or not )
dnl   BARF1=`sigc-config --cflags`
dnl   BARF2=`sigc-config --libs`
dnl   extra_includes="$extra_includes $BARF1"
dnl   extra_libs="$extra_libs $BARF2"
dnl else
dnl   echo "no"
dnl   AC_DEFINE(USE_SIGCXX, 0, Using sigc++ or not)
dnl fi
dnl AC_SUBST(extra_includes)
dnl AC_SUBST(extra_libs)


AC_MSG_CHECKING(for a forced cpu type)
AC_ARG_ENABLE(cpu, 
[  --enable-cpu=CPUTYPE    Force the use of the given cpu type in compilation.]
[                          This is for using a specific CPU within a family.  ]
[                          --enable-cpu=pentium4  or  --enable-cpu=athlon-xp  ]
[                          are both within the i686 family group, but perform ]
[                          very differently.                                  ]
[                                                                             ]
[                          Alternatively, you can use the --target= option to ]
[                          specify a family, but not a specific CPU.          ]
[                                                                             ]
[                          gcc supports some of the following (check yours):  ]
[                              i386, i486, i586, i686, pentium, pentiumpro,   ]
[                              pentium-mmx, pentium2, pentium3, pentium4,     ]
[                              k6, k6-2, k6-3, athlon, athlon-tbird,          ]
[                              athlon-xp, athlon-mp                           ],
CPU_TYPE=$enableval, CPU_TYPE="no")
if test $CPU_TYPE = "yes"; then
  CPU_TYPE=$target_cpu
  CPU_MESSAGE="yes, but not specified, guessing $CPU_TYPE"
  CPU_OVERRIDE=1
elif test $CPU_TYPE = "guess"; then
  CPU_TYPE=$target_cpu
  CPU_MESSAGE="no, guessing $CPU_TYPE"
  CPU_OVERRIDE=1
elif test $CPU_TYPE = "no"; then
  CPU_OVERRIDE=0
  CPU_MESSAGE="no"
else
  CPU_MESSAGE="yes, $CPU_TYPE"
  CPU_OVERRIDE=1
fi
AC_SUBST(CPU_TYPE)
AC_MSG_RESULT($CPU_MESSAGE)

if test $CPU_OVERRIDE != 0
then 
  AC_MSG_CHECKING(which compiler flag specifies CPU type)
  OLD_CXXFLAGS=$CXXFLAGS
  CXXFLAGS="$OLD_CXXFLAGS -march=$CPU_TYPE"
  AC_TRY_LINK( [ int iii; ], [ iii = 0; ], CPU_SPECIFIC_SWITCH="-march", CPU_SPECIFIC_SWITCH="no")
  if test "no" = $CPU_SPECIFIC_SWITCH; then
    CXXFLAGS="$OLD_CXXFLAGS -mcpu=$CPU_TYPE"
    AC_TRY_LINK( [ int iii; ], [ iii = 0;], CPU_SPECIFIC_SWITCH="-mcpu", CPU_SPECIFIC_SWITCH="no")
  fi
  dnl I don't have anything else to try right now.  Someone else can add something.
  if test "no" = $CPU_SPECIFIC_SWITCH; then
    AC_MSG_RESULT(
[NOT FOUND]
[                   Your CPU type override ($CPU_TYPE) may be invalid         ]
[                   for your compiler (CHECK THIS FIRST), or I don't know how ]
[                   to override it on your compiler (send a patch)... Ignoring]
[                   forced CPU override. ])
    CPU_SPECIFIC_FLAG=""
  else
    AC_MSG_RESULT($CPU_SPECIFIC_SWITCH)
    CPU_SPECIFIC_FLAG="$CPU_SPECIFIC_SWITCH=$CPU_TYPE"
  fi
  CXXFLAGS=$OLD_CXXFLAGS
else
  CPU_SPECIFIC_FLAG=""
fi
AC_SUBST(CPU_SPECIFIC_FLAG)


dnl ---------------------------------------------------------------------------
dnl Checks for optimizations option.
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING(whether to enable optimizations or not)
AC_ARG_ENABLE(optimizations,
[  --enable-optimizations  Enable optimizations (=level given)],
OPTIMIZATION_VAL=$enableval, OPTIMIZATION_VAL="no")
if test $OPTIMIZATION_VAL = "yes"; then
  OPTIMIZATIONS_ALLOWED=1
  OPTIMIZATION_LEVEL=""
  OPTIMIZE_EXPENSIVE=0
  OPTIMIZATION_VAL="yes"
elif test $OPTIMIZATION_VAL != "no"; then
  OPTIMIZATIONS_ALLOWED=0
  OPTIMIZE_EXPENSIVE=0
  OPTIMIZATION_LEVEL=""
  dnl For some reason, this didn't work correctly with a simple case:
  dnl [0-9]) ...

  case $OPTIMIZATION_VAL in
    1) OPTIMIZATIONS_ALLOWED=1 ;;
    2) OPTIMIZATIONS_ALLOWED=1 ;;
    3) OPTIMIZATIONS_ALLOWED=1 ;;
    4) OPTIMIZATIONS_ALLOWED=1 ;;
    5) OPTIMIZATIONS_ALLOWED=1 ;; 
    6) OPTIMIZATIONS_ALLOWED=1 ;; 
    7) OPTIMIZATIONS_ALLOWED=1 ;; 
    8) OPTIMIZATIONS_ALLOWED=1 ;; 
    9) OPTIMIZATIONS_ALLOWED=1 ;; 
    0) OPTIMIZATIONS_ALLOWED=1 ;;
    *) OPTIMIZATION_VAL="NO -- unknown value \"$OPTIMIZATION_VAL\"" ;;
  esac
  if test $OPTIMIZATIONS_ALLOWED != 0
  then
    OPTIMIZATION_LEVEL=$OPTIMIZATION_VAL
    OPTIMIZATION_VAL="yes, level $OPTIMIZATION_LEVEL"
    if test $OPTIMIZATION_LEVEL -ge 5
    then
      OPTIMIZE_EXPENSIVE=1
    fi
  fi
else
  OPTIMIZATIONS_ALLOWED=0
  OPTIMIZATION_VAL="no"
  OPTIMIZE_EXPENSIVE=0
fi
AC_SUBST(OPTIMIZATIONS_ALLOWED)
AC_SUBST(OPTIMIZATION_LEVEL)
AC_SUBST(OPTIMIZE_EXPENSIVE)
AC_MSG_RESULT($OPTIMIZATION_VAL)

dnl ---------------------------------------------------------------------------
dnl Checks for exceptions option.
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING(whether to enable exceptions or not)
AC_ARG_ENABLE(exceptions,
[  --enable-exceptions     Enable exception handling],
EXCEPTION_VAL=$enableval, EXCEPTION_VAL="no")
if test $EXCEPTION_VAL = "yes"; then
  EXCEPTIONS_ALLOWED=1
  AC_DEFINE(USE_EXCEPTIONS, 1, Exception handling allowed or not (C++) )
else
  EXCEPTIONS_ALLOWED=0
  EXCEPTION_VAL="no"
fi
AC_SUBST(EXCEPTIONS_ALLOWED)
AC_MSG_RESULT($EXCEPTION_VAL)

dnl ---------------------------------------------------------------------------
dnl Checks for rtti option.
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING(whether to enable rtti or not)
AC_ARG_ENABLE(rtti,
[  --enable-rtti           Enable runtime type identification],
RTTI_VAL=$enableval, RTTI_VAL="no")
if test $RTTI_VAL = "yes"; then
  RTTI_ALLOWED=1
else
  RTTI_ALLOWED=0
  RTTI_VAL="no"
fi
AC_SUBST(RTTI_ALLOWED)
AC_MSG_RESULT($RTTI_VAL)


dnl ---------------------------------------------------------------------------
dnl Checks for profile option.
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING(whether to add profiling information or not)
AC_ARG_ENABLE(profile,
[  --enable-profile        Add profiling information],
PROFILE_VAL=$enableval, PROFILE_VAL="no")
if test $PROFILE_VAL = "yes"; then
  PROFILE=1
else
  PROFILE_VAL="no";
  PROFILE=0
fi
AC_SUBST(PROFILE)
AC_MSG_RESULT($PROFILE_VAL)

dnl ---------------------------------------------------------------------------
dnl Checks for debug option.
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING(whether to enable debug info or not)
AC_ARG_ENABLE(debug,
[  --enable-debug          Generate debug information when compiling],
DEBUG_VAL=$enableval, DEBUG_VAL="no")
if test $DEBUG_VAL = "yes"; then
  DEBUG_INFO=1
else
  DEBUG_VAL="no";
  DEBUG_INFO=0
fi
AC_SUBST(DEBUG_INFO)
AC_MSG_RESULT($DEBUG_VAL)

dnl ---------------------------------------------------------------------------
dnl Checks for experimental code option.
dnl ---------------------------------------------------------------------------
AC_MSG_CHECKING(whether to enable experimental code or not)
AC_ARG_ENABLE(experimental,
[  --enable-experimental   Include experimental code in build],
EXPER_VAL=$enableval, EXPER_VAL="no")
if test $EXPER_VAL = "yes"; then
  EXPERIMENTAL=1
  AC_DEFINE(USE_EXPERIMENTAL, 1, Experimental code allowed to be compiled/run)
else
  EXPER_VAL="no";
  EXPERIMENTAL=0
fi
AC_SUBST(EXPERIMENTAL)
AC_MSG_RESULT($EXPER_VAL)

AC_SUBST(ARCH_MAKE_SHARED_OPTS)
AC_SUBST(ARCH_PROG_SETLIBPATH)
  
AC_OUTPUT([ Makefile          intl/Makefile \
            doc/Makefile     \
               \
            po/Makefile.in   \
            po/Makefile      \
            m4/Makefile      \
            src/Makefile     \
            src/utils/Makefile \
            src/generic/Makefile \
            src/graphics/Makefile \
            src/input/Makefile \
	    src/platform/Makefile \
	    src/platform/gtkmm/Makefile \
	    src/platform/X/Makefile \
            include/Makefile \
            include/manygames/Makefile \
	    test/Makefile 
          ],
          echo "------------------"
          echo "Configure is done."
          echo "------------------"
)

if test ! -e install-sh
then
  ln -s "$ac_aux_dir/install-sh" . 2>/dev/null || echo "install-sh could not be linked."
fi

