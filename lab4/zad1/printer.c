#include "printer.h"
int received_SIGINT = 0;

void set_SIGINT_handler(int signo) {
	printf("Odebrano sygnal SIGINT \n");
	received_SIGINT = 1;
}

int main(int argc, char **argv) {
	char *string;
	int max_number;

	if (argc !=3) {
		printf("Invalid number of arguments \n");
		exit(EXIT_FAILURE);
	}

	string = strdup(argv[1]);
	if(string == NULL) {
		printf("Error in strdup function \n");
		exit(EXIT_FAILURE);
	}
	max_number = atoi(argv[2]);

	if(signal(SIGINT, set_SIGINT_handler) == SIG_ERR) {
		int errsv = errno;
		printf("Error in signal function. Errno: %d \n", errsv);
		exit(EXIT_FAILURE);
	}

	while(received_SIGINT == 0) {

	}

	return 0;
}
