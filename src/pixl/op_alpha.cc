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

#include "operations.h"
#include "image.h"
#include "types.h"
#include "utils.h"

namespace pixl {
    namespace op {

        // ----------------------------------------------------------------------------
        void add_alpha_channel(Image* img, u8 defaultValue) {
            if(img->channels != 3) return;
            img->channels = 4;
            img->lineSize = img->channels * img->width;
            img->size = img->lineSize * img->height;

            u8* newData = (u8*)malloc(img->size);
            for(int i = 1; i <= img->size; i++) {
                int idx = i - 1;
                if(i % 4 == 0) {
                    newData[idx] = defaultValue;
                } else {
                    newData[idx] = img->data[idx-i/4];
                }
            }

            free(img->data);
            img->data = newData;
        }

        // ----------------------------------------------------------------------------
        void remove_alpha_channel(Image* img) {
            if(img->channels != 4) return;
            auto oldSize = img->size;
            img->channels = 3;
            img->lineSize = img->channels * img->width;
            img->size = img->lineSize * img->height;

            u8* newData = (u8*)malloc(img->size);
            for(int i = 1; i <= oldSize; i++) {
                int idx = i - 1;
                if(i % 4 == 0) {
                    continue;
                } else {
                    newData[idx-i/4] = img->data[idx];
                }
            }

            free(img->data);
            img->data = newData;
        }
    }
}