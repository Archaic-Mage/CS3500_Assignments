#ifndef PROCESS_QUEUE
#define PROCESS_QUEUE

#include "process.h"

/* 

    Author: Soham Tripathy
    CS3500: Assignment 4
    topic: CPU scheduling algorithm

*/

class Compare {

public:

    //comparator operator according to which the processes get prioritzed
    bool operator() (Process p1, Process p2) {
        if(p1.schedule_num == p2.schedule_num) {
            return p1.id > p2.id;
        } else return p1.schedule_num > p2.schedule_num;
    }

};

class Process_Queue {

    priority_queue<Process, vector<Process>, Compare> processes;
    int robinTimeSlice;
    int queue_type;

public:

    void addProcess(Process);

    void setProcessScheduleNum(Process&);

    Process_Queue(int, int);

    // returns vector of process - executed from time 'from_time' to 'from_time+robinTimeSlice' (if possible)
    // it also changes the time 'from_time' to time it can execute (which can be used later)
    vector<Process> executeProcess(int &from_time);   
    
};


#endif