@echo off
setlocal EnableDelayedExpansion
set /p str=please input *.ipa file : 
echo ipa install...
ideviceinstaller -i %str%
pause
exit