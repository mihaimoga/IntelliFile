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

// CViewAudioFileDlg dialog

class CViewAudioFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewAudioFileDlg)

public:
	CViewAudioFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CViewAudioFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ViewAudioFileDlg };
#endif
	CString m_strFilePath;
protected:
	DWORD m_nPlaySoundThreadID;
	HANDLE m_hPlaySoundThread;
	UINT_PTR m_nTimerID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
