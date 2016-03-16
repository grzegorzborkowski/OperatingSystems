#include "tree.h"

/* this variable is global beacuse it is necessary in
 file_function and can't be passed as a argument beacuse it's nfsw execution
 could be refactor by creating a function with a pointer to another function
 and from that funciton executing nftw */
char *mode;

int is_valid_mode_string(char *mode) {
    char pattern[3] = "rwx";
    int i;
    if (strlen(mode) != 9) return -1;
    for (i = 0; i < 9; i++) {
        if (mode[i] != pattern[i % 3] && mode[i] != '-') return -1;
    }
    return 0;
}

int check_modes_matching(char *mode_pattern,const struct stat *file_stat) {
    int i;
    int bits[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP,
                   S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    for (i = 0; i < 9; i++) {
        if (mode_pattern[i] != '-') {
            if (!(file_stat->st_mode & bits[i])) return 0;
        } else if (file_stat->st_mode & bits[i]) return 0;
    }
    return 1;
}

int file_function(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {

    char time[20];

    /* file is not a regular file */
     if(tflag != FTW_F) return 0;

    if(check_modes_matching(mode ,sb) == 1) {
        strftime(time, 20, "%Y-%m-%d %H:%M:%S", localtime(&sb->st_atime));
        printf("File name %s\n", fpath);
        printf("File size in bytes: %d\n", (int)(sb->st_size));
        printf("Last access %s\n", time);
        printf("----------\n");
    }
    return 0;
}


int list_directory(char *directory_path) {
    int nftw_output;
    int flags = 0;
    /* 20 -> maximum number of directories that nftw opens simultaneously */
    nftw_output = nftw(directory_path, file_function, 20, flags);
    return nftw_output;
}

/* fpath - the pathname of the entry
 * sb is a pointer to the stat structure returned by a call to stat to fpath
 * tflag one of following values: FTW_F (fpath is a regular FILE), FTW_D (fpath is a directory), FTW_DNR(file is a directory which can't be read)
 * ftwbuf -> struct with int base, int level. Base: offset of the file, level: depth in the directory tree
 */


int main(int argc, char **argv) {
    /* default files access mode: rw-rw-r-- */
    char *directory_path;
    int valid_flag, nftw_output;

    if (argc != 3) {
        printf("Unsupported number of arguments\n");
        exit(1);
    }

    directory_path = strdup(argv[1]);
    if (directory_path == NULL) {
        printf("Error in strdup function\n");
        exit(1);
    }

    mode = strdup(argv[2]);
    if (mode == NULL) {
        printf("Error in strdup function\n");
        exit(1);
    }

    valid_flag = is_valid_mode_string(mode);
    if (valid_flag == -1) {
        printf("Entered mode is not valid");
        exit(1);
    }

    nftw_output = list_directory(directory_path);

    if (nftw_output == -1) {
        printf("Error in nftw function\n");
        exit(1);
    }
    free(mode);
    free(directory_path);
    return 0;
}