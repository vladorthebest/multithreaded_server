#ifndef TECHNICAL_TASK_H
#define TECHNICAL_TASK_H
#include <stdio.h>

typedef struct data{
    int* arr;
    int size;
} data;

void* threadAvg(void *arg);

void * threadisPrime(void * arg);


#endif