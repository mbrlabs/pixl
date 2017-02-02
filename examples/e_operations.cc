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

#include <pixl/pixl.h>
#include <pixl/debug.h>

#define IMAGE_LENA "../images/lena.png"
#define IMAGE_BIRD "../images/bird.jpg"

void flip() {
    auto image = pixl::read("../images/lena.png");
    pixl::Timer timer;

    timer.begin();
    image->flip();
    timer.end();
    PIXL_DEBUG("filp ms: " << timer.time_ms() << " ms");

    pixl::write(image, "lena_flip.png");
    delete image;
}

void resize() {
    auto image = pixl::read(IMAGE_BIRD);

    auto ratio = ((float)image->width) / ((float)image->height);
    ratio /= 10.0;

    auto newWidth = image->width * ratio;
    auto newHeight = image->height * ratio;

    pixl::Timer timer;

    // nearest neighbor
    timer.begin();
    image->resize(newWidth, newHeight, pixl::ResizeMethod::NEARSET_NEIGHBOR);
    timer.end();
    PIXL_DEBUG("nearest neighbor resize ms: " << timer.time_ms() << " ms");
    pixl::write(image, "bird_resize_nearest_neighbor.jpg");
    delete image;

    // bilinear
    image = pixl::read(IMAGE_BIRD);
    timer.begin();
    image->resize(newWidth, newHeight, pixl::ResizeMethod::BILINEAR);
    timer.end();
    PIXL_DEBUG("bilinear resize ms: " << timer.time_ms() << " ms");
    pixl::write(image, "bird_resize_bilinear.jpg");

    delete image;
}

void grayscale() {
    auto image = pixl::read(IMAGE_LENA);
    image->grayscale();
    pixl::write(image, "lena_gray.jpg");
    delete image;
}

void invert() {
    auto image = pixl::read(IMAGE_LENA);
    image->invert();
    pixl::write(image, "lena_invert.jpg");
    delete image;
}

void convolution() {
    auto image = pixl::read(IMAGE_BIRD);

    // edge detect
    std::array<float, 9> edge = {0,1,0,1,-4,1,0,1,0};
    image->convolution(edge);

    // emboss detect
    //std::array<float, 9> emboss = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
    //image->convolution(emboss);

    pixl::write(image, "bird_conv.jpg", 95);
    delete image;
}

int main() {
    // flip();
    // resize();
    invert();
    convolution();
    return 0;
}