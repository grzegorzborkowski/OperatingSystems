#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>


typedef struct tms tms_t;

void print_times(clock_t real, tms_t *tms_start, tms_t * tms_end);

#endif