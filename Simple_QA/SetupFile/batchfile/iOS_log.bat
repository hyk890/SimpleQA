@echo off
call filename.bat

echo Log extracting...
idevicesyslog.exe > %UserProfile%/Desktop/iOS_log_%filename%.txt
pause
exit