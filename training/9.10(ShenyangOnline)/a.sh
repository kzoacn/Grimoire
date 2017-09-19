#!/bin/bash
make make
g++ I.cpp -o I -O2
g++ std.cpp -o std -O2
while true;
do
	./make > in
	./I < in > out
	./std < in > ans
	if diff out ans
	then echo AC
	else echo WA
	exit 0
	fi
done
