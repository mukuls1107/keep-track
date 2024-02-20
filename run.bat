@echo off


set filename=main

gcc %filename%.c -o task.exe 2> error_log.txt

if %errorlevel% equ 0 (
    echo Compilation successful!
    task.exe
) else (
    echo Compilation failed.
)

pause
