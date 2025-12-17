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

// MainFrame.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "MainFrame.h"
#include "Base64Dlg.h"
#include "WebBrowserDlg.h"
#include "CheckForUpdatesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, &CFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_HELP, &CFrameWndEx::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, &CFrameWndEx::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, &CFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)

	ON_COMMAND(ID_REFRESH, &CMainFrame::OnRefresh)
	ON_COMMAND(ID_CHANGE_DRIVE, &CMainFrame::OnChangeDrive)
	ON_COMMAND(ID_RESET_VIEW, &CMainFrame::OnResetView)
	ON_COMMAND(IDC_SWITCH_VIEWS, &CMainFrame::OnSwitchViews)
	ON_COMMAND(ID_VIEW_FILE, &CMainFrame::OnViewFile)
	ON_COMMAND(ID_EDIT_FILE, &CMainFrame::OnEditFile)
	ON_COMMAND(ID_SELECT_FILE, &CMainFrame::OnSelectFile)
	ON_COMMAND(ID_SEARCH_FILE, &CMainFrame::OnSearchFile)
	ON_COMMAND(ID_COPY_FILE, &CMainFrame::OnCopyFile)
	ON_COMMAND(ID_MOVE_FILE, &CMainFrame::OnMoveFile)
	ON_COMMAND(ID_NEW_FOLDER, &CMainFrame::OnNewFolder)
	ON_COMMAND(ID_DELETE_FILE, &CMainFrame::OnDeleteFile)
	ON_COMMAND(ID_BASE64_ENCODE_DECODE, &CMainFrame::OnBase64EncodeDecode)
	ON_COMMAND(ID_QUICK_ACCESS, &CMainFrame::OnQuickAccess)
	ON_COMMAND(ID_COMMAND_PROMPT, &CMainFrame::OnCommandPrompt)
	ON_COMMAND(IDC_TWITTER, &CMainFrame::OnTwitter)
	ON_COMMAND(IDC_LINKEDIN, &CMainFrame::OnLinkedin)
	ON_COMMAND(IDC_FACEBOOK, &CMainFrame::OnFacebook)
	ON_COMMAND(IDC_INSTAGRAM, &CMainFrame::OnInstagram)
	ON_COMMAND(IDC_ISSUES, &CMainFrame::OnIssues)
	ON_COMMAND(IDC_DISCUSSIONS, &CMainFrame::OnDiscussions)
	ON_COMMAND(IDC_WIKI, &CMainFrame::OnWiki)
	ON_COMMAND(IDC_USER_MANUAL, &CMainFrame::OnUserManual)
	ON_COMMAND(IDC_CHECK_FOR_UPDATES, &CMainFrame::OnCheckForUpdates)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_MainButton = nullptr;
	m_wndLeftFileView = nullptr;
	m_wndRightFileView = nullptr;

	m_bShiftPressed = false;
	m_bCtrlPressed = false;
	m_bMenuPressed = false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	/*if (!m_wndLeftView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}*/

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	m_MainButton = new CMFCRibbonApplicationButton;
	m_MainButton->SetVisible(FALSE);
	m_wndRibbonBar.SetApplicationButton(m_MainButton, CSize());

	/* if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(
		ID_STATUSBAR_PANE1, m_wndLeftFileView->m_pFileSystem.GetCurrentFolder(), TRUE, nullptr,
		_T("012345678901234567890123456789012345678901234567890123456789")), _T("")); */

	// Create a caption bar:
	if (!CreateCaptionBar())
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	return 0;
}

void CMainFrame::OnDestroy()
{
	if ((m_wndLeftFileView != nullptr) && (m_wndRightFileView != nullptr))
	{
		CString strLeftLastFolder = m_wndLeftFileView->m_pFileSystem.GetCurrentFolder();
		CString strRightLastFolder = m_wndRightFileView->m_pFileSystem.GetCurrentFolder();
		theApp.WriteString( _T("LeftLastFolder"), strLeftLastFolder);
		theApp.WriteString(_T("RightLastFolder"), strRightLastFolder);
	}
	CFrameWndEx::OnDestroy();
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect rectClient;
	GetClientRect(&rectClient);

	const int nDefaultViewWidth = (rectClient.Width() - 12) / 2;
	const int nDefaultViewHeight = rectClient.Height();

	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CFileView), CSize(nDefaultViewWidth, nDefaultViewHeight), pContext))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFileView), CSize(nDefaultViewWidth, nDefaultViewHeight), pContext))
		return FALSE;

	if ((m_wndLeftFileView = (CFileView*) m_wndSplitter.GetPane(0, 0)) != nullptr)
	{
		m_wndLeftFileView->m_pMainFrame = this;
		m_wndLeftFileView->m_bIsLeftPane = true;
		m_wndLeftFileView->m_pFileSystem.SetCurrentFolder(theApp.GetString( _T("LeftLastFolder"), _T("C:\\")));
		VERIFY(m_wndLeftFileView->Refresh());
	}

	if ((m_wndRightFileView = (CFileView*) m_wndSplitter.GetPane(0, 1)) != nullptr)
	{
		m_wndRightFileView->m_pMainFrame = this;
		m_wndRightFileView->m_bIsLeftPane = false;
		m_wndRightFileView->m_pFileSystem.SetCurrentFolder(theApp.GetString(_T("RightLastFolder"), _T("C:\\")));
		VERIFY(m_wndRightFileView->Refresh());
	}

	ASSERT(m_wndLeftFileView->m_bIsLeftPane != m_wndRightFileView->m_bIsLeftPane);
	SetActiveView(m_wndRightFileView);

	SHFILEINFO pshFileInfo = { 0 };
	HIMAGELIST hSystemImageList =
		(HIMAGELIST) SHGetFileInfo(
		_T(""),
		0,
		&pshFileInfo,
		sizeof(pshFileInfo),
		SHGFI_ICON | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	if (hSystemImageList != nullptr)
	{
		VERIFY(m_pImageList.Attach(hSystemImageList));
		m_wndLeftFileView->GetListCtrl().SetImageList(&m_pImageList, LVSIL_SMALL);
		m_wndRightFileView->GetListCtrl().SetImageList(&m_pImageList, LVSIL_SMALL);
	}

	return CFrameWndEx::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	const int nDefaultViewWidth = (cx - 12) / 2;
	// const int nDefaultViewHeight = cy;

	if (m_wndSplitter.GetSafeHwnd() != nullptr)
	{
		m_wndSplitter.SetColumnInfo(0, nDefaultViewWidth, 100);
		m_wndSplitter.SetColumnInfo(1, nDefaultViewWidth, 100);
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg != nullptr)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
				case VK_MENU:
				{
					m_bMenuPressed = true;
					break;
				}
			}
		}
		if (pMsg->message == WM_KEYUP)
		{
			m_bCtrlPressed = (GetAsyncKeyState(VK_CONTROL) != 0);
			m_bShiftPressed = (GetAsyncKeyState(VK_SHIFT) != 0);

			switch (pMsg->wParam)
			{
				case VK_MENU:
				{
					m_bMenuPressed = false;
					break;
				}
				case VK_TAB:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						CFileView* pActiveView = (CFileView*) GetActiveView();
						ASSERT_VALID(pActiveView);
						SetActiveView(pActiveView->m_bIsLeftPane ? m_wndRightFileView : m_wndLeftFileView);
						return TRUE;
					}
					break;
				}
				case VK_RETURN:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						CFileView* pActiveView = (CFileView*) GetActiveView();
						ASSERT_VALID(pActiveView);
						const int nListItem = pActiveView->GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
						if (nListItem != -1)
						{
							pActiveView->DoubleClickEntry(nListItem);
							return TRUE;
						}
					}
					break;
				}
				case VK_F2:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnRefresh();
						return TRUE;
					}
					break;
				}
				case VK_F3:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnViewFile();
						return TRUE;
					}
					break;
				}
				case VK_F4:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnEditFile();
						return TRUE;
					}
					break;
				}
				case VK_F5:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnCopyFile();
						return TRUE;
					}
					break;
				}
				case VK_F6:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnMoveFile();
						return TRUE;
					}
					break;
				}
				case VK_F7:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnNewFolder();
						return TRUE;
					}
					break;
				}
				case VK_F8:
				{
					if (!m_bMenuPressed && !m_bCtrlPressed && !m_bShiftPressed)
					{
						OnDeleteFile();
						return TRUE;
					}
					break;
				}
			}
		}
	}

	return CFrameWndEx::PreTranslateMessage(pMsg);
}

bool CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	bool bNameValid;
	CString strTemp, strTemp2;
	/*bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);*/

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	ASSERT_VALID(m_wndLeftFileView);
	m_wndLeftFileView->m_pFileSystem.SetWindow(&m_wndCaptionBar);
	ASSERT_VALID(m_wndRightFileView);
	m_wndRightFileView->m_pFileSystem.SetWindow(&m_wndCaptionBar);

	return true;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	// m_wndLeftView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	// if (m_wndLeftView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		// return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != nullptr);

	pOptionsDlg->DoModal();
delete pOptionsDlg;
}

bool CMainFrame::HideMessageBar()
{
	m_wndCaptionBar.ShowWindow(SW_HIDE);
	m_wndCaptionBar.Invalidate();
	m_wndCaptionBar.UpdateWindow();
	RecalcLayout();
	return true;
}

bool CMainFrame::ShowMessageBar(CString strMessage)
{
	m_wndCaptionBar.SetText(strMessage, CMFCCaptionBar::ALIGN_LEFT);
	m_wndCaptionBar.ShowWindow(SW_SHOW);
	m_wndCaptionBar.Invalidate();
	m_wndCaptionBar.UpdateWindow();
	return true;
}

/* bool CMainFrame::SetStatusBar(CString strMessage)
{
	if (m_wndStatusBar.GetSafeHwnd() != nullptr)
	{
		m_wndStatusBar.GetElement(0)->SetText(strMessage);
		m_wndStatusBar.Invalidate();
		m_wndStatusBar.UpdateWindow();
		return true;
	}
	return false;
} */

void CMainFrame::OnRefresh()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->Refresh(nullptr));
}

void CMainFrame::OnChangeDrive()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->ChangeDrive());
}

void CMainFrame::OnResetView()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->ResetView());
}

void CMainFrame::OnSwitchViews()
{
	ASSERT_VALID(m_wndLeftFileView);
	CString strLeftFolder = m_wndLeftFileView->m_pFileSystem.GetCurrentFolder();
	ASSERT_VALID(m_wndRightFileView);
	CString strRightFolder = m_wndRightFileView->m_pFileSystem.GetCurrentFolder();
	if (strLeftFolder.CompareNoCase(strRightFolder) != 0)
	{
		m_wndLeftFileView->m_pFileSystem.SetCurrentFolder(strRightFolder);
		m_wndLeftFileView->Refresh(nullptr);
		m_wndRightFileView->m_pFileSystem.SetCurrentFolder(strLeftFolder);
		m_wndRightFileView->Refresh(nullptr);
	}
}

void CMainFrame::OnViewFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->ViewFile());
}

void CMainFrame::OnEditFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->EditFile());
}

void CMainFrame::OnSelectFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->SelectFile());
}

void CMainFrame::OnSearchFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->SearchFile());
}

void CMainFrame::OnCopyFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->CopyFile(pActiveView->m_bIsLeftPane ? m_wndRightFileView : m_wndLeftFileView));
}

void CMainFrame::OnMoveFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->MoveFile(pActiveView->m_bIsLeftPane ? m_wndRightFileView : m_wndLeftFileView));
}

void CMainFrame::OnNewFolder()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->NewFolder(pActiveView->m_bIsLeftPane ? m_wndRightFileView : m_wndLeftFileView));
}

void CMainFrame::OnDeleteFile()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->DeleteFile(pActiveView->m_bIsLeftPane ? m_wndRightFileView : m_wndLeftFileView));
}

void CMainFrame::OnQuickAccess()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->QuickAccess());
}

void CMainFrame::OnBase64EncodeDecode()
{
	CBase64Dlg dlgBase64(this);
	dlgBase64.DoModal();
}

void CMainFrame::OnCommandPrompt()
{
	CFileView* pActiveView = (CFileView*)GetActiveView();
	ASSERT_VALID(pActiveView);
	VERIFY(pActiveView->CommandPrompt());
}

void CMainFrame::OnTwitter()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://x.com/stefanmihaimoga"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnLinkedin()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://www.linkedin.com/in/stefanmihaimoga/"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnFacebook()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://www.facebook.com/stefanmihaimoga"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnInstagram()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://www.instagram.com/stefanmihaimoga/"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnIssues()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://github.com/mihaimoga/IntelliFile/issues"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnDiscussions()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://github.com/mihaimoga/IntelliFile/discussions"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnWiki()
{
	::ShellExecute(GetSafeHwnd(), _T("open"), _T("https://github.com/mihaimoga/IntelliFile/wiki"), nullptr, nullptr, SW_SHOW);
}

void CMainFrame::OnUserManual()
{
	CWebBrowserDlg dlgWebBrowser(this);
	dlgWebBrowser.DoModal();
}

void CMainFrame::OnCheckForUpdates()
{
	CCheckForUpdatesDlg dlgCheckForUpdates(this);
	dlgCheckForUpdates.DoModal();
}
