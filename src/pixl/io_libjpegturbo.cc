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

#include <turbojpeg.h>

#include "io.h"
#include "types.h"
#include "utils.h"


namespace pixl {

	// ----------------------------------------------------------------------------
	u8* read_binary(const char* path, u64* length) {
	    FILE* file = fopen(path, "rb");
	    
	    // read file size
	    fseek(file, 0, SEEK_END);
	    *length = ftell(file);
	    
	    // setup data
	    u8* data = new u8[*length + 1];

	    // read file
	    fseek(file, 0, SEEK_SET);
	    fread(data, 1, *length, file);
	    fclose(file);

	    return data;
	}

    Image* JpegTurboReader::read(const char* path) {
        // read file
        u64 dataSize;
        u8* dataBuffer = read_binary(path, &dataSize);

        // jpg meta data
        int width, height, subsamp;

        // read meta data
        auto decoder = tjInitDecompress();
        auto result = tjDecompressHeader2(decoder, dataBuffer, dataSize, &width, &height, &subsamp);

        if(result == -1) {
 			PIXL_ERROR("Error: " + std::string(tjGetErrorStr()));
        	return nullptr;
        }

		PIXL_DEBUG("header decoding success");
		PIXL_DEBUG("width: " << width);
		PIXL_DEBUG("height: " << height);
		PIXL_DEBUG("subsamp: " << subsamp);

		// create decoded buffer
		int pitch = width * tjPixelSize[TJPF_RGB];
		u8* data = (u8*)malloc(pitch * height); 

		result = tjDecompress2(
			decoder,
			dataBuffer,
			dataSize,
			data,
			width, 
			pitch,
			height, 
			TJPF_RGB,
			0 // flags
		);

		if(result == -1) {
 			PIXL_ERROR("Error: " + std::string(tjGetErrorStr()));
 			return nullptr;
		}

		return new Image(width, height, 3, data);
    }

    void JpegTurboWriter::write(const char* path, Image* image) {
        StbiWriter writer;
        writer.write(path, image);
    }
    
}