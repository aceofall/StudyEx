#!/bin/bash

echo -n "몇 점이세요? (0-100) : "

read num
if [ $num -lt 0 -o $num -gt 100 ]
then
	echo "0 이상 100 이하의 수를 입력하세요"
	exit 1
fi

if [ $num -le 69 ]
then
#	echo "70점 이하네요."
	echo 70점 이하네요.
elif [ $num -ge 70 -a $num -le 79 ]
then
	echo 70점대군요 .
elif [ $num -ge 80 -a $num -le 89 ]
then
	echo 80점대군요 .
elif [ $num -ge 90 -a $num -le 99 ]
then
	echo 90점대군요 .
elif [ $num -eq 100 ]
then
	echo 만점이시네요. 축하합니다. 
else
	echo "숫자를 입력해주세요 (1-100)"
fi
