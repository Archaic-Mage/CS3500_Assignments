/*
    Author: Soham Tripathy CS20B073
    CS3500: Assignment
    Topic: MultiThreading (shared memory - semaphores and mutex locks)

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>


int no_of_philosophers;
int done;

//keeps track of the time passed
int time_elapsed = 0;

// semaphore 
// 1 -> chopstick available
// 0 -> chopstick being used by some philosopher
sem_t *is_chopstick_available;

// keeping track of the time each philosopher ate
int* eat_count;


//for getting time to think
int getRandNum() {
    return (rand()%51 + 50);            //rand()%50 will give numbers from 0-50; adding 50 will give numbers in range 50-100
}


void eat(int index)
{
    printf("<%d> Philosopher %d in EATING state - %d\n", time_elapsed, index, eat_count[index]);
    fflush(stdout);
    time_elapsed+=100;
}

// Philosopher's execution 
void* philosopher_exe(void* index) {
    int which_philosopher = (int)index;

    int time_to_think = getRandNum();
    int start = time_elapsed;
    
    //philosopher thinks
    printf("<%d> Philosopher %d in THINKING state\n", start, which_philosopher);
    fflush(stdout); 

    if(eat_count[which_philosopher] == 5) return;

    while(time_elapsed-start < time_to_think);


    sem_wait(&is_chopstick_available[which_philosopher]);
    sem_wait(&is_chopstick_available[(which_philosopher + 1) % no_of_philosophers]);

    eat_count[which_philosopher]++;
    eat(which_philosopher);

    sem_post(&is_chopstick_available[(which_philosopher + 1) % no_of_philosophers]);
    sem_post(&is_chopstick_available[which_philosopher]);

    if (eat_count[which_philosopher] == 5)
        done--;

    philosopher_exe(index);
}

void* increase_time(void* args) {
    while(done) {
        sleep(0.001);
        time_elapsed++;
    }
}

int main()
{

    //getting the number of philosophers
    printf("Please Enter the number of Philosophers:> ");
    scanf("%d", &no_of_philosophers);

    done = no_of_philosophers;              //initializing the wether the execution is done or not

    //creating threads using pthread for each philosopher
    pthread_t t_id[no_of_philosophers];

    //time thread
    pthread_t time_tid;

    // creating the array to store number of times philosopher ate
    eat_count = (int *) malloc(no_of_philosophers * sizeof(int));

    //initializing the eat_count to zero for each philosopher
    for(int i = 0; i < no_of_philosophers; i++) eat_count[i] = 0;

    // creating the array to store the semaphor values - for each chopstick
    is_chopstick_available = (sem_t *)malloc(no_of_philosophers * sizeof(sem_t));

    //initializing the semaphor to 1 -> all chopsticks are available
    for (int i = 0; i < no_of_philosophers; i++) 
        sem_init(&is_chopstick_available[i], 0, 1);

    //creating the philosopher thread and calling the execution function in them
    for (int i = 0; i < no_of_philosophers; i++)
        pthread_create(&t_id[i], NULL, philosopher_exe, i);

    pthread_create(&time_tid, NULL, increase_time, NULL);

    //waiting for each thread to complete its execution
    for (int i = 0; i < no_of_philosophers; i++)
        pthread_join(t_id[i], NULL);

    pthread_join(time_tid, NULL);

    return 0;
}

