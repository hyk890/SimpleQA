@echo off
call filename.bat

c:
cd %UserProfile%/Desktop
idevicescreenshot %filename%.png
ffmpeg -i %filename%.png -vf scale=iw/2:-1 screen.png
move screen.png %filename%.png
pause
exit

REM gm mogrify -resize 640x640 %filename%.png
REM magick mogrify -resize 640x640 %filename%.png