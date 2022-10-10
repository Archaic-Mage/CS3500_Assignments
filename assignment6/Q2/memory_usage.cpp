#include <bits/stdc++.h>
#include <sys/resource.h>

using namespace std;

//for having the information regarding the memory usage and page faults
struct rusage* resource_used;

//for storing random numbers in the array
long number = rand();


//function to alllocate the memory to a 2d array
void allocate(long** &A, int n) {
    A = (long **) malloc(sizeof(long*)*n);
    for(int i = 0; i<n; i++) {
        A[i] = (long *) malloc(sizeof(long)*n);
        for(int j = 0; j < n; j++) {
            A[i][j] = number;
        }  
    }
}

//function to find the inplace transpose of a matrix
void transpose(long** &A, int n) {
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<n; j++) {
            swap(A[i], A[j]);
        }
    }
}


//analysing the memory usage and page faults in type 1 execution
void type1(int n) {

    resource_used = (struct rusage*) malloc(sizeof(struct rusage));
    getrusage(RUSAGE_SELF, resource_used);
    long baseline_memory = resource_used->ru_maxrss;

    long** A;
    long** B;
    long** C;
    long** D;
    long** E;

    allocate(A, n);
    allocate(B, n);
    allocate(C, n);
    allocate(D, n);
    allocate(E, n);


    for(int i = 0; i<10; i++) {


        transpose(A, n);
        transpose(B, n);
        transpose(C, n);
        transpose(D, n);
        transpose(E, n);

        getrusage(RUSAGE_SELF, resource_used);

        cout << "memory usage: " << baseline_memory << " + " << resource_used->ru_maxrss - baseline_memory << ", page_faults: " << resource_used->ru_majflt + resource_used->ru_minflt << endl;
    }

    
}

//analysing the memory usage and page faults in type 2 execution
void type2(int n) {

    resource_used = (struct rusage*) malloc(sizeof(struct rusage));
    getrusage(RUSAGE_SELF, resource_used);
    long baseline_memory = resource_used->ru_maxrss;

    long** A;
    long** B;
    long** C;
    long** D;
    long** E;


    for(int i = 0; i<10; i++) {

        allocate(A, n);
        allocate(B, n);
        allocate(C, n);
        allocate(D, n);
        allocate(E, n);
        transpose(A, n);
        transpose(B, n);
        transpose(C, n);
        transpose(D, n);
        transpose(E, n);

        getrusage(RUSAGE_SELF, resource_used);

        cout << "memory usage: " << baseline_memory << " + " << resource_used->ru_maxrss - baseline_memory << ", page_faults: " << resource_used->ru_majflt + resource_used->ru_minflt << endl;
    }
}

int main() {
    int n; 
    cout << "Enter n value: ";
    cin >> n;   
    cout << endl;

    cout << "Memory Allocated once: 1\n";
    cout << "Memory Allocated each time: 2\n";
    cout << endl;

    int type_memory;
    cout << "Type of Memory Allocation: ";
    cin >> type_memory;
    cout << endl;
    
    if(type_memory==1) type1(n);
    else if(type_memory ==2)type2(n);
    else cout << "incorrect memory type allocation\n";
}