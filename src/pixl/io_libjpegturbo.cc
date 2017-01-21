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
#include "utils.h"

namespace pixl {

    Image* JpegTurboReader::read(const char* path) {
        PIXL_DEBUG("turbo: " << TJ_NUMXOP);
        auto x = tjInitCompress();

        StbiReader reader;
        return reader.read(path);
    }

    void JpegTurboWriter::write(const char* path, Image* image) {
        StbiWriter writer;
        writer.write(path, image);
    }
    
}