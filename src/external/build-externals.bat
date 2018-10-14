setlocal
@echo off

SET CURR_DIR=%cd%
SET THIS_SCRIPT_PATH=%~dp0
cd %THIS_SCRIPT_PATH%

SET CONFIGURATION=%1
IF '%CONFIGURATION%'=='' SET CONFIGURATION=Release

IF /I %CONFIGURATION%==debug (
    SET CONFIGURATION=Debug
) ELSE (
    SET CONFIGURATION=Release
)

SET PLATFORM=%2
IF '%PLATFORM%'=='' SET PLATFORM=x64

IF /I '%PLATFORM%'=='x64' (
	SET PLATFORM=x64
) ELSE (
	SET PLATFORM=Win32
)

cd %THIS_SCRIPT_PATH%\tools\cppan
cppan

echo Compiling Cinder...
REM build cinder with cmake
cd %THIS_SCRIPT_PATH%\Cinder
mkdir build
cd build
del CMakeCache.txt
cmake -DCINDER_TARGET=MSW -DCMAKE_GENERATOR_PLATFORM=%PLATFORM% ..
cmake --build . --target ALL_BUILD --config %CONFIGURATION%

echo Compiling Cinder completed!
REM pause
echo Compiling Cinder blocks...
cd %THIS_SCRIPT_PATH%Cinder\blocks\Cinder-ImGui
mkdir build
cd build
del CMakeCache.txt
cmake -DCMAKE_GENERATOR_PLATFORM=%PLATFORM% ..
cmake --build . --target ALL_BUILD --config %CONFIGURATION%

cd %CURR_DIR%
endlocal