#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "technical_task.h"

void * threadAvg(void *arg)
{   
    data* ptr = (data*)arg;
    int size = ptr->size;

    int sum = 0;
    for(int i=0;i<size;i++){
        sum += ptr->arr[i];
    }
    float avg = sum/size;
    float* result = malloc(sizeof(float));
    *result = avg;

    return (void *) result;
}

void * threadisPrime(void * arg){
    int num = *(int*)arg;
    int* result = malloc(sizeof(int));
    *result = 1;
    for (int i = 2; i <= sqrt(num); i++) {
  
        // If n is divisible by any number between
        // 2 and n/2, it is not prime
        if (num % i == 0) {
            *result = 0;
        }
    }
    
    return (void *) result;
}

