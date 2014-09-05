#!/bin/bash

function Usage { echo "에러 : $*" 2>&1; exit 1; }

if (( $# != 2 ))
then
	Usage "$0: 두 개의 아규먼트가 필요합니다."
fi

if [[ ! ( -r $1 && -w $1 ) ]]
then
	Usage "$1: 파일은 읽고 쓸 수 없습니다."
fi

echo 아규먼트: $*
