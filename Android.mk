#
# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

common_msm_dirs := libcopybit liblights libopencorehw librpc libstagefrighthw pvomx
msm7k_dirs := $(common_msm_dirs) boot libgralloc libaudio libcamera2
msm7k_adreno_dirs := $(common_msm_dirs) boot libgralloc-qsd8k libaudio
qsd8k_dirs := $(common_msm_dirs) libgralloc-qsd8k libaudio-qsd8k dspcrashd
#msm7x30_dirs := $(common_msm_dirs) libgralloc-qsd8k libaudio-msm7x30 liboverlay
msm7x30_dirs := $(common_msm_dirs) liboverlay libaudio-msm7x30 libgralloc-qsd8k

ifeq ($(TARGET_BOARD_PLATFORM),qsd8k)
    ### QSD8k
    include $(call all-named-subdir-makefiles,$(qsd8k_dirs))
else ifeq ($(TARGET_BOOTLOADER_BOARD_NAME),adq)
    ### "adq" board (7x25)
    include $(call all-named-subdir-makefiles,$(common_msm_dirs))
else ifeq ($(TARGET_BOARD_PLATFORM),msm7x30)
    ### MSM7x30
    include $(call all-named-subdir-makefiles,$(msm7x30_dirs))
else ifeq ($(TARGET_BOARD_PLATFORM_GPU),qcom-adreno200)
    ### MSM7k with Adreno GPU
    include $(call all-named-subdir-makefiles,$(msm7k_adreno_dirs))
else ifeq ($(TARGET_BOARD_PLATFORM),msm7k)
    ### Other MSM7k
    include $(call all-named-subdir-makefiles,$(msm7k_dirs))
endif
