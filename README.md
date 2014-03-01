# Lory
[![Build Status](https://travis-ci.org/faultier/lory.png)](https://travis-ci.org/faultier/lory)

This project provides C library and tool that convert image to a selective color image.

original image:

![original](https://raw.github.com/faultier/lory/master/img/original.jpg)

selective color red:

![red](https://raw.github.com/faultier/lory/master/img/red.jpg)

selective color green:

![green](https://raw.github.com/faultier/lory/master/img/green.jpg)

selective color blue:

![blue](https://raw.github.com/faultier/lory/master/img/blue.jpg)


## Instration

If you want command line tool and shared library:

```shell
mkdir build
cd build
cmake ..
make
sudo make install
```

Or you want static library for Android:

```shell
mkdir android-build
cd android-build
# APP_ABI is optional. Default 'all'.
cmake -DLORY_ANDROID=ON -DLORY_ANDROID_APP_ABI=armeabi-v7a -DCMAKE_INSTALL_PREFIX=/path/to/android-project ..
make
make install
```

## Usage

### with jpeglib

```c
struct jpeg_decompress_struct in;
struct jpeg_compress_struct out;

// ...

if (in.out_color_space == JCS_RGB && in.output_components == 3) {
    JSAMPROW buffer = (JSAMPROW)calloc(sizeof(JSAMPLE), in.output_width * in.output_components);
    while (in.output_scanline < in.output_height)
    {
        jpeg_read_scanlines(&in, &buffer, 1);
        lory_convert_rgb_array(buffer, in.output_width, hue, range);
        jpeg_write_scanlines(&out, &buffer, 1);
    }
    free(buffer);
}
```

### with Android jnigraphics

```c
#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <lory/lory.h>

#define  LOG_TAG    "tag"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JNIEXPORT void JNICALL Java__package_name_ClassName_methodName(JNIEnv *env,
    jobject thiz,
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

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        LOGE("Bitmap format is not RGBA_8888!");
        return;
    }

    void* pixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed! error=%d", ret);
        return;
    }

    lory_convert_argb_code_array((uint32_t *)pixels,
            info.width,
            info.height,
            info.stride,
            hue,
            range);

    AndroidBitmap_unlockPixels(env, bitmap);
}
```

### loryconv

```shell
loryconv -h 0.0 -r 60.0 -o lory-red.jpg lory.jpg
```

## Todo

- iOS support
- Algorithm enhancement
- Performance tuning

## License

This project distributed under the MIT License.
http://opensource.org/licenses/MIT
