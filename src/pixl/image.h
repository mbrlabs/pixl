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

#ifndef PIXL_IMAGE_H
#define PIXL_IMAGE_H

#include "types.h"

namespace pixl {

    enum class Orientation {
        HORIZONTAL,
        VERTICAL,
    };

    enum class ResizeMethod {
        NEARSET_NEIGHBOR,
        BILINEAR,
        // BICUBIC,
        // LANCZOS_2,
        // LANCZOS_3,
    };

    class Image {
    public:
        Image(u32 width, u32 height, u32 channels, u8* data);
        Image(Image* image);
        ~Image();

        // Returns a pointer to the start of the pixel at x,y.
        // This method performes a bounds check and returns a nullptr if x,y is out of bounds.
        inline u8* getPixelOrNull(const u32 x, const u32 y) const {
            auto offset = y * lineSize + x * channels;
            if (offset >= size)
                return nullptr;
            return data + offset;
        }

        // Returns a pointer to the start of the pixel at x,y.
        // This method performes no bound checks and results in undefined behaviour if x,y is out of
        // bounds.
        inline u8* getPixel(const u32 x, const u32 y) const {
            return data + (y * lineSize + x * channels);
        }

        Image* resize(u32 width, u32 height, ResizeMethod method = ResizeMethod::BILINEAR);
        Image* flip(Orientation orientation = Orientation::HORIZONTAL);

    public:
        i32 width;
        i32 height;
        i32 channels;
        u8* data;
        u64 size;
        u64 lineSize;
    };
}

#endif