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

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
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

// Halt (shutdown) the system by sending a special
// signal to QEMU.
// Based on: http://pdos.csail.mit.edu/6.828/2012/homework/xv6-syscall.html
// and: https://github.com/t3rm1n4l/pintos/blob/master/devices/shutdown.c
int
sys_halt(void)
{
  char *p = "Shutdown";
  for( ; *p; p++)
    outw(0xB004, 0x2000);
  return 0;
}

int
sys_clone(void)
{
	int func, arg, stack;
	//error checking
	if(argint(0, &func)<0){
		return -1;
	}
	if(argint(1, &arg)<0){
		return -1;
	}
	if(argint(2, &stack)<0){
		return -1;
	}

	return clone((void*)func, (void*)arg, (void*)stack);
	//return 0;
	
}
int
sys_join(void)
{
	int pid;
	int joinstack, retval;
	if(argint(0, &pid)<0){
		return -1;
	}
	if(argint(1, &joinstack)<0){
		return -1;
	}
	if(argint(2, &retval)<0){
		return -1;
	}

	return join(pid, (void**)joinstack, (void**)retval);
	//return 0; 
}

int
sys_texit(void)
{ 

	int rVal;
	argint(0, &rVal); 
	proc->retval = (void*)rVal;
	//int rPrint = *(int*)(proc->retval); // previously proc->retval was a void**
	//cprintf(" retval: %d, rVal: %d\n",rPrint, rVal);
	exit();
	return 0;
}
int
sys_mutex_init(void)
{
	void* threadptr;
	argint(0, &threadptr);
	if (proc->mutexCount > 31 || proc->mutexCount < 0){
		//max number of mutexes or invalid
		return -1;
	}
	
	initlock(&proc->mTable[mutexCount].lock, "mutex");
	
	proc->mTable[mutexCount].id = mutexCount;
	
	proc->mTable[mutexCount].isLocked = 0;  //Set to active/unlocked initially
	proc->mTable[mutexCount].isActive = 1;	
	
	threadptr = &proc->mTable[mutexCount];
	
	proc->mutexCount++;
	return proc->mutexCount-1;	//Return the correct id after incrementing
}

int
sys_mutex_destroy(void)
{
	void* threadptr;
	argint(0, &threadptr);
	return mutex_destroy((pthread_mutex_t*)threadptr->id);
}

int
sys_mutex_lock(void)
{
	void* threadptr;
	argint(0, &threadptr);
	return mutex_lock((void*)threadptr->id);
}

int sys_mutex_unlock(void)
{
	int threadptr;
	argint(0, &threadptr);
	return mutex_lock((void*)threadptr->id);
}

