#include <igloo/igloo_alt.h>
using namespace igloo;

#include <lory/bitmap.h>

Describe(pixel)
{
    It(can_create_from_argb_values)
    {
        LoryPixelRef pixel = LoryPixelCreateARGB(0xFF, 0xFF, 0x99, 0x33);
        Assert::That((int)LoryPixelGetAlpha(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetRed(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetGreen(pixel), Equals(0x99));
        Assert::That((int)LoryPixelGetBlue(pixel), Equals(0x33));
        Assert::That(LoryPixelGetHue(pixel),
                EqualsWithDelta(30.0, 0.05));
        Assert::That(LoryPixelGetSaturation(pixel),
                EqualsWithDelta(0.8, 0.05));
        Assert::That(LoryPixelGetBrightness(pixel), Equals(1.0));
        LoryPixelRelease(pixel);
    }

    It(can_create_from_hsb_values)
    {
        LoryPixelRef pixel = LoryPixelCreateHSB(160.0, 0.75, 0.80);
        Assert::That((int)LoryPixelGetAlpha(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetRed(pixel), Equals(0x33));
        Assert::That((int)LoryPixelGetGreen(pixel), Equals(0xCC));
        Assert::That((int)LoryPixelGetBlue(pixel), Equals(0x99));
        Assert::That(LoryPixelGetHue(pixel),
                EqualsWithDelta(160.0, 0.05));
        Assert::That(LoryPixelGetSaturation(pixel),
                EqualsWithDelta(0.75, 0.05));
        Assert::That(LoryPixelGetBrightness(pixel),
                EqualsWithDelta(0.80, 0.05));
        LoryPixelRelease(pixel);
    }

    It(can_modify)
    {
        LoryPixelRef pixel = LoryPixelCreateARGB(0xFF, 0x00, 0x00, 0xFF);
        LoryPixelSetAlpha(pixel, 0x80);
        LoryPixelSetRed(pixel, 0xFF);
        LoryPixelSetGreen(pixel, 0xFF);
        LoryPixelSetBlue(pixel, 0x00);

        Assert::That((int)LoryPixelGetAlpha(pixel), Equals(0x80));
        Assert::That((int)LoryPixelGetRed(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetGreen(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetBlue(pixel), Equals(0x00));
        Assert::That(LoryPixelGetHue(pixel), Equals(60.0));

        LoryPixelSetHue(pixel, 0.0);
        Assert::That((int)LoryPixelGetRed(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetGreen(pixel), Equals(0x00));
        Assert::That((int)LoryPixelGetBlue(pixel), Equals(0x00));

        LoryPixelSetSaturation(pixel, 0.0);
        Assert::That((int)LoryPixelGetRed(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetGreen(pixel), Equals(0xFF));
        Assert::That((int)LoryPixelGetBlue(pixel), Equals(0xFF));
    }
};
