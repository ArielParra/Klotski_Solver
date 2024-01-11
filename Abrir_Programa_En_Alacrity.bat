@echo off
mode 35,3
if not DEFINED IS_MINIMIZED set IS_MINIMIZED=1 && start "" /min "%~f0" %* && exit
.\alacritty.exe -o "window.startup_mode=Fullscreen" --command .\Klotski-Windows.exe /fullscreen
exit