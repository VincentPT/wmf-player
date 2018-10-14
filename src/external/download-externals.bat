setlocal
@echo off

SET CURR_DIR=%cd%
SET THIS_SCRIPT_PATH=%~dp0
cd %THIS_SCRIPT_PATH%


REM download Cinder at version v0.9.1
git clone --recursive https://github.com/cinder/Cinder.git
cd Cinder
git checkout tags/v0.9.1
cd ..

echo Download Cinder at version v0.9.1 completed!

REM copy some patch files to fix compiling issue at version v0.9.1 of Cinder for Windows & Visual Studio platform
xcopy %THIS_SCRIPT_PATH%\patch\msw\Cinder %THIS_SCRIPT_PATH%\Cinder /E /Y

REM download Cinder-ImGui at revision ccbf3a8
cd %THIS_SCRIPT_PATH%\Cinder\blocks
git clone https://github.com/simongeilfus/Cinder-ImGui.git
cd Cinder-ImGui
git checkout ccbf3a8 .
cd ..
REM copy some patch files of Cinder-ImGui to build with v1.65 of imgui
xcopy %THIS_SCRIPT_PATH%patch\global\Cinder-ImGui %THIS_SCRIPT_PATH%Cinder\blocks\Cinder-ImGui /E /Y

REM download imgui at version v1.65
git clone https://github.com/ocornut/imgui.git
cd imgui
git checkout tags/v1.65
cd ..

REM copy imgui source to Cinder-ImGui
xcopy .\imgui\*.h .\Cinder-ImGui\lib\imgui\ /Y
xcopy .\imgui\*.cpp .\Cinder-ImGui\lib\imgui\ /Y

echo Download Cinder block completed!

cd %CURR_DIR%
endlocal