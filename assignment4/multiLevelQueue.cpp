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

//for printing
const char separator    = ' ';

template<typename T> void printElement(T t)
{
    cout << left << setw(25) << setfill(separator) << t;
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

bool areAllQueueEmpty(vector<Process_Queue> Queues) {

    for(Process_Queue process_queue: Queues) {
        if(process_queue.getQueueSize()) {
            return false;
        }
    }

    return true;
}

int main() {

    int robinTimeSlice;
    int numberOfProcesses;

    cin >> robinTimeSlice >> numberOfProcesses;

    //indicating process completed or not
    unordered_map<int, Process> process_complete;

    //execution sequence
    vector<int> process_exe_sequence; 
    vector<int> time_sequence;
    time_sequence.push_back(0);

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

        Queues[curr_process.process_type-1].addWaitingList(curr_process);
    }

    print("Done taking in input");

    //Scheduling

    int time = 0;
    int i = 0;

    while(process_complete.size() != numberOfProcesses) {

        int init_time = time;

        for(int j = 0; j<5; j++) {
            while(Queues[j].waiting_processes.size() != 0 && Queues[j].waiting_processes[0].arrival_time <= time) {
                Queues[j].addProcess(Queues[j].waiting_processes[0]);
                Queues[j].waiting_processes.erase(Queues[j].waiting_processes.begin());
                print("added for process for time");
            }
        }


        //executes the processes

        vector<Process> executed_processes = Queues[i].executeProcess(time, time_sequence);

        if(time == init_time && areAllQueueEmpty(Queues)) {
            print("CPU gap");
            // CPU gap - When no process is available - it should reset
            time++;
            i=-1;           //resets CPU
        }

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

    printElement("Process ID");
    printElement("Arrival Time (A.T)");
    printElement("Brust Time (B.T)");
    printElement("Completion Time (C.T)");
    printElement("Turn-Around Time (T.A.T)");
    printElement("Wait Time (W.T)");
    cout << endl;

    for(int i = 0; i<numberOfProcesses; i++) {

        Process p = process_complete[i+1];

        //print process id
        printElement(p.id);
        printElement(p.arrival_time);
        printElement(p.brust_time);
        printElement(p.completion_time);
        printElement(p.completion_time - p.arrival_time);
        printElement(p.completion_time - p.arrival_time - p.brust_time);
        cout << endl;
    }

    cout << endl;

    int j = 0;

    cout << "(" <<time_sequence[j] << ") ";
    j++;

    for(int process: process_exe_sequence) { 
        cout << "p" << process << " ";
        cout << "(" <<time_sequence[j] << ") ";
        j++;
    }

    return 0;
}