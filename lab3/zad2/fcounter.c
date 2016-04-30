#include "fcounter.h"

const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) return "";
	return dot + 1;
}

int collect_children_file_count() {
	int file_count, status;
	file_count = 0;
	while(wait(&status)>0) {
		/* increase the count if child terminated normally(return exit, or _exit) */
		if(WIFEXITED(status) && WEXITSTATUS(status) != 1){
			file_count += WEXITSTATUS(status);
		}
	}
	return file_count;
}

void execute_child_process(char *path, char **argv) {
	int exec_result;
	pid_t process_id;
	setenv("PATH_TO_BROWSE", path, 1);
	process_id = fork();
	   if(process_id == 0) {
	   		/* int execvp(const char *file, char *const argv[]); */
            exec_result = execvp(argv[0], argv);
            if(exec_result < 0) {
            	printf("Error in execvp function\n");
            	exit(EXIT_FAILURE);
            }
            fprintf(stderr, "exec error\n");
            _exit(0);
        } else if(process_id < 0) {
            fprintf(stderr, "fork error\n");
        }
}

void insert_argv_path(int argc, char **argv, char *dir) {
	int i;
	if(argc > 1 && argv[1][0] == '-') {
		argv[argc+1] = NULL;
		for(i=1; i<argc; i+=1) {
			argv[i+1] = argv[i];
		}
	}
	argv[1] = dir;
}

void run(char* dir_path, int argc, char **argv, char *ext, int wait_flag, int display_flag) {
	int file_count, children_file_count, sprintf_result;
	DIR *dir;
	dirent_t *dirent_file;
	char *file_path;
	file_count = 0;
	dir = opendir(dir_path);

	if(dir == NULL) {
		printf("Error while opening the directory\n");
		exit(EXIT_FAILURE);
	}

	while((dirent_file = readdir(dir)) != NULL) {
		if(strcmp(dirent_file->d_name, "." )!=0 && strcmp(dirent_file->d_name, "..")!= 0) {

		if(dirent_file->d_type == DT_DIR) {
			file_path = malloc(strlen(dir_path) + strlen(dirent_file->d_name) + 2);
			if(file_path == NULL) {
				printf("Error in malloc function \n");
				exit(EXIT_FAILURE);
			}
			/* copy path + dirent_file->d_nme to entry_path string */
			sprintf_result = sprintf(file_path, "%s/%s", dir_path, dirent_file->d_name);
			if(sprintf_result < 0) {
				printf("Error in sprintf function \n");
				exit(EXIT_FAILURE);
			}
			insert_argv_path(argc, argv, file_path);
			execute_child_process(file_path, argv);
			free(file_path);
		}

		else if(dirent_file->d_type == DT_REG) {
			if(ext==NULL || strcmp(get_filename_ext(dirent_file->d_name), ext) == 0) {
				file_count += 1;
				}
			}
		}
	}
	if(wait_flag) sleep(15);

	children_file_count = collect_children_file_count();

	if(display_flag) {
		printf("Directory %s \n File count %d \n Children file count %d \n ------- \n",
		dir_path, file_count, children_file_count);
	}

	closedir(dir);
	exit(file_count+children_file_count);
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

    while ((opt = getopt(argc, argv, "wvp")) != -1) {
        switch(opt) {
        	case 'p': path_browse_flag=1; break;
            case 'w': wait_flag=1; break;
            case 'v': display_flag=1; break;
        }
    }

    /* default option -> without flag p */
    if(path_browse_flag== 0 && (dir == NULL || strlen(dir) == 0)) {
		dir = ".";
    }

    if(path_browse_flag == 1) {
    	dir = getenv("PATH_TO_BROWSE");
    }
    run(dir, argc, argv, ext, wait_flag, display_flag);

    return 0;
}