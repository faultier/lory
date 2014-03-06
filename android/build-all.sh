#!/bin/sh

if [ ! "${ANDROID_NDK_ROOT}" ]; then
    echo "Please set ANDROID_NDK_ROOT"
    exit 1
fi

if [ ! -d "${ANDROID_NDK_ROOT}" ]; then
    echo "Please set ANDROID_NDK_ROOT"
    exit 1
fi


if [ $# != 2 ]; then
    echo "Usage: ${0} PATH [HOST_64BIT]"
    echo "\tPATH: location of Android application project"
    echo "\tHOST_64BITG: 'ON' or 'OFF', Default 'OFF'"
    exit 1
fi

dest=$1
if [ ! -d "$dest" ]; then
    echo "Invalid project path."
    echo "Usage: ${0} PATH [HOST_64BIT]"
    echo "\tPATH: location of Android application project"
    echo "\tHOST_64BITG: 'ON' or 'OFF', Default 'OFF'"
    exit 1
fi
expr ${1} : "/.*" > /dev/null || dest=`(cd "${dest}" && pwd)`
cwd=`dirname ${0}`
src=`(cd "${cwd}/.." && pwd)`
tmp=/tmp/lorybuild
mkdir -p $tmp

archs="arm armv7 x86 mips"
for arch in $archs; do
    mkdir -p $tmp/$arch
    cd $tmp/$arch
    cmake -DCMAKE_TOOLCHAIN_FILE="${src}/android/ndk-r9.cmake" \
        -DANDROID_NDK_ARCH=$arch \
        -DCMAKE_INSTALL_PREFIX=$dest \
        -DANDROID_NDK_HOST_64BIT=$2 \
        $src
    make install
done

rm -rf $tmp
