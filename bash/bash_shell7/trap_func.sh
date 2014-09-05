#!/bin/bash

function trapper () {
	echo "trapper 안"
	trap 'echo "trap이 가로챔!"' INT
	# trap이 한번 설정되면 trap은 스크립트 전체에 영향을 준다.
	# ^C를 입력하더라도 스크립트는 무시한다.
}

while :
do
	echo "메인 스크립트안에서"
	trapper
	echo "아직 메인 스크립트"
	echo "프로세스 아이디(PID) :$$"
	sleep 5
done
