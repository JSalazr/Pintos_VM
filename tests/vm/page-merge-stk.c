#include "tests/main.h"
#include "tests/vm/parallel-merge.h"
#include <stdio.h>
#include <syscall.h>

struct mini_thread{
  pid_t tid;
  int cant_sleep;
  int cant_run;
  int priority;	
  int cant_page_faults;
};

void
test_main (void) 
{
  parallel_merge ("child-qsort", 72);
struct mini_thread mt;
mt.tid = 3;
int val = test(&mt);
printf("PID %d, Cant Page Faults %d\n", mt.tid, mt.cant_page_faults);
}
