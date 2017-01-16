#!/bin/bash

ls src/pixl/* | xargs clang-format -i -style=file
ls tests/* | xargs clang-format -i -style=file
