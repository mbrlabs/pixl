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

#ifndef PIXL_UTILS_H
#define PIXL_UTILS_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "types.h"

#define PIXL_DEBUG(msg) std::cout << "[DEBUG] " << msg << std::endl
#define PIXL_WARNING(msg) std::cout << "[WARNING] " << msg << std::endl
#define PIXL_ERROR(msg) std::cout << "[ERROR] " << msg << std::endl

namespace pixl {

    // Swaps the content of array a with array b from a[0] till a[len].
    inline void aswap(u8* a, u8* b, i32 len) {
        u8 tmp;
        for (i32 i = 0; i < len; i++) {
            tmp = a[i];
            a[i] = b[i];
            b[i] = tmp;
        }
    }

    // Splits a string.
    inline void str_split(const std::string& str,
                          const char delimiter,
                          std::vector<std::string>& out) {
        out.clear();
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            out.push_back(token);
        }
    }

    // Checks if a string starts with annother string.
    inline bool str_starts_with(const std::string& a, const std::string& b) {
        return a.find(b) == 0;
    }


    // Checks if string a ends with b.
    inline bool str_ends_with(const std::string& a, const std::string& b) {
        if (a.length() >= b.length()) {
            return (0 == a.compare(a.length() - b.length(), b.length(), b));
        } else {
            return false;
        }
    }

    // Checks if the filename has a png file extension.
    inline bool is_png(const std::string& name) {
        return str_ends_with(name, ".png") || str_ends_with(name, ".PNG");
    }

    // Checks if the filename has a jpg file extension.
    inline bool is_jpg(const std::string& name) {
        return str_ends_with(name, ".jpg") || str_ends_with(name, ".jpeg") ||
               str_ends_with(name, ".JPG") || str_ends_with(name, ".JPEG");
    }
}

#endif