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