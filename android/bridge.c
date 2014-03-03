/* lory/bridge.c
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

#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <lory/lory.h>

#define  LOG_TAG    "lory"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JNIEXPORT void JNICALL Java_jp_faultier_android_lory_Lory_convertBitmap(JNIEnv *env,
    jclass class,
    jobject bitmap,
    jdouble hue,
    jdouble range)
{
    int ret;
    AndroidBitmapInfo info;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0)
    {
        LOGE("AndroidBitmap_getInfo() failed! error=%d", ret);
        return;
    }

    void* pixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed! error=%d", ret);
        return;
    }

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        LoryConvertAndroid8888(pixels,
                info.width,
                info.height,
                info.stride,
                hue,
                range);
    }
    else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565)
    {
        LoryConvertAndroid565(pixels,
                info.width,
                info.height,
                info.stride,
                hue,
                range);
    }
    else
    {
        LOGE("Bitmap format is not RGBA_8888 or RGB_565!");
        return;
    }


    AndroidBitmap_unlockPixels(env, bitmap);
}
