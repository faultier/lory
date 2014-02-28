/* lory/convert.c
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Taro Sako

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <math.h>
#include <lory/convert.h>
#include "types.h"

extern inline void lory_convert(lory_color_t *color, double hue, double range)
{
    double h = lory_getColorH(color);

    double max = hue + (range/2);
    if (max >= 360.0)
    {
        max -= 360.0;
    }

    double min = hue - (range/2);
    if (min < 0.0)
    {
        min += 360.0;
    }

    if ((max > min && (h < min || h > max))
            || (max < min && (h < min && h > max)))
    {
        lory_setColorS(color, 0.0);
    }
}

void lory_convert_rgb_array(uint8_t *buffer, uint32_t length, double hue, double range)
{
    uint32_t i;
    for (i = 0; i < length; i++)
    {
        int ri = i*3, gi = i*3+1, bi = i*3+2;
        lory_color_t *color = lory_createColorWithARGB(0, buffer[ri], buffer[gi], buffer[bi]);
        lory_convert(color, hue, range);
        buffer[ri] = color->red;
        buffer[gi] = color->green;
        buffer[bi] = color->blue;
        lory_releaseColor(color);
    }
}

static inline lory_color_t * code2color(uint32_t code)
{
    uint8_t a = (uint8_t)((code & 0xFF000000) >> 24);
    uint8_t r = (uint8_t)((code & 0x00FF0000) >> 16);
    uint8_t g = (uint8_t)((code & 0x0000FF00) >> 8);
    uint8_t b = (uint8_t)(code & 0x000000FF);
    return lory_createColorWithARGB(a, r, g, b);
}

static inline uint32_t color2code(lory_color_t *color)
{
    return (((((uint32_t)color->alpha) << 24) & 0xFF000000)
            | ((((uint32_t)color->red) << 16) & 0x00FF0000)
            | ((((uint32_t)color->green) << 8) & 0x0000FF00)
            | (((uint32_t)color->blue) & 0x000000FF));
}

void lory_convert_argb_code_array(uint32_t *bitmap,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        double hue,
        double range)
{
    uint32_t x, y;
    uint32_t *line = bitmap;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            lory_color_t *color = code2color(line[x]);
            lory_convert(color, hue, range);
            line[x] = color2code(color);
            lory_releaseColor(color);
        }
        line = (uint32_t *)line + stride;
    }
}
