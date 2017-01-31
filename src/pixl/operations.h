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

namespace pixl { namespace op {

    void flip_vertically(Image* img);
    void flip_horizontally(Image* img);
    void resize_nearest(Image* img, u8* out, u32 width, u32 height);
    void resize_bilinear(Image* img, u8* out, u32 width, u32 height);

}}

#endif