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

#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <limits>


#include "types.h"

namespace pixl {

    // Timer with nanosecond precision.
    //
    // This can be used for benchmarks.
    class Timer {
    public:
        // Resets the timer and starts new measurement
        void begin() {
            executionTimeInNs = 0;
            start = std::chrono::high_resolution_clock::now();
        }

        // Stops measurement. Must be called after begin().
        void end() { pause(); }

        void pause() {
            finish = std::chrono::high_resolution_clock::now();
            executionTimeInNs +=
                std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
        }

        void resume() { start = std::chrono::high_resolution_clock::now(); }

        // Returns the execution time in nanoseconds.
        i64 time_ns() { return this->executionTimeInNs; }

        // Returns the exectution time in milliseconds
        f64 time_ms() { return time_ns() / 1000000.0; }

        // Returns the execution time in seconds
        f64 time_s() { return time_ns() / 1000000000.0; }

    private:
        i64 executionTimeInNs = 0;
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> finish;
    };


    void benchmark(std::string name, u32 loops, std::function<void(Timer&)> func) {
        Timer timer;

        f64 avg = 0;
        f64 min = std::numeric_limits<f64>::max();
        f64 max = std::numeric_limits<f64>::min();
        for (u32 i = 0; i < loops; i++) {
            timer.begin();
            func(timer);
            timer.end();

            auto time = timer.time_ms();
            min = std::min(min, time);
            max = std::max(max, time);
            avg += timer.time_ms();
        }
        avg /= (float)loops;

        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "Benchmark results for: " << name << std::endl;
        std::cout << "[" << loops << " runs] -> " << "avg: " << avg << ", max: " 
                    << max << " ms, min: " << min << " ms" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
    }
}

#endif