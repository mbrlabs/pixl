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
# │  libs 							                                 │
# └──────────────────────────────────────────────────────────────────┘
find_package(PNG REQUIRED)
# ┌──────────────────────────────────────────────────────────────────┐
# │  Build static library libpixl.a                                  │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_SOURCES
    src/pixl/*
)
set(STB_IMAGE libs/stb_image-2.13)
set(STB_IMAGE_WRITE libs/stb_image_write-1.02)

add_library(pixl STATIC ${PIXL_SOURCES})
target_link_libraries(pixl ${PNG_LIBRARY})
target_include_directories(pixl PUBLIC ${STB_IMAGE} ${STB_IMAGE_WRITE} ${PNG_INCLUDE_DIR})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build examples                                                  │
# └──────────────────────────────────────────────────────────────────┘

# --------------------------------------------------------------------------
add_executable(e_flip examples/e_flip.cc)
target_include_directories(e_flip PUBLIC src/)
target_link_libraries(e_flip pixl)


# --------------------------------------------------------------------------
add_executable(e_libpng examples/e_libpng.cc)
target_include_directories(e_libpng PUBLIC src/)
target_link_libraries(e_libpng pixl)

# --------------------------------------------------------------------------
add_executable(e_chain examples/e_chain.cc)
target_include_directories(e_chain PUBLIC src/)
target_link_libraries(e_chain pixl)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Build test suite                                                │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB PIXL_TEST_SOURCES
    tests/*
)
set(CATCH "libs/catch-1.6.0")
add_executable(tests ${PIXL_SOURCES} ${PIXL_TEST_SOURCES})
target_include_directories(tests PUBLIC src/ ${CATCH})
target_link_libraries(tests pixl)