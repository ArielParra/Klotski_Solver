@echo off
if exist "Klotski-Windows.exe " (
    del "Klotski-Windows.exe "
)
echo g++.exe -o Klotski-Windows.exe main.cpp -lwinmm icono.res -O3 -w -std=c++17
g++.exe -o Klotski-Windows.exe main.cpp -lwinmm icono.res -O3 -w -std=c++17
::make.exe
if exist "%temp%\tmp.vbs" (
    del "%temp%\tmp.vbs"
)
echo x=msgbox("Klotski_Windows.exe ha sido creado con exito", 64, "EXITO!") > "%temp%\tmp.vbs"
start %temp%\tmp.vbs
exit