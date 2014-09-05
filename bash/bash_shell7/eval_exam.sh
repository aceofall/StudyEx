#!/bin/bash

eval `id | sed 's/[^a-z0-9=].*//'`
if [ "${uid:=0}" -ne 0 ]
then
	echo $0: only root can run $0
	exit 2
else
	echo "root user : superuser"
fi
