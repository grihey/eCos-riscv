#!/bin/sh
TOPDIR=$(realpath $(dirname $0))/ecos-3.0
BLDDIR=$TOPDIR/build_stm32
TOOLDIR=$TOPDIR/tools

ECOSTOOL=$TOOLDIR/bin/ecosconfig
CONFIG_ECC=$TOPDIR/Configs/stm32eval.ecc
REPO_DIR=$TOPDIR/packages 
INST_DIR=$TOPDIR/Configs/stm32eval_install

rm -rf $BLDDIR
mkdir -p $BLDDIR && cd $BLDDIR
$ECOSTOOL --config=$CONFIG_ECC --srcdir=$REPO_DIR --prefix=$INST_DIR tree
