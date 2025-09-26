# Convex Hull C++ Implementation

## Prerequisites
* CMake ≥ 3.10
* MSYS2 with the ucrt64 environment
* Installed compilers:
*   C:/msys64/ucrt64/bin/gcc.exe
*   C:/msys64/ucrt64/bin/g++.exe
* Make sure C:/msys64/ucrt64/bin is in your PATH when running from PowerShell, CMD, or VS Code.

## Usage
* Configure the project using the GCC preset
*   cmake --preset GCC
* Build the executable
*   cmake --build --preset GCC
* Run the program with input file as a command-line argument
*   ./out/build/GCC/Test.exe <Input_file_name>

The output will be located in the "output" directory
