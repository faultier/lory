#include <igloo/igloo_alt.h>
#include <iostream>
#include <cmath>
using namespace igloo;

#include <lory/convert.h>
#include "fixtures.h"

When(target_is_red)
{
    Then(should_not_convert_red_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0xD9, 0x00, 0x00, 0.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xD9));
        Assert::That(dest[1], Equals(0x00));
        Assert::That(dest[2], Equals(0x00));
    }

    Then(should_convert_green_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0x00, 0xB3, 0x00, 0.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xB3));
        Assert::That(dest[1], Equals(0xB3));
        Assert::That(dest[2], Equals(0xB3));
    }

    Then(should_convert_blue_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0x00, 0x00, 0xCC, 0.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xCC));
        Assert::That(dest[1], Equals(0xCC));
        Assert::That(dest[2], Equals(0xCC));
    }
};

When(target_is_green)
{
    Then(should_convert_red_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0xD9, 0x00, 0x00, 120.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xD9));
        Assert::That(dest[1], Equals(0xD9));
        Assert::That(dest[2], Equals(0xD9));
    }

    Then(should_not_convert_green_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0x00, 0xB3, 0x00, 120.0, 60.0, dest);
        Assert::That(dest[0], Equals(0x00));
        Assert::That(dest[1], Equals(0xB3));
        Assert::That(dest[2], Equals(0x00));
    }

    Then(should_convert_blue_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0x00, 0x00, 0xCC, 120.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xCC));
        Assert::That(dest[1], Equals(0xCC));
        Assert::That(dest[2], Equals(0xCC));
    }
};

When(target_is_blue)
{
    Then(should_convert_red_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0xD9, 0x00, 0x00, 240.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xD9));
        Assert::That(dest[1], Equals(0xD9));
        Assert::That(dest[2], Equals(0xD9));
    }

    Then(should_convert_green_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0x00, 0xB3, 0x00, 240.0, 60.0, dest);
        Assert::That(dest[0], Equals(0xB3));
        Assert::That(dest[1], Equals(0xB3));
        Assert::That(dest[2], Equals(0xB3));
    }

    Then(should_not_convert_blue_pixel)
    {
        uint8_t dest[3];
        LoryConvert(0x00, 0x00, 0xCC, 240.0, 60.0, dest);
        Assert::That(dest[0], Equals(0x00));
        Assert::That(dest[1], Equals(0x00));
        Assert::That(dest[2], Equals(0xCC));
    }
};

When(RGB_8_SPLIT)
{
    Then(shuold_convert_rgb_array)
    {
        uint16_t size = 360;
        uint8_t **bitmap;
        LoryTestCreateBitmap((void **)&bitmap, size, LORY_RGB_8_SPLIT);
        uint8_t *scanline = bitmap[0];
        LoryConvertJpeglib888(scanline, size, 30.0, 60.0);

        int border = round(60*(size/360.0));
        for (int i = 0; i < size; i++)
        {
            uint8_t r = scanline[i*3];
            uint8_t g = scanline[i*3+1];
            uint8_t b = scanline[i*3+2];

            if (i <= border)
            {
                // target hue range should not be converted.
                Assert::That((int)r, !(Equals((int)g) && Equals((int)b)));
            }
            else {
                // other pixels should be converted.
                Assert::That((int)r, Equals((int)g) && Equals((int)b));
            }
        }

        LoryTestReleaseBitmap(bitmap, size, LORY_RGB_8_SPLIT);
    }
};

When(ABGR_8888)
{
    Then(should_convert_rgba_code_array)
    {
        uint16_t size = 360;
        uint32_t *bitmap;
        LoryTestCreateBitmap((void **)&bitmap, size, LORY_ABGR_8888);

        LoryConvertAndroid8888(bitmap, size, size, size*sizeof(uint32_t), 30.0, 60.0);

        int border = round(60*(size/360.0));
        for (int i = 0; i < size; i++)
        {
            uint32_t pixel = bitmap[i];

            if (i <= border)
            {
                // target hue range should not be converted.
                Assert::That((pixel & 0x000000FF),
                        !(Equals((pixel & 0x0000FF00) >> 8) && Equals((pixel & 0x00FF0000) >> 16)));
            }
            else {
                // other pixels should be converted.
                Assert::That((pixel & 0x000000FF),
                        Equals((pixel & 0x0000FF00) >> 8) && Equals((pixel & 0x00FF0000) >> 16));
            }
        }

        LoryTestReleaseBitmap((void *)bitmap, size, LORY_ABGR_8888);
    }
};

When(ANDROID_565)
{
    Then(should_convert_rgb_code_array)
    {
        uint16_t size = 360;
        uint16_t *bitmap;
        LoryTestCreateBitmap((void **)&bitmap, size, LORY_RGB_565);

        LoryConvertAndroid565(bitmap, size, size, size*sizeof(uint16_t), 60.0, 60.0);

        int border1 = round(30*(size/360.0));
        int border2 = round(90*(size/360.0));
        for (int i = 0; i < size; i++)
        {
            uint16_t pixel = bitmap[i];

            uint8_t r = (uint8_t) (((pixel & 0xF800) >> 11) / 31.0 * 255.0);
            uint8_t g = (uint8_t) (((pixel & 0x07E0) >> 5) / 63.0 * 255.0);
            uint8_t b = (uint8_t) ((pixel & 0x001F) / 31.0 * 255.0);

            if (i > border1 + 2 && i < border2 - 2)
            {
                // target hue range should not be converted.
                Assert::That((int)r, !(Equals((int)g) && Equals((int)b)));
            }
            else if (i < border1 - 2 || i > border2 + 2)
            {
                // other pixels should be converted.
                Assert::That((int)r, Equals((int)g) && Equals((int)b));
            }
        }

        LoryTestReleaseBitmap((void *)bitmap, size, LORY_RGB_565);
    }
};
