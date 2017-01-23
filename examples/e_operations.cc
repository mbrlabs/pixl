#include <pixl/pixl.h>
#include <pixl/debug.h>

#define IMAGE_LENA "../images/lena.png"
#define IMAGE_BIRD "../images/bird.jpg"

void flip() {
    auto image = pixl::read("../images/lena.png");
    pixl::FlipTransformation flip;
    pixl::Timer timer;

    timer.begin();
    flip.apply(image);
    timer.end();
    PIXL_DEBUG("filp ms: " << timer.time_ms() << " ms");

    pixl::write("lena_flip.png", image);
    delete image;
}

void resize() {
    auto image = pixl::read("../images/bird.jpg");

    auto ratio = ((float)image->width) / ((float)image->height);
    ratio /= 2.0;

    pixl::ResizeTransformation resize(image->width * ratio, image->height * ratio);
    pixl::Timer timer;

    timer.begin();
    resize.apply(image);
    timer.end();
    PIXL_DEBUG("resize ms: " << timer.time_ms() << " ms");

    pixl::write("bird_resize.jpg", image);
    delete image;
}

int main() {
    flip();
    resize();
    return 0;
}