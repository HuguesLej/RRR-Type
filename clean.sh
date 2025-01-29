#/bin/bash

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


echo -e "${CYAN}Cleaning up the build directory...${NC}"
if [ -d "build" ]; then
    find build -mindepth 1 ! -name '.gitkeep' -exec rm -rf {} +
else
    echo -e "${LIGHT_RED}The build directory does not exist.${NC}"
fi

echo -e "${CYAN}Cleaning up the bin directory...${NC}"
if [ -d "bin" ]; then
    find bin -mindepth 1 ! -name '.gitkeep' -exec rm -rf {} +
else
    echo -e "${LIGHT_RED}The bin directory does not exist.${NC}"
fi

echo -e "${LIGHT_GREEN}Cleanup complete.${NC}"
