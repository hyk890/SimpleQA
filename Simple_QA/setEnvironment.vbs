Set objShell = CreateObject("WScript.Shell")
Set objEnv = objShell.Environment("System")
 
PathToAdd = "C:\QA_TEST\batchfile;C:\QA_TEST\device_driver;C:\QA_TEST\compiler\bin;C:\QA_TEST\compiler\msys;"
oldSystemPath = objEnv("PATH")
newSystemPath = oldSystemPath & ";" & PathToAdd
objEnv("PATH") = newSystemPath