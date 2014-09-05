#!/bin/bash

echo "Are you o.k. (no way) ?"
read answer

if [[ $answer = [Nn]o?( way|t really) ]]
then
	echo "Match."
fi
