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

@: Client
@del ".\\fonline_renderhelper.dll"
cl.exe /nologo /MT /W3 /O2 /Gd /D "__CLIENT" /Fo".\\fonline_renderhelper.obj" /Fd".\\" /FD /c ".\\fonline_renderhelper.cpp"
link.exe /nologo /dll /incremental:no /machine:I386 ".\\fonline_renderhelper.obj" /out:".\\fonline_renderhelper.dll"

@: Delete unnecessary stuff
@del ".\\fonline_renderhelper.obj"
@del ".\\fonline_renderhelper.exp"
@del ".\\fonline_renderhelper.lib"
@del ".\\vc100.idb"