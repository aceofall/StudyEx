#!/bin/bash
# "continue n" 명령, n번 레벨의 루프에서 계속하기(continue)


for outer in A B C D E # 바깥쪽 2번 루프
do
	echo; echo -n "Group $outer: "
	for inner in 1 2 3 4 5 6 7 8 9 10 # 안쪽 1번 루프
	do
		if [ "$inner" -eq 6 ]
		then
			continue 2	# "바깥쪽 루프"인 2번 루프에서 계속 진행한다..
						# 윗줄을 "continue"라고 하면 안쪽 1번 루프를 순회한다.
		fi
		echo -n "$inner " # 6 7 8 9 10은 출력되지 않는다. 
	done
done
echo; echo
exit 0
