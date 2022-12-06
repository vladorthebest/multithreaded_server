#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "technical_task.h"

void * threadAvg(void *arg)
{   
    data* ptr = (data*)arg;
    int size = ptr->size;
    printf("Size: %d\n", size);
    int sum = 0;
    for(int i=0;i<size;i++){
        sum += ptr->arr[i];
    }
    float avg = sum/size;
    float* result = malloc(sizeof(float));
    *result = avg;
    // printf("Avg: %f", avg);
    return (void *) result;
}

// float average(int num[], size_t size){
//     int sum = 0;
//     float avg;
//     for(int i=0;i<size;i++){
//         sum += *num[i];
//     }
//     avg = sum/size;   
    
//     return avg;
// }

// int isPrime(int num){
//     for (int i = 2; i <= sqrt(num); i++) {
  
//         // If n is divisible by any number between
//         // 2 and n/2, it is not prime
//         if (num % i == 0) {
//             return 0;
//         }
//     }
//     return 1;
// }

// void print_prime(int num[], size_t size){
//     for(int i=0;i<size;i++){
//         if (isPrime(num[i])) printf("%d\n", num[i]);
//     }
// }
