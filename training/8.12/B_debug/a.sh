#!/bin/bash
make B_O1
make B_std
make make_B

g++ B_O1.cpp -o B_O1 -std=c++11 -O2
g++ B_std.cpp -o B_std -std=c++11 -O2
g++ make_B.cpp -o make_B -std=c++11 -O2

while true
do
./make_B > in
./B_std < in > ans
./B_O1 < in > out
if diff out ans
then echo AC
else echo WA
exit 0
fi
done
