#!/bin/bash

dialog --title "vsftpd 서버 관리" --backtitle "vsftpd 서버관리" \
	--msgbox "vsftpd 서버를 관리합니다." 15 35
dialog --title "vsftpd 시작/중지/재시작" --backtitle "vsftpd 시작/중지/재시작" \
	--menu "선택하세요." 15 35 4 start "시작하기" stop "중지하기"\
	restart "재시작하기" exit "종료" 2>/tmp/vsftpd_menu.$$

menuitem=`cat /tmp/vsftpd_menu.$$`


case "$menuitem" in 
	start)
		/etc/init.d/vsftpd start
		dialog --backtitle "결과" --infobox "vsftpd 서버를 시작하였습니다." 10 25
		;;
	stop)
		/etc/init.d/vsftpd start
		dialog --backtitle "결과" --infobox "vsftpd 서버를 중지하였습니다." 10 25
		;;
	restart)
		/etc/init.d/vsftpd start
		dialog --backtitle "결과" --infobox "vsftpd 서버를 재시작하였습니다." 10 25
		;;
	exit)
		exit 0
		;;
esac

rm -f /tmp/vsftpd_menu.$$
