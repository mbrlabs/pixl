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

#include <functional>

#include <pixl/errors.h>
#include <pixl/io.h>
#include "job.h"

// ----------------------------------------------------------------------------
Job::Job(std::string name, std::string input, std::string output, pixl::Operation* operation)
    : name(name), input(input), output(output), operation(operation) {
}

// ----------------------------------------------------------------------------
void Job::setInfoHandler(std::function<void(const std::string&)> handler) {
    this->infoHandler = handler;
}

// ---------------------------------------------------------------------------
// TODO in case of an exception. Will the image be destructed ???
void Job::start(std::function<void(bool)> handler) {
    this->doneHandler = handler;

    // read image
    postInfoMessage("Decoding input image: " + this->input);
    pixl::Image* image;
    try {
        image = pixl::read(this->input.c_str());
        if (image == nullptr) {
            postInfoMessage("Failed to read image: " + this->input);
            doneHandler(false);
            return;
        }
    } catch (pixl::PixlException e) {
        postInfoMessage("Error while decoding; " + e.getMessage());
        doneHandler(false);
        return;
    }

    // apply operation
    postInfoMessage("Applying operation");
    operation->apply(image);

    // write image
    postInfoMessage("Encoding output image: " + this->output);
    try {
        pixl::write(image, this->output.c_str());
        doneHandler(true);
    } catch (pixl::PixlException e) {
        postInfoMessage("Error while decoding; " + e.getMessage());
        doneHandler(false);
        return;
    }
}

// ----------------------------------------------------------------------------
void Job::postInfoMessage(const std::string message) {
    if (this->infoHandler != nullptr) {
        this->infoHandler(message);
    }
}