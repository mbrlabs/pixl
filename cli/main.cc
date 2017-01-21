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

#include <vector>

#include "log.h"
#include "cli_parser.h"

void process_command(CliParserResult& result) {
    // TODO stuff
}

int main(int argc, char** argv) {
    LOG_INFO("pixl")

    CliParserResult result;
    CliParser parser;

    // Basic args
    CliArg version("v", false);
    CliArg help("h", false);
    parser.addArg(&version);
    parser.addArg(&help);

    // Shared subcommand args
    CliArg input("i", true);
    CliArg output("o", true);

    // Flip subcommand
    CliSubcommand flipCmd("flip");
    flipCmd.addArg(&input);
    flipCmd.addArg(&output);
    parser.addSubcommand(&flipCmd);

    // Resize subcommand
    CliArg resizeSize("s", true);
    CliSubcommand resizeCmd("resize");
    resizeCmd.addArg(&input);
    resizeCmd.addArg(&output);
    resizeCmd.addArg(&resizeSize);
    parser.addSubcommand(&resizeCmd);

    if (parser.parse(argc, argv, result)) {
        process_command(result);
    } else {
        LOG_ERROR("Invalid input: " << result.errorMessage);
    }

    return 0;
}