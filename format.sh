#!/bin/bash

CLANGF=clang-format

ls src/pixl/* | xargs $CLANGF -i -style=file
ls tests/* | xargs $CLANGF -i -style=file
ls examples/* | xargs $CLANGF -i -style=file