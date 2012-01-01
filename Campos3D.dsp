# Microsoft Developer Studio Project File - Name="Campos3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Campos3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Campos3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Campos3D.mak" CFG="Campos3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Campos3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Campos3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Campos3D - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "NDEBUG"
# ADD RSC /l 0x816 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Campos3D - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "_DEBUG"
# ADD RSC /l 0x816 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Campos3D - Win32 Release"
# Name "Campos3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Calculadora.cpp
# End Source File
# Begin Source File

SOURCE=.\Campos3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Campos3D.rc
# End Source File
# Begin Source File

SOURCE=.\Campos3DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Campos3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Complexo.cpp
# End Source File
# Begin Source File

SOURCE=.\Formula_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiaC.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiaR.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiasCilDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiasNCampos.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiasNCamposZDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiasRectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiasRectDlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\Ondas.cpp
# End Source File
# Begin Source File

SOURCE=.\OndasDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TEc.cpp
# End Source File
# Begin Source File

SOURCE=.\TEr.cpp
# End Source File
# Begin Source File

SOURCE=.\TM_Rectangular.cpp
# End Source File
# Begin Source File

SOURCE=.\TMc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Calculadora.h
# End Source File
# Begin Source File

SOURCE=.\Campos3D.h
# End Source File
# Begin Source File

SOURCE=.\Campos3DDoc.h
# End Source File
# Begin Source File

SOURCE=.\Campos3DView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Complexo.h
# End Source File
# Begin Source File

SOURCE=.\Formula_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\GuiaC.h
# End Source File
# Begin Source File

SOURCE=.\GuiaR.h
# End Source File
# Begin Source File

SOURCE=.\GuiasCilDlg.h
# End Source File
# Begin Source File

SOURCE=.\GuiasNCampos.h
# End Source File
# Begin Source File

SOURCE=.\GuiasNCamposZDlg.h
# End Source File
# Begin Source File

SOURCE=.\GuiasRectDlg.h
# End Source File
# Begin Source File

SOURCE=.\GuiasRectDlg2.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\Ondas.h
# End Source File
# Begin Source File

SOURCE=.\OndasDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TEc.h
# End Source File
# Begin Source File

SOURCE=.\TEr.h
# End Source File
# Begin Source File

SOURCE=.\TM_Rectangular.h
# End Source File
# Begin Source File

SOURCE=.\TMc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap_g.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Campos3D.ico
# End Source File
# Begin Source File

SOURCE=.\res\Campos3D.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Campos3DDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Res\guia_cil.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Campos3D : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:26:CG_IDR_POPUP_CAMPOS3_DVIEW:103
# 	1:25:CG_IDR_POPUP_FORMULA__DLG:104
# End Section
# Section Campos3D : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section Campos3D : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
