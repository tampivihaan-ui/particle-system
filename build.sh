#!/bin/bash

# Remove old executable
rm -f game.exe

# Compile
gcc -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib main.c -o game.exe -lraylib -lopengl32 -lgdi32 -lwinmm

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "✓ Build successful!"
    ./game.exe
else
    echo "✗ Build failed!"
fi 