#!/bin/bash

name=$1
#if [ "$name" == "" ] # [ ! "$name" ] 또는 [ -z "$name" ]
if [ "$1" == "" ] # [ ! "$name" ] 또는 [ -z "$name" ]
then
	echo "첫 번째 아규먼트의 값을 입력하지 않았다. (null)"
else
	echo "첫 번째 아규먼트의 값은 $name이다."
fi
