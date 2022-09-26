mkdir results

for test in ./tests/*.tst;
do
    argument=$(cat $test)
    name="$(basename $test .tst)"
    ./multi_pc $argument > ./results/$name.out
done;
