#!/bin/sh
TOPDIR=$(realpath $(dirname $0))/ecos-3.0
BLDDIR=$TOPDIR/../Configs/bemicrocva9_build
TOOLDIR=$TOPDIR/tools

ECOSTOOL=$TOOLDIR/bin/ecosconfig
CONFIG_ECC=$TOPDIR/../Configs/bemicrocva9.ecc
REPO_DIR=$TOPDIR/packages 
INST_DIR=$TOPDIR/../Configs/bemicrocva9_install

rm -rf $BLDDIR
mkdir -p $BLDDIR && cd $BLDDIR
$ECOSTOOL --config=$CONFIG_ECC --srcdir=$REPO_DIR --prefix=$INST_DIR tree
