@echo off
setlocal EnableDelayedExpansion
set /p str=please input *.apk file : 
echo apk install...
adb install %str%
pause
exit