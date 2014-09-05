#!/bin/bash

name="linux"
if [[ $name == "centos" ]]
then
	printf "Hello $name\n"
fi

declare -i num=1
while (( num < 5 ))
do
	let num+=1
done
printf "Total: %d\n" $num
