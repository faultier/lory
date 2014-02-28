/* lory/types.c
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
#include "types.h"

static inline void rgb2hsv(uint8_t red,
        uint8_t green,
        uint8_t blue,
        double *hue,
        double *sat,
        double *val)
{
    double r = (double) red / 255;
    double g = (double) green / 255;
    double b = (double) blue / 255;
    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));

    if (max == r) {
        *hue = 60 * (g - b) / (max - min);
    } else if (max == g) {
        *hue = 60 * (b - r) / (max - min) + 120;
    } else {
        *hue = 60 * (r - g) / (max - min) + 240;
    }
    if (*hue < 0) {
        *hue += 360.0;
    }

    *sat = (max - min) / max;
    *val = max;
}

static inline void hsv2rgb(double hue,
        double sat,
        double val,
        uint8_t *red,
        uint8_t *green,
        uint8_t *blue)
{
    int hi = ((int) hue / 60) % 6;
    double f = hue / 60 - hi;
    double p = val * (1 - sat);
    double q = val * (1 - f * sat);
    double t = val * (1 - (1 - f) * sat);

    double v = val * 255;
    p *= 255;
    q *= 255;
    t *= 255;

    switch (hi)
    {
        case 0: *red = v; *green = t; *blue = p; break;
        case 1: *red = q; *green = v; *blue = p; break;
        case 2: *red = p; *green = v; *blue = t; break;
        case 3: *red = p; *green = q; *blue = v; break;
        case 4: *red = t; *green = p; *blue = v; break;
        case 5: *red = v; *green = p; *blue = q; break;
    }
}

uint8_t lory_getColorA(lory_color_t *color)
{
    return color->alpha;
}

uint8_t lory_getColorR(lory_color_t *color)
{
    return color->red;
}

uint8_t lory_getColorG(lory_color_t *color)
{
    return color->green;
}

uint8_t lory_getColorB(lory_color_t *color)
{
    return color->blue;
}

double lory_getColorH(lory_color_t *color)
{
    return color->hue;
}
double lory_getColorS(lory_color_t *color)
{
    return color->saturation;
}

double lory_getColorV(lory_color_t *color)
{
    return color->value;
}

void lory_setColorA(lory_color_t *color, uint8_t alpha)
{
    color->alpha = alpha;
}

void lory_setColorR(lory_color_t *color, uint8_t red)
{
    color->red = red;
    rgb2hsv(color->red, color->green, color->blue, &(color->hue), &(color->saturation), &(color->value));
}

void lory_setColorG(lory_color_t *color, uint8_t green)
{
    color->green = green;
    rgb2hsv(color->red, color->green, color->blue, &(color->hue), &(color->saturation), &(color->value));
}

void lory_setColorB(lory_color_t *color, uint8_t blue)
{
    color->blue = blue;
    rgb2hsv(color->red, color->green, color->blue, &(color->hue), &(color->saturation), &(color->value));
}

void lory_setColorH(lory_color_t *color, double hue)
{
    color->hue = hue;
    hsv2rgb(color->hue, color->saturation, color->value, &(color->red), &(color->green), &(color->blue));
}

void lory_setColorS(lory_color_t *color, double sat)
{
    color->saturation = sat;
    hsv2rgb(color->hue, color->saturation, color->value, &(color->red), &(color->green), &(color->blue));
}

void lory_setColorV(lory_color_t *color, double val)
{
    color->value = val;
    hsv2rgb(color->hue, color->saturation, color->value, &(color->red), &(color->green), &(color->blue));
}

lory_color_t * lory_createColorWithARGB(uint8_t alpha,
        uint8_t red,
        uint8_t green,
        uint8_t blue)
{
    lory_color_t *color = (lory_color_t *)malloc(sizeof(lory_color_t));
    color->alpha = alpha;
    color->red = red;
    color->green = green;
    color->blue = blue;
    rgb2hsv(red, green, blue, &(color->hue), &(color->saturation), &(color->value));
    return color;
}

lory_color_t * lory_createColorWithHSV(double hue,
        double sat,
        double val)
{
    lory_color_t *color = (lory_color_t *)malloc(sizeof(lory_color_t));
    color->hue = hue;
    color->saturation = sat;
    color->value = val;
    color->alpha = 0;
    hsv2rgb(hue, sat, val, &(color->red), &(color->green), &(color->blue));
    return color;
}

void lory_releaseColor(lory_color_t *color)
{
    free(color);
}
