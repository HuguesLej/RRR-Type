@echo off
setlocal

REM Define the light blue color code
set CYAN=-ForegroundColor Cyan
REM Define the light green color code
set LIGHT_GREEN=-ForegroundColor Green
REM Define the light red color code
set LIGHT_RED=-ForegroundColor Red


if "%1"=="" (
    call :install
) else if "%1"=="rebuild" (
    call :rebuild
) else if "%1"=="re" (
    call :rebuild
) else (
    powershell -command "Write-Host 'Invalid arguments.' %CYAN%"
    powershell -command "Write-Host 'Usage: %0' %CYAN%"
    powershell -command "Write-Host '       %0 [rebuild|re]' %CYAN%"
    exit /b 1
)

if %errorlevel% neq 0 (
    powershell -command "Write-Host 'An error occurred.' %LIGHT_RED%"
    exit /b 1
)

endlocal
powershell -command "Write-Host 'Build completed successfully.' %LIGHT_GREEN%
exit /b 0


:install_cmake
    where cmake >nul 2>nul
    if %errorlevel% neq 0 (
        REM Install CMake
        winget install -e --id Kitware.CMake
        if %errorlevel% neq 0 if %errorlevel% neq 1 (
            powershell -command "Write-Host 'Failed to install CMake. Please check for errors.' %LIGHT_RED%"
            exit /b 1
        )
    )

    exit /b 0


:install
    REM Check if winget is installed
    where winget >nul 2>nul
    if %errorlevel% neq 0 (
        powershell -command "Write-Host 'winget not found. Please install it from the Microsoft Store or ensure your Windows version is up to date.' %LIGHT_RED%"
        exit /b 1
    )

    call :install_cmake
    if %errorlevel% neq 0 (
        exit /b 1
    )

    git submodule update --init --recursive
    if %errorlevel% neq 0 (
        powershell -command "Write-Host 'Failed to update submodules. Please check for errors.' %LIGHT_RED%"
        exit /b 1
    )

    if not exist ".\vcpkg\vcpkg.exe" (
        cd vcpkg
        call .\bootstrap-vcpkg.bat
        if %errorlevel% neq 0 (
            powershell -command "Write-Host 'Failed to bootstrap vcpkg. Please check for errors.' %LIGHT_RED%"
            exit /b 1
        )
        cd ..
    )

    .\vcpkg\vcpkg.exe install

    REM Create bin and build directories if they don't exist
    if not exist "bin" mkdir bin
    if not exist "build" mkdir build

    REM Check if the directories were created successfully
    if not exist "build" (
        powershell -command "Write-Host 'The build directory does not exist.' %LIGHT_RED%"
        exit /b 1
    )
    if not exist "bin" (
        powershell -command "Write-Host 'The bin directory does not exist.' %LIGHT_RED%"
        exit /b 1
    )

    REM Configure CMake
    powershell -command "Write-Host 'Configuring CMake...' %CYAN%"
    cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_PREFIX_PATH=vcpkg_installed -B build -S .
    if %errorlevel% neq 0 (
        exit /b 1
    )

    REM Build the project
    powershell -command "Write-Host 'Building the project...' %CYAN%"
    cmake --build build
    if %errorlevel% neq 0 (
        exit /b 1
    )

    powershell -command "Write-Host 'Build completed successfully!' %CYAN%"

    exit /b 0


:rebuild
    if not exist "build" (
        powershell -command "Write-Host 'The build directory does not exist. Please rerun the install script with no arguments.' %LIGHT_RED%"
        exit /b 1
    )
    if not exist "bin" (
        powershell -command "Write-Host 'The bin directory does not exist. Please rerun the install script with no arguments.' %LIGHT_RED%"
        exit /b 1
    )

    where cmake >nul 2>nul
    if %errorlevel% neq 0 (
        powershell -command "Write-Host 'CMake not found. Please rerun the install script with no arguments.' %LIGHT_RED%"
        exit /b 1
    )

    call .\clean.bat
    powershell -command "Write-Host 'Rebuilding the project...' %CYAN%"
    cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_PREFIX_PATH=vcpkg_installed -B build -S .
    cmake --build build

    exit /b 0
