# Microsoft Developer Studio Project File - Name="Scanner" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Scanner - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Scanner.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Scanner.mak" CFG="Scanner - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Scanner - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Scanner - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Scanner - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Scanner - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Scanner - Win32 Release"
# Name "Scanner - Win32 Debug"
# Begin Source File

SOURCE=.\AllScan.cpp
# End Source File
# Begin Source File

SOURCE=.\AllScan.h
# End Source File
# Begin Source File

SOURCE=.\CmdDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdDlg.h
# End Source File
# Begin Source File

SOURCE=.\DosScan.cpp
# End Source File
# Begin Source File

SOURCE=.\DosScan.h
# End Source File
# Begin Source File

SOURCE=.\HostScan.cpp
# End Source File
# Begin Source File

SOURCE=.\HostScan.h
# End Source File
# Begin Source File

SOURCE=.\IPEXPORT.H
# End Source File
# Begin Source File

SOURCE=.\Iphlpapi.h
# End Source File
# Begin Source File

SOURCE=.\IPTYPES.H
# End Source File
# Begin Source File

SOURCE=.\NetBIOSScan.cpp
# End Source File
# Begin Source File

SOURCE=.\NetBIOSScan.h
# End Source File
# Begin Source File

SOURCE=.\PortScan.cpp
# End Source File
# Begin Source File

SOURCE=.\PortScan.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanner.h
# End Source File
# Begin Source File

SOURCE=.\Scanner.rc
# End Source File
# Begin Source File

SOURCE=.\ScannerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScannerDlg.h
# End Source File
# Begin Source File

SOURCE=.\SnifferScan.cpp
# End Source File
# Begin Source File

SOURCE=.\SnifferScan.h
# End Source File
# Begin Source File

SOURCE=.\SNMPScan.cpp
# End Source File
# Begin Source File

SOURCE=.\SNMPScan.h
# End Source File
# Begin Source File

SOURCE=.\SQLScan.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLScan.h
# End Source File
# Begin Source File

SOURCE=.\SSSelectIP.cpp
# End Source File
# Begin Source File

SOURCE=.\SSSelectIP.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WeakKeyScan.cpp
# End Source File
# Begin Source File

SOURCE=.\WeakKeyScan.h
# End Source File
# End Target
# End Project
