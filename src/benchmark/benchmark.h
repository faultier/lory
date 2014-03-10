#ifndef LORY_BENCHMARK_H
#define LORY_BENCHMARK_H

void benchmark(const char *label,
        int count,
        void (*func)(void),
        void (*setup)(void),
        void (*teardown)(void));

#endif
