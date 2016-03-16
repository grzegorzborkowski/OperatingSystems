CC = gcc
FLAGS = -Wall -pedantic
DEPS_DIRECT = tree.h tree_direct.c
DEPS_RELATIVE = tree.h tree_relative.c

all: relative clean

relative: $(DEPS_RELATIVE)
	$(CC) $(FLAGS) tree_relative.c -o tree_relative

direct: $(DEPS_DIRECT)
	$(CC) $(FLAGS) tree_direct.c -o tree_direct
	
clean:


