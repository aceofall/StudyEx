#!/bin/bash

dialog --title "경고: 파일 삭제" --backtitle \
	"김태용의 리눅스 쉘 스크립트 프로그래밍 입문" --yesno \
	"\n삭제하시겠습니까? '/home/Q301000080/test/bash_shell7/testdel.sh' file" 7 60
sel=$?
case $sel in
	0) echo "삭제를 선택했습니다." ;;
	1) echo "삭제를 선택하지 않았습니다." ;;
	255) echo "<ESC> 키를 눌러 취소하였습니다.";;
esac
