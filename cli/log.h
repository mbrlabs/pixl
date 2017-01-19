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

#ifndef PIXL_CLI_LOG_H
#define PIXL_CLI_LOG_H

#include <iostream>
#include <rang.hpp>

#include "config.h"

#define LOG_ERROR(msg)                                                                         \
    std::cout << rang::fg::red << rang::style::bold << "[ERROR] " << rang::style::reset << msg \
              << std::endl;
#define LOG_WARNING(msg)                                                                     \
    std::cout << rang::fg::yellow << rang::style::bold << "[WARNING] " << rang::style::reset \
              << msg << std::endl;
#define LOG_INFO(msg)                                                                          \
    std::cout << rang::fg::cyan << rang::style::bold << "[INFO] " << rang::style::reset << msg \
              << std::endl;
#define LOG_SUCCESS(msg)                                                                           \
    std::cout << rang::fg::green << rang::style::bold << "[SUCCESS] " << rang::style::reset << msg \
              << std::endl;
#ifdef ENABLE_DEBUG_OUTPUT
#define LOG_DEBUG(msg)                                                                          \
    std::cout << rang::fg::gray << rang::style::bold << "[DEBUG] " << rang::style::reset << msg \
              << std::endl;
#else
#define LOG_DEBUG(msg)
#endif

#endif