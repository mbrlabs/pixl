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

#include <thread>
#include <chrono>

#define IMAGE_BIRD "../images/bird.jpg"

int main() {
    auto image = pixl::read(IMAGE_BIRD);

    pixl::benchmark("test", 20, [&](pixl::Timer& timer) {
        // create new image. Stop measurment for now.
        timer.pause();
        pixl::Image tmpImage(image);
        timer.resume();

        tmpImage.resize(26, 16);
    });

    return 0;
}