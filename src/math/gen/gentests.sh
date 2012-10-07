#!/bin/sh

D=..
sed 's/^T(//;s/,//;s/)//' functions.h | while read N T
do
	[ -e $D/$N.c ] || {
		cp template/$T.c $D/$N.c || continue
		ND=`echo $N |sed 's/l$//'`

		H=''
		for i in crlibm/$N.h ucb/$N.h sanity/$N.h
		do
			[ -e $D/$i ] && H="$H\\n#include \"$i\""
		done
		DH=''
		for i in crlibm/$ND.h ucb/$ND.h sanity/$ND.h
		do
			[ -e $D/$i ] && DH="$DH\\n#include \"$i\""
		done

		sed -i "s/___/$N/g;s,HEADERS,$H,;s,DHEADERS,$DH," $D/$N.c
	}
done
