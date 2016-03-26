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
    int N, i, status;
    pid_t pid, wait_pid;

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
        /* FLAGS specifies termination signal sent to parent when the child dies
        OR what is shared between the calling process and the child process */
        pid = clone(process_function, stackTop, SIGCHLD, NULL);
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
    }
    printf("Counter %d\n", counter);
    free(stack);
    return 0;
}