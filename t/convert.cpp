#include <igloo/igloo.h>
using namespace igloo;

#include <cstdint>
#include <lory/convert.h>

Context(red)
{
    lory_color_t *red;
    lory_color_t *green;
    lory_color_t *blue;
    double hue;
    double angle;

    void SetUp()
    {
        red   = lory_createColorWithARGB(0x00, 0xD9, 0x00, 0x00);
        green = lory_createColorWithARGB(0x00, 0x00, 0xB3, 0x00);
        blue  = lory_createColorWithARGB(0x00, 0x00, 0x00, 0xCC);
        hue   = 0.0;
        angle = 30.0;
    }

    void TearDown()
    {
        lory_releaseColor(red);
        lory_releaseColor(green);
        lory_releaseColor(blue);
    }

    Spec(shuold_not_convert_red_pixel)
    {
        lory_convert(red, hue, angle);
        Assert::That((int)lory_getColorR(red), Equals(0xD9));
        Assert::That((int)lory_getColorG(red), Equals(0x00));
        Assert::That((int)lory_getColorB(red), Equals(0x00));
        Assert::That(lory_getColorS(red), !Equals(0.0));
    }

    Spec(should_convert_green_pixel)
    {
        lory_convert(green, hue, angle);
        Assert::That((int)lory_getColorR(green), Equals(0xB3));
        Assert::That((int)lory_getColorG(green), Equals(0xB3));
        Assert::That((int)lory_getColorB(green), Equals(0xB3));
        Assert::That(lory_getColorS(green), Equals(0.0));
    }

    Spec(should_convert_blue_pixel)
    {
        lory_convert(blue, hue, angle);
        Assert::That((int)lory_getColorR(blue), Equals(0xCC));
        Assert::That((int)lory_getColorG(blue), Equals(0xCC));
        Assert::That((int)lory_getColorB(blue), Equals(0xCC));
        Assert::That(lory_getColorS(blue), Equals(0.0));
    }
};

Context(green)
{
    lory_color_t *red;
    lory_color_t *green;
    lory_color_t *blue;
    double hue;
    double angle;

    void SetUp()
    {
        red   = lory_createColorWithARGB(0x00, 0xD9, 0x00, 0x00);
        green = lory_createColorWithARGB(0x00, 0x00, 0xB3, 0x00);
        blue  = lory_createColorWithARGB(0x00, 0x00, 0x00, 0xCC);
        hue   = 120.0;
        angle = 30.0;
    }

    void TearDown()
    {
        lory_releaseColor(red);
        lory_releaseColor(green);
        lory_releaseColor(blue);
    }

    Spec(shuold_convert_red_pixel)
    {
        lory_convert(red, hue, angle);
        Assert::That((int)lory_getColorR(red), Equals(0xD9));
        Assert::That((int)lory_getColorG(red), Equals(0xD9));
        Assert::That((int)lory_getColorB(red), Equals(0xD9));
        Assert::That(lory_getColorS(red), Equals(0.0));
    }

    Spec(should_not_convert_green_pixel)
    {
        lory_convert(green, hue, angle);
        Assert::That((int)lory_getColorR(green), Equals(0x00));
        Assert::That((int)lory_getColorG(green), Equals(0xB3));
        Assert::That((int)lory_getColorB(green), Equals(0x00));
        Assert::That(lory_getColorS(green), !Equals(0.0));
    }

    Spec(should_convert_blue_pixel)
    {
        lory_convert(blue, hue, angle);
        Assert::That((int)lory_getColorR(blue), Equals(0xCC));
        Assert::That((int)lory_getColorG(blue), Equals(0xCC));
        Assert::That((int)lory_getColorB(blue), Equals(0xCC));
        Assert::That(lory_getColorS(blue), Equals(0.0));
    }
};

Context(blue)
{
    lory_color_t *red;
    lory_color_t *green;
    lory_color_t *blue;
    double hue;
    double angle;

    void SetUp()
    {
        red   = lory_createColorWithARGB(0x00, 0xD9, 0x00, 0x00);
        green = lory_createColorWithARGB(0x00, 0x00, 0xB3, 0x00);
        blue  = lory_createColorWithARGB(0x00, 0x00, 0x00, 0xCC);
        hue   = 240.0;
        angle = 30.0;
    }

    void TearDown()
    {
        lory_releaseColor(red);
        lory_releaseColor(green);
        lory_releaseColor(blue);
    }

    Spec(shuold_convert_red_pixel)
    {
        lory_convert(red, hue, angle);
        Assert::That((int)lory_getColorR(red), Equals(0xD9));
        Assert::That((int)lory_getColorG(red), Equals(0xD9));
        Assert::That((int)lory_getColorB(red), Equals(0xD9));
        Assert::That(lory_getColorS(red), Equals(0.0));
    }

    Spec(should_convert_green_pixel)
    {
        lory_convert(green, hue, angle);
        Assert::That((int)lory_getColorR(green), Equals(0xB3));
        Assert::That((int)lory_getColorG(green), Equals(0xB3));
        Assert::That((int)lory_getColorB(green), Equals(0xB3));
        Assert::That(lory_getColorS(green), Equals(0.0));
    }

    Spec(should_not_convert_blue_pixel)
    {
        lory_convert(blue, hue, angle);
        Assert::That((int)lory_getColorR(blue), Equals(0x00));
        Assert::That((int)lory_getColorG(blue), Equals(0x00));
        Assert::That((int)lory_getColorB(blue), Equals(0xCC));
        Assert::That(lory_getColorS(blue), !Equals(0.0));
    }
};

Context(rgb_array)
{
    Spec(can_convert_rgb_array)
    {
        uint8_t scanline[9] = {
            0xD9, 0x00, 0x00, // red
            0x00, 0xB3, 0x00, // green
            0x00, 0x00, 0xCC  // blue
        };

        lory_convert_rgb_array(scanline, 3, 0.0, 30.0);

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

Context(argb_code_array)
{
    Spec(can_convert_argb_code_array)
    {
        uint32_t pixels[16] = {
            // first line
            0x000000D9, // red
            0x0000B300, // green
            0x00CC0000, // blue
            0x800000FF, // alpha
            0x8000FFFF,
            0x80FFFFFF,

            // second line
            0x000000D9,
            0x0000B300,
            0x00CC0000,
            0x8000FF00,
            0x80FFFF00,
            0x80FF0000
        };

        int width    = 6;
        int height   = 2;
        int stride   = 6*4;
        double hue   = 0.0;
        double range = 30.0;

        lory_convert_rgba_code_array(pixels, width, height, stride, hue, range);

        // red color should not be converted.
        Assert::That(pixels[0], Equals(0x000000D9));
        Assert::That(pixels[6], Equals(0x000000D9));

        // green color should be converted.
        Assert::That(pixels[1], Equals(0x00B3B3B3));
        Assert::That(pixels[7], Equals(0x00B3B3B3));

        // blue color should be converted.
        Assert::That(pixels[2], Equals(0x00CCCCCC));
        Assert::That(pixels[8], Equals(0x00CCCCCC));

        // alpha value should be not changed.
        Assert::That((pixels[3] & 0xFF000000), Equals(0x80000000));
        Assert::That((pixels[4] & 0xFF000000), Equals(0x80000000));
        Assert::That((pixels[5] & 0xFF000000), Equals(0x80000000));
        Assert::That((pixels[9] & 0xFF000000), Equals(0x80000000));
        Assert::That((pixels[10] & 0xFF000000), Equals(0x80000000));
        Assert::That((pixels[11] & 0xFF000000), Equals(0x80000000));
    }
};
