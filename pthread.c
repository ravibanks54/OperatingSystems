#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "pthread.h"

// Implement your pthreads library here.


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


int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr){
	int mutexid = mutex_init();
	printf(1,"Mutexid: %d\n", mutexid);
	return mutex->id = mutexid; 
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
	return mutex_destroy(mutex->id);
}

int pthread_mutex_lock(pthread_mutex_t *mutex){
	return mutex_lock(mutex->id);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
	return mutex_unlock(mutex->id);
}


