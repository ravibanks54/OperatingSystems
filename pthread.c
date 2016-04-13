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
