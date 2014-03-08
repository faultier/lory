#include <igloo/igloo_alt.h>
using namespace igloo;

#include <lory/convert.h>

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

When(ANDROID_565)
{
    Then(should_convert_rgba_code_array)
    {
        uint16_t pixels[6] = {
            // first line
            (31 << 11), // red
            (63 << 5),  // green
            31,         // blue

            // second line
            (31 << 11),
            (63 << 5),
            31,
        };

        int width    = 3;
        int height   = 2;
        int stride   = 3*2;
        double hue   = 0.0;
        double range = 30.0;

        LoryConvertAndroid565(pixels, width, height, stride, hue, range);

        // red color should not be converted.
        Assert::That(pixels[0], Equals((31 << 11)));
        Assert::That(pixels[3], Equals((31 << 11)));

        // green color should be converted.
        Assert::That(pixels[1], !Equals((63 << 5)));
        Assert::That(pixels[4], !Equals((63 << 5)));

        // blue color should be converted.
        Assert::That(pixels[2], !Equals(31));
        Assert::That(pixels[5], !Equals(31));
    }
};
