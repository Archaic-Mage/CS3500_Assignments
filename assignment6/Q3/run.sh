#!/bin/sh

for t in ./tests/*.tst;
do
    q=$(basename $t .tst)
    ./page_replacement < $t > ./results/$q.out
done;