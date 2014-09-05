#!/bin/bash

hour=0
until (( hour >= 24 ))
do
	case "$hour" in
		[0-9]|1[0-1]) echo $hour시 : 오전
			;;
		12) echo $hour시 : 정오
			;;
		*) echo $hour시 : 오후
	esac
	(( hour+=1 )) # hour 변수를 1 증가해야 한다.
done
