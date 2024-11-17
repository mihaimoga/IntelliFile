/* Copyright (C) 2022-2025 Stefan-Mihai MOGA
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

// CSelectFileDlg dialog

class CSelectFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectFileDlg)

public:
	CSelectFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSelectFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SelectFileDlg };
#endif

protected:
	CEdit m_ctrlSearchFor;
	CButton m_ctrlFileDateCheck;
	CDateTimeCtrl m_ctrlFileDateFrom;
	CDateTimeCtrl m_ctrlFileTimeFrom;
	CDateTimeCtrl m_ctrlFileDateTo;
	CDateTimeCtrl m_ctrlFileTimeTo;
	CButton m_ctrlFileSizeCheck;
	CComboBox m_ctrlFileSizeSign;
	CEdit m_ctrlFileSizeAmount;
	CComboBox m_ctrlFileSizeType;
	CButton m_ctrlFileAttrCheck;
	CButton m_ctrlFileAttrReadOnly;
	CButton m_ctrlFileAttrHidden;
	CButton m_ctrlFileAttrSystem;
	CButton m_ctrlFileAttrArchive;
	CButton m_ctrlFileAttrDirectory;
	CButton m_ctrlOkButton;
public:
	bool m_bHideDirectoryFlag;
	CString m_strSearchFor;
	bool m_bFileDateCheck;
	COleDateTime m_ftDateTimeFrom;
	COleDateTime m_ftDateTimeTo;
	bool m_bFileSizeCheck;
	TCHAR m_chFileSize; // sign
	ULONGLONG m_nFileSize; // amount
	bool m_bFileAttrCheck;
	DWORD m_dwFileAttrData;
	DWORD m_dwFileAttrMask;
public:
	int m_nFileSizeSign;
	CString m_strFileSize;
	int m_nFileSizeType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnChangeSearchFor();
	afx_msg void OnClickedDateBetween();
	afx_msg void OnClickedFileSizeCheck();
	afx_msg void OnClickedFileAttrCheck();

	DECLARE_MESSAGE_MAP()
};
