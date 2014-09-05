#!/bin/bash

while getopts xy options 2> /dev/null 
do
	case $options in
		x) echo "-x 옵션을 사용하셨네요.";;
		y) echo "-y 옵션을 사용하셨네요.";;
		?) echo "-x, -y 옵션만 사용할 수 있습니다." 1>&2;;
	esac
done
