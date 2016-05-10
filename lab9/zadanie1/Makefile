CC = gcc
FLAGS = -Wall -pthread

all: philosophers

philosophers: philosophers.c philosophers.h
	$(CC) $(FLAGS) philosophers.c -o philo

clean:
	rm philo