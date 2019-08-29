@echo off

@: Environment
@set PATH=D:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;%PATH%
@set PATH=D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin;%PATH%
@set LIB=D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib;%LIB%
@set LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib;%LIB%
@set LIB=.\StlPort\;%LIB%
@set INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include;%INCLUDE%
@set INCLUDE=D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include;%INCLUDE%
@set INCLUDE=.\StlPort\;%INCLUDE%

@: Server
@del ".\\fonline_offplayer.dll"
cl.exe /nologo /MT /W3 /O2 /Gd /D "__SERVER" /Fo".\\" /Fd".\\fonline_offplayer.obj" /FD /c ".\\fonline_offplayer.cpp"
link.exe /nologo /dll /incremental:no /machine:I386 ".\\fonline_offplayer.obj" /out:".\\fonline_offplayer.dll"

@: Delete unnecessary stuff
@del ".\\fonline_offplayer.obj"
@del ".\\fonline_offplayer.exp"
@del ".\\fonline_offplayer.lib"
@del ".\\fonline_offplayer.idb"
