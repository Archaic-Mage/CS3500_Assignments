/*
    Author: Soham Tripathy CS20B073
    CS3500: Assignment
    Topic: Multi-Pipeline IPC
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

//debug print
void print(char* s) {
    printf("%s\n", s);
    fflush(stdout);
}

//file descriptors
int fd[10][2];

//process ids childs
pid_t pid[5];

//for arrays
int n = 25;
int is_empty[5];

//including the child.c for executing child process
#include "child.c"

//declaring the data send and recieve variables
int data_recieved;
int data_send;

int m_child[5];
int m = 0;
int k;


void executeParent() {
    
    //selects a random child and queries it for a random element
    //reads the response for non-negative pivot
    data_recieved = -1;

    while(data_recieved == -1) {
        int req_child = rand()%5;
        data_send = REQUEST;
    
        write(fd[2*req_child+1][1], &data_send, sizeof(data_send));
        printf("Parent send REQUEST to Child %d\n", req_child);

        //reading from child

        read(fd[2*req_child][0], &data_recieved, sizeof(data_recieved));
        printf("Child %d sends %d to parent\n", req_child, data_recieved);
        if(data_recieved == -1) is_empty[req_child] = 1;

        int to_stop = 1;
        for(int i = 0; i<5; i++) if(is_empty[i] != 1) to_stop = 0;
        if(to_stop) {
            perror("all empty\n");
            exit(0);
        }
    }

    //setting the pivot and broadcasting it to all the childs
    int pivot = data_recieved;

    for(int i = 0; i<5; i++) {
        data_send = PIVOT;
        write(fd[2*i+1][1], &data_send, sizeof(data_send));
    }

    for(int i = 0; i<5; i++) {
        data_send = pivot;
        write(fd[2*i+1][1], &data_send, sizeof(data_send));
    }

    printf("Parent broadcasts pivot %d to all children\n", pivot);

    //reads the responses from the child
    m = 0;
    for(int i = 0; i<5; i++) {
        read(fd[2*i][0], &data_recieved, sizeof(data_recieved));
        m_child[i] = data_recieved;
        m+=data_recieved;
    }
}

int main() {

    //creating the pipes for communication
    for(int i = 0; i<5; i++) {
        pipe(fd[2*i]);
        pipe(fd[2*i+1]);
    }

    //parent creates child processes
    for(int i = 0; i<5; i++) {
        pid[i] = fork();

        if(pid[i] == 0) {

            //recieving the id
            int data_recieved;
            int data_send;

            read(fd[2*i+1][0], &data_recieved, sizeof(data_recieved));
            
            set_id(data_recieved);

            executeChild(data_recieved, data_send);

            return 0;
        }
    }

    //allocating ids
    for(int i = 0; i<5; i++) {
        data_send = i+1;
        write(fd[2*i+1][1], &data_send, sizeof(i+1));
    }

    //checking if ready
    int done = 0;
    for(int i = 0; i<5; i++) {
        if(read(fd[2*i][0], &data_recieved, 4) < 0 ) 
        {
            perror("failed to read");
            exit(0);
        } else done++;
    }
    if(done == 5) printf("Parent READY\n");

    //instantiates k = n/2
    k = n/2;

    //executeParent untill k == m
    while(k != m) {
        
        executeParent();

        //checking condition for k and m
        if(m==k) {
            //formating for output
            printf("Parent: m=");
            for(int i = 0; i<5; i++) {
                printf("%d", m_child[i]);
                if(i != 4) printf("+");
                else {
                    printf("=%d. %d=%d Median found!\n", m, m, k);
                    printf("Median = %d\n", data_send);
                }
            }

            //sends the exit to all child
            data_send = EXIT;                       
            print("Parent sends kill signals to all children");
            for(int i = 0; i<5; i++) {
                write(fd[2*i+1][1], &data_send, sizeof(data_send));
            }
            break;
        } else if(m > k) {
            //Sends Small signal to all child
            data_send = SMALL;

            printf("Parent broadcasts SMALL to all its child\n");

            for(int i = 0; i<5; i++) {
                write(fd[2*i+1][1], &data_send, sizeof(data_send));
            }
        } else if(m < k) {
            //sends Large signal to all children
            data_send = LARGE;

            printf("Parent broadcasts LARGE to all its child\n");

            for(int i = 0; i<5; i++) {
                write(fd[2*i+1][1], &data_send, sizeof(data_send));
            }
            k-=m;
        }
        //resetting the m value
        m=0;
    }

    //closes the pipes for communication
    for(int i = 0; i<10; i++) {
        for(int j = 0; j<1; j++) {
            close(fd[i][j]);
        }
    }

    //waits for the  child processes to teminate
    for(int i = 0; i<5; i++) wait(NULL);

    return 0;
}