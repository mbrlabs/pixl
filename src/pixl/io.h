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
#include "utils.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    static u8* read_binary(const char* path, u64* length) {
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
    static void write_binary(const char* path, u8* data, u64 length) {
        FILE* file = fopen(path, "wb");
        fwrite(data, sizeof(u8), length, file);
        fclose(file);
    }

    // Image Reader interface.
    class ImageReader {
    public:
        // Decodes an image and returns a pointer to that image.
        // The caller is responsible for deleting the image.
        virtual Image* read(const char* path) = 0;
    };


    // Image Writer interface.
    class ImageWriter {
    public:
        // Encodes an image and writes the file to the specified path.
        // The file extension of the path parameter determines wich image encoder
        // should be used.
        virtual void write(const char* path, Image* image) = 0;
    };


    // libpng reader.
    //
    // This reader uses the official libpng library to decode png images.
    class PngReader : public ImageReader {
    public:
        Image* read(const char* path);
    };

    // libpng writer.
    //
    // This writer uses the official libpng library to encode png images.
    class PngWriter : public ImageWriter {
    public:
        void write(const char* path, Image* image);
    };

    // libjpegturbo reader.
    //
    // This reader uses the official libpng library to decode png images.
    class JpegTurboReader : public ImageReader {
    public:
        JpegTurboReader();
        ~JpegTurboReader();
        Image* read(const char* path);

    private:
        void* turboDecompressor;
    };

    // libjpegturbo writer
    //
    // This writer uses the libjpegturbo library to encode png images.
    class JpegTurboWriter : public ImageWriter {
    public:
        JpegTurboWriter();
        ~JpegTurboWriter();
        void write(const char* path, Image* image);
        i32 quality = 75;

    private:
        void* turboCompressor;
    };


    // Convenience function for decoding an image.
    //
    // This function internally picks an appropriate image decoder.
    static Image* read(const char* path) {
        if (is_png(path)) { // png
            PngReader reader;
            return reader.read(path);
        } else if (is_jpg(path)) { // jpg
            JpegTurboReader reader;
            return reader.read(path);
        }

        return nullptr;
    }

    // Convenience function for encoding an image.
    //
    // This function internally picks an appropriate image encoder.
    // The file extension of the path parameter determines wich image encoder
    // should be used.
    static void write(const char* path, Image* image) {
        if (is_png(path)) { // png
            PngWriter writer;
            return writer.write(path, image);
        } else if (is_jpg(path)) { // jpg
            JpegTurboWriter writer;
            return writer.write(path, image);
        }

        // TODO throw error or smt
    }
}

#endif