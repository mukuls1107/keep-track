@echo off


set filename=main

gcc %filename%.c -o %filename%.exe 2> error_log.txt

if %errorlevel% equ 0 (
    echo Compilation successful!
    %filename%.exe
) else (
    echo Compilation failed.
)

pause
