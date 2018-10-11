// Create a zombie process that
// must be reparented at exit.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "stdlib.h"
int
main(void)
{
  if(fork() > 0)
    sleep(5);  // Let child exit before parent.
  exit(EXIT_SUCCESS);
}
