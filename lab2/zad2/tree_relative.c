#include "tree.h"

int is_valid_mode_string(char *mode) {
    char pattern[3] = "rwx";
    int i;
    if (strlen(mode) != 9) return -1;
    for (i = 0; i < 9; i++) {
        if (mode[i] != pattern[i % 3] && mode[i] != '-') return -1;
    }
    return 0;
}

void list_directory(char *path, char *mode) {
    struct dirent *dirent;
    struct stat fileStat;
    char *file_path;
    struct stat file_stat;
    int stat_result;
    DIR *pDir;

    pDir = opendir(path);
    if (pDir == NULL) {
        printf("Error while opening the directory\n");
        exit(1);
    }

    while ((dirent = readdir(pDir)) != NULL) {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
            // allocates memory for concatened path string and dirent name.
            // 2 additional bytes for 2*(\n)
           file_path = malloc(strlen(path) + strlen(dirent->d_name) + 2);
            //writes path, dirent->d_name to file_path string
            sprintf(file_path, "%s/%s", path, dirent->d_name);
            // retrievs stats about file_path and saves to file_stat
            stat_result = stat(file_path, &file_stat);
            if (stat_result < 0) {
                printf("Error while retrieving stats\n");
                exit(1);
            }
            if(S_ISREG(file_stat.st_mode)) {
                printf("Regular file: %s\n", file_path);
            }
            if(S_ISDIR(file_stat.st_mode)) {
                // recursively execute this function for
                // every directory found in tree
                list_directory(file_path, mode);
            }
            free(file_path);
        }
    }
    closedir(pDir);
}


int main(int argc, char **argv) {
    char *directory_path, *mode;
    struct stat *buffer;
    int valid_flag;

    if (argc != 3) {
        printf("Unsupported number of arguments\n");
        exit(1);
    }

    directory_path = strdup(argv[1]);
    if(directory_path == NULL) {
        printf("Error in strdup function\n");
        exit(1);
    }

    mode = strdup(argv[2]);
    if(mode == NULL) {
        printf("Error in strdup function\n");
        exit(1);
    }

    valid_flag = is_valid_mode_string(mode);
    if (valid_flag == -1) {
        printf("Entered mode is not valid");
        exit(1);
    }

    list_directory(directory_path, mode);

    free(mode);
    free(directory_path);
    return 0;
}