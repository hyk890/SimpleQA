@echo off
call filename.bat

set /p str1=please input first video filename : 
set /p str2=please input second video filename : 

set separator=\\
set str2=%str2:\=/%
set str2=%str2:~0,1%%separator%%str2:~1%

ffmpeg -i "%str1%" -vf "[in] pad=2*iw:ih [left]; movie="%str2%" [right]; [left][right] overlay=main_w/2:0 [out]" %UserProfile%\Desktop\video_%filename%.mp4
pause
exit