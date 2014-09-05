#!/bin/sh

listener () {
	echo "현재 디렉터리는 `pwd` 입니다."
	echo "현재 디렉터리의 파일들은 아래와 같습니다."
	ls
}

listener
