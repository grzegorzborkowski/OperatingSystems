#include "lib.h"

int counter = 0;

int main(int argc, char** argv) {
    int i, wait_result, N;
    tms_t tms_start, tms_end, tms_child;
    clock_t start, end, child_start, child_end;
    double children_real;
    pid_t pid;

    start = times(&tms_start);

    if (argc !=2) {
        printf("Unsupported number of arguments \n");
        exit(1);
    }

    N = atoi(argv[1]);
    for(i=0; i<N; i++) {
        child_start = times(&tms_child);
        pid = vfork();
       /* child process */
        if(pid == 0) {
            counter += 1;
            _exit(0);
            /* parent process */
        } else if(pid > 0) {
            wait_result = wait(NULL); /* suspends execution until child process terminates */
            if(wait_result == -1) {
                printf("Error on return wait function \n");
                exit(1);
            }
            child_end = times(&tms_child);
            children_real += (child_end - child_start) / (double)(sysconf(_SC_CLK_TCK));

        } else {
            printf("Error when creating new process\n");
            exit(1);
        }
    }
    printf("Counter: %d\n", counter);

    end = times(&tms_end);
    print_times(end-start, &tms_start, &tms_end);
    printf("Children real time %f\n", children_real);

    return 0;
}
