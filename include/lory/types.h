/* lory/types.h
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
 * @defgroup Lory_types types
 * @{
 */

#ifndef LORY_TYPES_H
#define LORY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct lory_color;

/**
 * @typedef lory_color_t
 * @brief   a color struct type.
 *
 * This struct has ARGB values and HSV values.
 */
typedef struct lory_color lory_color_t;

/**
 * @fn uint8_t lory_getColorA(lory_color_t *color)
 * @brief accessor of ARGB alpha value.
 *
 * @param [in] color a color struct.
 *
 * @return alpha value of the color.
 */
uint8_t lory_getColorA(lory_color_t *color);

/**
 * @fn uint8_t lory_getColorR(lory_color_t *color)
 * @brief accessor of ARGB red value.
 *
 * @param [in] color a color struct.
 *
 * @return red value of the color.
 */
uint8_t lory_getColorR(lory_color_t *color);

/**
 * @fn uint8_t lory_getColorG(lory_color_t *color)
 * @brief accessor of ARGB green value.
 *
 * @param [in] color a color struct.
 *
 * @return green value of the color.
 */
uint8_t lory_getColorG(lory_color_t *color);

/**
 * @fn uint8_t lory_getColorB(lory_color_t *color)
 * @brief Accessor of ARGB blue value.
 *
 * @param [in] color a color struct.
 *
 * @return blue value of the color.
 */
uint8_t lory_getColorB(lory_color_t *color);

/**
 * @fn double lory_getColorH(lory_color_t *color)
 * @brief accessor of HSV-Hue.
 *
 * @param [in] color a color struct.
 *
 * @return hue of the color.
 */
double lory_getColorH(lory_color_t *color);

/**
 * @fn double lory_getColorS(lory_color_t *color)
 * @brief accessor of HSV-Saturation.
 *
 * @param [in] color a color struct.
 *
 * @return saturation of the color.
 */
double lory_getColorS(lory_color_t *color);

/**
 * @fn double lory_getColorV(lory_color_t *color)
 * @brief accessor of HSV-Value.
 *
 * @param [in] color a color struct.
 *
 * @return value of the color.
 */
double lory_getColorV(lory_color_t *color);

/**
 * @fn void lory_setColorA(lory_color_t *color, uint8_t alpha)
 * @brief accessor of ARGB alpha value.
 *
 * @param [out] color a color struct.
 * @param [in] alpha alpha.
 */
void lory_setColorA(lory_color_t *color, uint8_t alpha);

/**
 * @fn void lory_setColorR(lory_color_t *color, uint8_t red)
 * @brief accessor of ARGB red value.
 *
 * @param [out] color a color struct.
 * @param [in] red red.
 */
void lory_setColorR(lory_color_t *color, uint8_t red);

/**
 * @fn void lory_setColorG(lory_color_t *color, uint8_t green)
 * @brief accessor of ARGB green value.
 *
 * @param [out] color a color struct.
 * @param [in] green green.
 */
void lory_setColorG(lory_color_t *color, uint8_t green);

/**
 * @fn uint8_t lory_setColorB(lory_color_t *color, uint8_t blue)
 * @brief Accessor of ARGB blue value.
 *
 * @param [out] color a color struct.
 * @param [in] blue blue.
 */
void lory_setColorB(lory_color_t *color, uint8_t blue);

/**
 * @fn void lory_setColorH(lory_color_t *color, double hue)
 * @brief accessor of HSV-Hue.
 *
 * @param [out] color a color struct.
 * @param [in] hue hue.
 */
void lory_setColorH(lory_color_t *color, double hue);

/**
 * @fn void lory_setColorS(lory_color_t *color, double sat)
 * @brief accessor of HSV-Saturation.
 *
 * @param [out] color a color struct.
 * @param [in] sat saturation.
 */
void lory_setColorS(lory_color_t *color, double sat);

/**
 * @fn void lory_setColorV(lory_color_t *color, double val)
 * @brief accessor of HSV-Value.
 *
 * @param [out] color a color struct.
 * @param [in] val value.
 */
void lory_setColorV(lory_color_t *color, double val);

/**
 * @fn lory_color_t * lory_createColorWithARGB(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
 * @brief allocate and initialize color struct from ARGB values.
 *
 * @param [in] alpha    alpha value.
 * @param [in] red      red value.
 * @param [in] green    green value.
 * @param [in] blue     blue value.
 *
 * @return a color struct.
 */
lory_color_t * lory_createColorWithARGB(uint8_t alpha,
        uint8_t red,
        uint8_t green,
        uint8_t blue);

/**
 * @fn lory_color_t * lory_createColorWithHSV(double hue, double sat, double val)
 * @brief allocate and initialize color struct from HSV values.
 *
 * @param [in] hue  hue, shuould be in range of 0.0 to 359.0.
 * @param [in] sat  saturation, should be in range of 0.0 to 1.0.
 * @param [in] val  value, should be in range of 0.0 to 1.0.
 *
 * @return a color struct.
 */
lory_color_t * lory_createColorWithHSV(double hue,
        double sat,
        double val);

/**
 * @fn void lory_releaseColor(lory_color_t *color)
 * @brief release color struct.
 *
 * @param color a color struct.
 */
void lory_releaseColor(lory_color_t *color);

#ifdef __cplusplus
}
#endif

#endif

/*
 * @file        lory/types.h
 * @brief       Type definitions and accessor functions.
 *
 * This module provides color struct and that accessor functions.
 *
 * @author      Taro Sako
 * @par         Revision
 * $Id$
 * @par         Copyright
 * 2014 Taro Sako All rights reserved.
 *
 * @}
 */
