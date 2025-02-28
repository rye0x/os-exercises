#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

float power_result;
int fact;

// Add a semaphore to control the sequence
sem_t input_sem;

// Function prototypes
void *thread_factorial(void *var);
void *thread_power(void *var);

int main()
{
    // Initialize the semaphore
    sem_init(&input_sem, 0, 1);

    // declaring the threads
    pthread_t thread1, thread2;

    // creating the threads
    pthread_create(&thread1, NULL, thread_power, NULL);
    pthread_create(&thread2, NULL, thread_factorial, NULL);

    // joining the threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&input_sem);

    // printing the results
    printf("The base and power is %f\n", power_result);
    printf("The factorial is %d\n", fact);

    return 0;
}

void *thread_factorial(void *var)
{
    // Wait for the power thread to complete input
    sem_wait(&input_sem);

    // Function to take input from the user and calculate the factorial
    int count;
    printf("Enter the number you want to calculate the factorial: ");
    scanf("%d", &count);
    int factorial = 1;
    for (int i = 1; i <= count; i++)
    {
        factorial *= i;
    }
    fact = factorial;

    // Release the semaphore
    sem_post(&input_sem);

    sleep(1);
    pthread_exit(0);
}

void *thread_power(void *var)
{
    // Wait for our turn to get input
    sem_wait(&input_sem);

    // function to take input from the user and calculate the power
    int base, power;
    printf("Enter the base: ");
    scanf("%d", &base);
    printf("Enter the power: ");
    scanf("%d", &power);

    // Formula to calculate the power
    float result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= base;
    }
    power_result = result;

    // Release the semaphore so the factorial thread can proceed
    sem_post(&input_sem);

    sleep(1);
    pthread_exit(0);
}
