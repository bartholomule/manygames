#!/bin/sh
# $Id$

echo "---------------------------------------------------------------------------"

if [ -z "$MAKE" ]
then
  MAKE=`which gnumake 2>/dev/null`
  if test ! -x "$MAKE" ; then MAKE=`which gmake 2>/dev/null` ; fi
  if test ! -x "$MAKE" ; then MAKE=`which make 2>/dev/null` ; fi
  HAVE_GNU_MAKE=`$MAKE --version 2>/dev/null |grep -c "Free Software Foundation"`
fi

if test "$HAVE_GNU_MAKE" != "1"; then
echo !!!! Warning: not tested with non Gnu-Make $MAKE
else
echo Found GNU Make at $MAKE ... good.
fi

echo This script runs configure and make...
echo You did remember necessary arguments for configure, right?

libtoolize --force --copy
autoheader
aclocal
automake --add-missing --copy --gnu
autoconf
./configure $*
$MAKE
