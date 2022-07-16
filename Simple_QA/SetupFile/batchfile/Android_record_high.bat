@echo off
call filename.bat
echo Recording...
c:
cd %UserProfile%/Desktop
adb shell screenrecord --bit-rate 12000000 /sdcard/DCIM/recorddelete.mp4
timeout /t 2 > nul
adb pull /sdcard/DCIM/recorddelete.mp4 %filename%.mp4
adb shell rm -f /sdcard/DCIM/recorddelete.mp4
pause
exit