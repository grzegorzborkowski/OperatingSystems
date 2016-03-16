#include "libs.h"

void generate_records(int file_descriptor,
                      unsigned record_length, unsigned record_count) {
    char *buffer;
    int i, j;
    ssize_t write_result;

    srand(time(NULL));

    buffer = (char *) malloc(sizeof(char) * record_length);
    for (j = 0; j < record_count; j++) {
        for (i = 0; i < record_length; i++) {
            buffer[i] = rand() % 76 + 48;
        }
        write_result = write(file_descriptor, buffer, record_length);
        if (write_result < 0) {
            printf("Error occured while writing to file");
            exit(1);
        }
    }
    free(buffer);
}


int main(int argc, char **argv) {
    int file_descriptor, close_result;
    unsigned record_length, record_count;

    if (argc != 4) {
        printf("Unsupported number of arguments\n");
        exit(1);
    }

    file_descriptor = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        printf("Error while opening the file");
        exit(1);
    }

    record_length = (atol)(argv[2]);
    if (record_length == 0) {
        printf("Record length must be a number greater than 0");
        exit(1);
    }

    record_count = (atol)(argv[3]);
    if (record_count == 0) {
        printf("Record count must be a number greater than 0");
        exit(1);
    }

    generate_records(file_descriptor, record_length, record_count);

    close_result = close(file_descriptor);
    if (close_result == -1) {
        printf("Error while closing the file");
        exit(1);
    }
    return 0;
}