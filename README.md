# pixl
pixl is a lightweight image processing library, written in C++11.

The main goals of this project are ease of use and performance. All operations can optionally be run on multiple threads.

Image decoding/encoding is done by third party libraries. Pixl uses [libpng](http://www.libpng.org/pub/png/libpng.html) for png images, [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/) for jpeg and [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)/[stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) for everything else.
While the stb libraries are both very convenient to use, they not very performant or secure. 
In the future i am going to add more decoding/encoding options, but until then do NOT use this library in a production environment.

## Usage
```cpp
#include <pixl/pixl.h>

int main() {
	// load image
	auto image = pixl::read("path/to/image.png");

	// scale the image using the Nearest Neighbor method as default 
	pixl::ResizeTransformation resize;
	resize.numThreads = 4;
	resize.width = 256;
    resize.height = 256;
	resize.apply(image);

	// write scaled image
	pixl::write("path/to/small_image.png", image);
	return 0;
}
```

## Transformations & Filters
- [ ] Resize
	- [x] Nearest Neighbor
	- [ ] Bilinear
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

These libraries will be built together with the project and linked statically:

- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for reading other file formats. Will be removed soon
- [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) for writing other file formats. Will be removed soon.

Additionally i use [Catch](https://github.com/philsquared/Catch) for unit testing.

## Building
You need CMake to build the library with all examples and tests.    
You also need a C++11 compatible compiler.

While the code should work on all major platforms, the only supported OS so far is Linux.
Pixl compiles successfully on:

- Linux Mint Mint 17.3
- Arch Linux

### Building on Linux
```
cmake .
make
```