#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define max 5

pthread_mutex_t forks[max];

void *philosopher(void *num)
{
    int id = *(int *)num;
    int left = id;
    int right = (id + 1) % max;

    for (int i = 0; i < 3; i++)
    {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);
        // Pick up forks (to prevent deadlock, pick lower-numbered fork first)
        if (id % 2 == 0)
        {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        }
        else
        {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }
        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        // Put down forks
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);

        printf("Philosopher %d finished eating.\n", id);
    }
    return NULL;
}

int main()
{
    pthread_t philosophers[max];
    int ids[max];
    // Initialize mutexes
    for (int i = 0; i < max; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }
    // Create philosopher threads
    for (int i = 0; i < max; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    // Wait for all philosophers to finish
    for (int i = 0; i < max; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
    // Destroy mutexes
    for (int i = 0; i < max; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}