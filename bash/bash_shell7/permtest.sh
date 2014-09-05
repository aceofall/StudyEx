#!/bin/bash

if [ -z $1 ]
then
	echo 사용법: ./permtest.sh 파일명
	exit
fi

if [ -d $1 ]
then
	echo "$1 은 디렉터리다."
elif [ -f $1 ]
then
	if [ -r $1 -a -w $1 -a -x $1 ]
	then
		echo "$1 파일은 읽기, 쓰기, 실행이 가능한 파일이다."
	fi
else
	echo "$1 은 디렉터리도 파일도 아니다."
fi
