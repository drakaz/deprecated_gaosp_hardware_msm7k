
ifneq ($(BUILD_TINY_ANDROID),true)

LOCAL_PATH := $(call my-dir)

# ---------------------------------------------------------------------------------
#             Make the Shared library libaudiopolicy
# ---------------------------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_SRC_FILES := AudioPolicyManager.cpp
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libmedia
LOCAL_MODULE := libaudiopolicy

LOCAL_STATIC_LIBRARIES := libaudiopolicybase

ifeq ($(BOARD_HAVE_BLUETOOTH),true)
  LOCAL_CFLAGS += -DWITH_A2DP
endif

ifeq ($(BOARD_HAVE_FM_RADIO),true)
  LOCAL_CFLAGS += -DHAVE_FM_RADIO
endif

include $(BUILD_SHARED_LIBRARY)

# ---------------------------------------------------------------------------------
#             Make the Shared library libaudio
# ---------------------------------------------------------------------------------

ifneq ($(BOARD_PREBUILT_LIBAUDIO),true)

include $(CLEAR_VARS)

LOCAL_MODULE := libaudio
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libmedia
LOCAL_SHARED_LIBRARIES += libhardware_legacy
LOCAL_SHARED_LIBRARIES += libaudioalsa

ifeq ($TARGET_OS)-$(TARGET_SIMULATOR),linux-true)
LOCAL_LDLIBS += -ldl
endif
ifneq ($(TARGET_SIMULATOR),true)
LOCAL_SHARED_LIBRARIES += libdl
endif
ifeq ($(BOARD_HAVE_BLUETOOTH),true)
LOCAL_SHARED_LIBRARIES += liba2dp
endif

LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/mm-audio/audio-alsa
LOCAL_SRC_FILES += AudioHardware.cpp
LOCAL_CFLAGS += -fno-short-enums
LOCAL_STATIC_LIBRARIES += libaudiointerface

include $(BUILD_SHARED_LIBRARY)

endif # not BOARD_PREBUILT_LIBAUDIO

endif # not BUILD_TINY_ANDROID

