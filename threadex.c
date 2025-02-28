#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototype
// void *myVar is a pointer to a void type while *myFunc is a pointer to a function
// void *myFunc(void *myVar) is a function that takes a pointer to a void type and returns a pointer to a void type
void *myFunc(void *myVar);

int main()
{
    pthread_t thread1, thread2;
    char *msg1 = "First Thread";
    char *msg2 = "Second Thread";

    // Storing the return value of the thread
    int ret1, ret2;

    // Creating the threads
    // pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    ret1 = pthread_create(&thread1, NULL, myFunc, (void *)msg1);
    ret2 = pthread_create(&thread2, NULL, myFunc, (void *)msg2);

    printf("Currently in the main thread function\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("First thread returns: %d\n", ret1);
    printf("Second thread returns: %d\n", ret2);
    return 0;
}

void *myFunc(void *myVar)
{
    // Casting the void pointer to a char pointer
    char *msg;
    msg = (char *)myVar;
    int i;
    for (i = 0; i <= 10; i++)
    {
        printf("%s %d\n", msg, i);
        sleep(1);
    }
    pthread_exit(0);
}
