#ifndef PIXL_IMAGE_H
#define PIXL_IMAGE_H

#include "types.h"

namespace pixl {

    class Image {
    public:
        Image();
        ~Image();
        inline u8* getData() { return this->data; }
        inline u32 getWidth() { return this->width; }
        inline u32 getHeight() { return this->height; }
        inline u32 getSize() { return this->size; }
    private:
        u32 width;
        u32 height;
        u32 size;
        u8* data;
    };
}

#endif