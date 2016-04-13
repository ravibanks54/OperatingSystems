#ifndef XV6_PTHREAD
#define XV6_PTHREAD

// Define all functions and types for pthreads here.
// This can be included in both kernel and user code.

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_exit(void *retval);

typedef unsigned long int pthread_t; 
typedef unsigned long int pthread_attr_t;
#endif
