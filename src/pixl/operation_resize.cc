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
#include <cstdlib>
#include <math.h>

#include "image.h"
#include "types.h"
#include "operation.h"

namespace pixl {

    void nearest_neighbor(Image* image, u32 width, u32 height) {
    	/*
	   	u8* temp = (u8*) malloc(sizeof(u8)*width*height*image->channels);
	    f64 x_ratio = image->width / (f64) width;
	    f64 y_ratio = image->height / (f64) height;

	    // TODO implement
    
	    image->width = width;
	    image->height = height;
	    free(image->data);
	    image->data = temp; 
	    */
    }

    void ResizeTransformation::apply(Image* image) {
        if (this->method == ResizeMethod::NEARSET_NEIGHBOR) {
            nearest_neighbor(image, this->width, this->height);
        }
    }
}