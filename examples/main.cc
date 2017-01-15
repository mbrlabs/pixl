#include <iostream>

#include <pixl/pixl.h>

int main() {
    pixl::Image* img = pixl::read("../images/lenna.png");
    std::cout << "channles: " << img->channels << std::endl;
    std::cout << "size: " << img->width << "x" << img->height << std::endl;

    pixl::write("lenna.png", img);

    return 0;
}