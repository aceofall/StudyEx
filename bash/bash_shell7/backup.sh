#!/bin/bash

dir=$HOME/test/bash_shell7/backup

for file in if*
do
	if [ -f $file ]
	then
		cp $file $dir/$file.bak
		echo "$file 파일이 $dir 디렉터리에 백업되었습니다."
	fi
done
