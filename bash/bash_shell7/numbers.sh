#!/bin/bash

number=0 # number 변수 초기화

while (( $number < 10 )) # 또는 while [ number -lt 10 ]
do
	echo -n "$number "
	let number+=1 # number 변수 1증가
done

echo -e "\n루프 종료."
