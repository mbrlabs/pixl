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

    class Image {
    public:
        Image(u32 width, u32 height, u32 channels, u8* data);
        Image(Image* image);
        ~Image();

        inline u8* getPixelOrNull(const u32 x, const u32 y) const {
            auto offset = y * lineSize + x * channels;
            if (offset >= size)
                return nullptr;
            return data + offset;
        }

        inline u8* getPixel(const u32 x, const u32 y) const {
            return data + (y * lineSize + x * channels);
        }

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