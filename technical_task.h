#ifndef TECHNICAL_TASK_H
#define TECHNICAL_TASK_H
#include <stdio.h>

typedef struct data{
    int* arr;
    int size;
} data;

void* threadAvg(void *arg);

// float average(int num[]);

// int isPrime(int num);

// void print_prime(int num[]);

#endif