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
IntelliEdit. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#pragma once
#include "EdgeWebBrowser.h"

// CWebBrowserDlg dialog

class CWebBrowserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebBrowserDlg)

public:
	CWebBrowserDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CWebBrowserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WebBrowserDlg };
#endif

protected:
	CWebBrowser m_pCustomControl;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};
