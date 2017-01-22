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

#include <iostream>

#include "pixl.h"

extern "C" {

	// ----------------------------------------------------------------------------
	void pixl_say_hello() {
		std::cout << "Hello from std::cout" << std::endl;
	}

	// ----------------------------------------------------------------------------
	void* pixl_load_image(const char* path) {
		return pixl::read(path);
	}

	// ----------------------------------------------------------------------------
	void pixl_destroy_image(void* image) {
		delete static_cast<pixl::Image*>(image);
	}

	// ----------------------------------------------------------------------------
	void pixl_save_image(const char* path, void* image) {
		pixl::write(path, static_cast<pixl::Image*>(image));
	}

	// ----------------------------------------------------------------------------
	void pixl_resize(void* image, unsigned int width, unsigned int height, unsigned int num_threads) {
		auto img = static_cast<pixl::Image*>(image);
		pixl::ResizeTransformation resize(width, height);
		resize.numThreads = num_threads;
		resize.apply(img);
	}

	// ----------------------------------------------------------------------------
	void pixl_flip(void* image, int orientation, unsigned int num_threads) {
		auto img = static_cast<pixl::Image*>(image);
		
		pixl::Orientation orient;
		if(orientation == PIXL_ORIENTATION_VERTICAL) {
			orient = pixl::Orientation::VERTICAL;
		} else if(orientation == PIXL_ORIENTATION_HORIZONTAL) {
			orient = pixl::Orientation::HORIZONTAL;
		} else {
			return;
		}

		pixl::FlipTransformation flip(orient);
		flip.numThreads = num_threads;
		flip.apply(img);
	}

}