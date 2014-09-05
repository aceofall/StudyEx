#!/bin/bash

while getopts ab: options
do
	case $options in
		a) echo "-a 옵션을 사용하셨네요.";;
		b) echo "-b 옵션을 아규먼트는 $OPTARG";;
		?) echo "사용법: opt3 -ab 파일명" 1>&2;;
	esac
done
