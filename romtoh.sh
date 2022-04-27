#!/bin/bash
    
if [ $# -ne 1 ];
    then echo "illegal # of parameters!"
fi

if [ -f include/rom.h ];
    then rm include/rom.h
fi

xxd -i $1 > include/rom.h

varname=$1

varname=${varname////_}
varname=${varname//-/_}
varname=${varname//./_}

echo $varname

sed 's/$varname/rom_bytes/' $1
