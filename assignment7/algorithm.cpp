#include <bits/stdc++.h>
#include "fcfs.cpp"
#include "sstf.cpp"
#include "scan.cpp"
#include "c-scan.cpp"
#include "look.cpp"
#include "c-look.cpp"

int no_of_cylinders = 5000;
int no_of_requests = 1000;

vector<int> requests;

void printOrder(pair<vector<int>, int> ans) {
    vector<int> order = ans.first;
    int total_head_movement = ans.second;
    cout << "Sequence of Requests' served\n";
    for(auto req: order) cout << req << " ";
    cout << "\n";
    cout << "Average Head Movement: " << (double) total_head_movement/ (double) requests.size() << endl;
    cout << "Total Head Movement: " << total_head_movement << endl;
}

void printCSV(pair<vector<int>, int> ans, int algo) {
    vector<int> order = ans.first;
    int total_head_movement = ans.second;
    string name = "./csv/"+ to_string(algo)+".csv";
    ofstream Myfile(name);
    Myfile << "Reqs\n";
    Myfile << 2000 << "\n";
    for(int req : order) {
        Myfile << req << "\n";
    }
    Myfile.close();
}

int main(int argc, char* argv[]) {

    srand(time(NULL));

    int initial_head = 2000;
    int algorithm = 1;

    for(int i = 0; i<no_of_requests; i++) {
        requests.push_back(rand()%no_of_cylinders);
    }

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i],"-h") == 0) {
            i++;
            initial_head = stoi(argv[i]);
        } else if(strcmp(argv[i],"-a") == 0) {
            i++;
            algorithm = stoi(argv[i]);
        } else {
            cout << "Illegal argument\n";
            return 0;
        }
    }

    if(argc == 1) {
        pair<vector<int>, int> ans;

        for(algorithm = 1; algorithm<7; algorithm++) {
            switch(algorithm) {
                case 1: 
                    ans = fcfs(requests, initial_head);
                    printOrder(ans);
                    printCSV(ans, algorithm);           
                    break;
                case 2:
                    ans = sstf(requests, initial_head);
                    printOrder(ans);
                    printCSV(ans, algorithm); 
                    break;
                case 3:
                    ans = scan(requests, initial_head);
                    printOrder(ans);
                    printCSV(ans, algorithm); 
                    break;
                case 4:
                    ans = cScan(requests, initial_head, no_of_cylinders);
                    printOrder(ans);
                    printCSV(ans, algorithm); 
                    break;
                case 5:
                    ans = look(requests, initial_head);
                    printOrder(ans);
                    printCSV(ans, algorithm); 
                    break;
                case 6: 
                    ans = cLook(requests, initial_head);
                    printOrder(ans);
                    printCSV(ans, algorithm); 
                    break;
                default:
                    break;
            }

        }

        return 0;
    }

    
    switch(algorithm) {
        case 1: 
            printOrder(fcfs(requests, initial_head));            
            break;
        case 2:
            printOrder(sstf(requests, initial_head));
            break;
        case 3:
            printOrder(scan(requests, initial_head));
            break;
        case 4:
            printOrder(cScan(requests, initial_head, no_of_cylinders));
            break;
        case 5:
            printOrder(look(requests, initial_head));
            break;
        case 6: 
            printOrder(cLook(requests, initial_head));
            break;
        default:
            break;
    }


    return 0;
}