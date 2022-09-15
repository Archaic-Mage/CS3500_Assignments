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
            a.schedule_num = a.brust_complete;
            break;
        case 5:
            a.schedule_num = a.brust_complete;
        default:
            break;
    }
}

//adds the process in the queue for allocating its schedule num and brust_complete
void Process_Queue::addProcess(Process a) {
    a.brust_complete = a.brust_time;
    setProcessScheduleNum(a);
    processes.push(a);
}

void Process_Queue::addWaitingList(Process a) {
    waiting_processes.push_back(a);
}

bool Process_Queue::checkProcessAddPreempt(int from_time, Process curr) {
    if(waiting_processes.size() == 0) {
        processes.push(curr);
        return false;
    }
    else {
        while(waiting_processes.size() != 0 && waiting_processes[0].arrival_time <= from_time) {
            addProcess(waiting_processes[0]);
            waiting_processes.erase(waiting_processes.begin());
        }

        setProcessScheduleNum(curr);
        processes.push(curr);

        Process new_top = processes.top();

        if(new_top.id != curr.id) {
            return true;
        }
        else return false;
    }
}

//executes the processes for the round robin time slice alloted
vector<Process> Process_Queue::executeProcess(int &from_time, vector<int>& time_sequence) {
    int available_time = robinTimeSlice;
    vector<Process> processes_executed;

    while(!processes.empty() && available_time > 0) {
        Process curr = processes.top();
        processes.pop();

        available_time--;
        curr.brust_complete--;
        from_time++;

        if(curr.brust_complete == 0) {
            curr.completion_time = from_time;
            processes_executed.push_back(curr);
            time_sequence.push_back(from_time);
            continue;
        }

        if(checkProcessAddPreempt(from_time, curr)) {
            processes_executed.push_back(curr);
            time_sequence.push_back(from_time);
        }

        if(available_time == 0) {
            processes_executed.push_back(curr);
            time_sequence.push_back(from_time);
            break;
        }
    }

    return processes_executed;
}

