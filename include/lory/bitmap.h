/* lory/bitmap.h
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
 * @defgroup Lory_bitmap bitmap
 * @{
 */

#ifndef LORY_BITMAP_H
#define LORY_BITMAP_H

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

#include <lory/definitions.h>

struct lory_color;

/**
 * @typedef LoryPixelRef
 * @brief   Pixel struct reference.
 *
 * This struct has ARGB values and HSV values.
 */
typedef struct lory_pixel * LoryPixelRef;

/**
 * @fn uint8_t LoryPixelGetAlpha(LoryPixelRef pixel)
 * @brief Return the alpha component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0 and 255
 */
uint8_t LoryPixelGetAlpha(LoryPixelRef pixel);

/**
 * @fn uint8_t LoryPixelGetRed(LoryPixelRef pixel)
 * @brief Return the red component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0 and 255
 */
uint8_t LoryPixelGetRed(LoryPixelRef pixel);

/**
 * @fn uint8_t LoryPixelGetGreen(LoryPixelRef pixel)
 * @brief Return the green component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0 and 255
 */
uint8_t LoryPixelGetGreen(LoryPixelRef pixel);

/**
 * @fn uint8_t LoryPixelGetBlue(LoryPixelRef pixel)
 * @brief Return the blue component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0 and 255
 */
uint8_t LoryPixelGetBlue(LoryPixelRef pixel);

/**
 * @fn double LoryPixelGetHue(LoryPixelRef pixel)
 * @brief Return the hue component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0.0 and 359.0
 */
double LoryPixelGetHue(LoryPixelRef pixel);

/**
 * @fn double LoryPixelGetSaturation(LoryPixelRef pixel)
 * @brief Return the saturation component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0.0 and 1.0
 */
double LoryPixelGetSaturation(LoryPixelRef pixel);

/**
 * @fn double LoryPixelGetBrightness(LoryPixelRef pixel)
 * @brief Return the brightness component of a pixel.
 *
 * @param [in] pixel Pixel
 * @return A value between 0.0 and 1.0
 */
double LoryPixelGetBrightness(LoryPixelRef pixel);

/**
 * @fn void LoryPixelSetAlpha(LoryPixelRef pixel, uint8_t alpha)
 * @brief Set the alpha component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] alpha Alpha component.
 */
void LoryPixelSetAlpha(LoryPixelRef pixel, uint8_t alpha);

/**
 * @fn void LoryPixelSetRed(LoryPixelRef pixel, uint8_t red)
 * @brief Set the red component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] red Red component.
 */
void LoryPixelSetRed(LoryPixelRef pixel, uint8_t red);

/**
 * @fn void LoryPixelSetGreen(LoryPixelRef pixel, uint8_t green)
 * @brief Set the green component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] green Green component.
 */
void LoryPixelSetGreen(LoryPixelRef pixel, uint8_t green);

/**
 * @fn void LoryPixelSetBlue(LoryPixelRef pixel, uint8_t blue)
 * @brief Set the blue component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] blue Blue component.
 */
void LoryPixelSetBlue(LoryPixelRef pixel, uint8_t blue);

/**
 * @fn void LoryPixelSetHue(LoryPixelRef pixel, double h)
 * @brief Set the hue component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] h Hue component.
 */
void LoryPixelSetHue(LoryPixelRef pixel, double h);

/**
 * @fn void LoryPixelSetSaturation(LoryPixelRef pixel, double s)
 * @brief Set the hue component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] s Saturation component.
 */
void LoryPixelSetSaturation(LoryPixelRef pixel, double s);

/**
 * @fn void LoryPixelSetBrightness(LoryPixelRef pixel, double b)
 * @brief Set the hue component of a pixel.
 *
 * @param [out] pixel Pixel
 * @param [in] b Brightness component.
 */
void LoryPixelSetBrightness(LoryPixelRef pixel, double b);

/**
 * @fn LoryPixelRef LoryPixelCreateARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
 * @brief Allocate and initialize pixel from ARGB components.
 *
 * @param [in] a Alpha component.
 * @param [in] r Red component.
 * @param [in] g Green component.
 * @param [in] b Blue component.
 * @return A pixel reference.
 */
LoryPixelRef LoryPixelCreateARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

/**
 * @fn LoryPixelRef LoryPixelCreateHSB(double h, double s, double b)
 * @brief Allocate and initialize pixel from HSB values.
 *
 * @param [in] h Hue component between 0.0 and 359.0.
 * @param [in] s Saturation component between 0.0 and 1.0.
 * @param [in] b Brightness component between 0.0 and 1.0.
 * @return A pixel reference.
 */
LoryPixelRef LoryPixelCreateHSB(double hue, double s, double b);

/**
 * @fn void LoryPixelRelease(LoryPixelRef pixel)
 * @brief Release pixel.
 *
 * @param pixel a target pixel
 */
void LoryPixelRelease(LoryPixelRef pixel);

#ifdef __cplusplus
}
#endif

#endif

/*
 * @file        lory/bitmap.h
 * @brief       Bitmap handling.
 *
 * This module provides bitmap structure and functions for creating and converting.
 *
 * @author      Taro Sako
 * @par         Revision
 * $Id$
 * @par         Copyright
 * 2014 Taro Sako All rights reserved.
 *
 * @}
 */
