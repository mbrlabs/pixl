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

#ifndef PIXL_CLI_JOB_H
#define PIXL_CLI_JOB_H

#include <string>
#include <thread>
#include <functional>

#include <pixl/operation.h>

class Job {
public:
    Job(std::string name, std::string input, std::string output, pixl::Operation* operation);

    void setInfoHandler(std::function<void(const std::string&)> handler);
    void start(std::function<void(bool)> handler);

private:
    std::string name;
    std::string input;
    std::string output;
    pixl::Operation* operation;
    std::function<void(const std::string&)> infoHandler;
    std::function<void(bool)> doneHandler;

    void postInfoMessage(const std::string message);
};

#endif