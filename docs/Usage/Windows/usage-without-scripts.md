# Windows Installation without Scripts

This document provides instructions on how to install, clean, or uninstall the R-Type project on Windows systems without using the provided Batch scripts.

All commands should be run from the project root in a PowerShell terminal.


## Prerequisites

Before proceeding, ensure that [CMake](https://cmake.org/download/) is installed on your system.


## Install and Compile


### Install Dependencies

To install required packages, run the following commands:

```powershell
git submodule update --init --recursive
cd vcpkg
./bootstrap-vcpkg.bat
cd ..
./vcpkg/vcpkg.exe install
```


### Configure Compilation

To configure compilation tools, run:

```powershell
cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_PREFIX_PATH=vcpkg_installed -B build -S .
```


### Build Project

To build the project, run:

```powershell
cmake --build build
```


## Recompile

This step allows to recompile the project without reinstalling dependencies.


### Reconfigure Compilation

To reconfigure compilation, first run the [clean compilation steps](#clean-compilation-files), then run the [configure compilation step](#configure-compilation).


### Rebuild Project

To rebuild the project, run:

Run the [build project step](#build-project).


## Clean Compilation Files

To remove previous build files (without affecting installed dependencies), run:

```powershell
Get-ChildItem -Path build -Exclude .gitkeep | Remove-Item -Recurse -Force
Get-ChildItem -Path bin -Exclude .gitkeep | Remove-Item -Recurse -Force
```


## Uninstall

To remove both the project build and all installed dependencies, including cached ones, first run the [clean compilation steps](#clean-compilation-files), then run:

```powershell
Remove-Item -Recurse -Force .\vcpkg_installed
Remove-Item -Recurse -Force %LOCALAPPDATA%\vcpkg
git submodule deinit -f vcpkg
```

**Note:** If you want to completely remove the project from your machine, first run the uninstall steps, then manually delete the project directory.
