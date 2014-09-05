#!/bin/bash

if [[ $1 == "" ]]
then
	echo 사용법: ./ifelse.sh 아이디
	exit 1
fi

if grep "$1" /etc/passwd >& /dev/null
then
	echo $1 아이디를 찾았습니다. 
else
	echo "$1 아이디를 찾지 못했습니다."
	exit 2
fi
