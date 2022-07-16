@echo off
call filename.bat

set /p str1=please input first image filename : 
set /p str2=please input second image filename : 

set separator=\\
set str2=%str2:\=/%
set str2=%str2:~0,1%%separator%%str2:~1%


ffmpeg -i "%str1%" -vf "[in] pad=iw:2*ih [left]; movie="%str2%" [right]; [left][right] overlay=0:main_h/2:0 [out]" %UserProfile%\Desktop\image_%filename%.png
pause
exit