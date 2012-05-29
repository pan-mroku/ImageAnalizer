@echo off
if [%pendrive%]==[] (
	set pendrive=1
	set path=%path%;%cd:~0,2%\home\MinGW\bin;%cd:~0,2%\home\git\bin
) 
@echo on
mingw32-make %*
mv analizer analizer.exe
pause