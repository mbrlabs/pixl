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


    class StbiImageReader : ImageReader {
    public:
        Image* read(const char* path);
    };

    class StbiImageWriter : ImageWriter {
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