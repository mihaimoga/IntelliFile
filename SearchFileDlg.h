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

#pragma once
#include "WndResizer.h"
#include "FileList.h"
#include "MainFrame.h"

// CSearchFileDlg dialog

class CSearchFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchFileDlg)

public:
	CSearchFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSearchFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SearchFileDlg };
#endif

protected:
	CEdit m_ctrlSearchFor;
	CEdit m_ctrlSearchFolder;
	CButton m_ctrlFindText;
	CEdit m_ctrlInputText;
	CButton m_ctrlReplaceText;
	CEdit m_ctrlOutputText;
public:
	CProgressCtrl m_ctrlProgress;
	CMFCListCtrl m_ctrlFileList;
	CButton m_btnAdvance;
	CButton m_btnBrowse;
	CButton m_btnSearch;
	CMainFrame* m_pMainFrame;
protected:
	DWORD m_nSearchThreadID;
	HANDLE m_hSearchThread;

public:
	CFileSystem* m_pFileSystem;
	CWndResizer m_pWindowResizer;
	CString m_strSearchFor;
	CString m_strCurrentFolder;
	bool m_bFileDateCheck;
	COleDateTime m_ftDateTimeFrom;
	COleDateTime m_ftDateTimeTo;
	bool m_bFileSizeCheck;
	TCHAR m_chFileSize; // sign
	ULONGLONG m_nFileSize; // amount
	bool m_bFileAttrCheck;
	DWORD m_dwFileAttrData;
	DWORD m_dwFileAttrMask;
protected:
	int m_nFileSizeSign;
	CString m_strFileSize;
	int m_nFileSizeType;
public:
	bool m_bFindTextCheck;
	CString m_strFindText;
	bool m_bReplaceTextCheck;
	CString m_strReplaceText;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeSearchFor();
	afx_msg void OnClickedFindText();
	afx_msg void OnClickedReplaceText();
	afx_msg void OnClickedAdvance();
	afx_msg void OnClickedBrowse();
	afx_msg void OnClickedSearch();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()
};
