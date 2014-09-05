#!/bin/bash

echo q를 입력하면 종료합니다. 
go=start
while [[ -n "$go" ]] # 변수에 큰따옴표를 확인하라.
do
	echo -n 종료하려면 q를 입력하세요. :
	read word
	if [[ $word == [Qq] ]] # 예전 스타일 : [ "$word" = q -o "$word" = Q ]
	then
		echo "q를 입력하셨네요. 종료합니다. "
		go=
	fi
done
