# pixl
Pixl is a lightweight image manipulation library, written in C++.

## Usage
```cpp
auto image = pixl::read("path/to/image.png");
```

## Building
I am using CMake to build the library + examples.
Currently only Linux is supported. 

### Building on Linux
```
cmake .
make
```