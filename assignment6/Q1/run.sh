#!/bin/sh

for t in ./tests/*.tst;
do
    q=$(basename $t .tst)
    ./memoryAllocator < $t > ./results/$q.out
done;