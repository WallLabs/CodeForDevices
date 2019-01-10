@echo off
setlocal
echo Release
echo =======
echo.
echo Performs a full build of all configurations then copies the output
echo to the central build directory for check-in and use by other
echo components or release.

echo.
echo Close Visual Studio now to avoid errors with locked files.
pause

echo.
echo Initializing Visual Studio environment...
call "%~dp0Dependencies\Variables.cmd"
if %errorlevel% neq 0 goto Error

echo.
echo Clean any previous builds...
if exist "%~dp0Temp\Build" rmdir "%~dp0Temp\Build" /s /q
if %errorlevel% neq 0 goto Error

echo.
echo Versioning...
call "%~dp0Version.cmd"
if %errorlevel% neq 0 goto Error

echo.
echo Building...
call "%~dp0Build.cmd" Debug
if %errorlevel% neq 0 goto Error
call "%~dp0Build.cmd" Release
if %errorlevel% neq 0 goto Error

echo.
echo Delete old build directory so that renamed or deleted items are cleaned...
if exist "%~dp0..\..\Build\Code for Devices on Windows" rmdir "%~dp0..\..\Build\Code for Devices on Windows" /s /q
if %errorlevel% neq 0 goto Error

echo.
echo Copying output to build directory...
robocopy "%~dp0Temp\Build" "%~dp0..\..\Build\Code for Devices on Windows" /s
if %errorlevel% gtr 7 goto Error

echo.
echo Clean temporary files...
rmdir "%~dp0Temp" /s /q
if %errorlevel% neq 0 goto Error

echo.
echo Build all successful.
endlocal
exit /b 0

:Error
echo Error %errorlevel%!
echo.
echo Note: Visual Studio must be closed before running this script to prevent build errors from locked files and caches.
endlocal
exit /b 1