#include "lib.h"
#define STACK_SIZE (1024 * 1024)

int counter = 0;

int process_function(void *arg) {
    counter += 1;
    _exit(0);
    return 0;
}

int main(int argc, char **argv) {
    char *stack; /* Start of stack buffer */
    char *stackTop; /* End of stack buffer */
    tms_t tms_start, tms_end, tms_child;
    clock_t start, end, child_start, child_end;
    double children_real;
    int N, i, status;
    pid_t pid, wait_pid;

    start = times(&tms_start);

    if (argc !=2) {
            printf("Unsupported number of arguments \n");
            exit(1);
    }

    /* Allocate stack for child */
    stack = malloc(STACK_SIZE);
    if(stack == NULL) {
        printf("Error in malloc function \n");
        exit(1);
    }
    stackTop = stack + STACK_SIZE; /* Assume stack grows downward */

    N = atoi(argv[1]);
    for(i=0; i<N; i++) {
        child_start = times(&tms_child);
        /* FLAGS specifies termination signal sent to parent when the child dies
        OR what is shared between the calling process and the child process */
        /* CLONE_VM : processes share memory space */
        /* CLONE_VFORK : firstly child process, then parent process */
        /* SIGCHLD : signal sent when child terminates */
        pid = clone(process_function, stackTop, CLONE_VM | CLONE_VFORK | SIGCHLD, NULL);
        if(pid == -1) {
            printf("Error in clone function \n");
            exit(1);
        }

        /* pid, status, options */
        wait_pid = waitpid(pid, &status, 0);
        if (wait_pid == -1) {
            printf("Error in wait pid function \n");
            exit(1);
        }
        child_end = times(&tms_child);
        children_real += (child_end - child_start) / (double)(sysconf(_SC_CLK_TCK));
    }
    printf("Counter %d\n", counter);
    end = times(&tms_end);
    print_times(end-start, &tms_start, &tms_end);
    printf("Children real time %f\n", children_real);
    free(stack);
    return 0;
}