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

#include <pixl/pixl.h>
#include <pixl/debug.h>

#define IMAGE_LENA "../images/lena.png"
#define IMAGE_BIRD "../images/bird.jpg"

void flip() {
    auto image = pixl::read("../images/lena.png");
    pixl::FlipTransformation flip;
    pixl::Timer timer;

    timer.begin();
    flip.apply(image);
    timer.end();
    PIXL_DEBUG("filp ms: " << timer.time_ms() << " ms");

    pixl::write("lena_flip.png", image);
    delete image;
}

void resize() {
    auto image = pixl::read("/home/marcus/Desktop/rms.jpg");

    auto ratio = ((float)image->width) / ((float)image->height);
    ratio /= 10.0;

    pixl::ResizeTransformation resize(image->width * ratio, image->height * ratio);
    pixl::Timer timer;

    // nearest neighbor
    timer.begin();
    resize.apply(image);
    timer.end();
    PIXL_DEBUG("nearest neighbor resize ms: " << timer.time_ms() << " ms");
    pixl::write("rms_resize_nearest_neighbor.jpg", image);
    delete image;

    image = pixl::read("/home/marcus/Desktop/rms.jpg");
    // bilinear
    timer.begin();
    resize.method = pixl::ResizeMethod::BILINEAR;
    resize.apply(image);

    timer.end();
    PIXL_DEBUG("bilinear resize ms: " << timer.time_ms() << " ms");
    pixl::write("rms_resize_bilinear.jpg", image);

    delete image;
}

int main() {
    // flip();
    resize();
    return 0;
}