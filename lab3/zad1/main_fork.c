#include "lib.h"

int counter = 0;

int main(int argc, char**argv) {
    int N;

    if (argc !=2) {
        printf("Unsupported number of arguments \n");
        exit(1);
    }

    N = atoi(argv[1]);
    printf("%d", N);
    return 0;
}
