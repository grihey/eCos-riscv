#!/bin/sh
TOPDIR=$(realpath $(dirname $0))/ecos-3.0
BLDDIR=$TOPDIR/../Configs/kernel_riscv_build
TOOLDIR=$TOPDIR/tools

ECOSTOOL=$TOOLDIR/bin/ecosconfig
CONFIG_ECC=$TOPDIR/../Configs/kernel_riscv.ecc
REPO_DIR=$TOPDIR/packages 
INST_DIR=$TOPDIR/../Configs/kernel_riscv_install
EXAMPLES_DIR=$TOPDIR/examples

rm -rf $BLDDIR
mkdir -p $BLDDIR && cd $BLDDIR
$ECOSTOOL --config=$CONFIG_ECC --srcdir=$REPO_DIR --prefix=$INST_DIR tree

make -C $BLDDIR
make -C $EXAMPLES_DIR -f twothreads.mak clean    
make -C $EXAMPLES_DIR -f twothreads.mak 
make -C $INST_DIR/lib clean
make -C $INST_DIR/lib
