#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "pthread.h"



int 
pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
  thread->stack = (void *)malloc(4096);
  thread->isThread = 1;
  thread->func = (void*)(* start_routine);
  thread->arg = arg;
  thread->pid = clone(thread->func, thread->arg, thread->stack);
  return thread->pid;  
}


int 
pthread_join(pthread_t thread, void **retval)
{
int ret = join(thread.pid, (void **)thread.stack, retval);
free(thread.stack);
return ret;
}



int 
pthread_exit(void *retval)
{
	texit(retval);
	return 0;
}
