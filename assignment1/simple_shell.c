/* 

   CS3500: Assignment
   Author: Soham Tripathy CS20B073
   Topic: Immitate Shell by C

*/


#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

//declaring the required variables
char cwd[PATH_MAX];
char* commands[7] = {"clear", "pwd", "mkdir", "ls", "history", "exit"};
char command[20] = "true";


//declaring the command functions which will be called 

void getWorkingDirectory() {
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
       perror("getcwd() error");
       exit(1);
    }
}

void getCommand() {
   char* buffer;
   size_t bufsize = 32;
   buffer = (char *) malloc(bufsize * sizeof(char));

   if(buffer == NULL) {
      perror("Unable to allocate buffer");
      exit(1);
   }

   getline(&buffer, &bufsize, stdin);
}

void clear() {
   system("clear");
}
 
void mkdirDir() {
   int is_ndone = mkdir("dir", 0777);

   if(is_ndone) {
      perror("Unable to create a directory");
      exit(1);
   }
}

void rmdirDir() {
   int is_ndone = rmdir("./dir");

   if(is_ndone) {
      perror("Unable to delete the directory");
      exit(1);
   }
}

// void ls(char options[]) {

// }

// void history() {

// }

int main() {

   getWorkingDirectory();

   while(strcmp(command, "exit") != 0) {
      printf("%s> ", cwd);
      scanf("%s", command);
      if(strcmp(command, "clear") == 0) clear();
      if(strcmp(command, "mkdir") == 0) {
         mkdirDir();
      }
      if(strcmp(command, "rmdir")==0) {
         rmdirDir();
      }
      if(strcmp(command, "pwd") == 0) {
         printf("%s\n", cwd);
      }
   }

   return 0;
}