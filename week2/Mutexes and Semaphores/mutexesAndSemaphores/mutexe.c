#include <stdio.h>
#include <pthread.h>

int counter = 0; 
pthread_mutex_t semaphore; 

void*increment_counter(void*arg)
{
    int i; 
    for(i=0; i < 10000; i++)
    {
        pthread_mutex_lock(&semaphore);
        counter = counter +1; 
        pthread_mutex_unlock(&semaphore); 
    }
    return NULL;
}

int main()
{
     pthread_t t1, t2;

    pthread_mutex_init(&semaphore, NULL);

    pthread_create(&t1, NULL, increment_counter, NULL);
    pthread_create(&t2, NULL, increment_counter, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter value: %d\n", counter);

    pthread_mutex_destroy(&semaphore);

    return 0;
}