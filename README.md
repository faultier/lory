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
cmake -DLORY_ANDROID=ON -DCMAKE_INSTALL_PREFIX=/path/to/android-project ..
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

### with Android bridge

```java
import jp.faultier.android.lory;
import android.graphics.Bitmap;

// Bitmap shuould be mutable and ARGB_8888
Lory.convertBitmap(bitmap, hue, range);

// or use preset
Lory.convertBitmap(bitmap, Lory.Preset.RED);
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
