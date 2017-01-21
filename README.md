# pixl
pixl is a lightweight image processing library, written in C++11.

The main goals of this project are ease of use and performance. 
All operations can optionally be run on multiple threads.

Image decoding/encoding is done by third party libraries. Currently i am using [libpng](http://www.libpng.org/pub/png/libpng.html) png, [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/) for jpeg and [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) + [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) for everything else.
While the stb libraries are both very convenient to use, they not very performant or secure. 
In the future i am going to add more decoding/encoding options, but until then do NOT use this library in a production environment.

## Usage
```cpp
#include <pixl/pixl.h>

int main() {
	// load image
	auto image = pixl::read("path/to/image.png");

	// flip image horizontally
	pixl::FlipTransformation flip;
	flip.numThreads = 4;
	flip.apply(image);

	// write flipped image
	pixl::write("path/to/flipped_image.png", image);
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
The following libraries must be installed as shared libraries on the system:

- [libpng](http://www.libpng.org/pub/png/libpng.html) for png decoding & encoding
- [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/) for fast jpeg decoding & encoding

These libraries will be statically linked with pixl:

- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for reading other file formats. Will be removed soon
- [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) for writing other file formats. Will be removed soon.

Additionally i use [catch](https://github.com/philsquared/Catch) for unit testing.

## Building
I am using CMake to build the library + examples.    
Currently only Linux is supported. 

### Building on Linux
```
cmake .
make
```