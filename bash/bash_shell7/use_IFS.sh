#!/bin/bash

names=홍길동:김길동:이길동:박길동
oldifs="$IFS"
IFS=":"
for persons in $names
do
	echo $persons 님 안녕하세요.
done

echo "===="
IFS="$oldifs"
set 박정희 김대중 노무현 이명박

for president in $*
do
	echo $president님 안녕하세요.
done
