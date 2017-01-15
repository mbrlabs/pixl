#include <iostream>

#include <pixl/pixl.h>
#include <pixl/transform.h>

int main() {
    pixl::Image* img = pixl::read("../images/lenna.png");
    std::cout << "channles: " << img->channels << std::endl;
    std::cout << "size: " << img->width << "x" << img->height << std::endl;

    pixl::FlipTransformation flip(img, true);
    flip.apply();

    pixl::write("lenna_flip.png", img);

    return 0;
}