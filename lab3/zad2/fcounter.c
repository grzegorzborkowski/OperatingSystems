#include "fcounter.h"

void run(char* dir_path, char *ext, int wait_flag, int display_flag) {
	int file_count;
	DIR *dir;
	dirent_t *dirent_file;

	file_count = 0;

	dir = opendir(dir_path);
	if(dir == NULL) {
		printf("Error while opening the directory\n");
		exit(EXIT_FAILURE);
	}

	while(dirent_file = readdir(dir)) {
		if(!strcmp(dirent_file->d_name, "." )|| !strcmp(dirent_file->d_name, "..")) continue;

		if(dirent_file->d_type == DT_DIR) {
			printf("Directory %s\n", dirent_file->d_name);
		}
		else if(dirent_file->d_type == DT_REG) {
			printf("Regular file %s\n", dirent_file->d_name);
			if(ext==NULL) {
				file_count += 1;
			}
		}
	}
	closedir(dir);
}

int main(int argc, char **argv) {
    char *dir, *ext;
    int opt;
    int wait_flag = 0;
    int display_flag = 0;
    int path_browse_flag = 0;


    dir = NULL;
    /* argv[1] exists and is not an option e.g -w -v */
    if(argc > 1 && argv[1][0] != '-') {
        dir = argv[1];
    }

    ext = getenv("EXT_TO_BROWSE");

    while ((opt = getopt(argc, argv, "wvp")) == 0) {
        switch(opt) {
        	case 'p': path_browse_flag=1; break;
            case 'w': wait_flag=1; break;
            case 'v': display_flag=1; break;
        }
    }

    /* default option -> without flag p */
    if(path_browse_flag ==0 && (dir == NULL || strlen(dir))) {
        dir = ".";
    }

    if(path_browse_flag == 1) {
    	dir = getenv("PATH_TO_BROWSE");
    }

    run(dir, ext, wait_flag, display_flag);

    return 0;
}