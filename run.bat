@echo off

>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"

if %errorlevel% neq 0 (
    echo You must run this script as Administrator.
    pause
    goto :eof
)

set filename=main

gcc %filename%.c -o %filename%.exe 2> error_log.txt

if %errorlevel% equ 0 (
    echo Compilation successful!
    %filename%.exe
) else (
    echo Compilation failed.
)

pause
