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