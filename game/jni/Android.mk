LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := flgame
LOCAL_SRC_FILES := main.cpp

LOCAL_LDLIBS    := -lGLESv3 -lEGL -llog -landroid
LOCAL_CPPFLAGS  := -std=c++17 -O2 -fvisibility=hidden -ffunction-sections -fdata-sections -DOBFUSCATE
LOCAL_LDFLAGS   := -Wl,--gc-sections -Wl,--strip-all

include $(BUILD_SHARED_LIBRARY)
