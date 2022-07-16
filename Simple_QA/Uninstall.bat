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
 
echo Uninstall...

adb kill-server

if exist C:\QA_TEST (RMDIR /S /Q C:\QA_TEST)
del "%UserProfile%\Desktop\Simple_QA.lnk"
del "%UserProfile%\Desktop\ScrCpy.lnk"

if exist C:\ProgramData\chocolatey (RMDIR /S /Q "C:\ProgramData\chocolatey")
if exist "C:\Program Files\GraphicsMagick-1.3.31-Q8" ("C:\Program Files\GraphicsMagick-1.3.31-Q8\unins000.exe")
if exist "C:\Program Files\GraphicsMagick-1.3.32-Q8" ("C:\Program Files\GraphicsMagick-1.3.32-Q8\unins000.exe")

reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v ChocolateyInstall /f
reg delete "HKEY_CURRENT_USER\Environment" /v ChocolateyLastPathUpdate /f

"%~dp0\deleteEnviroment.vbs"

echo Finish!
pause