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

#include <turbojpeg.h>

#include "io.h"
#include "types.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    JpegTurboReader::JpegTurboReader() {
        // create decompressor
        this->turboDecompressor = tjInitDecompress();
    }

    // ----------------------------------------------------------------------------
    JpegTurboReader::~JpegTurboReader() {
        // destroy decompressor
        tjDestroy(this->turboDecompressor);
    }

    // ----------------------------------------------------------------------------
    Image* JpegTurboReader::read(const char* path) {
        // read file
        u64 fileSize;
        u8* fileBuffer = read_binary(path, &fileSize);

        // read meta data
        int width, height, subsamp;
        auto result =
            tjDecompressHeader2(turboDecompressor, fileBuffer, fileSize, &width, &height, &subsamp);

        if (result == -1) {
            PIXL_ERROR("Error: " + std::string(tjGetErrorStr()));
            return nullptr;
        }

        // create decoded buffer
        int pitch = width * tjPixelSize[TJPF_RGB];
        u8* data = (u8*)malloc(pitch * height);

        // decode image
        result = tjDecompress2(turboDecompressor, fileBuffer, fileSize, data, width, pitch, height,
                               TJPF_RGB, TJFLAG_NOREALLOC);

        if (result == -1) {
            PIXL_ERROR("Error: " + std::string(tjGetErrorStr()));
            return nullptr;
        }

        return new Image(width, height, 3, data);
    }

    // ----------------------------------------------------------------------------
    void JpegTurboWriter::write(const char* path, Image* image) {
        // TODO use jpegturbo
        StbiWriter writer;
        writer.write(path, image);
    }
}