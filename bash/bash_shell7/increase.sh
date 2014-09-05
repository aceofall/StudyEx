#!/bin/bash

increase () {
	local sum;
	let "sum=$1 + 1"
	return $sum
}

echo -n "합계는 "
increase 7
echo $? # increase 함수의 리턴값을 출력함
echo $sum # 아무런 값도 출력하지 않음
