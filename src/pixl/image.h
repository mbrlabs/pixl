#ifndef PIXL_IMAGE_H
#define PIXL_IMAGE_H

#include "types.h"

namespace pixl {

    class Image {
    public:
        Image(i32 width, i32 height, i32 channels, u8* data);
        ~Image();
        inline u8* getData() { return this->data; }
        inline i32 getWidth() { return this->width; }
        inline i32 getHeight() { return this->height; }
        inline i32 getChannels() { return this->channels; }

    private:
        i32 width;
        i32 height;
        i32 channels;
        u8* data;
    };
}

#endif