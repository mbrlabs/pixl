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
        i32 quality = 100;

    private:
        void* turboCompressor;
    };


    // Reads a file in binary mode.
    //
    // If successuful it returns a newly allocated byte array and stores it's length in
    // the provided length pointer. Otherwise it returns a nullptr.
    // The user of this function is reponsible for freeing the memory.
    u8* read_binary(const char* path, u64* length);

    // Writes a byte array to specified path.
    void write_binary(const char* path, u8* data, u64 length);

    // Convenience function for decoding an image.
    //
    // This function internally picks an appropriate image decoder.
    Image* read(const char* path);

    // Convenience function for encoding an image.
    //
    // This function internally picks an appropriate image encoder.
    // The file extension of the path parameter determines wich image encoder
    // should be used.
    void write(const char* path, Image* image);

}

#endif