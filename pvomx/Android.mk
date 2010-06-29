ifneq ($(BUILD_WITHOUT_PV),true)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

$(call add-prebuilt-files, ETC, 01_qcomm_omx.cfg)

include hardware/msm7k/pvomx/omx_core_plugin/Android.mk
endif
