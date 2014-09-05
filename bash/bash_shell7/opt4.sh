#!/bin/bash

while getopts abc: arguments 2>/dev/null
do
	case $arguments in
		a) echo "-a 옵션을 사용하셨네요.";;
		b) echo "-b 옵션을 사용하셨네요.";;
		c) echo "-c 옵션을 사용하셨네요."
		   echo "OPTARG 변수값은 $OPTARG 이다.";;
		?) echo "사용법: opt4 [-ab] [-c 아규먼트]"
		   exit 1;;
	esac
done
echo "사용된 아규먼트의 수는 $(($OPTIND - 1))개이다."
