#!/bin/bash

PS3="번호를 입력하면 웹사이트 주소를 볼수 있습니다. : "

select choice in 구글 네이버 네이버닷컴 다음 종료
do
	case "$choice" in
		구글)
			echo "구글 - http://www.google.com"
			continue;;
		네이버|네이버닷컴)
			echo "네이버 - http://www.naver.com"
			continue;;
		다음)
			echo "다음 - http://www.daum.net"
			continue;;
		종료)
			echo "종료하였습니다."
			break;;
		*)
			echo "$REPLY는 없습니다. 1에서 4사이의 수를 입력하세요" 1>&2
			echo "다시 선택."
			;;
	esac
done
