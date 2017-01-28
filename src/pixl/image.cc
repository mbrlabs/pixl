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

namespace pixl {

    // ----------------------------------------------------------------------------
    Image::Image(u32 width, u32 height, u32 channels, u8* data)
        : width(width),
          height(height),
          channels(channels),
          data(data),
          size(height * width * channels),
          lineSize(size * height) {}

    // ----------------------------------------------------------------------------
    Image::Image(Image* image)
        : width(image->width),
          height(image->height),
          channels(image->channels),
          size(height * width * channels),
          lineSize(size * height) {
        this->data = (u8*)malloc(size);
    }

    // ----------------------------------------------------------------------------
    Image::~Image() { free(data); }
}