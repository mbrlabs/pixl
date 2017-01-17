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

#ifndef PIXL_CLI_PARSER_H
#define PIXL_CLI_PARSER_H

struct CliArg {
    CliArg(std::string name, bool hasParam) : name(name), hasParam(hasParam) {}

    std::string name;
    bool hasParam;
    std::string param;
};

struct CliSubcommand {
    CliSubcommand(std::string name) : name(name) {}
    ~CliSubcommand() {}
    void addArg(CliArg* arg) { this->args.push_back(arg); }

    std::string name;
    std::vector<CliArg*> args;
};

struct CliParserResult {
    CliParserResult() {}
    ~CliParserResult() {}

    bool hasArg(CliArg* arg) {
        for (const auto& a : args) {
            if (a == arg)
                return true;
        }
        return false;
    }

    std::string errorMsg;
    std::vector<CliArg*> args;
    CliSubcommand* subcommand = 0;
};

class CliParser {
public:
    CliParser() {}
    ~CliParser() {}

    void addSubcommand(CliSubcommand* sub) { this->subcommands.push_back(sub); }

    void addArg(CliArg* arg) { this->args.push_back(arg); }

    std::string help() { return "help"; }

    bool parse(int argc, char** argv, CliParserResult& args) { return true; }

private:
    std::vector<CliSubcommand*> subcommands;
    std::vector<CliArg*> args;
};

#endif