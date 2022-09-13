#!/bin/sh

for test in ./tests/*.in;
do  
    name="$(basename $test .in)"
    ./schedule < $test > ./output/$name.out
done