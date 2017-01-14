# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘
cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_OUTPUT_PATH "bin")

project(pixl)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Compilation flags                                               │
# └──────────────────────────────────────────────────────────────────┘
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build static library libpixl.a                                  │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_SOURCES
    src/pixl/*
)
set(STB_IMAGE libs/stb_image-2.13)
set(STB_IMAGE_WRITE libs/stb_image-write-1.02)

add_library(pixl STATIC ${PIXL_SOURCES})
target_include_directories(pixl PUBLIC ${STB_IMAGE} ${STB_IMAGE_WRITE})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build examples                                                  │
# └──────────────────────────────────────────────────────────────────┘

# --------------------------------------------------------------------------
add_executable(pixltest examples/main.cc)
target_link_libraries(pixltest pixl)