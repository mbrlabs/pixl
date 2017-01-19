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

#include <vector>
#include <thread>

#include "iostream"

#include "operation.h"
#include "image.h"
#include "types.h"
#include "utils.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    void flip_vertically(Image* img, i32 startColumn, i32 endColumn) {
        const auto lineSizeInBytes = img->width * img->channels;
        for (i32 column = startColumn; column < endColumn; column++) {
            u8* start = img->data + (column * img->channels);
            u8* end = start + (img->height * lineSizeInBytes);

            while (start <= end) {
                aswap(start, end, img->channels);
                start += lineSizeInBytes;
                end -= lineSizeInBytes;
            }
        }
    }

    // ----------------------------------------------------------------------------
    void flip_horizontally(Image* img, i32 startLine, i32 endLine) {
        const auto lineSizeInBytes = img->width * img->channels;
        for (i32 line = startLine; line < endLine; line++) {
            u8* start = img->data + (line * lineSizeInBytes);
            u8* end = start + lineSizeInBytes - img->channels;

            while (start <= end) {
                aswap(start, end, img->channels);
                start += img->channels;
                end -= img->channels;
            }
        }
    }

    // ----------------------------------------------------------------------------
    void FlipTransformation::apply(Image* image) {
        // Run operation on main thread if numThreads <= 1
        if(numThreads <= 1) {
            if (this->orientation == Orientation::HORIZONTAL) {
                flip_horizontally(image, 0, image->height);
            } else if (this->orientation == Orientation::VERTICAL) {
                flip_vertically(image, 0, image->width);            
            }
            return;
        }

        // create n threads
        std::vector<std::thread> threads;
        threads.reserve(this->numThreads);

        // start threads
        if (this->orientation == Orientation::HORIZONTAL) {
            auto chunk = image->height / numThreads;
            for (i32 i = 0; i < numThreads; i++) {
                threads.emplace_back(flip_horizontally, image, chunk * i, chunk * i + chunk);
            }
        } else if (this->orientation == Orientation::VERTICAL) {
            auto chunk = image->width / numThreads;
            for (i32 i = 0; i < numThreads; i++) {
                threads.emplace_back(flip_vertically, image, chunk * i, chunk * i + chunk);
            }
        }

        // wait until everybody is finished
        for (auto& t : threads) {
            t.join();
        }
    }
}