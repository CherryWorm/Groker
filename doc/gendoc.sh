#!/bin/bash

doxygen "doxygen.conf"
for dir in *
do
	if [ -r "$dir/Makefile" ]
	then
		cwd="$PWD"
		cd "$dir"
		make -j3
		cd "$cwd"
	fi
done
