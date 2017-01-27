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
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>
#include <math.h>

#include "image.h"
#include "types.h"
#include "utils.h"
#include "operation.h"

// Performes a floor by casting to an int.
// Should only be used with values > 0
#define FAST_FLOOR(x) ((int)(x))

// linear interpolates x between start and end
#define LERP(start, end, x) (start + (end - start) * x)

// bilinear interpolation
static inline float blerp(float c00, float c10, float c01, float c11, float x, float y) {
    return LERP(LERP(c00, c10, x), LERP(c01, c11, x), y);
}

namespace pixl {

    // ----------------------------------------------------------------------------
    // Nearest Neighbor scaling.
    void nearest_neighbor(const Image* image,
                          u8* imageBuffer,
                          u32 targetWidth,
                          u32 targetHeight,
                          u32 startLine,
                          u32 endLine) {
        // Pre-calc some constants
        const f64 xRatio = image->width / (f64)targetWidth;
        const f64 yRatio = image->height / (f64)targetHeight;
        const u32 originalLineSize = image->width * image->channels;
        const u32 newRowSize = targetWidth * image->channels;

        const auto channels = image->channels;

        // Go through each image line
        i32 newStart, oldStart;
        i32 scaledOriginalLineSize;
        for (u32 y = startLine; y < endLine; y++) {
            scaledOriginalLineSize = FAST_FLOOR(y * yRatio) * originalLineSize;

            for (u32 x = 0; x < targetWidth; x++) {
                // calc start index of old and new pixel data
                newStart = y * newRowSize + x * channels;
                oldStart = scaledOriginalLineSize + FAST_FLOOR(x * xRatio) * channels;

                // copy values from the old pixel array to the new one
                std::memcpy(imageBuffer + newStart, image->data + oldStart, channels);
            }
        }
    }

    // ----------------------------------------------------------------------------
    // Bilinear scaling.
    void bilinear(const Image* image,
                  u8* imageBuffer,
                  u32 targetWidth,
                  u32 targetHeight,
                  u32 startLine,
                  u32 endLine) {
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
                    imageBuffer[newStart + i] = blerp(data[c00 + i],
                                                      data[c10 + i],
                                                      data[c01 + i],
                                                      data[c11 + i],
                                                      newXScale,
                                                      newYScale);
                }
            }
        }
    }

    // ----------------------------------------------------------------------------
    void ResizeTransformation::apply(Image* image) {
        // alloc new data
        u8* imageBuffer = (u8*)malloc(sizeof(u8) * this->width * this->height * image->channels);

        // Run operation on main thread if numThreads <= 1
        if (numThreads <= 1) {
            if (this->method == ResizeMethod::NEARSET_NEIGHBOR) {
                nearest_neighbor(image, imageBuffer, width, height, 0, height);
            } else if (this->method == ResizeMethod::BILINEAR) {
                bilinear(image, imageBuffer, width, height, 0, height);
            }
        } else {
            // create n threads
            std::vector<std::thread> threads;
            threads.reserve(this->numThreads);

            // start threads
            if (this->method == ResizeMethod::NEARSET_NEIGHBOR) {
                auto chunk = this->height / numThreads;
                for (u32 i = 0; i < numThreads; i++) {
                    auto last = (i == numThreads - 1) ? this->height : chunk * i + chunk;
                    threads.push_back(std::thread(nearest_neighbor,
                                                  image,
                                                  imageBuffer,
                                                  this->width,
                                                  this->height,
                                                  chunk * i,
                                                  last));
                }
            }
            // TODO bilinear for multi threads

            // wait until everybody is finished
            for (auto& t : threads) {
                t.join();
            }
        }

        // update image
        free(image->data);
        image->width = this->width;
        image->height = this->height;
        image->data = imageBuffer;
    }
}