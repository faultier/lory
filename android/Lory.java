/* Lory JNI Bridge
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


package jp.faultier.android.lory;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;

public class Lory {
    public enum Preset {
        RED(0.0, 60.0), YELLOW(60.0, 60.0), GREEN(120.0, 60.0),
        CYAN(180.0, 60.0), BLUE(240.0, 60.0), MAGENTA(300.0, 60.0),
        R2Y(30.0, 60.0), Y2G(90.0, 60.0), G2C(150.0, 60.0),
        C2B(210.0, 60.0), B2M(270.0, 60.0), M2R(330.0, 60.0);

        private double hue;
        private double range;

        private Preset(double hue, double range) {
            this.hue = hue;
            this.range = range;
        }

        public double getHue() { return hue; }
        public double getRange() { return range; }
    }

    public static native void convertBitmap(Bitmap bitmap, double hue, double range);

    public static void convertBitmap(Bitmap bitmap, Preset preset) {
        convertBitmap(bitmap, preset.getHue(), preset.getRange());
    }

    private double hue = 0.0;
    private double range = 60.0;

    public Lory() {}

    public Lory(double hue, double range) {
        this.hue = hue;
        this.range = range;
    }

    public Lory(Preset preset) {
        this(preset.getHue(), preset.getRange());
    }

    public Bitmap convertBitmap(Bitmap src) {
        Bitmap dest = src;
        if (dest.getConfig() != Bitmap.Config.ARGB_8888 || !dest.isMutable()) {
            dest = src.copy(Bitmap.Config.ARGB_8888, true);
        }
        convertBitmap(dest, hue, range);
        return dest;
    }

    public Bitmap convertResource(Context context, int resId) {
        BitmapDrawable drawable = (BitmapDrawable) context.getResources().getDrawable(resId);
        return convertBitmap(drawable.getBitmap());
    }

    public double getHue() {
        return hue;
    }

    public void setHue(double hue) {
        this.hue = hue;
    }

    public double getRange() {
        return range;
    }

    public void setRange(double range) {
        this.range = range;
    }

    static {
        System.loadLibrary("lory");
    }
}
