#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>


timer_t createTimer(int signal)
{
  struct sigevent timerEvent;
  timerEvent.sigev_notify=SIGEV_SIGNAL;
  timerEvent.sigev_signo=signal;

  timer_t timer;
  timer_create(CLOCK_REALTIME, &timerEvent, &timer);
  return(timer); 
}

void runTimer(timer_t timer, int sec)
{
  struct itimerspec timerTime;
  timerTime.it_value.tv_sec=sec;
  timerTime.it_value.tv_nsec=0;
  timerTime.it_interval.tv_sec=0;
  timerTime.it_interval.tv_nsec=0;
  timer_settime(timer,CLOCK_REALTIME,&timerTime,NULL);
}
