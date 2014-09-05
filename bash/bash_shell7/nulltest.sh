#!/bin/bash

if grep "$1" testfile >& /dev/null
then
	:
else
	echo "$1 문자열은 testfile에 없네요."
	exit 1
fi
