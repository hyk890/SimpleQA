@echo off
Setlocal EnableDelayedExpansion
:: BatchGotAdmin
 :-------------------------------------
REM  --> Check for permissions
 >nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"

REM --> If error flag set, we do not have admin.
 if '%errorlevel%' NEQ '0' (
     goto UACPrompt
 ) else ( goto gotAdmin )

:UACPrompt
     echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
     echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
    "%temp%\getadmin.vbs"
     exit /B

:gotAdmin
     if exist "%temp%\getadmin.vbs" ( del "%temp%\getadmin.vbs" )
     pushd "%CD%"
     CD /D "%~dp0"
 :--------------------------------------  
REM install choco 
 @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command " [System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"

REM install image resize app 		
C:\ProgramData\chocolatey\bin\choco install sudo -y
C:\ProgramData\chocolatey\bin\choco install ffmpeg -y
C:\ProgramData\chocolatey\bin\choco install scrcpy -y


REM driver copy 
 if not exist C:\QA_TEST (
	mkdir "C:\QA_TEST"
	xcopy "%~dp0\SetupFile" C:\QA_TEST /e /h /k
	"%~dp0\setEnvironment.vbs"
	) else (
	xcopy "%~dp0\SetupFile" C:\QA_TEST /d /e /h /k
	)
	

REM C:\ProgramData\chocolatey\bin\choco install graphicsmagick -y

REM iOS Diskimagedirectory extraction
call C:\QA_TEST\iOSDiskList.bat

REM C:
REM cd C:\QA_TEST\compiler\bin 

echo Compiling...
REM timeout 2 > nul
REM g++ -W -Wall -O2 -o C:\QA_TEST\Simple_QA.exe "%~dp0\simple_qa.cpp"

call C:\QA_TEST\simplelink.vbs
	
pause