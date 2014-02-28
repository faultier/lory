#include <igloo/igloo_alt.h>
using namespace igloo;

#include <lory/types.h>

Describe(color)
{
    It(can_create_from_argb_values)
    {
        lory_color_t *color = lory_createColorWithARGB(0x00, 0xFF, 0x99, 0x33);
        Assert::That((int)lory_getColorA(color), Equals(0x00));
        Assert::That((int)lory_getColorR(color), Equals(0xFF));
        Assert::That((int)lory_getColorG(color), Equals(0x99));
        Assert::That((int)lory_getColorB(color), Equals(0x33));
        Assert::That(lory_getColorH(color), EqualsWithDelta(30.0, 0.05));
        Assert::That(lory_getColorS(color), EqualsWithDelta(0.8, 0.05));
        Assert::That(lory_getColorV(color), EqualsWithDelta(1.0, 0.05));
        lory_releaseColor(color);
    }

    It(can_create_from_hsv_values)
    {
        lory_color_t *color = lory_createColorWithHSV(160.0, 0.75, 0.80);
        Assert::That((int)lory_getColorA(color), Equals(0x00));
        Assert::That((int)lory_getColorR(color), Equals(0x33));
        Assert::That((int)lory_getColorG(color), Equals(0xcc));
        Assert::That((int)lory_getColorB(color), Equals(0x99));
        Assert::That(lory_getColorH(color), Equals(160.0));
        Assert::That(lory_getColorS(color), Equals(0.75));
        Assert::That(lory_getColorV(color), Equals(0.80));
        lory_releaseColor(color);
    }
};
