#include <stdio.h>

float average(int num[], size_t size){
    int sum = 0;
    float avg;
    for(int i=0;i<size;i++){
        sum += num[i];
    }
    avg = sum/size;   
    
    return avg;
}

int main() {
    int num[] = {2, 4, 2, 4};
    size_t size = sizeof(num)/sizeof(int);
    printf("%.3f", average(num, size));
    return 0;
}