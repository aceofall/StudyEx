#!/bin/bash

while true
do
	echo "리눅스를 사용해 보신 적이 있나요[y/n]? : "
	read answer
	if [[ "$answer" == [Yy] ]]
	then
		break
	else
		echo "리눅스를 사용해 보신 적이 없군요."
	fi
done
echo "리눅스 사용자이시군요."
