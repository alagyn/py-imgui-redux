: Execute the bash script
@echo off

set SCRIPT_DIR=%~dp0
"%PROGRAMFILES%\Git\bin\sh.exe" %SCRIPT_DIR%\build-wheels.sh