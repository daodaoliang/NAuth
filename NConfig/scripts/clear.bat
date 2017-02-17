rmdir /S /Q %~dp0..\NConfig\release
rmdir /S /Q %~dp0..\NConfig\debug
rmdir /S /Q %~dp0..\NConfig\build_
rmdir /S /Q %~dp0..\example\build_
rmdir /S /Q %~dp0..\example\release
rmdir /S /Q %~dp0..\example\debug
rmdir /S /Q %~dp0..\AppCustomConfig\build_
rmdir /S /Q %~dp0..\AppCustomConfig\release
rmdir /S /Q %~dp0..\AppCustomConfig\debug
rmdir /S /Q %~dp0..\bin
del /Q %~dp0..\Makefile*
del /Q %~dp0..\NConfig\Makefile*
del /Q %~dp0..\example\Makefile*
del /Q %~dp0..\AppCustomConfig\Makefile*
