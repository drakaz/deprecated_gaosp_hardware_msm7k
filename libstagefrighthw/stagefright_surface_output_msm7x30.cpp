/*
 * Copyright (C) 2009 The Android Open Source Project
 * Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <media/stagefright/HardwareAPI.h>
#include "QComHardwareOverlayRenderer.h"
#define LOG_TAG "StagefrightSurfaceOutput7630"
#include <utils/Log.h>

using android::sp;
using android::ISurface;
using android::VideoRenderer;

VideoRenderer *createRenderer(
        const sp<ISurface> &surface,
        const char *componentName,
        OMX_COLOR_FORMATTYPE colorFormat,
        size_t displayWidth, size_t displayHeight,
        size_t decodedWidth, size_t decodedHeight) {
    using android::QComHardwareOverlayRenderer;

    if (colorFormat == OMX_COLOR_FormatYUV420SemiPlanar
        && !strncmp(componentName, "OMX.qcom.video.decoder.", 23)) {
        LOGV("StagefrightSurfaceOutput7x30::createRenderer");
        return new QComHardwareOverlayRenderer(
                surface, displayWidth, displayHeight,
                decodedWidth, decodedHeight);
    }

    return NULL;
}
