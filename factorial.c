#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables to store results
float power_result;
int fact;

// Function prototypes
void *thread_factorial(void *var);
void *thread_power(void *var);

int main()
{
    // Declaring the threads
    pthread_t thread1, thread2;

    // Creating the threads
    pthread_create(&thread1, NULL, thread_power, NULL);
    pthread_create(&thread2, NULL, thread_factorial, NULL);

    // Joining the threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Printing the results
    printf("The base and power result is %f\n", power_result);
    printf("The factorial result is %d\n", fact);

    return 0;
}

void *thread_factorial(void *var)
{
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

    pthread_exit(0);
}

void *thread_power(void *var)
{
    // Function to take input from the user and calculate the power
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

    pthread_exit(0);
}
