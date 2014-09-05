#!/bin/bash
# 스크립트명: rootcheck.sh
# 수퍼유저의 유저아이디 번호는 0번임

id=`id | awk -F'[=(]' '{print $2}'` # 유저 아이디 얻기
echo 유저아이디 번호 : $id

if (( id == 0)) # [ $id -eq 0 ]
then
	echo "당신은 슈퍼 유저 입니다."
else
	echo "당신은 슈퍼 유저 아닙니다."
fi
	
