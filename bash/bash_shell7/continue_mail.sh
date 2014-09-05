#!/bin/bash

for name in $(cat mail_list)
do
	if [[ $name == multi ]]
	then
		continue
	else
		mail $name < mail_content.txt
	fi
done
