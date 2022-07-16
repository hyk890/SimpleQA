@echo off
Setlocal EnableDelayedExpansion
c:
cd C:\QA_TEST\iPhoneOSDeviceSupport
C:\QA_TEST\compiler\msys\ls -l | C:\QA_TEST\compiler\msys\grep "^d" > C:\QA_TEST\list.txt 
REM dir /ad > C:\QA_TEST\list.txt 
if exist C:\QA_TEST\iOSDiskdirectoryList.txt del C:\QA_TEST\iOSDiskdirectoryList.txt

for /f "tokens=9,10 delims= " %%i in (C:\QA_TEST\list.txt) do (
		echo %%i %%j>> C:\QA_TEST\iOSDiskdirectoryList.txt
	)
if exist C:\QA_TEST\iOSDiskdirectoryList.txt del C:\QA_TEST\list.txt

pause