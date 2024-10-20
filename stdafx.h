/* Copyright (C) 2022-2024 Stefan-Mihai MOGA
This file is part of IntelliFile application developed by Stefan-Mihai MOGA.
IntelliFile is an alternative Windows version to the famous Total Commander!

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include "targetver.h"

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

 // Here, minimal DB support is requested.  No view is chosen.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#include <afxsock.h>            // MFC socket extensions

#include <afxdb.h>        // ODBC
#include <afxcview.h>
#include <afx.h>

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <string>
#include <sstream>
#include <iomanip>
#include <atlsync.h>
#include <vector>
#include <map>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>

#define ID_MFCLISTCTRL (WM_USER+0x1234)

#define SIZE_COLUMN_LENGTH 60
#define DATE_COLUMN_LENGTH 120
#define ATTR_COLUMN_LENGTH 40

//Pull in support for Scintilla \ Lexilla
#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(pop)
#include <ScintillaTypes.h>
#include <ScintillaCall.h>
#include <ScintillaMessages.h>
#include <ScintillaStructures.h>
#include <ILexer.h>
#include <Lexilla.h>
#include <SciLexer.h>
#include <ILoader.h>
#include <Scintilla.h>

#define INSTALLER_URL _T("https://www.moga.doctor/freeware/IntelliFileSetup.msi")
#define APPLICATION_URL _T("https://www.moga.doctor/freeware/IntelliFile.xml")
#define USER_MANUAL_URL _T("https://www.moga.doctor/intellifile/")
