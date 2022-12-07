#ifndef TIMER_H
#define TIMER_H
#include <stdio.h>
#include <time.h>

timer_t createTimer(int signal);

void runTimer(timer_t timer, int sec);

#endif