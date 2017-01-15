// configure & include stb_image here
#define STBI_NO_HDR
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "io.h"
#include "image.h"

namespace pixl {

    // ----------------------------------------------------------------------------
    Image* StbiImageReader::read(const char* path) {
        i32 width, height, channels;
        u8* data = stbi_load(path, &width, &height, &channels, 0);
        if (data == 0) {
            // FATAL("Failed to load Pixmap: " << path)
            // FATAL("Failure Reason: " << stbi_failure_reason())
            return 0;
        }

        return new Image(width, height, channels, data);
    }

    // ----------------------------------------------------------------------------
    void StbiImageWriter::write(const char* path, Image* image) {
        stbi_write_png(path, image->getWidth(), image->getHeight(), image->getChannels(),
                       image->getData(), 0);
    }
}