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

#ifndef PIXL_DEBUG_H
#define PIXL_DEBUG_H

#include "types.h"
#include <chrono>

namespace pixl {

    class Timer {
    public:
        void begin() { start = std::chrono::high_resolution_clock::now(); }

        void end() { finish = std::chrono::high_resolution_clock::now(); }

        i64 time_ns() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
        }

        f64 time_ms() { return time_ns() / 1000000.0; }

        f64 time_s() { return time_ns() / 1000000000.0; }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> finish;
    };
}

#endif