/* Copyright (C) 2022-2026 Stefan-Mihai MOGA
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

#pragma once

#include "VersionInfo.h"

// CCheckForUpdatesDlg dialog

class CCheckForUpdatesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckForUpdatesDlg)

public:
	CCheckForUpdatesDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCheckForUpdatesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CheckForUpdatesDlg };
#endif

public:
	CStatic m_ctrlStatusMessage;
	CProgressCtrl m_ctrlProgress;
	CVersionInfo m_pVersionInfo;
protected:
	DWORD m_nUpdateThreadID;
	HANDLE m_hUpdateThread;
	UINT_PTR m_nTimerID;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
