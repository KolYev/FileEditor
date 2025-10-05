@echo off
echo Compiling...
g++ main.cpp window.cpp -o main -luser32 -lgdi32
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Running program...
    main.exe
) else (
    echo Compilation failed!
)
pause
