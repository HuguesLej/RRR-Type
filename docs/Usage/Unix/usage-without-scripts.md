# Unix Installation without Scripts

This document provides instructions on how to install, clean, or uninstall the R-Type project on Unix systems without using the provided Bash scripts.

All commands should be run from the project root in a Unix terminal.


## Prerequisites

Before proceeding, ensure that [CMake](https://cmake.org/download/) is installed on your system.


## Install and Compile


### Install Dependencies

To install required packages, run the following commands:

```bash
git submodule update --init --recursive
cd vcpkg
./bootstrap-vcpkg.sh
cd ..
./vcpkg/vcpkg install
```


### Configure Compilation

To configure compilation tools, run:

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH=./vcpkg_installed/x64-linux
```


### Build Project

To build the project, run:

```bash
cmake --build build
```


## Recompile

To recompile the project without reinstalling dependencies, run:

```bash
cd build
make clean
make re
cd ..
```


## Clean Compilation Files

To remove previous build files (without affecting installed dependencies), run:

```bash
find build -mindepth 1 ! -name '.gitkeep' -exec rm -rf {} +
find bin -mindepth 1 ! -name '.gitkeep' -exec rm -rf {} +
```


## Uninstall

To remove both the project build and all installed dependencies, including cached ones, first run the [clean compilation steps](#clean-compilation-files), then run:

```bash
rm -rf vcpkg_installed
rm -rf ~/.cache/vcpkg
git submodule deinit -f vcpkg
```

**Note:** If you want to completely remove the project from your machine, first run the uninstall steps, then manually delete the project directory.
