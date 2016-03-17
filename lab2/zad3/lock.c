#include "lock.h"

void set_write_lock(int open_descriptor, off_t offset) {
    struct flock flock1;
    int fcntl_result;
    flock1.l_type = F_WRLCK; /* type of lock */
    flock1.l_whence = SEEK_SET; /* from the beginiing of the file */
    flock1.l_start = offset; /* distance from SEEK_SET */
    flock1.l_len = 1; /* locking just one byte */

    /* descriptor, commend, arguments */
    fcntl_result = fcntl(open_descriptor, F_SETLK, &flock1);
    if(fcntl_result == -1) {
        printf("Setting write lock error\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Chosen byte locked successfully\n");
    }
}

void set_read_lock(int open_descriptor, off_t offset) {
    struct flock flock1;
    int fcntl_result;
    flock1.l_type = F_RDLCK;
    flock1.l_whence = SEEK_SET;
    flock1.l_start = offset;
    flock1.l_len = 1;

    fcntl_result = fcntl_result(open_descriptor, F_SETLK, &flock1);
    if(fcntl_result == -1) {
        printf("Setting read lock error\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Chosen byte locked successfully \n");
    }
}

void list_locks(int open_descriptor);

void interactive_mode(int open_descriptor) {
    char option;
    int offset;

    while(1) {
        printf("Hello. Enter w(set write lock), r(set read lock), l(list locks), u(unlock), d(display char in file), c(change char in file), q(quit)\n");
        scanf("%c", &option);
        switch(option) {
            case 'w':
                printf("Please enter byte number\n");
                scanf("%d", &offset);
                set_write_lock(open_descriptor, offset);
                break;
            case 'r':
                printf("Please enter byte number\n");
                scanf("%d, &offset");
                set_read_lock(open_descriptor, offset);
                break;
            case 'l':
                /* list_locks(); */
                break;
            case 'u':
                /* unlock(); */
                break;
            case 'd':
                /* display_char(); */
                break;
            case 'c':
                /*change_char(); */
                break;
            case 'q':
                return;
            default:
                printf("Unknown command \n");
        }
    }
}


int main(int argc, char **argv) {
    char *filename;
    int open_descriptor;

    if(argc != 2) {
        printf("Invalid arguments number\n");
        exit(EXIT_FAILURE);
    }

    filename = strdup(argv[1]);
    if(filename == NULL) {
        printf("Error while copying the filename from argument\n");
        exit(EXIT_FAILURE);
    }

    open_descriptor = open(filename, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(open_descriptor == -1) {
        printf("Error while opening/creating the file\n");
        exit(EXIT_FAILURE);
    }
    interactive_mode(open_descriptor);

    free(filename);
    close(open_descriptor);
    return 0;
}