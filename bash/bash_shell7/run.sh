#!/bin/bash

PS3="실행할 프로그램을 선택하세요. : "
select program in 'ls -F' pwd date exit
do
	$program
done
