#!/bin/bash
#  CS3500: Assignment 2
#  Author: Soham Tripathy CS20B073
#  Topic: Shell Scripting, Processes and Threads

read -a a
len=${#a[@]}

merge() {
	local i=2							#iterator for the first array
	local j=$(( $1 + 2 ))

	while [[ $j -lt $(($len + 2)) ]] && [[ $i -lt $(($1+2)) ]];
	do 
		if [[ ${@:$i:1} -lt ${@:$j:1} ]];
		then 
			echo ${@:$i:1} ; ((i += 1))
		else 
			if [[ ${@:$i:1} -ge ${@:$j:1} ]];
			then 
				echo ${@:$j:1} ; ((j += 1))
			fi
		fi
	done

	while [[ $j -lt $(($len + 2)) ]];
	do 
		echo ${@:$j:1} ; ((j += 1))
	done

	while [[ $i -lt $(($1+2)) ]];
	do 
		echo ${@:$i:1} ; ((i += 1))
	done
}

mergesort() {
	if [[ $1 -ge 2 ]]
	then
		local med=$(( $1 / 2 ))

		#split the array in $2 argument to lhs and call merge sort recurrsively
		local first=( $(mergesort $med ${@:2:$med}) )

		#split the array in $2 argument to rhs and call merge sort recurrsively			
		local second=( $(mergesort $(( $1 - $med )) ${@:$(( $med + 2 )):$(( $1 - $med ))}) )
		
		echo $(merge $med ${first[@]} ${second[@]})
	else
		echo $2
	fi
}

# printing the given array
echo ${a[@]} ; echo $(mergesort $len ${a[@]})

		
