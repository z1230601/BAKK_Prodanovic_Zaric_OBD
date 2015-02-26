#!/bin/bash

ZLATAN=~/Desktop/Bakk/BAKK_Prodanovic_Zaric_OBD/OBDCU
ZORAN=~/Desktop/BAKK_Prodanovic_Zaric_OBD/OBDCU

echo $1
if( test "$1" = "1") then
mkdir /tmp/OBDCU; cd /tmp/OBDCU; cmake $ZLATAN; make
fi

if(test "$1" = "2") then
mkdir /tmp/OBDCU; cd /tmp/OBDCU; cmake $ZORAN; make
fi


