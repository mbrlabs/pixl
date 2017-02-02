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

#include <iostream>

#include "pixl.h"

extern "C" {

// ----------------------------------------------------------------------------
PixlImage* pixl_load_image(const char* path) {
    auto handle = pixl::read(path);

    auto cimg = (PixlImage*)malloc(sizeof(PixlImage));
    cimg->width = handle->width;
    cimg->height = handle->height;
    cimg->__handle = handle;

    return cimg;
}

// ----------------------------------------------------------------------------
void pixl_destroy_image(PixlImage* image) {
    auto handle = static_cast<pixl::Image*>(image->__handle);
    delete handle;
    free(image);
}

// ----------------------------------------------------------------------------
void pixl_save_image(PixlImage* image, const char* path, int quality) {
    pixl::write(static_cast<pixl::Image*>(image->__handle), path, quality);
}

// ----------------------------------------------------------------------------
void pixl_resize(PixlImage* image, unsigned int width, unsigned int height, int method) {
    auto handle = static_cast<pixl::Image*>(image->__handle);

    pixl::ResizeMethod algo = pixl::ResizeMethod::NEARSET_NEIGHBOR;
    if (method == PIXL_RESIZE_METHOD_BILINEAR) {
        algo = pixl::ResizeMethod::BILINEAR;
    }

    handle->resize(width, height, algo);
    image->width = width;
    image->height = height;
}

// ----------------------------------------------------------------------------
void pixl_flip(PixlImage* image, int orientation) {
    auto handle = static_cast<pixl::Image*>(image->__handle);

    pixl::Orientation orient;
    if (orientation == PIXL_ORIENTATION_VERTICAL) {
        orient = pixl::Orientation::VERTICAL;
    } else if (orientation == PIXL_ORIENTATION_HORIZONTAL) {
        orient = pixl::Orientation::HORIZONTAL;
    } else {
        return;
    }

    handle->flip(orient);
}

// ----------------------------------------------------------------------------
void pixl_grayscale(PixlImage* image) {
    auto handle = static_cast<pixl::Image*>(image->__handle);
    handle->grayscale();
}
}