/* 

   CS3500: Assignment
   Author: Soham Tripathy CS20B073
   Topic: Immitate Shell by C


   functions: camelCase
   variables: snake_case
   constanst: UPPER_CASE
   
*/

//requiring the header files for the project

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

//declaring the required variables

char cwd[PATH_MAX];
char command[20] = "true";         
char* options[32];
FILE *fp;
char ch;


//declaring the command functions which will be called 


//to the current working directory

void getWorkingDirectory() {
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
       perror("getcwd() error");
       exit(1);
    }
}


//command pushes the stearm of characters in the file

void pushCommand(char* com) {
   fp = fopen("past_commands.txt", "a");
   int i = 0;
   while(com[i] != '\0') {
      putc(com[i], fp);
      i++;
   }
   fclose(fp);
}


//function to get command and its options

void getCommand() {

   //creating buffer to get the input line

   char* buffer;
   size_t bufsize = 32;
   buffer = (char *) malloc(bufsize * sizeof(char));

   //handling the errors

   if(buffer == NULL) {
      perror("Unable to allocate buffer");
      exit(1);
   }

   getline(&buffer, &bufsize, stdin);

   //processing the input line - splitting by spaces

   int i = 0;
   int k = -1;
   int j = 0;
   int start = 0;

   command[0] = '\0';

   while(buffer[i] != '\0') {

      char c = buffer[i];

      if(c != ' ' && c != '\n' && !start) {
         start = 1;
         if(k == -1) {
            command[j] = c;
            j++;
         } else {
            options[k][j] = c;
            j++;
         }
      } else if(c != ' ' && c != '\n' && start) {
         if(k == -1) {
            command[j] = c;
            j++;
         } else {
            options[k][j] = c;
            j++;
         }
      } else if((c == ' ' || c == '\n') && start) {
         start = 0;
         if(k == -1) command[j] = '\0';
         else options[k][j] = '\0';
         k++;
         options[k] = (char*) malloc (32*sizeof(char));
         j = 0;
      }

      i++;
   }

   options[k] = "";

   //storing the commands in the file to remember them

   if(strlen(command) != 0) pushCommand(buffer);

   free(buffer);
}

 
//makes a directory with the name 'dir' and permissions 0777

void mkdirDir() {
   int is_ndone = mkdir("dir", 0777);

   if(is_ndone) {
      perror("Unable to create a directory");
      exit(1);
   }
}


//removes directory named 'dir' if present in the pwd

void rmdirDir() {
   int is_ndone = rmdir("./dir");

   if(is_ndone) {
      perror("Unable to delete the directory");
   }
}


//this command gives all the previous commands with recent most at the bottom

void history() {
   fp = fopen("past_commands.txt", "r");
   while((ch = getc(fp)) != EOF) {
      printf("%c", ch);
   }
   fclose(fp);
}


//executes the pseudo shell commands

void executeCommand() {

   if(strlen(command) == 0) return;

   if(strcmp(command, "clear") == 0) {

      if(strlen(options[0]) > 0) {
         printf("Options not valid\n");
         return;
      }

      system("clear");

      return;
   }

   if(strcmp(command, "mkdir") == 0) {

      if(strlen(options[0]) > 0) {
         printf("Options not valid\n");
         return;
      }

      mkdirDir();

      return;
   }

   if(strcmp(command, "rmdir")==0) {

      if(strlen(options[0]) > 0) {
         printf("Options not valid\n");
         return;
      }

      rmdirDir();

      return;
   }

   if(strcmp(command, "pwd") == 0) {

      if(strlen(options[0]) > 0) {
         printf("Options not valid\n");
         return;
      }

      printf("%s\n", cwd);

      return;
   }

   if(strcmp(command, "ls") == 0) {

      if(strlen(options[0]) != 0 && strcmp(options[0], "-l") != 0) {
         printf("Options not valid\n");
         return;
      } 
      else if(strlen(options[0]) == 0) system("ls");
      else system("ls -l");

      return;
   }

   if(strcmp(command, "history") == 0) {

      if(strlen(options[0]) > 0) {
         printf("Options not valid\n");
         return;
      }

      history();

      return;
   }

   if(strcmp(command, "exit") == 0) return;

   printf("Command not found\n");
   return;
}

int main() {

   //gets the working directory
   getWorkingDirectory();

   //clears the txt file or creates a new file
   fp = fopen("past_commands.txt", "w");
   fclose(fp);

   while(strcmp(command, "exit") != 0) {
      printf("%s>", cwd);
      getCommand();
      executeCommand();      
   }

   return 0;
}