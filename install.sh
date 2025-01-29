#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the cyan color code
CYAN="\033[1;36m"
# Define the light green color code
LIGHT_GREEN="\033[1;92m"
# Define the light red color code
LIGHT_RED="\033[1;91m"
# Define the reset color code to reset the terminal color after printing
NC="\033[0m"


install_cmake() {
    # Detect the OS type
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        OS=$ID
    else
        echo -e "${CYAN}Unsupported OS.${NC}"
        return 1
    fi

    # Install CMake if not found
    if ! command -v cmake &> /dev/null; then
        echo -e "${CYAN}CMake not found. Installing CMake...${NC}"

        case "$OS" in
            ubuntu|debian)
                sudo apt-get update -y && sudo apt-get install -y cmake
                ;;
            fedora)
                sudo dnf install -y cmake
                ;;
            arch)
                sudo pacman -S cmake
                ;;
            opensuse*)
                sudo zypper install -y cmake
                ;;
            *)
                echo -e "${CYAN}Unsupported OS for automatic installation.${NC}"
                return 1
                ;;
        esac
    fi

    return 0
}


install() {
    install_cmake
    if [ $? -ne 0 ]; then
        return 1
    fi

    git submodule update --init --recursive
    if [ $? -ne 0 ]; then
        echo -e "${LIGHT_RED}Failed to update the submodules.${NC}"
        return 1
    fi

    if [ ! -f "vcpkg/vcpkg" ]; then
        cd vcpkg
        ./bootstrap-vcpkg.sh
        if [ $? -ne 0 ]; then
            echo -e "${LIGHT_RED}Failed to bootstrap vcpkg.${NC}"
            return 1
        fi
        cd ..
    fi

    ./vcpkg/vcpkg install
    if [ $? -ne 0 ] || [ ! -d "vcpkg_installed" ]; then
        echo -e "${LIGHT_RED}Failed to install the dependencies with vcpkg.${NC}"
        return 1
    fi

    mkdir -p bin
    mkdir -p build

    if [ ! -d "build" ] || [ ! -d "bin" ]; then
        echo -e "${LIGHT_RED}The build or bin directory does not exist.${NC}"
        return 1
    fi

    echo -e "${CYAN}Configuring CMake...${NC}"
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH=./vcpkg_installed/x64-linux
    if [ $? -ne 0 ]; then
        echo -e "${LIGHT_RED}Failed to configure CMake.${NC}"
        return 1
    fi

    echo -e "${CYAN}Building the project...${NC}"
    cmake --build build
    if [ $? -ne 0 ]; then
        echo -e "${LIGHT_RED}Failed to build the project.${NC}"
        return 1
    fi

    return 0
}


rebuild() {
    if [ ! -d "build" ] || [ ! -d "bin" ]; then
        echo -e "${LIGHT_RED}The build or bin directory does not exist. Please rerun the script without arguments.${NC}"
        return 1
    fi

    if [ ! command -v cmake &> /dev/null ]; then
        echo -e "${LIGHT_RED}CMake not found. Please rerun the script without arguments.${NC}"
        return 1
    fi

    if [ ! -f "build/Makefile" ]; then
        echo -e "${LIGHT_RED}Makefile not found. Please rerun the script without arguments.${NC}"
        return 1
    fi

    echo -e "${CYAN}Rebuilding the project...${NC}"

    cd build
    make clean
    make re
    cd ..

    return 0
}


if [ $# -gt 1 ] || { [ $# -eq 1 ] && [ "$1" != "rebuild" ] && [ "$1" != "re" ]; }; then
    echo -e "${CYAN}Invalid arguments.${NC}"
    echo -e "${CYAN}Usage: $0${NC}"
    echo -e "${CYAN}       $0 [rebuild|re]${NC}"
    exit 1
fi


if [ $# -eq 0 ]; then
    install
    if [ $? -ne 0 ]; then
        exit 1
    fi
else
    rebuild
    if [ $? -ne 0 ]; then
        exit 1
    fi
fi

echo -e "${LIGHT_GREEN}Build completed successfully!${NC}"

exit 0
