#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64 freepmem(void);

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;
  int new_size;

  if(argint(0, &n) < 0){
    return -1;
  }
  addr = myproc()->sz;
  new_size = addr + n;
  
  if(new_size < TRAPFRAME){
  	myproc() -> sz = new_size;
  	return addr;
  }
  
  return -1;
}

uint64
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

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the number of active processes in the system
// fill in user-provided data structure with pid,state,sz,ppid,name
uint64
sys_getprocs(void)
{
  uint64 addr;  // user pointer to struct pstat
  //struct proc *p;  //create a pointer to struct proc
  
  //checks if address of first argument (index 0) passed to system call and be retrieved
  //by argaddr function
  if (argaddr(0, &addr) < 0){
    return -1;
  }
  
  return(procinfo(addr));
}

// sys_wait2
uint64
sys_wait2(void)
{
  uint64 p;
  uint64 p2;
  
  if(argaddr(0, &p) < 0){
    return -1;
  }
  
  if(argaddr(1, &p2) < 0){
    return -1;
  }
  
  return wait2(p, p2);
  
}

// sys_getprocs
uint64
sys_getpriority(void){
	return myproc()->priority;
}

// sys_setprocs
uint64
sys_setpriority(void){
	int priority;
	if(argint(0, &priority) < 0){
		return -1;
	}
	//if(priority->MAXEFPRIORITY){
	//	return -1;
	//}
	
	myproc()->priority = priority;
	return 0;
}

uint64
sys_freepmem(void)
{
	int res = freepmem();
	return res;
}

uint64
sys_memuser(void)
{
	int res = freepmem();
	return res;
}
