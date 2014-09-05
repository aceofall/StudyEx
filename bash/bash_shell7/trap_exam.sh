#!/bin/bash

trap 'echo "Ctrl-C 종료하지 않음 $0."' INT
trap 'echo "Ctrl-\\ 종료하지 않음 $0."' QUIT
trap 'echo "Ctrl-Z 종료하지 않음 $0."' TSTP
echo "프롬프트에 아무 문자열이나 입력하세요.
종료를 하려면 \"stop\"을 입력하세요."

while true
do
	echo -n "GOGO...> "
	read

	if [[ $REPLY == [Ss]top ]]
	then
		break
	fi
done
