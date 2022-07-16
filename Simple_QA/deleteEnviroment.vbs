Set oShell = WScript.CreateObject("WScript.Shell")
Set oEnv = oShell.Environment("SYSTEM")
Dim path(11)
path(0)=";C:\ProgramData\chocolatey\bin"
path(1)=";C:\QA_TEST\batchfile"
path(2)=";C:\QA_TEST\device_driver"
path(3)=";C:\QA_TEST\MinGW\bin"
path(4)=";C:\QA_TEST\MinGW\include"
path(5)=";C:\QA_TEST\MinGW\msys\1.0\bin"
path(6)="c:\program files\graphicsmagick-1.3.32-q8"
path(7)="c:\program files\graphicsmagick-1.3.31-q8"
path(8)=";C:\QA_TEST\compiler\bin"
path(9)=";C:\QA_TEST\compiler\include"
path(10)=";C:\QA_TEST\compiler\msys"



For i = 0 To 10
	ExistingPath = oEnv("PATH")
	var2 = Replace(ExistingPath,path(i),"")
	oEnv("PATH") = var2
Next
