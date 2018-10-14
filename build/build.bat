setlocal

SET CONFIGURATION=%1
IF '%CONFIGURATION%'=='' SET CONFIGURATION=Release

IF /I %CONFIGURATION%==debug (
    SET CONFIGURATION=Debug
) ELSE (
    SET CONFIGURATION=Release
)

SET CURR_DIR=%cd%
SET THIS_SCRIPT_PATH=%~dp0
cd %THIS_SCRIPT_PATH%
cmake --build . --target ALL_BUILD --config %CONFIGURATION%
cd %CURR_DIR%

endlocal