#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

sem_t semaphore;

struct thread_data {
    int thread_id;
    char *message;
};

void * thread(void * arg)
{
    // WE NEED TO LOCK THE MUTEX HERE
    sem_wait(&semaphore);
    struct thread_data *td = (struct thread_data *)arg;

    printf("Ounce %d is in the filter\n", td->thread_id);
    
    printf("%s\n", td->message);

    sleep(1);
    
    printf("Ounce %d is dripping into carafe\n\n", td->thread_id);
    td->message = "Dispensed coffee";
    // WE NEED TO UNLOCK THE MUTEX HERE
    sem_post(&semaphore);
    return (void *)td;
}

int main(void)
{    
    // WE NEED TO INITIALIZE THE MUTEX HERE
    sem_init(&semaphore, 0, 1);
    pthread_t brewing;

    // WE NEED TO CREATE THE THREADS HERE
    struct thread_data carafe;

    for (int i = 0; i < 12; i++)
    {
        carafe.thread_id = i + 1;
        carafe.message = "Brewing coffee";
        pthread_create(&brewing, NULL, thread, (void*)(&carafe));
        // WE NEED TO JOIN THE THREADS HERE
        pthread_join(brewing, (void *)(&carafe));
        
        printf("Ounce %d: %s\n\n", i + 1, carafe.message);
    }
    // WE NEED TO DESTROY THE MUTEX HERE
    sem_destroy(&semaphore);

    return EXIT_SUCCESS;
}
