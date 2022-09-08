#!/bin/sh

#  CS3500: Assignment 2
#  Author: Soham Tripathy CS20B073
#  Topic: Shell Scripting, Processes and Threads


# finds the path to the .txt file and store it in variable 
PATH_TXT=$(find ~/ -name "Assignment1_data.txt" -print -quit)

# using tr (translate command) delete the special characters like (., #, $, %, ...) 
tr -d -c '[^[:blank:][:alnum:]]+' < $PATH_TXT > temp.txt
# storing the intermediate result in temp.txt file

# using tr we insert new line characters in place of spaces
# first sort, sorts every line of strings ascendingly ( a < b < c < ... )
# uniq -c inserts the number of occurrance of similiar lines before the lines
# second sort -nr sorts the number of occurrances in descending order
tr -c '[:alnum:]' '[\n*]' < temp.txt | sort | uniq -c | sort -nr | head -3


# removing and clearing temp files
rm temp.txt



# Sources: https://man7.org/linux/man-pages/man1/uniq.1.html   -> uniq
#          https://man7.org/linux/man-pages/man1/sort.1.html   -> sort 
#          https://linuxcommand.org/lc3_man_pages/tr1.html     -> tr
