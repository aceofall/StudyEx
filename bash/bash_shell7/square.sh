#!/bin/bash

function square {
	local square
	let "sq=$1 * $1"
	echo "가로와 세로 길이 : $1"
	echo "정사각형 넓이 : $sq "
}

echo "정사각형의 가로는? "
read number
value_returned=$(square $number)
echo "$value_returned"
