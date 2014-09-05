#!/bin/bash

if (( $# < 2 ))
then
	echo "Usage: $0 [입력 파일명] [출력 파일명]" >&2
	exit 1
fi

count=1
cat $1 | while read line
do
	(( count == 1 )) && echo "Processing file $1 ..." > /dev/tty
	echo -e "$count\t$line"
	let count+=1
done > tmp$$
mv tmp$$ $2
