@echo off
setlocal

set BUILD_DIR=build_debug
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --parallel %NUMBER_OF_PROCESSORS%

echo Debug build complete. Executable located in: %BUILD_DIR%

endlocal