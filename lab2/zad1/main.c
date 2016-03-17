#include "libs.h"

void sort_records() {
    printf("Here sorting the records\n");
}


void run_with_system_functions(char *filename, unsigned record_length) {
    int file_descriptor;
    int close_descriptor;

    file_descriptor = open(filename, O_RDWR);

    if (file_descriptor == -1) {
        printf("An error occured while opening the file\n");
        exit(1);
    }

    lseek(file_descriptor, 0, SEEK_SET);

    sort_records(filename, record_length);

    lseek(file_descriptor, 0, SEEK_SET);
    close_descriptor = close(file_descriptor);
    if (close_descriptor == -1) {
        printf("An error while closing the file\n");
        exit(1);
    }
}

void run_with_library_functions(char *filename, unsigned record_length) {
    FILE *filepointer;
    int fseek_result;

    filepointer = fopen(filename, "r+");
    if(filepointer == NULL) {
        printf("Error in opening the file\n");
        exit(1);
    }


    fseek_result = fseek(filepointer, 0, 0);
    if(fseek_result == -1) {
        printf("Error when moving to the beignning of the file\n");
        exit(1);
    }

    sort_records(filename, record_length);
    fseek_result = fseek(filepointer, 0, 0);
    if(fseek_result == -1) {
            printf("Error when moving to the beignning of the file\n");
            exit(1);
        }

    fclose(filepointer);
}

int main(int argc, char **argv) {
    char *mode;
    char *filename;
    unsigned record_length;

    if (argc != 4) {
        printf("Unsupported number of arguments\n");
        exit(1);
    }

    filename = strdup(argv[1]);
    if (filename == NULL) {
        printf("Error while creating copy of filename string");
        exit(1);
    }

    record_length = (atol)(argv[2]);
    if (record_length == 0) {
        printf("Record length must be a number");
        exit(1);
    }

    mode = strdup(argv[3]);
    if (mode == NULL) {
        printf("Error while creating copy of mode string");
        exit(1);
    }

    if (strcmp(mode, "sys") == 0) {
        run_with_system_functions(filename, record_length);
    } else if (strcmp(mode, "lib") == 0) {
        run_with_library_functions(filename, record_length);
    } else {
        printf("Invalid mode. Use either sys or lib\n");
        exit(1);
    }

    free(mode);
    free(filename); /* need to free beacuse of strdup usage */
    return 0;
}