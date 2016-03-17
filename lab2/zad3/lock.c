#include "lock.h"

int execute_lock(int open_descriptor, int function, int type, int offset) {
    struct flock flock1;
    flock1.l_type = type; /* type of lock */
    flock1.l_whence = SEEK_SET;  /* from the beginiing of the file */
    flock1.l_start = offset; /* distance from SEEK_SET */
    flock1.l_len = 1; /* locking just one byte */
    return fcntl(open_descriptor, function, &flock1);
}

void set_write_lock(int open_descriptor, off_t offset) {
    int fcntl_result;
    fcntl_result = execute_lock(open_descriptor, F_SETLK, F_WRLCK, offset);
    if(fcntl_result == -1) {
        printf("Setting write lock error\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Chosen byte locked successfully\n");
    }
}

void set_read_lock(int open_descriptor, off_t offset) {
    int fcntl_result;
    fcntl_result = execute_lock(open_descriptor, F_SETLK, F_RDLCK, offset);
    if(fcntl_result == -1) {
        printf("Setting read lock error\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Chosen byte locked successfully \n");
    }
}

/*void list_locks(int open_descriptor) {
    int fcntl_result;

    fcntl_result = fcntl(open_descriptor, F_GETLK, &flock1);
    if(fcntl_result == -1) {
        printf("Error in fcntl F_GETLK (GET LOCK)\n");
        exit(EXIT_FAILURE);
    }

} */


void unlock(int open_descriptor, off_t offset) {
    int fcntl_result;
    fcntl_result = execute_lock(open_descriptor, F_SETLK, F_UNLCK, offset);
    if(fcntl_result == -1) {
        printf("Unlocking failed\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Removing lock succeed\n");
    }
}

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
                scanf("%d", &offset);
                set_read_lock(open_descriptor, offset);
                break;
            case 'l':
                /* list_locks(); */
                break;
            case 'u':
                printf("Enter the byte number\n");
                scanf("%d", &offset);
                unlock(open_descriptor, offset);
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