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

#include <algorithm>
#include <cstdlib>
#include <cstring>

#include "operations.h"
#include "image.h"
#include "types.h"
#include "utils.h"


namespace pixl {

    // ----------------------------------------------------------------------------
    void op::invert(Image* img) {
        const int channels = std::min(img->channels, 3);

        for(auto offset = 0; offset < img->size; offset += img->channels) {
            auto pixel = img->data + offset;
            for(auto c = 0; c < channels; c++) {
                pixel[c] = 255 - pixel[c];
            }
        }
    }

}