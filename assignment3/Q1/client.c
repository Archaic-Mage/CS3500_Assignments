/*
    CS3500: Assignment
    Author: Soham Tripathy CS20B073
    Topic: Client Server communication using message queues
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

// structure for message queue
typedef struct mesg_buffer {
	long mesg_type;
	char mesg_text[1000];
} message;


int main()
{
    //keys for c2s and s2c process respectively
	key_t key, key2;

    //identifiers for the process
	int c2s_id;
    int s2c_id;

    //message queue elements
    message c2s_msg;

    //setting the key values
	key = 12345678;
    key2 = 87654321;

    printf("|******* Client Side *******|\n");

    while(true) {

        printf("\n");

        // msgget creates a message queue
	    // and returns identifier
        c2s_id = msgget(key, 0666 | IPC_CREAT);
	    c2s_msg.mesg_type = 1;

        printf("...Waiting For User Input....\n");
        printf("Enter System Call: ");
        fgets(c2s_msg.mesg_text, MAX, stdin);

        // msgsnd to send message
	    if(msgsnd(c2s_id, &c2s_msg, sizeof(c2s_msg), 0) == -1) {
            printf("Failed to Send the Data!\n");
            printf("...Please! Try Again....\n");
        } else {
            printf("...Data Sent Successfully...\n");
        }

        //exit condition
        if(strcmp(c2s_msg.mesg_text, "End\n") == 0) break;

        //Output Message from Server
        message s2c_msg;

        s2c_id = msgget(key2, 0666 | IPC_CREAT);

        printf("...Client waiting for output!..\n");

        if(msgrcv(s2c_id, &s2c_msg, sizeof(s2c_msg), 1, 0) == -1) {
            printf("Failed to Recieve the Data!\n");
            printf("....Please! Try Again.....\n");
        } else {
            printf("Data recieved is : %s \n", s2c_msg.mesg_text);
        }        
    }

	return 0;
}
