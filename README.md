# Lory

This project provides C library and tool that convert image to a selective color image.

original image:

![original](https://raw.github.com/faultier/lory/master/img/original.jpg)

selective color red:

![red](https://raw.github.com/faultier/lory/master/img/red.jpg)

selective color green:

![red](https://raw.github.com/faultier/lory/master/img/green.jpg)

selective color blue:

![red](https://raw.github.com/faultier/lory/master/img/blue.jpg)


## Instration

If you want command line tool and shared library:

```shell
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ sudo make install
```

Or you want static library for Android:

```shell
    $ mkdir android-build
    $ cd android-build
    # APP_ABI is optional. Default 'all'.
    $ cmake -DLORY_ANDROID=ON -DLORY_ANDROID_APP_ABI=armeabi-v7a -DCMAKE_INSTALL_PREFIX=/path/to/android-project ..
    $ make
    $ make install
```

### Usage

```shell
    $ loryconv -h 0.0 -r 60.0 -o lory-red.jpg lory.jpg
```
