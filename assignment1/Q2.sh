#!/bin/bash

# Author: Soham Tripathy CS20B073


#declaring and initializing the variables

IS_THERE[0]=0
IS_THERE[1]=0
IS_THERE[2]=0
IS_THERE[3]=0
IS_THERE[4]=0

STR=$1

LEN=${#STR}


#echo $LEN
#echo $STR
#echo ${IS_THERE[0]}

if [ $LEN -ge 8 ] 
then
    IS_THERE[3]=1
    #echo "I AM Triggered"
fi

#echo ${IS_THERE[3]}

for ((i = 0; i<${#STR}; i++)) 
do
    c=${STR:$i:1}
    #echo $c
    if [[ $c == [a-z] ]]; then 
        IS_THERE[0]=1
        #echo "YEs 0"
    elif [[ $c == [A-Z] ]]; then
        IS_THERE[1]=1
        #echo "Yes 1"
    elif [[ $c == "!" ]] || [[ $c == "@" ]] || [[ $c == "#" ]] || [[ $c == "$" ]] || [[ $c == "%" ]] || [[ $c == "^" ]] || [[ $c == "&" ]] || [[ $c == "*" ]] || [[ $c == "(" ]] || [[ $c == ")" ]] || [[ $c == "-" ]] || [[ $c == "+" ]]; then 
        IS_THERE[2]=1
        #echo "Yes 2"
    elif [[ $c == [0-9] ]]; then 
        IS_THERE[4]=1
        #echo "Yes 4"
    fi
done

if [[ ${IS_THERE[0]} == 1 ]] && [[ ${IS_THERE[1]} == 1 ]] && [[ ${IS_THERE[2]} == 1 ]] && [[ ${IS_THERE[3]} == 1 ]] && [[ ${IS_THERE[4]} == 1 ]]; then
    echo "Strong Password"
elif [[ ${IS_THERE[0]} == 1 ]] && [[ ${IS_THERE[1]} == 1 ]] && [[ ${IS_THERE[2]} == 1 ]] && [[ $LEN -ge 6 ]]; then
    echo "Moderate Password"
else
    echo "Weak Password"
fi