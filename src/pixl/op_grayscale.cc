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

#include "operations.h"
#include "image.h"
#include "types.h"
#include "utils.h"


namespace pixl {

    // ----------------------------------------------------------------------------
    void op::grayscale(Image* img) {
        for (auto y = 0; y < img->height; y++) {
            for (auto x = 0; x < img->width; x++) {
                auto pixel = img->getPixel(x, y);

                // calc mean
                f32 mean = 0;
                for (u8 c = 0; c < img->channels; c++) {
                    mean += (f32) * (pixel + c);
                }
                mean /= img->channels;

                // set new values
                memset(pixel, (u8)mean, img->channels);
            }
        }
    }
}