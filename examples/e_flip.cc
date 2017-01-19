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

int main() {
    // load image
    auto image = pixl::read("../images/lena.png");
    
    pixl::FlipTransformation flip;

    // flip image horizontally
    pixl::Timer timer;
    timer.begin();
    flip.apply(image);
    timer.end();
    PIXL_DEBUG("flip hori ns: " << timer.time_ns() << " ns");
    PIXL_DEBUG("flip hori ms: " << timer.time_ms() << " ms");
    PIXL_DEBUG("flip hori s: " << timer.time_s() << " s");

    // flip image vertically
    flip.orientation = pixl::Orientation::VERTICAL;
    timer.begin();
    flip.apply(image);
    timer.end();
    PIXL_DEBUG("flip vert ns: " << timer.time_ns() << " ns");
    PIXL_DEBUG("flip vert ms: " << timer.time_ms() << " ms");
    PIXL_DEBUG("flip vert s: " << timer.time_s() << " s");

    // write flipped image
    pixl::write("lena_flip.png", image);
    return 0;
}