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
extern "C" {
#endif

#include <stdint.h>
#include <lory/types.h>

/**
 * @fn void lory_convert(lory_color_t *color, double hue, double range)
 * @brief Color convert function.
 *
 * @param [in,out] color    source color struct.
 * @param [in] hue          target hue, should be in range of 0.0 to 359.0.
 * @param [in] range        hue range, should be in range of 0.1 to 180.0
 */
void lory_convert(lory_color_t *color, double hue, double range);

/**
 * @fn void lory_convert_rgb_array(uint8_t *buffer, uint32_t length, double hue, double range)
 * @brief Color convert function.
 *
 * @param [in,out] buffer   RGB value's array.
 * @param [in] length       length of array.
 * @param [in] hue          target hue, should be in range of 0.0 to 359.0.
 * @param [in] range        hue range, should be in range of 0.1 to 180.0
 */
void lory_convert_rgb_array(uint8_t *buffer, uint32_t length, double hue, double range);

/**
 * @fn void lory_convert_argb_code_array(uint32_t *bitmap, uint32_t width, uint32_t height, uint32_t stride, double hue, double range)
 * @brief Color convert function.
 *
 * @param [in,out] bitmap   ARGB color code value's array.
 * @param [in] width        image width.
 * @param [in] height       image height.
 * @param [in] stride       image stride.
 * @param [in] hue          target hue, should be in range of 0.0 to 359.0.
 * @param [in] range        hue range, should be in range of 0.1 to 180.0
 */
void lory_convert_argb_code_array(uint32_t *pixels,
        uint32_t width,
        uint32_t height,
        uint32_t stridehue,
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
