/*
 * Copyright (C) 2019 The LineageOS Project
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

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"
#include <android-base/logging.h>
#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    {0, {250, "Two fingers down swipe", "/proc/touchpanel/double_swipe_enable"}},
    {1, {251, "Up arrow", "/proc/touchpanel/up_arrow_enable"}},
    {2, {254, "Right arrow", "/proc/touchpanel/right_arrow_enable"}},
    {3, {252, "Down arrow", "/proc/touchpanel/down_arrow_enable"}},
    {4, {253, "Left arrow", "/proc/touchpanel/left_arrow_enable"}},
    {5, {255, "One finger up swipe", "/proc/touchpanel/up_swipe_enable"}},
    {6, {258, "One finger right swipe", "/proc/touchpanel/right_swipe_enable"}},
    {7, {256, "One finger down swipe", "/proc/touchpanel/down_swipe_enable"}},
    {8, {257, "One finger left swipe", "/proc/touchpanel/left_swipe_enable"}},
    {9, {247, "Letter M", "/proc/touchpanel/letter_m_enable"}},
    {10, {249, "Letter O", "/proc/touchpanel/letter_o_enable"}},
    {11, {246, "Letter W", "/proc/touchpanel/letter_w_enable"}},
};

Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(
    const ::vendor::lineage::touch::V1_0::Gesture& gesture, bool enabled) {
    const auto entry = kGestureInfoMap.find(gesture.id);
    if (entry == kGestureInfoMap.end()) {
        return false;
    }

    std::ofstream file(entry->second.path);
    file << (enabled ? "1" : "0");
    LOG(DEBUG) << "Wrote file " << entry->second.path << " fail " << file.fail();
    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor