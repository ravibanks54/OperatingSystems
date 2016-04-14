#include "types.h"
#include "mmu.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "fs.h"
#include "proc.h"
#include "x86.h"

/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
	void* stack = malloc(4096);
	if (clone(start_routine, arg, stack) == 0){
		return 0;
	}else{
		return -1;
	}
}

int pthread_join(pthread_t thread, void **retval){
	// free up stack	
	return join();
}

int pthread_exit(void *retval){
	return texit(retval);
}

*/


int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr){
	int mutexid = mutex_init();
	mutex->id = mutexid; 
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
	return mutex_init(mutex->id);
}

int pthread_mutex_lock(pthread_mutex_t *mutex){
	return mutex_init(mutex->id);
}
int pthread_mutex_unlock(pthread_mutex_t *mutex){
	return mutex_init(mutex->id);
}
