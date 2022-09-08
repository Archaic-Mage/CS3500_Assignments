/*
    Author: Soham Tripathy CS20B073
    CS3500: Assignment
    Topic: Multi-Pipeline IPC
*/

#include <stdlib.h>

//Commands Used for communication
#define REQUEST 100
#define PIVOT 200
#define LARGE 300
#define SMALL 400
#define READY 500
#define EXIT 600

//Properties required by each child
int id;
char* file_name;
int array[50];
int len = 5;
int pivot;

//setting the id for each child
void set_id(int i) {
    id = i;
}

//execute child function
void executeChild(int data_recieved, int data_send) {

    //set the index i
    int i = id-1;

    //for debugging if all the elements become empty
    is_empty[i] = 0;

    for(int i = 0; i<50; i++) array[i] = -1;

    //getting the file name with respect to the id given
    file_name = (char *) malloc(sizeof(char)*100);
    sprintf(file_name, "./data/data_%d.txt", id);

    //open file and get the array
    FILE *myfile;
    myfile = fopen(file_name, "r");

    for(int i = 0; i<5; i++) {
        fscanf(myfile, "%d", &array[i]);
    }

    fclose(myfile);
    
    //Sends ready after recieving the ids
    data_send = READY;
    write(fd[2*i][1], &data_send, sizeof(READY));
    printf("Child %d sends READY\n", i+1); 

    //Enters while loop to accept commands from parent->child pipes
    data_recieved = -1;

    while(data_recieved != EXIT) {

        //read the command
        read(fd[2*i+1][0], &data_recieved, sizeof(data_recieved));

        //command processing
        if(data_recieved == REQUEST) {
            //handeling request
            if(len == 0) {
                //if length zero - send -1
                data_send = -1;
                write(fd[2*i][1], &data_send, sizeof(data_send));
            } else {
                //else sends random number
                data_send = array[rand()%len];                
                write(fd[2*i][1], &data_send, sizeof(data_send));
            }
        } 
        else if(data_recieved == PIVOT) {
            //reads the pivot
            read(fd[2*i+1][0], &data_recieved, sizeof(data_recieved));

            //sets the pivot
            pivot = data_recieved;

            //set the count variable
            int greater = 0;

            //find the count
            for(int i = 0; i<len; i++) {
                if(array[i] > pivot) greater++;
            }

            //send the count to parent
            data_send = greater;
            write(fd[2*i][1], &data_send, sizeof(data_send));

            //print the information
            printf("Child %d recieves pivot and replies %d\n", id, data_send);
            fflush(stdout);

        } else if(data_recieved == SMALL) {
            //removes elements smaller then pivot from the array
            for(int i = 0; i<len; i++) {
                if(array[i] < pivot) {
                    int temp = array[len-1];
                    array[len-1] = array[i];
                    array[i] = temp;
                    len--;
                    i--;
                }
            }
        } else if(data_recieved == LARGE) {
            //removes elements larger than pivot from the array
            for(int i = 0; i<len; i++) {
                if(array[i] > pivot) {
                    int temp = array[len-1];
                    array[len-1] = array[i];
                    array[i] = temp;
                    len--;
                    i--;
                }
            }
        }
    }

    //when the child terminates
    printf("Child %d terminates\n", id);
}