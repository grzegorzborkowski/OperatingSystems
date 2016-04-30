#include "printer.h"

int MAX_NUMBER = 0;
int INCREMENT_VALUE = 1;
int counter_SIGTSTP_FLAG = 1;

int GOT_MAXIMUM_FLAG = 0;
int PRINTBACKWARD_FLAG = 0;
int received_SIGINT_FLAG = 0;


void SIGINT_handler(int signo) {
	printf("Odebrano sygnal SIGINT \n");
	received_SIGINT_FLAG = 1;
}

void SIGTSTP_handler(int signo) {
	printf("Odebrano sygnal SIGSTP \n");
	counter_SIGTSTP_FLAG += INCREMENT_VALUE;
	PRINTBACKWARD_FLAG += 1;
	if(counter_SIGTSTP_FLAG >= MAX_NUMBER) {
		GOT_MAXIMUM = 1;
		INCREMENT_VALUE *= -1;
	}
	if(GOT_MAXIMUM && counter_SIGTSTP_FLAG == 1) {
		INCREMENT_VALUE *= -1;
	}
}

void print_string(char *string, size_t length) {
	int i;

	if(PRINTBACKWARD_FLAG % 2 == 0) {
		for(i=0; i<length; i++) {
			printf("%c", string[i]);
		}
	} else {
		for(i=length-1; i>=0; i--) {
			printf("%c", string[i]);
		}
	}
}


int main(int argc, char **argv) {
	char *string;
	int errsv, i;
	sigaction_t act;
	size_t length;

	if (argc !=3) {
		printf("Invalid number of arguments \n");
		exit(EXIT_FAILURE);
	}

	string = strdup(argv[1]);
	if(string == NULL) {
		printf("Error in strdup function \n");
		exit(EXIT_FAILURE);
	}

	MAX_NUMBER = atoi(argv[2]);

	if(signal(SIGINT, SIGINT_handler) == SIG_ERR) {
		errsv = errno;
		printf("Error in signal function. Errno: %d \n", errsv);
		exit(EXIT_FAILURE);
	}

	/* pointer to a function handling signal */
	act.sa_handler = &SIGTSTP_handler;

	/* NULL is oldact parametr */
	if (sigaction(SIGTSTP, &act, NULL) == -1) {
		errsv = errno;
		printf("Error in sigaction function. Errno %d \n", errsv);
		exit(EXIT_FAILURE);
	}

	length = strlen(string);

	while(received_SIGINT_FLAG == 0) {
		for(i=0; i<counter_SIGTSTP_FLAG; i++) {
		print_string(string, length);
		}
			printf("\n");
	}

	return 0;
}
