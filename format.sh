#!/bin/bash

CLANGF=clang-format-3.5

ls src/pixl/* | xargs $CLANGF -i -style=file
ls tests/* | xargs $CLANGF -i -style=file
ls examples/*.cc | xargs $CLANGF -i -style=file
ls cli/* | xargs $CLANGF -i -style=file