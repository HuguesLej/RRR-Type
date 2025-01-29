@echo off
setlocal

REM Define the light blue color code
set CYAN=-ForegroundColor Cyan
REM Define the light green color code
set LIGHT_GREEN=-ForegroundColor Green
REM Define the light red color code
set LIGHT_RED=-ForegroundColor Red


powershell -command "Write-Host 'Cleaning up the build directory...' %CYAN%"
if not exist "build" (
    powershell -command "Write-Host 'The build directory does not exist.' %LIGHT_RED%"
    exit /b 1
)

powershell -command "Get-ChildItem -Path build -Exclude .gitkeep | Remove-Item -Recurse -Force"
if %errorlevel% neq 0 (
    powershell -command "Write-Host 'An error occurred.' %LIGHT_RED%"
    exit /b 1
)


powershell -command "Write-Host 'Cleaning up the bin directory...' %CYAN%"
if not exist "bin" (
    powershell -command "Write-Host 'The bin directory does not exist.' %LIGHT_RED%"
    exit /b 1
)

powershell -command "Get-ChildItem -Path bin -Exclude .gitkeep | Remove-Item -Recurse -Force"
if %errorlevel% neq 0 (
    powershell -command "Write-Host 'An error occurred.' %LIGHT_RED%"
    exit /b 1
)

endlocal
powershell -command "Write-Host 'Cleanup complete.' %LIGHT_GREEN%"
exit /b 0
