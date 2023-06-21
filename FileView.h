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

#include "MFCListView.h"
#include "FileList.h"

class CMainFrame;

// CFileView view

class CFileView : public CMFCListView
{
	DECLARE_DYNCREATE(CFileView)

public:
	CFileView();           // protected constructor used by dynamic creation
	virtual ~CFileView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblClickEntry(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEndLabelEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

public:
	bool m_bInitialized;
	CMainFrame* m_pMainFrame;
	bool m_bIsLeftPane;
	CFileSystem m_pFileSystem;
	bool m_bShiftPressed;
	bool m_bCtrlPressed;
	bool m_bMenuPressed;

public:
	void ResizeListCtrl();
	void DoubleClickEntry(int nIndex);
	bool RenameClickEntry(int nIndex, CString strText);
	bool Refresh(CString* strNewFolderName = nullptr);
	bool ResetView();
	bool ChangeDrive();
	bool ChangeFolder();
	bool ViewFile();
	bool EditFile();
	bool CopyFile(CFileView* pDestination);
	bool MoveFile(CFileView* pDestination);
	bool NewFolder(CFileView* pDestination);
	bool DeleteFile(CFileView* pDestination);

	DECLARE_MESSAGE_MAP()
};
