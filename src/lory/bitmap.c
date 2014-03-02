/* lory/bitmap.c
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
#include <stdlib.h>
#include "bitmap.h"

static inline void rgb2hsb(LoryPixelRef pixel, uint8_t *rgb)
{
    double r = (double) rgb[0] / 255.0;
    double g = (double) rgb[1] / 255.0;
    double b = (double) rgb[2] / 255.0;
    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));

    if (max == r) {
        pixel->hue = 60.0 * (g - b) / (max - min);
    } else if (max == g) {
        pixel->hue = 60.0 * (b - r) / (max - min) + 120.0;
    } else if (max == b) {
        pixel->hue = 60.0 * (r - g) / (max - min) + 240.0;
    }
    if (pixel->hue < 0) {
        pixel->hue += 360.0;
    }
    pixel->saturation = ((max == min) ? 0.0 : ((max - min) / max));
    pixel->brightness = max;
}

static inline void hsb2rgb(LoryPixelRef pixel, double *hsb)
{
    int hi = ((int) hsb[0] / 60) % 6;
    double f = hsb[0] / 60 - hi;
    double p = hsb[2] * (1 - hsb[1]);
    double q = hsb[2] * (1 - f * hsb[1]);
    double t = hsb[2] * (1 - (1 - f) * hsb[1]);

    double v = hsb[2] * 255;
    p *= 255;
    q *= 255;
    t *= 255;

    switch (hi)
    {
        case 0: pixel->red = v; pixel->green = t; pixel->blue = p; break;
        case 1: pixel->red = q; pixel->green = v; pixel->blue = p; break;
        case 2: pixel->red = p; pixel->green = v; pixel->blue = t; break;
        case 3: pixel->red = p; pixel->green = q; pixel->blue = v; break;
        case 4: pixel->red = t; pixel->green = p; pixel->blue = v; break;
        case 5: pixel->red = v; pixel->green = p; pixel->blue = q; break;
    }
}

uint8_t LoryPixelGetAlpha(LoryPixelRef pixel)
{
    return pixel->alpha;
}

uint8_t LoryPixelGetRed(LoryPixelRef pixel)
{
    return pixel->red;
}

uint8_t LoryPixelGetGreen(LoryPixelRef pixel)
{
    return pixel->green;
}

uint8_t LoryPixelGetBlue(LoryPixelRef pixel)
{
    return pixel->blue;
}

double LoryPixelGetHue(LoryPixelRef pixel)
{
    return pixel->hue;
}

double LoryPixelGetSaturation(LoryPixelRef pixel)
{
    return pixel->saturation;
}

double LoryPixelGetBrightness(LoryPixelRef pixel)
{
    return pixel->brightness;
}

void LoryPixelSetAlpha(LoryPixelRef pixel, uint8_t alpha)
{
    pixel->alpha = alpha;
}

void LoryPixelSetRed(LoryPixelRef pixel, uint8_t red)
{
    pixel->red = red;
    uint8_t rgb[3] = { pixel->red, pixel->green, pixel->blue };
    rgb2hsb(pixel, rgb);
}

void LoryPixelSetGreen(LoryPixelRef pixel, uint8_t green)
{
    pixel->green = green;
    uint8_t rgb[3] = { pixel->red, pixel->green, pixel->blue };
    rgb2hsb(pixel, rgb);
}

void LoryPixelSetBlue(LoryPixelRef pixel, uint8_t blue)
{
    pixel->blue = blue;
    uint8_t rgb[3] = { pixel->red, pixel->green, pixel->blue };
    rgb2hsb(pixel, rgb);
}

void LoryPixelSetHue(LoryPixelRef pixel, double h)
{
    pixel->hue = h;
    double hsb[3] = { pixel->hue, pixel->saturation, pixel->brightness };
    hsb2rgb(pixel, hsb);
}

void LoryPixelSetSaturation(LoryPixelRef pixel, double s)
{
    pixel->saturation = s;
    double hsb[3] = { pixel->hue, pixel->saturation, pixel->brightness };
    hsb2rgb(pixel, hsb);
}

void LoryPixelSetBrightness(LoryPixelRef pixel, double b)
{
    pixel->brightness = b;
    double hsb[3] = { pixel->hue, pixel->saturation, pixel->brightness };
    hsb2rgb(pixel, hsb);
}

LoryPixelRef LoryPixelCreateARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
    LoryPixelRef pixel = (LoryPixelRef)malloc(sizeof(struct lory_pixel));
    pixel->alpha = a;
    pixel->red   = r;
    pixel->green = g;
    pixel->blue  = b;
    uint8_t rgb[3] = { r, g, b };
    rgb2hsb(pixel, rgb);
    return pixel;
}

LoryPixelRef LoryPixelCreateHSB(double h, double s, double b)
{
    LoryPixelRef pixel = (LoryPixelRef)malloc(sizeof(struct lory_pixel));
    pixel->alpha = 255;
    pixel->hue = h;
    pixel->saturation = s;
    pixel->brightness = b;
    double hsb[3] = { h, s, b };
    hsb2rgb(pixel, hsb);
    return pixel;
}

void LoryPixelRelease(LoryPixelRef pixel)
{
    free(pixel);
}
