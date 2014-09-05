#!/bin/bash

echo "2007년 12월 19일 제 17대 대한민국 대통령에 당선된 사람의 이름은?"
read answer
while [[ "$answer" != "이명박" ]]
do
	echo "정답이 아닙니다. 다시 입력해주세요"
	read answer
done

echo 정답입니다. :: 이명박
