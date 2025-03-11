#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// This program ask a user to enter the number of threads to create
// Then it creates the threads and join them
// Decleration of the function that will execute by each thread
void *threadexer1(void *var);

int main()
{
    int count;
    printf("Enter the number of threads you want to create: ");
    scanf("%d", &count);

    // Array of threads
    pthread_t threadIDs[count];

    // Creating the threads
    for (int i = 0; i < count; i++)
    {
        pthread_create(&threadIDs[i], NULL, threadexer1, (void *)&i);
        printf("Successfully created thread: %d\n", i);
    }
    // Joining the threads
    for (int i = 0; i < count; i++)
    {
        pthread_join(threadIDs[i], NULL);
        printf("Successfully joined thread: %d\n", i);
    }

    return 0;
}
void *threadexer1(void *var)
{
    // We want to confirm if the thread is running
    int *threadnum;
    threadnum = (int *)var;
    printf("Thread %d is running\n", *threadnum);
    sleep(1);
    pthread_exit(0);
}
