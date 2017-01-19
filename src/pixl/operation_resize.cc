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
#include <math.h>

#include "image.h"
#include "types.h"
#include "operation.h"

// Performes a floor by casting to an int.
// Should only be used with values > 0
#define FAST_FLOOR(x) ((int)(x))

namespace pixl {

    // ----------------------------------------------------------------------------
    // Nearest Neighbor scaling.
    void nearest_neighbor(Image* image, u32 width, u32 height) {
        // Malloc new pixel data
        u8* temp = (u8*)malloc(sizeof(u8) * width * height * image->channels);

        // Pre-calc some constants
        const f64 xRatio = image->width / (f64)width;
        const f64 yRatio = image->height / (f64)height;
        const i32 originalLineSize = image->width * image->channels;
        const i32 newRowSize = width * image->channels;
        
        const auto data = image->data;  
        const auto channels = image->channels;  

        // Go through each image line
        i32 tempStart, oldStart;
        i32 scaledOriginalLineSize;
        for (int y = 0; y < height; y++) {
            scaledOriginalLineSize = FAST_FLOOR(y * yRatio) * originalLineSize;
            
            for (int x = 0; x < width; x++) {
                // calc start index of old and new pixel data
                tempStart = y * newRowSize + x * channels;
                oldStart = scaledOriginalLineSize + FAST_FLOOR(x * xRatio) * channels;

                // copy values from the old pixel array to the new one
                std::memcpy(temp + tempStart, data + oldStart, channels);
            }
        }

        // Update dimensions
        image->width = width;
        image->height = height;

        // Free old pixels and assign new
        free(image->data);
        image->data = temp;
    }

    // ----------------------------------------------------------------------------
    void ResizeTransformation::apply(Image* image) {
        if (this->method == ResizeMethod::NEARSET_NEIGHBOR) {
            nearest_neighbor(image, this->width, this->height);
        }
    }
}