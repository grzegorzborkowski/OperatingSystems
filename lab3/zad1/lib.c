#include "lib.h"

void print_times(clock_t real, tms_t *tms_start, tms_t *tms_end) {
    static long clk = 0;
    double clk_double;
    clk = sysconf(_SC_CLK_TCK);
    clk_double = (double)(clk);
    printf("Real time %f\n", real / clk_double);
    printf("User time %f\n", (tms_end->tms_utime - tms_start->tms_utime) / clk_double);
    printf("System time %f\n", (tms_end->tms_stime - tms_start->tms_stime) / clk_double);
    printf("Child user time %f\n", (tms_end->tms_cutime - tms_start->tms_cutime) / clk_double);
    printf("Child system time %f\n", (tms_end->tms_cstime - tms_start->tms_cstime) / clk_double);
}