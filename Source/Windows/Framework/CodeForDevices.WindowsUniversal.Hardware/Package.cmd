@echo off
setlocal

echo NuGet Package Script
echo ====================
echo Creates a release build then generates the NuGet package into the output directory.
echo Remember to update the version number and release notes in the "nuspec" file before each release.
echo.

rem * Check syntax
if "%~1" == "" (
	echo Configuration name parameter is required.
	endlocal
	exit /b 1
)
set ConfigurationName=%~1

echo.
echo %ConfigurationName% Package...

echo Initializing Visual Studio environment...
call "%~dp0..\..\Dependencies\Variables.cmd"
if %errorlevel% neq 0 goto error

echo.
echo Getting version....
set /p Version=<"%~dp0..\..\Version.txt"
if %errorlevel% neq 0 goto error
echo Version: %Version%

echo.
echo Creating NuGet Package...
pushd
"%~dp0..\..\Dependencies\NuGet\nuget.exe" pack "%~dp0CodeForDevices.WindowsUniversal.Hardware.nuspec" -Properties Configuration=Release;Platform=ARM -BasePath "%~dp0bin\%ConfigurationName%" -OutputDirectory "%~dp0bin\%ConfigurationName%\NuGet" -Version %Version% -ForceEnglishOutput -Verbosity detailed
if %errorlevel% neq 0 goto error
popd

echo.
echo Packaging successful.
endlocal
exit /b 0

:error
echo Error %errorlevel%
endlocal
exit /b 1
