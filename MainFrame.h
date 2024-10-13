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

// MainFrame.h : interface of the CMainFrame class
//

#pragma once

#include "FileView.h"

class CMainFrame : public CFrameWndEx
{
protected: 
	DECLARE_DYNAMIC(CMainFrame)
	
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton* m_MainButton;
	CMFCToolBarImages m_PanelImages;
	// CMFCRibbonStatusBar  m_wndStatusBar;
	CMFCCaptionBar    m_wndCaptionBar;
	CSplitterWndEx m_wndSplitter;
	CFileView*    m_wndLeftFileView;
	CFileView*    m_wndRightFileView;
	bool m_bShiftPressed;
	bool m_bCtrlPressed;
	bool m_bMenuPressed;
public:
	CImageList m_pImageList;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();

	afx_msg void OnRefresh();
	afx_msg void OnChangeDrive();
	afx_msg void OnResetView();
	afx_msg void OnSwitchViews();
	afx_msg void OnViewFile();
	afx_msg void OnEditFile();
	afx_msg void OnSelectFile();
	afx_msg void OnSearchFile();
	afx_msg void OnCopyFile();
	afx_msg void OnMoveFile();
	afx_msg void OnNewFolder();
	afx_msg void OnDeleteFile();
	afx_msg void OnQuickAccess();
	afx_msg void OnBase64EncodeDecode();
	afx_msg void OnCommandPrompt();
	afx_msg void OnTwitter();
	afx_msg void OnLinkedin();
	afx_msg void OnFacebook();
	afx_msg void OnInstagram();
	afx_msg void OnIssues();
	afx_msg void OnDiscussions();
	afx_msg void OnWiki();
	afx_msg void OnUserManual();
	afx_msg void OnCheckForUpdates();

public:
	bool CreateCaptionBar();
	bool HideMessageBar();
	bool ShowMessageBar(CString strMessage);
	// bool SetStatusBar(CString strMessage);

	DECLARE_MESSAGE_MAP()
};
