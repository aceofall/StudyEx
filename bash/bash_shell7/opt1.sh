#!/bin/bash

while getopts xy options
do
	case $options in
		x) echo "-x 옵션을 사용하셨네요.";;
		y) echo "-y 옵션을 사용하셨네요.";;
	esac
done
