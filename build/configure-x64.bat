setlocal
@echo off

SET CURR_DIR=%cd%
SET THIS_SCRIPT_PATH=%~dp0
cd %THIS_SCRIPT_PATH%

del CMakeCache.txt

SET GENERATOR=%1

set PATH=%PATH%%THIS_SCRIPT_PATH%..\src\external\tools\cppan;

IF '%GENERATOR%'=='2012' (
	cmake -G "Visual Studio 11 2012 Win64" -DCMAKE_BUILD_TYPE=Debug -DCINDER_PATH=%THIS_SCRIPT_PATH%..\src\external\Cinder ../src
) ELSE IF '%GENERATOR%'=='2017' (
	cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug -DCINDER_PATH=%THIS_SCRIPT_PATH%..\src\external\Cinder ../src
) ELSE IF '%GENERATOR%'=='2013' (
	cmake -G "Visual Studio 12 2013 Win64" -DCMAKE_BUILD_TYPE=Debug -DCINDER_PATH=%THIS_SCRIPT_PATH%..\src\external\Cinder ../src
) ELSE (
	cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug -DCINDER_PATH=%THIS_SCRIPT_PATH%..\src\external\Cinder ../src
)

cd %CURR_DIR%

endlocal