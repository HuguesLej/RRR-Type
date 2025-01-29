@echo off
setlocal

REM Define the light blue color code
set CYAN=-ForegroundColor Cyan
REM Define the light green color code
set LIGHT_GREEN=-ForegroundColor Green
REM Define the light red color code
set LIGHT_RED=-ForegroundColor Red


call .\clean.bat

powershell -command "Write-Host 'Removing vcpkg_installed directory...' %CYAN%"
powershell -command "Remove-Item -Recurse -Force .\vcpkg_installed"

if exist "%LOCALAPPDATA%\vcpkg" (
    powershell -command "Write-Host 'Remove vcpkg cache...' %CYAN%"
    powershell -command "Remove-Item -Recurse -Force %LOCALAPPDATA%\vcpkg"
    if %errorlevel% neq 0 (
        powershell -command "Write-Host 'An error occurred.' %LIGHT_RED%"
        exit /b 1
    )
)

if exist ".\vcpkg\vcpkg" (
    powershell -command "Write-Host 'Clean up vcpkg submodule...' %CYAN%"
    call git submodule deinit -f vcpkg
)


endlocal
powershell -command "Write-Host 'Uninstall completed successfully.' %LIGHT_GREEN%"
exit /b 0
