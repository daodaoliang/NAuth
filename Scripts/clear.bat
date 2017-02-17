rmdir /S /Q %~dp0..\NAuth\release
rmdir /S /Q %~dp0..\NAuth\debug
rmdir /S /Q %~dp0..\NAuth\build_
rmdir /S /Q %~dp0..\Example\build_
rmdir /S /Q %~dp0..\Example\release
rmdir /S /Q %~dp0..\Example\debug
rmdir /S /Q %~dp0..\bin
del /Q %~dp0..\Makefile*
del /Q %~dp0..\NAuth\Makefile*
del /Q %~dp0..\NAuth\Makefile*

call %~dp0..\NComputerInfo\Scripts\clear.bat
call %~dp0..\NEncryptionKit\Scripts\clear.bat
call %~dp0..\NConfig\Scripts\clear.bat
