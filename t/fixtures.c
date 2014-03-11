#include <stdlib.h>
#include <math.h>
#include "fixtures.h"

static inline void _hsv2rgb(double h, double s, double v, uint8_t *rgb)
{
    int hi = ((int)(h/60))%6;
    double f = h / 60 - hi;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch (hi)
    {
        case 0: rgb[0] = (uint8_t)(v*255); rgb[1] = (uint8_t)(t*255); rgb[2] = (uint8_t)(p*255); break;
        case 1: rgb[0] = (uint8_t)(q*255); rgb[1] = (uint8_t)(v*255); rgb[2] = (uint8_t)(p*255); break;
        case 2: rgb[0] = (uint8_t)(p*255); rgb[1] = (uint8_t)(v*255); rgb[2] = (uint8_t)(t*255); break;
        case 3: rgb[0] = (uint8_t)(p*255); rgb[1] = (uint8_t)(q*255); rgb[2] = (uint8_t)(v*255); break;
        case 4: rgb[0] = (uint8_t)(t*255); rgb[1] = (uint8_t)(p*255); rgb[2] = (uint8_t)(v*255); break;
        case 5: rgb[0] = (uint8_t)(v*255); rgb[1] = (uint8_t)(p*255); rgb[2] = (uint8_t)(q*255); break;
    }
}

static inline void _rgb_8_split(uint8_t ***bitmap, uint16_t size)
{
    *bitmap = (uint8_t **)malloc(sizeof(uint8_t*)*size);
    double hs = 360.0 / size;
    double svs = 1.0 / size;
    for (int y = 0; y < size; y++)
    {
        double s = 1.0 - (y * svs);
        uint8_t *row = (uint8_t *)malloc(sizeof(uint8_t)*size*3);
        for (int x = 0; x < size; x++)
        {
            double h = (s == 0.0 ? 0.0 : x * hs );
            double v = (s == 0.0 ? x * svs : 1.0);
            _hsv2rgb(h, s, v, (uint8_t *)(row + x*3));
        }
        (*bitmap)[y] = row;
    }
}

static inline void _abgr_8888(uint32_t **bitmap, uint16_t size)
{
    *bitmap = (uint32_t *)malloc(sizeof(uint32_t)*size*size);
    uint32_t *p = *bitmap;
    double hs = 360.0 / size;
    double svs = 1.0 / size;
    for (int y = 0; y < size; y++)
    {
        double s = 1.0 - (y * svs);
        for (int x = 0; x < size; x++)
        {
            double h = (s == 0.0 ? 0.0 : x * hs );
            double v = (s == 0.0 ? x * svs : 1.0);
            uint8_t rgb[3];
            _hsv2rgb(h, s, v, rgb);
            p[0] = (0xFF << 24 | ((uint32_t)rgb[2]) << 16 | ((uint32_t)rgb[1]) << 8 | rgb[0]);
            p++;
        }
    }
}

static inline void _rgb_565(uint16_t **bitmap, uint16_t size)
{
    *bitmap = (uint16_t *)malloc(sizeof(uint16_t)*size*size);
    uint16_t *p = *bitmap;
    double hs = 360.0 / size;
    double svs = 1.0 / size;
    for (int y = 0; y < size; y++)
    {
        double s = 1.0 - (y * svs);
        for (int x = 0; x < size; x++)
        {
            double h = (s == 0.0 ? 0.0 : x * hs );
            double v = (s == 0.0 ? x * svs : 1.0);
            uint8_t rgb[3];
            _hsv2rgb(h, s, v, rgb);
            uint16_t r = (((uint16_t)round(rgb[0] / 255.0 * 31.0)) << 11) & 0xF800;
            uint16_t g = (((uint16_t)round(rgb[1] / 255.0 * 63.0)) << 5) & 0x07E0;
            uint16_t b = ((uint16_t)round(rgb[2] / 255.0 * 31.0)) & 0x001F;
            p[0] = (r | g | b);
            p++;
        }
    }
}

void LoryTestCreateBitmap(void **bitmap, uint16_t size, LoryPixelFormat format)
{
    switch (format)
    {
        case LORY_RGB_8_SPLIT:
            _rgb_8_split((uint8_t ***)bitmap, size);
            break;
        case LORY_RGB_565:
            _rgb_565((uint16_t **)bitmap, size);
            break;
        case LORY_ABGR_8888:
            _abgr_8888((uint32_t **)bitmap, size);
            break;
    }
}

void LoryTestReleaseBitmap(void *bitmap, uint16_t size, LoryPixelFormat format)
{
    switch (format)
    {
        case LORY_RGB_8_SPLIT:
            for (int y = 0; y < size; y++)
            {
                free(((uint8_t**)bitmap)[y]);
            }
            free(bitmap);
            break;
        default:
            free(bitmap);
    }
}
