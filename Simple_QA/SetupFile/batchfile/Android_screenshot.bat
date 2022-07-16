@echo off
call filename.bat
c:
cd %UserProfile%/Desktop
adb shell screencap -p /sdcard/%filename%.png
adb pull /sdcard/%filename%.png
ffmpeg -i %filename%.png -vf scale=iw/2:-1 screen.png
move screen.png %filename%.png
adb shell rm -f /sdcard/%filename%.png
pause
exit

REM gm mogrify -resize 640x640 %UserProfile%/Desktop/%filename%.png
REM magick mogrify -resize 640x640 %UserProfile%/Desktop/%filename%.png