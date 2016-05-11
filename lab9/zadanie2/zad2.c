#include "zad2.h"

pthread_cond_t start_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t land_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t run_way = PTHREAD_MUTEX_INITIALIZER;
pthread_t planes[PLANE_COUNT];

int resting_planes = PLANE_COUNT;
int planes_to_land = 0;
int planes_to_start = 0;
int func_output;

void print_errno_quit(const char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void start(int plane_id) {
    func_output = pthread_mutex_lock(&run_way);
    if(func_output < 0) {
        print_errno_quit("Error while locking run_way mutex in start function");
    }
    planes_to_start += 1;
    while(resting_planes < LANDING_PRIORITY && planes_to_land != 0) {
        func_output = pthread_cond_wait(&start_cond, &run_way);
        if(func_output < 0) {
            print_errno_quit("Error in pthread_cond_wait function in start func");
        }
    }

    planes_to_start -= 1;
    resting_planes -= 1;
    printf("Plane id %d has just STARTED. There are %d planes waiting on the ship \n", plane_id, resting_planes);

    func_output = pthread_cond_signal(&land_cond);
    if(func_output < 0) {
        print_errno_quit("Error in pthread_cond_signal function with land_cond argument from start func.");
    }

    func_output = pthread_mutex_unlock(&run_way);
    if (func_output < 0) {
        print_errno_quit("Error while unlocking the run_way mutex in start function");
    }
}

void fly() {
    usleep(rand()%FLYING_TIME);
}

void land(int plane_id) {
    func_output = pthread_mutex_lock(&run_way);
    if(func_output < 0) {
        print_errno_quit("Error while locking run_way mutex in land function");
    }

    planes_to_land += 1;
    while(resting_planes >= LANDING_PRIORITY && planes_to_start != 0) {
        pthread_cond_wait(&land_cond, &run_way);
    }

    planes_to_land -= 1;
    resting_planes += 1;
    printf("Plane id %d has just LANDED. There are %d planes waiting on the ship\n", plane_id, resting_planes);

    func_output = pthread_cond_signal(&start_cond);
    if(func_output < 0) {
        print_errno_quit("Error in pthread_cond_signal function with start_cond argument from land func");
    }

    func_output = pthread_mutex_unlock(&run_way);
    if(func_output < 0) {
            print_errno_quit("Error while unlocking the run_way mutex in land function");
    }
}

void rest() {
    usleep(rand()%RESTING_TIME);
}
void *plane_actions(void *arg) {
    int plane_id = (intptr_t)(arg);
    for(;;) {
        start(plane_id);
        fly();
        land(plane_id);
        rest();
    }
    return NULL;
}

void sighandler(int signum)
{
    int i;
    printf("Caught signal, coming out...\n");

    for(i=0; i<PLANE_COUNT; i+=1) {
        func_output = pthread_cancel(planes[i]);
        if(func_output < 0) {
            print_errno_quit("Error while canceling the plane threads");
        }
    }

    pthread_cond_destroy(&start_cond);
    pthread_cond_destroy(&land_cond);
    pthread_mutex_destroy(&run_way);

    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int i;

    for(i=0; i<PLANE_COUNT; i+=1) {
        pthread_create(&planes[i], NULL, &plane_actions, (void *) (intptr_t)i);
    }

    signal(SIGINT, sighandler);

    while(1) {

    }

    return 0;
}