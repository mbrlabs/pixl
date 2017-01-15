#ifndef PIXL_TRANSFORM_H
#define PIXL_TRANSFORM_H

#include "image.h"

namespace pixl {

    class Transformation {
    public:
        Transformation(Image* image) : image(image) {}
        virtual void apply() = 0;

    protected:
        Image* image;
    };

    class FlipTransformation : public Transformation {
    public:
        FlipTransformation(Image* image, bool vertical)
            : Transformation(image), vertical(vertical) {}
        void apply();

    private:
        bool vertical;
    };
}

#endif