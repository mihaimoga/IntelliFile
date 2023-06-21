/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#pragma once

// CQuickAccessDlg dialog

class CQuickAccessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuickAccessDlg)

public:
	CQuickAccessDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CQuickAccessDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QuickAccessDlg };
#endif

public:
	CListBox m_listFavoriteFolders;
	CButton m_ctrlQuickAccess;
	CButton m_ctrlAddFolder;
	CButton m_ctrlRemoveFolder;
	CString m_strSelectedFolder;
	CString m_strSelectedItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkFolderList();
	afx_msg void OnBnClickedAccess();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();

	DECLARE_MESSAGE_MAP()
};
