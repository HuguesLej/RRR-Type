# Project Usage

This document provides instructions on how to install and run the R-Type project on both Unix and Windows systems. It serves as a comprehensive guide for users to set up the project environment and execute the necessary binaries to get the project up and running.


## Prerequisites

Before proceeding, ensure that [git](https://git-scm.com/downloads) and a proper C++ compiler is installed on your system.

Examples of C++ compilers:
- **Unix**: [g++](https://gcc.gnu.org/install/download.html)
- **Windows**: [Microsoft Visual Studio (MSVC)](https://visualstudio.microsoft.com/vs/features/cplusplus/)


## Install the project

First, clone the project repository on your system. Then, you can find the installation guide for both Unix and Windows systems at the following locations:

- **Unix**: [Unix Installation Guide](Unix/index.md)
- **Windows**: [Windows Installation Guide](Windows/index.md)


## Run the Project

After installing the project on your system, follow the steps below to run it depending on your platform.


### Unix

Two binary files (`r-type_serveur` and `r-type_client`) are located in the `bin/` directory under the project root. To run each binary from the project root, use the following commands in a Unix terminal:

- **r-type_serveur:**
```bash
./bin/r-type_serveur <port> <ip_address>
```
For example:
```bash
./bin/r-type_serveur 8000 127.0.0.1
```

- **r-type_client:**
```bash
./bin/r-type_client <server_port> <server_ip_address>
```
For example:
```bash
./bin/r-type_client 8000 127.0.0.1
```


### Windows

Two binary files (`r-type_serveur.exe` and `r-type_client.exe`) are located in the `bin\Debug\` directory under the project root. To run each binary from the project root, use the following commands in a PowerShell terminal:

- **r-type_serveur:**
```powershell
.\bin\Debug\r-type_serveur.exe <port> <ip_address>
```
For example:
```powershell
.\bin\Debug\r-type_serveur.exe 8000 127.0.0.1
```

- **r-type_client:**
```powershell
.\bin\Debug\r-type_client.exe <server_port> <server_ip_address>
```
For example:
```powershell
.\bin\Debug\r-type_client.exe 8000 127.0.0.1
```
