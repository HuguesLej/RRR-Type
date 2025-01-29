# Unix Installation with Scripts

This document provides instructions on how to install, clean, or uninstall the R-Type project on Unix systems using the provided Bash scripts.

To use the scripts, run them in a Unix terminal from the project root.


## Install and Compile

To install the required packages, dependencies, and compile the project, run:

```bash
./install.sh
```


## Recompile

To recompile the project without reinstalling dependencies, use the `re` or `rebuild` argument:

```bash
./install.sh re
```
Or:
```bash
./install.sh rebuild
```


## Clean Compilation Files

To remove previous build files (without affecting installed dependencies), run:

```bash
./clean.sh
```


## Uninstall

To remove both the project build and all installed dependencies, including cached ones, run:

```bash
./uninstall.sh
```

**Note:** If you want to completely remove the project from your machine, first run the uninstall script, then manually delete the project directory.
