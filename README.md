# pixl
pixl is a lightweight image processing library, written in C++11.

The main goals of this project are ease of use and performance. All operations can optionally be run on multiple threads.
Image decoding/encoding is done by third party libraries. Currently supported image formats are: png and jpeg.

There are also APIs for C and Python.

## Usage
```cpp
#include <pixl/pixl.h>

int main() {
	// load image
	auto image = pixl::read("path/to/image.png");

	// scale the image using the Nearest Neighbor method as default 
	pixl::ResizeTransformation resize(256, 256);
	resize.numThreads = 4;
	resize.apply(image);

	// write scaled image
	pixl::write("path/to/small_image.png", image);
	return 0;
}
```

## Transformations & Filters
- [ ] Resize
	- [x] Nearest Neighbor
	- [x] Bilinear
	- [ ] Bicubic
	- [ ] Lanczos2
	- [ ] Lanczos3
- [x] Flip
	- [x] Horizontally
	- [x] Vertically
- [ ] Crop
- [ ] Rotate

## Dependencies
The following libraries must be on the system:

- [libpng](http://www.libpng.org/pub/png/libpng.html) for png decoding & encoding
- [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/) for fast jpeg decoding & encoding

Additionally i use [Catch](https://github.com/philsquared/Catch) for unit testing.

## Building
You need CMake to build the library with all examples and tests.    
You also need a C++11 compatible compiler.

While the code should work on all major platforms, the only supported OS so far is Linux.
Pixl compiles successfully on:

- Linux Mint 17.3
- Arch Linux

### Building on Linux
```
cmake .
make
```