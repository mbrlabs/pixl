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

#include <array>

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

    typedef std::array<f32, 9> Kernel;

    class Image {
    public:
        // Creates a new image with prefilled data.
        // This constructor should be used when the image data is already available, e.g. when
        // decoding from an image file.
        Image(u32 width, u32 height, u32 channels, u8* data);

        // Creates a new image with the given dimensions and allocates enough memory
        // to store the image data.
        Image(u32 width, u32 height, u32 channels);        
        
        // Image copy constructor. 
        Image(Image* image);

        // Releases all resources accociated with this image.
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

        // Resizes the image.
        // The resize method specifies whick algorithm should be used to resize the image.
        // The defualt - bilinear - is a good compromise between performance and quality.
        //
        // NOTE: Currently, the aspect ration won't be reserved.
        Image* resize(u32 width, u32 height, ResizeMethod method = ResizeMethod::BILINEAR);

        // Filps the image horizontlly or vertically.
        // Default ist horizontal.
        Image* flip(Orientation orientation = Orientation::HORIZONTAL);

        // Applies a 3x3 convolution matrix to the image.
        Image* convolution(const Kernel kernel, f32 scale = 1);

        // Grayscales the image while preserving all color channels.
        Image* grayscale();

        // Inverts all color channels of the image.
        Image* invert();

        // Adds a alpha channel to the image if not already available.
        // You can also specify the default value of all alpha values.
        Image* addAlphaChannel(u8 defaultValue = 255);

        // Removes the alpha channel if present.
        Image* removeAlphaChannel();        
                
    public:
        u8* data;
        i32 width;
        i32 height;
        i32 channels;
        u64 size;
        u64 lineSize;
    };
}

#endif