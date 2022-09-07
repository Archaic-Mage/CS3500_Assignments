/*
    CS3500: Assignment
    Author: Soham Tripathy CS20B073
    Topic: Client Server communication using message queues
*/

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1000000

typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[1000000];
} message;
  
int main()
{
    key_t c2s_key, s2c_key;
    int c2s;
    int s2c;
    message c2s_msg;
    message s2c_msg;

    c2s_key = 12345678;
    s2c_key = 87654321;
  
    // msgget creates a message queue
    // and returns identifier
    c2s = msgget(c2s_key, 0666 | IPC_CREAT);
    s2c = msgget(s2c_key, 0666 | IPC_CREAT);
    
    msgrcv(c2s, &c2s_msg, sizeof(c2s_msg), 0, 0);

    while(strcmp(c2s_msg.mesg_text, "End") != 0) {
        printf("%s", c2s_msg.mesg_text);
    }
  
    return 0;
}