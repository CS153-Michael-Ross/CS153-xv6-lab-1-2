#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

//Should this take a parameter?
int
sys_exit(int status)
{
  argint(0, &status);
  exit(status);
  return 0;  // not reached
}

int
sys_wait(int *status)
{
  argptr(0, (char**)&status, sizeof(int*));
  return wait(status);
}

int
sys_waitpid(int pid, int *status, int options)
{
  argint(0, &pid);
  argptr(1, (char**)&status, sizeof(int*));
  argint(2, &options);
  return waitpid(pid, status, options);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// set the priority of the current process. We're assuming
// this will never fail so always return 0.
int
sys_setpriority(int priority)
{
  setpriority(priority);
  return 0;
}
