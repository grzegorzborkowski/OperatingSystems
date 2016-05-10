#include "philosophers.h"

sem_t waiter;
pthread_t philosophers[PHILO_COUNT];
pthread_mutex_t forks_mutex[PHILO_COUNT];
pthread_mutexattr_t mutexattr;


int func_output;

void print_errno_quit(const char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void take_fork(int fork_id) {
    func_output = pthread_mutex_lock(&forks_mutex[fork_id]);
    if(func_output < 0) {
        print_errno_quit("Error while locking the fork mutex");
    }
}

void putdown_fork(int fork_id) {
    func_output = pthread_mutex_unlock(&forks_mutex[fork_id]);
    if(func_output < 0) {
        print_errno_quit("Error while unlocking the fork mutex");
    }
}

void *philosopher_thread(void * arg) {
        int philosopher_id = (intptr_t)(arg);
        int second_fork_number = (philosopher_id+1)%PHILO_COUNT;
        for(;;) {
                printf("Philosopher %d is thinking\n", philosopher_id);
                usleep(rand() % THIKING_TIME);
                printf("Philosopher %d is waiting for forks \n", philosopher_id);
                sem_wait(&waiter);
                take_fork(philosopher_id);
                take_fork(second_fork_number);
                printf("Philosopher nr %d is eating\n", philosopher_id);
                usleep(rand() % EATING_TIME);
                putdown_fork(philosopher_id);
                putdown_fork(second_fork_number);
                sem_post(&waiter);
                printf("Philosopher nr %d finished eating\n", philosopher_id);
    }
    return NULL;
}

void sighandler(int signum)
{
    int i;
    printf("Caught signal, coming out...\n");

    for(i=0; i<PHILO_COUNT; i+=1) {
        func_output = pthread_cancel(philosophers[i]);
        if(func_output < 0) {
            print_errno_quit("Error in canceling the thread");
        }
    }

    func_output = pthread_mutexattr_destroy(&mutexattr);
    if(func_output < 0) {
        print_errno_quit("Error while destroying the mutex attribute structure");
    }

    for(i=0; i<PHILO_COUNT; i+=1) {
        func_output = pthread_mutex_destroy(&forks_mutex[i]);
        if(func_output < 0) {
            print_errno_quit("Error while destroying fork mutex");
        }
    }

    func_output = sem_destroy(&waiter);
    if(func_output < 0) {
        print_errno_quit("Error while destroying the waiter semaphore");
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    int i;

    signal(SIGINT, sighandler);
    /* init variables */

    /* second argument(0): pshared (the semaphore is shared between threads */
    func_output = sem_init(&waiter, 0, WAITER_INITIAL_VALUE);
    if(func_output < 0) {
        print_errno_quit("Error while initialising the waiter semaphore");
    }

    func_output = pthread_mutexattr_init(&mutexattr);
    if(func_output < 0) {
        print_errno_quit("Error while initialising the mutex attribute structure");
    }

    for(i=0; i<PHILO_COUNT; i+=1) {
        func_output = pthread_mutex_init(&forks_mutex[i], &mutexattr);
        if(func_output < 0) {
            print_errno_quit("Error while initing the fork mutex");
        }
    }

    for(i=0; i<PHILO_COUNT; i+=1) {
        func_output = pthread_create(&philosophers[i], NULL, &philosopher_thread, (void *) (intptr_t)i);
        if(func_output < 0) {
            print_errno_quit("Error when creating philosophers threads");
        }
    }

    while(1) {

    }

    return 0;
}