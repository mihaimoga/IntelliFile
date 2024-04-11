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

// CViewRichFileDlg dialog

class CViewRichFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewRichFileDlg)

public:
	CViewRichFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CViewRichFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ViewRichFileDlg };
#endif

public:
	CWndResizer m_pWindowResizer;
	CRichEditCtrl m_ctrlTextFile;
	CString m_strFilePath;
	UINT_PTR m_nTimerID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
