@ECHO OFF

cl.exe /nologo /W0 patchhooker.cpp /MT /link /DLL /OUT:patchhooker.dll

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tp targetforpatchhooker.cpp /link /OUT:targetforpatchhooker.exe /SUBSYSTEM:CONSOLE
del *.obj *.lib *.exp