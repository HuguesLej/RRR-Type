# Windows Installation with Scripts

This document provides instructions on how to install, clean, or uninstall the R-Type project on Windows systems using the provided Batch scripts.

To use the scripts, run them in a PowerShell terminal from the project root.


## Install and Compile

To install the required packages, dependencies, and compile the project, run:

```powershell
.\install.bat
```


## Recompile

To recompile the project without reinstalling dependencies, use the `re` or `rebuild` argument:

```powershell
.\install.bat re
```
Or:
```powershell
.\install.bat rebuild
```


## Clean Compilation Files

To remove previous build files (without affecting installed dependencies), run:

```powershell
.\clean.bat
```


## Uninstall

To remove both the project build and all installed dependencies, including cached ones, run:

```powershell
.\uninstall.bat
```

**Note:** If you want to completely remove the project from your machine, first run the uninstall script, then manually delete the project directory.
