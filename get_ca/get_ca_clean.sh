#!/bin/sh

PACKAGE=$1

FETCHEDDIR=${FETCHDIR}/${PACKAGE}

. ${PACKAGESDIR}/common/common_functions

abspath=`pwd`
ca_platform=pepos
ca_variant=std

make -C ${FETCHEDDIR} platform=$ca_platform variant=$ca_variant clean
