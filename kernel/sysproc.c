#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

uint64
sys_exit(void)
{
  int n;

  argint(0, &n);
  kexit(n);

  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;

  argaddr(0, &p);

  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  // Get arguments:
  // n = number of bytes requested
  // t = allocation type (eager or lazy)
  argint(0, &n);
  argint(1, &t);

  struct proc *p = myproc();

  // Save current process size.
  // This is the address returned to the user.
  addr = p->sz;

  // ------------------------------------------------------------
  // EAGER ALLOCATION
  // ------------------------------------------------------------
  //
  // In eager allocation, physical memory is allocated immediately
  // using growproc().
  //
  // Also, when shrinking memory (n < 0), pages must be unmapped
  // and freed immediately.
  //
  if(t == SBRK_EAGER || n < 0) {

    if(growproc(n) < 0) {
      return -1;
    }

  } else {

    // ------------------------------------------------------------
    // LAZY ALLOCATION
    // ------------------------------------------------------------
    //
    // Instead of allocating physical pages now, we only increase
    // the virtual address space size of the process.
    //
    // Actual memory allocation will happen later when the process
    // accesses the page and triggers a page fault.
    //

    // Prevent address overflow.
    if(addr + n < addr) {
      return -1;
    }

    // Increase process size WITHOUT allocating pages.
    p->sz += n;
  }

  // Return previous process size.
  // This is the start of newly allocated memory region.
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);

  if(n < 0)
    n = 0;

  acquire(&tickslock);

  ticks0 = ticks;

  while(ticks - ticks0 < n) {

    if(killed(myproc())) {
      release(&tickslock);
      return -1;
    }

  }

  release(&tickslock);

  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);

  return kkill(pid);
}

// Return how many clock tick interrupts have occurred
// since system startup.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);

  return xticks;
}
