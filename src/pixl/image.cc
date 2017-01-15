#include <cstdlib>

#include "image.h"
#include "types.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    Image::Image(i32 width, i32 height, i32 channels, u8* data)
        : width(width),
          height(height),
          channels(channels),
          data(data) {}

    // ----------------------------------------------------------------------------
    Image::~Image() { free(data); }
}