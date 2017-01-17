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

#include <pixl/pixl.h>

int main() {
    // load image
    auto image = pixl::read("../images/lenna.png");
    
    // create operations
    pixl::FlipTransformation flipH;
    pixl::FlipTransformation flipV;
    flipV.orientation = pixl::Orientation::VERTICAL;

    // add them to the chain
    pixl::OperationChain chain;
    chain.add(&flipH);
    chain.add(&flipV);    
    
    // apply chain
    chain.apply(image);

    // write flipped image
    pixl::write("lenna_stack.png", image);
    return 0;
}