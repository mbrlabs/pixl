//
// Copyright (c) 2017. See AUTHORS file.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <cstring>

#include "image.h"
#include "types.h"
#include "utils.h"
#include "operations.h"

// Performes a floor by casting to an int.
// Should only be used with values > 0
#define FAST_FLOOR(x) ((int)(x))

// linear interpolates x between start and end
#define LERP(start, end, x) (start + (end - start) * x)

namespace pixl { namespace op {

    // bilinear interpolation
    static inline float blerp(float c00, float c10, float c01, float c11, float x, float y) {
        return LERP(LERP(c00, c10, x), LERP(c01, c11, x), y);
    }

    // ----------------------------------------------------------------------------
    // Nearest Neighbor scaling.
    void resize_nearest(Image* image, u8* out, u32 targetWidth, u32 targetHeight) {
        // Pre-calc some constants
        const f64 xRatio = image->width / (f64)targetWidth;
        const f64 yRatio = image->height / (f64)targetHeight;
        const u32 originalLineSize = image->width * image->channels;
        const u32 newRowSize = targetWidth * image->channels;

        const auto channels = image->channels;

        // Go through each image line
        i32 newStart, oldStart;
        i32 scaledOriginalLineSize;
        for (u32 y = 0; y < targetHeight; y++) {
            scaledOriginalLineSize = FAST_FLOOR(y * yRatio) * originalLineSize;

            for (u32 x = 0; x < targetWidth; x++) {
                // calc start index of old and new pixel data
                newStart = y * newRowSize + x * channels;
                oldStart = scaledOriginalLineSize + FAST_FLOOR(x * xRatio) * channels;

                // copy values from the old pixel array to the new one
                std::memcpy(out + newStart, image->data + oldStart, channels);
            }
        }
    }

    // ----------------------------------------------------------------------------
    // Bilinear scaling.
    void resize_bilinear(Image* image, u8* out, u32 targetWidth, u32 targetHeight) {
        const auto data = image->data;
        const auto channels = image->channels;

        const u32 newLineSize = targetWidth * channels;
        const u32 oldLineSize = image->width * channels;

        for (u32 y = 0; y < targetHeight; y++) {
            u32 oldY = y / (float)(targetHeight) * (image->height - 1);
            f32 newYScale = (f32)y / targetHeight;
            u32 currentLineOffset = y * newLineSize;


            for (u32 x = 0; x < targetWidth; x++) {
                u32 oldX = x / (float)(targetWidth) * (image->width - 1);

                u32 c00 = (oldX * channels) + (oldY * oldLineSize);
                u32 c10 = c00 + channels;
                u32 c01 = c00 + oldLineSize;
                u32 c11 = c01 + channels;

                u32 newStart = currentLineOffset + x * channels;
                f32 newXScale = (f32)x / targetWidth;
                for (auto i = 0; i < channels; i++) {
                    out[newStart + i] = blerp(data[c00 + i],
                                              data[c10 + i],
                                              data[c01 + i],
                                              data[c11 + i],
                                              newXScale,
                                              newYScale);
                }
            }
        }
    }

}}