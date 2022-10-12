/*
    Author: Soham Tripathy
    CS3500: Assignment
    Topic: Contigous Memory Allocations

*/

#include <bits/stdc++.h>

using namespace std;

template<typename T> void printElement(T t)
{
    cout << left << setw(20) << setfill(' ') << t;
}

class Allocation {
public:
    vector<pair<int, int>> processes;
    vector<pair<int, int>> blocks;

    void printAllocation() {
        printElement("Process number");
        printElement("Process size");
        printElement("Block size");
        printElement("Block number");
        cout << endl;


        for(int i = 0; i<processes.size(); i++) {
            printElement(processes[i].second);
            printElement(processes[i].first);
            if(blocks[i].first == -1) {
                printElement("NA");
                printElement("NA");
            }else {
                printElement(blocks[i].first);
                printElement(blocks[i].second);
            }

            cout << endl;
        }
    }

    void createCSV(string name) {
        ofstream csv_file(name + ".csv");

        csv_file << "Process number,Process size,Block size, Block number\n"; 

        for(int i = 0; i<processes.size(); i++) {
            csv_file << processes[i].second << ',' << processes[i].first << ',';
            csv_file << blocks[i].first << ',' << blocks[i].second;
            csv_file << '\n';
        }

        csv_file.close();
    }
};

void firstFit(vector<pair<int, int>> blocks, vector<pair<int, int>> processes) {

    Allocation first_fit_allocation = Allocation();
    
    for(auto process: processes) {
        auto i = blocks.begin();
        bool found = false;
        for(auto block: blocks) {
            if(block.first >= process.first) {
                first_fit_allocation.processes.push_back(process);
                first_fit_allocation.blocks.push_back(block);
                blocks.erase(i);
                found = true;
                break;
            } 
            i++;
        }

        if(!found) {
            first_fit_allocation.processes.push_back(process);
            first_fit_allocation.blocks.push_back({-1, -1});
        }
    }

    cout << "FIRST-FIT\n\n";
    first_fit_allocation.printAllocation();
    cout << endl;
}

void bestFit(vector<pair<int, int>> blocks, vector<pair<int, int>> processes) {
    Allocation best_fit_allocation = Allocation();

    sort(blocks.begin(), blocks.end());

    for(auto process: processes) {
        auto i = blocks.begin();
        bool found = false;
        for(auto block: blocks) {
            if(block.first >= process.first) {
                best_fit_allocation.processes.push_back(process);
                best_fit_allocation.blocks.push_back(block);
                blocks.erase(i);
                found = true;
                break;
            } 
            i++;
        }

        if(!found) {
            best_fit_allocation.processes.push_back(process);
            best_fit_allocation.blocks.push_back({-1, -1});
        }
    }

    cout << "BEST-FIT\n\n";
    best_fit_allocation.printAllocation();
    cout << endl;
}

void worstFit(vector<pair<int,int>> blocks, vector<pair<int, int>> processes) {
    Allocation worst_fit_allocation = Allocation();

    sort(blocks.begin(), blocks.end());
    reverse(blocks.begin(), blocks.end());

    for(auto process: processes) {
        auto i = blocks.begin();
        bool found = false;

        for(auto block: blocks) {
            if(block.first >= process.first) {
                worst_fit_allocation.processes.push_back(process);
                worst_fit_allocation.blocks.push_back(block);
                blocks.erase(i);
                found = true;
                break;
            }
            i++;
        }

        if(!found) {
            worst_fit_allocation.processes.push_back(process);
            worst_fit_allocation.blocks.push_back({-1, -1});
        }
    }

    cout << "WORST-FIT\n\n";
    worst_fit_allocation.printAllocation();
    cout << endl;
}

int main() {

    vector<pair<int, int>> blocks;
    vector<pair<int, int>> processes;

    int number_of_blocks, number_of_processes;

    cout << "Enter Number of Blocks: ";
    cin >> number_of_blocks;

    cout << "Enter " << number_of_blocks << " block sizes: ";

    for(int i = 0; i<number_of_blocks; i++) {
        int size; 
        cin >> size;
        blocks.push_back({size, i+1});
    }

    cout << "Enter Number of Processes: ";
    cin >> number_of_processes;

    cout << "Enter " << number_of_processes << " Process sizes: ";

    for(int i = 0; i<number_of_processes; i++) {
        int size;
        cin >> size;
        processes.push_back({size, i+1});
    }

    cout << endl;
    
    firstFit(blocks, processes);
    bestFit(blocks, processes);
    worstFit(blocks, processes);

    return 0;
}