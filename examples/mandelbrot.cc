//
// Copyright (c) 2017. See AUTHORS file.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <cstring>

#include <pixl/pixl.h>
#include <pixl/debug.h>

#define OUTPUT_FILE "mandelbrot.png"
#define MAX_ITERATIONS 512
#define WIDTH 1920
#define HEIGHT 1080

void putPixel(int col, int row, pixl::u8* data, int iterations) {
    double c_re = (col - WIDTH/2)*4.0/WIDTH;
    double c_im = (row - HEIGHT/2)*4.0/WIDTH;
    double x = 0, y = 0;
    double r2;

    int iteration = 0;
    while (x*x+y*y < 4 && iteration < MAX_ITERATIONS) {
        double x_new = x*x-y*y+c_re;
        y = 2*x*y+c_im;
        x = x_new;
        iteration++;
    } 

    if (iteration < MAX_ITERATIONS) {
        std::memset(data, 255, 3);
    } else {
        std::memset(data, 0, 3);        
    }
}

int main() {
    auto image = new pixl::Image(WIDTH, HEIGHT, 3);
    
    for(int x = 0; x < WIDTH; x++) {
        for(int y = 0; y < HEIGHT; y++) {
            putPixel(x, y, image->getPixel(x, y), MAX_ITERATIONS);
        }   
    }

    pixl::write(image, OUTPUT_FILE);
    return 0;
}