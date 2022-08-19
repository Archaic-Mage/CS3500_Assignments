/*

    CS3500: Assignment
    Author: Soham Tripathy CS20B073
    Topic: Searching Array using Threads

*/


#include <iostream>
#include <bits/stdc++.h>
#include <pthread.h>


//creating a struct to pass it as argument in threads
typedef struct Array {
    long long* s;               //starting array pointer
    long long* e;               //ending array pointer
} Array;


//creating variables that will be shared by all the threads (Global Variables)

long long* a;                           //pointer to array
long long a_siz;                        //array size
long long N;                            //number of divisions of array (for searching)
long long element;                      //element to find the multiples for
long long cnt = 0;                      //counting the number of multiples

using namespace std;

//function to check errors
void check(int s) {
    if(s != 0) {
        perror("Oops! Faces some issues.");
        exit(1);
    }
    return;
}

//function to find the multiples
void* find_multiples(void* arg) {

    Array* arr = (Array *) arg;

    for(auto i = arr->s; i <= arr->e; i++) {
        long long ele = *i;
        if(ele%element == 0) cnt++;
    }

    return (void*) NULL;
}

//function to merge the two half of sorted arrays
void* merge(void* arg) {

    long long* x = (long long*) malloc(a_siz*sizeof(long long));

    long long k = 0, i = 0, j = a_siz/2+1;

    while(k < a_siz) {
        if(j == a_siz || a[i] < a[j]) {
            x[k] = a[i];
            i++, k++;
        } else if(i == a_siz/2+1 || a[i] >= a[j]) {
            x[k] = a[j];
            j++, k++;
        }
    }

    for(i = 0; i<a_siz; i++) {
        a[i] = x[i];
    }

    free(x);

    return (void*) NULL;
}

//sorts the first half of the array
void* sort_array_1(void* arg) {
    sort(a, a+a_siz/2+1);
    return (void*) NULL;
}

//sorts the second half of the array
void* sort_array_2(void* arg) {
    sort(a+a_siz/2+1, a+a_siz);
    return (void*) NULL;
}

int main() {

    //getting the array size
    cout << "Enter Array Size: ";
    cin >> a_siz;

    //allocating space for the array
    a = (long long*) malloc(a_siz*sizeof(long long));

    //getting number of divisions
    cout << "Enter number N: ";
    cin >> N;

    while(N > a_siz) {
        cout << "Invalid partition number (N cannot be greater than array size)\n";
        cin >> N;
    }

    //getting array values
    cout << "Enter array elements:\n";
    for(long long i = 0; i<a_siz; i++) {
        cin >> a[i];
    }

    //getting the element to check multiples for
    cout << "Enter element number: ";
    cin >> element;

    //declaring the thread attr and ids(processes)
    pthread_attr_t attr;
    pthread_t ptids[N];


    //creating two threads to sort the first and second half of the array
    check(pthread_attr_init(&attr));
    check(pthread_create(&ptids[0], &attr, sort_array_1, (void*) NULL));
    check(pthread_attr_init(&attr));
    check(pthread_create(&ptids[1], &attr, sort_array_2, (void*) NULL));

    //joining the threads created
    check(pthread_join(ptids[0], NULL));
    check(pthread_join(ptids[1], NULL));

    //creating a thread to merge the two sorted halves
    check(pthread_attr_init(&attr));
    check(pthread_create(&ptids[0], &attr, merge, (void*) NULL));
    check(pthread_join(ptids[0], NULL));


    //creating N threads to search and count multiples of element
    for(int i = 0; i< N; i++) {
        Array arr;
        if(i == N-1) {
            arr.s = a + i*(a_siz/N);
            arr.e = a + a_siz;
        } else {
            arr.s = a + i*(a_siz/N);
            arr.e = a + (i+1)*(a_siz/N);
        }
        check(pthread_attr_init(&attr));
        check(pthread_create(&ptids[i], &attr, find_multiples, &arr));
    }


    //joining the N threads
    for(int i = 0; i<N; i++) {
        check(pthread_join(ptids[i], NULL));
    }

    //printing the final results
    cout << cnt << endl;  

    //free all the memory used
    free(a);  

    return 0;
}