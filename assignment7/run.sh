for t in ./tests/*.tst; 
do
    q=$(basename $t .tst)
    ./algorithm $(cat $t) > ./output/$q.out
done;