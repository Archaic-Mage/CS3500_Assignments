#include "processQueue.h"

/* 

    Author: Soham Tripathy
    CS3500: Assignment 4
    topic: CPU scheduling algorithm

*/

//for debugging
void print(string s) {
    return;
    cout << s << endl;
    cout.flush();
}

//from the given string it gets the queue types
int getQueueTypeCode(string process_type) {
    if(process_type == "sys") return 0;

    if(process_type == "ip") return 1;

    if(process_type == "iep") return 2;

    if(process_type == "bp") return 3;

    if(process_type == "sp") return 4;

    return -1;
}

int main() {

    int robinTimeSlice;
    int numberOfProcesses;

    cin >> robinTimeSlice >> numberOfProcesses;

    //indicating process completed or not
    unordered_map<int, Process> process_complete;

    //execution sequence
    vector<int> process_exe_sequence;

    //waiting queue of process -> goes to ready queue
    vector<Process> waiting_queue; 

    //setting the queues
    vector<Process_Queue> Queues;

    // 0 -> sys
    // 1 -> ip
    // 2 -> iep
    // 3 -> bp
    // 4 -> sp

    for(int i = 0; i<5; i++) {
        Queues.push_back(Process_Queue(robinTimeSlice, i+1));
    }

    //adds the processes in the waiting queue
    for(int i = 0; i<numberOfProcesses; i++) {
        Process curr_process = Process();

        string temp;

        cin >> temp;                                            //process_id

        curr_process.id = stoi(temp.substr(1, temp.size()-1));

        cin >> curr_process.arrival_time;                       //arrival_time

        cin >> curr_process.brust_time;                         //brust_time

        cin >> temp;                                            //process_type
        
        curr_process.process_type = getQueueTypeCode(temp)+1;

        cin >> curr_process.priority;                           //priority

        waiting_queue.push_back(curr_process);
    }

    print("Done taking in input");

    //Scheduling

    int time = 0;
    int i = 0;

    while(process_complete.size() != numberOfProcesses) {

        //transfer from waiting to ready queue
        while(waiting_queue.size() != 0 && waiting_queue[0].arrival_time <= time) {
            Queues[waiting_queue[0].process_type-1].addProcess(waiting_queue[0]);
            waiting_queue.erase(waiting_queue.begin());
        }
        
        //executes the processes
        vector<Process> executed_processes = Queues[i].executeProcess(time);

        //storing the execution sequence and completion data
        for(Process process: executed_processes) {
            process_exe_sequence.push_back(process.id);
            if(process.completion_time != -1) {
                process_complete[process.id] = process;
            }
        }

        //ensures round robin
        i = (i+1)%5;
    }

    //prints relevant information

    for(int i = 0; i<numberOfProcesses; i++) {

        Process p = process_complete[i+1];

        //print process id
        cout << "p" << p.id << endl;
        cout << "AT: " << p.arrival_time << endl;
        cout << "BT: " << p.brust_time << endl;
        cout << "CT: " << p.completion_time << endl;
        cout << "TAT: " << p.completion_time - p.arrival_time << endl;
        cout << "WT: " << p.completion_time - p.arrival_time - p.brust_time << endl;
        cout << endl;
    }

    int k = 0;

    for(int process: process_exe_sequence) {
        cout << "p" << process << " ";
        k++;
        if(k == 10) {
            cout << endl;
            k = 0;
        }
    }

    return 0;
}