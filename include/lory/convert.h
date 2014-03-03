/* lory/convert.h
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

/**
 * @defgroup Lory_convert convert
 * @{
 */

#ifndef LORY_CONVERT_H
#define LORY_CONVERT_H

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

#include <lory/bitmap.h>

/**
 * @fn void LoryConvert(LoryPixelRef src, LoryPixelRef dest, double hue, double range)
 * @brief Convert pixel to selective color.
 *
 * If pixel's hue value is out range of (hue-range/2) to (hue+range/2), that convert to monotone pixel.
 *
 * @param [in] src      Source pixel
 * @param [out] dest    Destination pixel
 * @param [in] hue      Target hue between 0.0 and 359.0
 * @param [in] range    Hue range between 0.1 and 180.0
 */
void LoryConvert(LoryPixelRef src, LoryPixelRef dest, double hue, double range);
/**
 * @fn void LoryConvertAndroid8888(void *src, void *dest, uint32_t width, uint32_t heigth, uint32_t stride, double hue, double range, LoryPixelFormat format)
 * @brief Convert bitmap to selective color.
 *
 * All pixels in bitmap apply LoryConvert.
 *
 * @param [in,out] pixels   Pixel array
 * @param [in] width        Image width
 * @param [in] height       Image height
 * @param [in] stride       Bitmap stride
 * @param [in] hue          Target hue between 0.0 and 359.0
 * @param [in] range        Hue range between 0.1 and 180.0
 */
void LoryConvertAndroid8888(void *pixels,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        double hue,
        double range);

void LoryConvertAndroid565(void *pixels,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        double hue,
        double range);

void LoryConvertJpeglib888(uint8_t *scanline,
        uint32_t width,
        double hue,
        double range);


#ifdef __cplusplus
}
#endif

#endif

/**
 * @file        lory/convert.h
 * @brief       Convert module.
 *
 * This module provides partcolor convert functions.
 *
 * @author      Taro Sako
 * @par         Revision
 * $Id$
 * @}
 */
