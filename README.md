# pixl
pixl is a lightweight image manipulation library, written in C++.

Image decoding/encoding is done by third party libraries. Currently i am using [libpng](http://www.libpng.org/pub/png/libpng.html) for the png image
format and [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) +
[stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) for everything else.
While the stb libraries are both very convenient to use, they not very performant or secure. In the future i am going to add more
decoding/encoding options, but until then do NOT use this library in a production environment.

## Usage
```cpp
#include <pixl/pixl.h>

int main() {
	// load image
	auto image = pixl::read("path/to/image.png");

	// flip image horizontally
	pixl::FlipTransformation flip;
	flip.apply(image);

	// write flipped image
	pixl::write("path/to/flipped_image.png", image);
	return 0;
}
```

## Features
- [ ] Resize
	- [ ] Nearest Neighbor
	- [ ] Bilinear
	- [ ] Bicubic
	- [ ] Lanczos2
	- [ ] Lanczos3
- [x] Flip
	- [x] Horizontally
	- [x] Vertically
- [ ] Crop
- [ ] Rotate

## Building
I am using CMake to build the library + examples.    
Currently only Linux is supported. 

### Building on Linux
```
cmake .
make
```