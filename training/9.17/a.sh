#!/bin/bash
make make_D
g++ DD.cpp -o DD -O2
g++ force.cpp -o force -O2

while true;
do
./make_D > in
./DD < in > out
./force < in > ans
if diff out ans
then echo AC
else echo WA
exit 0
fi
done
