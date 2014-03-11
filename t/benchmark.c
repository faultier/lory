#include <float.h>
#include <stdio.h>
#include <time.h>

#include "benchmark.h"
#include "fixtures.h"

static uint8_t **bitmap_rgb_8_split;
static uint32_t *bitmap_abgr_8888;
static uint16_t *bitmap_rgb_565;

void benchmark(const char *label,
        int count,
        void (*func)(void),
        void (*setup)(void),
        void (*teardown)(void))
{
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
    printf("%s\t: total = %9.5fsec, avg = %9.5fms, max = %9.5f ms, min = %9.5f ms\n", label, total/1000, total/count, min, max);
}

void setup_rgb_8_split(void)
{
    LoryTestCreateBitmap((void **)&bitmap_rgb_8_split, 512, LORY_RGB_8_SPLIT);
}

void teardown_rgb_8_split(void)
{
    LoryTestReleaseBitmap((void *)bitmap_rgb_8_split, 512, LORY_RGB_8_SPLIT);
}

void convert_rgb_8_split()
{
    for (int y = 0; y < 512; y++)
    {
        LoryConvertJpeglib888(bitmap_rgb_8_split[y], 512, 0.0, 40.0);
    }
}

void setup_abgr_8888(void)
{
    LoryTestCreateBitmap((void **)&bitmap_abgr_8888, 512, LORY_ABGR_8888);
}

void teardown_abgr_8888(void)
{
    LoryTestReleaseBitmap((void *)bitmap_abgr_8888, 512, LORY_ABGR_8888);
}

void convert_abgr_8888()
{
    LoryConvertAndroid8888(bitmap_abgr_8888, 512, 512, 512*sizeof(uint32_t), 0.0, 40.0);
}

void setup_rgb_565(void)
{
    LoryTestCreateBitmap((void **)&bitmap_rgb_565, 512, LORY_RGB_565);
}

void teardown_rgb_565(void)
{
    LoryTestReleaseBitmap((void *)bitmap_rgb_565, 512, LORY_RGB_565);
}

void convert_rgb_565()
{
    LoryConvertAndroid565(bitmap_rgb_565, 512, 512, 512*sizeof(uint16_t), 0.0, 40.0);
}

void run_benchmark(void)
{
    printf("===== benchmark =====\n");
    benchmark("RGB_8_SPLIT", 100, convert_rgb_8_split, setup_rgb_8_split, teardown_rgb_8_split);
    benchmark("ABGR_8888  ", 100, convert_abgr_8888, setup_abgr_8888, teardown_abgr_8888);
    benchmark("RGB_565    ", 100, convert_rgb_565, setup_rgb_565, teardown_rgb_565);
}
