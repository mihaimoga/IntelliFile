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

// IntelliFile.h : main header file for the IntelliFile application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "sinstance.h"

// CIntelliFileApp:
// See IntelliFile.cpp for the implementation of this class
//

class CIntelliFileApp : public CWinAppEx
{
public:
	CIntelliFileApp();

public:
	CInstanceChecker m_pInstanceChecker;
	Lexilla::CreateLexerFn m_pCreateLexer;
	HINSTANCE m_hScintilla;
	HINSTANCE m_hLexilla;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	HMODULE LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName);

// Implementation

public:
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIntelliFileApp theApp;
