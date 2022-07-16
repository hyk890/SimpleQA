@echo off
set YEAR=%date:~0,4%
set MONTH=%date:~5,2%
set DAY=%date:~8,2%
REM HOUR condition
set res=%time:~0,2% LSS 10
if %res% (
	set HOUR=0%time:~1,1%
)else (
	set HOUR=%time:~0,2%
)
set MINUTE=%time:~3,2%
set SECOND=%time:~6,2%
set filename=%YEAR%-%MONTH%-%DAY%_%HOUR%-%MINUTE%-%SECOND%
REM filename complete