
#ifndef XV6_PTHREAD
#define XV6_PTHREAD

// Define all functions and types for pthreads here.
// This can be included in both kernel and user code.

struct pthread_attr_t{

};
typedef struct pthread_attr_t pthread_attr_t;

struct pthread_t {
	void* stack;
	int pid;
	void * func;
	int isThread;
	void * arg;
};
typedef struct pthread_t pthread_t;

struct pthread_mutex {
  int id;
};


typedef struct pthread_mutex pthread_mutex_t;

struct pthread_mutexattr {
 
};
typedef struct pthread_mutexattr pthread_mutexattr_t;



int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

int pthread_join(pthread_t thread, void **retval);

int pthread_exit(void *retval);
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

#endif
