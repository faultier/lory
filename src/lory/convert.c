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

static inline uint8_t _umax(uint8_t a, uint8_t b)
{
    return a > b ? a : b;
}

static inline uint8_t _umin(uint8_t a, uint8_t b)
{
    return a < b ? a : b;
}

static inline void _convert888(uint8_t red, uint8_t green, uint8_t blue, double target, double range, uint8_t *dest)
{
    if (red == green && green == blue) {
        dest[0] = red;
        dest[1] = green;
        dest[2] = blue;
        return;
    }

    uint8_t max = _umax(red, _umax(green, blue));
    uint8_t min = _umin(red, _umin(green, blue));

    double hue;
    if (max == red)
    {
        hue = 60.0 * (((double)green - (double)blue) / 255.0) / ((max - min) / 255.0);
    }
    else if (max == green)
    {
        hue = 60.0 * (((double)blue - (double)red) / 255.0) / ((max - min) / 255.0) + 120.0;
    }
    else
    {
        hue = 60.0 * (((double)red - (double)green) / 255.0) / ((max - min) / 255.0) + 240.0;
    }
    if (hue < 0)
    {
        hue += 360.0;
    }

    double r = range / 2;
    double top = target + r;
    if (top >= 360.0)
    {
        top -= 360.0;
    }
    double bottom = target - r;
    if (bottom < 0.0)
    {
        bottom += 360.0;
    }

    if ((top > bottom && (hue < bottom || hue > top))
            || (top < bottom && (hue < bottom && hue > top)))
    {
        dest[0] = dest[1] = dest[2] = max;
    } else {
        dest[0] = red;
        dest[1] = green;
        dest[2] = blue;
    }
}

static inline void _convert565(uint8_t red, uint8_t green, uint8_t blue, double target, double range, uint8_t *dest)
{
    if (red == (green/2) && red == blue) {
        dest[0] = red;
        dest[1] = green;
        dest[2] = blue;
        return;
    }

    double r = red / 31.0;
    double g = green / 63.0;
    double b = blue / 31.0;

    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));

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

    double ra = range / 2.0;
    double top = target + ra;
    if (top >= 360.0)
    {
        top -= 360.0;
    }
    double bottom = target - ra;
    if (bottom < 0.0)
    {
        bottom += 360.0;
    }

    if ((top > bottom && (hue < bottom || hue > top))
            || (top < bottom && (hue < bottom && hue > top)))
    {
        dest[0] = (uint8_t)max * 31.0;
        dest[1] = (uint8_t)max * 63.0;
        dest[2] = (uint8_t)max * 31.0;
    } else {
        dest[0] = red;
        dest[1] = green;
        dest[2] = blue;
    }
}

void LoryConvert(uint8_t red, uint8_t green, uint8_t blue, double target, double range, uint8_t *dest)
{
    _convert888(red, green, blue, target, range, dest);
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
        _convert888(scanline[rx], scanline[gx], scanline[bx], hue, range, dest);
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
    const static uint32_t RMASK = 0x000000FF;
    const static uint32_t GMASK = 0x0000FF00;
    const static uint32_t BMASK = 0x00FF0000;
    const static uint32_t AMASK = 0xFF000000;

    for (uint32_t y = 0; y < height; y++)
    {
        uint32_t *line = (uint32_t *)(pixels + y * stride);
        for (uint32_t x = 0; x < width; x++)
        {
            uint8_t r = (uint8_t)(line[x] & RMASK);
            uint8_t g = (uint8_t)((line[x] & GMASK) >>  8);
            uint8_t b = (uint8_t)((line[x] & BMASK) >> 16);

            uint8_t dest[3];
            _convert888(r, g, b, hue, range, dest);

            line[x] = ((((uint32_t)dest[0])        & RMASK)
                    | ((((uint32_t)dest[1]) <<  8) & GMASK)
                    | ((((uint32_t)dest[2]) << 16) & BMASK)
                    | (line[x] & AMASK));
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
    const static uint16_t RMASK = 0xF800;
    const static uint16_t GMASK = 0x07E0;
    const static uint16_t BMASK = 0x001F;

    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            uint16_t *line = (uint16_t *)(pixels + y * stride);
            uint8_t b = (uint8_t)(line[x]  & BMASK);
            uint8_t g = (uint8_t)((line[x] & GMASK) >>  5);
            uint8_t r = (uint8_t)((line[x] & RMASK) >> 11);

            uint8_t dest[3];
            _convert565(r, g, b, hue, range, dest);

            line[x] = ((((uint16_t)dest[2])        & BMASK)
                    | ((((uint16_t)dest[1]) <<  5) & GMASK)
                    | ((((uint16_t)dest[0]) << 11) & RMASK));
        }
    }
}
