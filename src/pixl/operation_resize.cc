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
#include <math.h>

#include "image.h"
#include "types.h"
#include "operation.h"

namespace pixl {

    void nearest_neighbor(Image* image, u32 width, u32 height) {
        // Malloc new pixel data
        u8* temp = (u8*)malloc(sizeof(u8) * width * height * image->channels);

        // Pre-calc some constants
        const f64 xRatio = image->width / (f64)width;
        const f64 yRatio = image->height / (f64)height;
        const i32 originalRowSize = image->width * image->channels;
        const i32 newRowSize = width * image->channels;

        // Goes through each image line and performes linear interolation between
        // the old and new image.
        i32 tempStart, oldStart;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
				// calc start index of old and new pixel data
                tempStart = y * newRowSize + x * image->channels;
                oldStart = (i32)(floor(y * yRatio) * originalRowSize + // full lines
                                 floor(x * xRatio) * image->channels); // current line

                // go through channels
                for (int c = 0; c < image->channels; c++) {
                    temp[tempStart + c] = image->data[oldStart + c];
                }
            }
        }

        // Update dimensions
        image->width = width;
        image->height = height;

        // Free old pixels and assign new
        free(image->data);
        image->data = temp;
    }

    void ResizeTransformation::apply(Image* image) {
        if (this->method == ResizeMethod::NEARSET_NEIGHBOR) {
            nearest_neighbor(image, this->width, this->height);
        }
    }
}