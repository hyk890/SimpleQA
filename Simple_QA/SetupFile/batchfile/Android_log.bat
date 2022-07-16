@echo off
call filename.bat
echo Log extracting...
adb logcat -v time *:d > %UserProfile%/Desktop/Android_log_%filename%.txt 
pause
exit