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

#define VERSION "0.1.0"

#include <vector>

#include <pixl/pixl.h>

#include "log.h"
#include "job.h"
#include "cli_parser.h"

void process_command(CliParserResult& result);

// ----------------------------------------------------------------------------
// Statics used for cli parsing.
static CliParser parser;

static CliSubcommand flipCmd("flip");
static CliSubcommand resizeCmd("resize");

static CliArg helpArg("h", "Prints the help", false);
static CliArg versionArg("v", "Prints the version number", false);
static CliArg inputArg("i", "Path to the source image", true, true);
static CliArg outputArg("o", "Path to the output image", true, true);
static CliArg sizeArg("s",
                      "Specifies the new image dimensions for the output image. Must be in the "
                      "form 512x512 (width, height) or 1.2 (upscale) / 0.8 (downscale)",
                      true);


// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
    LOG_INFO("pixl")

    CliParserResult result;

    // Basic args
    parser.addArg(&versionArg);
    parser.addArg(&helpArg);

    // Flip subcommand
    flipCmd.addArg(&inputArg);
    flipCmd.addArg(&outputArg);
    parser.addSubcommand(&flipCmd);

    // Resize subcommand
    resizeCmd.addArg(&inputArg);
    resizeCmd.addArg(&outputArg);
    resizeCmd.addArg(&sizeArg);
    parser.addSubcommand(&resizeCmd);

    if (parser.parse(argc, argv, result)) {
        process_command(result);
    } else {
        LOG_ERROR("Invalid input: " << result.errorMessage);
    }

    return 0;
}

// ----------------------------------------------------------------------------
void execute_operation(std::string name, std::string& input, std::string& output, pixl::Operation* operation) {
    Job job(name, input, output, operation);
    job.setInfoHandler([&](const std::string& message) {
        LOG_INFO(message);
    });

    job.start([&](bool success) {
        if (success) {
            LOG_INFO("SUCCESS!!");
        } else {
            LOG_ERROR("ERROR!!");
        }
    });
}

// ----------------------------------------------------------------------------
void process_command(CliParserResult& result) {
    // Printing basic info
    if (result.subcommand == nullptr) {
        // Print help
        if (result.getArgument(helpArg.name) != nullptr) {
            parser.help();
        }

        // Print version
        if (result.getArgument(versionArg.name) != nullptr) {
            LOG_INFO(VERSION);
        }
        return;
    }

    pixl::Operation* operation;
    auto cmd = result.subcommand;

    // Resize
    if (cmd == &resizeCmd) {
        pixl::ResizeTransformation resize;
        // TODO parse width, height from cli result
        resize.width = 1024;
        resize.height = 1024;
        execute_operation("resize", inputArg.param, outputArg.param, &resize);
        // Flip
    } else if (cmd == &flipCmd) {
        pixl::FlipTransformation flip;
        // TODO parse orientation from cli result
        execute_operation("flip", inputArg.param, outputArg.param, &flip);
    }
}