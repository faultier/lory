#ifndef LORY_BITMAP_H_PRIVATE
#define LORY_BITMAP_H_PRIVATE

#include <lory/bitmap.h>

struct lory_pixel {
    uint8_t alpha;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    double hue;
    double saturation;
    double brightness;
};

#endif
