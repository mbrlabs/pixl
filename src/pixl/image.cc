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
#include <array>

#include "image.h"
#include "types.h"
#include "utils.h"
#include "operations.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    Image::Image(u32 width, u32 height, u32 channels, u8* data)
        : data(data),
          width(width),
          height(height),
          channels(channels),
          size(height * width * channels),
          lineSize(channels * width) {}

    // ----------------------------------------------------------------------------
    Image::Image(u32 width, u32 height, u32 channels)
        : data(data),
          width(width),
          height(height),
          channels(channels),
          size(height * width * channels),
          lineSize(channels * width) 
    {
        this->data = (u8*)malloc(this->size);
    }

    // ----------------------------------------------------------------------------
    Image::Image(Image* image)
        : width(image->width),
          height(image->height),
          channels(image->channels),
          size(image->size),
          lineSize(image->lineSize) 
    {
        this->data = (u8*)malloc(image->size);
        memcpy(this->data, image->data, image->size);
    }

    // ----------------------------------------------------------------------------
    Image::~Image() { free(this->data); }

    // ----------------------------------------------------------------------------
    Image* Image::resize(u32 width, u32 height, ResizeMethod method) {
        // malloc new data
        u8* imageBuffer = (u8*)malloc(sizeof(u8) * width * height * this->channels);

        // perform operation
        if (method == ResizeMethod::NEARSET_NEIGHBOR) {
            op::resize_nearest(this, imageBuffer, width, height);
        } else if (method == ResizeMethod::BILINEAR) {
            op::resize_bilinear(this, imageBuffer, width, height);
        }

        // update image
        free(this->data);
        this->data = imageBuffer;
        this->width = width;
        this->height = height;
        this->lineSize = width * this->channels;
        this->size = height * this->lineSize;

        return this;
    }

    // ----------------------------------------------------------------------------
    Image* Image::flip(Orientation orientation) {
        if (orientation == Orientation::HORIZONTAL) {
            op::flip_horizontally(this);
        } else if (orientation == Orientation::VERTICAL) {
            op::flip_vertically(this);
        }

        return this;
    }

    // ----------------------------------------------------------------------------
    Image* Image::grayscale() {
        op::grayscale(this);
        return this;
    }

    // ----------------------------------------------------------------------------
    Image* Image::invert() {
        op::invert(this);
        return this;
    }

    // ----------------------------------------------------------------------------
    Image* Image::convolution(const Kernel kernel, f32 scale) {
        op::convolution(this, kernel, scale);
        return this;
    }

    // ----------------------------------------------------------------------------
    Image* Image::addAlphaChannel(u8 defaultValue) {
        op::add_alpha_channel(this, defaultValue);
        return this;
    }

    // ----------------------------------------------------------------------------    
    Image* Image::removeAlphaChannel() {
        op::remove_alpha_channel(this);
        return this;
    }

    // ----------------------------------------------------------------------------    
    Image* Image::contrast(f32 contrast) {
        op::contrast(this, contrast);
        return this;
    }

}