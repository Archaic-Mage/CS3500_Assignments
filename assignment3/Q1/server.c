/*
    CS3500: Assignment
    Author: Soham Tripathy CS20B073
    Topic: Client Server communication using message queues
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <errno.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

// structure for message queue
typedef struct mesg_buffer {
	long mesg_type;
	char mesg_text[1000];
} message;


//Stores the file descriptor
int fd = -1;

//flag for valid command
int flag = 0;

//function to process the system calls
int processCall(char* text) {

    //open(2) system call
    if(strcmp(text, "open\n") == 0) {
        flag = 1;
        fd = open("./temp.txt", O_RDWR | O_CREAT, S_IRWXU);
        return fd;
    } 

    //close(1) system call
    if(strcmp(text, "close\n") == 0) {
        flag = 1;
        int out = close(fd);
        fd = -1;
        return out;
    }

    //read(3) system call
    if(strcmp(text, "read\n") == 0) {
        flag = 1;
        char* buff;
        buff = (char *) malloc(sizeof(char)*1000);
        size_t out = read(fd, buff, 1000);

        return (int) out;
    }

    //write(3) system call
    if(strcmp(text, "write\n") == 0) {
        flag = 1;
        if(fd == -1) return -1;
        char buff[] = "This is Writing\n";
        int out = (int) write(fd, buff, sizeof(buff));
        return out;
    }

    //fchmod(2) system call
    if(strcmp(text, "fchmod\n") == 0) {
        flag = 1;
        return fchmod(fd, S_IRWXU | S_IRWXG | S_IRWXO);
    }

    flag = 0;
    return -1;
    
}

int main()
{
    //keys for c2s and s2c process respectively
	key_t key, key2;

    //indentifiers for the process
	int c2s_id;
    int s2c_id;

    //message queue elements
    message s2c_msg;

    //setting the key values
	key = 12345678;
    key2 = 87654321;

    printf("|******* Server Side *******|\n");

    while(true) {

        printf("\n");
        printf("..Server Waiting for User System Call..\n");

        //Recieves System call from client side
        message c2s_msg;

        // msgget creates a message queue
	    // and returns identifier
        c2s_id = msgget(key, 0666 | IPC_CREAT);

        // recieves the messages from the message queue
        msgrcv(c2s_id, &c2s_msg, sizeof(c2s_msg), 1, 0);

        //exit condition
        if(strcmp(c2s_msg.mesg_text, "End\n") == 0) break;

        printf("...Server is working!...\n");

        s2c_id = msgget(key2, 0666 | IPC_CREAT);
        s2c_msg.mesg_type = 1;

        int result = processCall(c2s_msg.mesg_text);
        if(flag) sprintf(s2c_msg.mesg_text, "%d", result);
        else sprintf(s2c_msg.mesg_text, "Enter Valid System Call");

        //sends the data returned by execution of such commands
        msgsnd(s2c_id, &s2c_msg, sizeof(s2c_msg), 0);

        printf("--- Server done working! ----\n");
    }

    // to destroy the message queue
	msgctl(c2s_id, IPC_RMID, NULL);

    remove("./temp.txt");

	return 0;
}
