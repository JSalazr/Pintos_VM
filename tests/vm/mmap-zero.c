/* Tries to map a zero-length file, which may or may not work but
   should not terminate the process or crash.
   Then dereferences the address that we tried to map,
   and the process must be terminated with -1 exit code. */

#include <syscall.h>
#include <stdio.h>
#include "tests/lib.h"
#include "tests/main.h"

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
  char *data = (char *) 0x7f000000;
  int handle;

  CHECK (create ("empty", 0), "create empty file \"empty\"");
  CHECK ((handle = open ("empty")) > 1, "open \"empty\"");

  /* Calling mmap() might succeed or fail.  We don't care. */
  msg ("mmap \"empty\"");
  mmap (handle, data);

  /* Regardless of whether the call worked, *data should cause
     the process to be terminated. */
  fail ("unmapped memory is readable (%d)", *data);

struct mini_thread mt[3];
  pid_t idk1, idk2, idk3;

  idk1 = exec("page-merge-mm");
  idk2 = exec("page-merge-stk");
  idk3 = exec("page-merge-par");

  int val;
  mt[0].tid = idk1;
  val = test(&mt[0]);
  mt[1].tid = idk2;
  val = test(&mt[1]);
  mt[2].tid = idk3;
  val = test(&mt[2]);

  while(mt[0].priority != 0 || mt[1].priority != 0 || mt[2].priority != 0 || mt[3].priority != 0){    
    if(mt[0].priority != 0)
      printf("PID %d, Priority %d, Cant Run, %d, Cant Sleep %d, Cant Page Faults %d\n", mt[0].tid, mt[0].priority, mt[0].cant_run, mt[0].cant_sleep, mt[0].cant_page_faults);
    
    if(mt[1].priority != 0)
      printf("PID %d, Priority %d, Cant Run, %d, Cant Sleep %d, Cant Page Faults %d\n", mt[1].tid, mt[1].priority, mt[1].cant_run, mt[1].cant_sleep, mt[1].cant_page_faults);

    if(mt[2].priority != 0)
      printf("PID %d, Priority %d, Cant Run, %d, Cant Sleep %d, Cant Page Faults %d\n", mt[2].tid, mt[2].priority, mt[2].cant_run, mt[2].cant_sleep, mt[2].cant_page_faults);
    
    val = test(&mt[0]);
    val = test(&mt[1]);
    val = test(&mt[2]);
  }

  return EXIT_SUCCESS;
}

