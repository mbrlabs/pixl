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

#include "job.h"

// ----------------------------------------------------------------------------
Job::Job(std::string name, pixl::Operation* operation) : name(name), operation(operation) {
}

// ----------------------------------------------------------------------------
void Job::setInfoHandler(std::function<void(const std::string&)> handler) {
    this->infoHandler = handler;
}

// ----------------------------------------------------------------------------
void Job::start(std::function<void(bool)> handler) {
    this->doneHandler = handler;

    postInfoMessage("Starting job: " + this->name);
    // TODO do work
    postInfoMessage("Job done");

    doneHandler(true);
}

// ----------------------------------------------------------------------------
void Job::postInfoMessage(const std::string message) {
    if (this->infoHandler != nullptr) {
        this->infoHandler(message);
    }
}