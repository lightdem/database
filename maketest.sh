#!/bin/bash
#############################################################################
# maketest.sh
# Linux Pro Staff
#
# Un helper per lo script makefile per gestire il debug e release
# usando gli stessi sorgenti, oggetti e file eseguibili.
# In Makefile usare:  @source ../maketest.sh && test release debug (release)
#					@source ../maketest.sh && test debug release (debug)
# Invocare Makefile con make release, make debug o make clean.
#
#############################################################################
function test()
{
	if [[ ! -f $1 ]]; then
		touch $1;	
		rm -f $2;
    else
        touch $1;
	fi
}
#############################################################################
