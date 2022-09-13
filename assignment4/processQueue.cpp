#include "processQueue.h"

/* 

    Author: Soham Tripathy
    CS3500: Assignment 4
    topic: CPU scheduling algorithm

*/

//setting the queue type and round robin time quantum
Process_Queue::Process_Queue(int time, int type) {
    this->robinTimeSlice = time;
    this->queue_type = type;
}

// setting the number for prioritizing
void Process_Queue::setProcessScheduleNum(Process& a) {
    switch(queue_type) {
        case 1: 
            a.schedule_num = a.priority;
            break;
        case 2:
            a.schedule_num = a.id;
            break;
        case 3:
            a.schedule_num = a.id;
            break;
        case 4:
            a.schedule_num = a.brust_time;
            break;
        case 5:
            a.schedule_num = a.brust_time;
        default:
            break;
    }
}

//adds the process in the queue for allocating its schedule num and brust_complete
void Process_Queue::addProcess(Process a) {
    setProcessScheduleNum(a);
    a.brust_complete = a.brust_time;
    processes.push(a);
}

//executes the processes for the round robin time slice alloted
vector<Process> Process_Queue::executeProcess(int &from_time) {
    int available_time = robinTimeSlice;
    vector<Process> processes_executed;

    while(!processes.empty()) {
        Process curr = processes.top();
        processes.pop();

        if(available_time >= (curr.brust_complete)) {
            available_time -= (curr.brust_complete);
            curr.completion_time = from_time + (robinTimeSlice - available_time);
            curr.brust_complete = 0;
            processes_executed.push_back(curr);

            if(available_time == 0) break;
        } else {
            curr.brust_complete -= available_time;
            available_time = 0;
            processes.push(curr);
            processes_executed.push_back(curr);
            break;
        }
    }
    
    from_time = from_time + (robinTimeSlice-available_time);

    return processes_executed;
}

