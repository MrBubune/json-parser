@echo off
setlocal

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