#include <pixl/pixl.h>

int main() {
    // load image
    auto image = pixl::read("../images/lenna.png");

    // flip image horizontally
    pixl::FlipTransformation flip(image);
    flip.apply();

    // write flipped image
    pixl::write("lenna_flip.png", image);
    return 0;
}