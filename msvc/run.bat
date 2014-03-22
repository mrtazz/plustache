@ECHO OFF

REM @file run.bat
REM @brief Run the unit test.
REM @author Joshua Napoli <jnapoli@alum.mit.edu>

SETLOCAL

REM "ROOT" is the directory containing this script.
SET ROOT=%~dp0

REM Run the command given on the command line.
%*

REM Quit if the test command failed. Forward the command's exit code.
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%

REM Create a file to show that the test passed. This allows us to avoid re-running a passing test.
TYPE NUL>%1.passed

ENDLOCAL
EXIT 0
