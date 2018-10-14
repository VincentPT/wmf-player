setlocal
@echo off

SET CURR_DIR=%cd%
SET THIS_SCRIPT_PATH=%~dp0
cd %THIS_SCRIPT_PATH%

del CMakeCache.txt

SET PLATFORM=%1
IF '%PLATFORM%'=='' SET PLATFORM=x64

set PATH=%PATH%%THIS_SCRIPT_PATH%..\src\external\tools\cppan;

cmake -DCMAKE_GENERATOR_PLATFORM=Win32 -DCMAKE_BUILD_TYPE=Debug -DCINDER_PATH=%THIS_SCRIPT_PATH%..\src\external\Cinder ../src
cd %CURR_DIR%

endlocal