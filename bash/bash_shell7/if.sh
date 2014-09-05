#!/bin/bash

echo "Are you o.k. (y/n) ?"
read answer

if [ "$answer" = Y -o "$answer" = y ]
then
	echo "y 라고 대답했네요."
fi
