@echo off

@:1

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
@del ".\\fonline_tla.dll"
cl.exe /nologo /MT /W3 /O2 /Gd /D "__SERVER" /Fo".\\" /Fd".\\fonline_tla.obj" /FD /c ".\\fonline_tla.cpp"
link.exe /nologo /dll /incremental:no /machine:I386 ".\\fonline_tla.obj" /out:".\\fonline_tla.dll"

@: Client
@del ".\\fonline_tla_client.dll"
cl.exe /nologo /MT /W3 /O2 /Gd /D "__CLIENT" /Fo".\\fonline_tla_client.obj" /Fd".\\" /FD /c ".\\fonline_tla.cpp"
link.exe /nologo /dll /incremental:no /machine:I386 ".\\fonline_tla_client.obj" /out:".\\fonline_tla_client.dll"

@: Delete unnecessary stuff
@del ".\\fonline_tla.obj"
@del ".\\fonline_tla.exp"
@del ".\\fonline_tla.lib"
@del ".\\fonline_tla.idb"
@del ".\\fonline_tla_client.obj"
@del ".\\fonline_tla_client.exp"
@del ".\\fonline_tla_client.lib"
@del ".\\vc90.idb"

@pause