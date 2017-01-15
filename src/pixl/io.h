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

#ifndef PIXL_IO_H
#define PIXL_IO_H

#include "image.h"

namespace pixl {

    // Image Reader interface.
    class ImageReader {
    public:
        virtual Image* read(const char* path) = 0;
    };

    // Image Writer interface.
    class ImageWriter {
    public:
        virtual void write(const char* path, Image* image) = 0;
    };


    class StbiImageReader : public ImageReader {
    public:
        Image* read(const char* path);
    };

    class StbiImageWriter : public ImageWriter {
    public:
        void write(const char* path, Image* image);
    };


    typedef StbiImageReader DefaultReader;
    typedef StbiImageWriter DefaultWriter;

    static Image* read(const char* path) {
        DefaultReader reader;
        return reader.read(path);
    }

    static void write(const char* path, Image* image) {
        DefaultWriter writer;
        writer.write(path, image);
    }
}

#endif