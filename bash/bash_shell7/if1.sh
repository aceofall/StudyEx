#!/bin/bash

echo "Are you o.k. (y/n) ?"
read answer

if [[ $answer == [Yy]* || $answer = Maybe ]]
then
	echo "y 라고 대답했네요."
fi
