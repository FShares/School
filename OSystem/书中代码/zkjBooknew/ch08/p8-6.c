#include "ch08.h"
volatile int gotit = 0;
void alarm_handler(int signal)
{
    gotit = 1;
    puts("catch alarm");
}
int main(int argc, char ** argv)
{
  clock_t  start, stop;
  struct tms buffer;
  signal(SIGALRM, alarm_handler);  /* 设置信号句柄 */
  start = times(&buffer);
  alarm(1);
  while (!gotit);                  /* 等待定时器到时 */
  stop = times(&buffer);
  printf("%ld clock ticks per second (start=%ld, stop=%ld)\n",
	  stop-start, start, stop);
  printf("sysconf(_SC_CLK_TCK)=%ld\n", sysconf(_SC_CLK_TCK));
  return 0;
}
