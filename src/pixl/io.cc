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

#include "io.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    Image* read(const char* path) {
        if (is_png(path)) { // png
            PngReader reader;
            return reader.read(path);
        } else if (is_jpg(path)) { // jpg
            JpegTurboReader reader;
            return reader.read(path);
        }

        return nullptr;
    }

    // ----------------------------------------------------------------------------
    void write(Image* image, const char* path, i32 quality) {
        if (is_png(path)) { // png
            PngWriter writer;
            return writer.write(image, path);
        } else if (is_jpg(path)) { // jpg
            JpegTurboWriter writer;
            writer.quality = quality;
            return writer.write(image, path);
        }

        // TODO throw error or smt
    }

    // ----------------------------------------------------------------------------
    u8* read_binary(const char* path, u64* length) {
        FILE* file = fopen(path, "rb");

        // read file size
        fseek(file, 0, SEEK_END);
        *length = ftell(file);

        // setup data
        u8* data = new u8[*length + 1];

        // read file
        fseek(file, 0, SEEK_SET);
        fread(data, 1, *length, file);
        fclose(file);

        return data;
    }

    // ----------------------------------------------------------------------------
    void write_binary(const char* path, u8* data, u64 length) {
        FILE* file = fopen(path, "wb");
        fwrite(data, sizeof(u8), length, file);
        fclose(file);
    }
}
