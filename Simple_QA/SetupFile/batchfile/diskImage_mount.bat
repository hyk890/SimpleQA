@echo off
Setlocal EnableDelayedExpansion
c:
cd C:\QA_TEST\iPhoneOSDeviceSupport\%1 %2
ideviceimagemounter DeveloperDiskImage.dmg DeveloperDiskImage.dmg.signature
pause
exit