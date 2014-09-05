#!/bin/bash

dialog --title "입력 박스" --backtitle "김태용의 리눅스 쉘 스크립트 프로그래밍 >입문" --inputbox "이름을 입력하세요." 8 60 2>/tmp/input.$$

sel=$?
name=`cat /tmp/input.$$`

case $sel in
	0) echo "$name님 안녕하세요." ;;
	1) echo "취소를 누르셨네요." ;;
	255) echo "<ESC>키를 누르셨네요." ;;
esac

rm -f /tmp/input.$$
