#!/bin/bash

echo -n "색을 표현하는 영어단어를 적으세요. 한글로 번역합니다. : "
read color

case $color in
	[Bb]l??)
		echo 푸른색입니다. 
		;;
	[Gg]ree*)
		echo 녹색입니다. 
		;;
	red | orange) # 버티칼 바는 or를 의미함
		echo 빨간색 또는 오렌지색입니다.
		;;
	*)
		echo "다시 입력해 주세요(blue, green, red, orange)."
		;;
esac

echo "case 명령을 실행 완료했습니다."
