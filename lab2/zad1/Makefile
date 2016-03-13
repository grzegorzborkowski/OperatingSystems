CC = gcc
FLAGS = -Wall -pedantic
DEPSMAIN = libs.h main.c
DEPSGENERATOR = libs.h generate.c

all: main generate

main: $(DEPSMAIN)
	$(CC) $(FLAGS) main.c -o main

generate: $(DEPSGENERATOR)
	$(CC) $(FLAGS) generate.c -o generate

clean:
	rm main
	rm generate
	rm Makefile~
