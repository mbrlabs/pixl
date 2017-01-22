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

#ifndef PIXL_PIXL_H
#define PIXL_PIXL_H

#ifdef __cplusplus
	#include "types.h"
	#include "errors.h"
	#include "image.h"
	#include "io.h"
	#include "operation.h"
#endif

// ----------------------------------------------------------------------------
// 					C API BELOW (implementation in c_api.cc)
// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

static const int PIXL_ORIENTATION_VERTICAL = 0;
static const int PIXL_ORIENTATION_HORIZONTAL = 1;

void pixl_say_hello();

void* pixl_load_image(const char* path);
void pixl_destroy_image(void* image);
void pixl_save_image(const char* path, void* image);

void pixl_resize(void* image, unsigned int width, unsigned int height, unsigned int num_threads);
void pixl_flip(void* image, int orientation, unsigned int num_threads);

#ifdef __cplusplus
}
#endif
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#endif