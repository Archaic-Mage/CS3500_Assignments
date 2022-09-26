#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

//stock buffer

/***** Stack *****/

int MAXSIZE = 100000;       
int stack[100000];     
int top = -1;            

//stack functions

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

void pop() {
   int data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

void push(int data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}


// Semaphore for Stack (since it is the critical section)
// 0 -> stack is busy and being used by some producer or consumer
// 1 -> stack is available and can used by anyone
sem_t is_stack_available;


/***** Producers *****/

int no_of_producers;
int* capacity_of_production;
int max_production_capacity;

void* produce_product(void* index) {

   //we get the index of producer
   int which_producer = (int) index;

   //till the capacity is not zero we keep iterating
   while(capacity_of_production[which_producer] > 0) {

      //checking if stack is available
      //we use it if available
      sem_wait(&is_stack_available);

      int to_produce = rand()%501 + 500;

      push(to_produce);

      //producer produces the number
      printf("Producer %d produced %d\n", which_producer+1, to_produce);
      fflush(stdout);

      //we decrease the capacity of production
      capacity_of_production[which_producer]--;

      //we make the stack available again      
      sem_post(&is_stack_available);
   }

}

/**** Consumers ****/

int no_of_consumers;
int* capacity_of_consumption;
int max_consumer_capacity;

void* consume_product(void* ind) {
   
  //consumer index 
   int which_consumer = (int) ind;

   while(capacity_of_consumption[which_consumer] > 0) {

     // waits till the stack has atleast one element

      //checks if stack is available
      // and uses it if free
      sem_wait(&is_stack_available);

      if(isempty()) {
         sem_post(&is_stack_available);
         continue;
      }

      int to_consume = peek();
      pop();

      printf("Consumer %d consumed %d\n", which_consumer+1, to_consume);
      fflush(stdout);

      capacity_of_consumption[which_consumer]--;

      // make the stack available again
      sem_post(&is_stack_available);

   }
}


int main(int argc, char* argv[]) {

   //Formatting and storing the arguments
   for(int i = 1; i<argc; i+=2) {
     if(strcmp(argv[i], "-p") == 0) no_of_producers = atoi(argv[i+1]);
     else if(strcmp(argv[i], "-pc") == 0) max_production_capacity = atoi(argv[i+1]);
     else if(strcmp(argv[i], "-c") == 0) no_of_consumers = atoi(argv[i+1]);
     else if(strcmp(argv[i], "-cc") == 0) max_consumer_capacity = atoi(argv[i+1]);
     else {
      printf("Invalid Arguments\n");
      return 1;
     }
   }

   //for producers  

   capacity_of_production = (int *) malloc(no_of_producers*sizeof(int));

   for(int i = 0; i<no_of_producers; i++) capacity_of_production[i] = max_production_capacity;

   //for consumers

   capacity_of_consumption = (int *) malloc(no_of_consumers*sizeof(int));

   for(int i = 0; i<no_of_consumers; i++) capacity_of_consumption[i] = max_consumer_capacity;


   //initializing semaphore for the stack 
   sem_init(&is_stack_available, 0, 1);


   //starting producers threads
   pthread_t producer_tid[no_of_producers];
   //starting consumer threads
   pthread_t consumer_tid[no_of_consumers];

   for(int j = 0; j<no_of_consumers; j++) {
      pthread_create(&consumer_tid[j], NULL, consume_product, j);
   }

   sleep(5);

   for(int i = 0; i<no_of_producers; i++) {
      pthread_create(&producer_tid[i], NULL, produce_product, i);   
   }


   //waiting for all the processes to complete execution
   for(int k = 0; k<no_of_producers; k++) {
      pthread_join(producer_tid[k], NULL);
   }

   for(int k = 0; k<no_of_consumers; k++) {
      pthread_join(consumer_tid[k], NULL);
   }

   return 0;
}
