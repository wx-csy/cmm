#!/bin/bash

for kase in $*
do
	(echo $kase; awk '{printf("%2d %s\n", NR, $0)}' $kase; echo; ./parser < $kase) | less
done
