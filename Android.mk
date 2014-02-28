LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lory
LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/src/lory/*.c)
LOCAL_CFLAGS    := -I$(LOCAL_PATH)/include

include $(BUILD_STATIC_LIBRARY)
