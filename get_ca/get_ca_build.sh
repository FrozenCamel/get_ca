#!/bin/sh

PACKAGE=$1

FETCHEDDIR=${FETCHDIR}/${PACKAGE}

. ${PACKAGESDIR}/common/common_functions

abspath=`pwd`

make -C $FETCHEDDIR \
        ARCH=$ARCH \
        CROSS_COMPILE=$HOST_PREFIX- \
        $MAKE_OPTS || exit $?


