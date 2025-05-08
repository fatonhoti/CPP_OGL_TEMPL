@echo off
setlocal

set BUILD_DIR=build_release
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel %NUMBER_OF_PROCESSORS%

echo Release build complete. Executable located in: %BUILD_DIR%

endlocal 