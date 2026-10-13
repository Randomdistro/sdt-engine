@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
cd /d "%~dp0"
cl /std:c++20 /EHsc /O2 /utf-8 /nologo /I "..\..\..\Engine\include" /Fe:np17_reset_1.exe np17_reset_1.cpp
