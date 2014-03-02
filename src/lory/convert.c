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
#include "bitmap.h"

static inline void convert(LoryPixelRef src, LoryPixelRef dest, double hue, double range)
{
    double h = LoryPixelGetHue(src);

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

    if (dest != src) {
        LoryPixelSetAlpha(dest, LoryPixelGetAlpha(src));
        LoryPixelSetRed(dest, LoryPixelGetRed(src));
        LoryPixelSetGreen(dest, LoryPixelGetGreen(src));
        LoryPixelSetBlue(dest, LoryPixelGetBlue(src));
    }

    if ((max > min && (h < min || h > max))
            || (max < min && (h < min && h > max)))
    {
        LoryPixelSetSaturation(dest, 0.0);
    }
}

void LoryConvert(LoryPixelRef src, LoryPixelRef dest, double hue, double range)
{
    convert(src, dest, hue, range);
}

void LoryConvertJpeglib888(uint8_t *scanline,
        uint32_t width,
        double hue,
        double range)
{
    uint32_t x;
    for (x = 0; x < width; x++)
    {
        int rx = x*3, gx = x*3+1, bx = x*3+2;
        LoryPixelRef pixel = LoryPixelCreateARGB(0xFF, scanline[rx], scanline[gx], scanline[bx]);
        convert(pixel, pixel, hue, range);
        scanline[rx] = pixel->red;
        scanline[gx] = pixel->green;
        scanline[bx] = pixel->blue;
        LoryPixelRelease(pixel);
    }

}

void LoryConvertAndroid8888(void *pixels,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        double hue,
        double range)
{
    uint32_t y, x;
    for (y = 0; y < height; y++)
    {
        uint32_t *line = (uint32_t *)pixels;
        for (x = 0; x < width; x++)
        {
            uint8_t r = (uint8_t)(line[x] & 0x000000FF);
            uint8_t g = (uint8_t)((line[x] & 0x0000FF00) >>  8);
            uint8_t b = (uint8_t)((line[x] & 0x00FF0000) >> 16);
            uint8_t a = (uint8_t)((line[x] & 0xFF000000) >> 24);

            LoryPixelRef pixel = LoryPixelCreateARGB(a, r, g, b);
            convert(pixel, pixel, hue, range);

            line[x] = ((((uint32_t)pixel->red)          & 0x000000FF)
                    | ((((uint32_t)pixel->green) <<  8) & 0x0000FF00)
                    | ((((uint32_t)pixel->blue)  << 16) & 0x00FF0000)
                    | ((((uint32_t)pixel->alpha) << 24) & 0xFF000000));

            LoryPixelRelease(pixel);
        }

        pixels = (char *)pixels + stride;
    }
}
