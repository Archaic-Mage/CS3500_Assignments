#!/bin/bash

# Author: Soham Tripathy CS20B073

count = 0
is_there[0] = 0
is_there[1] = 0
is_there[2] = 0
is_there[3] = 0
is_there[4] = 0

for c in $1 
do
    if [[c -ge 'a']] && [[c -le 'z']]; then 
        is_there[0] = 1
    if [[c -ge 'A']] && [[c -le 'Z']]; then 
        is_there[1] = 1
    if [[c == '!']] || [[c == '@']] || [[c == 'B']]
