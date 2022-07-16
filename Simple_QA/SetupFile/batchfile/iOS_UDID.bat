@echo off

FOR /F "tokens=*" %%F IN ('idevice_id -l%') DO (
SET var=%%F
)
idevice_id -l > %UserProfile%/Desktop/iOS_UDID_%var%.txt
echo %var%
pause
exit