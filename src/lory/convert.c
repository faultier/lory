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

static inline void convert(uint8_t red, uint8_t green, uint8_t blue, double target, double range, uint8_t *dest)
{
    double r = (double) red   / 255.0;
    double g = (double) green / 255.0;
    double b = (double) blue  / 255.0;
    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));

    dest[0] = red;
    dest[1] = green;
    dest[2] = blue;

    if (max == min) {
        return;
    }

    double hue;
    if (max == r)
    {
        hue = 60.0 * (g - b) / (max - min);
    }
    else if (max == g)
    {
        hue = 60.0 * (b - r) / (max - min) + 120.0;
    }
    else
    {
        hue = 60.0 * (r - g) / (max - min) + 240.0;
    }
    if (hue < 0)
    {
        hue += 360.0;
    }

    double top = target + (range / 2);
    if (top >= 360.0)
    {
        top -= 360.0;
    }

    double bottom = target - (range / 2);
    if (bottom < 0.0)
    {
        bottom += 360.0;
    }

    if ((top > bottom && (hue < bottom || hue > top))
            || (top < bottom && (hue < bottom && hue > top)))
    {
        dest[0] = (uint32_t)(max * 255.0);
        dest[1] = (uint32_t)(max * 255.0);
        dest[2] = (uint32_t)(max * 255.0);
        return;
    }
}

void LoryConvert(uint8_t red, uint8_t green, uint8_t blue, double target, double range, uint8_t *dest)
{
    convert(red, green, blue, target, range, dest);
}

void LoryConvertJpeglib888(uint8_t *scanline,
        uint32_t width,
        double hue,
        double range)
{
    for (uint32_t x = 0; x < width; x++)
    {
        int rx = x*3, gx = x*3+1, bx = x*3+2;
        uint8_t dest[3];
        convert(scanline[rx], scanline[gx], scanline[bx], hue, range, dest);
        scanline[rx] = dest[0];
        scanline[gx] = dest[1];
        scanline[bx] = dest[2];
    }
}

void LoryConvertAndroid8888(void *pixels,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        double hue,
        double range)
{
    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            uint32_t *line = (uint32_t *)(pixels + y * stride);
            uint8_t r = (uint8_t)(line[x] & 0x000000FF);
            uint8_t g = (uint8_t)((line[x] & 0x0000FF00) >>  8);
            uint8_t b = (uint8_t)((line[x] & 0x00FF0000) >> 16);

            uint8_t dest[3];
            convert(r, g, b, hue, range, dest);

            line[x] = ((((uint32_t)dest[0])        & 0x000000FF)
                    | ((((uint32_t)dest[1]) <<  8) & 0x0000FF00)
                    | ((((uint32_t)dest[2]) << 16) & 0x00FF0000)
                    | (line[x] & 0xFF000000));
        }
    }
}

void LoryConvertAndroid565(void *pixels,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        double hue,
        double range)
{
    const static uint16_t BIT5  = 31;
    const static uint16_t BIT6  = 63;
    const static uint16_t RMASK = 0x001F;
    const static uint16_t GMASK = 0x07E0;
    const static uint16_t BMASK = 0xF800;

    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            uint16_t *line = (uint16_t *)(pixels + y * stride);
            uint8_t b = (uint8_t)round((line[x]  & RMASK)        / BIT5 * 255);
            uint8_t g = (uint8_t)round(((line[x] & GMASK) >>  5) / BIT6 * 255);
            uint8_t r = (uint8_t)round(((line[x] & BMASK) >> 11) / BIT5 * 255);

            uint8_t dest[3];
            convert(r, g, b, hue, range, dest);

            line[x] = ((((uint16_t)round(dest[2]/255.0*BIT5))        & RMASK)
                    | ((((uint16_t)round(dest[1]/255.0*BIT6)) <<  5) & GMASK)
                    | ((((uint16_t)round(dest[0]/255.0*BIT5)) << 11) & BMASK));
        }
    }
}
