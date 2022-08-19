/*

    CS3500: Assignment
    Author: Soham Tripathy CS20B073
    Topic: Searching Array using Threads

*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int fd[2];              // declaring variables for the file descriptors (pipe)
    pid_t pid;              // declaring the pid to identify the processes
    char buf;               // char buff to read the inputs

    if (argc < 2)
    {
        perror("Number of Arguments is too small-> please enter the string to process");
        exit(1);
    } else if(argc > 2) {
        perror("So Many arguments!");
        exit(1);
    }

    if (pipe(fd) != 0)             // calling the pipe to get file descriptors of the read and write ends
    {
        perror("Failed to pipe!");
        exit(1);
    }

    pid = fork();                 //creating the child process for the parent
    if (pid == -1)
    {
        perror("forking error!");
        exit(1);
    }

    if (pid != 0)
    {                                       /* Parent reads from pipe */
        close(fd[1]);                       /* Close unused write end */
        cout << "Reading from the pipe in Parent Process\n";
        while(read(fd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO             /* file descriptor for stdout*/
                , &buf, 1);                 //till we recieve EOF the child will read one character and print it
        }    
        write(STDOUT_FILENO, "\n", 1);        
        close(fd[0]);
        exit(0);
    }
    else
    {   // Child writes argv[1] to pipe
        close(fd[0]);                               // Close unused read end 
        write(fd[1], argv[1], strlen(argv[1]));
        close(fd[1]);                               //closing the write end to send EOF
        wait(NULL);                                 // Wait for child 
        exit(0);
    }
}
