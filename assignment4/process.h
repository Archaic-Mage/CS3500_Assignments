#ifndef PROCESS
#define PROCESS

/* 

    Author: Soham Tripathy
    CS3500: Assignment 4
    topic: CPU scheduling algorithm

*/

#include <bits/stdc++.h>

using namespace std;

/*  Process type
1. System processes (sys)
2. Interactive processes (ip)
3. Interactive editing processes (iep)
4. Batch processes (bp)
5. Student processes (std)
*/

class Process {

public: 
    int id;
    int arrival_time;
    int completion_time;
    int brust_time;
    int process_type;
    int priority;

    //indicates how much time remaining to complete its execution
    int brust_complete;

    // The number according to which the queues prioritizes the processes
    int schedule_num;

    //sets completions time to -1 indicating the process is not completed
    //brust complete set to zero 
    Process() {
        this->completion_time = -1;
        brust_complete = 0;
    }
};


#endif