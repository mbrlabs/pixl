#include <iostream>

#include <pixl/pixl.h>

int main() {
    pixl::Image* img = pixl::read("../images/lenna.png");
    std::cout << "channles: " << img->getChannels() << std::endl;
    std::cout << "size: " << img->getWidth() << "x" << img->getHeight() << std::endl;

    return 0;
}