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

#ifndef PIXL_TRANSFORM_H
#define PIXL_TRANSFORM_H

#include <vector>

#include "image.h"
#include "types.h"

// Performes a floor by casting to an int. Should only be used with values > 0.
#define FAST_FLOOR(x) ((int)(x))

// Linear interpolates x between start and end.
#define LERP(start, end, x) (start + (end - start) * x)

namespace pixl {
    namespace op {

        // Bilinear interpolation.
        inline float blerp(float c00, float c10, float c01, float c11, float x, float y) {
            return LERP(LERP(c00, c10, x), LERP(c01, c11, x), y);
        }

        // Flips the image vertically.
        void flip_vertically(Image* img);

        // Flips the image horizontally.
        void flip_horizontally(Image* img);

        // Resizes the image using the nearest neighbor method.
        // The original image is not changed. The newly scaled image is stored in
        // the provided 'out' buffer.
        void resize_nearest(const Image* img, u8* out, u32 width, u32 height);

        // Resizes the image using the bilinear method.
        // The original image is not changed. The newly scaled image is stored in
        // the provided 'out' buffer.
        void resize_bilinear(const Image* img, u8* out, u32 width, u32 height);

        // Grayscales the image while keeping all channels.
        void grayscale(Image* img);

        // Inverts all color values of the image.
        void invert(Image* img);

        // Applies a 3x3 convolution matrix to the image.
        void convolution(Image* img, const Kernel kernel, const f32 scale);

    }
}

#endif