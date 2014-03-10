#include <float.h>
#include <stdio.h>
#include <time.h>

#include "benchmark.h"

void benchmark(const char *label,
        int count,
        void (*func)(void),
        void (*setup)(void),
        void (*teardown)(void))
{
    printf("==========\n%s: \n", label);
    int i = count;
    double total = 0.0;
    double min   = DBL_MAX;
    double max   = DBL_MIN;
    for (; i; i--) {
        (*setup)();
        clock_t start = clock();
        (*func)();
        clock_t end = clock();
        (*teardown)();
        double msec = ((end - start) / (double)CLOCKS_PER_SEC) * 1000.0;
        total += msec;
        if (min > msec) min = msec;
        if (max < msec) max = msec;
    }
    printf("  times: %d\n", count);
    printf("  total: %.5f sec\n", total/1000.0);
    printf("  avg:   %.5f msec\n", total/count);
    printf("  min:   %.5f msec\n", min);
    printf("  max:   %.5f msec\n", max);
}
