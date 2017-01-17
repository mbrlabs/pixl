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

#include <pixl/pixl.h>

int main() {
    // load image
    pixl::PngReader reader;
    auto image = reader.read("../images/lenna.png");

    std::cout << "width: " << image->width << std::endl;
    std::cout << "height: " << image->height << std::endl;
    std::cout << "channels: " << image->channels << std::endl;

    pixl::PngWriter writer;

    writer.write("libpng_lenna.png", image);


    return 0;
}