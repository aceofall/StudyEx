#!/bin/bash

echo "웹 서버를 시작할지 중지할지 선택하세요.. : "

cat <<- ENDIT
	1) 웹 서버 시작
	2) 웹 서버 중지
	3) 웹 서버 재시작
ENDIT

read choice

case $choice in
	1) STATUS="시작"
		/etc/init.d/httpd start
		;;
	2) STATUS="중지"
		/etc/init.d/httpd stop
		;;
	3) STATUS="재시작"
		/etc/init.d/httpd restart
		;;
esac

echo "웹 서버가 $STATUS 되었습니다."
cat ENDIT
