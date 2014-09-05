#!/bin/bash

echo "정수를 입력하세요."
read number

if expr "$number" + 0 >& /dev/null
then
	:
else
	echo "입력된 값은 정수가 아닙니다."
#	exit 1
fi
