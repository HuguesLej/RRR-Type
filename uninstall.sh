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


./clean.sh

echo -e "${CYAN}Remove vcpkg_installed directory...${NC}"
rm -rf vcpkg_installed

if [ -d ~/.cache/vcpkg ]; then
    echo -e "${CYAN}Remove vcpkg cache...${NC}"
    rm -rf ~/.cache/vcpkg
fi

if [ -f "./vcpkg/vcpkg" ]; then
    echo -e "${CYAN}Clean up vcpkg submodule...${NC}"
    git submodule deinit -f vcpkg
fi

echo -e "${LIGHT_GREEN}Uninstallation complete.${NC}"
