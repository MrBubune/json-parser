@echo off
setlocal

echo === Deleting existing build directory if it exists ===
if exist build (
    rmdir /s /q build
)

echo.
echo.
echo === Creating build directory ===
mkdir build

cd build

echo.
echo.
echo === Running CMake configuration ===
cmake ..

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    exit /b %errorlevel%
)

echo.
echo.
echo === Building project in Debug mode ===
cmake --build . --config Debug

if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo.
echo.
echo === Running tests ===
ctest --output-on-failure -C Debug

if %errorlevel% neq 0 (
    echo Some tests failed!
    exit /b %errorlevel%
)

echo.
echo.
echo === All tests passed successfully! ===

endlocal
pause
