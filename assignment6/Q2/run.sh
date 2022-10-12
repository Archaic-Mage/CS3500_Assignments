#!/bin/sh

for t in ./tests/*.tst;
do
    q=$(basename $t .tst)
    ./memory_usage < $t > ./results/$q.out
done;