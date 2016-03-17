#include "libs.h"

int compare_records(char *first, char *second) {
    int f,s;
    f = (int)first[0];
    s = (int)second[0];
    return f-s;
}

int get_with_system_functions(int file_descriptor, char *buffer, int record_length, int record_index) {
    int bytes_read;
    lseek(file_descriptor, record_index*record_length, SEEK_SET);
    bytes_read = read(file_descriptor, buffer, record_length);
    if(bytes_read != record_length) return -1;
    return 0;
}

int insert_with_system_functions(int file_descriptor, char *record, int record_length, int record_index) {
    int bytes_written;
    lseek(file_descriptor, record_index*record_length, SEEK_SET);
    bytes_written = write(file_descriptor, record, record_length);
    if(bytes_written != record_length) return -1;
    return 0;
}

void sort_with_system_functions(int file_descriptor, unsigned record_length){
    char *current;
    char *compared;
    int i,j;
    int insert_result;

    current = malloc(sizeof(char)*record_length);
    compared = malloc(sizeof(char)*record_length);

   i=1;
   while(get_with_system_functions(file_descriptor, current, record_length, i) == 0) {
        j = i-1;
        get_with_system_functions(file_descriptor, compared, record_length, j);
        while(j>=0 && compare_records(current, compared) < 0) {
            insert_result = insert_with_system_functions(file_descriptor, current ,record_length,j);
            if(insert_result == -1 ){
                printf("error while inserting the record\n");
                exit(EXIT_FAILURE);
            }
            insert_result = insert_with_system_functions(file_descriptor, compared, record_length, j+1);
            if(insert_result == -1 ){
                printf("error while inserting the record \n");
                exit(EXIT_FAILURE);
            }
            j = j -1;
            get_with_system_functions(file_descriptor, compared, record_length, j);
        }
        i+=1;
   }
    free(current);
    free(compared);
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

    sort_with_system_functions(file_descriptor, record_length);

    lseek(file_descriptor, 0, SEEK_SET);
    close_descriptor = close(file_descriptor);
    if (close_descriptor == -1) {
        printf("An error while closing the file\n");
        exit(1);
    }
}

int get_with_library_functions(FILE* filepointer, char *buffer, int record_length, int record_index) {
    size_t read_records;
    fseek(filepointer, record_length*record_index, SEEK_SET);
    read_records = fread(buffer, record_length, 1, filepointer);
    if(read_records != record_length) {
        return -1;
    }
    return 0;
}

int insert_with_library_functions(FILE *filepointer, char *buffer, int record_length, int record_index) {
    size_t written_records;
    fseek(filepointer, record_length*record_index, SEEK_SET);
    written_records = fwrite(buffer, record_length, 1, filepointer);
    if (written_records != record_length) {
        return -1;
    }
    return 0;
}

void sort_with_library_functions(FILE* filepointer, int record_length) {
    char *current;
    char *compared;
    int i,j;
    int insert_result;

     current = malloc(sizeof(char)*record_length);
     compared = malloc(sizeof(char)*record_length);

       i=1;
       while(get_with_library_functions(filepointer, current, record_length, i) == 0) {
            j = i-1;
            get_with_library_functions(filepointer, compared, record_length, j);
            while(j>=0 && compare_records(current, compared) < 0) {
                insert_result = insert_with_library_functions(filepointer, current ,record_length,j);
                if(insert_result == -1 ){
                    printf("error while inserting the record\n");
                    exit(EXIT_FAILURE);
                }
                insert_result = insert_with_library_functions(filepointer, compared, record_length, j+1);
                if(insert_result == -1 ){
                    printf("error while inserting the record \n");
                    exit(EXIT_FAILURE);
                }
                j = j -1;
                get_with_library_functions(filepointer, compared, record_length, j);
            }
            i+=1;
       }
        free(current);
        free(compared);
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

    sort_with_library_functions(filepointer, record_length);
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