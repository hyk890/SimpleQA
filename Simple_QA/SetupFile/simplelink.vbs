set WshShell = WScript.CreateObject("WScript.Shell" )
strDesktop = WshShell.SpecialFolders("Desktop" )
set oShellLink = WshShell.CreateShortcut(strDesktop & "\Simple_QA.lnk" )
oShellLink.TargetPath="C:\QA_TEST\Simple_QA.exe"
oShellLink.Arguments = " /k %HOMEPATH%\cmd-startup.cmd"
oShellLink.WindowStyle = 1
oShellLink.IconLocation = "C:\QA_TEST\qa.ico"
oShellLink.Description = "cmdr"
oShellLink.WorkingDirectory = "%HOMEPATH%"
oShellLink.Hotkey = "Ctrl+Alt+C"
oShellLink.Save