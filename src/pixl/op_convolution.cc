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

#include <array>
#include <cstring>
#include <algorithm>

#include "operations.h"
#include "image.h"
#include "types.h"
#include "utils.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    void op::convolution(Image* img, const Kernel kernel, const f32 scale) {
        // TODO throw error
        if (img->width < 3 || img->height < 3) {
            PIXL_DEBUG("For a convolution the image must be at least 3x3");
            return;
        }

        const i32 channels = img->channels;
        
        // create new buffer
        u8* buffer = (u8*)malloc(img->size);
        std::memcpy(buffer, img->data, img->size);

        for (i32 y = 1; y < img->height - 1; y++) {
            const auto yOffset = (y-1) * img->lineSize;
            for (i32 x = 1; x < img->width - 1; x++) {
                const auto offset = yOffset + (x-1) * channels;

                // apply kernel
                auto k0 = img->data + offset;
                auto k1 = k0 + channels;
                auto k2 = k1 + channels;
                auto k3 = k0 + img->lineSize;
                auto k4 = k3 + channels;
                auto k5 = k4 + channels;
                auto k6 = k3 + img->lineSize;
                auto k7 = k6 + channels;
                auto k8 = k7 + channels;
                u8* start = buffer + offset;
                for (i32 c = 0; c < channels; c++) {
                    f32 val = kernel[0] * k0[c] + kernel[1] * k1[c] + kernel[2] * k2[c] +
                              kernel[3] * k3[c] + kernel[4] * k4[c] + kernel[5] * k5[c] +
                              kernel[6] * k6[c] + kernel[7] * k7[c] + kernel[8] * k8[c];
                    val *= scale;
                    start[c] = (u8) std::max(0.0f, std::min(val, 255.0f));
                }
            }
        }

        free(img->data);
        img->data = buffer;
    }
}