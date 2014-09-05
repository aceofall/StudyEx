#!/bin/bash

until who | grep $1
do
	sleep 5
done

echo $1 유저가 로그인해 있습니다. 
