LOCAL_PATH := $(call my-dir)
PROJRCT_PATH := $(realpath $(LOCAL_PATH)/..)
DEMO_PATH := $(realpath $(LOCAL_PATH)/../..)
IRR_PATH := $(realpath $(LOCAL_PATH)/../../../..)

$(info local = $(LOCAL_PATH))
$(info demo = $(DEMO_PATH))
$(info irr = $(IRR_PATH))
$(info prj = $(PROJRCT_PATH))

include $(CLEAR_VARS)
LOCAL_MODULE := Irrlicht
LOCAL_SRC_FILES := $(IRR_PATH)/lib/Android/libIrrlicht.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := IrrDemo

LOCAL_CFLAGS := -pipe -fno-exceptions -fno-rtti -fstrict-aliasing -Wc++11-extensions

ifndef NDEBUG
LOCAL_CFLAGS += -g -D_DEBUG
else
LOCAL_CFLAGS += -fexpensive-optimizations -O3
endif

ifeq ($(TARGET_ARCH_ABI),x86)
LOCAL_CFLAGS += -fno-stack-protector
endif

LOCAL_C_INCLUDES := $(IRR_PATH)/include

LOCAL_SRC_FILES := $(DEMO_PATH)/main.cpp $(DEMO_PATH)/CDemo.cpp android_tools.cpp

LOCAL_LDLIBS := -lEGL -llog -lGLESv1_CM -lGLESv2 -lz -landroid

LOCAL_STATIC_LIBRARIES := Irrlicht android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

# copy Irrlicht data to assets

$(shell mkdir -p $(PROJRCT_PATH)/assets)
$(shell mkdir -p $(PROJRCT_PATH)/assets/media)
$(shell mkdir -p $(PROJRCT_PATH)/assets/media/Shaders)
$(shell mkdir -p $(PROJRCT_PATH)/src)
$(shell cp $(IRR_PATH)/media/Shaders/*.* $(PROJRCT_PATH)/assets/media/Shaders/)
$(shell cp $(IRR_PATH)/media/irrlicht.dat $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/map-20kdm2.pk3 $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/sydney.md2 $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/spheremap.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/sydney.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlicht2_up.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlicht2_dn.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlicht2_lf.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlicht2_rt.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlicht2_ft.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlicht2_bk.jpg $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal1.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal2.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal3.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal4.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal5.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal6.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/portal7.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/particlewhite.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/fireball.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/irrlichtlogo2.png $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/fonthaettenschweiler.bmp $(PROJRCT_PATH)/assets/media/)
$(shell cp $(IRR_PATH)/media/smoke.bmp $(PROJRCT_PATH)/assets/media/)
