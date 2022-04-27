#!/bin/bash

if [ -f include/rom.h ];
then rm include/rom.h

else

    if [ $# -ne 1 ];
	then echo "illegal # of parameters!"

    else
	xxd -i $1 > include/rom.h
    fi

fi
