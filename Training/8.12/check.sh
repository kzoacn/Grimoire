#!/bin/bash
make A
make A_gen
make AA
while true
do
./A_gen > in
./A < in > out 
./AA < in > ans
if diff ans out 
then echo AC
else echo WA
exit 0
fi
done
