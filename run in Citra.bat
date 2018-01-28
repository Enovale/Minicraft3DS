@echo off
echo Building 3DSX/ELF/SMDH...
make
echo Running in citra
%localappdata%/Citra/canary-mingw/citra-qt.exe result/Minicraft3DS.3dsx