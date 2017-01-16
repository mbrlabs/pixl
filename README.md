# pixl
pixl is a lightweight image manipulation library, written in C++.

Image decoding/encoding is done by third party libraries. Currently i am using 
[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) and
[stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) 
which are both very convenient to use, but not very performant or secure. In the future i am going to add more
decoding/encoding options, but until then do NOT use this library in a production environment.

## Usage
```cpp
auto image = pixl::read("path/to/image.png");

// flip image horizontally
pixl::FlipTransformation flip(image);
flip.apply();

pixl::write("path/to/flipped_image.png", image);
```

## Building
I am using CMake to build the library + examples.    
Currently only Linux is supported. 

### Building on Linux
```
cmake .
make
```