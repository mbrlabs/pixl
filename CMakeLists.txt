# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘
cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
project(pixl)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Compilation flags                                               │
# └──────────────────────────────────────────────────────────────────┘
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pthread")

# ┌──────────────────────────────────────────────────────────────────┐
# │  libs 							                                 │
# └──────────────────────────────────────────────────────────────────┘
find_package(PNG REQUIRED)
include(FindTurboJPEG)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build libpixl-static.a & libpixl.so            			     │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_SOURCES
    src/pixl/*
)
set(STB_IMAGE libs/stb_image-2.13)
set(STB_IMAGE_WRITE libs/stb_image_write-1.02)

# STATIC library 
add_library(apixl STATIC ${PIXL_SOURCES})
target_link_libraries(apixl ${PNG_LIBRARY} ${TurboJPEG_LIBRARIES})
target_include_directories(apixl PUBLIC ${STB_IMAGE} ${STB_IMAGE_WRITE} ${PNG_INCLUDE_DIR} ${TurboJPEG_INCLUDE_DIRS})

# SHARED library
add_library(pixl SHARED ${PIXL_SOURCES})
target_link_libraries(pixl ${PNG_LIBRARY} ${TurboJPEG_LIBRARIES})
target_include_directories(pixl PUBLIC ${STB_IMAGE} ${STB_IMAGE_WRITE} ${PNG_INCLUDE_DIR} ${TurboJPEG_INCLUDE_DIRS})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build cli tool                                                  │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_TOOL_SOURCES
    cli/*
)
add_executable(pixl-cli ${PIXL_TOOL_SOURCES})
target_include_directories(pixl-cli PUBLIC src/ libs/rang/)
target_link_libraries(pixl-cli apixl)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build examples                                                  │
# └──────────────────────────────────────────────────────────────────┘

# --------------------------------------------------------------------------
# examples/examples.cc
add_executable(examples examples/examples.cc)
target_include_directories(examples PUBLIC src/)
target_link_libraries(examples apixl)

# --------------------------------------------------------------------------
# examples/mandelbrot.cc
add_executable(mandelbrot examples/mandelbrot.cc)
target_include_directories(mandelbrot PUBLIC src/)
target_link_libraries(mandelbrot apixl)

# --------------------------------------------------------------------------
# examples/bench.cc
add_executable(bench examples/bench.cc)
target_include_directories(bench PUBLIC src/)
target_link_libraries(bench apixl)
# ┌──────────────────────────────────────────────────────────────────┐
# │  Build test suite                                                │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_TEST_SOURCES
    tests/*
)
set(CATCH "libs/catch-1.6.0")
add_executable(tests ${PIXL_SOURCES} ${PIXL_TEST_SOURCES})
target_include_directories(tests PUBLIC src/ ${CATCH})
target_link_libraries(tests apixl)