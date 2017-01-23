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

#include "image.h"
#include "types.h"
#include "utils.h"

#define GET_DATA_POINTER_AT(x, y) data + (y * channels * width) + (x * channels)

namespace pixl {

    // ----------------------------------------------------------------------------
    Image::Image(i32 width, i32 height, i32 channels, u8* data)
        : width(width), height(height), channels(channels), data(data) {}

    // ----------------------------------------------------------------------------
    Image::~Image() { free(data); }

    // ----------------------------------------------------------------------------
    void Image::setPixel(i32 x, i32 y, const Pixel<u8>& pixel) {
        u8* start = GET_DATA_POINTER_AT(x, y);
        if (channels == 4) {
            *start = pixel.r;
            *(++start) = pixel.g;
            *(++start) = pixel.b;
            *(++start) = pixel.a;
        } else if (channels == 3) {
            *start = pixel.r;
            *(++start) = pixel.g;
            *(++start) = pixel.b;
        } else if (channels == 2) {
            *start = pixel.r;
            *(++start) = pixel.g;
        } else {
            *start = pixel.r;
        }
    }

    // ----------------------------------------------------------------------------
    void Image::getPixel(i32 x, i32 y, Pixel<u8>& pixel) {
        u8* start = GET_DATA_POINTER_AT(x, y);
        if (channels == 4) {
            pixel.r = *start;
            pixel.g = *(++start);
            pixel.b = *(++start);
            pixel.a = *(++start);
        } else if (channels == 3) {
            pixel.r = *start;
            pixel.g = *(++start);
            pixel.b = *(++start);
        } else if (channels == 2) {
            pixel.r = *start;
            pixel.g = *(++start);
        } else {
            pixel.r = *start;
        }
    }
}