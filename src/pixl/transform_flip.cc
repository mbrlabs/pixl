#include <utility>
#include "iostream"

#include "transform.h"
#include "image.h"
#include "types.h"

// ODD
// 0 5
// 1 4
// 2 3
// 3 2

// EVEN
// 0 4
// 1 3
// 2 2
// 3 1

namespace pixl {

    void flipVertically(Image* img) {
        auto lineSizeInBytes = img->width * img->channels;        
        for (i32 column = 0; column < img->width; column++) {
            u8* start = img->data + (column * img->channels);
            u8* end = start + (img->height * lineSizeInBytes);
            
            while(start <= end) {
                // swap pixel
                for(u64 i = 0; i < img->channels; i++) {
                    std::swap(start[i], end[i]);
                }
                start += lineSizeInBytes;
                end -= lineSizeInBytes;
            }
        }
    }

    void flipHorizontally(Image* img) {
        auto lineSizeInBytes = img->width * img->channels;
        for (i32 line = 0; line < img->height; line++) {
            u8* start = img->data + (line * lineSizeInBytes);
            u8* end = start + lineSizeInBytes - img->channels;
            
            while(start <= end) {
                // swap pixel
                for(u64 i = 0; i < img->channels; i++) {
                    std::swap(start[i], end[i]);
                }
                start += img->channels;
                end -= img->channels;
            }
        }
    }

    void FlipTransformation::apply() {
        if (vertical) {
            flipVertically(image);
        } else {
            flipHorizontally(image);
        }
    }
}