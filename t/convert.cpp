#include <igloo/igloo_alt.h>
using namespace igloo;

#include <lory/convert.h>

When(red_target)
{
    LoryPixelRef red;
    LoryPixelRef green;
    LoryPixelRef blue;
    double hue;
    double range;

    void SetUp()
    {
        red   = LoryPixelCreateARGB(0x00, 0xD9, 0x00, 0x00);
        green = LoryPixelCreateARGB(0x00, 0x00, 0xB3, 0x00);
        blue  = LoryPixelCreateARGB(0x00, 0x00, 0x00, 0xCC);
        hue   = 0.0;
        range = 30.0;
    }

    void TearDown()
    {
        LoryPixelRelease(red);
        LoryPixelRelease(green);
        LoryPixelRelease(blue);
    }

    Then(shuold_not_convert_red_pixel)
    {
        LoryConvert(red, red, hue, range);
        Assert::That((int)LoryPixelGetRed(red), Equals(0xD9));
        Assert::That((int)LoryPixelGetGreen(red), Equals(0x00));
        Assert::That((int)LoryPixelGetBlue(red), Equals(0x00));
        Assert::That(LoryPixelGetSaturation(red), !Equals(0.0));
    }

    Then(shuold_convert_green_pixel)
    {
        LoryConvert(green, green, hue, range);
        Assert::That((int)LoryPixelGetRed(green), Equals(0xB3));
        Assert::That((int)LoryPixelGetGreen(green), Equals(0xB3));
        Assert::That((int)LoryPixelGetBlue(green), Equals(0xB3));
        Assert::That(LoryPixelGetSaturation(green), Equals(0.0));
    }

    Then(shuold_convert_blue_pixel)
    {
        LoryConvert(blue, blue, hue, range);
        Assert::That((int)LoryPixelGetRed(blue), Equals(0xCC));
        Assert::That((int)LoryPixelGetGreen(blue), Equals(0xCC));
        Assert::That((int)LoryPixelGetBlue(blue), Equals(0xCC));
        Assert::That(LoryPixelGetSaturation(blue), Equals(0.0));
    }
};

When(green_target)
{
    LoryPixelRef red;
    LoryPixelRef green;
    LoryPixelRef blue;
    double hue;
    double range;

    void SetUp()
    {
        red   = LoryPixelCreateARGB(0x00, 0xD9, 0x00, 0x00);
        green = LoryPixelCreateARGB(0x00, 0x00, 0xB3, 0x00);
        blue  = LoryPixelCreateARGB(0x00, 0x00, 0x00, 0xCC);
        hue   = 120.0;
        range = 30.0;
    }

    void TearDown()
    {
        LoryPixelRelease(red);
        LoryPixelRelease(green);
        LoryPixelRelease(blue);
    }

    Then(shuold_convert_red_pixel)
    {
        LoryConvert(red, red, hue, range);
        Assert::That((int)LoryPixelGetRed(red), Equals(0xD9));
        Assert::That((int)LoryPixelGetGreen(red), Equals(0xD9));
        Assert::That((int)LoryPixelGetBlue(red), Equals(0xD9));
        Assert::That(LoryPixelGetSaturation(red), Equals(0.0));
    }

    Then(shuold_not_convert_green_pixel)
    {
        LoryConvert(green, green, hue, range);
        Assert::That((int)LoryPixelGetRed(green), Equals(0x00));
        Assert::That((int)LoryPixelGetGreen(green), Equals(0xB3));
        Assert::That((int)LoryPixelGetBlue(green), Equals(0x00));
        Assert::That(LoryPixelGetSaturation(green), !Equals(0.0));
    }

    Then(shuold_convert_blue_pixel)
    {
        LoryConvert(blue, blue, hue, range);
        Assert::That((int)LoryPixelGetRed(blue), Equals(0xCC));
        Assert::That((int)LoryPixelGetGreen(blue), Equals(0xCC));
        Assert::That((int)LoryPixelGetBlue(blue), Equals(0xCC));
        Assert::That(LoryPixelGetSaturation(blue), Equals(0.0));
    }
};

When(blue_target)
{
    LoryPixelRef red;
    LoryPixelRef green;
    LoryPixelRef blue;
    double hue;
    double range;

    void SetUp()
    {
        red   = LoryPixelCreateARGB(0x00, 0xD9, 0x00, 0x00);
        green = LoryPixelCreateARGB(0x00, 0x00, 0xB3, 0x00);
        blue  = LoryPixelCreateARGB(0x00, 0x00, 0x00, 0xCC);
        hue   = 240.0;
        range = 30.0;
    }

    void TearDown()
    {
        LoryPixelRelease(red);
        LoryPixelRelease(green);
        LoryPixelRelease(blue);
    }

    Then(shuold_convert_red_pixel)
    {
        LoryConvert(red, red, hue, range);
        Assert::That((int)LoryPixelGetRed(red), Equals(0xD9));
        Assert::That((int)LoryPixelGetGreen(red), Equals(0xD9));
        Assert::That((int)LoryPixelGetBlue(red), Equals(0xD9));
        Assert::That(LoryPixelGetSaturation(red), Equals(0.0));
    }

    Then(shuold_convert_green_pixel)
    {
        LoryConvert(green, green, hue, range);
        Assert::That((int)LoryPixelGetRed(green), Equals(0xB3));
        Assert::That((int)LoryPixelGetGreen(green), Equals(0xB3));
        Assert::That((int)LoryPixelGetBlue(green), Equals(0xB3));
        Assert::That(LoryPixelGetSaturation(green), Equals(0.0));
    }

    Then(shuold_not_convert_blue_pixel)
    {
        LoryConvert(blue, blue, hue, range);
        Assert::That((int)LoryPixelGetRed(blue), Equals(0x00));
        Assert::That((int)LoryPixelGetGreen(blue), Equals(0x00));
        Assert::That((int)LoryPixelGetBlue(blue), Equals(0xCC));
        Assert::That(LoryPixelGetSaturation(blue), !Equals(0.0));
    }
};

When(JPEGLIB_888)
{
    Then(shuold_convert_rgb_array)
    {
        uint8_t scanline[9] = {
            0xD9, 0x00, 0x00, // red
            0x00, 0xB3, 0x00, // green
            0x00, 0x00, 0xCC  // blue
        };

        LoryConvertJpeglib888(scanline, 3, 0.0, 30.0);

        // red color should not be converted.
        Assert::That((int)scanline[0], Equals(0xD9));
        Assert::That((int)scanline[1], Equals(0x00));
        Assert::That((int)scanline[2], Equals(0x00));

        // green color should be converted.
        Assert::That((int)scanline[3], Equals(0xB3));
        Assert::That((int)scanline[4], Equals(0xB3));
        Assert::That((int)scanline[5], Equals(0xB3));

        // blue color should be converted.
        Assert::That((int)scanline[6], Equals(0xCC));
        Assert::That((int)scanline[7], Equals(0xCC));
        Assert::That((int)scanline[8], Equals(0xCC));
    }
};

When(ANDROID_8888)
{
    Then(should_convert_rgba_code_array)
    {
        uint32_t pixels[6] = {
            // first line
            0xFF0000D9, // red
            0xFF00B300, // green
            0xFFCC0000, // blue

            // second line
            0xFF0000D9, // red
            0xFF00B300, // green
            0xFFCC0000, // blue
        };

        int width    = 3;
        int height   = 2;
        int stride   = 3*4;
        double hue   = 0.0;
        double range = 30.0;

        LoryConvertAndroid8888(pixels, width, height, stride, hue, range);

        // red color should not be converted.
        Assert::That(pixels[0], Equals(0xFF0000D9));
        Assert::That(pixels[3], Equals(0xFF0000D9));

        // green color should be converted.
        Assert::That(pixels[1], Equals(0xFFB3B3B3));
        Assert::That(pixels[4], Equals(0xFFB3B3B3));

        // blue color should be converted.
        Assert::That(pixels[2], Equals(0xFFCCCCCC));
        Assert::That(pixels[5], Equals(0xFFCCCCCC));
    }
};
