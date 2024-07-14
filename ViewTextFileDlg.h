/* Copyright (C) 2022-2024 Stefan-Mihai MOGA
This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#pragma once

#include "WndResizer.h"
#include "ScintillaCtrl.h"

// CViewTextFileDlg dialog

class CViewTextFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewTextFileDlg)

public:
	CViewTextFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CViewTextFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ViewTextFileDlg };
#endif

public:
	Scintilla::ILexer5* m_pCLexer;
	CWndResizer m_pWindowResizer;
	Scintilla::CScintillaCtrl m_ctrlTextFile;
	CString m_strFilePath;
	UINT_PTR m_nTimerID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SetAStyle(int style, COLORREF fore, COLORREF back = RGB(0xff, 0xff, 0xff), int size = -1, const char* face = nullptr);
	void DefineMarker(int marker, Scintilla::MarkerSymbol markerType, COLORREF fore, COLORREF back);

	DECLARE_MESSAGE_MAP()
};
