@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" && cl /std:c++20 /EHsc /O2 /utf-8 /I "%~dp0..\..\..\Engine\include" /Fe:"%~dp0%1.exe" "%~dp0%1.cpp"
