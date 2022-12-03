#include <stdbool.h>
#include <stdio.h>
#include <math.h>

float average(int num[], size_t size){
    int sum = 0;
    float avg;
    for(int i=0;i<size;i++){
        sum += num[i];
    }
    avg = sum/size;   
    
    return avg;
}

bool isPrime(int num){
    bool flag = true;
    for (int i = 2; i <= sqrt(num); i++) {
  
        // If n is divisible by any number between
        // 2 and n/2, it is not prime
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void print_prime(int num[], size_t size){
    for(int i=0;i<size;i++){
        if (isPrime(num[i])) printf("%d\n", num[i]);
    }
}
