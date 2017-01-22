# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘
cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project(pixl)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Compilation flags                                               │
# └──────────────────────────────────────────────────────────────────┘
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")

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
add_library(pixl-static STATIC ${PIXL_SOURCES})
target_link_libraries(pixl-static ${PNG_LIBRARY} ${TurboJPEG_LIBRARIES})
target_include_directories(pixl-static PUBLIC ${STB_IMAGE} ${STB_IMAGE_WRITE} ${PNG_INCLUDE_DIR} ${TurboJPEG_INCLUDE_DIRS})

# SHARED library
add_library(pixl SHARED ${PIXL_SOURCES})
target_link_libraries(pixl ${PNG_LIBRARY} ${TurboJPEG_LIBRARIES})
target_include_directories(pixl PUBLIC ${STB_IMAGE} ${STB_IMAGE_WRITE} ${PNG_INCLUDE_DIR} ${TurboJPEG_INCLUDE_DIRS})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build cli tool                                                  │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB CLI_SOURCES
    cli/*
)
add_executable(cli ${CLI_SOURCES})
target_include_directories(cli PUBLIC src/ libs/rang/)
target_link_libraries(cli pixl-static)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build examples                                                  │
# └──────────────────────────────────────────────────────────────────┘

# --------------------------------------------------------------------------
# examples/e_flip.cc
add_executable(e_flip examples/e_flip.cc)
target_include_directories(e_flip PUBLIC src/)
target_link_libraries(e_flip pixl-static)

# --------------------------------------------------------------------------
# examples/e_libpng.cc
add_executable(e_libpng examples/e_libpng.cc)
target_include_directories(e_libpng PUBLIC src/)
target_link_libraries(e_libpng pixl-static)

# --------------------------------------------------------------------------
# examples/e_libjpegturbo.cc
add_executable(e_libjpegturbo examples/e_libjpegturbo.cc)
target_include_directories(e_libjpegturbo PUBLIC src/)
target_link_libraries(e_libjpegturbo pixl-static)

# --------------------------------------------------------------------------
# examples/e_chain.cc
add_executable(e_chain examples/e_chain.cc)
target_include_directories(e_chain PUBLIC src/)
target_link_libraries(e_chain pixl-static)

# --------------------------------------------------------------------------
# examples/e_resize.cc
add_executable(e_resize examples/e_resize.cc)
target_include_directories(e_resize PUBLIC src/)
target_link_libraries(e_resize pixl-static)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build test suite                                                │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_TEST_SOURCES
    tests/*
)
set(CATCH "libs/catch-1.6.0")
add_executable(tests ${PIXL_SOURCES} ${PIXL_TEST_SOURCES})
target_include_directories(tests PUBLIC src/ ${CATCH})
target_link_libraries(tests pixl-static)