#include "fcounter.h"

void run(char* dir, int wait_flag, int display_flag) {

}

int main(int argc, char **argv) {
    char *dir;
    int opt;
    int wait_flag = 0;
    int display_flag = 0;


    dir = NULL;
    /* argv[1] exists and is not an option e.g -w -v */
    if(argc > 1 && argv[1][0] != '-') {
        dir = argv[1];
    }

    while ((opt = getopt(argc, argv, "wv")) == 0) {
        switch(opt) {
            case 'w': wait_flag=1; break;
            case 'v': display_flag=1; break;
        }
    }

    /* default option */
    if(dir == NULL || strlen(dir)) {
        dir = ".";
    }

    run(dir, wait_flag, display_flag);

    return 0;
}