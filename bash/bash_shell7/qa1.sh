#!/bin/bash

echo -n "몇 점이세요? (0-100) : "

read num
if (( $num < 0 || $num > 100 ))
then
	echo "0 이상 100 이하의 수를 입력하세요"
	exit 1
fi

if (( $num < 69 ))
then
#	echo "70점 이하네요."
	echo 70점 이하네요.
elif (( $num >= 70 && $num <= 79 ))
then
	echo 70점대군요 .
elif (( $num >= 80 && $num <= 89 ))
then
	echo 80점대군요 .
elif (( $num >= 90 && $num <= 99 ))
then
	echo 90점대군요 .
elif (( $num == 100 ))
then
	echo 만점이시네요. 축하합니다. 
else
	echo "숫자를 입력해주세요 (1-100)"
fi
