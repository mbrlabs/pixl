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

#include "image.h"
#include "types.h"
#include "operation.h"

namespace pixl {

    void nearest_neighbor(Image* image, bool preserveRatio, u32 width, u32 height) {}

    void ResizeTransformation::apply(Image* image) {
        if (this->method == ResizeMethod::NEARSET_NEIGHBOR) {
            nearest_neighbor(image, this->preserveAspectRatio, this->width, this->height);
        }
    }
}