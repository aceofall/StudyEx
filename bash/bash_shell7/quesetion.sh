#!/bin/bash
# 스크림트명: question.sh

echo -e "행복하세요? : \c"
read answer
echo "$answer 라고 답하셨네요"
echo -e "이름은 어떻게 되세요? : \c"
read last first
echo "안녕하세요? $last $first님"
echo -n "어디에 사세요? : "
read
echo $REPLY에 사시는 군요!
read -p "사용하는 리눅스 배포판은 무엇인가요? : "
echo $REPLY를 사용하고 계시군요.
echo -n "대표적인 리눅스 배포판을 3가지를 적어주세요. : "
read -a dist
echo "${dist[2]}를 세번째로 적어 주셨네요."
